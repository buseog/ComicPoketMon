#include "StdAfx.h"
#include "UIObserver.h"

#include "Export_Function.h"
#include "Include.h"

CUIObserver::CUIObserver(void)
: m_pStatusSubject(Engine::Get_StatSubject())
, m_pStatus(NULL)
{
}

CUIObserver::~CUIObserver(void)
{
}

void CUIObserver::Update( int iMessage ,void* pData)
{
	vector<void*>*		pDataList = m_pStatusSubject->GetDataList(iMessage);
	NULL_CHECK(pDataList);

	switch(iMessage)
	{
	case DT_STATUS:
		m_pStatus = ((Engine::CStatus*)pDataList->front());
		break;

	case DT_MATRIX:
		m_pStatus = ((Engine::CStatus*)pDataList->front());
		break;
	}
}

CUIObserver* CUIObserver::Create( void )
{
	return new CUIObserver;
}

Engine::CStatus* CUIObserver::GetStatus( void )
{
	return m_pStatus;
}
