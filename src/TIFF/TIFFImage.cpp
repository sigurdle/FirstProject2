#include "stdafx.h"
#include "TIFF.h"
#include "TIFFImage.h"
#include "TIFFFile.h"
#include "../LMedia/LZWDecoder.h"

#include <memory>

namespace System
{
namespace Imaging
{

TIFFImage::TIFFImage()
{
	m_file = nullptr;

	m_imageWidth = 0;
	m_imageHeight = 0;
	m_bitsPerSample = 0;
	m_colorMap = nullptr;
	m_colorMapSize = 0;
}

bool TIFFImage::ReadDirectory()
{
	uint16 count;
	if (!m_file->ReadWord(&count))
	{
		return false;
	}

	for (int i = 0; i < count; ++i)
	{
		CTIFFField* pField = new CTIFFField;

		ULONG nRead;
		nRead = m_file->m_stream->Read(&pField->m_entry, 12);
		if (nRead != 12)
		{
			return false;
		}

		pField->m_entry.tag = m_file->EndianWord(pField->m_entry.tag);
		pField->m_entry.type = m_file->EndianWord(pField->m_entry.type);
		pField->m_entry.count = m_file->EndianLong(pField->m_entry.count);

		m_fields.push_back(pField);
	}

	LONGLONG pos = m_file->m_stream->position;//Seek(0, System::IO::STREAM_SEEK_CUR);
//	LONGLONG pos = m_file->m_stream->Seek(0, System::IO::STREAM_SEEK_CUR);

//////
	m_imageWidth = 0;
	if (!GetTIFFFieldLongValues(256, 1, &m_imageWidth))
		return false;

	m_imageHeight = 0;
	if (!GetTIFFFieldLongValues(257, 1, &m_imageHeight))
		return false;

	m_bitsPerSample = 1;	// Default
	if (!GetTIFFFieldLongValues(258, 1, &m_bitsPerSample))
		return false;

	if (!GetTIFFFieldLongValues(259, 1, (int*)&m_compression))
		return false;

//	m_photoMetricInterpretation = PhotoMetricInterpretation_0;
	if (!GetTIFFFieldShortValues(262, 1, (short*)&m_photoMetricInterpretation))
		return false;

	GetTIFFFieldCount(320, &m_colorMapSize);
	if (m_colorMapSize > 0)
	{
		m_colorMap = new uint16[m_colorMapSize];

		if (!GetTIFFFieldShortValues(320, m_colorMapSize, (SHORT*)m_colorMap))
			return false;
	}

	m_file->m_stream->Seek(pos, System::IO::STREAM_SEEK_SET);

	return true;
}

void TIFFImage::GetTIFFFieldCount(uint16 tag, int32* count)
{
	for (size_t i = 0; i < m_fields.size(); ++i)
	{
		CTIFFField* pField = m_fields[i];

		if (pField->m_entry.tag == tag)
		{
			*count = pField->m_entry.count;
		//	return 0;
		}
	}

	*count = 0;
//	return 1;
}

bool TIFFImage::GetTIFFFieldShortValues(uint16 tag, int count, short* values)
{
	for (int i = 0; i < m_fields.size(); ++i)
	{
		CTIFFField* pField = m_fields[i];

		if (pField->m_entry.tag == tag)
		{
			if (pField->m_entry.type != IFDTYPE_SHORT)
			{
				raise(Exception("Expected short EntryType"));
			}

			if (GetTypeSize(pField->m_entry.type) * pField->m_entry.count <= 2)
			{
				ASSERT(count == 1);	// TODO remove

				if (pField->m_entry.type == IFDTYPE_SHORT)
				{
				// Not tested
					values[0] = (uint16)m_file->EndianWord((uint16)(pField->m_entry.value & 0xffff));
				}
			}
			else
			{
				m_file->m_stream->position = m_file->EndianLong(pField->m_entry.offset);//Seek(m_file->EndianLong(pField->m_entry.offset), IO::SeekOrigin_Set);
				//m_file->m_stream->Seek(m_file->EndianLong(pField->m_entry.offset), IO::SeekOrigin_Set);

				for (int i = 0; i < count; i++)
				{
					ULONG nRead;

					if (pField->m_entry.type == IFDTYPE_SHORT)
					{
						SHORT value;
						nRead = m_file->m_stream->Read(&value, 2);
						values[i] = m_file->EndianWord(value);
					}
				}
			}

			return true;
		}
	}

	return false;
}

bool TIFFImage::GetTIFFFieldLongValues(uint16 tag, int count, int32* values)
{
	for (int i = 0; i < m_fields.size(); ++i)
	{
		CTIFFField* pField = m_fields[i];

		if (pField->m_entry.tag == tag)
		{
			if (GetTypeSize(pField->m_entry.type) * pField->m_entry.count <= 4)
			{
				ASSERT(count == 1);	// TODO remove

				if (pField->m_entry.type == IFDTYPE_LONG)
				{
					values[0] = (LONG)m_file->EndianLong(pField->m_entry.value);
				}
				else if (pField->m_entry.type == IFDTYPE_SHORT)
				{
					values[0] = (LONG)m_file->EndianWord((uint16)(pField->m_entry.value & 0xffff));
				}
			}
			else
			{
				m_file->m_stream->Seek(m_file->EndianLong(pField->m_entry.offset), IO::STREAM_SEEK_SET);

				for (int i = 0; i < count; i++)
				{
					ULONG nRead;

					if (pField->m_entry.type == IFDTYPE_LONG)
					{
						int32 value;
						nRead = m_file->m_stream->Read(&value, 4);
						values[i] = m_file->EndianLong(value);
					}
					else if (pField->m_entry.type == IFDTYPE_SHORT)
					{
						int16 value;
						nRead = m_file->m_stream->Read(&value, 2);
						values[i] = m_file->EndianWord(value);
					}
				}
			}

			return true;
		}
	}

	return false;
}

int TIFFImage::ReadImage(void* data, int rowbytes, int rows, int bitcount)
{
	size_t nRead;

	int16 predictor = 1;	// Defaults to no prediction
	GetTIFFFieldShortValues(317, 1, &predictor);

	int32 rowsPerStrip;
	GetTIFFFieldLongValues(278, 1, &rowsPerStrip);

	int32 nStripOffsets;
	GetTIFFFieldCount(273, &nStripOffsets);

	std::unique_ptr<uint32> stripOffsets(new uint32[nStripOffsets]);

	GetTIFFFieldLongValues(273, nStripOffsets, (int32*)stripOffsets.get());

	int bytesPerRow;

	if (m_bitsPerSample == 1)	// Bilevel
	{
		bytesPerRow = (m_imageWidth*m_bitsPerSample+7) / 8;
	}
	else if (m_photoMetricInterpretation <= 1)	// Grayscale
	{
		bytesPerRow = (m_imageWidth*m_bitsPerSample+7) / 8;
	}
	else if (m_photoMetricInterpretation == 3 && m_colorMap != NULL)	// Paletted image
	{
		bytesPerRow = (m_imageWidth*m_bitsPerSample+7) / 8;
	}
	else if (m_photoMetricInterpretation == 2)	// RGB
	{
		bytesPerRow = (m_imageWidth*(m_bitsPerSample*3)+7) / 8;
	}
	else
	{
		raise(Exception("Unsupported photoMetricInterpretation"));
	}

	std::unique_ptr<ubyte> buffer(new ubyte[bytesPerRow]);

	int nrow = 0;
	for (int i = 0; i < nStripOffsets; i++)
	{
		m_file->m_stream->Seek(stripOffsets.get()[i], IO::STREAM_SEEK_SET);

		int nStripRows = rowsPerStrip;
		if (nrow + nStripRows > m_imageHeight)
			nStripRows = m_imageHeight-nrow;

		if (m_compression == TiffCompression_Uncompressed)	// Uncompressed
		{
			for (int stripRow = 0; stripRow < nStripRows; stripRow++)
			{
				if (m_bitsPerSample == 1)	// Bilevel
				{
					ubyte* dst = (ubyte*)data + rowbytes*(nrow+stripRow);

					if (bitcount == 1)
					{
						nRead = m_file->m_stream->Read(dst, bytesPerRow);
					}
					else
					{
						nRead = m_file->m_stream->Read(buffer.get(), bytesPerRow);

						ubyte* src = buffer.get();

						int bit = 7;	// start with left-most bit, decreasing towards right

						for (int x = 0; x < m_imageWidth; ++x)
						{
							// I think this is wrong
							//int value = (*src & (1<<bit));
							// It should probably be something like:
							int value = (*src >> bit) & 1;

							if (m_photoMetricInterpretation == 0)
							{
								value = 1-value;
							}

							if (bitcount == 4)
							{
								if (x & 1)
									*dst++ |= value;
								else
									*dst = value<<4;
							}
							else if (bitcount == 8)
							{
								*dst++ = value;
							}
							else if (bitcount == 24)
							{
								dst[0] = value*255;
								dst[1] = value*255;
								dst[2] = value*255;

								dst += 3;
							}
							else if (bitcount == 32)
							{
								dst[0] = value*255;
								dst[1] = value*255;
								dst[2] = value*255;
								dst[3] = 255;

								dst += 4;
							}
							else
								ASSERT(0);

							if (--bit == -1)
							{
								src++;
								bit = 7;
							}
						}
					}
				}
				else if (m_photoMetricInterpretation <= 1)	// Grayscale
				{
					nRead = m_file->m_stream->Read(buffer.get(), bytesPerRow);
					if (nRead < bytesPerRow) return nrow+stripRow;

					ubyte* dst = (ubyte*)data + rowbytes*(nrow+stripRow);
					ubyte* src = buffer.get();

					for (int x = 0; x < m_imageWidth; x++)
					{
						int value;
						if (m_bitsPerSample == 4)
						{
							if (x & 1)
								value = *src++ & 0xf;
							else
								value = (*src) >> 4;

							value = (value<<4) | value;	// 4-bit to 8-bit conversion
						}
						else// if (m_bitsPerSample == 8)
						{
							value = *src++;
						}

						if (m_photoMetricInterpretation == 0)
						{
							value = 255-value;
						}

						if (bitcount == 8)
						{
							*dst++ = value;
						}
						else if (bitcount == 24)
						{
							dst[0] = value;
							dst[1] = value;
							dst[2] = value;
							dst += 3;
						}
						else if (bitcount == 32)
						{
							dst[0] = value;
							dst[1] = value;
							dst[2] = value;
							dst[3] = 255;
							dst += 4;
						}
						else
							ASSERT(0);
					}
				}
				else if (m_photoMetricInterpretation == 3 && m_colorMap != nullptr)	// Paletted image
				{
					int ncolors = 1<<m_bitsPerSample;
					nRead = m_file->m_stream->Read(buffer.get(), bytesPerRow);
					if (nRead < bytesPerRow) return nrow+stripRow;

					ubyte* dst = (ubyte*)data + rowbytes*(nrow+stripRow);
					ubyte* src = buffer.get();

					for (int x = 0; x < m_imageWidth; ++x)
					{
						uint8 index;

						if (m_bitsPerSample == 4)
						{
							if (x & 1)
								index = *src++ & 0xf;
							else
								index = (*src) >> 4;
						}
						else// if (m_bitsPerSample == 8)
						{
							index = *src++;
						}

						if (bitcount == 8)
						{
							*dst++ = index;
						}
						else if (bitcount == 24)
						{
							dst[0] = m_colorMap[index + ncolors*2]>>8;
							dst[1] = m_colorMap[index + ncolors*1]>>8;
							dst[2] = m_colorMap[index + ncolors*0]>>8;
							dst += 3;
						}
						else if (bitcount == 32)
						{
							dst[0] = m_colorMap[index + ncolors*2]>>8;
							dst[1] = m_colorMap[index + ncolors*1]>>8;
							dst[2] = m_colorMap[index + ncolors*0]>>8;
							dst[3] = 255;
							dst += 4;
						}
					}
				}
				else if (m_photoMetricInterpretation == 2)	// RGB
				{
					nRead = m_file->m_stream->Read(buffer.get(), bytesPerRow);
					if (nRead < bytesPerRow) return nrow+stripRow;

					ubyte* dst = (ubyte*)data + rowbytes*(nrow+stripRow);
					ubyte* src = buffer.get();

					for (int x = 0; x < m_imageWidth; x++)
					{
						if (bitcount == 32)
						{
							dst[0] = src[2];
							dst[1] = src[1];
							dst[2] = src[0];
							dst[3] = 255;
							dst += 4;
						}
						else
						{
							dst[0] = src[2];
							dst[1] = src[1];
							dst[2] = src[0];
							dst += 3;
						}

						src += 3;
					}
				}
			}
		}
		else if (m_compression == TiffCompression_LZW)	// LZW
		{
			TIFFBitStream bitstream(m_file->m_stream);
			LZWDecoder<1> decoder(&bitstream, 8);

			if (m_photoMetricInterpretation == 2)	// RGB
			{
				for (int stripRow = 0; stripRow < nStripRows; stripRow++)
				{
					int bytesPerRow = (m_imageWidth*(m_bitsPerSample*3)+7) / 8;

					ubyte* dst = (ubyte*)data + rowbytes*(nrow+stripRow);
					//LPBYTE src = buffer;

					for (int x = 0; x < m_imageWidth; ++x)
					{
						int r = decoder.GetNextChar();
						if (r < 0) return nrow+stripRow;

						int g = decoder.GetNextChar();
						if (g < 0) return nrow+stripRow;

						int b = decoder.GetNextChar();
						if (b < 0) return nrow+stripRow;

						if (bitcount == 32)
						{
							dst[0] = r;
							dst[1] = g;
							dst[2] = b;
							dst[3] = 255;
							dst += 4;
						}
						else
						{
							dst[2] = r;
							dst[1] = g;
							dst[0] = b;
							dst += 3;
						}
					}
				}

		//		ATLTRACE("%d\n", count);
/*
				int Code;
				int OldCode;

				while ((Code = decoder.getnbits(m_codeBitSize)) != EoiCode)
				{
					if (Code == ClearCode)
					{
						CodeBitSize = 9;
						StringTableSize = 258;

						Code = GetNextCode();
						if (Code == EoiCode)
							break;

						OldCode = Code;
					}
					else
					{
						if (Code < StringTableSize)
						{
						}
						else
						{
						}
					}
				}
				*/
			}
			else
				ASSERT(0);
		}

		nrow += nStripRows;
	}

	return rows;
}

}	// Imaging
}	// System
