#pragma once
#include "Scene.h"
#include "Terrain.h"

class CGameScene : public CScene
{
public:
	CGameScene();
	virtual ~CGameScene();

public:
	virtual HRESULT Ready_Scene()		override;
	virtual void Update_Scene()			override;
	virtual void Late_Update_Scene()	override;
	virtual void Render_Scene()			override;
	virtual void Release_Scene()		override;

private:
	HRESULT	LoadUnitData();
};

