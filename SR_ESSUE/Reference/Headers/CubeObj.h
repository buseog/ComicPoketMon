/*!
 * \file CubeObj.h
 * \date 2017/01/10 16:04
 *
 * \author ESSUE
 * Contact: user@company.com
 *
 * \brief 몸을 이루고있는 큐브들을 모아놓은 클래스 / 세이브용으로 이용하는 벡터를 지니고있음
 *
 * TODO: long description
 *
 * \note 기본적으로는 큐브들을 모아서 하나의 객체를 만드는 클래스이지만, 세이브&로드가 번거로워서
		세이브 로드용 STL을 하나 새로 추가해서 이용함.
*/

#ifndef CubeObj_h__
#define CubeObj_h__


#include "Resources.h"

namespace Engine
{
	class CVIBuffer;
}

BEGIN(Engine)

class ENGINE_DLL CCubeObj
	:public CResources
{
private:
	typedef vector<SAVEFRAME*>				VECTORFRAME;
	typedef vector<Engine::CVIBuffer*>		VECCUBE;
	VECTORFRAME						m_vecFrame;
	VECCUBE							m_vecCube;
	Engine::VTXCUBE*				m_pVertex;

public:
	virtual void Update( D3DXMATRIX* matWorld, D3DXMATRIX* matView, D3DXMATRIX* matProj );
	virtual void Render( void );
	virtual CResources* CloneResource( void );

	void Release( void );
	void AddCube(Engine::CVIBuffer* pCube);
	void RemoveCube(Engine::CVIBuffer* pCube);

	void AddFrame(SAVEFRAME* pSave );
	void RemoveFrame( const wstring& wstrName );

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
