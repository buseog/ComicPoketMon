/*!
 * \file Engine_struct.h
 * \date 2016/12/21 16:04
 *
 * \author Administrator
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef Engine_struct_h__
#define Engine_struct_h__

namespace Engine
{
	typedef struct tagVerTexColor
	{
		D3DXVECTOR3		vPos;
		DWORD			dwColor;

	}VTXCOL;

	const DWORD	VTXFVF_COL = D3DFVF_XYZ | D3DFVF_DIFFUSE;

	typedef struct tagVerTexTexture
	{
		D3DXVECTOR3		vPos;
		D3DXVECTOR2		vTex;

	}VTXTEX;

	const DWORD	VTXFVF_TEX = D3DFVF_XYZ | D3DFVF_TEX1;

	typedef struct tagVertexCube
	{
		D3DXVECTOR3		vPos;
		D3DXVECTOR3		vTex;

	}VTXCUBE;

	const DWORD VTXFVF_CUBE = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE3(0);

	typedef	struct tagIndex16
	{
		WORD	_1, _2, _3;

	}INDEX16;

	typedef struct tagIndex32
	{
		DWORD	_1, _2, _3;

	}INDEX32;

	typedef	struct tagInfo
	{
		D3DXVECTOR3		vPos;
		D3DXVECTOR3		vDir;
		D3DXVECTOR3		vLook;
		D3DXMATRIX		matWorld;

	}INFO;

	typedef struct tagSaveFile
	{
		VTXCUBE VtxInfo[8];
		wstring wstrName;
	}SAVEFILE;

	typedef struct tagSaveFrame
	{
		wstring wstrStateKey;
		wstring wstrPartsKey;
		wstring wstrTexKey;
		int		FrameKey;
		VTXCUBE	VtxInfo[8];
	
	}SAVEFRAME;

	typedef struct TagParticle
	{
		D3DXVECTOR3	vPos;
		D3DCOLOR	vColor;

	}PARTICLE;

	const DWORD PARTICLEFVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;

	typedef	struct	TagAttribute
	{
		D3DXVECTOR3	vPos;			// 파티클 위치
		D3DXVECTOR3	vVelocity;		// 파티클 속도 ( /s)
		D3DXVECTOR3	vAcceleration;	// 파티클 가속도 ( /s)
		float		fLifeTime;		// 파티클 유지시간
		float		fAge;			// 파티클 나이
		D3DXCOLOR	vColor;			// 파티클 컬러
		D3DXCOLOR	vColorFade;		// 파티클 컬러가 시간에 따라 퇴색하는 방법
		bool		bAlive;			// 파티클 생존여부
	}ATTRIBUTE;

	typedef struct D3DMATERIAL9
	{
		D3DCOLORVALUE Diffuse, Ambient, Specular, Emissive ;
		float Power;
	} MATERIAL9;

	typedef struct Sprite
	{
		int		iMaxFrame;
		int		iCurFrame;
		int		iFrameCounter;
		int		iFrameDelay;
	}SPRITE;

	typedef struct SpriteTex
	{
		D3DXVECTOR4		vPos;
		DWORD			dwColor;
		float			fTu;
		float			fTv;
	}SPRITETEX;

	typedef	struct	tagObjectInfo
	{
		D3DXVECTOR3	vPos;
		int			iTexCount;
		wstring		wstrTexKey;
	}OBJINFO;
}

#endif // Engine_struct_h__