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

	void		Grid_Render(void);
	void		NormalGrid_Render(void);
	void		SmallGrid_Render(void);
	void		Collider_Render(void);

	void		Release(void);


public:
	void		Set_MainView(CToolView* pMainView) { m_pMainView = pMainView; }
	void		Set_Ratio(D3DXMATRIX* pOut, float fRatioX, float fRatioY);


public:
	void	Set_GridState(GRID_STATE _GridType) { m_GridState = _GridType; }
	void	Set_ColState(SETCOL_STATE _ColState) { m_ColState = _ColState; }

	void	Tile_Change(const D3DXVECTOR3& vPos);

private:
	vector<TILE*>		m_vecTile;
	TILE*				m_pMapInfo;
	CToolView*			m_pMainView = nullptr;

	GRID_STATE			m_GridState;
	SETCOL_STATE		m_ColState;
};
