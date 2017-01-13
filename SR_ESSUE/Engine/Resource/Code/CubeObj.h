/*!
 * \file CubeObj.h
 * \date 2017/01/10 16:04
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


#include "Resources.h"

BEGIN(Engine)

class ENGINE_DLL CCubeObj
	:public CResources
{
private:
	typedef vector<SAVEFRAME*>		VECTORFRAME;
	VECTORFRAME						m_vecFrame;

public:
	virtual void Render( void );
	virtual void Release( void );
	virtual void Update( void );
	virtual CResources* CloneResource( void );

	void AddSprite(const wstring& wstrName, SAVEFRAME* pSave );
	void RemoveSprite( const wstring& wstrName );

	VECTORFRAME* GetVecPart(void);

public:
	static CCubeObj* Create(LPDIRECT3DDEVICE9 pDevice);

private:
	explicit	CCubeObj(LPDIRECT3DDEVICE9 pDevice);
public:
	virtual ~CCubeObj(void);

};

END

#endif // CubeObj_h__
