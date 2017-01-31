#include "StdAfx.h"
#include "Projectile.h"


CProjectile::CProjectile(LPDIRECT3DDEVICE9 pDevice)
: Engine::CGameObject(pDevice)
{

}

CProjectile::~CProjectile(void)
{

}

HRESULT CProjectile::Initialize(void)
{
	return S_OK;
}

void CProjectile::Update(void)
{
	
}

void CProjectile::Render(void)
{

}
