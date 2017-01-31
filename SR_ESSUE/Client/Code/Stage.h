#ifndef Stage_h__
#define Stage_h__

#include "Scene.h"
#include "SoundMgr.h"
#include "Snow.h"
#include "Layer.h"

namespace Engine
{
	class CManagement;
}

class CSnow;
class CStage
	: public Engine::CScene
{
private:
	Engine::CManagement*		m_pManagement;
	CSoundMgr*					m_pSound;
	CSnow*						m_pSnow;

public:
	enum LAYERID { LAYER_ENVIRONMENT, LAYER_GAMELOGIC, LAYER_UI };

public:
	virtual HRESULT InitScene(void);
	virtual void	Update(void);
	virtual void	Render(void);

public:
	void			DataLoad(Engine::CLayer* pLayer);

private:
	HRESULT			Add_Environment_Layer(void);
	HRESULT			Add_GameLogic_Layer(void);
	HRESULT			Add_UI_Layer(void);
	void			Release(void);

public:
	static CStage*	Create(LPDIRECT3DDEVICE9 pDevice);

private:
	explicit CStage(LPDIRECT3DDEVICE9 pDevice);
public:
	~CStage(void);

};
#endif // Stage_h__
