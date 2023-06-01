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
	float		fFrame; // �������� ���� ���� ����
	float		fMax;	// �ִ� �̹����� ������ ��

}FRAME;

typedef struct tagTexture
{
	LPDIRECT3DTEXTURE9		pTexture;   // �� ��ü

	D3DXIMAGE_INFO			tImgInfo;	// ����ü

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

	int		iAttack;		// ���ݷ�
	int		iDeffnse;		// ����

	float	fMovefSpeed;	// �̵� �ӵ�
	float	fAttackSpeed;	// ���� �ӵ�

	int		iSightRange;	// �þ� �Ÿ�
	int		iFireRange;		// ��Ÿ�

	int		iMaxHp;			// �ִ� ü��
	int		iHp;			// ü��
	int		iMaxShield;		// �ִ� ��ȣ��
	int		iShield;		// ��ȣ��
	int		iMaxEnergy;		// �ִ� ������
	int		iEnergy;		// ������
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