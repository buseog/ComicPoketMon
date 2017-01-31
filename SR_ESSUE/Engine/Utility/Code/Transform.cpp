#include "Transform.h"
#include "MathMgr.h"
#include "Pipeline.h"

Engine::CTransform::CTransform(const D3DXVECTOR3& vLook)
: vPos(0.f, 0.f, 0.f)
, vDir(vLook)
, vScale(1.f, 1.f, 1.f)
{
	ZeroMemory(fAngle, sizeof(float) * 3);
	CMathMgr::MyIdentity(&matWorld);
}

Engine::CTransform::~CTransform(void)
{

}

void Engine::CTransform::Update(void)
{
	Engine::CPipeline::MakeWorldMatrix(&matWorld, &vScale, fAngle, &vPos);
}

Engine::CTransform* Engine::CTransform::Create(const D3DXVECTOR3& vLook)
{
	return new CTransform(vLook);
}
