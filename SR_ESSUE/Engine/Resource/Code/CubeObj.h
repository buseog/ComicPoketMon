/*!
 * \file CubeObj.h
 * \date 2017/01/10 16:04
 *
 * \author ESSUE
 * Contact: user@company.com
 *
 * \brief ���� �̷���ִ� ť����� ��Ƴ��� Ŭ���� / ���̺������ �̿��ϴ� ���͸� ���ϰ�����
 *
 * TODO: long description
 *
 * \note �⺻�����δ� ť����� ��Ƽ� �ϳ��� ��ü�� ����� Ŭ����������, ���̺�&�ε尡 ���ŷο���
		���̺� �ε�� STL�� �ϳ� ���� �߰��ؼ� �̿���.
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
