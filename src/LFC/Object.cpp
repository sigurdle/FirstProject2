#include "stdafx.h"
#include "LFC.h"

namespace System
{

extern Module _Module;

#if AMIGA

long InterlockedIncrement(long* plong)
{
	Forbid();
	(*plong)++;
	long value = *plong;
	Permit();
	return value;
}

long InterlockedDecrement(long* plong)
{
	Forbid();
	(*plong)--;
	long value = *plong;
	Permit();
	return value;
}

#endif

Object::Object()
{
}

Object::~Object()
{
}

ClassType* Object::GetType() const
{
	return System::GetType(this);
}

Type* Object::GetPrimitiveType() const
{
	return GetType();
}

// returns true only if they're bit-by bit equal (override, if this isn't what you want)
bool Object::Equals(const Object* other) const
{
	if (this == other) return true;

	ClassType* pType = GetType();

	if (pType != other->GetType())
		return false;

	return memcmp(this, other, pType->get_sizeof()) == 0;
}

String Object::ToString()
{
	return nullptr;
}

uint32 Object::GetHashCode()
{
	return (uint32)this;
}

#undef new
#undef delete

void* Object::operator new (size_t size)
{
	return allocate_object(size);
}

void* Object::operator new (size_t size, const char* filename, int line)
{
	return allocate_object(size, filename, line);
}

void Object::operator delete (void* pv)
{
	free_buffer(pv);
}

// __gc_alloc

void* __gc_alloc::operator new (size_t size)
{
	return allocate_object(size);
}

void* __gc_alloc::operator new (size_t size, const char* filename, int line)
{
	return allocate_object(size, filename, line);
}

void __gc_alloc::operator delete (void* pv)
{
	free_buffer(pv);
}

}	// System
