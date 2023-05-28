#include "stdafx.h"
#include "Terrain.h"
#include "TextureMgr.h"
#include "Device.h"
#include "ToolView.h"

#include "Mainfrm.h"
//#include ""

CTerrain::CTerrain()
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
		AfxMessageBox(L"TileTexture Create Failed");
		return E_FAIL;
	}

	TILE*	pMap = new TILE;
	pMap->vPos = { 0.f, 0.f, 0.f };
	pMap->vSize = { MAPCX, MAPCY, 0.f };
	pMap->byOption = 0;
	pMap->byDrawID = 0;

	m_pMapInfo = pMap;
//	m_iZoomLevel = 0;
	//for (int i = 0; i < TILEY; ++i)
	//{
	//	for (int j = 0; j < TILEX; ++j)
	//	{
	//		TILE* pTile = new TILE;
	//
	//		float	fX = (TILECX * j) + ((TILECX / 2.f) * (i % 2));
	//		float	fY = (TILECY / 2.f) * i;
	//
	//		pTile->vPos = {fX, fY, 0.f};
	//		pTile->vSize = { TILECX, TILECY, 0.f };
	//		pTile->byOption = 0;
	//		pTile->byDrawID = 3;
	//		
	//		m_vecTile.push_back(pTile);
	//	}
	//}

	return S_OK;
}

void CTerrain::Update(void)
{
}

void CTerrain::Render(void)
{
	D3DXMATRIX	matWorld, matScale, matTrans;

	RECT	rc{};

	// GetClientRect : ���� Ŭ���̾�Ʈ ������ rect ������ ����
	GetClientRect(m_pMainView->m_hWnd, &rc);

	float	fX = WINCX / float(rc.right - rc.left);
	float	fY = WINCY / float(rc.bottom - rc.top);

	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixTranslation(&matTrans,
		m_pMapInfo->vPos.x - m_pMainView->GetScrollPos(0),
		m_pMapInfo->vPos.y - m_pMainView->GetScrollPos(1),
		0.f);

	matWorld = matScale * matTrans;
	//if(0 == m_iZoomLevel)

	//else if(0 > m_iZoomLevel)

	//else

	Set_Ratio(&matWorld, fX, fY);

	CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

	const TEXINFO*	pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"Map");

	CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
					nullptr,							// ����� �̹��� ������ ���� Rect �ּ�, null�� ��� �̹����� 0, 0 �������� ���
					&D3DXVECTOR3(fX, fY, 0.f),			// ����� �̹����� �߽��࿡ ���� vector3 �ּ�, null�� ��� �̹����� 0, 0�� �߽� ��ǥ
					nullptr,							// ��ġ ��ǥ�� ���� vector3 �ּ�, null�� ��� ��ũ�� ���� 0, 0��ǥ ���
					D3DCOLOR_ARGB(255, 255, 255, 255)); // ����� �̹����� ���� ���� ��, 0xffffffff�� �Ѱ��ָ� ���� ���� ����

	/*for (auto iter : m_vecTile)
	{
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
		D3DXMatrixTranslation(&matTrans, 
			iter->vPos.x - m_pMainView->GetScrollPos(0), // 0�� ��� x ��ũ�� �� ����
			iter->vPos.y - m_pMainView->GetScrollPos(1), // 1�� ��� y ��ũ�� �� ����
			0.f);

		matWorld = matScale * matTrans;

//		Set_Ratio(&matWorld, fX, fY);

		const TEXINFO*	pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"Map", L"Tile", iter->byDrawID);
		
		float	fX = pTexInfo->tImgInfo.Width / 2.f;
		float	fY = pTexInfo->tImgInfo.Height / 2.f;
			
		// �̹����� ����� �ݿ�
		CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

		CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
			nullptr,							// ����� �̹��� ������ ���� Rect �ּ�, null�� ��� �̹����� 0, 0 �������� ���
			&D3DXVECTOR3(fX, fY, 0.f),			// ����� �̹����� �߽��࿡ ���� vector3 �ּ�, null�� ��� �̹����� 0, 0�� �߽� ��ǥ
			nullptr,							// ��ġ ��ǥ�� ���� vector3 �ּ�, null�� ��� ��ũ�� ���� 0, 0��ǥ ���
			D3DCOLOR_ARGB(255, 255, 255, 255)); // ����� �̹����� ���� ���� ��, 0xffffffff�� �Ѱ��ָ� ���� ���� ����
	}*/
}

void CTerrain::Mini_Render(void)
{
	D3DXMATRIX	matWorld, matScale, matTrans;

	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixScaling(&matScale, 0.975f, 0.975f, 1.f);
	D3DXMatrixTranslation(&matTrans,
		m_pMapInfo->vPos.x,
		m_pMapInfo->vPos.y,
		0.f);

	matWorld = matScale * matTrans;

	CMainFrame*		pMainFrm = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	CMiniView*		pMiniView = dynamic_cast<CMiniView*>(pMainFrm->m_SecondSplitter.GetPane(0, 0));
	CRect rc;
	
	pMiniView->GetClientRect(rc);
	
	const TEXINFO*	pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"Map");

	float	fX = rc.Width() / (2.f * WINCX);
	float	fY = rc.Height() / (2.f * WINCY);

	// �̹����� ����� �ݿ�
	Set_Ratio(&matWorld, 0.2f, 0.15f);

	CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

	CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
		nullptr,
		&D3DXVECTOR3(fX, fY, 0.f),
		nullptr,
		D3DCOLOR_ARGB(255, 255, 255, 255));

	/*for (auto iter : m_vecTile)
	{
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
		D3DXMatrixTranslation(&matTrans,
			iter->vPos.x, 
			iter->vPos.y, 
			0.f);

		matWorld = matScale * matTrans;

		Set_Ratio(&matWorld, 0.3f, 0.3f);

		const TEXINFO*	pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"Terrain", L"Tile", iter->byDrawID);

		float	fX = pTexInfo->tImgInfo.Width / 2.f;
		float	fY = pTexInfo->tImgInfo.Height / 2.f;

		// �̹����� ����� �ݿ�
		CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

		CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
			nullptr,							
			&D3DXVECTOR3(fX, fY, 0.f),			
			nullptr,							
			D3DCOLOR_ARGB(255, 255, 255, 255)); 
	}*/
}

void CTerrain::Release(void)
{
	/*for_each(m_vecTile.begin(), m_vecTile.end(), CDeleteObj());
	m_vecTile.clear();
	m_vecTile.shrink_to_fit();*/
	delete m_pMapInfo;
	m_pMapInfo = nullptr;
}

void CTerrain::Tile_Change(const D3DXVECTOR3 & vPos, const int & iDrawID)
{
	/*int		iIndex = Get_TileIndex(vPos);

	if (-1 == iIndex)
		return;

	m_vecTile[iIndex]->byDrawID = (BYTE)iDrawID;
	m_vecTile[iIndex]->byOption = 1;*/
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

int CTerrain::Get_TileIndex(const D3DXVECTOR3 & vPos)
{
	//for (size_t index = 0; index < m_vecTile.size(); ++index)
	//{
	//	if (Picking_Dot(vPos, index))
	//	{
	//		return index;
	//	}
	//}

	return -1;
}

bool CTerrain::Picking(const D3DXVECTOR3 & vPos, const int & iIndex)
{

	//float	fGradient[4] {

	//	((TILECY / 2.f) / (TILECX / 2.f)) * -1.f,
	//	((TILECY / 2.f) / (TILECX / 2.f)),
	//	((TILECY / 2.f) / (TILECX / 2.f)) * -1.f,
	//	((TILECY / 2.f) / (TILECX / 2.f))
	//};

	//// 12, 3, 6, 9 �� ������ ���� ��ġ�� ����

	//D3DXVECTOR3		vPoint[4] {

	//	{ m_vecTile[iIndex]->vPos.x,m_vecTile[iIndex]->vPos.y + (TILECY / 2.f), 0.f },
	//	{ m_vecTile[iIndex]->vPos.x + (TILECX / 2.f),m_vecTile[iIndex]->vPos.y, 0.f },
	//	{ m_vecTile[iIndex]->vPos.x,m_vecTile[iIndex]->vPos.y - (TILECY / 2.f), 0.f },
	//	{ m_vecTile[iIndex]->vPos.x - (TILECX / 2.f),m_vecTile[iIndex]->vPos.y , 0.f }
	//};
	//
	//// Y = aX + b-> b = y - ax;

	//float	fB[4] {

	//	vPoint[0].y - fGradient[0] * vPoint[0].x, 
	//	vPoint[1].y - fGradient[1] * vPoint[1].x,
	//	vPoint[2].y - fGradient[2] * vPoint[2].x,
	//	vPoint[3].y - fGradient[3] * vPoint[3].x	
	//};


	//// 0 == ax + b - y		: ���� �� �ִ� ����
	//// 0 > ax + b - y		: ���� ���� ���ʿ� �ִ� ����
	//// 0 < ax + b - y		: ���� ���� �Ʒ��ʿ� �ִ� ����

	//bool		bCheck[4] { false };

	//if (0 < fGradient[0] * vPos.x + fB[0] - vPos.y)
	//	bCheck[0] = true;

	//if (0 >= fGradient[1] * vPos.x + fB[1] - vPos.y)
	//	bCheck[1] = true;

	//if (0 > fGradient[2] * vPos.x + fB[2] - vPos.y)
	//	bCheck[2] = true;

	//if (0 < fGradient[3] * vPos.x + fB[3] - vPos.y)
	//	bCheck[3] = true;
	//
	//return bCheck[0] && bCheck[1] && bCheck[2] && bCheck[3];
	return false;
}

bool CTerrain::Picking_Dot(const D3DXVECTOR3 & vPos, const int & iIndex)
{
	/*D3DXVECTOR3		vPoint[4]{

		{ m_vecTile[iIndex]->vPos.x,m_vecTile[iIndex]->vPos.y + (TILECY / 2.f), 0.f },
		{ m_vecTile[iIndex]->vPos.x + (TILECX / 2.f),m_vecTile[iIndex]->vPos.y, 0.f },
		{ m_vecTile[iIndex]->vPos.x,m_vecTile[iIndex]->vPos.y - (TILECY / 2.f), 0.f },
		{ m_vecTile[iIndex]->vPos.x - (TILECX / 2.f),m_vecTile[iIndex]->vPos.y , 0.f }
	};

	D3DXVECTOR3			vDir[4] {
		
		vPoint[1] - vPoint[0],
		vPoint[2] - vPoint[1], 
		vPoint[3] - vPoint[2],
		vPoint[0] - vPoint[3],
	};

	D3DXVECTOR3			vNormal[4]{
		{ -vDir[0].y, vDir[0].x, 0.f},
		{ -vDir[1].y, vDir[1].x, 0.f },
		{ -vDir[2].y, vDir[2].x, 0.f },
		{ -vDir[3].y, vDir[3].x, 0.f },
	};

	D3DXVECTOR3			vMouseDir[4]{

		vPos - vPoint[0],
		vPos - vPoint[1],
		vPos - vPoint[2],
		vPos - vPoint[3]
	};

	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3Normalize(&vNormal[i], &vNormal[i]);
		D3DXVec3Normalize(&vMouseDir[i], &vMouseDir[i]);
	}

	for (int i = 0; i < 4; ++i)
	{
		if (0.f < D3DXVec3Dot(&vNormal[i], &vMouseDir[i]))
			return false;
	}
*/
	return true;
}
