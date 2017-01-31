/*!
 * \file Emanation.h
 * \date 2017/01/24 4:12
 *
 * \author Administrator
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \ �������� ���� �������� ���ù����� Ŭ���� �Դϴ�.
 *		���� �̻ڰ� ���� �� �����Ű��׿�
*/

#ifndef Emanation_h__
#define Emanation_h__

#include "SingleGameObject.h"

namespace Engine
{
	class CTransform;
	class CLayer;
}
class CEmanation : public CSingleGameObject
{
private:
	vector<CEmanation*>		m_vecParticleManaged;

public:
	enum COLARGB{COL_A, COL_R, COL_G, COL_B, COL_END};
	bool				m_bContents;

protected:
	Engine::VTXCOL*		m_pVertex;
	Engine::VTXCOL*		m_pConvertVertex;
//	Engine::CLayer*		m_pLayer;
	DWORD				m_dwColorARGB[COL_END];

	float				m_fGunDistance;
	float				m_fShotRadian;

	// �� ��ġ�� ���� ��� ��Ÿ��� �����մϴ�.
	float				m_fRange;

	bool				m_bCulling;

public:
	virtual HRESULT				Initialize(void);
	virtual void				Update(void);
	virtual void				Render(void);
	
public:
	HRESULT						AddComponent(void);
	void						Release(void);

protected:
	explicit	CEmanation(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual~CEmanation(void);

};
#endif // Emanation_h__