#include "Transform.h"
#include "MathMgr.h"
#include "Pipeline.h"

Engine::CTransform::CTransform(const D3DXVECTOR3& vLook)
: vPos(0.f, 0.f, 0.f)
, vDir(vLook)
{
	ZeroMemory(fAngle, sizeof(float) * 3);
	CMathMgr::MyIdentity(&matWorld);
}

Engine::CTransform::~CTransform(void)
{

}

void Engine::CTransform::Update(void)
{
	Engine::CPipeline::MakeWorldMatrix(&matWorld, &D3DXVECTOR3(1.f, 1.f, 1.f), fAngle, &vPos);
}

Engine::CTransform* Engine::CTransform::Create(const D3DXVECTOR3& vLook)
{
	return new CTransform(vLook);
}
