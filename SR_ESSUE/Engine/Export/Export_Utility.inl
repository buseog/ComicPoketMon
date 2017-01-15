CManagement* Get_Management(void)
{
	return CManagement::GetInstance();
}

CInfoSubject* Get_InfoSubject(void)
{
	return CInfoSubject::GetInstance();
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