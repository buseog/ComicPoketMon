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
 * \ ����Ʈ���� �����ϴ� �Ŵ��� �Դϴ�. �׳� ���ӿ�����Ʈ�� �ֱ⵵ ������ 
 *   �����ϴ¹��� ���� ���� ��������ϴ�.
*/

/// ���Ͽͼ� �Ұ��� ����� �̱��� ����� CEmanation �� ����Ʈ �����ϰ�
/// ������ �����ٰ� RC Texture ���� RC Color ������ ���� ���Բ� �����
/// �ϴ� ���Ѵ�� ȭ�����Ⱑ �������� Ȯ�κ��� �ϰ�

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
