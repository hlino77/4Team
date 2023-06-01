#include "stdafx.h"
#include "Terrain.h"
#include "TextureMgr.h"
#include "Device.h"

#include "Collider.h"
#include "CameraMgr.h"
#include "KeyMgr.h"

CTerrain::CTerrain() : m_bColRender(false)
{
	//m_vecTile.reserve(TILEX * TILEY);
	m_pMapInfo = nullptr;
}

CTerrain::~CTerrain()
{
	Release();
}

HRESULT CTerrain::Initialize(void)
{
	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/Stage/Terrain/Map/NeoLostTemple.png", TEX_SINGLE, L"Map")))
	{
		ERR_MSG(L"TileTexture Create Failed");
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/Stage/Terrain/Collider/ColliderGreen.png", TEX_SINGLE, L"Col_Green")))
	{
		ERR_MSG(L"TileTexture Create Failed");
		return E_FAIL;
	}
	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/Stage/Terrain/Collider/ColliderRed.png", TEX_SINGLE, L"Col_Red")))
	{
		ERR_MSG(L"TileTexture Create Failed");
		return E_FAIL;
	}
	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/Stage/Terrain/Collider/ColliderBlack.png", TEX_SINGLE, L"Col_Black")))
	{
		ERR_MSG(L"TileTexture Create Failed");
		return E_FAIL;
	}

	TILE*	pMap = new TILE;
	pMap->vPos = { 0.f, 0.f, 0.f };
	pMap->vSize = { MAPCX, MAPCY, 0.f };
	pMap->byOption = 0;
	pMap->byDrawID = 0;

	m_pMapInfo = pMap;

	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			TILE* pTile = new TILE;
			pTile->m_iID = g_iNextID++;
			pTile->eType = OBJID::OBJ_TILE;

			float	fX = (TILECX * j) + (TILECX / 2);
			float	fY = (TILECY * i) + (TILECY / 2);

			pTile->vPos = { fX, fY, 0.f };
			pTile->vSize = { TILECX, TILECY, 0.f };
			pTile->byOption = 0;
			pTile->byDrawID = 0;


			pTile->vPoint[0] = { (TILECX * 0.5f) * -1.0f, (TILECY * 0.5f) * -1.0f, 0.0f };
			pTile->vPoint[1] = { (TILECX * 0.5f), (TILECY * 0.5f) * -1.0f, 0.0f };
			pTile->vPoint[2] = { (TILECX * 0.5f), (TILECY * 0.5f), 0.0f };
			pTile->vPoint[3] = { (TILECX * 0.5f) * -1.0f, (TILECY * 0.5f), 0.0f };
			pTile->vPoint[4] = { (TILECX * 0.5f) * -1.0f, (TILECY * 0.5f) * -1.0f, 0.0f };



			for (int i = 0; 5 > i; ++i)
			{
				pTile->vOriginPoint[i] = pTile->vPoint[i];
			}

			pTile->bCollider = false;

			m_vecTile.push_back(pTile);
		}
	}

	m_ColState = SETCOL_STATE::NONE;

	Load_TileData();

	return S_OK;
}

void CTerrain::Update(void)
{
	if (CKeyMgr::Get_Instance()->Key_Down('C'))
	{
		m_bColRender = !m_bColRender;
	}
}

void CTerrain::Render(void)
{
	D3DXMATRIX	matWorld, matScale, matTrans;

	float m_fScrollX = CCameraMgr::Get_Instance()->Get_ScrollX();
	float m_fScrollY = CCameraMgr::Get_Instance()->Get_ScrollY();

	float	fX = MAPCX * 0.5f;
	float	fY = MAPCY * 0.5f;

	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixTranslation(&matTrans,
		m_pMapInfo->vPos.x + m_fScrollX,
		m_pMapInfo->vPos.y + m_fScrollY,
		0.f);

	matWorld = matScale * matTrans;

	//Set_Ratio(&matWorld, fX, fY);

	CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

	const TEXINFO*	pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"Map");

	CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
		nullptr,							// 출력할 이미지 영역에 대한 Rect 주소, null인 경우 이미지의 0, 0 기준으로 출력
		nullptr,			// 출력할 이미지의 중심축에 대한 vector3 주소, null인 경우 이미지의 0, 0이 중심 좌표
		nullptr,							// 위치 좌표에 대한 vector3 주소, null인 경우 스크린 상의 0, 0좌표 출력
		D3DCOLOR_ARGB(255, 255, 255, 255)); // 출력할 이미지와 섞을 색상 값, 0xffffffff를 넘겨주면 원본 색상 유지


}

void CTerrain::Mini_Render(void)
{
	//D3DXMATRIX	matWorld, matScale, matTrans;

	//D3DXMatrixIdentity(&matWorld);
	//D3DXMatrixScaling(&matScale, 0.975f, 0.975f, 1.f);
	//D3DXMatrixTranslation(&matTrans,
	//	m_pMapInfo->vPos.x,
	//	m_pMapInfo->vPos.y,
	//	0.f);

	//matWorld = matScale * matTrans;

	//CMainFrame*		pMainFrm = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	//CMiniView*		pMiniView = dynamic_cast<CMiniView*>(pMainFrm->m_SecondSplitter.GetPane(0, 0));
	//CRect rc;

	//pMiniView->GetClientRect(rc);

	//const TEXINFO*	pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"Map");

	//float	fX = rc.Width() / (2.f * WINCX);
	//float	fY = rc.Height() / (2.f * WINCY);


	//// 이미지에 행렬을 반영
	//Set_Ratio(&matWorld, 0.2f, 0.15f);

	//CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

	//CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
	//	nullptr,
	//	&D3DXVECTOR3(0.9f * fX, 0.9f * fY, 0.f),
	//	nullptr,
	//	D3DCOLOR_ARGB(255, 255, 255, 255));

}


void CTerrain::Collider_Render(void)
{
	if (!m_bColRender)
		return;

	D3DXMATRIX	matWorld, matScale, matTrans;

	D3DXVECTOR2 vRenderPoint[5];

	RECT	rc{};

	LPDIRECT3DDEVICE9 pDevice = CDevice::Get_Instance()->Get_Device();

	// GetClientRect : 현재 클라이언트 영역의 rect 정보를 얻어옴

	float m_fScrollX = CCameraMgr::Get_Instance()->Get_ScrollX();
	float m_fScrollY = CCameraMgr::Get_Instance()->Get_ScrollY();


	for (auto iter : m_vecTile)
	{
		if (iter->bCollider)
		{
			D3DXMatrixIdentity(&matWorld);
			D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
			D3DXMatrixTranslation(&matTrans,
				int(iter->vPos.x + m_fScrollX), // 0일 경우 x 스크롤 값 얻어옴
				int(iter->vPos.y + m_fScrollY), // 1일 경우 y 스크롤 값 얻어옴
				0.f);

			matWorld = matScale * matTrans;



			CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

			const TEXINFO*	pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"Col_Red");

			CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
				nullptr,							// 출력할 이미지 영역에 대한 Rect 주소, null인 경우 이미지의 0, 0 기준으로 출력
				&D3DXVECTOR3(16.0f, 16.0f, 0.f),			// 출력할 이미지의 중심축에 대한 vector3 주소, null인 경우 이미지의 0, 0이 중심 좌표
				nullptr,							// 위치 좌표에 대한 vector3 주소, null인 경우 스크린 상의 0, 0좌표 출력
				D3DCOLOR_ARGB(100, 255, 255, 255)); // 출력할 이미지와 섞을 색상 값, 0xffffffff를 넘겨주면 원본 색상 유지
		}
	}




}

void CTerrain::Release(void)
{
	delete m_pMapInfo;
	m_pMapInfo = nullptr;
	for (auto& iter : m_vecTile)
		Safe_Delete(iter);
	m_vecTile.clear();
}




void CTerrain::Set_Ratio(D3DXMATRIX * pOut, float fRatioX, float fRatioY)
{
	pOut->_11 *= fRatioX;
	pOut->_21 *= fRatioX;
	pOut->_31 *= fRatioX;
	pOut->_41 *= fRatioX;

	pOut->_12 *= fRatioY;
	pOut->_22 *= fRatioY;
	pOut->_32 *= fRatioY;
	pOut->_42 *= fRatioY;
}

void CTerrain::Load_TileData(void)
{
	const TCHAR* pTilePath = L"../Data/TileData.dat";

	HANDLE hFile = CreateFile(pTilePath, GENERIC_READ,
		0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	if (INVALID_HANDLE_VALUE == hFile)
		return;

	DWORD	dwByte = 0;

	for (auto& iter : m_vecTile)
	{
		ReadFile(hFile, &iter->bCollider, sizeof(bool), &dwByte, nullptr);
		if (0 == dwByte)
		{
			break;
		}
	}

	CloseHandle(hFile);


}

