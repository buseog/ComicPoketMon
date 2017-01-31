/*!
 * \file SkyBox.h
 * \date 2017/01/15 23:46
 *
 * \author Administrator
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 *                            ┌----┐
 *						       ◎= ◎ 	
 *						   ┌__________┐
 * \note	스카이박스입니다 < ^ 오 ^ >~
 *							  / ∇∇ \
*/

#ifndef SkyBox_h__
#define SkyBox_h__

#include "SingleGameObject.h"

class CSkyBox 
	: public CSingleGameObject
{
private:
	const size_t				m_iBoxCount;

private:
	vector<Engine::VTXTEX*>		m_vecVertex;
	vector<Engine::VTXTEX*>		m_vecConvertVertex;

	D3DXMATRIX					m_matBoxWorld[6];
	float						m_fSize;
	float						m_finterval;

private:
	HRESULT				Initialize(void);
	void				SetDirection(void);
	void				SetTransform(void);

public:
	void				Update(void);
	void				Render(void);
	void				Release(void);
	HRESULT				AddComponent(void);

public:
	static	CSkyBox*	Create(LPDIRECT3DDEVICE9 pDevice);

private:
	explicit	CSkyBox(LPDIRECT3DDEVICE9 pDevice);
public:
	~CSkyBox(void);
};

#endif // SkyBox_h__