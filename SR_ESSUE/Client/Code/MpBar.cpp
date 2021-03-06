#include "StdAfx.h"
#include "MpBar.h"

#include "Export_Function.h"
#include "ResourceMgr.h"
#include "Include.h"
#include "Texture.h"

CMpBar::CMpBar( LPDIRECT3DDEVICE9 pDevice )
: Engine::CUI(pDevice)
, m_pResourceMgr(Engine::Get_ResourceMgr())
, m_pConvertVertex(NULL)
, m_pVertex(NULL)
{

}

CMpBar::~CMpBar( void )
{
	Release();
}

HRESULT CMpBar::Initialize( void )
{
	FAILED_CHECK(AddComponent());

	m_dwVtxCnt			= 4;
	m_pVertex			= new Engine::VTXTEX[m_dwVtxCnt];
	m_pConvertVertex	= new Engine::VTXTEX[m_dwVtxCnt];

	m_vPos = D3DXVECTOR3(90.f, 570.f, 0.f);
	m_vSize = D3DXVECTOR3(180.f, 40.f, 0.f);

	CUI::SetUI();

	m_pResourceMgr->GetVtxInfo(Engine::RESOURCE_STATIC, L"Buffer MpBar", m_pVertex);


	return S_OK;
}

void CMpBar::Update( void )
{
	Engine::CGameObject::Update();
	Engine::CUI::Update();
	SetTransform();
}

void CMpBar::Render( void )
{
	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	m_pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
	m_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	m_pResourceMgr->SetVtxInfo(Engine::RESOURCE_STATIC, L"Buffer MpBar", m_pConvertVertex);

	m_pTexture->Render(0);
	m_pBuffer->Render();

	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

void CMpBar::Release( void )
{
	if(m_pVertex)
	{
		Engine::Safe_Delete_Array(m_pVertex);
	}

	if(m_pConvertVertex)
	{
		Engine::Safe_Delete_Array(m_pConvertVertex);
	}
}

HRESULT CMpBar::AddComponent( void )
{
	Engine::CComponent*		pComponent = NULL;

	// Buffer
	pComponent = m_pResourceMgr->CloneResource(Engine::RESOURCE_STATIC, L"Buffer MpBar");
	m_pBuffer = dynamic_cast<Engine::CVIBuffer*>(pComponent);
	NULL_CHECK_RETURN(m_pBuffer, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Buffer", pComponent));

	//Texture
	pComponent = m_pResourceMgr->CloneResource(Engine::RESOURCE_STATIC, L"Texture MpBar");
	m_pTexture = dynamic_cast<Engine::CTexture*>(pComponent);
	NULL_CHECK_RETURN(m_pTexture, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Texture", pComponent));

	return S_OK;
}

CMpBar* CMpBar::Create( LPDIRECT3DDEVICE9 pDevice )
{
	CMpBar* pMpbar = new CMpBar(pDevice);

	if (FAILED(pMpbar->Initialize()))
		Engine::Safe_Delete(pMpbar);

	return pMpbar;
}

void CMpBar::SetTransform( void )
{
	D3DXMATRIX matPrint = m_matWorld * m_matView * m_matProj;

	for(size_t i = 0; i < m_dwVtxCnt; ++i)
	{
		m_pConvertVertex[i] = m_pVertex[i];

		Engine::MyTransformCoord(&m_pConvertVertex[i].vPos, 
			&m_pConvertVertex[i].vPos, 
			&matPrint);
	}
}
