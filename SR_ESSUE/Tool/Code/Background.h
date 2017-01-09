/*!
 * \file Background.h
 * \date 2017/01/08 23:42
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
#ifndef Background_h__
#define Background_h__

#include "Engine_Include.h"

class CBackground
{
private:
	LPDIRECT3DDEVICE9	m_pDeivce;

public:
	void	Initialize(void);
	void	Render(void);
	void	Release(void);
	void	KeyCheck(void);
	void	Picking(void);


public:
	static CBackground* Create(LPDIRECT3DDEVICE9 pDevice);

private:
	explicit CBackground(LPDIRECT3DDEVICE9 pDevice);
public:
	~CBackground(void);
};

#endif // Background_h__
