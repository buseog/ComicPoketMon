/*!
 * \file Sprite.h
 * \date 2017/01/14 15:43
 *
 * \author ESSUE
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef Sprite_h__
#define Sprite_h__

#include "Component.h"

namespace Engine
{
	class CTimeMgr;
}

BEGIN(Engine)

class ENGINE_DLL CSprite
	:public CComponent
{
public:
	Engine::CTimeMgr*	pTimeMgr;
	float	fSpriteCnt;
	float	fSpriteMax;
	float	fSpriteSpeed;

public:
	bool	PlaySprite(void);

public:
	static CSprite* Create(void);

private:
	CSprite(void);

public:
	virtual ~CSprite(void);
};

END
#endif // Sprite_h__