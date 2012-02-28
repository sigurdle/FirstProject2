#include "stdafx.h"
#include "LPDF.h"
#include "PDFCosName.h"

namespace System
{
namespace PDF
{

StringA* ReadNameFromStream(std::FILE* fp)
{
	BufferImp<char> buffer;
	StringBuilderA stream(&buffer);

	int c = std::fgetc(fp);

	ASSERT(c == '/');

	while (!feof(fp))
	{
		c = std::fgetc(fp);
		if (!std::isalnum(c) && c != '+' && c != ',')
		{
			std::ungetc(c, fp);
			break;
		}

		stream << (char)c;
	}

	StringA* name = buffer.DetachToString();

	return name;
}

//virtual
void CPDFCosName::WriteToStream(std::FILE* fp)
{
	std::fprintf(fp, "/%s", m_name->c_str());
}

void CPDFCosName::ReadFromStream(std::FILE* fp)
{
	m_name = ReadNameFromStream(fp);
}

}
}
