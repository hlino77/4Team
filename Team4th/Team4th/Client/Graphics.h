#pragma once
#include "Component.h"

class CToolView;
class CGraphics :
	public CComponent
{
public:
	CGraphics();
	CGraphics(const CGraphics& rhs);
	virtual ~CGraphics();

	void	Render(const TCHAR * pObjKey, const TCHAR * pStateKey, const int & iCount);

	// CComponent��(��) ���� ��ӵ�
	virtual void Initialize(CGameObject * _pHost) override;

private:
	CToolView*	m_pMainView = nullptr;
};

