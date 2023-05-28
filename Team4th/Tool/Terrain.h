#pragma once

#include "Include.h"

class CToolView;
class CTerrain
{
public:
	CTerrain();
	~CTerrain();

public:
	HRESULT		Initialize(void);
	void		Update(void);
	void		Render(void);
	void		Mini_Render(void);
	void		Release(void);
	

public:
	void		Set_MainView(CToolView* pMainView) { m_pMainView = pMainView; }
	void		Set_Ratio(D3DXMATRIX* pOut, float fRatioX, float fRatioY);
//	void		Set_ZommScale(int _iZoomLevel, CPoint _pt) { m_iZoomLevel = _iZoomLevel; }

public:
	int		Get_TileIndex(const D3DXVECTOR3& vPos);
	void	Tile_Change(const D3DXVECTOR3& vPos, const int& iDrawID);
	bool	Picking(const D3DXVECTOR3& vPos, const int& iIndex);
	bool	Picking_Dot(const D3DXVECTOR3& vPos, const int& iIndex);
private:
	//vector<TILE*>		m_vecTile;
	TILE*				m_pMapInfo;
	CToolView*			m_pMainView = nullptr;

	//int					m_iZoomLevel;
	//CPoint				m_cZoomPoint;
};

