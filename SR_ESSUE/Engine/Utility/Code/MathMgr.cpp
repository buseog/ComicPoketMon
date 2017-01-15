#include "MathMgr.h"

Engine::CMathMgr::CMathMgr(void)
{
}

Engine::CMathMgr::~CMathMgr(void)
{
}

float Engine::CMathMgr::MyLength(D3DXVECTOR3* vDest, D3DXVECTOR3* vDepa)
{
	D3DXVECTOR3 vTemp = *vDest - *vDepa;

	float fDistance = sqrt((vTemp.x * vTemp.x) + (vTemp.y * vTemp.y) + (vTemp.z * vTemp.z));

	return fDistance;
}

void Engine::CMathMgr::MyNormalize(D3DXVECTOR3* vOut, D3DXVECTOR3* vIn)
{
	float fDistance = sqrt((vIn->x * vIn->x) + (vIn->y * vIn->y) + (vIn->z * vIn->z));

	vOut->x = vIn->x / fDistance;
	vOut->y = vIn->y / fDistance;
	vOut->z = vIn->z / fDistance;
}

float Engine::CMathMgr::MyDot(D3DXVECTOR3* vDest, D3DXVECTOR3* vDepa)
{
	float fDot = (vDest->x * vDepa->x) + (vDest->y * vDepa->y) + (vDest->z * vDepa->z);

	return fDot;
}

D3DXVECTOR3 Engine::CMathMgr::MyCross(D3DXVECTOR3* vDest, D3DXVECTOR3* vDepa)
{
	D3DXVECTOR3 vTemp = D3DXVECTOR3(0.f, 0.f, 0.f);

	vTemp.x = (vDest->y * vDepa->z) - (vDest->z * vDepa->y);
	vTemp.y = (vDest->z * vDepa->x) - (vDest->x * vDepa->z);
	vTemp.z = (vDest->x * vDepa->y) - (vDest->y * vDepa->x);

	return vTemp;
}

void Engine::CMathMgr::MyIdentity(D3DXMATRIX* matWorld)
{
	ZeroMemory(matWorld, sizeof(D3DXMATRIX));

	matWorld->_11 = matWorld->_22 = matWorld->_33 = matWorld->_44 = 1; 
}

void Engine::CMathMgr::MyScaling(D3DXMATRIX* matScale, float fX, float fY, float fZ)
{
	CMathMgr::MyIdentity(matScale);

	matScale->_11 = fX;
	matScale->_22 = fY;
	matScale->_33 = fZ;
}

void Engine::CMathMgr::MyScaling(D3DXMATRIX* matScale, D3DXVECTOR3* vScale)
{
	CMathMgr::MyIdentity(matScale);

	matScale->_11 = vScale->x;
	matScale->_22 = vScale->y;
	matScale->_33 = vScale->z;
}

//// 수업소스

void Engine::CMathMgr::MyRotationX(D3DXVECTOR3* pOut, D3DXVECTOR3* pIn, float fAngle)
{
	/*
	1	0	0	0
	0   c   s   0
	0  -s	c   0
	0	0	0	1
	*/

	D3DXVECTOR3	vTemp = *pIn;

	pOut->x = vTemp.x;
	pOut->y = vTemp.y * cosf(fAngle) - vTemp.z * sinf(fAngle);
	pOut->z = vTemp.y * sinf(fAngle) + vTemp.z * cosf(fAngle);

}

void Engine::CMathMgr::MyRotationY(D3DXVECTOR3* pOut, D3DXVECTOR3* pIn, float fAngle)
{
	/*
	c	0	-s	0
	0   1   0   0
	s   0	c   0
	0	0	0	1
	*/

	D3DXVECTOR3	vTemp = *pIn;

	pOut->x = vTemp.x * cosf(fAngle) + vTemp.z * sinf(fAngle);
	pOut->y = vTemp.y;
	pOut->z = vTemp.x * -sinf(fAngle) + vTemp.z * cosf(fAngle);
}

void Engine::CMathMgr::MyRotationZ(D3DXVECTOR3* pOut, D3DXVECTOR3* pIn, float fAngle)
{
	/*
	c	s	0	0
	-s  c   0   0
	0   0	1   0
	0	0	0	1
	*/

	D3DXVECTOR3	vTemp = *pIn;

	pOut->x = vTemp.x * cosf(fAngle) - vTemp.y * sinf(fAngle);
	pOut->y = vTemp.x * sinf(fAngle) + vTemp.y * cosf(fAngle);
	pOut->z = vTemp.z;
}


//// Test
void Engine::CMathMgr::MyRotationX(D3DXMATRIX* matRotX, float fAngle)
{
	CMathMgr::MyIdentity(matRotX);

	D3DXVECTOR3 vTemp;

	matRotX->_12 = cosf(fAngle);
	matRotX->_13 = sinf(fAngle);
	matRotX->_22 = -sinf(fAngle);
	matRotX->_23 = cosf(fAngle);
}

void Engine::CMathMgr::MyRotationY(D3DXMATRIX* matRotY, float fAngle)
{
	CMathMgr::MyIdentity(matRotY);

	matRotY->_11 = cosf(fAngle);
	matRotY->_13 = -sinf(fAngle);
	matRotY->_31 = sinf(fAngle);
	matRotY->_33 = cosf(fAngle);
}

void Engine::CMathMgr::MyRotationZ(D3DXMATRIX* matRotZ, float fAngle)
{
	CMathMgr::MyIdentity(matRotZ);

	matRotZ->_11 = cosf(fAngle);
	matRotZ->_12 = sinf(fAngle);
	matRotZ->_21 = -sinf(fAngle);
	matRotZ->_22 = cosf(fAngle);
}

void Engine::CMathMgr::MyTranslation(D3DXMATRIX* matTrans, D3DXVECTOR3* vTrans)
{
	CMathMgr::MyIdentity(matTrans);

	matTrans->_41 = vTrans->x;
	matTrans->_42 = vTrans->y;
	matTrans->_43 = vTrans->z;

}
