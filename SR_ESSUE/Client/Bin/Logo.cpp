#include "stdafx.h"
#include "Logo.h"
#include "Layer.h"

#include "Include.h"
#include "SceneSelector.h"
#include "Export_Function.h"
#include "Texture.h"
#include <Vfw.h>
#pragma comment(lib, "Vfw32.lib")

int CLogo::m_iImageCount = 0;
unsigned int __stdcall CLogo::ImgLoadThreadFunc(void* pArg)
{
	CLogo*		pLogo = (CLogo*)pArg;

	EnterCriticalSection(&pLogo->GetCrt());

	HRESULT hr = NULL;

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//																	//
//							AddBuffer								//
//																	//
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

	// RcTex Buffer
	hr = Engine::Get_ResourceMgr()->AddBuffer(pLogo->GetDevice(), 
		Engine::RESOURCE_STATIC, 
		Engine::CVIBuffer::BUFFER_RCTEX, 
		L"Buffer RcTex");
	FAILED_CHECK_MSG(hr, L"Buffer RcTex Create Failed");


	// CubeTex Buffer
	hr = Engine::Get_ResourceMgr()->AddBuffer(pLogo->GetDevice(), 
		Engine::RESOURCE_STATIC, 
		Engine::CVIBuffer::BUFFER_CUBETEX, 
		L"Buffer CubeTex");
	FAILED_CHECK_MSG(hr, L"Buffer CubeTex Create Failed");

	// CubeCol Buffer
	hr = Engine::Get_ResourceMgr()->AddBuffer(pLogo->GetDevice(), 
		Engine::RESOURCE_STATIC, 
		Engine::CVIBuffer::BUFFER_CUBECOL, 
		L"Buffer CubeCol");
	FAILED_CHECK_MSG(hr, L"Buffer CubeTex Create Failed");

	// Terrain Buffer
	hr = Engine::Get_ResourceMgr()->AddBuffer(pLogo->GetDevice(), 
		Engine::RESOURCE_STATIC, 
		Engine::CVIBuffer::TERRAIN_TEX, 
		L"Buffer Terrain", VTXCNTX, VTXCNTZ, VTXITV);
	FAILED_CHECK_MSG(hr, L"Buffer Terrain Create Failed");

	// TerrainCenter Buffer
	hr = Engine::Get_ResourceMgr()->AddBuffer(pLogo->GetDevice(), 
		Engine::RESOURCE_STATIC, 
		Engine::CVIBuffer::TERRAIN_TEX, 
		L"Buffer TerrainCenter", 33, 33, VTXITV);
	FAILED_CHECK_MSG(hr, L"Buffer Terrain Create Failed");

	
	// SkyBox Buffer
	hr = Engine::Get_ResourceMgr()->AddBuffer(pLogo->GetDevice(), 
		Engine::RESOURCE_STATIC, 
		Engine::CVIBuffer::TERRAIN_TEX, 
		L"Buffer SkyBox", 11, 11, VTXITV);
	FAILED_CHECK_MSG(hr, L"Buffer SkyBox Create Failed");

	// Inven Buffer
	hr = Engine::Get_ResourceMgr()->AddBuffer(pLogo->GetDevice(), 
		Engine::RESOURCE_STATIC, 
		Engine::CVIBuffer::BUFFER_RCTEX, 
		L"Buffer Effect");

	FAILED_CHECK_MSG(hr, L"Buffer Effect Create Failed");

	// Inven Buffer
	hr = Engine::Get_ResourceMgr()->AddBuffer(pLogo->GetDevice(), 
		Engine::RESOURCE_STATIC, 
		Engine::CVIBuffer::BUFFER_RCTEX, 
		L"Buffer Inven");

	FAILED_CHECK_MSG(hr, L"Buffer Inven Create Failed");

	// Item Buffer
	hr = Engine::Get_ResourceMgr()->AddBuffer(pLogo->GetDevice(), 
		Engine::RESOURCE_STATIC, 
		Engine::CVIBuffer::BUFFER_RCTEX, 
		L"Buffer Item");

	FAILED_CHECK_MSG(hr, L"Buffer Item Create Failed");

	// HpBar Buffer
	hr = Engine::Get_ResourceMgr()->AddBuffer(pLogo->GetDevice(), 
		Engine::RESOURCE_STATIC, 
		Engine::CVIBuffer::BUFFER_RCTEX, 
		L"Buffer HpBar");

	FAILED_CHECK_MSG(hr, L"Buffer Item Create Failed");

	// MpBar Buffer
	hr = Engine::Get_ResourceMgr()->AddBuffer(pLogo->GetDevice(), 
		Engine::RESOURCE_STATIC, 
		Engine::CVIBuffer::BUFFER_RCTEX, 
		L"Buffer MpBar");

	FAILED_CHECK_MSG(hr, L"Buffer Item Create Failed");

	// Gauge Buffer
	hr = Engine::Get_ResourceMgr()->AddBuffer(pLogo->GetDevice(), 
		Engine::RESOURCE_STATIC, 
		Engine::CVIBuffer::BUFFER_RCTEX, 
		L"Buffer Gauge");

	FAILED_CHECK_MSG(hr, L"Buffer Item Create Failed");

	// Fire Effect Buffer
	hr = Engine::Get_ResourceMgr()->AddBuffer(pLogo->GetDevice(), 
		Engine::RESOURCE_STATIC, 
		Engine::CVIBuffer::BUFFER_RCTEX, 
		L"Buffer FireEffect");

	FAILED_CHECK_MSG(hr, L"Buffer FireEffect Create Failed");

	// Water Effect Buffer
	hr = Engine::Get_ResourceMgr()->AddBuffer(pLogo->GetDevice(), 
		Engine::RESOURCE_STATIC, 
		Engine::CVIBuffer::BUFFER_RCTEX, 
		L"Buffer WaterEffect");

	FAILED_CHECK_MSG(hr, L"Buffer FireEffect Create Failed");

	// Electric Effect Buffer
	hr = Engine::Get_ResourceMgr()->AddBuffer(pLogo->GetDevice(), 
		Engine::RESOURCE_STATIC, 
		Engine::CVIBuffer::BUFFER_RCTEX, 
		L"Buffer ElectricEffect");

	FAILED_CHECK_MSG(hr, L"Buffer FireEffect Create Failed");

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//																	//
//							AddTexture								//
//																	//
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


	// Terrain Texture
	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(), 
		Engine::RESOURCE_STATIC, 
		Engine::TEX_NORMAL, 
		L"Texture Terrain", 
		L"../bin/Resources/Texture/Terrain/Terrain_grass%d.png", 
		3);
	FAILED_CHECK_MSG(hr, L"Texture Terrain Create Failed");

	// SkyBox Texture
	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(), 
		Engine::RESOURCE_STATIC, 
		Engine::TEX_NORMAL, 
		L"Texture SkyBox", 
		L"../bin/Resources/Texture/SkyBox/Sky_Side%d.png", 
		3);
	FAILED_CHECK_MSG(hr, L"Texture Terrain Create Failed");

	
	// Inven Texture
	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(), 
		Engine::RESOURCE_STATIC, 
		Engine::TEX_NORMAL, 
		L"Texture Inven", 
		L"../bin/Resources/Texture/Ui/Inven.png", 
		1);
	FAILED_CHECK_MSG(hr, L"Texture Inven Create Failed");

	// Item Texture
	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(), 
		Engine::RESOURCE_STATIC, 
		Engine::TEX_NORMAL, 
		L"Texture Item", 
		L"../bin/Resources/Texture/Ui/Item%d.png", 
		3);
	FAILED_CHECK_MSG(hr, L"Texture Item Create Failed");

	// Poketmon icon Texture
	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(), 
		Engine::RESOURCE_STATIC, 
		Engine::TEX_NORMAL, 
		L"Poketmon icon", 
		L"../bin/Resources/Texture/Ui/Porketmon%d.png", 
		3);
	FAILED_CHECK_MSG(hr, L"Texture Poketmon icon Create Failed");

	// PoketballUI icon Texture
	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(), 
		Engine::RESOURCE_STATIC, 
		Engine::TEX_NORMAL, 
		L"PoketballUI icon", 
		L"../bin/Resources/Texture/Ui/PoketballUI.png", 
		1);
	FAILED_CHECK_MSG(hr, L"Texture PoketballUI icon Create Failed");

	// HpBar Texture
	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(), 
		Engine::RESOURCE_STATIC, 
		Engine::TEX_NORMAL, 
		L"Texture HpBar", 
		L"../bin/Resources/Texture/Ui/HpBar.png", 
		1);

	// MpBar Texture
	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(), 
		Engine::RESOURCE_STATIC, 
		Engine::TEX_NORMAL, 
		L"Texture MpBar", 
		L"../bin/Resources/Texture/Ui/MpBar.png", 
		1);
	FAILED_CHECK_MSG(hr, L"Texture Item Create Failed");

	// HPGauge Texture
	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(), 
		Engine::RESOURCE_STATIC, 
		Engine::TEX_NORMAL, 
		L"Texture HpGauge", 
		L"../bin/Resources/Texture/Ui/HpGauge.png", 
		1);
	FAILED_CHECK_MSG(hr, L"Texture Item Create Failed");

	// HPGauge1 Texture
	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(), 
		Engine::RESOURCE_STATIC, 
		Engine::TEX_NORMAL, 
		L"Texture HpGauge1", 
		L"../bin/Resources/Texture/Ui/HpGauge1.png", 
		1);
	FAILED_CHECK_MSG(hr, L"Texture Item Create Failed");

	// MPGauge Texture
	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(), 
		Engine::RESOURCE_STATIC, 
		Engine::TEX_NORMAL, 
		L"Texture MpGauge", 
		L"../bin/Resources/Texture/Ui/MpGauge.png", 
		1);
	FAILED_CHECK_MSG(hr, L"Texture Item Create Failed");

	// Cube Texture
	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(), 
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"Texture CenterMark", 
		L"../bin/Resources/Texture/Cube/CenterMark%d.dds", 
		1);
	FAILED_CHECK_MSG(hr, L"Texture Item Create Failed");

	// Cube Texture
	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(), 
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"Texture CenterRoofTex", 
		L"../bin/Resources/Texture/Cube/CenterRoofTex%d.dds", 
		1);
	FAILED_CHECK_MSG(hr, L"Texture Item Create Failed");

	// Cube Texture
	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(), 
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"Texture Danger", 
		L"../bin/Resources/Texture/Cube/Danger%d.dds", 
		1);
	FAILED_CHECK_MSG(hr, L"Texture Item Create Failed");

	// Cube Texture
	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(), 
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"Texture Glass", 
		L"../bin/Resources/Texture/Cube/Glass%d.dds", 
		1);
	FAILED_CHECK_MSG(hr, L"Texture Item Create Failed");

	// Cube Texture
	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(), 
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"Texture RedRoof", 
		L"../bin/Resources/Texture/Cube/RedRoof%d.dds", 
		1);
	FAILED_CHECK_MSG(hr, L"Texture Item Create Failed");

	// Cube Texture
	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(), 
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"Texture Wall_White", 
		L"../bin/Resources/Texture/Cube/Wall_White%d.dds", 
		1);
	FAILED_CHECK_MSG(hr, L"Texture Item Create Failed");

	// Cube Texture
	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(), 
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"renga.dds", 
		L"../bin/Resources/Texture/Cube/WoodenBox%d.dds", 
		1);
	FAILED_CHECK_MSG(hr, L"Texture Item Create Failed");

	//	Etc Texture
	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(), 
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"Texture MonsterBall", 
		L"../bin/Resources/Texture/Etc/MonsterBall.dds", 
		1);
	FAILED_CHECK_MSG(hr, L"Texture Item Create Failed");

	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(), 
		Engine::RESOURCE_STATIC, 
		Engine::TEX_NORMAL, 
		L"Texture FireEffect", 
		L"../bin/Resources/Texture/Effect/FireEffect/FireEffect.png", 
		1);
	FAILED_CHECK_MSG(hr, L"Texture Fire Effect Create Failed");

	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(), 
		Engine::RESOURCE_STATIC, 
		Engine::TEX_NORMAL, 
		L"Texture WaterEffect", 
		L"../bin/Resources/Texture/Effect/WaterEffect/WaterEffect.png", 
		1);
	FAILED_CHECK_MSG(hr, L"Texture Water Effect Create Failed");

	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(), 
		Engine::RESOURCE_STATIC, 
		Engine::TEX_NORMAL, 
		L"Texture ElectricEffect", 
		L"../bin/Resources/Texture/Effect/ElectricEffect/ElectricEffect.png", 
		1);
	FAILED_CHECK_MSG(hr, L"Texture Electric Effect Create Failed");

	/////////////////////////////////////////////////////////////
	///////////////////// ²¿ºÎ±â/////////////////////////////////
	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(),
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"SHead.dds", 
		L"../bin/Resources/Texture/CubeTexture/SHead.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(),
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"SBody.dds", 
		L"../bin/Resources/Texture/CubeTexture/SBody.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(),
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"SArm.dds", 
		L"../bin/Resources/Texture/CubeTexture/SArm.dds", 
		1);
	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(),
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"SArm1.dds", 
		L"../bin/Resources/Texture/CubeTexture/SArm1.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(),
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"SArm2.dds", 
		L"../bin/Resources/Texture/CubeTexture/SArm2.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(),
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"SArm3.dds", 
		L"../bin/Resources/Texture/CubeTexture/SArm3.dds", 
		1);

	/////////////////////////////////////////////////////////////
	///////////////////// Áö¿ì/////////////////////////////////
	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(),
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"THead.dds", 
		L"../bin/Resources/Texture/CubeTexture/THead.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(),
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"TBody.dds", 
		L"../bin/Resources/Texture/CubeTexture/TBody.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(),
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"TArm.dds", 
		L"../bin/Resources/Texture/CubeTexture/TArm.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(),
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"TArm1.dds", 
		L"../bin/Resources/Texture/CubeTexture/TArm1.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(),
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"TLeg.dds", 
		L"../bin/Resources/Texture/CubeTexture/TLeg.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(),
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"TLeg1.dds", 
		L"../bin/Resources/Texture/CubeTexture/TLeg1.dds", 
		1);

	// ÇÇÄ«Ãò
	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(),
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"PHead.dds", 
		L"../bin/Resources/Texture/CubeTexture/PHead.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(),
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"PEar.dds", 
		L"../bin/Resources/Texture/CubeTexture/PEar.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(),
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"PEar1.dds", 
		L"../bin/Resources/Texture/CubeTexture/PEar1.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(),
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"PBody.dds", 
		L"../bin/Resources/Texture/CubeTexture/PBody.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(),
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"PArm.dds", 
		L"../bin/Resources/Texture/CubeTexture/PArm.dds", 
		1);
	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(),
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"PArm1.dds", 
		L"../bin/Resources/Texture/CubeTexture/PArm1.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(),
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"PArm2.dds", 
		L"../bin/Resources/Texture/CubeTexture/PArm2.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(),
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"PArm3.dds", 
		L"../bin/Resources/Texture/CubeTexture/PArm3.dds", 
		1);

	// ÆÄÀÌ¸®
	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(),
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"CHead.dds", 
		L"../bin/Resources/Texture/CubeTexture/CHead.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(),
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"CBody.dds", 
		L"../bin/Resources/Texture/CubeTexture/CBody.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(),
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"CArm.dds", 
		L"../bin/Resources/Texture/CubeTexture/CArm.dds", 
		1);
	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(),
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"CArm1.dds", 
		L"../bin/Resources/Texture/CubeTexture/CArm1.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(),
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"CArm2.dds", 
		L"../bin/Resources/Texture/CubeTexture/CArm2.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(),
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"CArm3.dds", 
		L"../bin/Resources/Texture/CubeTexture/CArm3.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(),
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"Charman.dds", 
		L"../bin/Resources/Texture/CubeTexture/Charman.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(),
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"Fire.dds", 
		L"../bin/Resources/Texture/CubeTexture/Fire.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(),
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"CTail1.dds", 
		L"../bin/Resources/Texture/CubeTexture/CTail1.dds", 
		1);

	///////////////////////// ¸Á³ª´¨ º¸½º ///////////////////////////
	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(),
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"MBody.dds", 
		L"../bin/Resources/Texture/CubeTexture/MBody.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(),
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"MHead.dds", 
		L"../bin/Resources/Texture/CubeTexture/MHead.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(),
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"MLArm.dds", 
		L"../bin/Resources/Texture/CubeTexture/MLArm.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(),
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"MRArm.dds", 
		L"../bin/Resources/Texture/CubeTexture/MRArm.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(),
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"MLWing.dds", 
		L"../bin/Resources/Texture/CubeTexture/MLWing.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(),
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"MRWing.dds", 
		L"../bin/Resources/Texture/CubeTexture/MRWing.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(),
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"MLLeg.dds", 
		L"../bin/Resources/Texture/CubeTexture/MLLeg.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(),
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"MRLeg.dds", 
		L"../bin/Resources/Texture/CubeTexture/MRLeg.dds", 
		1);


	//¼¾ÅÍ
	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(),
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"Cenmark.dds", 
		L"../bin/Resources/Texture/Cube/Center/Cenmark.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(),
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"RoofTex.dds", 
		L"../bin/Resources/Texture/Cube/Center/RoofTex.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(),
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"Danger.dds", 
		L"../bin/Resources/Texture/Cube/Center/Danger.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(),
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"RedRoof.dds", 
		L"../bin/Resources/Texture/Cube/Center/RedRoof.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(),
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"Wall_Wh.dds", 
		L"../bin/Resources/Texture/Cube/Center/Wall_Wh.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(),
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"Wooden.dds", 
		L"../bin/Resources/Texture/Cube/Center/Wooden.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(),
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"Glass.dds", 
		L"../bin/Resources/Texture/Cube/Center/Glass.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(),
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"renga1.dds", 
		L"../bin/Resources/Texture/Cube/Center/renga1.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(),
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"renga2.dds", 
		L"../bin/Resources/Texture/Cube/Center/renga2.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(),
		Engine::RESOURCE_STATIC, 
		Engine::TEX_NORMAL, 
		L"Tree", 
		L"../Bin/Resources/Texture/Etc/tree0%d.png", 
		5);

	m_iImageCount = 1;
	LeaveCriticalSection(&pLogo->GetCrt());
	_endthreadex(0);

	return 0;
}

CRITICAL_SECTION CLogo::GetCrt(void)
{
	return m_Crt;
}

CLogo::CLogo(LPDIRECT3DDEVICE9 pDevice)
: Engine::CScene(pDevice)
, m_pManagement(Engine::Get_Management())
, m_pResourceMgr(Engine::Get_ResourceMgr())
, m_fCount(0)
, m_fMaxCount(0)

{

}

CLogo::~CLogo(void)
{
	Release();
}

HRESULT CLogo::InitScene(void)
{
	/*m_hVideo = MCIWndCreate(g_hWnd, NULL, MCIWNDF_NOPLAYBAR | WS_VISIBLE | WS_CHILD,
		L"../Bin/Video/Opening.wmv");

	HRESULT hr = NULL;

	InitializeCriticalSection(&m_Crt);

	m_hThread = (HANDLE)_beginthreadex(NULL, 0, ImgLoadThreadFunc, this, 0, NULL);

	MoveWindow(m_hVideo, 0, 0, WINCX, WINCY, NULL);
	MCIWndPlay(m_hVideo);*/

	HRESULT hr = NULL;

	hr = Engine::Get_ResourceMgr()->AddTexture(m_pDevice, 
		Engine::RESOURCE_STATIC, 
		Engine::TEX_NORMAL, 
		L"Logo", 
		L"../bin/Resources/Texture/Etc/Loading%d.jpg", 
		2);

	hr = Engine::Get_ResourceMgr()->AddBuffer(m_pDevice, 
		Engine::RESOURCE_STATIC, 
		Engine::CVIBuffer::BUFFER_RCTEX, 
		L"Logo Buffer");

	Engine::CComponent*		pComponent = NULL;

	pComponent = Engine::Get_ResourceMgr()->CloneResource(Engine::RESOURCE_STATIC, L"Logo");
	m_pTexture = dynamic_cast<Engine::CTexture*>(pComponent);

	pComponent = Engine::Get_ResourceMgr()->CloneResource(Engine::RESOURCE_STATIC, L"Logo Buffer");
	m_pBuffer = dynamic_cast<Engine::CVIBuffer*>(pComponent);

	InitializeCriticalSection(&m_Crt);

	m_hThread = (HANDLE)_beginthreadex(NULL, 0, ImgLoadThreadFunc, this, 0, NULL);

	return S_OK;
}

void CLogo::Update(void)
{
	if(GetAsyncKeyState(VK_RETURN))
	{
		WaitForSingleObject(m_hThread, INFINITE);
		CloseHandle(m_hThread);

		DeleteCriticalSection(&m_Crt);

		//MCIWndClose(m_hVideo);


		m_pManagement->SceneChange(CSceneSelector(SC_STAGE), SC_STAGE);

		return;
	}
}

void CLogo::Render(void)
{
	m_pTexture->Render(m_iImageCount);
	m_pBuffer->Render();
}
CLogo* CLogo::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CLogo*	pLogo = new CLogo(pDevice);

	if (FAILED(pLogo->InitScene()))
		Engine::Safe_Delete(pLogo);

	return pLogo;
}

HRESULT CLogo::Add_Environment_Layer(void)
{
	return S_OK;
}

HRESULT CLogo::Add_GameLogic_Layer(void)
{

	return S_OK;
}

LPDIRECT3DDEVICE9 CLogo::GetDevice( void )
{
	return m_pDevice;
}

void CLogo::Release( void )
{
	Engine::Safe_Delete(m_pBuffer);
	Engine::Safe_Delete(m_pTexture);
}
