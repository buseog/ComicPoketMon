#include "InfoSubject.h"

IMPLEMENT_SINGLETON(Engine::CInfoSubject)

Engine::CInfoSubject::CInfoSubject(void)
{

}

Engine::CInfoSubject::~CInfoSubject(void)
{
	Release();
}

Engine::VECDATA* Engine::CInfoSubject::GetDataList(int iMessage)
{
	MAPDATALIST::iterator	iter = m_MapDataList.find(iMessage);

	if(iter == m_MapDataList.end())
		return NULL;

	return &iter->second;
}

void Engine::CInfoSubject::AddData(int iMessage, void* pData)
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


void Engine::CInfoSubject::RemoveData(int iMessage, void* pData)
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

void Engine::CInfoSubject::Release(void)
{
	for(MAPDATALIST::iterator	iter = m_MapDataList.begin();
		iter != m_MapDataList.end(); ++iter)
	{
		iter->second.clear();
	}
	m_MapDataList.clear();
}

