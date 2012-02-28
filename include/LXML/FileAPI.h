namespace Web
{

class Blob
{
public:

	unsigned long long get_size();
	String get_type();

	Blob* slice(long long start, long long end, String contentType);
};

class File : public Blob
{
};

class FileReader : public EventTarget
{
public:

// async read methods
	void readAsArrayBuffer(Blob blob);
	void readAsBinaryString(Blob blob);
	void readAsText(Blob blob, optional String encoding);
	void readAsDataURL(Blob blob);

	void abort();

// states
	enum ReadyState
	{
		EMPTY = 0,
		LOADING = 1,
		DONE = 2,
	};

	ReadyState get_readyState();

	// File or Blob data
	Variant get_result();

	DOMError get_error();

	// event handler attributes
	attribute [TreatNonCallableAsNull] Function? onloadstart;
	attribute [TreatNonCallableAsNull] Function? onprogress;
	attribute [TreatNonCallableAsNull] Function? onload;
	attribute [TreatNonCallableAsNull] Function? onabort;
	attribute [TreatNonCallableAsNull] Function? onerror;
	attribute [TreatNonCallableAsNull] Function? onloadend;
};

}
