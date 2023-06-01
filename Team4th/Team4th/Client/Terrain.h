#pragma once

#include "Include.h"

class CTerrain
{
public:
	CTerrain();
	~CTerrain();

public:
	HRESULT		Initialize(void);
	void		Update(void);
	void		Render(void);

	void		Collider_Render(void);

	void		Release(void);


public:
	void		Set_Ratio(D3DXMATRIX* pOut, float fRatioX, float fRatioY);

public:
	vector<TILE*>&		Get_TileList() { return m_vecTile; }

	void	Set_ColState(SETCOL_STATE _ColState) { m_ColState = _ColState; }


private:
	vector<TILE*>		m_vecTile;
	TILE*				m_pMapInfo;

	SETCOL_STATE		m_ColState;

	void		Load_TileData(void);
	bool		m_bColRender;

};
