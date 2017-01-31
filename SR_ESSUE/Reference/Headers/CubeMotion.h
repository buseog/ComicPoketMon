/*!
 * \file CCubeMotion.h
 * \date 2017/01/13 2:09
 *
 * \author ESSUE
 * Contact: user@company.com
 *
 * \brief 큐브객체를 스프라이트 형식으로 가지는 리소스
 *
 * TODO: long description
 *
 * \note
*/

#ifndef CCubeMotion_h__
#define CCubeMotion_h__

#include "Resources.h"

namespace Engine
{
	class CCubeObj;
}

BEGIN(Engine)

class ENGINE_DLL CCubeMotion
	:public CResources
{
private:
	typedef vector<Engine::CCubeObj*>	VECVERTEX;
	typedef map<wstring, VECVERTEX>		MAPVECTOR;
	MAPVECTOR							m_SpriteMap;
	wstring								m_wstrKey;

public:
	void		AddSprite(const wstring& wstrName, Engine::CCubeObj* pComponent);
	void		RemoveSprite(const wstring& wstrName);
	MAPVECTOR*	GetSpriteMap(void);
	int			GetSpriteCount( const wstring& wstrKey );

public:
	virtual void Update( const wstring& wstrStateKey, D3DXMATRIX* matWorld, D3DXMATRIX* matView, D3DXMATRIX* matProj );
	void Render( const DWORD& Frame );
	void Render( void );

	void Release( void );
	virtual CResources* CloneResource( void );

public:
	static CCubeMotion* Create(LPDIRECT3DDEVICE9 pDevice);

private:
	explicit	CCubeMotion(LPDIRECT3DDEVICE9 pDevice);
public:
	virtual ~CCubeMotion(void);

};

END

#endif // CCubeMotion_h__