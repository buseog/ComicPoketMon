#ifndef Management_h__
#define Management_h__

#include "Renderer.h"

BEGIN(Engine)

class CLayer;
class CRenderer;
class CScene;
class ENGINE_DLL CManagement
{
	DECLARE_SINGLETON(CManagement)
	enum SCENEID { SC_LOGO, SC_STAGE, SC_CENTER, SC_END };

private:
	LPDIRECT3DDEVICE9		m_pDevice;
	CRenderer*				m_pRenderer;
	CScene*					m_pScene;
	CScene*					m_pSceneTemp[SC_END];

public:
	static int	m_iScene;

private:
	void	Release(void);

public:
	HRESULT	InitManagement(LPDIRECT3DDEVICE9	_pDevice);
	void	Update(void);
	void	Render(float fTime);
	const Engine::VTXTEX*		GetTerrainVertex(const WORD& LayerID, const wstring& wstrObjKey);

	Engine::CScene*			GetScene(int ID);

public:
	template <typename T>
	HRESULT SceneChange(T& Functor, int SceneID);

private: 
	CManagement();
	~CManagement();
};

template <typename T>
HRESULT Engine::CManagement::SceneChange( T& Functor , int SceneID)
{
	/*if(NULL != m_pScene)
		Engine::Safe_Delete(m_pScene);*/

	m_iScene = SceneID;

	if(m_pSceneTemp[SceneID] == NULL)
		FAILED_CHECK(Functor(&m_pSceneTemp[SceneID], m_pDevice));

	m_pScene = m_pSceneTemp[SceneID];
	m_pRenderer->SetScene(m_pScene);
	return S_OK;
}

END
#endif // Management_h__
