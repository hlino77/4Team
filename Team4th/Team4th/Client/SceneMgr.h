#pragma once

#include "Include.h"

class CScene;
class CSceneMgr final
{
	DECLARE_SINGLETON(CSceneMgr)

private:
	CSceneMgr();
	~CSceneMgr();

public:
	void Initialize(CScene* _pScene);
	void Update();
	void LateUpdate();
	void Render();
	void Release();

public:
	CScene* GetScene() { return m_pScene; }

private:
	CScene* m_pScene;
};

