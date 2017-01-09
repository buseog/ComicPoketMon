/*!
 * \file CubeObj.h
 * \date 2017/01/09 0:54
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

#ifndef CubeObj_h__
#define CubeObj_h__

#include "Component.h"

class CCubeCol;
class CCubeObj
	:public Engine::CComponent
{
private:
	typedef map<wstring, CCubeCol*>		MAPCUBE;
	MAPCUBE								m_mapCube;
	LPDIRECT3DDEVICE9					m_pDevice;

public:
	HRESULT Initialize(void);
	void	Update(void);
	void	Render(void);
	void	Release(void);

public:
	static CCubeObj* Create(LPDIRECT3DDEVICE9 pDevice);

private:
	explicit CCubeObj(LPDIRECT3DDEVICE9 pDevice);
public:
	~CCubeObj(void);
};


#endif // CubeObj_h__