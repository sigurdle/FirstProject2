#include "stdafx.h"
#include "LFC.h"
#include "asn.h"

namespace System
{
namespace ASN
{

void AscendTag(Tag* tag, IO::Stream& stream)
{
	stream.Seek(tag->start + tag->Length, IO::STREAM_SEEK_SET);
}

ULONG ReadTag(IO::Stream& stream, Tag* tag)
{

	uint8 ClassAndTag;
	if (stream.Read(&ClassAndTag, 1) != 1)
		THROW(-1);

	uint8 Class = ClassAndTag>>6;
	ULONG Tag = ClassAndTag & 31;

	if (Tag == 31)
	{
		uint8 byte;
		Tag = 0;
		do
		{
			stream.Read(&byte, 1);

			Tag <<= 7;
			Tag |= (byte & ~128);
		}
		while (byte & 128);
	}

	uint8 byte;
	stream.Read(&byte, 1);
	ULONG Length;
	if (byte & 128)
	{
		Length = 0;

		uint8 n = byte & ~128;
		while (n--)
		{
			stream.Read(&byte, 1);

			Length <<= 8;
			Length |= byte;
		}
	}
	else
	{
		Length = byte;
	}

	tag->Kind = Tag;
	tag->Length = Length;
	tag->Class = Class;
	tag->Constructed = (ClassAndTag>>5)&1;
	tag->start = stream.Seek(0, IO::STREAM_SEEK_CUR);

#if 0
	TRACE("Tag:%d, Length: %d ", Tag, Length);

	const char* str = NULL;

	switch (Tag)
	{
	case 0:	str = "end"; break;
	case 2:	str = "INTEGER"; break;
	case 3:	str = "BIT STRING"; break;
	case 4:	str = "OCTET STRING"; break;
	case 5:	str = "NULL"; break;
	case 6:	str = "OBJECT IDENTIFIER"; break;
	case 16:	str = "SEQUENCE and SEQUENCE OF"; break;
	case 17:	str = "SET and SET OF"; break;
	case 19:	str = "PrintableString"; break;
	case 20:	str = "T61String"; break;
	case 22:	str = "IA5String"; break;
	case 23:	str = "UTCTime"; break;
	}

	TRACE("%s", str);

	if ((ClassAndTag>>5)&1)	// Constructed
	{
		TRACE("\n");

		LONGLONG start = stream->Seek(0, STREAM_SEEK_CUR);
		ULONG Tag;
		while (1)
		{
			LONGLONG cur = stream->Seek(0, STREAM_SEEK_CUR);
			if (cur-start >= Length)
			{
				ASSERT(cur-start == Length);
				break;
			}

			Tag = ASNTag(stream);
		}
	}
	else
	{
		if (Tag == 2)
		{
			LONGLONG integer = 0;
			while (Length--)
			{
				integer <<= 8;

				uint8 byte;
				stream->Read(&byte, 1);
				integer |= byte;
			}

			ATLTRACE(" = %ld", (LONG)integer);
		}
		else if (Tag == 19)
		{
			char* buf = new char[Length+1];
			stream->Read(buf, Length);
			buf[Length] = 0;
			ATLTRACE(" = %s", buf);
			delete buf;
		}
		else
		{
			stream->Seek(Length, STREAM_SEEK_CUR);
		}

		ATLTRACE("\n");
	}
#endif

	return Tag;
}

void ReadExplicitTag(IO::Stream& stream, ULONG TagKind)
{
	Tag tag;
	ReadTag(stream, &tag);
	if (tag.Kind != TagKind) THROW(-1);
}

/*
ULONG ReadTag(ISequentialByteStream* stream, Tag* tag)
{
	while (ReadTag2(stream, tag) == 0)
	{
		AscendTag(tag, stream);
	}
	return tag->Kind;
}
*/

LONGLONG ReadInteger(IO::Stream& stream)
{
	Tag tag;
	ReadTag(stream, &tag);

	if (tag.Kind != 2) THROW(-1);

	LONGLONG integer = 0;
	LONGLONG Length = tag.Length;

	while (Length--)
	{
		integer <<= 8;

		uint8 byte;
		stream.Read(&byte, 1);
		integer |= byte;
	}

	return integer;
}

vector<ULONG> ReadObjectIdentifier(IO::Stream& stream)
{
	vector<ULONG> result;

	Tag tag;
	ReadTag(stream, &tag);
	if (tag.Kind == 5)	// NULL
	{
	}
	else
	{
		if (tag.Kind != 6)
			raise(Exception("tag.Kind != 6"));

		ULONG len = tag.Length;

		uint8 byte;
		stream.Read(&byte, 1);
		len--;

		long value1 = byte / 40;
		long value2 = byte % 40;

		result.Add(value1);
		result.Add(value2);

		while (len > 0)
		{
			LONGLONG value = 0;
			do
			{
				stream.Read(&byte, 1);
				value <<= 7;
				value |= (byte & ~128);
				len--;
			}
			while (byte & 128);

			result.Add(value);
		}
		ASSERT(len == 0);

//		AscendTag(&tag, stream);
	}

	return result;
}

}	// ASN
}
