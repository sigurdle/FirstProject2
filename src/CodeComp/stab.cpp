#include "stdafx.h"
#include "LFC/debug.h"
#include "stab.h"
#include "a_out.h"

namespace System
{
using namespace std;

static String get_name(const char* &p)
{
	IO::StringWriter name;

	int n = 0;

	while (*p)
	{
		if (*p == '<')
		{
			n++;
		}
		else if (*p == '>')
		{
			n--;
		}
		else if (*p == ':')
		{
			if (n == 0)
			{
				break;
			}
		}

		name << *p;
		p++;
	}
	ASSERT(*p == ':');
	if (*p != ':')
	{
		ASSERT(0);
		THROW(-1);
	}

	p++;

	return name.str();
}

static int get_number(const char* &p)
{
	int sign;
	if (*p == '-')
	{
		sign = -1;
		p++;
	}
	else
		sign = 1;

	ASSERT(isdigit(*p));
	int num = *p - '0';
	p++;

	while (*p && isdigit(*p))
	{
		num *= 10;
		num += *p - '0';
		p++;
	}

	if (sign < 0) num = -num;
	return num;
}

void eat(const char* &p, char c)
{
	if (*p != c)
	{
		ASSERT(0);
		THROW(-1);
	}

	p++;
}

//Type* get_type(const char* &p, StringA name);

Type* StabDebugInfo::get_type2(const char* &p, StringIn name, int file_num, int type_num)
{
	Type* pType = nullptr;

	char typeDescriptor = *p++;
//	TRACE("%c", typeDescriptor);
	switch (typeDescriptor)
	{
	case 's':	// struct
		{
			ClassType* pClass = new ClassType();
			pType = pClass;
			//pClass->AddRef();

			pClass->m_kwType = ClassKey_struct;
			pClass->m_name = name;
			
			ASSERT(pType != NULL);
			//ASSERT(m_types[file_num*100 + type_num] == NULL);

			//Class* pClass2 = (Class*)m_types[file_num*100 + type_num];

			//if (pClass2 == NULL)
			m_types[file_num*100 + type_num] = pType;
		
//			TRACE("struct");
			int size = get_number(p);
			pClass->m_sizeof = size;// / 8;
			
			if (*p == '!')
			{
				p++;

				int nbases = get_number(p);
				eat(p, ',');

				for (int i = 0; i < nbases; i++)
				{
					char virtualChar = *p++;
					char visibilityChar = *p++;
					long offset = get_number(p);
					eat(p, ',');
					System::Type* baseType = get_type(p, nullptr);
					eat(p, ';');
				}
			}

			while (*p != ';')
			{
				Declarator* pMemberDecl = new Declarator;
				pMemberDecl->m_name = get_name(p);

				if (*p == '/')
				{
					p++;
					char visibility = *p++;
					ASSERT(isdigit(visibility));
				}

				if (pMemberDecl->m_name.GetLength() && pMemberDecl->m_name.LeftOf(3) == "$vb")
				{
					System::Type* pType = get_type(p, nullptr);

					eat(p, ',');
					pMemberDecl->m_offset = get_number(p) / 8;
				}
				else if (pMemberDecl->m_name.GetLength() && pMemberDecl->m_name.LeftOf(3) == "$vf")
				{
					System::Type* pType = get_type(p, nullptr);

					eat(p, ',');
					pMemberDecl->m_offset = get_number(p) / 8;
				}
				else if (*p == ':')	// Method
				{
					p++;
					do
					{
						System::Type* pType = get_type(p, nullptr);
						
						eat(p, ':');
						
						while (*p)
						{
							if (*p == ';')
								break;
							p++;
						}
						eat(p, ';');
						char number = *p++; ASSERT(isdigit(number));
						char letter = *p++; //ASSERT(isalpha(letter));
						ASSERT(letter == 'A' || letter == 'B' || letter == 'C' || letter == 'D');

						int next = *p++;
						switch (next)
						{
						case '.':	// normal
							break;

						case '*':	// virtual
							{
							get_number(p);
							//ASSERT(0);
							eat(p, ';');
							get_type(p, nullptr);
							eat(p, ';');
							}
							break;

						case '?':	// static;
							break;

						default:
							ASSERT(0);
						}
					}
					while (*p != ';');

						/*
					if (*p != ';')
					{
						Type* pType = get_type(p, StringA());
						eat(p, ':');
						
						while (*p)
						{
							if (*p == ';')
								break;
							p++;
						}

						eat(p, ';');
						char number = *p++; ASSERT(isdigit(number));
						char letter = *p++; //ASSERT(isalpha(letter));
						ASSERT(letter == 'A' || letter == 'B' || letter == 'C' || letter == 'D');

						int next = *p++; ASSERT(next == '.' || next == '*');
						ASSERT(next == '.');

					}
					*/
				}
				else
				{
					pMemberDecl->m_pType = get_type(p, nullptr);
					
					if (*p == ':')	// static member
					{
						p++;
						while (*p)
						{
							if (*p == ';')
								break;

							p++;
						}

					//	get_name(p);
					}
					else
					{
						eat(p, ',');
						pMemberDecl->m_offset = get_number(p) / 8;
						
						eat(p, ',');
						int numbits = get_number(p) / 8;

						pClass->m_pScope->AddDeclarator(pMemberDecl);
					}
				}
				
				eat(p, ';');
			}
			eat(p, ';');

			// For classes containing virtual functions the very last section of the string part of the stab holds a type reference to the first base class.
			if (*p == '~')
			{
				p++;
				eat(p, '%');
				get_type(p, nullptr);
				eat(p, ';');
			}

			/*
			if (pClass2)
			{
				if (!pClass->Equals(pClass2))
				{
					ASSERT(0);
				}
			}
			*/
		}
		break;
		
	case 'u':	// union
		{
			ClassType* pClass = new ClassType();
			pType = pClass;
		//	pClass->AddRef();
			pClass->m_kwType = ClassKey_union;

			pClass->m_name = name;
			
			ASSERT(pType != NULL);
		//	ASSERT(m_types[file_num*100 + type_num] == NULL);
			m_types[file_num*100 + type_num] = pType;
			
//			TRACE("union");
			int size = get_number(p);
			pClass->m_sizeof = size;// / 8;
			
			while (*p != ';')
			{
				Declarator* pMemberDecl = new Declarator;
				pMemberDecl->m_name = get_name(p);
				
				if (*p == ':')	// Method
				{
					p++;

					do
					{
						System::Type* pType = get_type(p, nullptr);
						
						eat(p, ':');
						
						while (*p)
						{
							if (*p == ';')
								break;
							p++;
						}
						eat(p, ';');
						char number = *p++; ASSERT(isdigit(number));
						char letter = *p++; ASSERT(isalpha(letter));
						int next = *p++; ASSERT(next == '.' || next == '*');
						ASSERT(next == '.');
					}
					while (*p != ';');
				}
				else
				{
					
					pMemberDecl->m_pType = get_type(p, nullptr);
					
					eat(p, ',');
					pMemberDecl->m_offset = get_number(p) / 8;
					
					eat(p, ',');
					int numbits = get_number(p) / 8;
					
					pClass->m_pScope->AddDeclarator(pMemberDecl);
				}
				
				eat(p, ';');
			}
			eat(p, ';');
		}
		break;
		
	case 'e':	// enum
		{
			NamedType* pType2 = m_pReceiver->LookupNamedType(name);

			EnumType* pEnum = new EnumType;
			pEnum->m_name = name;
	
			while (*p != ';')
			{
				String name = get_name(p);
				long value = get_number(p);

				//EnumDef& enumDef = new ;
				
				pEnum->m_deflist.push_back(EnumDef(name, value));
				
				eat(p, ',');
			}
			eat(p, ';');

			if (pType2)
			{
#if 0
				if (!pType2->Equals(*pEnum))
				{
				//	ASSERT(0);
				}
#endif
				pType = pType2;

			}
			else
			{
				pType = pEnum;
			}

			m_types[file_num*100 + type_num] = pType;
		}
		break;
		
	case 'a':	// array
		{
			get_type2(p, nullptr, -1, -1);	// index type

			get_type(p, nullptr);	// element type
		}
		break;
		
	case 'f':	// function type
		{
			pType = new FunctionType;//new Type(type_function);
			//pType->m_pFunction = ;
			pType->AsFunction()->m_pReturnType = get_type(p, nullptr);
		}
		break;
#if 0
	case 'f': /* || typeDescriptor == 'F' */
		{
			Type* pReturnType = get_type(p);
			// TODO
			/*
			if (*p == ',')
			{
			p++;
			}
			eatchar(';');
			*/
		}
		break;
#endif
		
	case 'r':	// subrange type
		{
		/*
		pType = new PrimitiveType;//(type_int, 4);
		ASSERT(pType);
		ASSERT(m_types[file_num*100 + type_num] == NULL);
		m_types[file_num*100 + type_num] = pType;
			*/
			
			Type* pType2 = get_type(p, nullptr);
			eat(p, ';');
			
			int lower = get_number(p);
			eat(p, ';');
			
			int upper = get_number(p);
			eat(p, ';');
			
			//Type_type type;
			
			LONGLONG range = (LONGLONG)upper - (LONGLONG)lower;
			if (range <= 255)
			{
				pType = &Types::type_char;
				//	pType->m_sizeof = 1;
			}
			else if (range <= 65535)
			{
				pType = &Types::type_short;
				//	pType->m_sizeof = 2;
			}
			else// if (range <= MAX_INT)
			{
				pType = &Types::type_int;
				//	pType->m_sizeof = 4;
			}
			//pType = System::PrimitiveType(type);//(type_int, 4);

			if (type_num != -1)
			{
				if (m_types[file_num*100 + type_num] != NULL)
				{
					/*
					if (!m_types[file_num*100 + type_num]->Equals(pType))
					{
						ASSERT(0);
					}
					*/
				}
				//ASSERT(m_types[file_num*100 + type_num] == NULL);
				m_types[file_num*100 + type_num] = pType;
			}	
		}
		break;
		
	case 'R':
		{
			char fp_type = *p++;
			
			if (fp_type == '1')			pType = &Types::type_float;
			else if (fp_type == '2')	pType = &Types::type_double;
			else
				ASSERT(0);	// TODO
			
			eat(p, ';');
			int /*pType->m_*/ _sizeof = get_number(p);
			VERIFY(pType->get_sizeof() == _sizeof);
			
		//	ASSERT(m_types[file_num*100 + type_num] == NULL || m_types[file_num*100 + type_num]->Equals(pType));
			m_types[file_num*100 + type_num] = pType;
		}
		break;
		
	case '*':
		{
			pType = new PointerType(get_type(p, nullptr));
			
//			ASSERT(m_types[file_num*100 + type_num] == NULL || m_types[file_num*100 + type_num]->Equals(pType));
			m_types[file_num*100 + type_num] = pType;
		}
		break;
		
	case '&':
		{
			pType = new ReferenceType(get_type(p, nullptr));
			
		//	ASSERT(m_types[file_num*100 + type_num] == NULL);
			m_types[file_num*100 + type_num] = pType;
		}
		break;
		
	case 'k':
		{
			pType = new ModifierType(get_type(p, nullptr), true, false);
		//	((CVType*)pType)->m_bConst = true;
			
		//	ASSERT(m_types[file_num*100 + type_num] == NULL || m_types[file_num*100 + type_num]->Equals(pType));
			m_types[file_num*100 + type_num] = pType;
		}
		break;
		
	case 'B':
		{
			pType = new ModifierType(get_type(p, nullptr), false, true);
		//	((CVType*)pType)->m_bVolatile = true;
			
		//	ASSERT(m_types[file_num*100 + type_num] == NULL || m_types[file_num*100 + type_num]->Equals(pType));
			m_types[file_num*100 + type_num] = pType;
		}
		break;
		
	case '#':
		{
			if (*p == '#')
			{
				p++;
				
				Type* returnType = get_type(p, nullptr);
				eat(p, ';');
				
				// the class and argument types are not specified, specified, and must be
				// determined by demangling the name of the method if it is available
			}
			else
			{
				Type* classType = get_type(p, nullptr);
				eat(p, ',');
				Type* returnType = get_type(p, nullptr);
				//eat(p, ',');
				while (*p == ',')
				{
					p++;
					Type* paramType = get_type(p, nullptr);
				}
				eat(p, ';');
			}
		}
		break;
		
	case '-':	// negative type descriptor
		{
			int num = -get_number(p);
			eat(p, ';');
			
			switch (num)
			{
			case -16:
				pType = &Types::type_int;	// 32bit boolean
				break;
				
			default:
				ASSERT(0);
				throw new Exception(L"parse error");
			}
			
			//		pType = new Type(type_pointer, sizeof_pointer);
			//		pType->m_pPointerTo = get_type(p);
			
		//	ASSERT(m_types[file_num*100 + type_num] == NULL || m_types[file_num*100 + type_num]->Equals(pType));
			m_types[file_num*100 + type_num] = pType;
		}
		break;

	case 'x':	// forward reference
		{
			char type = *p++;
			ASSERT(type == 's' || type == 'u' || type == 'e');
			String name = get_name(p);
		}
		break;

	default:
		{
			ASSERT(0);
			// TODO
			pType = &Types::type_int;
			ASSERT(pType != NULL);
		//	ASSERT(m_types[file_num*100 + type_num] == NULL);
			m_types[file_num*100 + type_num] = pType;
		}
	}

	return pType;
}

Type* StabDebugInfo::get_type(const char* &p, StringIn name)
{
	int file_num = 0;
	int type_num = 0;
	if (*p == '(')
	{
		p++;

		file_num = get_number(p);
		eat(p, ',');

		type_num = get_number(p);
		eat(p, ')');
	}
	else
	{
		file_num = 0;
		type_num = get_number(p);
	}
//	TRACE("(filenumber:%d, type_number:%d)", file_num, type_num);

	if (*p == '=')	// type definition
	{
//		TRACE("=");

		p++;

		if (!isdigit(*p) && *p != '-' && *p != '(')	// type descriptor
		{
			while (*p == '@')
			{
				p++;
				char c = *p++;
				if (c == 's')
				{
					int size = get_number(p);
				}
				else
				{
					while (*p)
					{
						if (*p == ';')
							break;
						p++;
					}
				}
				eat(p, ';');
			}

			Type* pType = get_type2(p, name, file_num, type_num);

			return pType;
		}
		else
		{
			Type* pType = NULL;
			pType = get_type(p, nullptr);

			if (pType == nullptr)
			{
				pType = Types::get_void();
			}

			/*
			if (m_types[file_num*100 + type_num])
			{
				if (!m_types[file_num*100 + type_num]->Equals(pType))
				{
					ASSERT(0);
				}
			}
			*/

			//ASSERT(m_types[file_num*100 + type_num] == NULL);
			m_types[file_num*100 + type_num] = pType;

			return pType;
		}
	}
	else	// type reference
	{
		Type* pType = m_types[file_num*100 + type_num];
	//	ASSERT(pType);
		return pType;
	}

	return NULL;
}

#define printf	TRACE

#if 0
CodeCompExt CDeclarator* stab_lsym(char* p, Scope* pScope)
{
//	Stab* pStab = new Stab;

	TRY
	{
		CDeclarator* pDecl = new CDeclarator;
	//	pStab->m_name = get_name(p);
		pDecl->m_name = get_name(p);

		TRACE("%s", pDecl->m_name.c_str());

		printf("stab_lsym: %s\n", pDecl->m_name.c_str());

	//	if (*p == ':')
		{

			uint16 symbolDescriptor = 0;
			if (isalpha(*p))
			{
				symbolDescriptor = *p++;
				if (isalpha(*p))
				{
					symbolDescriptor += (*p++) << 8;
				}
				TRACE("%c", symbolDescriptor);
			}

			if (symbolDescriptor == 'c')	// constant
			{
				if (*p == '=')
				{
					p++;
				}
				else
					ASSERT(0);
			}
			else
			{
				pDecl->m_pType = get_type(p, StringA());

				if (symbolDescriptor == 't' || symbolDescriptor == 'tT' || symbolDescriptor == 'Tt')
				{
					Type* pType = pDecl->m_pType;

					if (pType->m_type == type_class ||
						pType->m_type == type_typedef ||
						pType->m_type == type_enum)
					{
						NamedType* pNamedType = (NamedType*)pType;//
						pNamedType->m_name = pDecl->m_name;
						pScope->m_types.insert(typemap::value_type(pNamedType->m_name, pNamedType));
						delete pDecl;
					}

					return NULL;
#if 0
					Type* pType2 = new Type(type_typedef);
					pType2->m_pDeclarator = pDecl;

					pScope->m_types.insert(typemap::value_type(pDecl->m_name, pType2));
#endif

					//_Typedef
				}
				else if (symbolDescriptor == 'f' || symbolDescriptor == 'F')	// local or global function
				{
					Type* pType2 = new CFunction();
					pType2->GetFunction()->m_pReturnType = pDecl->m_pType;
					pDecl->m_pType = pType2;

				//	pType = 
				//	pType->m_pFunction->m_pReturnType = get_type(p);

				//	pScope->m_decls.insert(declsmap::value_type(pDecl->m_name, new CDeclaratorReference(pDecl)));
				}
				else
				{
					// ??
					pScope->m_decls.insert(declsmap::value_type(pDecl->m_name, new CDeclaratorReference(pDecl)));
				}
			}
		}

		TRACE("\n");

		return pDecl;
	}
	CATCH(int n)
	{
		return NULL;
	}
}
#endif

void StabDebugInfo::stab_lsym(const char* p, Scope* pScope)
{
	TRY
	{
		String name = get_name(p);

		DebugTraceLn(name);

	//	printf("stab_lsym: %s\n", name.c_str());

	//	if (*p == ':')
		{

			uint16 symbolDescriptor = 0;
			if (isalpha(*p))
			{
				symbolDescriptor = *p++;
				if (isalpha(*p))
				{
					symbolDescriptor += (*p++) << 8;
				}
			//	TRACE("%c", symbolDescriptor);
			}

			if (symbolDescriptor == 'c')	// constant
			{
				if (*p == '=')
				{
					p++;
				}
				else
					ASSERT(0);
			}
			else
			{
				Type* pType = get_type(p, name);
				/*
				NamedType* pNamedType = dynamic_cast<NamedType*>(pType);
				if (pNamedType)
				{
					pNamedType->m_name = name;
				}
				*/

				if (symbolDescriptor == 't' || symbolDescriptor == 'tT' || symbolDescriptor == 'Tt')
				{
				//	Type* pType = pDecl->m_pType;

					if (pType->get_Kind() == type_class ||
						pType->get_Kind() == type_typedef ||
						pType->get_Kind() == type_enum)
					{
					//	NamedType* pNamedType = (NamedType*)pType;//
					//	pNamedType->m_name = pDecl->m_name;
					//	pScope->m_types.insert(typemap::value_type(pNamedType->m_name, pNamedType));
					//	delete pDecl;
						m_pReceiver->OnType(name, dynamic_cast<NamedType*>(pType), 0);
					}
					return;

					//return NULL;
#if 0
					Type* pType2 = new Type(type_typedef);
					pType2->m_pDeclarator = pDecl;

					pScope->m_types.insert(typemap::value_type(pDecl->m_name, pType2));
#endif

					//_Typedef
				}
				else if (symbolDescriptor == 'f' || symbolDescriptor == 'F')	// local or global function
				{
					Declarator* pDecl = new Declarator;
					Type* pType2 = new FunctionType();
					pType2->AsFunction()->m_pReturnType = pType;
					pDecl->m_pType = pType2;

				//	pType = 
				//	pType->m_pFunction->m_pReturnType = get_type(p);

				//	pScope->m_decls.insert(declsmap::value_type(pDecl->m_name, new CDeclaratorReference(pDecl)));
				}
				else
				{
#if 0	// ??
					// ??
					pScope->m_decls.insert(declsmap::value_type(pDecl->m_name, new CDeclaratorReference(pDecl)));
#endif
				}
			}
		}

	//	TRACE("\n");

	}
	CATCH(int n)
	{
		ASSERT(0);
	}
}

StabDebugInfo::StabDebugInfo()
{
	m_pGlobalScope = new Scope;

	m_types.resize(100 * 10000);
}

StabDebugInfo::~StabDebugInfo()
{
	//delete[] m_types;

	delete m_pGlobalScope;
}

int StabDebugInfo::Parse(ObjectFileParser* pImage, IDebugInfoReceiver* receiver, ULONG_PTR dwData)
{
	ASSERT(0);
	return 0;
}

void StabDebugInfo::FromStab(/*std::vector<SourceFile*>& sourceFiles, Scope* pGlobalScope,*/ uint32 offaddr, nlist* stab, int nstabs, IDebugInfoReceiver* pReceiver)
{
	m_pReceiver = pReceiver;//D->m_debugInfo;
#if 0
	{
		for (int i = 0; i < ctx->m_pImage->header->NumberOfSections; i++)
		{
			IMAGE_SECTION_HEADER* pSectionHeader = &ctx->m_pImage->SectionHeader[i];

			if (!strncmp((const char*)pSectionHeader->Name, ".stab", 8))
			{
				ctx->stab = (nlist*)(ctx->m_pImage->m_fbuf + pSectionHeader->PointerToRawData);

				ctx->nstabs = pSectionHeader->SizeOfRawData / sizeof(nlist);
			}
			else if (!strncmp((const char*)pSectionHeader->Name, ".stabstr", 8))
			{
				ctx->stabstr = (char*)(ctx->m_pImage->m_fbuf + pSectionHeader->PointerToRawData);
			}
		}
	}
#endif

//////////////
	{
		SourceFile* pCurrentSourceFile = nullptr;
		//Scope* pFunctionBodyScope = NULL;
		Scope* pCurrentScope = m_pGlobalScope;
	//	uint32 fun_address = 0;

	//	ctx->sourceFileName = NULL;
		for (int nstab = 0; nstab < nstabs; nstab++)
		{
			nlist* pSymbol = &stab[nstab];
			const char* name = pSymbol->n_un.n_name;//stabstr + pSymbol->n_un.n_strx;
			//TRACE("%s\n", name);

			if (pSymbol->n_type == N_SO)
			{
				int len = strlen(name);
				if (len == 0)
				{
					// End the previous sourcefile / segment
					if (pCurrentSourceFile)
					{
						pCurrentSourceFile->m_segments[0].m_endAddress = pSymbol->n_value + offaddr;
					}
				}
			// If it ends with a slash, it's the directory where it was compiled, so keep searching
				else if (name[len-1] == '/')
				{
					// The path where the source file was compiled
					// Currently ignore
				}
				else
				{
					// Start a new source file and corresponding segment
					pCurrentSourceFile = new SourceFile;
					/*ctx->*/ m_sourceFiles.Add(pCurrentSourceFile);

#if 0//_WINDOWS
					char filename[512];
					PathCanonicalize(filename, name);
					char* p;
					while (p = strchr(filename, '\\'))	// A like forward slashes better :)
					{
						*p = '/';
					}
#else
					const char* filename = name;
#endif
				//	printf("f: %s\n", filename);

					SourceFile::Segment segment;
					segment.m_startAddress = pSymbol->n_value + offaddr;

					pCurrentSourceFile->m_filename = string_copy(filename);
					pCurrentSourceFile->m_segments.Add(segment);

#if 0
					FILE* sfp = fopen(name, "r");
					if (sfp)
					{
						StringA str;

						while (!feof(sfp))
						{
							int c = fgetc(sfp);

							str += c;

							if (c == '\n')
							{
								pCurrentSourceFile->sourceLines.Add(str);
								str = "";
							}
						}
						if (str.length())
							pCurrentSourceFile->sourceLines.Add(str);

						fclose(sfp);
					}
#endif
				}
			}
			else
			{
				switch (pSymbol->n_type)
				{
				case N_SOL:
					{
						if (pCurrentSourceFile)
						{
							pCurrentSourceFile->m_segments[0].m_endAddress = pSymbol->n_value + offaddr;
					//		pCurrentSourceFile->endAddress = pSymbol->n_value;
						}

						// Start a new source file / segment
						pCurrentSourceFile = new SourceFile;
						/*ctx->*/ m_sourceFiles.Add(pCurrentSourceFile);

						pCurrentSourceFile->m_filename = string_copy(name);
//						pCurrentSourceFile->startAddress = pSymbol->n_value;
						SourceFile::Segment segment;
						segment.m_startAddress = pSymbol->n_value + offaddr;
						pCurrentSourceFile->m_segments.Add(segment);

#if 0
						FILE* sfp = fopen(name, "r");
						if (sfp)
						{
							StringA str;

							while (!feof(sfp))
							{
								int c = fgetc(sfp);

								str += c;

								if (c == '\n')
								{
									pCurrentSourceFile->sourceLines.Add(str);
									str = "";
								}
							}
							if (str.length())
								pCurrentSourceFile->sourceLines.Add(str);

							fclose(sfp);
						}
#endif
					}
					break;

				case N_FUN:
					{
#if 0
						if (name[0])
						{
							printf("function %d\n", pSymbol->n_value);

							// We currently don't use the symbols value (the functions address)

							CDeclarator* pDecl = stab_lsym(name, pCurrentScope);

							Scope* pScope = T_Scope();
							pScope->m_pParentScope = pCurrentScope;
							pCurrentScope->m_subScopes.Add(pScope);
							pScope->m_pType = pDecl->m_pType;
							pScope->m_name = pDecl->m_name;
							pCurrentScope = pScope;
							pCurrentScope->m_startAddress = pSymbol->n_value + offaddr;

							// Prepare a scope for local variables, but don't add it to parent yet,
							// as we don't know if there are any local variables
							{
								Scope* pScope = T_Scope();
								pScope->m_pParentScope = pCurrentScope;
								pCurrentScope = pScope;
								pCurrentScope->m_startAddress = 0;//pSymbol->n_value + offaddr;
								pCurrentScope->m_endAddress = 0;	// Not known yet
							}
						}
						else
						{
#if 0
						//	pCurrentScope->m_endAddress = pCurrentScope->m_startAddress + pSymbol->n_value;
							pCurrentScope = pCurrentScope->m_pParentScope;
							pCurrentScope = pCurrentScope->m_pParentScope;
#endif
							printf("end_function\n");
						}
#endif
					}
					break;

				case N_LBRAC:
					{
					//	printf("{ %d\n", pSymbol->n_value);
#if 0

					// Finish the current scope
						pCurrentScope->m_startAddress = pSymbol->n_value + offaddr;

						if (pCurrentScope->m_pParentScope == NULL)
							THROW(-1);

						pCurrentScope->m_pParentScope->m_subScopes.Add(pCurrentScope);

					// Prepare a scope for next block (but don't add it to parent yet)
						Scope* pScope = T_Scope();
						pScope->m_pParentScope = pCurrentScope;
						pCurrentScope = pScope;
						pCurrentScope->m_startAddress = 0;//pSymbol->n_value + offaddr;
						pCurrentScope->m_endAddress = 0;	// Not known yet
						
#if 0
						ASSERT(pCurrentScope);

						if (pCurrentScope == NULL)
							THROW(-1);

	//					ASSERT(pCurrentScope->m_pParentScope);

					//	printf("{ %X\n", pCurrentScope->m_startAddress);

						// If we get here, pCurrentScope is valid, so add it to parent
						pCurrentScope->m_startAddress = pSymbol->n_value + offaddr;
						pCurrentScope->m_pParentScope->m_subScopes.Add(pCurrentScope);

						Scope* pScope = new Scope;
						pScope->m_pParentScope = pCurrentScope;
						pCurrentScope = pScope;
						pCurrentScope->m_startAddress = 0;//pSymbol->n_value + offaddr;
						pCurrentScope->m_endAddress = 0;	// Not known yet
					//	pCurrentScope->m_subScopes.Add(pScope);

						//ASSERT(pCurrentScope->m_pParentScope);
					//	pCurrentScope->m_startAddress = fun_address + pSymbol->n_value;
#endif
#endif
					}
					break;

				case N_RBRAC:
					{
#if 0
						printf("} %d\n", pSymbol->n_value);

						Scope* pScope = pCurrentScope;
						pCurrentScope = pCurrentScope->m_pParentScope;

						if (pScope->m_startAddress == pScope->m_endAddress)
							delete pScope;

						pCurrentScope->m_endAddress = offaddr + pSymbol->n_value;//fun_address/*pCurrentScope->m_startAddress*/ + pSymbol->n_value;

						// ??
						pCurrentSourceFile->m_segments[0].m_endAddress = pCurrentScope->m_endAddress;//pSymbol->n_value + offaddr;

						if (pCurrentScope->m_pParentScope->m_pType && pCurrentScope->m_pParentScope->m_pType->m_type == type_function)
						{
							pCurrentScope = pCurrentScope->m_pParentScope;
							pCurrentScope->m_endAddress = offaddr + pSymbol->n_value;//fun_address/*pCurrentScope->m_startAddress*/ + pSymbol->n_value;
							pCurrentScope = pCurrentScope->m_pParentScope;
						}

#if 0
						if (pCurrentScope->m_pParentScope->m_endAddress < pCurrentScope->m_endAddress)
							pCurrentScope->m_pParentScope->m_endAddress = pCurrentScope->m_endAddress;

					//	pCurrentScope = pCurrentScope->m_pParentScope;
#endif
#endif
					}
					break;
#if 0
				case N_BINCL:
					{
						/*
						SourceFile* pFile = new SourceFile;
						pFile->sourceFileName = name;
						pFile->m_pParentFile = pCurrentSourceFile;
						pFile->startAddress = pSymbol->n_value;
						if (pCurrentSourceFile)
						{
							pCurrentSourceFile->sourceFiles.Add(pFile);
						}
*/
						TRACE("Inlude file %s\n", name);
/*
						pCurrentSourceFile = pFile;
						*/
					}
					break;

				case N_EINCL:
					{
						TRACE("end of Inlude file\n");
						/*
						if (pCurrentSourceFile->m_pParentFile)
						{
							pCurrentSourceFile = pCurrentSourceFile->m_pParentFile;
						}
						else
						{
							MessageBox(NULL, "unmatched end of include file stab", "", MB_OK);
						}
						*/
					}
					break;
#endif
				case N_SLINE:
					{
						if (pCurrentSourceFile)
						{
							pCurrentSourceFile->m_segments[0].m_endAddress = pSymbol->n_value + offaddr;
							pCurrentSourceFile->m_lines.Add(SourceFile::SourceLine(pSymbol->n_value + offaddr, pSymbol->n_desc));
						}
					}
					break;

				case N_LSYM:
					{
						int len = std::strlen(name);
						//StringA* name2;
						IO::StringWriter name2;

						ASSERT(0);
#if 0
						name2 << StringA(name, (name[len-1] == '\\')? len-1: len);
						while (name[len-1] == '\\')
						{
							nstab++;
							nlist* pSymbol = &stab[nstab];
							name = pSymbol->n_un.n_name;
							len = strlen(name);

							name2 << StringA(name, (name[len-1] == '\\')? len-1: len);
						}
#endif
						name2 << '\0';
						stab_lsym(name2.str().GetData8(), pCurrentScope);

#if 0	// TODO, have this
					//	break;//
						printf("Local symbol:value: %d\t", pSymbol->n_value);
						CDeclarator* pDecl = stab_lsym(name, pCurrentScope);
						if (pDecl)
						{
							pDecl->m_localVar = true;
							pDecl->m_offset = pSymbol->n_value;

						//	pCurrentScope->m_decls.insert(declsmap::value_type(pDecl->m_name, new CDeclaratorReference(pDecl)));
						}
#if 0
						pCurrentSourceFile->m_stabvec.Add(pSymbol);
#endif
#endif
					}
					break;

				case N_PSYM:
					{
#if 0
						printf("Parameter symbol:value: %d\t", pSymbol->n_value);
						CDeclarator* pDecl = stab_lsym(name, pCurrentScope);
						if (pDecl)
						{
							pDecl->m_localVar = true;
							pDecl->m_offset = pSymbol->n_value;

						//	pCurrentScope->m_decls.insert(declsmap::value_type(pDecl->m_name, new CDeclaratorReference(pDecl)));
						}
#endif
					}
					break;

				case N_GSYM:
					{
#if 0
						printf("Global symbol:value: %d\t", pSymbol->n_value);
						CDeclarator* pDecl = stab_lsym(name, pCurrentScope);
#if 0
						if (pDecl)
						{
							pDecl->m_tempLabel = new Temp_label;

							tysymbolmap_name::iterator si = ctx->symbols_name.find("_" + pDecl->m_name);
							if (si != ctx->symbols_name.end())
							{
								DebugSymbol* pDebugSymbol = (*si).second;
								pDecl->m_tempLabel->m_spOffset = pDebugSymbol->m_address;

								MessageBeep(-1);
							}
						}
#endif
#endif
					}
					break;

				default:
					{
					//	stab_lsym(name);
					//	TRACE("%s\n", name);

						if (pCurrentSourceFile)
						{
						//	stab(name);

						//	pCurrentSourceFile->m_stabvec.Add(pSymbol);
						}
					}
				}
			}
		}

		ASSERT(pCurrentScope);

		while (pCurrentScope->m_pParentScope)
		{
			if (pCurrentScope->m_pParentScope->m_endAddress < pCurrentScope->m_endAddress)
			{
				pCurrentScope->m_pParentScope->m_endAddress = pCurrentScope->m_endAddress;
			//	printf("} %X\n", pCurrentScope->m_pParentScope->m_endAddress);
			}

			pCurrentScope = pCurrentScope->m_pParentScope;
		}

		if (pCurrentSourceFile)
		{
		//	printf("start: %x\n", pCurrentSourceFile->m_segments[0].m_startAddress);
	//		printf("end: %x\n", pCurrentSourceFile->m_segments[0].m_endAddress);

			SourceFile* p = pCurrentSourceFile->m_pParentFile;

			while (p != NULL)
			{
#if WIN32
				MessageBoxA(NULL, "unmatched include stab", "", MB_OK);
#else
				printf("unmatched include stab\n");
#endif
				p = p->m_pParentFile;
			}
		}
	}
}

}
