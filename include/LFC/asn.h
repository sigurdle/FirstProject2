namespace System
{
namespace ASN
{

enum asnclass
{
	class_universal =	0,
	class_application = 1,
	class_context_specific = 2,
	class_private = 3,
};

class LFCEXT Tag
{
public:
	LONGLONG Kind;
	LONGLONG Length;
	ubyte/*asnclass*/ Class;
	bool Constructed;

	LONGLONG start;
};

LFCEXT void ReadExplicitTag(IO::Stream& stream, ULONG TagKind);
LFCEXT ULONG ReadTag(IO::Stream& stream, Tag* tag);
LFCEXT LONGLONG ReadInteger(IO::Stream& stream);
LFCEXT vector<ULONG> ReadObjectIdentifier(IO::Stream& stream);
LFCEXT void AscendTag(Tag* tag, IO::Stream& stream);

}	// ASN
}
