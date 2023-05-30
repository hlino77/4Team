#include "stdafx.h"
#include "Stage.h"
#include "TextureMgr.h"
#include "ObjectMgr.h"

CStage::CStage()
{
}

CStage::~CStage()
{
	Release_Scene();
}

HRESULT CStage::Ready_Scene()
{
	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/Stage/Terrain/Tile/Tile%d.png",
		TEX_MULTI, L"Terrain", L"Tile", 36)))
	{
		ERR_MSG(L"Stage Tile Image Insert failed");
		return E_FAIL;
	}

	
	



	// 플레이어
	/*pObj = new CPlayer;
	if (nullptr == pObj)
	return E_FAIL;

	pObj->Initialize();

	CObjMgr::Get_Instance()->Add_Object(CObjMgr::PLAYER, pObj);*/

	return S_OK;
}

void CStage::Update_Scene()
{

}

void CStage::Late_Update_Scene()
{
	
}

void CStage::Render_Scene()
{
	
}

void CStage::Release_Scene()
{

}
