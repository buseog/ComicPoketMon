#include "Camera.h"
#include "Pipeline.h"

Engine::CCamera::CCamera(LPDIRECT3DDEVICE9 pDevice)
: CGameObject(pDevice)
, m_vEye(0.f, 0.f, 0.f)
, m_vAt(0.f, 0.f, 0.f)
, m_vUp(0.f, 1.f, 0.f)
{
	D3DXMatrixIdentity(&m_matView);
	D3DXMatrixIdentity(&m_matProj);
}

Engine::CCamera::~CCamera(void)
{

}

void Engine::CCamera::SetViewSpaceMatrix(const D3DXVECTOR3* pEye, const D3DXVECTOR3* pAt, const D3DXVECTOR3* pUp)
{	
	CPipeline::MakeViewSpaceMatrix(&m_matView, pEye, pAt, pUp);
}

void Engine::CCamera::SetProjectionMatrix(const float& fFovY, const float& fAspect, const float& fNear, const float& fFar)
{
	CPipeline::MakeProjectionMatrix(&m_matProj, fFovY, fAspect, fNear, fFar);
}

D3DXMATRIX Engine::CCamera::GetView(void)
{
	return m_matView;
}

D3DXMATRIX Engine::CCamera::GetProj(void)
{
	return m_matProj;
}

