#include "StdAfx.h"
#include "Graphics.h"

#include <d3d9.h>
#include <D3dx9math.h>

namespace System
{
namespace Graphics
{

VertexDeclarationGL::VertexDeclarationGL() :
	m_refcount(0),
	m_elements(NULL)
{
}

VertexDeclarationGL::~VertexDeclarationGL()
{
	delete[] m_elements;
}

ULONG VertexDeclarationGL::Release()
{
	VERIFY(m_refcount > 0);
	--m_refcount;
	if (m_refcount == 0)
	{
		delete this;
		return 0;
	}
	return m_refcount;
}

}
}
