/*!
 * \file Frame.h
 * \date 2017/01/14 15:13
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

#ifndef Frame_h__
#define Frame_h__

#include "Component.h"

namespace Engine
{
	class CTimeMgr;
}

BEGIN(Engine)

class ENGINE_DLL CFrame
	:public CComponent
{
public:
	Engine::CTimeMgr*	pTimeMgr;
	float				fFrameCnt;
	float				fMaxCnt;
	float				fFrameSpeed;

public:
	virtual void Update( void );

private:
	explicit CFrame(void);

public:
	virtual ~CFrame(void);
};

END
#endif // Frame_h__