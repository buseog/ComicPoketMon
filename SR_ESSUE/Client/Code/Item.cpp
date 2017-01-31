#include "stdafx.h"
#include "Item.h"

#include "Export_Function.h"
#include "ResourceMgr.h"
#include "Texture.h"

CItem::CItem( LPDIRECT3DDEVICE9 pDevice )
: Engine::CUI(pDevice)
, m_pResourceMgr(Engine::Get_ResourceMgr())
, m_pConvertVertex(NULL)
, m_pVertex(NULL)
{

}

CItem::~CItem( void )
{
	Release();
}


HRESULT CItem::Initialize( ITEMID ID )
{
	FAILED_CHECK(AddComponent(ID));

	m_dwVtxCnt			= 4;
	m_pVertex			= new Engine::VTXTEX[m_dwVtxCnt];
	m_pConvertVertex	= new Engine::VTXTEX[m_dwVtxCnt];

	//m_vPos = D3DXVECTOR3(450.f, 250.f, 0.f);
	m_vSize = D3DXVECTOR3(30.f, 30.f, 0.f);

	CUI::SetUI();

	m_eId = ID;

	m_iType = 0;

	m_pResourceMgr->GetVtxInfo(Engine::RESOURCE_STATIC, L"Buffer Item", m_pVertex);
	return S_OK;
}

void CItem::Update( void )
{
	Engine::CGameObject::Update();
	Engine::CUI::Update();
	SetTransform();
}

void CItem::Render( void )
{
	if(m_eId == IT_EMPTY)
		return;

	m_pResourceMgr->SetVtxInfo(Engine::RESOURCE_STATIC, L"Buffer Item", m_pConvertVertex);

	if(m_eId == IT_ITEM)
		m_pTexture->Render(m_iType);
	else if(m_eId == IT_POKETMON)
		m_pTexture->Render(m_iType);

	m_pBuffer->Render();
}

CItem* CItem::Create( LPDIRECT3DDEVICE9 pDevice, ITEMID ID )
{
	CItem* pItem = new CItem(pDevice);

	if (FAILED(pItem->Initialize(ID)))
		Engine::Safe_Delete(pItem);


	return pItem;
}

void CItem::Release( void )
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

void CItem::SetTransform( void )
{
	for(size_t i = 0; i < m_dwVtxCnt; ++i)
	{
		m_pConvertVertex[i] = m_pVertex[i];

		Engine::MyTransformCoord(&m_pConvertVertex[i].vPos, 
			&m_pConvertVertex[i].vPos, 
			&m_matWorld);

		Engine::MyTransformCoord(&m_pConvertVertex[i].vPos, 
			&m_pConvertVertex[i].vPos, 
			&m_matView);

		Engine::MyTransformCoord(&m_pConvertVertex[i].vPos, 
			&m_pConvertVertex[i].vPos, 
			&m_matProj);
	}
}

HRESULT CItem::AddComponent(ITEMID ID)
{
	Engine::CComponent*		pComponent = NULL;

	// Buffer
	pComponent = m_pResourceMgr->CloneResource(Engine::RESOURCE_STATIC, L"Buffer Item");
	m_pBuffer = dynamic_cast<Engine::CVIBuffer*>(pComponent);
	NULL_CHECK_RETURN(m_pBuffer, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Buffer", pComponent));

	//Texture
	switch(ID)
	{
	case IT_ITEM:
		pComponent = m_pResourceMgr->CloneResource(Engine::RESOURCE_STATIC, L"Texture Item");
		m_pTexture = dynamic_cast<Engine::CTexture*>(pComponent);
		NULL_CHECK_RETURN(m_pTexture, E_FAIL);
		m_mapComponent.insert(MAPCOMPONENT::value_type(L"Texture", pComponent));
		break;

	case IT_POKETMON:
		pComponent = m_pResourceMgr->CloneResource(Engine::RESOURCE_STATIC, L"Poketmon icon");
		m_pTexture = dynamic_cast<Engine::CTexture*>(pComponent);
		NULL_CHECK_RETURN(m_pTexture, E_FAIL);
		m_mapComponent.insert(MAPCOMPONENT::value_type(L"Texture", pComponent));
		break;

	}

	return S_OK;
}

void CItem::SetPos(float fX, float fY)
{
	m_vPos.x = fX;
	m_vPos.y = fY;
}

ITEMID	CItem::GetId(void)
{
	return m_eId;
}

void CItem::SetType( int Type )
{
	m_iType = Type;
}

int CItem::GetType( void )
{
	return m_iType;
}
