#ifndef TerrainCenter_h__
#define TerrainCenter_h__

#include "SingleGameObject.h"
#include "ZQuadTree.h"

class CTerrainCenter 
	: public CSingleGameObject
{
	// �ø���
private:
	int		m_IBCX;	// �ε��� ���� ����
	int		m_ICBY;	// �ε��� ���� ����
	int		m_IBCZ;	// �ε��� ���� ����

	D3DXVECTOR3	m_vScale; // ������
	LPDIRECT3DVERTEXBUFFER9	m_pVB;	// ���ؽ�����
	LPDIRECT3DINDEXBUFFER9	m_pIB;	// �ε�������

	int				m_iTriangles;	// ����� �ﰢ����
	CZQuadTree*		m_pQuadTree;	// ����Ʈ��

public:
	HRESULT		BuildQuadTree(void);


private:
	Engine::VTXTEX*				m_pVertex;
	Engine::VTXTEX*				m_pConvertVertex;

private:
	HRESULT				Initialize(void);
	void				DataLoad(void);
	void				SetTransform(void);

public:
	void				Update(void);
	void				Render(void);
	void				Release(void);
	HRESULT				AddComponent(void);

	virtual const Engine::VTXTEX* GetTerrainVertex(void);

public:
	static	CTerrainCenter*	Create(LPDIRECT3DDEVICE9 pDevice);

private:
	explicit	CTerrainCenter(LPDIRECT3DDEVICE9 pDevice);
public:
	~CTerrainCenter(void);

};
#endif // TerrainCenter_h__
