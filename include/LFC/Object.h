namespace System
{

class LFCEXT __gc_alloc
{
public:

#undef new
	void* operator new (size_t size);
	void* operator new (size_t size, const char* filename, int line);
#define new _new

	void operator delete (void* p);
};

/**
The Object class represents the root class for most classes, and provides some basic Type and
conversion services. This class has no datamembers and only adds one vtable entry as overhead.
This class is by default allocated in the garbage collected heap and do not need an explicit
delete. The current implementation however allows delete and frees the object. Using the object
after deleting results in undefined behavior.
*/
class LFCEXT Object
{
public:

	CTOR Object();	///< constructor
	virtual ~Object();	///< destructor

	/**
	Gets the Type of this Object. For objects that don't inherit from Object, but are
	polymorphic, that is, have virtual methods. You can use the global function
	::GetType(void* obj). This is not as safe, and will crash if you pass an object that is not
	polymorphic and have not associated c++ rtti (runtime type information) compiled. Notably, if you
	get a COM IUnknown* pointer from an outside dll
	@return The ClassType of this Object

	@code
	Object* p = new FooNS::Bar();
	ClassType* pType = p->GetType();
	pType->get_sizeof();	     // returns sizeof(FooNS::Bar)
	pType->get_Name();       // returns class name "Bar"
	pType->get_QName();      // returns qualified name "FooNS::Bar"
	...
	@endcode

	*/
	ClassType* GetType() const;

	virtual Type* GetPrimitiveType() const;

	/**
	@return A string representation of this object
	*/
	virtual String ToString();
	/**
	Computes a hashcode for this object. Hashcodes are commonly used in hashtables to quicly
	locate objects.
	@return 32-bit integer of computed hashcode. The default implementation returns the address of the object.
	In a 32-bit	application, this results in a unique hashcode for each object.
	*/
	virtual uint32 GetHashCode();

	/**
	@param other pointer to an object to check for equality with this object
	@return <code>true</code> if this object is bit-by bit equal with the other Object (override in a subclass if this isn't what you want)
	*/
	virtual bool Equals(const Object* other) const;

#undef new
	void* operator new (size_t size);
	void* operator new (size_t size, const char* filename, int line);
#define new _new

	void operator delete (void* p);
};

}	// System
