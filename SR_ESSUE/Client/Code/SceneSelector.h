
#ifndef SceneSelector_h__
#define SceneSelector_h__

#include "Include.h"
#include "Logo.h"
#include "Stage.h"

class CSceneSelector
{
private:
	SCENEID		m_eSceneID;
public:
	explicit CSceneSelector(SCENEID eSceneID)
		: m_eSceneID(eSceneID) {}
	~CSceneSelector(){}

public:
	HRESULT		operator()(Engine::CScene** ppScene, LPDIRECT3DDEVICE9 pDevice)
	{
		switch(m_eSceneID)
		{
		case SC_LOGO:
			*ppScene = CLogo::Create(pDevice);
			break;

		case SC_STAGE:
			*ppScene = CStage::Create(pDevice);
			break;
		}

		NULL_CHECK_RETURN(*ppScene, E_FAIL);

		return S_OK;
	}

};


#endif // SceneSelector_h__