#ifndef Inven_h__
#define Inven_h__


#include "UI.h"

namespace Engine
{
	class CResourceMgr;
	class CTexture;
	class CVIBuffer;
	class CTransform;
	class CKeyMgr;
}
class CItem;
class CCollisionMgr;
class CMouseCol;
class CInven 
	: public Engine::CUI
{
private:
	vector<CItem*>				m_pItem;
	vector<CItem*>				m_pPoketmon;

	Engine::CResourceMgr*		m_pResourceMgr;
	Engine::CVIBuffer*			m_pBuffer;
	Engine::CTexture*			m_pTexture;
	Engine::CKeyMgr*			m_pKeyMgr;

	Engine::VTXTEX*				m_pVertex;
	Engine::VTXTEX*				m_pConvertVertex;
	DWORD						m_dwVtxCnt;



	CCollisionMgr*				m_pCollisionMgr;
	CMouseCol*					m_pMouseCol;

	//¼º½Ä
	Engine::CGameObject*		m_pPlayer;

	CItem*						m_pTempItem;
	CItem*						m_pWeapon;
	CItem*						m_pPoket;

	bool						m_bOnOff;
private:
	HRESULT		Initialize(void);
	void		SetTransform(void);
	void		KeyInput(void);


public:
	void				Update(void);
	void				Render(void);
	void				Release(void);
	HRESULT				AddComponent(void);
	void				SetPlayer(Engine::CGameObject* Player);

	void				AddPoketmon(wstring wstrKey);
	void				AddItem(wstring wstrKey);
public:
	static	CInven*		Create(LPDIRECT3DDEVICE9 pDevice);


private:
	explicit	CInven(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CInven(void);

};
#endif // Inven_h__
