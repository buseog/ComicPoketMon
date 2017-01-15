#include "stdafx.h"
#include "StaticCamera.h"

#include "Export_Function.h"
#include "Transform.h"
#include "TimeMgr.h"
#include "Include.h"
#include "InfoSubject.h"

CStaticCamera::CStaticCamera(LPDIRECT3DDEVICE9 pDevice)
: CCamera(pDevice)
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
{

}

CStaticCamera::~CStaticCamera(void)
{

}

CStaticCamera* CStaticCamera::Create(LPDIRECT3DDEVICE9 pDevice, 
									 const Engine::CTransform* pTargetInfo)
{
	CStaticCamera*		pCamera = new CStaticCamera(pDevice);

	if(FAILED(pCamera->Initialize()))
		Engine::Safe_Delete(pCamera);

	pCamera->SetCameraTarget(pTargetInfo);
	pCamera->SetProjectionMatrix(D3DXToRadian(45.f), float(WINCX) / WINCY, 1.f, 1000.f);

	return pCamera;
}

void CStaticCamera::SetCameraTarget(const Engine::CTransform* pTargetInfo)
{
	m_pTargetInfo = pTargetInfo;
}

HRESULT CStaticCamera::Initialize(void)
{
	m_ptOriginPos.x = 0;
	m_ptOriginPos.y = 0;
	m_fCameraSpeed		= 0.f;
	m_fTargetDistance	= 10.f;
	m_fCameraDistance	= 0.f;
	m_fAngle			= D3DXToRadian(30.f);
	m_fAngleY			= 0.f;

	m_pInfoSubject->AddData(D3DTS_VIEW, &m_matView);
	m_pInfoSubject->AddData(D3DTS_PROJECTION, &m_matProj);

	return S_OK;
}

void CStaticCamera::Update(void)
{
	KeyCheck();
	TargetRenewal();

	m_pInfoSubject->Notify(D3DTS_VIEW);
	m_pInfoSubject->Notify(D3DTS_PROJECTION);

}

void CStaticCamera::KeyCheck(void)
{
	float		fTime = m_pTimeMgr->GetTime();

	if(GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_fAngle += D3DXToRadian(45.f) * fTime;
	}

	if(GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_fAngle -= D3DXToRadian(45.f) * fTime;
	}

	if(GetAsyncKeyState('O') & 0x8000)
	{
		m_fTargetDistance += fTime * 20.f;
	}

	if(GetAsyncKeyState('P') & 0x8000)
	{
		m_fTargetDistance -= fTime * 20.f;
	}

	if(m_fMaxDitance - 0.2f > g_fWheelControl)
		m_fMaxDitance -= fTime * 20.f;
	else if(m_fMaxDitance + 0.2f < g_fWheelControl)
		m_fMaxDitance += fTime * 20.f;

	if(g_fWheelControl < (m_fNearDist - m_fTargetDistance))
		g_fWheelControl = (m_fNearDist - m_fTargetDistance);

	if(g_fWheelControl > (m_fFarDist - m_fTargetDistance))
		g_fWheelControl = (m_fFarDist - m_fTargetDistance);

	if(GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		if(m_bRbuttonDown)
			return;

		m_ptOriginPos = GetMousePos();
		m_bRbuttonDown = true;
	}
	else
	{
		m_bRbuttonDown = false;
	}

}

void CStaticCamera::TargetRenewal(void)
{
	float		fTime = m_pTimeMgr->GetTime();

	m_vEye = m_pTargetInfo->vDir * (-1);
	D3DXVec3Normalize(&m_vEye, &m_vEye);

	// 카메라 앵글각도 카메라에서부터 시작하는게 좋을꺼같음
	if(m_bRbuttonDown)
	{
		m_fAngle -= D3DXToRadian(m_ptOriginPos.y - GetMousePos().y) * (fTime * 5.f);
		m_fAngleY -= D3DXToRadian(m_ptOriginPos.x - GetMousePos().x) * (fTime * 5.f);
		SetCursorPos(m_ptOriginPos.x, m_ptOriginPos.y);
		
	}
	else
	{
		if(m_fAngleY < 0.f)
			m_fAngleY += ((0.f - m_fAngleY) + 0.3f) * fTime;
		if(m_fAngleY > 0.f)
			m_fAngleY -= ((m_fAngleY - 0.f) + 0.3f) * fTime;
	}

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

POINT CStaticCamera::GetMousePos(void)
{
	POINT	pt;

	GetCursorPos(&pt);

	return pt;
}