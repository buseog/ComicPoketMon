#include "stdafx.h"
#include "InsideCamera.h"

CInsideCamera::CInsideCamera(LPDIRECT3DDEVICE9 pDevice)
: CBasicCamera(pDevice)
, m_pTimeMgr(Engine::Get_TimeMgr())
, m_pInfoSubject(Engine::Get_InfoSubject())
, m_pTargetInfo(NULL)
, m_fCameraSpeed(0.f)
, m_fTargetDistance(0.f)
, m_fCameraDistance(0.f)
, m_fAngle(0.f)
, m_fAngleY(0.f)
, m_fMaxDitance(0.f)
, m_fNearDist(2.f)
, m_fFarDist(50.f)
, m_bRbuttonDown(false)
, m_bKeyInput(false)
, m_iKeyDown(0)
{

}

CInsideCamera::~CInsideCamera(void)
{

}

CInsideCamera* CInsideCamera::Create(LPDIRECT3DDEVICE9 pDevice, 
									 const Engine::CTransform* pTargetInfo)
{
	CInsideCamera*		pCamera = new CInsideCamera(pDevice);

	if(FAILED(pCamera->Initialize()))
		Engine::Safe_Delete(pCamera);

	pCamera->SetCameraTarget(pTargetInfo);
	pCamera->SetProjectionMatrix(D3DXToRadian(45.f), float(WINCX) / WINCY, 0.1f, 1000.f);

	return pCamera;
}

void CInsideCamera::SetCameraTarget(const Engine::CTransform* pTargetInfo)
{
	m_pTargetInfo = pTargetInfo;
}

HRESULT CInsideCamera::Initialize(void)
{
	m_ptOriginPos.x = 0;
	m_ptOriginPos.y = 0;
	m_fCameraSpeed		= 0.f;
	m_fTargetDistance	= 30.f;
	m_fCameraDistance	= 00.f;
	m_fAngle			= D3DXToRadian(30.f);
	m_fAngleY			= 0.f;

	m_pInfoSubject->AddData(D3DTS_VIEW, &m_matView);
	m_pInfoSubject->AddData(D3DTS_PROJECTION, &m_matProj);

	return S_OK;
}

void CInsideCamera::Update(void)
{
	if (m_eCamType != CAM_INSIDE)
		return;

	TargetRenewal();
	m_pInfoSubject->Notify(D3DTS_VIEW, &m_matView);
	m_pInfoSubject->Notify(D3DTS_PROJECTION, &m_matProj);
}

void CInsideCamera::TargetRenewal( void )
{
	float		fTime = m_pTimeMgr->GetTime();

	m_vEye = m_pTargetInfo->vDir * (-1);
	D3DXVec3Normalize(&m_vEye, &m_vEye);

	D3DXVECTOR3		vRight, vUp;
	memcpy(&vRight, &m_pTargetInfo->matWorld.m[0][0], sizeof(float) * 3);
	memcpy(&vUp, &m_pTargetInfo->matWorld.m[1][0], sizeof(float) * 3);

	D3DXMATRIX		matRotAxis;
	D3DXMatrixRotationAxis(&matRotAxis, &vRight, m_fAngle);
	D3DXVec3TransformNormal(&m_vEye, &m_vEye, &matRotAxis);

	D3DXMatrixRotationAxis(&matRotAxis, &vUp, m_fAngleY);
	D3DXVec3TransformNormal(&m_vEye, &m_vEye, &matRotAxis);

	m_fCameraDistance = m_fTargetDistance + m_fMaxDitance;

	if(m_fCameraDistance < m_fNearDist)
		m_fCameraDistance += m_fNearDist - m_fCameraDistance;

	if(m_fCameraDistance > m_fNearDist)
		m_fCameraDistance += m_fCameraDistance - m_fNearDist;

	m_vEye *= m_fCameraDistance;

	m_vEye += m_pTargetInfo->vPos;
	m_vAt = m_pTargetInfo->vPos;

	CCamera::SetViewSpaceMatrix(&m_vEye, &m_vAt, &D3DXVECTOR3(0.f, 1.f, 0.f));

}

