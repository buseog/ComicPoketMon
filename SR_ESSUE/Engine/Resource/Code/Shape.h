/*!
 * \file Shape.h
 * \date 2017/01/10 3:51
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

#ifndef Shape_h__
#define Shape_h__

#include "Component.h"

BEGIN(Engine)

class CVIBuffer;
class ENGINE_DLL CShape
	:public CComponent
{
protected:
	typedef	list<CVIBuffer*>			BUFFERLIST;
	typedef map<wstring, BUFFERLIST>	MAPSHAPE;
	MAPSHAPE							m_mapShape;
	LPDIRECT3DDEVICE9					m_pDevice;
	WORD*								m_pwRefCnt;

public:
	virtual void Render(void);
	virtual void Release(void);
	virtual CShape* CloneResource(void);

protected:
	explicit CShape(LPDIRECT3DDEVICE9 pDevice);
public:
	~CShape(void);
};

END
#endif // Shape_h__