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

BEGIN(Engine)

class ENGINE_DLL CCubeMotion
	:public CResources
{
private:
	typedef map<wstring, vector<CResources*>>	MAPVECTOR;
	MAPVECTOR									m_SpriteMap;

public:
	void		AddSprite(const wstring& wstrName, CResources* pComponent);
	void		RemoveSprite(const wstring& wstrName);
	MAPVECTOR*	GetSpriteMap(void);

public:
	virtual void Render( void );
	virtual void Release( void );
	virtual void Update( void );
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