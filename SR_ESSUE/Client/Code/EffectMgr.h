/*!
 * \file EffectMgr.h
 * \date 2017/01/24 5:27
 *
 * \author Administrator
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \ 이펙트들을 관리하는 매니져 입니다. 그냥 게임오브젝트에 넣기도 귀찮고 
 *   삭제하는법도 몰라서 대충 만들었습니다.
*/

/// 내일와서 할것은 여기다 싱글톤 만들고 CEmanation 형 이펙트 저장하고
/// 맵으로 만들어다가 RC Texture 인지 RC Color 인지도 구별 가게끔 만들고
/// 일단 급한대로 화염방사기가 나가는지 확인부터 하고

#ifndef EffectMgr_h__
#define EffectMgr_h__

#include "Engine_Include.h"

namespace Engine
{
	class CLayer;
	class CTransform;
}
class CEmanation;
class CEffectMgr
{

private:
	static CEffectMgr*				m_pInstance;
	Engine::CLayer*			m_pLayer;
	LPDIRECT3DDEVICE9		m_pDevice;

public:
	static CEffectMgr*	GetInstance( void );
	static void			DestroyInstance( void );
	static void			CreateEffectMgr(LPDIRECT3DDEVICE9 pDevice, Engine::CLayer* pLayer);

private:
	CEffectMgr(LPDIRECT3DDEVICE9 pDevice, Engine::CLayer* pLayer);
	~CEffectMgr(void);

private:
	typedef list<CEmanation*> EMANATIONLIST;
	typedef map<Engine::EFFECTTYPE, list<CEmanation*>>	MAPEMANATIONLST;

	EMANATIONLIST			m_EffectList;
	MAPEMANATIONLST			m_mapEffectList;

public:
	void AddEffect(Engine::EFFECTTYPE eEffectType, Engine::EMANATIONID eEmanationID, Engine::CTransform* pTransform, D3DXVECTOR3 vDir);

	list<CEmanation*>	GetEffectList(Engine::EFFECTTYPE eEffectType);

	void	Update(void);
	void	Render(void);
	void	Release(void);

private:

};
#endif // EffectMgr_h__
