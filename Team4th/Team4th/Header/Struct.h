#pragma once
#include "Enum.h"

typedef struct tagInfo
{
	D3DXVECTOR3		vPos;
	D3DXVECTOR3		vDir;
	D3DXVECTOR3		vLook;
	D3DXVECTOR3		vSize;

	D3DXMATRIX		matWorld;
}INFO;

typedef	struct tagFrame
{
	float		fFrame; // 프레임을 세기 위한 변수
	float		fMax;	// 최대 이미지의 프레임 수

}FRAME;

typedef struct tagTexture
{
	LPDIRECT3DTEXTURE9		pTexture;   // 컴 객체

	D3DXIMAGE_INFO			tImgInfo;	// 구조체

}TEXINFO;

typedef struct tagTile
{
	OBJID		eType;

	D3DXVECTOR3	vPos;
	D3DXVECTOR3 vSize;

	D3DXVECTOR3 vPoint[5];
	D3DXVECTOR3 vOriginPoint[5];

	bool		bCollider;
	UINT		m_iID;

	BYTE		byOption;
	BYTE		byDrawID;
}TILE;



typedef	struct tagUnitData
{
#ifndef _AFX
	wstring		strName;
#else
	CString	strName;
#endif

	int		iAttack;		// 공격력
	int		iDeffnse;		// 방어력

	float	fMovefSpeed;	// 이동 속도
	float	fAttackSpeed;	// 공격 속도

	int		iSightRange;	// 시야 거리
	int		iFireRange;		// 사거리

	int		iMaxHp;			// 최대 체력
	int		iHp;			// 체력
	int		iMaxShield;		// 최대 보호막
	int		iShield;		// 보호막
	int		iMaxEnergy;		// 최대 에너지
	int		iEnergy;		// 에너지
}UNITDATA;

typedef struct tagTexturePath
{
	wstring		wstrObjKey		= L"";
	wstring		wstrStateKey	= L"";
	wstring		wstrPath = L"";
	int			iCount = 0;

}IMGPATH;


static D3DXVECTOR3		Get_Mouse()
{
	POINT	Pt{};

	GetCursorPos(&Pt);
	ScreenToClient(g_hWnd, &Pt);

	return D3DXVECTOR3((float)Pt.x, (float)Pt.y, 0.f);
}

struct Pos
{
	Pos() : x(0), y(0) {};
	Pos(int _x, int _y) { x = _x; y = _y; }

	bool operator==(Pos& other)
	{
		return y == other.y && x == other.x;
	}

	bool operator!=(Pos& other)
	{
		return !(*this == other);
	}

	bool operator<(const Pos& other) const
	{
		if (y != other.y)
			return y < other.y;
		return x < other.x;
	}

	Pos operator+(Pos& other)
	{
		Pos ret;
		ret.y = y + other.y;
		ret.x = x + other.x;
		return ret;
	}

	Pos& operator+=(Pos& other)
	{
		y += other.y;
		x += other.x;
		return *this;
	}

	int y;
	int x;
};

struct PQNode
{
	bool operator<(const PQNode& other) const { return f < other.f; }
	bool operator>(const PQNode& other) const { return f > other.f; }

	int	f; // f = g + h
	int	g;
	Pos	pos;
};