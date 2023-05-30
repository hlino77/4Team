#pragma once
#include "Include.h"

class CGameObject;
class CComponent
{
public:
	CComponent() = default;
	virtual ~CComponent();

	CComponent(CGameObject* _pHost) : m_pHost(_pHost) {}

	virtual void Initialize(CGameObject* _pHost) { m_pHost = _pHost; }
	CGameObject*	GetHost() { return m_pHost; }
	void			SetHost(CGameObject* _pHost) { m_pHost = _pHost; }

protected:
	CGameObject*	m_pHost;
};

