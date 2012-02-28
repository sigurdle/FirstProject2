#include "stdafx.h"
#include "LFC.h"
#include "BufferManager.h"

#if WIN32

//#include "../include/windows_header.h"

/*
#define Polygon gdiPolygon
#define Polyline gdiPolyline
#define vector winArray
#include <windows.h>
#undef Polygon
#undef Polyline
#undef vector
*/
#endif

namespace System
{

class Block
{
public:
	Block()
	{
		prev = NULL;
		next = NULL;

		next2 = NULL;
		prev2 = NULL;
	}

	Block* next;
	Block* prev;

	Block* next2;
	Block* prev2;
	LONGLONG m_filepos;
	ULONG flags;
};

class Buffer : public IBuffer
{
public:
	Buffer()
	{
//		m_size = -1;
	}

	Ptr<char> operator + (int n)
	{
		return Ptr<char>(this, n);
	}

	ULONG Read(void* pv, ULONGLONG pos, ULONG cb);
	ULONG Write(const void* pv, ULONGLONG pos, ULONG cb);

	//Ptr<char*>& ptr

	BufferManager* m_pManager;

	ULONG GetContentSize();
	uint8* GetContent();
	void ReleaseContent();

	ULONGLONG GetSize();

	ULONGLONG m_index;

	ULONGLONG GetIdentity()
	{
		/*
		if (m_blocks.size() > 0)
			return m_blocks[0]->m_filepos;
		else
			return 0;
			*/
		return m_index;
	}

	void SetSize(ULONGLONG size);

	void Close()
	{
	}

	vector<Block*> m_blocks;
//	LONGLONG m_size;
};

ULONGLONG Buffer::GetSize()
{
	return m_blocks.GetSize() * m_pManager->m_blocksize;
}

ULONG Buffer::Read(void* pv, ULONGLONG pos, ULONG cb)
{
	int nblock = 0;
	ULONGLONG blockpos = pos;
	while (blockpos >= m_pManager->m_blocksize)
	{
		blockpos -= m_pManager->m_blocksize;
		nblock++;
	}

	uint8* pb = (uint8*)pv;

	ULONGLONG n = 0;
	while (n < cb)
	{
		ULONG count = cb-n;
		if (blockpos+count > m_pManager->m_blocksize)
		{
			count = m_pManager->m_blocksize - blockpos;
		}

		m_pManager->ReadFromBlock(m_blocks[nblock], pb, blockpos, count);

		n += count;
		pb += count;
		blockpos = 0;
		nblock++;
	}

	return n;
}

ULONG Buffer::Write(const void* pv, ULONGLONG pos, ULONG cb)
{
	int nblock = 0;
	ULONGLONG blockpos =  pos;

	while (blockpos >= m_pManager->m_blocksize)
	{
		blockpos -= m_pManager->m_blocksize;
		nblock++;
	}

	uint8* pb = (uint8*)pv;

	ULONGLONG n = 0;
	while (n < cb)
	{
		ULONG count = cb-n;
		if (blockpos+count > m_pManager->m_blocksize)
		{
			count = m_pManager->m_blocksize - blockpos;
		}

		if (GetSize() < m_pManager->m_blocksize*nblock+count)
		{
			SetSize(m_pManager->m_blocksize*nblock+count);
		}
		/*
		Block* prevblock;
		if (m_blocks.size())
			prevblock = m_blocks[m_blocks.size()-1];
		else
			prevblock = NULL;

		while (nblock >= m_blocks.size())
		{
			Block* block = m_pManager->AllocateBlock();

			block->prev2 = prevblock;
			if (prevblock) prevblock->next2 = block;

			m_blocks.push_back(block);

			prevblock = block;
		}
		*/

		m_pManager->WriteToBlock(m_blocks[nblock], pb, blockpos, count);

		n += count;
		pb += count;
		blockpos = 0;
		nblock++;
	}

	return n;
}

void Buffer::SetSize(ULONGLONG size)
{
	Block* prevblock;
	if (m_blocks.GetSize())
		prevblock = m_blocks[m_blocks.GetSize()-1];
	else
		prevblock = NULL;

	ULONGLONG size2 = m_blocks.GetSize() * m_pManager->m_blocksize;

	while (m_blocks.GetSize() == 0 || (size2 < size))
	{
		Block* block = m_pManager->AllocateBlock();

		block->prev2 = prevblock;
		if (prevblock) prevblock->next2 = block;

		if (prevblock) m_pManager->WriteBlockHeader(prevblock);
		m_pManager->WriteBlockHeader(block);

		m_blocks.Add(block);

		prevblock = block;
		size2 += m_pManager->m_blocksize;
	}

	//m_size = size;
}

BufferManager::BufferManager(const char* filename, const char* accessmode)
{
	//m_fp = fopen(filename, accessmode);

	m_actualBlockSize = 256;
	m_blocksize = m_actualBlockSize-16;

	m_totalsize = 0;

	m_firstFree = NULL;
	m_lastFree = NULL;

	m_firstUsed = NULL;
	m_lastUsed = NULL;

	/*
	if (std::string(accessmode).find('a') != -1)
	{
		m_fp = CreateFile(filename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, 0, NULL);
	}
	else
		*/
	{
		m_fp = CreateFileA(filename, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, 0, NULL);

		if (GetFileSize(m_fp, NULL) == 0)
		{
			m_sysBuffer = _AllocateBufferAtAddress(0);

			m_nbuffers = 0;
			m_sysBuffer->Write(&m_nbuffers, 0, 8);
		}
		else
		{
			m_sysBuffer = _OpenBufferAtAddress(0);

			m_sysBuffer->Read(&m_nbuffers, 0, 8);

			m_totalsize = GetFileSize(m_fp, NULL);
		}
	}
}

void BufferManager::WriteBlockHeader(Block* block)
{
	ULONGLONG fpos = block->m_filepos;
	LONG low = fpos & 0xffffffff;
	LONG high = fpos>>32;

	SetFilePointer(m_fp, low, &high, NULL);

	ULONG nWritten;

	LONGLONG nextid2 = block->next2? block->next2->m_filepos: 0;
	LONGLONG previd2 = block->prev2? block->prev2->m_filepos: 0;

	WriteFile(m_fp, &previd2, 8, &nWritten, NULL);
	WriteFile(m_fp, &nextid2, 8, &nWritten, NULL);
}

ULONG BufferManager::ReadFromBlock(Block* block, void* pv, ULONG pos, ULONG cb)
{
	ASSERT(pos+cb <= m_blocksize);

	ULONGLONG fpos = block->m_filepos+pos + 16;
	LONG low = fpos & 0xffffffff;
	LONG high = fpos>>32;

	SetFilePointer(m_fp, low, &high, NULL);

	ULONG nRead;
	ReadFile(m_fp, pv, cb, &nRead, NULL);
	return nRead;
}

ULONG BufferManager::WriteToBlock(Block* block, const void* pv, ULONG pos, ULONG cb)
{
	ASSERT(pos+cb <= m_blocksize);
//	fseek(m_fp, block->m_filepos+pos, SEEK_SET);
	ULONGLONG fpos = block->m_filepos+pos + 16;
	LONG low = fpos & 0xffffffff;
	LONG high = fpos>>32;

//	fsetpos(m_fp, &fpos);
//	fwrite(pv, cb, 1, m_fp);

	SetFilePointer(m_fp, low, &high, NULL);

	ULONG nWritten;
	WriteFile(m_fp, pv, cb, &nWritten, NULL);
	return nWritten;
}

Block* BufferManager::AllocateBlock()
{
	if (m_firstFree == NULL)
	{
		m_firstFree = new Block;
	//	fseek(m_fp, 0, SEEK_END);
		m_firstFree->m_filepos = m_totalsize;

		m_totalsize += m_actualBlockSize;

		m_lastFree = m_firstFree;
	}

	// Get the first free block
	Block* block = m_firstFree;

	// Remove it from the free list

	/*
	Node* previous = oldChild->get_previousSibling();
	Node* next = oldChild->get_nextSibling();

	if (previous != NULL)
		previous->put_nextSibling(next);
	else
		m_firstChild = next;

	if (next != NULL)
		next->put_previousSibling(previous);
	else
		m_lastChild = previous;

	oldChild->put_previousSibling(NULL);
	oldChild->put_nextSibling(NULL);
	*/

	if (block->prev)
		block->prev->next = block->next;
	else
		m_firstFree = block->prev;

	if (block->next)
		block->next->prev = block->prev;
	else
		m_lastFree = block->next;

	// Insert it into the used list
	if (m_firstUsed)
	{
		if (m_firstUsed->next)
			m_firstUsed->next->prev = block;
	}

	if (m_lastUsed == NULL) m_lastUsed = block;

	block->prev = NULL;
	block->next = m_firstUsed;
	m_firstUsed = block;

	return block;
}

void BufferManager::FreeBlock(Block* useblock)
{
	ASSERT(0);
}

Buffer* BufferManager::_OpenBuffer(ULONGLONG identity)
{
	ASSERT(identity > 0);

	if (identity-1 >= m_nbuffers)
		return NULL;

	ULONGLONG address;
	m_sysBuffer->Read(&address, 8+(identity-1)*8, 8);

	return _OpenBufferAtAddress(address);
}

Buffer* BufferManager::_OpenBufferAtAddress(ULONGLONG address)
{
	Buffer* pBuffer = new Buffer;
	pBuffer->m_pManager = this;

	Block* prevblock = NULL;
	do
	{
		Block* block = new Block;
		block->m_filepos = address;

		if (prevblock)
			prevblock->next2 = block;

		block->prev2 = block;
		prevblock = block;

		pBuffer->m_blocks.Add(block);

		SetFilePointer(m_fp, address+8, NULL, NULL);
		
		ULONG nRead;
		ReadFile(m_fp, &address, 8, &nRead, NULL);
	}
	while (address);

	return pBuffer;
}

Buffer* BufferManager::_AllocateBufferAtAddress(ULONGLONG size)
{
	Buffer* pBuffer = new Buffer;
	pBuffer->m_pManager = this;

	pBuffer->SetSize(size);

	return pBuffer;
}

Buffer* BufferManager::_AllocateBuffer(ULONGLONG size)
{
	Buffer* pBuffer = new Buffer;
	pBuffer->m_pManager = this;

	pBuffer->SetSize(size);

	pBuffer->m_index = ++m_nbuffers;
	m_sysBuffer->Write(&m_nbuffers, 0, 8);
	m_sysBuffer->Write(&pBuffer->m_blocks[0]->m_filepos, 8+(pBuffer->m_index-1)*8, 8);

	/*
	Block* prevblock = NULL;
	ULONG n = 0;
	do
	{
		Block* block = AllocateBlock();

		block->prev2 = prevblock;
		if (prevblock) prevblock->next2 = block;

		p->m_blocks.push_back(block);
		n += m_blocksize;

		prevblock = block;
	}
	while (n < size);
	*/

	return pBuffer;
}

void BufferManager::_FreeBuffer(Buffer* buffer)
{
	for (int i = 0; i < buffer->m_blocks.GetSize(); i++)
	{
		FreeBlock(buffer->m_blocks[i]);
	}
	delete buffer;
}

IBuffer* BufferManager::GetSysBuffer()
{
	return m_sysBuffer;
}

IBuffer* BufferManager::OpenBuffer(ULONGLONG identity)
{
	return _OpenBuffer(identity);
}

IBuffer* BufferManager::AllocateBuffer(ULONGLONG size)
{
	return _AllocateBuffer(size);
}

void BufferManager::FreeBuffer(IBuffer* buffer)
{
	Buffer* pBuffer = dynamic_cast<Buffer*>(buffer);
	if (pBuffer == NULL)
	{
		ASSERT(0);
		THROW(-1);
	}

	FreeBuffer(pBuffer);
}

}
