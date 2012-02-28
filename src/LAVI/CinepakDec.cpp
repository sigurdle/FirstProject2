#include "stdafx.h"
#include "CinepakDec.h"

namespace System
{
namespace Media
{

int CinepakDecoder::Decode(const uint8* ptr, uint32 buflength, uint8* out, uint32 rowbytes)
{
	uint32 length = buflength;

	if (length < 10)
	{
		TRACE("Buffer not large enough");
		return -1;
	}

	uint8 flags = *ptr++;

	int cvidlen = (*ptr++) << 16;
	cvidlen |= (*ptr++) << 8;
	cvidlen |= (*ptr++);

	if (length < cvidlen)
	{
		TRACE("%s(%d): cvidlen (%x) larger than buffer size (%x)\n", __FILE__, __LINE__, cvidlen, length);
		return -1;
	}

	uint16 width = (*ptr++) << 8;
	width |= (*ptr++);

	uint16 height = (*ptr++) << 8;
	height |= (*ptr++);

	uint16 nstrips = (*ptr++) << 8;
	nstrips |= (*ptr++);

	length -= 10;

	width >>= 2;
	height >>= 2;

	int nblock = 0;

	for (int nstrip = 0; nstrip < nstrips; nstrip++)
	{
		if (!(flags & 1))
		{
		}

		if (length < 12)
		{
			TRACE("Buffer not large enough");
			return -1;
		}

		uint16 stripid = (*ptr++) << 8;
		stripid |= (*ptr++);

		if (stripid != 0x1000 && stripid != 0x1100)
		{
			TRACE("Unsupported stripid: %x\n", stripid);
		}

		int stripsize = (*ptr++) << 8;
		stripsize |= (*ptr++);

		uint16 topy = (*ptr++) << 8;
		topy |= (*ptr++);

		uint16 topx = (*ptr++) << 8;
		topx |= (*ptr++);

		uint16 bottomy = (*ptr++) << 8;
		bottomy |= (*ptr++);

		uint16 bottomx = (*ptr++) << 8;
		bottomx |= (*ptr++);

		topy >>= 2;
		topx >>= 2;
		bottomy >>= 2;
		bottomx >>= 2;

//		length -= 12;
	//	stripsize -= 12;

		if (length < stripsize)
		{
			TRACE("Buffer not large enough");
			return -1;
		}
		length -= stripsize;
		stripsize -= 12;

		while (stripsize > 0)
		{
			if (stripsize < 4)
			{
				TRACE("Buffer not large enough");
				return -1;
			}

			uint16 chunkid = (*ptr++) << 8;
			chunkid |= (*ptr++);

			int chunksize = (*ptr++) << 8;
			chunksize |= (*ptr++);

			if (stripsize < chunksize)
			{
				TRACE("Buffer not large enough");
				return -1;
			}

			stripsize -= chunksize;
			chunksize -= 4;

			//if (stripid == 0x1000)	// intra
			{
				switch (chunkid)
				{
				case 0x2000:// - List of blocks in 12 bit V4 codebook
					{
						int count = chunksize / 6;
						for (int i = 0; i < count; i++)
						{
							V4[i].c[0] = *ptr++;
							V4[i].c[1] = *ptr++;
							V4[i].c[2] = *ptr++;
							V4[i].c[3] = *ptr++;
							V4[i].c[4] = *ptr++;
							V4[i].c[5] = *ptr++;
						}

						chunksize = 0;
					}
					break;

				case 0x2200:// - List of blocks in 12 bit V1 codebook
					{
						int count = chunksize / 6;
						for (int i = 0; i < count; i++)
						{
							V1[i].c[0] = *ptr++;
							V1[i].c[1] = *ptr++;
							V1[i].c[2] = *ptr++;
							V1[i].c[3] = *ptr++;
							V1[i].c[4] = *ptr++;
							V1[i].c[5] = *ptr++;
						}

						chunksize = 0;
					}
					break;

				case 0x3000:	// Vectors used to encode a frame
					{
						int n = nblock;//topy*width;// + topx;
						int last = nblock + (bottomy)*width;// + bottomx;

						while (chunksize > 0 && n < last)
						{
							uint32 select = (*ptr++)<<24;
							select |= (*ptr++)<<16;
							select |= (*ptr++)<<8;
							select |= (*ptr++);

							chunksize -= 4;

							for (int i = 0; i < 32; i++)
							{
								if (n >= last) break;

								int x = (n % width) * 4;
								int y = (n / width) * 4;

								if (select & (1<<31))
								{
									uint8 r0 = *ptr++;
									uint8 r1 = *ptr++;
									uint8 r2 = *ptr++;
									uint8 r3 = *ptr++;

									uint8* p11 = out + y*rowbytes + x;

									p11[0] = V4[r0].c[0];
									p11[1+0] = V4[r0].c[1];
									p11[2+0] = V4[r1].c[0];
									p11[3+0] = V4[r1].c[1];

									p11[rowbytes+0] = V4[r0].c[2];
									p11[rowbytes+1+0] = V4[r0].c[3];
									p11[rowbytes+2+0] = V4[r1].c[2];
									p11[rowbytes+3+0] = V4[r1].c[3];

									p11[rowbytes*2+0] = V4[r2].c[0];
									p11[rowbytes*2+1+0] = V4[r2].c[1];
									p11[rowbytes*2+2+0] = V4[r3].c[0];
									p11[rowbytes*2+3+0] = V4[r3].c[1];

									p11[rowbytes*3+0] = V4[r2].c[2];
									p11[rowbytes*3+1+0] = V4[r2].c[3];
									p11[rowbytes*3+2+0] = V4[r3].c[2];
									p11[rowbytes*3+3+0] = V4[r3].c[3];

									chunksize -= 4;
								}
								else
								{
									uint8 r = *ptr++;

									uint8* p11 = out + y*rowbytes + x;

									CodeEntry12& v1entry = V1[r];

									p11[0] = v1entry.c[0];
									p11[1+0] = v1entry.c[1];
									p11[2+0] = v1entry.c[0];
									p11[3+0] = v1entry.c[1];

									p11[rowbytes+0] = v1entry.c[2];
									p11[rowbytes+1+0] = v1entry.c[3];
									p11[rowbytes+2+0] = v1entry.c[2];
									p11[rowbytes+3+0] = v1entry.c[3];

									p11[rowbytes*2+0] = v1entry.c[0];
									p11[rowbytes*2+1+0] = v1entry.c[1];
									p11[rowbytes*2+2+0] = v1entry.c[0];
									p11[rowbytes*2+3+0] = v1entry.c[1];

									p11[rowbytes*3+0] = v1entry.c[2];
									p11[rowbytes*3+1+0] = v1entry.c[3];
									p11[rowbytes*3+2+0] = v1entry.c[2];
									p11[rowbytes*3+3+0] = v1entry.c[3];

									chunksize -= 1;
								}

								select <<= 1;
								n++;
							}
						}

						nblock = last;
					}
					break;

				case 0x3200:	// List of blocks from only the V1 codebook
					{
						int n = nblock;//topy*width;// + topx;
						int last = nblock + (bottomy)*width;// + bottomx;

						while (chunksize > 0 && n < last)
						{
							int x = (n % width) * 4;
							int y = (n / width) * 4;

							uint8 r = *ptr++;
							CodeEntry12& v1entry = V1[r];

							uint8* p11 = out + y*rowbytes + x;

							p11[0] = v1entry.c[0];
							p11[1+0] = v1entry.c[1];
							p11[2+0] = v1entry.c[0];
							p11[3+0] = v1entry.c[1];

							p11[rowbytes+0] = v1entry.c[2];
							p11[rowbytes+1+0] = v1entry.c[3];
							p11[rowbytes+2+0] = v1entry.c[2];
							p11[rowbytes+3+0] = v1entry.c[3];

							p11[rowbytes*2+0] = v1entry.c[0];
							p11[rowbytes*2+1+0] = v1entry.c[1];
							p11[rowbytes*2+2+0] = v1entry.c[0];
							p11[rowbytes*2+3+0] = v1entry.c[1];

							p11[rowbytes*3+0] = v1entry.c[2];
							p11[rowbytes*3+1+0] = v1entry.c[3];
							p11[rowbytes*3+2+0] = v1entry.c[2];
							p11[rowbytes*3+3+0] = v1entry.c[3];

							chunksize -= 1;
							n++;
						}

						nblock = last;
					}
					break;

				case 0x2100:	// Selective list of blocks to update 12 bit V4 codebook
					{
						int i = 0;
						while (i < 256)
						{
							if (chunksize < 4)
								break;

							uint32 update = (*ptr++) << 24;
							update |= (*ptr++) << 16;
							update |= (*ptr++) << 8;
							update |= (*ptr++);

							chunksize -= 4;

							for (int ibit = 0; ibit < 32; ibit++)
							{
								if (update & (1<<31))
								{
									V4[i].c[0] = *ptr++;
									V4[i].c[1] = *ptr++;
									V4[i].c[2] = *ptr++;
									V4[i].c[3] = *ptr++;
									V4[i].c[4] = *ptr++;
									V4[i].c[5] = *ptr++;

									chunksize -= 6;
								}

								i++;
								update <<= 1;
							}
						}
					}
					break;

				case 0x2300:	// Selective list of blocks to update 12 bit V1 codebook
					{
						int i = 0;
						while (i < 256)
						{
							if (chunksize < 4)
								break;

							uint32 update = (*ptr++) << 24;
							update |= (*ptr++) << 16;
							update |= (*ptr++) << 8;
							update |= (*ptr++);

							chunksize -= 4;

							for (int ibit = 0; ibit < 32; ibit++)
							{
								if (update & (1<<31))
								{
									V1[i].c[0] = *ptr++;
									V1[i].c[1] = *ptr++;
									V1[i].c[2] = *ptr++;
									V1[i].c[3] = *ptr++;
									V1[i].c[4] = *ptr++;
									V1[i].c[5] = *ptr++;

									chunksize -= 6;
								}

								i++;
								update <<= 1;
							}
						}
					}
					break;

				case 0x3100:	// Selective set of vectors used to encode a frame
					{
						int n = nblock;//topy*width;// + topx;
						int last = nblock + (bottomy)*width;// + bottomx;

						while (chunksize > 0 && n < last)
						{
							uint32 select = (*ptr++)<<24;
							select |= (*ptr++)<<16;
							select |= (*ptr++)<<8;
							select |= (*ptr++);

							chunksize -= 4;

							uint32 mask = 1<<31;

							int i = 0;
							while (mask)
							{
								if (n >= last) break;

								if (select & mask)
								{
									if (mask == 1)
									{
										if (chunksize < 4)
											break;

										select = (*ptr++)<<24;
										select |= (*ptr++)<<16;
										select |= (*ptr++)<<8;
										select |= (*ptr++);
										mask = 1<<31;

										chunksize -= 4;
									}
									else
										mask >>= 1;

									int x = (n % width) * 4;
									int y = (n / width) * 4;

									if (select & mask)
									{
										uint8 r0 = *ptr++;
										uint8 r1 = *ptr++;
										uint8 r2 = *ptr++;
										uint8 r3 = *ptr++;

										uint8* p11 = out + y*rowbytes + x;

										p11[0] = V4[r0].c[0];
										p11[1+0] = V4[r0].c[1];
										p11[2+0] = V4[r1].c[0];
										p11[3+0] = V4[r1].c[1];

										p11[rowbytes+0] = V4[r0].c[2];
										p11[rowbytes+1+0] = V4[r0].c[3];
										p11[rowbytes+2+0] = V4[r1].c[2];
										p11[rowbytes+3+0] = V4[r1].c[3];

										p11[rowbytes*2+0] = V4[r2].c[0];
										p11[rowbytes*2+1+0] = V4[r2].c[1];
										p11[rowbytes*2+2+0] = V4[r3].c[0];
										p11[rowbytes*2+3+0] = V4[r3].c[1];

										p11[rowbytes*3+0] = V4[r2].c[2];
										p11[rowbytes*3+1+0] = V4[r2].c[3];
										p11[rowbytes*3+2+0] = V4[r3].c[2];
										p11[rowbytes*3+3+0] = V4[r3].c[3];

										chunksize -= 4;
									}
									else
									{
										uint8 r0 = *ptr++;
										uint8 r1 = r0;
										uint8 r2 = r0;
										uint8 r3 = r0;

										uint8* p11 = out + y*rowbytes + x;

										p11[0] = V1[r0].c[0];
										p11[1+0] = V1[r0].c[1];
										p11[2+0] = V1[r1].c[0];
										p11[3+0] = V1[r1].c[1];

										p11[rowbytes+0] = V1[r0].c[2];
										p11[rowbytes+1+0] = V1[r0].c[3];
										p11[rowbytes+2+0] = V1[r1].c[2];
										p11[rowbytes+3+0] = V1[r1].c[3];

										p11[rowbytes*2+0] = V1[r2].c[0];
										p11[rowbytes*2+1+0] = V1[r2].c[1];
										p11[rowbytes*2+2+0] = V1[r3].c[0];
										p11[rowbytes*2+3+0] = V1[r3].c[1];

										p11[rowbytes*3+0] = V1[r2].c[2];
										p11[rowbytes*3+1+0] = V1[r2].c[3];
										p11[rowbytes*3+2+0] = V1[r3].c[2];
										p11[rowbytes*3+3+0] = V1[r3].c[3];

										chunksize -= 1;
									}
								}	// skipped block

								mask >>= 1;
								n++;
							}
						}

						nblock = last;
					}
					break;

				default:
					ASSERT(0);
				}
			}

			ptr += chunksize;
		}
	}

	return buflength - length;
}

ErrorCode CinepakDec::InputPin::CompleteConnect(IPin* pPin)
{
	ErrorCode hr;
	hr = BasePinImpl::CompleteConnect(pPin);
	if (hr < 0) return hr;

	VideoInfoHeader* vih = (VideoInfoHeader*)m_mt->GetFormat();

	ybuf = new uint8[vih->vih->bmiHeader.biWidth * vih->vih->bmiHeader.biHeight];

	return Success;
}

bool CinepakDec::InputPin::Receive(IMediaSample *pBuffer)
{
	ULONG length;
	length = pBuffer->GetActualDataLength();

	LSampleData buffersampledata;
	if (pBuffer->LockBits(&buffersampledata) >= 0)
	{
		IMediaSample* videoSample;
		m_pFilter->m_pOutput->m_pAllocator->GetBuffer(0, &videoSample);
		if (videoSample)
		{
			LSampleData sampledata;
			videoSample->LockBits(&sampledata);

		//	memcpy(sampledata.idata, 0, sampledata.rowbytes*sampledata.height);
			dec.Decode(buffersampledata.idata, length, ybuf, sampledata.width);

			for (int y = 0; y < sampledata.height; y++)
			{
				uint8* src = ybuf + sampledata.width*y;
				uint8* dst = sampledata.idata + sampledata.rowbytes*y;

				for (int x = 0; x < sampledata.width; x++)
				{
					dst[0] = *src;
					dst[1] = *src;
					dst[2] = *src;

					dst += 3;
					src += 1;
				}
			}

			videoSample->UnlockBits();

			m_pFilter->m_pOutput->m_pInputPin->Receive(videoSample);

			videoSample->Release();
		}

		pBuffer->UnlockBits();
	}

	return true;
}

}	// Media
}
