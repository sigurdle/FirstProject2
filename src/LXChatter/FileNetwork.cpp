#include "stdafx.h"
#include "LXChatter2.h"
#include "FileNetwork.h"
//#include <sstream>
//#include <algorithm>

#include "../LXUI/Socket.h"
#pragma comment(lib, "ws2_32.lib")	// TODO, should not be necessary

uint8 Base32Char(int c)
{
	if (c >= 'A' && c <= 'Z')
	{
		return c - 'A';
	}
	else if (c >= 'a' && c <= 'z')
	{
		return c - 'a';
	}
	else if (c >= '2' && c <= '7')
	{
		return (26 - '2') + c;
	}

	ASSERT(0);
	return -1;
}
