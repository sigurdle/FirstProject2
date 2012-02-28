#include "stdafx.h"
#include "LFC.h"
#include "ASN.h"
#include "Certificate.h"

namespace System
{
namespace Security
{

/*
std::string GetString(ISequentialByteStream* stream)
{
}
*/

	void ReadAlgorithmIdentifier(IO::Stream& stream)
{
	ASN::Tag tag;
	ASN::ReadTag(stream, &tag);
	if (tag.Kind != 16) throw -1;	// SEQUENCE
	{
		vector<ULONG> algoritm = ASN::ReadObjectIdentifier(stream);
	}
	ASN::AscendTag(&tag, stream);

//	ASN::ReadObjectIdentifier(stream);	// ??
}

void ReadSubjectPublicKeyInfo(IO::Stream& stream)
{
	ASN::Tag tag;
	ASN::ReadTag(stream, &tag);
	ASSERT(tag.Kind == 16);
	{
		ReadAlgorithmIdentifier(stream);

		ASN::Tag tag;
		ASN::ReadTag(stream, &tag);
		ASSERT(tag.Kind == 3);
	}
}

void ReadName(IO::Stream& stream)
{
	ASN::Tag tag;
	ASN::ReadTag(stream, &tag);
	ASSERT(tag.Kind == 16);
	{
		ASN::ReadTag(stream, &tag);
		ASSERT(tag.Kind == 17);

		ASN::ReadTag(stream, &tag);
		ASSERT(tag.Kind == 16);

		vector<ULONG> attributeType = ASN::ReadObjectIdentifier(stream);

		ASN::ReadTag(stream, &tag);
		if (tag.Kind == 19)
		{
			char* buf = new char[tag.Length+1];
			stream.Read(buf, tag.Length);
			buf[tag.Length] = 0;
		//	TRACE(" = %s", buf);
			delete buf;
		}
		else
			ASSERT(0);
	}
	ASN::AscendTag(&tag, stream);
}

void ReadUTCTime(ASN::Tag* tag, IO::Stream& stream)
{
	if (tag->Constructed)
	{
		ASSERT(0);
	}
	else
	{
		char* str = new char[tag->Length+1];
		stream.Read(str, tag->Length);
		str[tag->Length] = 0;

	//	TRACE("%s\n", str);

		delete str;
	}
}

void ReadValidity(IO::Stream& stream)
{
	ASN::Tag tag;
	ASN::ReadTag(stream, &tag);
	ASSERT(tag.Kind == 16);
	{
		ASN::ReadTag(stream, &tag);
		if (tag.Kind == 23)
			ReadUTCTime(&tag, stream);
		else
			ASSERT(0);

		ASN::ReadTag(stream, &tag);
		if (tag.Kind == 23)
			ReadUTCTime(&tag, stream);
		else
			ASSERT(0);
	}
}

void ReadTBSCertificate(IO::Stream& stream)
{
	ASN::Tag tag;
	ASN::ReadTag(stream, &tag);
	if (tag.Kind != 16) throw -1;	// SEQUENCE

	ASN::ReadExplicitTag(stream, 0);
	LONG Version = ASN::ReadInteger(stream);

	LONGLONG SerialNumber = ASN::ReadInteger(stream);
	ReadAlgorithmIdentifier(stream);
	ReadName(stream);	// issuer
	ReadValidity(stream);
	ReadName(stream);	// subject
	ReadSubjectPublicKeyInfo(stream);

	ASN::AscendTag(&tag, stream);
}

void ReadCertificate(IO::Stream& stream)
{
	ASN::Tag tag;
	ASN::ReadTag(stream, &tag);
	if (tag.Kind != 16) throw -1;	// SEQUENCE

	ReadTBSCertificate(stream);

	ASN::AscendTag(&tag, stream);
}

}	// Security
}
