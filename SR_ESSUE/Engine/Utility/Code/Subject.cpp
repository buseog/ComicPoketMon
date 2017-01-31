#include "Subject.h"
#include "Observer.h"

Engine::CSubject::CSubject(void)
{

}

Engine::CSubject::~CSubject(void)
{
	Release();
}

void Engine::CSubject::Subscribe(CObserver* pObserver)
{
	NULL_CHECK(pObserver);

	m_ObserverList.push_back(pObserver);
}

void Engine::CSubject::UnSubscribe(CObserver* pObserver)
{
	if (m_ObserverList.empty())
		return;

	OBSERVERLIST::iterator		iter		= m_ObserverList.begin();
	OBSERVERLIST::iterator		iter_end	= m_ObserverList.end();

	for( ; iter != iter_end; )
	{
		if((*iter) == pObserver)
		{
			iter = m_ObserverList.erase(iter);
			return;
		}
		else
			++iter;
	}
}

void Engine::CSubject::Notify(int iMessage, void* pData)
{
	OBSERVERLIST::iterator		iter		= m_ObserverList.begin();
	OBSERVERLIST::iterator		iter_end	= m_ObserverList.end();

	for( ; iter != iter_end; ++iter)
	{
		(*iter)->Update(iMessage, pData);
	}
}

void Engine::CSubject::Release(void)
{
	m_ObserverList.clear();
}

