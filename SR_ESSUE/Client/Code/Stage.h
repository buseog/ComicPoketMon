#ifndef Stage_h__
#define Stage_h__

#include "Scene.h"

namespace Engine
{
	class CManagement;
	class CResourceMgr;
}

class CStage
	: public Engine::CScene
{
private:
	Engine::CManagement*		m_pManagement;
	Engine::CResourceMgr*		m_pResourceMgr;

public:
	enum LAYERID { LAYER_ENVIRONMENT, LAYER_GAMELOGIC, LAYER_UI };

public:
	virtual HRESULT InitScene(void);
	virtual void Update(void);
	virtual void Render(void);

private:
	HRESULT		Add_Environment_Layer(void);
	HRESULT		Add_GameLogic_Layer(void);
	HRESULT		Add_UI_Layer(void);
	void		Release(void);


public:
	static CStage*	Create(LPDIRECT3DDEVICE9 pDevice);

private:
	explicit CStage(LPDIRECT3DDEVICE9 pDevice);
public:
	~CStage(void);

};
#endif // Stage_h__
