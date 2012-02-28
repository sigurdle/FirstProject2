// CreateJava.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "../LFC/LFC.h"

#pragma comment(lib, "../LFC/Debug/LFC.lib")

namespace System
{

LFCEXT void printlevels(FILE* fp, int levels);

void printToJava(FILE* fp, ClassType* pClass, CDeclarator* pDeclarator, FunctionType* pType);
void printClassToJava(FILE* fp, ClassType* pClass, int level);

void printToJava(FILE* fp, Type* pType)
{
	switch (pType->get_Kind())
	{
	case type_cv:
		{
			ASSERT(0);
#if 0
			ModifierType* p = (ModifierType*)pType;

			if (p->m_bConst) fprintf(fp, "const ");
			if (p->m_bVolatile) fprintf(fp, "volatile ");

			print(fp, p->m_pPointerTo);
#endif
		}
		break;

	case type_pointer:
		{
			ClassType* pClassTo = pType->GetPointerTo()->GetClass();

			if (pClassTo)
			{
				if (pClassTo == typeid(Object).GetType())
				{
					fprintf(fp, "Object");
				}
				else if (pClassTo == typeid(StringW).GetType())
				{
					fprintf(fp, "String");
				}
				else
				{
					printToJava(fp, pClassTo);
				}
			}
#if 0
			if (((PointerType*)pType)->m_pPointerTo->get_Kind() == type_function)
			{
				fprintf(fp, "TODO: function\n");
			}
			else
			{
				print(fp, ((PointerType*)pType)->m_pPointerTo);
				fprintf(fp, "*");
			}
#endif
		}
		break;

	case type_reference:
		{
			ASSERT(0);
#if 0
			print(fp, ((ReferenceType*)pType)->m_pPointerTo);
			fprintf(fp, "&");
#endif
		}
		break;

	case type_typedef:
		{
		//	print(((Typedef*)pType)->m_pType);
			Typedef* pTypedef = (Typedef*)pType;

			/*
			if (pTypedef->m_ownerScope && pTypedef->m_ownerScope->m_pNamespace->m_name)
			{
				print(fp, pTypedef->m_ownerScope->m_pNamespace);
				fprintf(fp, "::");
			}
			*/

			fprintf(fp, "%s", pTypedef->m_name->c_str());
		}
		break;

	case type_namespace:
		{
			Namespace* pClass = (Namespace*)pType;
			if (pClass->m_ownerScope && pClass->m_ownerScope->m_pNamespace->m_name)
			{
				printToJava(fp, pClass->m_ownerScope->m_pNamespace);
				fprintf(fp, ".");
			}

			fprintf(fp, "%s", pClass->m_name->c_str());
		}
		break;

	case type_class:
		{
			ClassType* pClass = (ClassType*)pType;

			/*
			if (pClass == typeid(Object).GetType())
			{
				fprintf(fp, "Object");
			}
			else if (pClass == typeid(StringW).GetType())
			{
				fprintf(fp, "String");
			}
			else
			*/
			{
				if (pClass->m_ownerScope && pClass->m_ownerScope->m_pNamespace->m_name)
				{
					printToJava(fp, pClass->m_ownerScope->m_pNamespace);
					fprintf(fp, ".");
				}

			/*
				if (pClass->m_pInstantiatedFrom)
				{
					fprintf(fp, "%s", pClass->m_pInstantiatedFromClass->m_name->c_str());
					fprintf(fp, "<");
					for (int i = 0; i < pClass->m_pInstantiatedFrom->m_templateArgs.size(); i++)
					{
						if (i > 0) fprintf(fp, ", ");

						printArg(fp, pClass->m_pInstantiatedFrom->m_templateArgs[i]);
					}
					fprintf(fp, ">");
				}
				else
					*/
				{
			//	fprintf(fp, "%s(0x%x)", pClass->m_name->c_str(), pClass);
					fprintf(fp, "%s", pClass->m_name->c_str());
				}

			//	print((ClassType*)pType, recurseClass);
			}
		}
		break;

	case type_enum:
		{
			fprintf(fp, "%s", ((EnumType*)pType)->m_name->c_str());
		}
		break;

		/*
	case type_templatearg:
		{
			print(fp, (_TemplateArgType*)pType);
		}
		break;
		*/

	case type_array:
		{
			ArrayType* pArrayType = (ArrayType*)pType;

			printToJava(fp, pArrayType->m_pElemType);
			fprintf(fp, "[");
			fprintf(fp, "]");
		}
		break;

	case type_function:
		{
			printToJava(fp, NULL, NULL, (FunctionType*)pType);
		}
		break;

	default:
		{
			switch (((PrimitiveType*)pType)->get_Kind())
			{
			case type_void:							fprintf(fp, "void"); break;
			case type_bool:							fprintf(fp, "bool"); break;

			case type_char:							fprintf(fp, "byte"); break;
			case type_signed_char:					fprintf(fp, "byte"); break;
			case type_unsigned_char:				fprintf(fp, "byte"); break;

			case type_wchar:						fprintf(fp, "char"); break;

			case type_short_int:					fprintf(fp, "short"); break;
			case type_unsigned_short_int:			fprintf(fp, "short"); break;

			case type_int:							fprintf(fp, "int"); break;
			case type_unsigned_int:					fprintf(fp, "int"); break;
			case type_long_int:						fprintf(fp, "int"); break;
			case type_unsigned_long_int:			fprintf(fp, "int"); break;

			case type_long_long:					fprintf(fp, "long"); break;
			case type_unsigned_long_long:			fprintf(fp, "long"); break;

			case type_float:						fprintf(fp, "float");	break;
			case type_double:						fprintf(fp, "double");	break;

			default:
				ASSERT(0);
			}
		}
		break;
	}
}

void printToJava(FILE* fp, ClassType* pClass, CDeclarator* pDeclarator, int level)
{
	if (pDeclarator->m_pType->get_Kind() == type_function)
	{
		printlevels(fp, level);

	//	fprintf(fp, "native ");
		printToJava(fp, pClass, pDeclarator, (FunctionType*)pDeclarator->m_pType);
		fprintf(fp, ";");
	}
	else
	{
		if (pDeclarator->m_fwd)
		{
			ClassType* pClass = (ClassType*)pDeclarator->m_pType;

			printlevels(fp, level);
			fprintf(fp, "%s ", ClassKeyName((ClassKey)pDeclarator->m_pType->GetClass()->m_kwType));
			printToJava(fp, pClass);
			fprintf(fp, ";");
		}
		else if (pDeclarator->m_typedef)
		{
			if (pDeclarator->m_pType->get_Kind() == type_class)
			{
				printClassToJava(fp, pDeclarator->m_pType->GetClass(), level);
			}
			else if (pDeclarator->m_pType->get_Kind() == type_enum)
			{
				printlevels(fp, level);
				fprintf(fp, "enum {};");
			}
			else if (pDeclarator->m_pType->get_Kind() == type_typedef)
			{
				printlevels(fp, level);
				fprintf(fp, "typedef ");
				printToJava(fp, ((Typedef*)pDeclarator->m_pType)->m_pType);
				fprintf(fp, " %s;", pDeclarator->m_name->c_str());
			}
			else
				ASSERT(0);
		}
		else
		{
			printlevels(fp, level);

			printToJava(fp, pDeclarator->m_pType);
			fprintf(fp, " %s;", pDeclarator->m_name->c_str());
		}
	}
}

void printToJava(FILE* fp, ClassType* pClass, CDeclarator* pDeclarator, FunctionType* pType)
{
	/*
	if (pType->m_pTemplateParams)
	{
		fprintf(fp, "template<");
		for (int i = 0; i < pType->m_pTemplateParams->m_templateParams.size(); i++)
		{
			if (i > 0) fprintf(fp, ",");
			printToJava(fp, pType->m_pTemplateParams->m_templateParams[i]);
		}

		fprintf(fp, "> ");
	}
	*/

	fprintf(fp, "public ");

	if (*pDeclarator->m_name != *pClass->m_name)
	{
		fprintf(fp, "native ");
	}

	if (pType->m_pReturnType)
	{
		printToJava(fp, pType->m_pReturnType);
		fprintf(fp, " ");
	}

	if (pDeclarator)
	{
		fprintf(fp, "%s", pDeclarator->m_name->c_str());
	}

	fprintf(fp, "(");
	for (int i = 0; i < pType->m_parameters.m_parameters.size(); i++)
	{
		if (i > 0) fprintf(fp, ",");
		printToJava(fp, pType->m_parameters.m_parameters[i].m_pType);
		fprintf(fp, " %s", pType->m_parameters.m_parameters[i].m_name->c_str());
	}

	if (pType->m_parameters.m_bVarArg)
	{
		VERIFY(0);
		//fprintf(fp, ", ...");
	}

	fprintf(fp, ")");

	if (*pDeclarator->m_name == *pClass->m_name)
	{
		fprintf(fp, "\n{\n}\n");
	}

	/*
	if (pType->m_bConst)
		fprintf(fp, " const");
*/

	//printf("%s", pType->m_name->c_str());
}

void printClassToJava(FILE* fp, ClassType* pClass, int level)
{
	printlevels(fp, level);

	/*
	if (pClass->m_pTemplateParams)
	{
		fprintf(fp, "template<");
		for (int i = 0; i < pClass->m_pTemplateParams->m_templateParams.size(); i++)
		{
			if (i > 0) fprintf(fp, ",");
			print(fp, pClass->m_pTemplateParams->m_templateParams[i]);
		}

		fprintf(fp, "> ");
	}
	*/

	fprintf(fp, "public class %s", pClass->m_name->c_str());
//	fprintToJava(fp, pClass->m_name->c_str());

	/*
	BufferImp<char> buffer;
	StringBuilder<char> strbuilder(&buffer);
	pClass->Write(strbuilder);
	StringA* str = buffer.DetachToString();

//	printf("class %s at 0x%x ", str->c_str(), pClass);
//	printf("class %s ", str->c_str());
*/

	//if (recurseClass)
	{
		if (pClass->m_bases.size())
		{
			fprintf(fp, " extends ");

			if (pClass->m_bases[0]->m_pClass == typeid(Object).GetType())
			{
				fprintf(fp, "Object");
			}
			else
			{
				printToJava(fp, pClass->m_bases[0]->m_pClass);
			}

#if 0
			for (int i = 0; i < pClass->m_bases.size(); i++)
			{
				if (i > 0) fprintf(fp, ", ");
				fprintf(fp, "public ");
				print(fp, pClass->m_bases[i]->m_pClass);
				/*
				BufferImp<char> buffer;
				StringBuilder<char> strbuilder(&buffer);
				pClass->m_bases[i]->m_pClass->Write(strbuilder);
				StringA* str = buffer.DetachToString();

				printf("%s", str->c_str());
				*/
			}
#endif
		}

		fprintf(fp, "\n");
		printlevels(fp, level);
		fprintf(fp, "{\n");

		fprintf(fp, "static {\n");
		fprintf(fp, "System.loadLibrary(\"LFC\");");
		fprintf(fp, "\n}\n");

		for (int i = 0; i < pClass->m_pScope->m_orderedDecls.size(); i++)
		{
			CDeclarator* pMember = pClass->m_pScope->m_orderedDecls[i];

			printToJava(fp, pClass, pMember, level+1);
			/*
			if (pMember->m_fwd)
			{
				print(pMember, false);
			}
			else if (pMember->m_typedef && pMember->m_pType->get_Kind() == type_class)
			{
				print(pMember);
			}
			else
			{
				print(pMember, false);
			}
			*/

			/*
			print(pMember->m_pType);
			printf(" ");
			printf("%s;", pMember->m_name->c_str());
			*/
			fprintf(fp, "\n");
		}

		printlevels(fp, level);
		fprintf(fp, "}\n");
	}
}

}

using namespace System;

int main(int argc, char* argv[])
{
	InitTypes_no_gc();

	if (true)
	{
		StringA* filename = new StringA(true, argv[1]);

		IO::FileByteStream file(filename);
		TypeArchive ar(TypeArchive::Mode_Load, &file, filename);
		ar.m_pGlobalNamespace = new Namespace;
		ar.m_typestuff = new TypeStuff;
		ar.m_typelib = new TypeLib;

		ar.ReadHeader();
		ar.MapObject(ar.m_typelib);
		ar.m_typelib->Load(ar);

		// tojava
		ClassType* pType = (ClassType*)pD->LookupNamedType(&StringA(true, "Lerstad::Test"));

		FILE* fp = fopen("c:\\mmstudio\\java\\Lerstad\\Test.java", "w");
		if (fp)
		{
			if (pType->m_ownerScope->m_pNamespace->m_name)
			{
				fprintf(fp, "package ");
				printToJava(fp, pType->m_ownerScope->m_pNamespace);
				fprintf(fp, ";\n");
				fprintf(fp, "\n");
			}

			printClassToJava(fp, pType, 0);

			fclose(fp);
		}

		{
			FILE* fp = fopen("c:\\mmstudio\\java\\Test.cpp", "w");
			if (fp)
			{
				fprintf(fp, "class %sWrapper", pType->m_name->c_str());
				fprintf(fp, " : public %s", pType->m_name->c_str());
				fprintf(fp, "\n{\n");
				fprintf(fp, "\n};\n");

				fclose(fp);
			}
		}
	}

	return 0;
}

/*

  typedef void* JNIEnv;
typedef void* jobject;
typedef int jint;

extern "C"
{

namespace System
{

DECLSPEC_DLLEXPORT void __stdcall Java_Lerstad_Test_set_1value
  (JNIEnv *env, jobject self, jint value)
{
//	Method*
	MessageBeep(-1);
}

}

}

*/