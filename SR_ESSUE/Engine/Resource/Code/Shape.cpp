#include "Shape.h"
#include "VIBuffer.h"


Engine::CShape::CShape( LPDIRECT3DDEVICE9 pDevice )
: m_pDevice(pDevice)
, m_pwRefCnt(new WORD(0))
{

}

Engine::CShape::~CShape( void )
{
	Release();
}

void Engine::CShape::Render( void )
{
	MAPSHAPE::iterator		mapiter		= m_mapShape.begin();
	MAPSHAPE::iterator		mapiter_end = m_mapShape.end();

	for( ; mapiter != mapiter_end; ++mapiter)
	{
		BUFFERLIST::iterator		iterList	 = mapiter->second.begin();
		BUFFERLIST::iterator		iterList_end = mapiter->second.end();

		for(; iterList != iterList_end; ++iterList)
		{
			(*iterList)->Render();
		}
	}
}

void Engine::CShape::Release( void )
{
	if((*m_pwRefCnt) == 0)
	{
		Engine::Safe_Delete(m_pwRefCnt);
	}
	else
	{
		--(*m_pwRefCnt);
	}
}

Engine::CShape* Engine::CShape::CloneResource( void )
{
	++(*m_pwRefCnt);

	return new CShape(*this);
}
