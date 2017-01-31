#include "stdafx.h"
#include "CameraObserver.h"

#include "Export_Function.h"
#include "Include.h"
#include "BasicCamera.h"

CCameraObserver::CCameraObserver(void)
: m_pInfoSubject(Engine::Get_InfoSubject())

{

}

CCameraObserver::~CCameraObserver(void)
{

}

D3DXMATRIX* CCameraObserver::GetView(void)
{
	return &m_matView;
}	

D3DXMATRIX* CCameraObserver::GetProj(void)
{
	return &m_matProj;
}

CCameraObserver* CCameraObserver::Create(void)
{
	return new CCameraObserver;
}

void CCameraObserver::Update(int iMessage, void* pData)
{
	vector<void*>*		pDataList = m_pInfoSubject->GetDataList(iMessage);
	NULL_CHECK(pDataList);

	vector<void*>::iterator iter = find(pDataList->begin(), pDataList->end(), pData);

	switch(iMessage)
	{
	case D3DTS_VIEW:
		m_matView = *((D3DXMATRIX*)(*iter));
		break;

	case D3DTS_PROJECTION:
			m_matProj = *((D3DXMATRIX*)(*iter));
		break;
	}

}

