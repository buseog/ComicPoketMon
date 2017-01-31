/*!
 * \file GameObject.h
 * \date 2017/01/07 2:46
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

#ifndef GameObject_h__
#define GameObject_h__

#include "Engine_Include.h"

BEGIN(Engine)

class CComponent;
class ENGINE_DLL CGameObject
{
protected:
	typedef	map<wstring, CComponent*>		MAPCOMPONENT;
	MAPCOMPONENT							m_mapComponent;
	LPDIRECT3DDEVICE9						m_pDevice;
	bool									m_bDestroy;
	bool									m_bCulling;

private:
	void	Release(void);

public:
	void	SetDestroy(void);
	bool	GetDestroy(void);

public:
	virtual HRESULT Initialize(void);
	virtual void	Update(void);
	virtual void	Render(void);
	virtual const Engine::VTXTEX*	GetTerrainVertex(void);


	const CComponent*	GetComponent(const wstring& wstrComponentKey);

protected:
	explicit CGameObject(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CGameObject(void);
};


END
#endif // GameObject_h__