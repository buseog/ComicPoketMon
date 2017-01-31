#include "StatSubject.h"

IMPLEMENT_SINGLETON(Engine::CStatSubject)

Engine::CStatSubject::CStatSubject(void)
{

}

Engine::CStatSubject::~CStatSubject(void)
{
	Release();
}

Engine::VECDATA* Engine::CStatSubject::GetDataList(int iMessage)
{
	MAPDATALIST::iterator	iter = m_MapDataList.find(iMessage);

	if(iter == m_MapDataList.end())
		return NULL;

	return &iter->second;
}

void Engine::CStatSubject::AddData(int iMessage, void* pData)
{
	if(pData)
	{
		MAPDATALIST::iterator	iter = m_MapDataList.find(iMessage);

		if(iter == m_MapDataList.end())
		{
			m_MapDataList[iMessage] = VECDATA();
		}

		m_MapDataList[iMessage].push_back(pData);
		Notify(iMessage, pData);
	}
}


void Engine::CStatSubject::RemoveData(int iMessage, void* pData)
{	
	MAPDATALIST::iterator	mapiter = m_MapDataList.find(iMessage);

	if(mapiter != m_MapDataList.end())
	{
		VECDATA::iterator		iterList = mapiter->second.begin();
		VECDATA::iterator		iterList_end = mapiter->second.end();

		for( ;iterList != iterList_end; ++iterList)
		{
			if((*iterList) == pData)
			{
				mapiter->second.erase(iterList);
				return;
			}
		}
	}
}

void Engine::CStatSubject::Release(void)
{
	for(MAPDATALIST::iterator	iter = m_MapDataList.begin();
		iter != m_MapDataList.end(); ++iter)
	{
		iter->second.clear();
	}
	m_MapDataList.clear();
}

