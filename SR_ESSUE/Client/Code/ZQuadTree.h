/*!
 * \file ZQuadTree.h
 * \date 2017/01/20 5:49
 *
 * \author ESSUE
 * Contact: user@company.com
 *
 * \brief ������ �ø��ϱ����� ����Ʈ��
 *
 * TODO: long description
 *
 * \note ����Ʈ���� �̿��� ������ ���� ��ƸԴ� �ͷ����� ������ �����ս��� �ø� ����
*/

#ifndef ZQuadTree_h__
#define ZQuadTree_h__

#include "Engine_Include.h"

class CZQuadTree
{
	// ����Ʈ���� �����Ǵ� 4�� �ڳʰ��� ���� �̳Ѱ�
	enum	CornerType { CORNER_TL, CORNER_TR, CORNER_BL, CORNER_BR};

private:
	CZQuadTree*		m_pChild[4];	 // 4���� �ڽĳ��

	int				m_iCenter;		// ������ ù��° ��
	int				m_iCorner[4];	// ������ �ι�° ��
	bool			m_bCull;		// �ø� Ȯ�ο� ����
private:
	CZQuadTree*	AddChild(int iCornerTL, int iCornerTR, int iCornerBL, int iCornerBR);	// �ڽ� ��带 �߰�
	BOOL		SetCorners(int iCornerTL, int iCornerTR, int iCornerBL, int iCornerBR);	// 4���� �ڳʰ��� ����
	BOOL		SubDivide(void);														// 4���� ����Ʈ���� �κк�����.
	BOOL		IsVisible(void);														// ��� ������ �������
	int			GenTriIdnex(int iTriangles, LPVOID pIndex);								// ����� �������� �ε����� ������
	void		Destroy(void);															// �޸𸮿��� Ʈ���� ����
	
public:
	BOOL		Build(void);															// ����Ʈ���� ����
	int			GenerateIndex(LPVOID pIB);												// �ﰢ���� �ε����� �����, ����� ���ڸ� ��ȯ
	
	void		IsInFrustum();
	void		FrustumCull();

public:
	CZQuadTree(int iCX, int iCZ);		// ��Ʈ���
	CZQuadTree(CZQuadTree*	pParent);	// �ڽĳ��
	~CZQuadTree(void);
};

#endif // ZQuadTree_h__