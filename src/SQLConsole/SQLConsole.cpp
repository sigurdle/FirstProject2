// SQLConsole.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdlib.h>
#include <signal.h>

#pragma comment(lib, "LFC")
#pragma comment(lib, "SQL")

//#include <iostream>
//#include <string>

/*
void handler(int code)
{
	exit(0);
}
*/

#include "SQL/SQL.h"

using namespace System;
using namespace System::sql;

int main(int argc, char* argv[])
{
//	std::string statement;
//	std::cin >> statement;

	//signal(SIGTERM, handler);

	Database db("C:/mmstudio/test.db", "rw");

	char statement[2000];

	do
	{
		printf(">");
		statement[0] = 0;
		gets(statement);

		if (!::strcmp(statement, "q") ||
			!::strcmp(statement, "quit")
			)
		{
			break;
		}

		if (statement[0] == 0)
			continue;

		Table table = db.Execute(statement);
		if (table != NULL)
		{
			unsigned count = table.GetCount();
			unsigned int nfields = table.GetFieldCount();

			{
				printf("**************************\n");
				for (int n = 0; n < nfields; n++)
				{
					IFieldDef* fielddef = table.GetField(n);

					printf("%s ", fielddef->GetName()->ToStringA()->c_str());
				}
				printf("\n");
				printf("**************************\n");
			}

			for (unsigned i = 0; i < count; i++)
			{
				Record record = table[i];

				for (int n = 0; n < nfields; n++)
				{
					Variant value = record[n].GetValue();

					switch (value.kind)
					{
					case VARKIND_STRINGW:
						{
							printf("\"%s\" ", ((StringW*)value)->ToStringA()->c_str());
						}
						break;

					case VARKIND_INT32:
						{
							printf("%d ", value.u.int32_val);
						}
						break;

					default:
						ASSERT(0);
					}

				}

				printf("\n");
			}
		}

		//printf("%s\n", statement);
	}
	while (1);

	return 0;
}
