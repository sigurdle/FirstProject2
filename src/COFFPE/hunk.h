#include "../Include/doshunks.h"


class CHunk
{
public:
	CHunk()
	{
		m_size = 0;
		m_data = NULL;
	}

	ULONG m_size;
	BYTE* m_data;
};

typedef std::vector<CHunk> hunkvector;
