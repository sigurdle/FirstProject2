#include "StdAfx.h"
#include "XPCOMTypeLib.h"

struct InterfaceDescriptor
{
    uint16                   parent_interface_index;
    uint16                   num_methods;
	 /*
    MethodDescriptor         method_descriptors[num_methods];
    uint16                   num_constants;
    ConstDescriptor          const_descriptors[num_constants];
    boolean                  is_scriptable;
    boolean                  is_function;
    uint6                    reserved;
*/
};

struct InterfaceDirectoryEntry
{
    GUID              m_iid;
    //Identifier*          m_name;
	 DWORD m_name;
    //Identifier*          m_namespace;
	 DWORD m_namespace;
    //InterfaceDescriptor* m_interface_descriptor;
	 DWORD						m_interface_descriptor;
};

struct XPCOMTypeLibHeader
{
	char                    magic[16];
	uint8                   major_version;
	uint8                   minor_version;
	uint16                  num_interfaces;

	uint32                  file_length;

	//    InterfaceDirectoryEntry* interface_directory;
	DWORD							interface_directory;

	//    uint8*                   data_pool;
	DWORD	data_pool;

   // Annotation               annotations[];
};

HRESULT ReadIdentifier(FILE* fp, __live_object_ptr<StringA> ident)
{
	while (!feof(fp))
	{
		int c = fget8(fp);

		ident += c;

		if (c == 0)
			break;
	}

	return S_OK;
}

HRESULT ReadIdentifierFromLocation(FILE* fp, DWORD pos, sysstring& ident)
{
	long oldpos = ftell(fp);

	fseek(fp, pos, SEEK_SET);
	ReadIdentifier(fp, ident);

	fseek(fp, oldpos, SEEK_SET);

	return S_OK;
}

uint8 ReadTypeDescriptor(FILE* fp)
{
	/*
	struct TypeDescriptorPrefix
	{
	BYTE	is_pointer : 1,
	is_unique_pointer : 1,
	is_reference : 1,
	tag : 5;
	};
	*/
	
	uint8 TypeDescriptorPrefix = fget8(fp);
	uint8 tag = TypeDescriptorPrefix & 0x1f;
	if (tag <= 17)
	{
	//	BYTE SimpleTypeDescriptor = fget8(fp);
	}
	else if (tag == 18)	// InterfaceTypeDescriptor
	{
		uint16  interface_index = fget16(fp);
	}
	else if (tag == 19)	// InterfaceIsTypeDescriptor
	{
		uint8    arg_num = fget8(fp);
	}
	else
	{
		throw -1;//exit(1);
	}

	return tag;
}

void ReadParamDescriptor(FILE* fp)
{
/*
ParamDescriptor {
boolean         in;
boolean         out;
boolean         retval;
boolean         shared;
boolean         dipper;
uint3           reserved;
TypeDescriptor  type;
}
	*/
	uint8 flags = fget8(fp);

	ReadTypeDescriptor(fp);
}

class CXPTypeLib;

class CXPIFaceInfo : public IXPIFaceInfo
{
public:
	CXPTypeLib* m_pTypeLib;

	int m_nFuncs;
	XPFUNCDESC* *m_funcs;

	InterfaceDirectoryEntry m_iface_entry;
	String m_name;
	String m_namespace;

public:
	String GetName() const;
	String GetNamespace() const;
	HRESULT GetIFaceAttr(XPIFACEATTR* *ppIFaceAttr);
	HRESULT ReleaseIFaceAttr(XPIFACEATTR* pIFaceAttr);
	HRESULT GetFuncDesc(unsigned long index, XPFUNCDESC* *ppIFaceAttr);
	HRESULT ReleaseFuncDesc(XPFUNCDESC* pIFaceAttr);
	HRESULT GetContainingTypeLib(IXPTypeLib* *ppTLib,  unsigned int *pIndex);
};

class CXPTypeLib : public IXPTypeLib
{
public:
	FILE* fp;
	XPCOMTypeLibHeader header;

	CXPIFaceInfo* * ifaces;

public:
	HRESULT GetIFace(long index, IXPIFaceInfo* *pVal)
	{
		*pVal = ifaces[index];
		return S_OK;
	}

	HRESULT GetIFaceCount()
	{
		return 43;//header.num_interfaces;
	}
};

HRESULT CXPIFaceInfo::GetContainingTypeLib(IXPTypeLib* *ppTLib,  unsigned int *pIndex)
{
	*ppTLib = m_pTypeLib;
	return S_OK;
}

StringA* CXPIFaceInfo::GetName() const
{
	return m_name;
}

StringA* CXPIFaceInfo::GetNamespace() const
{
	return m_namespace;
}

HRESULT CXPIFaceInfo::GetIFaceAttr(XPIFACEATTR* *ppIFaceAttr)
{
	XPIFACEATTR* p = new XPIFACEATTR;

	p->guid = m_iface_entry.m_iid;
	p->cFuncs = m_nFuncs;//m_iface_entry.m_interface_descriptor

	*ppIFaceAttr = p;
	return S_OK;
}

HRESULT CXPIFaceInfo::ReleaseIFaceAttr(XPIFACEATTR* pIFaceAttr)
{
	delete pIFaceAttr;
	return S_OK;
}

HRESULT CXPIFaceInfo::GetFuncDesc(unsigned long index, XPFUNCDESC* *ppFuncDesc)
{
	*ppFuncDesc = m_funcs[index];
	return S_OK;
}

HRESULT CXPIFaceInfo::ReleaseFuncDesc(XPFUNCDESC* pFuncDesc)
{
//	SysFreeString(pFuncDesc->name);
//	delete pFuncDesc;
	return S_OK;
}

HRESULT XPTypeLibParse(FILE* fp, IXPTypeLib** ppTypeLib)
{
	CXPTypeLib* pTypeLib = new CXPTypeLib;
	pTypeLib->fp = fp;

	int nread = fread(pTypeLib->header.magic, 1, 16, fp);
	if (nread >= 16 && memcmp(pTypeLib->header.magic, "XPCOM\nTypeLib\r\n\032", 16)==0)
	{
		pTypeLib->header.major_version = fget8(fp);
		pTypeLib->header.minor_version = fget8(fp);
		pTypeLib->header.num_interfaces = fget16(fp);
		pTypeLib->header.file_length = fget32(fp);
		pTypeLib->header.interface_directory = fget32(fp);
		pTypeLib->header.data_pool = fget32(fp);

		if (pTypeLib->header.major_version > 1)
		{
//			ATLTRACE("XPCOM TypeLib unsupported major version %d\n", pTypeLib->header.major_version);
			return E_FAIL;
		}

		pTypeLib->ifaces = new CXPIFaceInfo*[pTypeLib->header.num_interfaces];

		fseek(fp, -1 + pTypeLib->header.interface_directory/* + i*sizeof(InterfaceDirectoryEntry)*/, SEEK_SET);

		int i;

		// Read all these in one go
		for (i = 0; i < pTypeLib->header.num_interfaces; i++)
		{
			pTypeLib->ifaces[i] = new CXPIFaceInfo;

			fread(&pTypeLib->ifaces[i]->m_iface_entry.m_iid, 16, 1, fp);
			pTypeLib->ifaces[i]->m_iface_entry.m_name = fget32(fp);
			pTypeLib->ifaces[i]->m_iface_entry.m_namespace = fget32(fp);
			pTypeLib->ifaces[i]->m_iface_entry.m_interface_descriptor = fget32(fp);
		}

		// I currently also read the rest now, but later I may read it only when necessary
		for (i = 0; i < 44/*pTypeLib->header.num_interfaces*/; i++)
		{
			ReadIdentifierFromLocation(fp, -1 + pTypeLib->header.data_pool + pTypeLib->ifaces[i]->m_iface_entry.m_name, pTypeLib->ifaces[i]->m_name);

			if (pTypeLib->ifaces[i]->m_iface_entry.m_namespace)
			{
				ReadIdentifierFromLocation(fp, -1 + pTypeLib->header.data_pool + pTypeLib->ifaces[i]->m_iface_entry.m_namespace, pTypeLib->ifaces[i]->m_namespace);
			}

			pTypeLib->ifaces[i]->m_nFuncs = 0;
			if (pTypeLib->ifaces[i]->m_iface_entry.m_interface_descriptor)
			{
				fseek(fp, -1 + pTypeLib->header.data_pool + pTypeLib->ifaces[i]->m_iface_entry.m_interface_descriptor, SEEK_SET);

				uint16 parent_interface_index = fget16(fp);
				pTypeLib->ifaces[i]->m_nFuncs = fget16(fp);

				pTypeLib->ifaces[i]->m_funcs = new XPFUNCDESC*[pTypeLib->ifaces[i]->m_nFuncs];

				for (int m = 0; m < pTypeLib->ifaces[i]->m_nFuncs; m++)
				{
					pTypeLib->ifaces[i]->m_funcs[m] = new XPFUNCDESC;
					/*
MethodDescriptor {
    boolean         is_getter;
    boolean         is_setter;
    boolean         is_not_xpcom;
    boolean         is_constructor;
    boolean         is_hidden;
    uint3           reserved;
    Identifier*     name;
    uint8           num_args;
    ParamDescriptor params[num_args];
    ParamDescriptor result;
}
*/

					uint8 flags = fget8(fp);
					DWORD name = fget32(fp);
					uint8 num_args = fget8(fp);

					for (int p = 0; p < num_args; p++)
					{
						ReadParamDescriptor(fp);
					}
					ReadParamDescriptor(fp);

					sysstring str;
					ReadIdentifierFromLocation(fp, -1 + pTypeLib->header.data_pool + name, str);
					pTypeLib->ifaces[i]->m_funcs[m]->name = str;
				}

				uint16 num_constants = fget16(fp);
				for (int c = 0; c < num_constants; c++)
				{
				/*
				ConstDescriptor
				{ 
				Identifier*     name;
				TypeDescriptor  type; 
				<type>          value;}
				*/
					DWORD name = fget32(fp);
					uint8 tag = ReadTypeDescriptor(fp);
					if (tag == 0)
					{
						char value = fget8(fp);
					}
					else if (tag == 1)
					{
						short value = fget16(fp);
					}
					else if (tag == 2)
					{
						long value = fget32(fp);
					}
					else if (tag == 4)
					{
						uint8 value = fget8(fp);
					}
					else if (tag == 5)
					{
						uint16 value = fget16(fp);
					}
					else if (tag == 6)
					{
						uint32 value = fget32(fp);
					}
					else
					{
						throw -1;//exit(1);
					}
				}
				/*
				boolean                  is_scriptable;
				boolean                  is_function;
				uint6                    reserved;
				*/
				uint8 flags = fget8(fp);

		/*
InterfaceDescriptor {
    uint16                   parent_interface_index;
    uint16                   num_methods;
    MethodDescriptor         method_descriptors[num_methods];
    uint16                   num_constants;
    ConstDescriptor          const_descriptors[num_constants];
    boolean                  is_scriptable;
    boolean                  is_function;
    uint6                    reserved;

}
		*/
			}
		}

		*ppTypeLib = pTypeLib;
		return S_OK;
	}
	else
	{
		return E_FAIL;
	}
}
