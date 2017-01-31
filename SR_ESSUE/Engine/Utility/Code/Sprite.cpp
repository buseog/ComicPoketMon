#include "Sprite.h"
#include "Export_Function.h"
#include "TimeMgr.h"

Engine::CSprite::CSprite(void)
: pTimeMgr(Engine::Get_TimeMgr())
, fSpriteCnt(0.f)
, fSpriteMax(0.f)
, fSpriteSpeed(1.f)
{

}
Engine::CSprite::~CSprite(void)
{

}

bool Engine::CSprite::PlaySprite( void )
{
	fSpriteCnt += fSpriteMax * pTimeMgr->GetTime() * fSpriteSpeed;

	if (fSpriteCnt >= fSpriteMax)
	{
		fSpriteCnt = 0.f;

		return true;
	}

	return false;
}

Engine::CSprite* Engine::CSprite::Create( void )
{
	return new CSprite;
}