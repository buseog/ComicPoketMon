/*!
 * \file Item.h
 * \date 2017/01/15 15:10
 *
 * \author ESSUE
 * Contact: user@company.com
 *
 * \brief ������Ŭ����
 *
 * TODO: long description
 *
 * \note �κ��丮�� �������� �������� ����, ���������� ���� ����� ������ ����.
         ������ �༭ ���°��� ���� ��Ÿ���� ������ �ٸ��� �ϸ� ����������
*/

#ifndef Item_h__
#define Item_h__

#include "UI.h"
#include "Include.h"
namespace Engine
{
	class CResourceMgr;
	class CTexture;
	class CVIBuffer;
}


class CItem
	: public Engine::CUI
{
private:
	Engine::CResourceMgr*		m_pResourceMgr;
	Engine::CVIBuffer*			m_pBuffer;
	Engine::CTexture*			m_pTexture;

private:
	Engine::VTXTEX*				m_pVertex;
	Engine::VTXTEX*				m_pConvertVertex;
	DWORD						m_dwVtxCnt;

	int							m_iType;

	ITEMID						m_eId;

public:
	void Release(void);
	void SetTransform(void);
	void SetPos(float fX, float fY);
	ITEMID	GetId(void);

	void	SetType(int Type);
	int		GetType(void);

public:
	virtual HRESULT Initialize( ITEMID Id);
	virtual void Update( void );
	virtual void Render( void );
	HRESULT				AddComponent(ITEMID ID);

public:
	static CItem* Create(LPDIRECT3DDEVICE9 pDevice, ITEMID ID);

private:
	explicit CItem(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CItem(void);


};


#endif // Item_h__