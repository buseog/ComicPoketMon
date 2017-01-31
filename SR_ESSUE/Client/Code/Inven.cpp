#include "stdafx.h"
#include "Inven.h"

#include "Export_Function.h"
#include "ResourceMgr.h"
#include "Include.h"
#include "Texture.h"
#include "Transform.h"
#include "Pipeline.h"
#include "CameraObserver.h"
#include "InfoSubject.h"
#include "CollisionMgr.h"
#include "MouseCol.h"
#include "Item.h"
#include "Player.h"

CInven::CInven(LPDIRECT3DDEVICE9 pDevice)
: Engine::CUI(pDevice)
, m_pResourceMgr(Engine::Get_ResourceMgr())
, m_pCollisionMgr(CCollisionMgr::GetInstance())
, m_pKeyMgr(Engine::Get_KeyMgr())
, m_pConvertVertex(NULL)
, m_pVertex(NULL)
, m_pMouseCol(NULL)
, m_bOnOff(true)
, m_pTempItem(NULL)
, m_pWeapon(NULL)
{

}

CInven::~CInven(void)
{
	Release();
}	

HRESULT CInven::Initialize(void)
{
	FAILED_CHECK(AddComponent());

	m_dwVtxCnt			= 4;
	m_pVertex			= new Engine::VTXTEX[m_dwVtxCnt];
	m_pConvertVertex	= new Engine::VTXTEX[m_dwVtxCnt];

	m_vPos = D3DXVECTOR3(450.f, 250.f, 0.f);
	m_vSize = D3DXVECTOR3(350.f, 350.f, 0.f);

	CUI::SetUI();

	m_pResourceMgr->GetVtxInfo(Engine::RESOURCE_STATIC, L"Buffer Inven", m_pVertex);

	for(int i = 0; i < 27; ++i)
	{
		m_pItem.push_back(CItem::Create(m_pDevice, IT_EMPTY));

		if(i < 9)
			m_pPoketmon.push_back(CItem::Create(m_pDevice, IT_EMPTY));
	}
	m_pWeapon = CItem::Create(m_pDevice, IT_EMPTY);
	m_pPoket = CItem::Create(m_pDevice, IT_EMPTY);
	return S_OK;
}

CInven*	CInven::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CInven*			pInven = new CInven(pDevice);

	if(FAILED(pInven->Initialize()))
		Engine::Safe_Delete(pInven);

	return pInven;
}
void CInven::Update(void)
{


	KeyInput();

	if(m_bOnOff)
		return;

	Engine::CGameObject::Update();
	Engine::CUI::Update();
	SetTransform();

	if(m_pTempItem != NULL)
	{
		POINT	ptMouse;

		GetCursorPos(&ptMouse);
		ScreenToClient(g_hWnd, &ptMouse);
		m_pTempItem->SetPos((float)ptMouse.x, (float)ptMouse.y);
		m_pTempItem->Update();
	}

	float fX = m_vPos.x - 143.f;
	float fY = m_vPos.y + 23.f;

	for(int i = 0; i < 3; ++i)
	{
		for(int j = 0; j < 9; ++j)
		{

			m_pItem[i*9+j]->SetPos(fX + (j * 36.f), fY + (i * 36.f));
		}
	}
	for(int i = 0; i < 9; ++i)
	{
		m_pPoketmon[i]->SetPos(fX + (i * 36.f), fY + 10.f + (3 * 36.f));
	}

	for(size_t i = 0; i < 27; ++i)
	{
		m_pItem[i]->Update();

		if(i < 9)
			m_pPoketmon[i]->Update();
	}

	m_pWeapon->SetPos(fX, fY - 57.f);
	m_pWeapon->Update();

	m_pPoket->SetPos(fX, fY - 93.f);
	m_pPoket->Update();

}
void CInven::Render(void)
{
	if(m_bOnOff)
		return;

	m_pResourceMgr->SetVtxInfo(Engine::RESOURCE_STATIC, L"Buffer Inven", m_pConvertVertex);

	m_pTexture->Render(0);
	m_pBuffer->Render();

	for(size_t i = 0; i < 27; ++i)
	{
		m_pItem[i]->Render();

		if(i < 9)
			m_pPoketmon[i]->Render();
	}

	if(m_pTempItem != NULL)
		m_pTempItem->Render();

	m_pWeapon->Render();
	m_pPoket->Render();

}
void CInven::Release(void)
{
	if(m_pVertex)
	{
		Engine::Safe_Delete_Array(m_pVertex);
	}

	if(m_pConvertVertex)
	{
		Engine::Safe_Delete_Array(m_pConvertVertex);
	}

	for(size_t i = 0; i < m_pItem.size(); ++i)
	{
		Engine::Safe_Delete(m_pItem[i]);
	}
	m_pItem.clear();

	for(size_t i = 0; i < m_pPoketmon.size(); ++i)
	{
		Engine::Safe_Delete(m_pPoketmon[i]);
	}
	m_pPoketmon.clear();

	Engine::Safe_Delete(m_pTempItem);
	Engine::Safe_Delete(m_pWeapon);
	Engine::Safe_Delete(m_pPoket);


}
HRESULT CInven::AddComponent(void)
{
	Engine::CComponent*		pComponent = NULL;

	// Buffer
	pComponent = m_pResourceMgr->CloneResource(Engine::RESOURCE_STATIC, L"Buffer Inven");
	m_pBuffer = dynamic_cast<Engine::CVIBuffer*>(pComponent);
	NULL_CHECK_RETURN(m_pBuffer, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Buffer", pComponent));

	//Texture
	pComponent = m_pResourceMgr->CloneResource(Engine::RESOURCE_STATIC, L"Texture Inven");
	m_pTexture = dynamic_cast<Engine::CTexture*>(pComponent);
	NULL_CHECK_RETURN(m_pTexture, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Texture", pComponent));

	// Collision Mouse
	pComponent = m_pCollisionMgr->CloneColObject(CCollisionMgr::COL_MOUSE);
	m_pMouseCol = dynamic_cast<CMouseCol*>(pComponent);
	NULL_CHECK_RETURN(m_pMouseCol, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"MouseCol", pComponent));

	return S_OK;
}

void CInven::SetTransform(void)
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

void CInven::KeyInput( void )
{
	if(m_pKeyMgr->KeyDown('I'))
	{
		if(m_bOnOff)
			m_bOnOff = false;

		else if(!m_bOnOff)
			m_bOnOff = true;
	}

	if(m_pKeyMgr->KeyDown(VK_RBUTTON))
	{	
		POINT	ptMouse;

		GetCursorPos(&ptMouse);
		ScreenToClient(g_hWnd, &ptMouse);

		ptMouse.y += 20;
		//장착
		for(int i = 0; i < 27; ++i)
		{
			if(PtInRect(&m_pItem[i]->GetRect(), ptMouse) && m_pItem[i]->GetId() == IT_ITEM)
			{
				((CPlayer*)m_pPlayer)->ItemEquip(m_pItem[i]->GetType());
				CItem* Temp = NULL;
				Temp = m_pWeapon;
				m_pWeapon =m_pItem[i];
				m_pItem[i] = Temp;
				return;
			}

		}

		for(int i = 0; i < 9; ++i)
		{
			if(PtInRect(&m_pPoketmon[i]->GetRect(), ptMouse) && m_pPoketmon[i]->GetId() == IT_POKETMON)
			{
				CSoundMgr::GetInstance()->PlaySound(L"Jiwoo3.mp3");
				((CPlayer*)m_pPlayer)->PoketEquip(m_pPoketmon[i]->GetType());
				Engine::Safe_Delete(m_pPoketmon[i]);
				m_pPoketmon[i] =  CItem::Create(m_pDevice, IT_EMPTY);
				return;
			}

		}

		//아이템 빼기
		if(PtInRect(&m_pWeapon->GetRect(), ptMouse) && m_pWeapon->GetId() == IT_ITEM)
		{
			for(int i = 0; i < 27; ++i)
			{
				if(m_pItem[i]->GetId() == IT_EMPTY)
				{
					CItem* Temp = NULL;
					Temp = m_pWeapon;
					m_pWeapon =m_pItem[i];
					m_pItem[i] = Temp;
					((CPlayer*)m_pPlayer)->ItemUnequip();
					return;

				}
			}
		}

		if(PtInRect(&m_pPoket->GetRect(), ptMouse) && m_pPoket->GetId() == IT_POKETMON)
		{
			for(int i = 0; i < 9; ++i)
			{
				if(m_pPoketmon[i]->GetId() == IT_EMPTY)
				{
					CItem* Temp = NULL;
					Temp = m_pPoket;
					m_pPoket =m_pPoketmon[i];
					m_pPoketmon[i] = Temp;
					return;

				}
			}
		}

	}

	if(m_pKeyMgr->KeyDown(VK_LBUTTON))
	{	
		POINT	ptMouse;

		GetCursorPos(&ptMouse);
		ScreenToClient(g_hWnd, &ptMouse);

		//인벤
		for(int i = 0; i < 27; ++i)
		{
			if(PtInRect(&m_pItem[i]->GetRect(), ptMouse) && 
				m_pItem[i]->GetId() != IT_EMPTY &&
				m_pTempItem == NULL)
			{
				m_pTempItem =m_pItem[i];
				m_pItem[i] = CItem::Create(m_pDevice, IT_EMPTY);
				return;
			}
			else if(PtInRect(&m_pItem[i]->GetRect(), ptMouse) && m_pTempItem != NULL)
			{
				CItem* Temp = NULL;
				Temp = m_pTempItem;
				m_pTempItem = m_pItem[i];
				m_pItem[i] = Temp;
				return;

			}
		}	

		//포켓몬 인벤
		for(int i = 0; i < 9; ++i)
		{
			if(PtInRect(&m_pPoketmon[i]->GetRect(), ptMouse) && 
				m_pPoketmon[i]->GetId() != IT_EMPTY &&
				m_pTempItem == NULL)
			{
				m_pTempItem =m_pPoketmon[i];
				m_pPoketmon[i] = CItem::Create(m_pDevice, IT_EMPTY);
				return;
			}
			else if(PtInRect(&m_pPoketmon[i]->GetRect(), ptMouse) && m_pTempItem != NULL)
			{
				CItem* Temp = NULL;
				Temp = m_pTempItem;
				m_pTempItem = m_pPoketmon[i];
				m_pPoketmon[i] = Temp;
				return;

			}
		}	

		// 장비창
		if(PtInRect(&m_pWeapon->GetRect(), ptMouse) && 
			m_pWeapon->GetId() == IT_EMPTY &&
			m_pTempItem != NULL)
		{
			CItem* Temp = NULL;
			Temp = m_pTempItem;
			m_pTempItem = NULL;
			m_pWeapon = Temp;
			return;
		}
		else if(PtInRect(&m_pWeapon->GetRect(), ptMouse) && 
			m_pWeapon->GetId() != IT_EMPTY &&
			m_pTempItem == NULL)
		{
			m_pTempItem = m_pWeapon;
			m_pWeapon = CItem::Create(m_pDevice, IT_EMPTY);
			return;
		}

		// 포켓몬 장비창
		if(PtInRect(&m_pPoket->GetRect(), ptMouse) && 
			m_pPoket->GetId() == IT_EMPTY &&
			m_pTempItem != NULL)
		{
			CItem* Temp = NULL;
			Temp = m_pTempItem;
			m_pTempItem = NULL;
			m_pPoket = Temp;
			return;
		}
		else if(PtInRect(&m_pPoket->GetRect(), ptMouse) && 
			m_pPoket->GetId() != IT_EMPTY &&
			m_pTempItem == NULL)
		{
			m_pTempItem = m_pPoket;
			m_pPoket = CItem::Create(m_pDevice, IT_EMPTY);
			return;
		}
	}

	if(m_pKeyMgr->StayKeyDown(VK_LBUTTON) && m_pTempItem == NULL)
	{
		m_pMouseCol->PickUi(&m_rcRect, &m_vPos);
	}
	else
	{
		m_pMouseCol->SetDrag();
	}

}

void CInven::SetPlayer(Engine::CGameObject* Player)
{
	m_pPlayer = Player;
}

void CInven::AddPoketmon( wstring wstrKey )
{
	for(size_t i = 0; i < m_pPoketmon.size(); ++i)
	{
		if(m_pPoketmon[i]->GetId() == IT_EMPTY)
		{
			CItem* pTemp = m_pPoketmon[i];
			m_pPoketmon[i] = CItem::Create(m_pDevice, IT_POKETMON);
			Engine::Safe_Delete(pTemp);

			if(wstrKey == L"Ggobugi")
				m_pPoketmon[i]->SetType(0);
			if(wstrKey == L"Pairi")
				m_pPoketmon[i]->SetType(1);
			if(wstrKey == L"Picachu")
				m_pPoketmon[i]->SetType(2);
			return;
		}
	}
}

void CInven::AddItem( wstring wstrKey )
{
	for(size_t i = 0; i < m_pItem.size(); ++i)
	{
		if(m_pItem[i]->GetId() == IT_EMPTY)
		{
			CItem* pTemp = m_pItem[i];
			m_pItem[i] = CItem::Create(m_pDevice, IT_ITEM);
			Engine::Safe_Delete(pTemp);

			if(wstrKey == L"Ggobugi")
				m_pItem[i]->SetType(0);
			if(wstrKey == L"Pairi")
				m_pItem[i]->SetType(1);
			if(wstrKey == L"Picachu")
				m_pItem[i]->SetType(2);
			return;
		}
	}

}
