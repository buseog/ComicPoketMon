#include "StdAfx.h"
#include "PoketballUI.h"

#include "Export_Function.h"
#include "ResourceMgr.h"
#include "Include.h"
#include "Texture.h"


CPoketballUI::CPoketballUI( LPDIRECT3DDEVICE9 pDevice )
: Engine::CUI(pDevice)
, m_pResourceMgr(Engine::Get_ResourceMgr())
, m_pConvertVertex(NULL)
, m_pVertex(NULL)
{

}

CPoketballUI::~CPoketballUI( void )
{
	Release();
}

HRESULT CPoketballUI::Initialize( void )
{
	FAILED_CHECK(AddComponent());

	m_dwVtxCnt			= 4;
	m_pVertex			= new Engine::VTXTEX[m_dwVtxCnt];
	m_pConvertVertex	= new Engine::VTXTEX[m_dwVtxCnt];

	m_vSize = D3DXVECTOR3(50.f, 50.f, 0.f);

	CUI::SetUI();

	m_pResourceMgr->GetVtxInfo(Engine::RESOURCE_STATIC, L"Buffer HpBar", m_pVertex);


	return S_OK;
}

void CPoketballUI::Update( void )
{
	Engine::CGameObject::Update();
	Engine::CUI::Update();
	SetTransform();
}

void CPoketballUI::Render( void )
{
	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	m_pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
	m_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	m_pResourceMgr->SetVtxInfo(Engine::RESOURCE_STATIC, L"Buffer HpBar", m_pConvertVertex);

	m_pTexture->Render(0);
	m_pBuffer->Render();

	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

void CPoketballUI::Release( void )
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

HRESULT CPoketballUI::AddComponent( void )
{
	Engine::CComponent*		pComponent = NULL;

	// Buffer
	pComponent = m_pResourceMgr->CloneResource(Engine::RESOURCE_STATIC, L"Buffer HpBar");
	m_pBuffer = dynamic_cast<Engine::CVIBuffer*>(pComponent);
	NULL_CHECK_RETURN(m_pBuffer, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Buffer", pComponent));

	//Texture
	pComponent = m_pResourceMgr->CloneResource(Engine::RESOURCE_STATIC, L"PoketballUI icon");
	m_pTexture = dynamic_cast<Engine::CTexture*>(pComponent);
	NULL_CHECK_RETURN(m_pTexture, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Texture", pComponent));

	return S_OK;
}

CPoketballUI* CPoketballUI::Create( LPDIRECT3DDEVICE9 pDevice )
{
	CPoketballUI* pMpbar = new CPoketballUI(pDevice);

	if (FAILED(pMpbar->Initialize()))
		Engine::Safe_Delete(pMpbar);

	return pMpbar;
}

void CPoketballUI::SetTransform( void )
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

void CPoketballUI::SetPos( D3DXVECTOR3 vPos )
{
	m_vPos = vPos;
}
