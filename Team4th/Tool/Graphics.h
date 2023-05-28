#pragma once
#include "Component.h"

class CToolView;
class CGraphics :
	public CComponent
{
public:
	CGraphics();
	virtual ~CGraphics();

	void	Render(const TCHAR * pObjKey, const TCHAR * pStateKey, const int & iCount);

	// CComponent을(를) 통해 상속됨
	virtual void Initialize(CGameObject * _pHost) override;

	void		Set_MainView(CToolView* pMainView) { m_pMainView = pMainView; }
	void		Set_Ratio(D3DXMATRIX* pOut, float fRatioX, float fRatioY);

private:
	CToolView*	m_pMainView = nullptr;
};

