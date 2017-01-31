/*!
 * \file ZQuadTree.h
 * \date 2017/01/20 5:49
 *
 * \author ESSUE
 * Contact: user@company.com
 *
 * \brief 지형을 컬링하기위한 쿼드트리
 *
 * TODO: long description
 *
 * \note 쿼드트리를 이용해 연산을 많이 잡아먹는 터레인을 제어해 퍼포먼스를 올릴 예정
*/

#ifndef ZQuadTree_h__
#define ZQuadTree_h__

#include "Engine_Include.h"

class CZQuadTree
{
	// 쿼드트리에 보관되는 4개 코너값에 대한 이넘값
	enum	CornerType { CORNER_TL, CORNER_TR, CORNER_BL, CORNER_BR};

private:
	CZQuadTree*		m_pChild[4];	 // 4개의 자식노드

	int				m_iCenter;		// 보관할 첫번째 값
	int				m_iCorner[4];	// 보관할 두번째 값
	bool			m_bCull;		// 컬링 확인용 변수
private:
	CZQuadTree*	AddChild(int iCornerTL, int iCornerTR, int iCornerBL, int iCornerBR);	// 자식 노드를 추가
	BOOL		SetCorners(int iCornerTL, int iCornerTR, int iCornerBL, int iCornerBR);	// 4개의 코너값을 세팅
	BOOL		SubDivide(void);														// 4개의 하위트리로 부분분할함.
	BOOL		IsVisible(void);														// 출력 가능한 노드인지
	int			GenTriIdnex(int iTriangles, LPVOID pIndex);								// 출력할 폴리곤의 인덱스를 생성함
	void		Destroy(void);															// 메모리에서 트리를 삭제
	
public:
	BOOL		Build(void);															// 쿼드트리를 구축
	int			GenerateIndex(LPVOID pIB);												// 삼각형의 인덱스를 만들고, 출력할 숫자를 반환
	
	void		IsInFrustum();
	void		FrustumCull();

public:
	CZQuadTree(int iCX, int iCZ);		// 루트노드
	CZQuadTree(CZQuadTree*	pParent);	// 자식노드
	~CZQuadTree(void);
};

#endif // ZQuadTree_h__