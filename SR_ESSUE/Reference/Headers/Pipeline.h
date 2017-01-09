/*!
 * \file Pipeline.h
 * \date 2017/01/08 17:11
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

#ifndef Pipeline_h__
#define Pipeline_h__

#include "Engine_Include.h"

BEGIN(Engine)

class ENGINE_DLL CPipeline
{
public:
	static void MakeWorldMatrix(D3DXMATRIX* pMatrix, const D3DXVECTOR3* pScale,const float* pAngle,	const D3DXVECTOR3* pPos);
	static void MakeTransformMatrix(D3DXMATRIX* pMatrix, const D3DXVECTOR3* pRight,	const D3DXVECTOR3* pUp,	const D3DXVECTOR3* pLook, const D3DXVECTOR3* pPos);
	static void MakeViewSpaceMatrix(D3DXMATRIX* pMatrix, const D3DXVECTOR3* pEye, const D3DXVECTOR3* pAt, const D3DXVECTOR3* pUp);
	static void MakeProjectionMatrix(D3DXMATRIX* pOut, const float& fFovY, const float& fAspect, const float& fNear, const float& fFar);
	//static void MyTransformCoord(D3DXVECTOR3* pOut, const D3DXVECTOR3* pVector, const D3DXMATRIX* pMatrix);
	static void	MyTransformCoord(D3DXVECTOR3* vOut, const D3DXVECTOR3* vVec, const D3DXMATRIX* matWorld);
	static void	MyTransformNormal(D3DXVECTOR3* vOut, const D3DXVECTOR3* vVec, const D3DXMATRIX* matWorld);

private:
	CPipeline(void);
	~CPipeline(void);
};

END
#endif // Pipeline_h__