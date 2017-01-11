#include "StdAfx.h"
#include "ObjBack.h"
#include "Resources.h"
#include "VIBuffer.h"
#include "Include.h"
#include "..\Include\MainFrm.h"

#include "Texture.h"
#include "CubeObj.h"
#include "CubeCol.h"



CObjBack::CObjBack(LPDIRECT3DDEVICE9 pDevice)
: CGameObject(pDevice)
, m_pBuffer(NULL)
, m_fDistance(0)
{

}

CObjBack::~CObjBack(void)
{
	Release();
}

void CObjBack::Release( void )
{
	for (list<Engine::CComponent*>::iterator iter = m_pCubeList.begin(); iter != m_pCubeList.end(); ++iter)
	{
		Engine::Safe_Delete(*iter);
	}
	m_pCubeList.clear();
}

void CObjBack::KeyCheck( void )
{
	if(GetAsyncKeyState('W') & 0x8000)
	{
		m_fDistance -= 1.f;
		D3DXVec3Normalize(&m_vAt, &m_vAt);
		m_vEye = m_vAt * -m_fDistance;
	}

	if(GetAsyncKeyState('S') & 0x8000)
	{
		m_fDistance += 1.f;
		D3DXVec3Normalize(&m_vAt, &m_vAt);
		m_vEye = m_vAt * -m_fDistance;
	}

	/*if(GetAsyncKeyState('A') & 0x8000)
	{
		m_vAt.x -= 5;
		D3DXVec3Normalize(&m_vAt, &m_vAt);
		m_vEye = m_vAt * -m_fDistance;
	}

	if(GetAsyncKeyState('D') & 0x8000)
	{
		m_vAt.x += 5;
		D3DXVec3Normalize(&m_vAt, &m_vAt);
		m_vEye = m_vAt * -m_fDistance;
	}*/

	if(GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_fAngle[Engine::ANGLE_Y] = D3DXToRadian(-5.f);
		D3DXMATRIX matRotY;
		D3DXMatrixRotationY(&matRotY, m_fAngle[Engine::ANGLE_Y]);
		D3DXVec3TransformNormal(&m_vAt, &m_vAt, &matRotY);
		D3DXVec3Normalize(&m_vAt, &m_vAt);
		m_vEye = -m_vAt * m_fDistance;
	}

	if(GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_fAngle[Engine::ANGLE_Y] = D3DXToRadian(5.f);
		D3DXMATRIX matRotY;
		D3DXMatrixRotationY(&matRotY, m_fAngle[Engine::ANGLE_Y]);
		D3DXVec3TransformNormal(&m_vAt, &m_vAt, &matRotY);
		D3DXVec3Normalize(&m_vAt, &m_vAt);
		m_vEye = -m_vAt * m_fDistance;
	}

	if(GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_fAngle[Engine::ANGLE_X] = D3DXToRadian(5.f);
		D3DXMATRIX matAxis;
		D3DXVECTOR3 vDirX;
		D3DXVec3Cross(&vDirX, &D3DXVECTOR3(0.f, 1.f, 0.f), &m_vAt);
		D3DXMatrixRotationAxis(&matAxis, &vDirX, m_fAngle[Engine::ANGLE_X]);
		D3DXVec3TransformNormal(&m_vAt, &m_vAt, &matAxis);
		m_vEye = -m_vAt * m_fDistance;

	}

	if(GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_fAngle[Engine::ANGLE_X] = D3DXToRadian(-5.f);
		D3DXMATRIX matAxis;
		D3DXVECTOR3 vDirX;
		D3DXVec3Cross(&vDirX, &D3DXVECTOR3(0.f, 1.f, 0.f), &m_vAt);
		D3DXMatrixRotationAxis(&matAxis, &vDirX, m_fAngle[Engine::ANGLE_X]);
		D3DXVec3TransformNormal(&m_vAt, &m_vAt, &matAxis);
		m_vEye = -m_vAt * m_fDistance;
	}

	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vAt, &D3DXVECTOR3(0.f,1.f,0.f));
	m_pDevice->SetTransform(D3DTS_VIEW, &matView);
}

void CObjBack::DeletePicking( void )
{
	POINT	pt;

	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	D3DXMATRIX matRView, matRProj;

	D3DXVECTOR3 vMouse;

	vMouse.x = (float(pt.x)  / (WINCX / 2) - 1.f) / matProj._11;
	vMouse.y = (float(-pt.y) / (WINCY / 2) + 1.f) / matProj._22;
	vMouse.z = 1.f;

	D3DXVECTOR3 vRayPos, vRayDir;
	vRayPos = D3DXVECTOR3(0.f,0.f,0.f);
	vRayDir = vMouse;

	D3DXMatrixInverse(&matRView, 0, &matView);
	D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matRView);
	D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matRView);

	D3DXMATRIX matRWorld;
	D3DXMatrixIdentity(&matRWorld);
	D3DXMatrixInverse(&matRWorld, 0, &matRWorld);
	D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matRWorld);
	D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matRWorld);


	float	fU, fV, fDist;
	Engine::VTXCOL*		pVertex = new Engine::VTXCOL[8];
	Engine::INDEX32*	pIndex = new Engine::INDEX32[12];

	for (list<Engine::CComponent*>::iterator iter = m_pCubeList.begin(); iter != m_pCubeList.end(); ++iter)
	{
		((Engine::CVIBuffer*)*iter)->GetVtxInfo(pVertex);
		((Engine::CVIBuffer*)*iter)->GetIdxInfo(pIndex);

		for (int i = 0; i < 12; ++i)
		{
			if(D3DXIntersectTri(&pVertex[pIndex[i]._2].vPos, &pVertex[pIndex[i]._1].vPos,	&pVertex[pIndex[i]._3].vPos,
				&vRayPos, &vRayDir, &fU, &fV, &fDist))
			{
				Engine::Safe_Delete(*iter);
				iter = m_pCubeList.erase(iter);
				
				return;
			}
		}
	}
}

void CObjBack::AddPicking( void )
{
	POINT	pt;

	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	D3DXMATRIX matRView, matRProj;

	D3DXVECTOR3 vMouse;

	vMouse.x = (float(pt.x)  / (WINCX / 2) - 1.f) / matProj._11;
	vMouse.y = (float(-pt.y) / (WINCY / 2) + 1.f) / matProj._22;
	vMouse.z = 1.f;

	D3DXVECTOR3 vRayPos, vRayDir;
	vRayPos = D3DXVECTOR3(0.f,0.f,0.f);
	vRayDir = vMouse;

	D3DXMatrixInverse(&matRView, 0, &matView);
	D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matRView);
	D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matRView);

	D3DXMATRIX matRWorld;
	D3DXMatrixIdentity(&matRWorld);
	D3DXMatrixInverse(&matRWorld, 0, &matRWorld);
	D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matRWorld);
	D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matRWorld);


	float	fU, fV, fDist;
	Engine::VTXCOL*		pVertex = new Engine::VTXCOL[8];
	Engine::INDEX32*	pIndex = new Engine::INDEX32[12];

	for (list<Engine::CComponent*>::iterator iter = m_pCubeList.begin(); iter != m_pCubeList.end(); ++iter)
	{
		((Engine::CVIBuffer*)*iter)->GetVtxInfo(pVertex);
		((Engine::CVIBuffer*)*iter)->GetIdxInfo(pIndex);

		for (int i = 0; i < 12; ++i)
		{
			if(D3DXIntersectTri(&pVertex[pIndex[i]._2].vPos, &pVertex[pIndex[i]._1].vPos,	&pVertex[pIndex[i]._3].vPos,
				&vRayPos, &vRayDir, &fU, &fV, &fDist))
			{
				if (i <= 1)
				{
					m_pCubeList.push_back(Engine::CCubeCol::Create(m_pDevice));
					Engine::VTXCOL*		pNew = new Engine::VTXCOL[8];
					((Engine::CVIBuffer*)m_pCubeList.back())->GetVtxInfo(pNew);

					for (int p = 0; p < 8 ; ++p)
						pNew[p].vPos = pVertex[p].vPos + D3DXVECTOR3(2.f, 0.f, 0.f);

					((Engine::CVIBuffer*)m_pCubeList.back())->SetVtxInfo(pNew);
					((Engine::CVIBuffer*)m_pCubeList.back())->SetOriginVtxInfo(pNew);

				}
				else if (i <= 3)
				{
					m_pCubeList.push_back(Engine::CCubeCol::Create(m_pDevice));
					Engine::VTXCOL*		pNew = new Engine::VTXCOL[8];
					((Engine::CVIBuffer*)m_pCubeList.back())->GetVtxInfo(pNew);

					for (int p = 0; p < 8 ; ++p)
						pNew[p].vPos = pVertex[p].vPos + D3DXVECTOR3(-2.f, 0.f, 0.f);

					((Engine::CVIBuffer*)m_pCubeList.back())->SetVtxInfo(pNew);
					((Engine::CVIBuffer*)m_pCubeList.back())->SetOriginVtxInfo(pNew);
				}

				else if (i <= 5)
				{
					m_pCubeList.push_back(Engine::CCubeCol::Create(m_pDevice));
					Engine::VTXCOL*		pNew = new Engine::VTXCOL[8];
					((Engine::CVIBuffer*)m_pCubeList.back())->GetVtxInfo(pNew);

					for (int p = 0; p < 8 ; ++p)
						pNew[p].vPos = pVertex[p].vPos + D3DXVECTOR3(0.f, 2.f, 0.f);

					((Engine::CVIBuffer*)m_pCubeList.back())->SetVtxInfo(pNew);
					((Engine::CVIBuffer*)m_pCubeList.back())->SetOriginVtxInfo(pNew);
				}

				else if (i <= 7)
				{
					m_pCubeList.push_back(Engine::CCubeCol::Create(m_pDevice));
					Engine::VTXCOL*		pNew = new Engine::VTXCOL[8];
					((Engine::CVIBuffer*)m_pCubeList.back())->GetVtxInfo(pNew);

					for (int p = 0; p < 8 ; ++p)
						pNew[p].vPos = pVertex[p].vPos + D3DXVECTOR3(0.f, -2.f, 0.f);

					((Engine::CVIBuffer*)m_pCubeList.back())->SetVtxInfo(pNew);
					((Engine::CVIBuffer*)m_pCubeList.back())->SetOriginVtxInfo(pNew);
				}

				else if (i <= 9)
				{
					m_pCubeList.push_back(Engine::CCubeCol::Create(m_pDevice));
					Engine::VTXCOL*		pNew = new Engine::VTXCOL[8];
					((Engine::CVIBuffer*)m_pCubeList.back())->GetVtxInfo(pNew);

					for (int p = 0; p < 8 ; ++p)
						pNew[p].vPos = pVertex[p].vPos + D3DXVECTOR3(0.f, 0.f, 2.f);

					((Engine::CVIBuffer*)m_pCubeList.back())->SetVtxInfo(pNew);
					((Engine::CVIBuffer*)m_pCubeList.back())->SetOriginVtxInfo(pNew);
				}

				else if (i <= 11)
				{
					m_pCubeList.push_back(Engine::CCubeCol::Create(m_pDevice));
					Engine::VTXCOL*		pNew = new Engine::VTXCOL[8];
					((Engine::CVIBuffer*)m_pCubeList.back())->GetVtxInfo(pNew);

					for (int p = 0; p < 8 ; ++p)
						pNew[p].vPos = pVertex[p].vPos + D3DXVECTOR3(0.f, 0.f, -2.f);

					((Engine::CVIBuffer*)m_pCubeList.back())->SetVtxInfo(pNew);
					((Engine::CVIBuffer*)m_pCubeList.back())->SetOriginVtxInfo(pNew);
				}
				return;
			}
		}
	}
}

void CObjBack::SelectPicking( void )
{
	POINT	pt;

	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	D3DXMATRIX matRView, matRProj;

	D3DXVECTOR3 vMouse;

	vMouse.x = (float(pt.x)  / (WINCX / 2) - 1.f) / matProj._11;
	vMouse.y = (float(-pt.y) / (WINCY / 2) + 1.f) / matProj._22;
	vMouse.z = 1.f;

	D3DXVECTOR3 vRayPos, vRayDir;
	vRayPos = D3DXVECTOR3(0.f,0.f,0.f);
	vRayDir = vMouse;

	D3DXMatrixInverse(&matRView, 0, &matView);
	D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matRView);
	D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matRView);

	D3DXMATRIX matRWorld;
	D3DXMatrixIdentity(&matRWorld);
	D3DXMatrixInverse(&matRWorld, 0, &matRWorld);
	D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matRWorld);
	D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matRWorld);


	float	fU, fV, fDist;
	Engine::VTXCOL*		pVertex = new Engine::VTXCOL[8];
	Engine::INDEX32*	pIndex = new Engine::INDEX32[12];

	for (list<Engine::CComponent*>::iterator iter = m_pCubeList.begin(); iter != m_pCubeList.end(); ++iter)
	{
		((Engine::CVIBuffer*)*iter)->GetVtxInfo(pVertex);
		((Engine::CVIBuffer*)*iter)->GetIdxInfo(pIndex);

		for (int i = 0; i < 12; ++i)
		{
			if(D3DXIntersectTri(&pVertex[pIndex[i]._2].vPos, &pVertex[pIndex[i]._1].vPos,	&pVertex[pIndex[i]._3].vPos,
				&vRayPos, &vRayDir, &fU, &fV, &fDist))
			{
				m_pBuffer = dynamic_cast<Engine::CVIBuffer*>(*iter);
				D3DXVECTOR3 vTemp;
				vTemp.x = (pVertex[0].vPos.x + pVertex[1].vPos.x) / 2;
				vTemp.y = (pVertex[0].vPos.y + pVertex[3].vPos.y) / 2;
				vTemp.z = (pVertex[0].vPos.z + pVertex[5].vPos.z) / 2;
				
				((CMainFrame*)AfxGetMainWnd())->m_pMainForm->m_pUnit.SetPos(vTemp);

				return;
			}
		}
	}
}

void CObjBack::SetTransCube( D3DXVECTOR3 vPos )
{
	if (m_pBuffer == NULL)
		return;

	Engine::VTXCOL*		pVertex = new Engine::VTXCOL[8];
	((Engine::CVIBuffer*)m_pBuffer)->GetVtxInfo(pVertex);

	pVertex[0].vPos = D3DXVECTOR3(-1.f, 1.f, -1.f) + vPos;

	pVertex[1].vPos = D3DXVECTOR3(1.f, 1.f ,-1.f) + vPos;

	pVertex[2].vPos = D3DXVECTOR3(1.f, -1.f ,-1.f) + vPos;

	pVertex[3].vPos = D3DXVECTOR3(-1.f, -1.f ,-1.f) + vPos;

	pVertex[4].vPos = D3DXVECTOR3(-1.f, 1.f ,1.f) + vPos;

	pVertex[5].vPos = D3DXVECTOR3(1.f, 1.f ,1.f) + vPos;

	pVertex[6].vPos = D3DXVECTOR3(1.f, -1.f ,1.f) + vPos;

	pVertex[7].vPos = D3DXVECTOR3(-1.f, -1.f ,1.f) + vPos;

	((Engine::CVIBuffer*)m_pBuffer)->SetVtxInfo(pVertex);
}

void CObjBack::DrawLine( void )
{
	D3DXMATRIX	matWorld;
	D3DXMatrixIdentity(&matWorld);
	matWorld = matView * matProj;

	D3DXCreateLine(m_pDevice, &m_pLine);

	m_pLine->SetWidth(5.f);
	m_pLine->SetAntialias(TRUE);
	m_pLine->Begin();

	D3DXVECTOR3 vLinePosX[2] = {D3DXVECTOR3(-0.01f, 0.f, 0.f), D3DXVECTOR3(2.f, 0.f, 0.f)};
	m_pLine->DrawTransform(vLinePosX, 2, &matWorld, 0xff0000ff);

	m_pLine->End();
	m_pLine->Release();

	D3DXCreateLine(m_pDevice, &m_pLine);
	m_pLine->SetWidth(5.f);
	m_pLine->SetAntialias(TRUE);
	m_pLine->Begin();

	D3DXVECTOR3 vLinePosY[2] = {D3DXVECTOR3(0.f, -0.01f, 0.f), D3DXVECTOR3(0.f, 2.f, 0.f)};
	m_pLine->DrawTransform(vLinePosY, 2, &matWorld, 0xffff0000);

	m_pLine->End();
	m_pLine->Release();

	D3DXCreateLine(m_pDevice, &m_pLine);
	m_pLine->SetWidth(5.f);
	m_pLine->SetAntialias(TRUE);
	m_pLine->Begin();

	D3DXVECTOR3 vLinePosZ[2] = {D3DXVECTOR3(0.f, 0.f, -0.01f), D3DXVECTOR3(0.f, 0.f, 2.f)};
	m_pLine->DrawTransform(vLinePosZ, 2, &matWorld, 0xff00ff00);

	m_pLine->End();
	m_pLine->Release();
}

void CObjBack::AddObject( wstring wstrTetureKey, D3DXVECTOR3 vScale, D3DXVECTOR3 vPos)
{
	Engine::CComponent*		pResources = NULL;

	pResources = Engine::CCubeCol::Create(m_pDevice);

	m_pBuffer = dynamic_cast<Engine::CVIBuffer*>(pResources);

	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Col Cube3", pResources));	

	//Engine::CCubeCol::Create(m_pDevice, D3DXVECTOR3(pVertex[pIndex[i]._1].vPos.x, 0.f, 0.f))
}

HRESULT CObjBack::Initialize( void )
{
	m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	ZeroMemory(m_fAngle, sizeof(float) * 3);
	m_fDistance = 10.f;

	D3DXMatrixIdentity(&matView);
	D3DXMatrixIdentity(&matProj);

	m_vEye = D3DXVECTOR3(0.f, 10.f, -1.f);
	m_vAt = D3DXVECTOR3(0.f, -1.f, 1.f);
	D3DXVec3Normalize(&m_vAt, &m_vAt);

	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vAt, &D3DXVECTOR3(0.f, 1.f, 0.f));

	m_pDevice->SetTransform(D3DTS_VIEW, &matView);

	// 투영행렬 함수
	D3DXMatrixPerspectiveFovLH(&matProj, 
		D3DXToRadian(45.f),					// fovY 값
		float(WINCX) / float(WINCY),		// Aspect값
		1.f,								// near 평면의 z값
		1000.f);							// far 평면의 z값

	m_pDevice->SetTransform(D3DTS_PROJECTION, &matProj);

	Engine::CComponent*		pResources = NULL;

	pResources = Engine::CCubeCol::Create(m_pDevice);

	m_pBuffer = dynamic_cast<Engine::CVIBuffer*>(pResources);

	m_pCubeList.push_back(pResources);	

	DrawLine();

	return S_OK;
}

void CObjBack::Update( void )
{

}

void CObjBack::Render( void )
{
	for (list<Engine::CComponent*>::iterator iter = m_pCubeList.begin(); iter != m_pCubeList.end(); ++iter)
		((Engine::CVIBuffer*)(*iter))->Render();
}

CObjBack* CObjBack::Create( LPDIRECT3DDEVICE9 pDevice )
{
	CObjBack* pBack = new CObjBack(pDevice);

	if (FAILED(pBack->Initialize()))
		Engine::Safe_Delete(pBack);

	return pBack;
}

