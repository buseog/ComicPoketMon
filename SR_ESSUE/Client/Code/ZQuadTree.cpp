#include "StdAfx.h"
#include "ZQuadTree.h"

CZQuadTree::CZQuadTree( int iCX, int iCZ )
{
	ZeroMemory(m_iCorner, sizeof(int) * 4);
	m_iCenter = 0;
	
	m_iCorner[CORNER_TL] = iCX * (iCZ - 1);
	m_iCorner[CORNER_TR] = iCX * iCZ - 1;
	m_iCorner[CORNER_BL] = 0;
	m_iCorner[CORNER_BR] = iCX - 1;

	m_iCenter = (m_iCorner[CORNER_TL] + m_iCorner[CORNER_TR] + m_iCorner[CORNER_BL] + m_iCorner[CORNER_BR]) / 4;
}

CZQuadTree::CZQuadTree( CZQuadTree* pParent )
{
	m_iCenter = 0;

	for (int i = 0; i < 4; ++i)
	{
		m_pChild[i] = NULL;
		m_iCorner[i] = 0;
	}
}

CZQuadTree::~CZQuadTree( void )
{
	Destroy();
}

void CZQuadTree::Destroy( void )
{
	for (int i = 0; i < 4; ++i)
		Engine::Safe_Delete(m_pChild[i]);
}

BOOL CZQuadTree::SetCorners( int iCornerTL, int iCornerTR, int iCornerBL, int iCornerBR )
{
	m_iCorner[CORNER_TL] = iCornerTL;
	m_iCorner[CORNER_TR] = iCornerTR;
	m_iCorner[CORNER_BL] = iCornerBL;
	m_iCorner[CORNER_BR] = iCornerBR;

	m_iCenter = (m_iCorner[CORNER_TL] + m_iCorner[CORNER_TR] + m_iCorner[CORNER_BL] + m_iCorner[CORNER_BR]) / 4;

	return TRUE;
}

CZQuadTree* CZQuadTree::AddChild( int iCornerTL, int iCornerTR, int iCornerBL, int iCornerBR )
{
	CZQuadTree*	pChild = new CZQuadTree(this);

	pChild->SetCorners(iCornerTL, iCornerTR, iCornerBL, iCornerBR);

	return pChild;
}

BOOL CZQuadTree::SubDivide( void )
{
	int iTopCenter;
	int	iBottomCenter;
	int	iLeftCenter;
	int	iRightCenter;
	int	iCenterPoint;

	iTopCenter =		(m_iCorner[CORNER_TL] +	m_iCorner[CORNER_TR]) / 2;	// 상
	iBottomCenter =		(m_iCorner[CORNER_BL] +	m_iCorner[CORNER_BR]) / 2;	// 하
	iLeftCenter =		(m_iCorner[CORNER_TL] +	m_iCorner[CORNER_BL]) / 2;	// 좌
	iRightCenter =		(m_iCorner[CORNER_TR] +	m_iCorner[CORNER_BR]) / 2;	// 우
	iCenterPoint =		(m_iCorner[CORNER_TL] +	m_iCorner[CORNER_TR] + m_iCorner[CORNER_BL] + m_iCorner[CORNER_BR]) / 4; // 센터

	if (m_iCorner[CORNER_BR] - m_iCorner[CORNER_BL] <= 1)
		return FALSE;

	m_pChild[CORNER_TL] = AddChild(m_iCorner[CORNER_TL], iTopCenter, iLeftCenter, iCenterPoint);
	m_pChild[CORNER_TR] = AddChild(iTopCenter, m_iCorner[CORNER_TR], iCenterPoint, iRightCenter);
	m_pChild[CORNER_BL] = AddChild(iRightCenter, iCenterPoint, m_iCorner[CORNER_BL], iBottomCenter);
	m_pChild[CORNER_BR] = AddChild(iCenterPoint, iRightCenter, iBottomCenter, m_iCorner[CORNER_BR]);

	return TRUE;
}

int CZQuadTree::GenTriIdnex( int iTriangles, LPVOID pIndex )
{
	if (IsVisible())
	{
		LPWORD p = ((LPWORD)pIndex) + iTriangles + 3;

		*p++ = m_iCorner[0];
		*p++ = m_iCorner[1];
		*p++ = m_iCorner[2];
		iTriangles++;

		*p++ = m_iCorner[0];
		*p++ = m_iCorner[2];
		*p++ = m_iCorner[3];
		iTriangles++;

		return iTriangles;
	}

	if (m_pChild[CORNER_TL])
		iTriangles = m_pChild[CORNER_TL]->GenTriIdnex(iTriangles, pIndex);

	if (m_pChild[CORNER_TR])
		iTriangles = m_pChild[CORNER_TR]->GenTriIdnex(iTriangles, pIndex);

	if (m_pChild[CORNER_BL])
		iTriangles = m_pChild[CORNER_BL]->GenTriIdnex(iTriangles, pIndex);

	if (m_pChild[CORNER_BR])
		iTriangles = m_pChild[CORNER_BR]->GenTriIdnex(iTriangles, pIndex);

	return iTriangles;
}

BOOL CZQuadTree::Build( void )
{
	if (SubDivide())
	{	
		m_pChild[CORNER_TL]->Build();
		m_pChild[CORNER_TR]->Build();
		m_pChild[CORNER_BL]->Build();
		m_pChild[CORNER_BR]->Build();
	}

	return TRUE;
}

int CZQuadTree::GenerateIndex( LPVOID pIB )
{
	return GenTriIdnex(0, pIB);
}

BOOL CZQuadTree::IsVisible( void )
{
	return (m_iCorner[CORNER_TR] - m_iCorner[CORNER_TL] <= 1);
}
