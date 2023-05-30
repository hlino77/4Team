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

	

	void		Collider_Render(void);

	void		Release(void);


public:
	void		Set_MainView(CToolView* pMainView) { m_pMainView = pMainView; }
	void		Set_Ratio(D3DXMATRIX* pOut, float fRatioX, float fRatioY);


public:
	vector<TILE*>&		Get_TileList() { return m_vecTile; }

	void	Set_ColState(SETCOL_STATE _ColState) { m_ColState = _ColState; }


private:
	vector<TILE*>		m_vecTile;
	TILE*				m_pMapInfo;
	CToolView*			m_pMainView = nullptr;

	SETCOL_STATE		m_ColState;
};
