/*!
 * \file Layer.h
 * \date 2017/01/07 2:52
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


#ifndef Layer_h__
#define Layer_h__

#include "Engine_Include.h"

BEGIN(Engine)

class CGameObject;
class CComponent;
class ENGINE_DLL CLayer
{
private:
	typedef	list<CGameObject*>		OBJLIST;
	typedef map<wstring, OBJLIST>	MAPOBJLIST;
	MAPOBJLIST						m_mapObjList;
	LPDIRECT3DDEVICE9				m_pDevice;

private:
	void		Release(void);

public:
	void						Update(void);
	void						Render(void);
	HRESULT						AddObject(const wstring& wstrObjKey, CGameObject*	pGameObject);
	OBJLIST*					GetComponentList(const wstring& wstrObjKey);
	const CComponent*			GetComponent(const wstring& wstrObjKey, const wstring& wstrComponentKey);
	const Engine::VTXTEX*		GetTerrainVertex(const wstring& wstrObjKey);

public:
	static CLayer* Create(LPDIRECT3DDEVICE9 pDevice);

private:
	explicit CLayer(LPDIRECT3DDEVICE9 pDevice);

public:
	~CLayer();
};

END
#endif // Layer_h__