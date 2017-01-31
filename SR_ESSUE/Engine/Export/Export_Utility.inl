CManagement* Get_Management(void)
{
	return CManagement::GetInstance();
}

CInfoSubject* Get_InfoSubject(void)
{
	return CInfoSubject::GetInstance();
}

CStatSubject* Get_StatSubject(void)
{
	return CStatSubject::GetInstance();
}

void MyTransformCoord(D3DXVECTOR3* vOut, const D3DXVECTOR3* vVec, const D3DXMATRIX* matWorld)
{
	D3DXVECTOR3 vTemp;

	vTemp.x = (vVec->x * matWorld->_11) + (vVec->y * matWorld->_21) + (vVec->z * matWorld->_31) + matWorld->_41;
	vTemp.y = (vVec->x * matWorld->_12) + (vVec->y * matWorld->_22) + (vVec->z * matWorld->_32) + matWorld->_42;
	vTemp.z = (vVec->x * matWorld->_13) + (vVec->y * matWorld->_23) + (vVec->z * matWorld->_33) + matWorld->_43;
	float w = (vVec->x * matWorld->_14) + (vVec->y * matWorld->_24) + (vVec->z * matWorld->_34) + matWorld->_44;

	vTemp.x = vTemp.x / w;
	vTemp.y = vTemp.y / w;
	vTemp.z = vTemp.z / w;

	*vOut = vTemp;

}

void MyIdentity(D3DXMATRIX* matWorld)
{
	ZeroMemory(matWorld, sizeof(D3DXMATRIX));

	matWorld->_11 = matWorld->_22 = matWorld->_33 = matWorld->_44 = 1; 
}


float MyLength(const D3DXVECTOR3* vDest, const D3DXVECTOR3* vDepa)
{
	D3DXVECTOR3 vTemp = *vDest - *vDepa;

	float fDistance = sqrt((vTemp.x * vTemp.x) + (vTemp.y * vTemp.y) + (vTemp.z * vTemp.z));

	return fDistance;
}

void MyNormalize(D3DXVECTOR3* vOut, D3DXVECTOR3* vIn)
{
	float fDistance = sqrt((vIn->x * vIn->x) + (vIn->y * vIn->y) + (vIn->z * vIn->z));

	vOut->x = vIn->x / fDistance;
	vOut->y = vIn->y / fDistance;
	vOut->z = vIn->z / fDistance;
}

float MyDot(D3DXVECTOR3* vDest, D3DXVECTOR3* vDepa)
{
	float fDot = (vDest->x * vDepa->x) + (vDest->y * vDepa->y) + (vDest->z * vDepa->z);

	return fDot;
}

D3DXVECTOR3 MyCross(D3DXVECTOR3* vDest, D3DXVECTOR3* vDepa)
{
	D3DXVECTOR3 vTemp = D3DXVECTOR3(0.f, 0.f, 0.f);

	vTemp.x = (vDest->y * vDepa->z) - (vDest->z * vDepa->y);
	vTemp.y = (vDest->z * vDepa->x) - (vDest->x * vDepa->z);
	vTemp.z = (vDest->x * vDepa->y) - (vDest->y * vDepa->x);

	return vTemp;
}