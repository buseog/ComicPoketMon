/*!
 * \file Poketmon.h
 * \date 2017/01/14 14:25
 *
 * \author ESSUE
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/
#ifndef Poketmon_h__
#define Poketmon_h__

#include "MultiGameObject.h"

class CTerrainCol;
class CAction;
class CBoundCol;
class CPoketmon	
	: public CMultiGameObject
{
private:
	Engine::CVIBuffer*			m_pHpBarBuffer;
	Engine::CTexture*			m_pHpBarTexture;
	Engine::CTexture*			m_pMpBarTexture;


	Engine::VTXTEX*				m_pVertex;
	Engine::VTXTEX*				m_pConvertVertex;

	CBoundCol*					m_pBoundCol;
	Engine::CBoundBox*			m_pAttackBox;

	CTerrainCol*				m_pTerrainCol;
	CAction*					m_pAction;


	
	float						m_fPattenTime;
	float						m_fSoundTime;
	float						m_fAttackTime;
	float						m_fSkillTime;
	float						m_fChannel;
	DWORD						m_dwPatten;
	DWORD						m_dwType;
	
	Engine::CLayer*				m_pLayer;
	const Engine::CTransform*	m_pTargetInfo;

private:
	HRESULT		Initialize( void );
	void		Release(void);
	void		Load(void);
	
	void		SetTransform(void);
	void		SetDirection(void);
	void        Follow(void);
	void		Patrol(void);
	void		FollowMove(void);
	void		Sound(void);

	void		ColPlayerAttack(void);
	bool		ColPoketmon(void);
	void		ColBulding(void);

	
public:
	HRESULT		AddComponent(void);
	void		Update( void );
	void		Render( void );
	void		SetType(DWORD dwType);
	virtual DWORD		GetType(void);

public:
	static	CPoketmon*	Create(LPDIRECT3DDEVICE9 pDevice, const wstring& wstrObjKey, Engine::CLayer* pLayer);

private:
	explicit CPoketmon(LPDIRECT3DDEVICE9 pDevice, const wstring& wstrObjKey, Engine::CLayer* pLayer);
	explicit CPoketmon(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual	~CPoketmon(void);


};

#endif // Poketmon_h__
