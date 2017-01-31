/*!
 * \file Player.h
 * \date 2016/12/26 16:45
 *
 * \author Administrator
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef Player_h__
#define Player_h__
#include "Include.h"
#include "MultiGameObject.h"

namespace Engine
{
	class CStatSubject;
	class CKeyMgr;
}

class CPoketmon;
class CItemParts;
class CTerrainCol;
class CMouseCol;
class CBoundCol;
class CAction;

class CFirework;
class CBreath;

class CPlayer 
	: public CMultiGameObject
{
private:
	bool						m_bMove;
	// 키매니저
	Engine::CKeyMgr*			m_pKeyMgr;

	Engine::CStatSubject*		m_pStatSubject;
	//성식
	Engine::CGameObject*		m_pInven;
	int							m_iItem;

	// 상수 & 이넘 변수
	int							m_iPoketballEA;
	STATEID						m_eState;
	SCENEID						m_eStage;
	CGameObject*				m_pPoketball[5];
	
	// 콜리전
	CTerrainCol*				m_pTerrainCol;
	CMouseCol*					m_pMouseCol;
	CBoundCol*					m_pBoundCol;

	Engine::CBoundBox*			m_pAttackBox;

	CAction*					m_pAction;
	D3DXVECTOR3					m_vDestPos;
	
	// 스테이지 씬
	Engine::CLayer*				m_pLayer;
	
private:
	HRESULT		Initialize(void);
	void		Release(void);
	void		KeyInput(void);
	void		SetDirection(void);
	void		Move(void);
	void		Load(void);
	void		CreatePoketball(void);

public:
	HRESULT		AddComponent(void);
	void		Update(void);
	void		Render(void);	
	void		SetLayer(Engine::CLayer* pLayer);

	//성식
	void		SetInven(Engine::CGameObject* Inven);
	void		ItemEquip(int Item);
	void		ItemUnequip(void);

	void		PoketEquip(int Type);
	void		PoketUnEquip(void);
	
	void		ColBulding(void);
	void		SetStage(SCENEID ID);

	void		BoundBoxSetting(void);
	void		ColBoss(void);
	void		ColPoketmon(void);
	void		ColMonsterball(void);
	void		ColItem(void);

	void		SetState(STATEID eState);

public:
	static	CPlayer*	Create(LPDIRECT3DDEVICE9 pDevice);

private:
	explicit	CPlayer(LPDIRECT3DDEVICE9 pDevice);
public:
	virtual ~CPlayer(void);

};

#endif // Player_h__