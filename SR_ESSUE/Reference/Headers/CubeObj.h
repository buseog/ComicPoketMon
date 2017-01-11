/*!
 * \file CubeObj.h
 * \date 2017/01/10 16:04
 *
 * \author ESSUE
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef CubeObj_h__
#define CubeObj_h__

#include "Resources.h"
namespace Engine
{
	class CTransform;
}
BEGIN(Engine)

class ENGINE_DLL CCubeObj
	:public CResources
{
private:
	typedef map<wstring, CComponent*>	MAPCOMPONENT;
	MAPCOMPONENT						m_MapComponent;

public:
	void	AddParts(const wstring& wstrName, CComponent* pComponent);
	void	RemoveParts(const wstring& wstrName);

public:
	virtual void Render( void );
	virtual void Release( void );
	virtual void Update( void );
	virtual CResources* CloneResource( void );

	void	PikingPlane(void);

private:
	CTransform*			m_pInfo;

private:
	explicit	CCubeObj(LPDIRECT3DDEVICE9 pDevice);
public:
	~CCubeObj(void);

};

END
#endif // CubeObj_h__