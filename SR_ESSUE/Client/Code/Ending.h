/*!
 * \file Ending.h
 * \date 2017/01/25 11:31
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

#ifndef Ending_h__
#define Ending_h__

#include "Scene.h"

class CEnding
	: public Engine::CScene
{
private:
	HWND				m_hVideo;

public:
	virtual void Update(void);
	virtual HRESULT InitScene(void);
	void		Release(void);


public:
	static CEnding* Create(LPDIRECT3DDEVICE9 pDevice);

private:
	explicit CEnding(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CEnding(void);
};

#endif // Ending_h__