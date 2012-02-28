#include "stdafx.h"
#include "LFC.h"
#include "TypeArchive.h"
//#include "Type.h"

namespace std
{
#include <stdlib.h>
#include <time.h>
}

namespace System
{
using namespace std;
using namespace IO;

const uint32 SIGNATURE = 0;

extern uint32 crc_table[256];
extern bool crc_table_computed;
void make_crc_table();

TypeArchive::TypeArchive(Mode mode, StringIn pathname)
{
	if (!crc_table_computed)
		make_crc_table();

	m_crc = 0;

	VERIFY(/*mode == Mode_Store ||*/ mode == Mode_Load);

	m_bIsStoring = (mode == Mode_Store);

	m_pathname = pathname;

	m_pGlobalNamespace = NULL;
	m_bSortedDecls = false;
	if (mode == Mode_Load)
		m_p2 = new IO::BinaryReader(new IO::FileStream(pathname, IO::FileMode_Open, IO::FileAccess_Read));
	else
		m_p = new IO::BinaryWriter(new IO::FileStream(pathname, IO::FileMode_Create, IO::FileAccess_Write));
}

TypeArchive::TypeArchive(Mode mode, Stream* p, StringIn pathname)
{
	if (!crc_table_computed)
		make_crc_table();

	m_crc = 0;

	VERIFY(mode == Mode_Store || mode == Mode_Load);

	m_bIsStoring = (mode == Mode_Store);

	m_pathname = pathname;

	m_pGlobalNamespace = NULL;
	m_bSortedDecls = false;

	if (mode == Mode_Load)
		m_p2 = new IO::BinaryReader(p);
	else
		m_p = new IO::BinaryWriter(p);
}

TypeArchive::~TypeArchive()
{
}

/*
void TypeArchive::Read(void* data, size_t count)
{
	UpdateCRC(data, count);
	m_p2.Read(data, count);
}

void TypeArchive::Write(const void* data, size_t count)
{
	UpdateCRC(data, count);
	m_p.Write(data, count);
}
*/

void TypeArchive::UpdateCRC(const void* buf, size_t length)
{
	for (size_t i = 0; i < length; i++)
	{
		m_crc = crc_table[(m_crc ^ ((uint8*)buf)[i]) & 0xff] ^ (m_crc >> 8);
	}
}

void TypeArchive::Init()
{
	MapObject(Types::get_nullType());
	MapObject(Types::get_void());
	MapObject(Types::get_bool());
	MapObject(Types::get_char());
	MapObject(Types::get_signed_char());
	MapObject(Types::get_unsigned_char());
	MapObject(Types::get_wchar());
	MapObject(&Types::type_short);
	MapObject(&Types::type_unsigned_short);
	MapObject(&Types::type_int);
	MapObject(&Types::type_unsigned_int);
	MapObject(&Types::type_long);
	MapObject(&Types::type_unsigned_long);
	MapObject(&Types::type_long_long);
	MapObject(&Types::type_unsigned_long_long);
	MapObject(&Types::type_float);
	MapObject(&Types::type_double);
	MapObject(&Types::type_long_double);
	MapObject(&Types::type_float128);
}

void TypeArchive::ReadHeader()
{
	ASSERT(!m_bIsStoring);

	uint32 sig;
	uint32 ntypes;
	uint32 nstrings;
	uint32 ndecls;

	*this >> sig;
	if (sig != SIGNATURE)
	{
		raise(Exception("error"));
	}

	*this >> m_typelib->m_id;

	*this >> ntypes;
	*this >> nstrings;
	*this >> ndecls;

	m_typeLoad.reserve(ntypes);
	m_stringLoad.reserve(nstrings);
	m_declLoad.reserve(ndecls);

	Init();
}

void TypeArchive::WriteHeader()
{
	ASSERT(m_bIsStoring);

	uint32 sig = SIGNATURE;

	srand( (unsigned)time( NULL ) );
	m_typelib->m_id = rand();

	uint32 ntypes = 0;
	uint32 nstrings = 0;
	uint32 ndecls = 0;

	*this << sig;
	*this << m_typelib->m_id;
	*this << ntypes;
	*this << nstrings;
	*this << ndecls;

	Init();
}

#if 0
TypeArchive& TypeArchive::operator >> (StringA & value)
{
	ULONG len = 0;
	do
	{
		uint8 byteval;
		*this >> byteval;
		len |= byteval & 0x7f;
		if	(!(byteval & 0x80)) break;
		len <<= 7;
	}
	while (1);

	value = StringA(NULL, len);
	Read(value.begin(), len);
	return *this;
}

TypeArchive& TypeArchive::operator << (const StringA & value)
{
	ULONG len = value.Length();
	ASSERT(len < 128);

	uint8 byteval = len;
	*this << byteval;

	Write(value.c_str(), value.Length());
	return *this;
}

TypeArchive& TypeArchive::operator << (StringW value)
{
	*this << value.Length();
	Write(value.c_str(), value.Length()*2);
	return *this;
}
#endif

TypeSerializable* TypeArchive::CreateType(uint8 classtype, TypeLib* typelib, StringIn qname, uint32 id)
{
	switch (classtype)
	{
	case TypeSerializable::Class_Namespace:
		{
			Namespace* p = Namespace::CreateFromArchive(*this, typelib, qname, id);
			p->m_typelib = typelib;
			return p;
		}
		break;

	case TypeSerializable::Class_EnumType:
		{
			EnumType* p = new EnumType;
			p->m_qname = qname;
			m_typeLoad[id-1] = p;
			p->m_typelib = typelib;
			p->Load(*this);
			return p;
		}
		break;

	case TypeSerializable::Class_Class:
		{
			ClassType* p = new ClassType;
			p->m_qname = qname;
			m_typeLoad[id-1] = p;
			p->m_typelib = typelib;
			p->Load(*this);
			return p;
		}
		break;

	case TypeSerializable::Class_Typedef:
		{
			Typedef* p = new Typedef;
			m_typeLoad[id-1] = p;
			p->m_qname = qname;
			p->m_typelib = typelib;
			p->Load(*this);
			return p;
		}
		break;

	case TypeSerializable::Class_PrimitiveType:
		{
			// Shouldn't happen
			ASSERT(0);
			THROW(-1);
			//pobj = new _PrimitiveType;
		}
		break;

	case TypeSerializable::Class_PointerType:
		{
			PointerType* p = new PointerType;
			m_typeLoad[id-1] = p;
			p->Load(*this);
			return p;
		}
		break;

	case TypeSerializable::Class_ReferenceType:
		{
			ReferenceType* p = new ReferenceType;
			m_typeLoad[id-1] = p;
			p->Load(*this);
			return p;
		}
		break;

	case TypeSerializable::Class_RValueReferenceType:
		{
			RValueReferenceType* p = new RValueReferenceType;
			m_typeLoad[id-1] = p;
			p->Load(*this);
			return p;
		}
		break;

	case TypeSerializable::Class_PointerMemberType:
		{
			PointerMemberType* p = new PointerMemberType;
			m_typeLoad[id-1] = p;
			p->Load(*this);
			return p;
		}
		break;

	case TypeSerializable::Class_ModifierType:
		{
			ModifierType* p = new ModifierType;
			m_typeLoad[id-1] = p;
			p->Load(*this);
			return p;
		}
		break;

	case TypeSerializable::Class_ArrayType:
		{
			ArrayType* p = new ArrayType;
			m_typeLoad[id-1] = p;
			p->Load(*this);
			return p;
		}
		break;
		
	case TypeSerializable::Class_Function:
		{
			FunctionType* p = new FunctionType;
			m_typeLoad[id-1] = p;
			p->Load(*this);
			return p;
		}
		break;

	case TypeSerializable::Class_TemplateArgType:
		{
			_TemplateArgType* p = new _TemplateArgType;
			m_typeLoad[id-1] = p;
			p->Load(*this);
			return p;
		}
		break;

		/*
	case Class_TemplatedClassType:
		{
			pobj = new TemplatedClassType;
		}
		break;
		*/

	case TypeSerializable::Class_TemplatedClassArg:
		{
			TemplatedClassArg* p = new TemplatedClassArg;
			m_typeLoad[id-1] = p;
			p->Load(*this);
			return p;
		}
		break;

	case TypeSerializable::Class_Define:
		{
			CDefine* p = new CDefine;
			m_typeLoad[id-1] = p;
			p->Load(*this);
			return p;
		}
		break;

	case TypeSerializable::Class_TypeLib:
		{
			VERIFY(0);
		//	object = TypeLib::CreateFromArchive(*this, id);
		//	return *this;
		}
		break;

		/*
	case TypeSerializable::Class_TypeLibImport:
		{
			pobj = new TypeLibImport;
		//	object = TypeLib::CreateFromArchive(*this, id);
		//	return *this;
		}
		break;
		*/

	default:
		{
#if 0
			pobj = NULL;
			DebugTrace("Unknown Class " <<  classtype << "\n");
			ASSERT(0);
			THROW(-1);
#endif
		}
	}

	return NULL;
}

TypeArchive& TypeArchive::operator >> (TypeSerializable* & object)
{
	uint32 id;
	*this >> id;

	if (id == 0)
	{
		object = NULL;
		return *this;
	}

	if (m_typeLoad.size() >= id)
	{
		object = m_typeLoad[id-1];
	}
//	map<uint32,TypeSerializable*, less<uint32>, __gc_allocator>::iterator it = m_objectmapLoad.find(id);
//	if (it != m_objectmapLoad.end())
//	{
//		object = (*it).second;
//	}
	else
	{
		uint8 classtype;
		*this >> classtype;

		if (m_typeLoad.size() < id) m_typeLoad.resize(id);

		if (classtype & (1<<7))	// import
		{
			classtype &= ~((1<<6)|(1<<7));

			String qname;
			TypeLib* typelib;

			*this >> qname;
			*this >> typelib;

			NamedType* pType = typelib->FindNamedType(qname);
			m_typeLoad[id-1] = pType;
			if (pType == NULL)
			{
				DebugTrace(m_typelib->m_typeinfo_filename << ": " << qname << " : not found in " << typelib->m_typeinfo_filename << "\n");
			}
			object = pType;
		}
		else if (classtype & (1<<6))	// defined with name
		{
			classtype &= ~((1<<6)|(1<<7));

			String qname;
			*this >> qname;

			TypeSerializable* pType = CreateType(classtype, m_typelib, qname, id);
			ASSERT(pType);
			object = pType;
		}
		else
		{
			TypeSerializable* pType = CreateType(classtype, m_typelib, nullptr, id);
			ASSERT(pType);
			object = pType;
		}

	//	m_objectmapLoad.insert(map<uint32, TypeSerializable*>::value_type(id, pobj));
	//	ASSERT(m_typeLoad.size() == id);

	//	pobj->Load(*this);

	//	object = pobj;
	}

	return *this;
}

class Tables
{
public:
	class TypeTable
	{
	public:
		size_t m_number;
		_Ptr<Stream> m_stream;
	};

	map<Type*, TypeTable*> m_type_tables;
};

Tables* m_tables;

unsigned int needbits(size_t range)
{
	unsigned int nbits = 0;
	while ((1ull<<nbits) < range)
	{
		++nbits;
	}

	return nbits;
}

template<class TYPE, class A> Stream& write(Stream& stream, vector<TYPE, A>& item)
{
	stream << item.size();
	vector<TYPE, A>::const_iterator it = item.begin();
	while (it != item.end())
	{
		stream << it;
		++it;
	}

	return stream;
}

template<class TYPE>
class Nth
{
public:

	CTOR Nth(size_t n, TYPE& v) : m_n(n), m_v(v)
	{
	}

	size_t m_n;
	TYPE& m_v;
};

template<class T> Nth<T> nth(size_t n, T& v)
{
	return Nth<T>(n, v);
}

template<class TYPE>
class LengthOf
{
public:

	CTOR LengthOf(size_t n) : m_n(n)
	{
	}

	size_t m_n;
};

/*
template<class T> lengthof<T> nth(size_t n)
{
	return LengthOf<T>(n);
}
*/

template<class TYPE, class A> Stream& read(Stream& stream, vector<TYPE, A>& item)
{
	size_t size;
	stream >> LengthOf<vector<TYPE, A>(size);

	item.reserve(size);

	while (size--)
	{
		item.push_back(TYPE());
		stream >> nth(i, item.back());
	}

	return stream;
}

template<class TYPE, class A> Stream& write(Stream& stream, list<TYPE, A>& item)
{
	stream << item.size();

	vector<TYPE, A>::const_iterator it = item.begin();
	size_t i = 0;

	while (it != item.end())
	{
		stream << nth(i, *it);
		++it;
		++i;
	}

	return stream;
}

template<class TYPE, class A> Stream& read(Stream& stream, list<TYPE, A>& item)
{
	size_t size;
	stream >> size;

	item.reserve(size);

	for (size_t i = 0; i < size; ++i)
	{
		item.push_back(TYPE());
		stream.ReadNth(i, item.back());
	}

	return stream;
}

template<class TYPE> Stream& write(Stream& stream, Nth<TYPE>& item)
{
	if (item.m_n > 0) stream << ", ";
	stream << item.m_v;
	return *this;
}

#if 0
TypeArchive& TypeArchive::operator << (const Object* object)
{
	if (object == NULL)
	{
		uint32 id = 0;
		*this << id;
		return *this;
	}

	map<const Object*, uint32>::iterator it = m_objectmapSave.find(object);
	if (it != m_objectmapSave.end())
	{
		uint32 id = (*it).second;
		*this << (uint32)id;
	}
	else
	{
		// The number of different classes of objects that this might point to

		// TODO, can also recursively count the different classes that are possible to reach starting from a type
		// (something else than Object, e.g TypeSerializable)

		size_t nderived = 1+object->GetType()->get_DerivedClasses()->GetCount();
		size_t nbits = needbits(nderived);	// Number of bits needed to store

		size_t table_num = GetTableNumber(object->GetType());

		*this << table_num;

		uint32 id = m_objectmapSave.size()+1;

		m_tables.m_type_tables[object->GetType()];

		m_objectmapSave.insert(map<const TypeSerializable*,uint32>::value_type(object, id));

		*this << (uint32)id;

		uint8 classtype = object->GetSerializableType();
		*this << classtype;
		VERIFY(classtype != TypeSerializable::Class_PrimitiveType);	// Shouldn't happen
}
#endif

TypeArchive& TypeArchive::operator << (const TypeSerializable* object)
{
	if (object == NULL)
	{
		uint32 id = 0;
		*this << id;
		return *this;
	}

	map<const TypeSerializable*, uint32>::iterator it = m_typeSave.find(object);
	if (it != m_typeSave.end())
	{
		uint32 id = (*it).second;
		*this << (uint32)id;
	}
	else
	{
		uint32 id = m_typeSave.size()+1;

		m_typeSave.insert(map<const TypeSerializable*,uint32>::value_type(object, id));

		*this << (uint32)id;

		uint8 classtype = object->GetSerializableType();
		VERIFY(classtype != TypeSerializable::Class_PrimitiveType);	// Shouldn't happen

		if (classtype == TypeSerializable::Class_Class ||
			classtype == TypeSerializable::Class_Typedef ||
			classtype == TypeSerializable::Class_EnumType)
		{
			const NamedType* pNamedType = dynamic_cast<const NamedType*>(object);

			if (pNamedType->m_qname)
			{
				if (pNamedType->m_typelib != m_typelib)	// write reference to import file
				{
					classtype |= (1<<7);	// Set import bit

					*this << classtype;
					*this << pNamedType->m_qname;
					*this << pNamedType->m_typelib;

					return *this;
				}
				else
				{
					classtype |= (1<<6);	// Set def bit

					*this << classtype;
					*this << pNamedType->m_qname;
					object->Store(*this);

					return *this;
				}
			}
		}

		*this << classtype;
		object->Store(*this);
	}

	return *this;
}

void TypeArchive::MapObject(const TypeSerializable* object)
{
	if (m_bIsStoring)
	{
		ASSERT(m_typeSave.find(object) == m_typeSave.end());

		m_typeSave.insert(map<const TypeSerializable*, uint32>::value_type(object, m_typeSave.size()+1));
	}
	else
	{
		ASSERT(0);
		THROW(-1);
	}
}

void TypeArchive::MapObject(TypeSerializable* object)
{
	if (m_bIsStoring)
	{
		ASSERT(m_typeSave.find(object) == m_typeSave.end());

		m_typeSave.insert(map<const TypeSerializable*, uint32>::value_type(object, m_typeSave.size()+1));
	}
	else
	{
//		m_objectmapLoad.insert(map<uint32, TypeSerializable*>::value_type(m_objectmapLoad.size()+1, object));
	//	ASSERT(m_objectLoad.size() == id);
		m_typeLoad.push_back(object);
	}
}

void TypeArchive::MapObject(Declarator* object)
{
	if (m_bIsStoring)
	{
		ASSERT(m_declSave.find(object) == m_declSave.end());

		m_declSave.insert(map<const Declarator*, uint32>::value_type(object, m_declSave.size()+1));
	}
	else
	{
		m_declLoad.push_back(object);
	}
}

void TypeArchive::MapObject(const Declarator* object)
{
	if (m_bIsStoring)
	{
		ASSERT(m_declSave.find(object) == m_declSave.end());

		m_declSave.insert(map<const Declarator*, uint32>::value_type(object, m_declSave.size()+1));
	}
	else
	{
		ASSERT(0);
	}
}

void TypeArchive::MapObject(CppSourceFile* object)
{
	if (m_bIsStoring)
	{
		ASSERT(m_objectSave.find(object) == m_objectSave.end());

		m_objectSave.insert(map<CppSourceFile*, uint32>::value_type(object, m_objectSave.size()+1));
	}
	else
	{
		m_objectLoad.push_back(object);
	}
}

/*
void TypeArchive::MapObject(CppSourceFile* object)
{
	if (m_bIsStoring)
	{
		ASSERT(m_objectSave.find(object) == m_objectSave.end());

		m_objectSave.insert(map<CppSourceFile*, uint32>::value_type(object, m_objectSave.size()+1));
	}
	else
	{
		ASSERT(0);
	}
}
*/

void TypeArchive::MapObject(FilePart* object)
{
	if (m_bIsStoring)
	{
		ASSERT(m_filepartSave.find(object) == m_filepartSave.end());

		m_filepartSave.insert(map<const FilePart*, uint32>::value_type(object, m_filepartSave.size()+1));
	}
	else
	{
		m_filepartLoad.push_back(object);
	}
}

void TypeArchive::MapObject(const FilePart* object)
{
	if (m_bIsStoring)
	{
		ASSERT(m_filepartSave.find(object) == m_filepartSave.end());

		m_filepartSave.insert(map<const FilePart*, uint32>::value_type(object, m_filepartSave.size()+1));
	}
	else
	{
		ASSERT(0);
	}
}

TypeArchive& TypeArchive::operator >> (Declarator* & object)
{
	uint32 id;
	*this >> id;

	if (id == 0)
	{
		object = NULL;
		return *this;
	}

	if (m_declLoad.size() >= id)
	{
		object = m_declLoad[id-1];
	}
//	map<uint32,TypeSerializable*, less<uint32>, __gc_allocator>::iterator it = m_objectmapLoad.find(id);
//	if (it != m_objectmapLoad.end())
//	{
//		object = (*it).second;
//	}
	else
	{
		ASSERT(0);
#if 0
		CDeclarator* pobj = new CDeclarator;

		pobj->Load(

	//	m_objectmapLoad.insert(map<uint32, TypeSerializable*>::value_type(id, pobj));
		m_declload.push_back(pobj);
		ASSERT(m_declLoad.size() == id);

		pobj->Load(*this);

		object = pobj;
#endif
	}

	return *this;
}

TypeArchive& TypeArchive::operator << (const Declarator* object)
{
	if (object == NULL)
	{
		uint32 id = 0;
		*this << id;
		return *this;
	}

	auto it = m_declSave.find(object);
	if (it != m_declSave.end())
	{
		uint32 id = it->second;
		*this << (uint32)id;
	}
	else
	{
		//uint32 id = m_objectmapSave.size()+1;
		ASSERT(0);
	}

	return *this;
}

TypeArchive& TypeArchive::operator >> (CppSourceFile* & object)
{
	uint32 id;
	*this >> id;

	if (id == 0)
	{
		object = NULL;
		return *this;
	}

	if (m_objectLoad.size() >= id)
	{
		object = m_objectLoad[id-1];
	}
//	map<uint32,TypeSerializable*, less<uint32>, __gc_allocator>::iterator it = m_objectmapLoad.find(id);
//	if (it != m_objectmapLoad.end())
//	{
//		object = (*it).second;
//	}
	else
	{
		raise(SystemException("TypeArchive " + m_typelib->m_typeinfo_filename));

#if 0
		CDeclarator* pobj = new CDeclarator;

		pobj->Load(

	//	m_objectmapLoad.insert(map<uint32, TypeSerializable*>::value_type(id, pobj));
		m_declload.push_back(pobj);
		ASSERT(m_declLoad.size() == id);

		pobj->Load(*this);

		object = pobj;
#endif
	}

	return *this;
}

TypeArchive& TypeArchive::operator << (CppSourceFile* object)
{
	if (object == NULL)
	{
		uint32 id = 0;
		*this << id;
		return *this;
	}

	auto it = m_objectSave.find(object);
	if (it != m_objectSave.end())
	{
		uint32 id = it->second;
		*this << (uint32)id;
	}
	else
	{
		uint32 id = 0;
		*this << id;
		Std::get_Out() << __FILE__ << "(" << __LINE__ << ")" << " : warning : source file not stored" << endl;
#if 0

		raise(Exception(object->ToString() + " already in archive"));
		//uint32 id = m_objectmapSave.size()+1;
		ASSERT(0);
#endif
	}

	return *this;
}

TypeArchive& TypeArchive::operator >> (FilePart* & object)
{
	uint32 id;
	*this >> id;

	if (id == 0)
	{
		object = NULL;
		return *this;
	}

	if (m_filepartLoad.size() >= id)
	{
		object = m_filepartLoad[id-1];
	}
	else
	{
		ASSERT(0);
	}

	return *this;
}

TypeArchive& TypeArchive::operator << (const FilePart* object)
{
	if (object == NULL)
	{
		uint32 id = 0;
		*this << id;
		return *this;
	}

	map<const FilePart*, uint32>::iterator it = m_filepartSave.find(object);
	if (it != m_filepartSave.end())
	{
		uint32 id = (*it).second;
		*this << (uint32)id;
	}
	else
	{
		//uint32 id = m_objectmapSave.size()+1;
		ASSERT(0);
	}

	return *this;
}

TypeArchive& TypeArchive::operator >> (String& value)
{
	uint16 len;
	*this >> len;
	value = String(string_alloc<char>(len));
	m_p2->Read(value.GetData8(), value.GetByteCount());

	return *this;
}

TypeArchive& TypeArchive::operator << (const String& name)
{
	size_t len = name.GetLength();
	ASSERT(len < 65536);
	*this << (uint16)len;
	if (len > 0)
	{
		m_p->Write(name.GetData8(), name.GetByteCount());
	}

	return *this;
}

/*
TypeArchive& TypeArchive::operator >> (String& value)
{
	uint16 len;
	*this >> len;
	value = StringW(string_alloc<WCHAR>(len));
	Read(value.begin(), value.ByteCount());

	return *this;
}

TypeArchive& TypeArchive::operator << (const StringW& name)
{
	unsigned int len = name.Length();
	ASSERT(len < 65536);
	*this << (uint16)len;
	Write(name.GetData(), name.ByteCount());

	return *this;
}
*/

void TypeArchive::StoreIdentifier(StringIn name)
{
	if (name.IsEmpty())
	{
		uint16 id = 0;
		*this << id;
		return;
	}

	map<String, uint32>::iterator it = m_stringSave.find(name);
	if (it != m_stringSave.end())
	{
		uint16 id = (*it).second;
		*this << id;
	}
	else
	{
		uint32 id = m_stringSave.size()+1;

		VERIFY(id < 32768);

		m_stringSave.insert(map<String,uint32>::value_type(name, id));

		*this << (uint16)id;

		size_t len = name.GetLength();

		VERIFY(len < 256);

		*this << (uint8)len;

		if (len > 0)
		{
			const char* p = name.GetData8();

#if 1
			m_p->Write(p, len);
#else
			BitStreamO bitstream(m_p->m_baseStream);

			int code = (uint8)p[0] - 64;
			ASSERT(code >= 0 && code < 64);

			bitstream.putnbits(6, code);

			for (size_t i = 1; i < len; ++i)
			{
				int code = (uint8)p[i];
				ASSERT(code < 128);
				bitstream.putnbits(7, code);
			}

			bitstream.byte_align();
#endif
		}
	}
}

String TypeArchive::LoadIdentifier()
{
	uint16 id;
	*this >> id;

	if (id == 0)
	{
		return nullptr;
	}

	/*
	map<uint32, System::StringA*>::iterator it = m_stringLoad.find(id);
	if (it != m_stringLoad.end())
	{
		return (*it).second;
	}
	else
	*/
	if (m_stringLoad.size() >= id)
	{
		return m_stringLoad[id-1];
	}
	else
	{
		uint8 len;
		*this >> len;

		char name[256];

		if (len > 0)
		{
#if 1
			m_p2->Read(name, len);
#else
			BitStream bitstream(m_p2->m_baseStream);
		//	bitstream.m_getbyte = BitStream(GetStream());
			name[0] = (uint8)bitstream.getnbits(6) + 64;

			for (int i = 1; i < len; i++)
			{
				name[i] = (uint8)bitstream.getnbits(7);
			}
			bitstream.byte_align();
#endif
		}
		//name[len] = 0;
	//	printf("%s\n", name);

		String nameobj(string_copy(name, len));

	//	m_stringLoad.insert(map<uint32, StringA*>::value_type(id, nameobj));
		m_stringLoad.push_back(nameobj);

		return nameobj;
	}
}

}	// System
