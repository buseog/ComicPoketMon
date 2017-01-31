#include "StdAfx.h"
#include "EarthCamera.h"


CEarthCamera::CEarthCamera( LPDIRECT3DDEVICE9 pDevice )
: CBasicCamera(pDevice)
, m_pTimeMgr(Engine::Get_TimeMgr())
, m_pInfoSubject(Engine::Get_InfoSubject())
, m_fTime(0.f)
, m_fSwing(0.5f)
{

}

CEarthCamera::~CEarthCamera( void )
{
	
}

HRESULT CEarthCamera::Initialize( void )
{
	m_fTime = 5.7f;

	m_pInfoSubject->AddData(D3DTS_VIEW, &m_matView);
	m_pInfoSubject->AddData(D3DTS_PROJECTION, &m_matProj);

	return S_OK;
}

void CEarthCamera::Update( void )
{
	if (m_eCamType != CAM_EARTH)
		return;

	m_fTime -= m_pTimeMgr->GetTime();

	if (m_fTime < 0.f)
	{
		m_bDestroy = true;
		CBasicCamera::m_eCamType = CAM_STATIC;
	}

	TargetRenewal();

	m_pInfoSubject->Notify(D3DTS_VIEW, &m_matView);
	m_pInfoSubject->Notify(D3DTS_PROJECTION, &m_matProj);
}

CEarthCamera* CEarthCamera::Create( LPDIRECT3DDEVICE9 pDevice, Engine::CTransform* pTargetInfo )
{
	CEarthCamera*		pCamera = new CEarthCamera(pDevice);

	if(FAILED(pCamera->Initialize()))
		Engine::Safe_Delete(pCamera);

	pCamera->SetCameraTarget(pTargetInfo);
	pCamera->SetProjectionMatrix(D3DXToRadian(45.f), float(WINCX) / WINCY, 0.1f, 1000.f);

	return pCamera;
}

void CEarthCamera::SetCameraTarget( Engine::CTransform* pTargetInfo )
{
	m_pTargetInfo = pTargetInfo;
}

void CEarthCamera::TargetRenewal( void )
{
	D3DXVECTOR3		vRight;
	memcpy(&vRight, &m_pTargetInfo->matWorld.m[0][0], sizeof(float) * 3);
	Engine::MyNormalize(&vRight, &vRight);


	if (m_fTime < 0.7f)
	{
		m_fSwing *= -1.f;

		m_vEye = m_pTargetInfo->vPos + (vRight * 3.f);
		m_vAt = m_vEye + (vRight * m_fSwing);
		m_vEye.y += 60.f;

	}
	else
	{
		m_vEye = m_pTargetInfo->vPos + vRight;
		m_vAt = m_vEye;
		m_vEye.y += 60.f;
	}
	
	
	CCamera::SetViewSpaceMatrix(&m_vEye, &m_vAt, &D3DXVECTOR3(0.f, 0.f, 1.f));
}
