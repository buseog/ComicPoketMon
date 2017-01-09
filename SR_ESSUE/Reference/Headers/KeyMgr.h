/*!
 * \file KeyMgr.h
 * \date 2017/01/08 19:26
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


#ifndef KeyMgr_h__
#define KeyMgr_h__

#include "Engine_Include.h"

BEGIN(Engine)

class ENGINE_DLL CKeyMgr
{
	DECLARE_SINGLETON(CKeyMgr)

private:
	bool	m_bKeyDown[KEYPORT][KEYMAX];
	bool	m_bKeyUp[KEYPORT][KEYMAX];

public:
	bool	StayKeyDown(int nKey);
	bool	KeyDown(int nKey, int iIndex = 0);
	bool	KeyUp(int nKey, int iIndex);

private:
	CKeyMgr(void);
	~CKeyMgr(void);
};

END
#endif // KeyMgr_h__