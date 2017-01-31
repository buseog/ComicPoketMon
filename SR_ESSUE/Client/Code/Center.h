#ifndef Center_h__
#define Center_h__

#include "Scene.h"
#include "SoundMgr.h"
#include "GameObject.h"
namespace Engine
{
	class CManagement;
}

class CCenter
	: public Engine::CScene
{
private:
	Engine::CManagement*		m_pManagement;
	Engine::CGameObject*		m_pPlayer;
	Engine::CGameObject*		m_pInven;

	CSoundMgr*					m_pSound;

public:
	enum LAYERID { LAYER_ENVIRONMENT, LAYER_GAMELOGIC, LAYER_UI };

public:
	virtual HRESULT InitScene(void);
	virtual void	Update(void);
	virtual void	Render(void);

private:
	HRESULT		Add_Environment_Layer(void);
	HRESULT		Add_GameLogic_Layer(void);
	HRESULT		Add_UI_Layer(void);
	void		Release(void);

public:
	static CCenter*	Create(LPDIRECT3DDEVICE9 pDevice);

private:
	explicit CCenter(LPDIRECT3DDEVICE9 pDevice);
public:
	~CCenter(void);

};

#endif // Center_h__
