#include "stdafx.h"
#include "GroundUnit.h"
#include "Transform.h"
#include "Collider.h"
#include "ObjectMgr.h"
#include "TextureMgr.h"
#include "CameraMgr.h"
#include "Device.h"
#include "Include.h"

CGroundUnit::CGroundUnit() : m_iPathIndex(0)
{
}


CGroundUnit::~CGroundUnit()
{
}

int CGroundUnit::Update()
{
	if (UNIT_STATE::IDLE == m_eState)
		m_vTargetPos = m_pTransform->Position();
	else if (UNIT_STATE::MOVE == m_eState)
	{
		if (!m_iPathIndex)
		{
			AStar();
			++m_iPathIndex;
		}

		if (m_iPathIndex < m_vecPath.size())
		{
			int iIndex = m_vecPath[m_iPathIndex].y * TILEX + m_vecPath[m_iPathIndex].x;
			m_vTargetPos = CObjectMgr::Get_Instance()->GetTerrain().Get_TileList()[iIndex]->vPos;

			if (D3DXVec3Length(&(m_vTargetPos - m_pTransform->Position())) < 2.f * m_tData.fMovefSpeed)
				++m_iPathIndex;
		}		
		else
		{
			InitPath();
			m_vTargetPos = m_pTransform->Position();
			m_eState = UNIT_STATE::IDLE;
		}
		
		Move();
	}

	return 0;
}

int CGroundUnit::LateUpdate()
{
	if (UNIT_STATE::IDLE != m_eState)
		Move_Frame();

	return 0;
}

void CGroundUnit::Render()
{
	if (CObjectMgr::Get_Instance()->m_bPath)
	{
		D3DXMATRIX	matWorld, matScale, matTrans;

		float m_fScrollX = CCameraMgr::Get_Instance()->Get_ScrollX();
		float m_fScrollY = CCameraMgr::Get_Instance()->Get_ScrollY();

		vector<TILE*>&	vecTile = CObjectMgr::Get_Instance()->GetTerrain().Get_TileList();
		const TEXINFO*	pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"Col_Blue");

		for (auto& iter : m_vecPath)
		{
			int iIndex = iter.y * TILEX + iter.x;

			D3DXMatrixIdentity(&matWorld);
			D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
			D3DXMatrixTranslation(&matTrans,
				int(vecTile[iIndex]->vPos.x + m_fScrollX), // 0�� ��� x ��ũ�� �� ����
				int(vecTile[iIndex]->vPos.y + m_fScrollY), // 1�� ��� y ��ũ�� �� ����
				0.f);

			matWorld = matScale * matTrans;

			CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

			CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
				nullptr,							// ����� �̹��� ������ ���� Rect �ּ�, null�� ��� �̹����� 0, 0 �������� ���
				&D3DXVECTOR3(16.0f, 16.0f, 0.f),	// ����� �̹����� �߽��࿡ ���� vector3 �ּ�, null�� ��� �̹����� 0, 0�� �߽� ��ǥ
				nullptr,							// ��ġ ��ǥ�� ���� vector3 �ּ�, null�� ��� ��ũ�� ���� 0, 0��ǥ ���
				D3DCOLOR_ARGB(50, 255, 255, 255));	// ����� �̹����� ���� ���� ��, 0xffffffff�� �Ѱ��ָ� ���� ���� ����
		}
	}
}

void CGroundUnit::OnCollisionEnter(CCollider * _pOther)
{
	CGameObject* pOtherObj = _pOther->GetHost();

	if (OBJID::OBJ_MOUSE == pOtherObj->GetType())	return;
	if (UNIT_STATE::IDLE == m_eState)				return;

	D3DXVECTOR3 vOtherPos = pOtherObj->GetCollider()->GetPosition();
	D3DXVECTOR3 vOtherScale = pOtherObj->GetCollider()->GetScale();

	D3DXVECTOR3 vThisPos = GetCollider()->GetPosition();
	D3DXVECTOR3 vThisScale = GetCollider()->GetScale();

	float fWidth = fabs(vOtherPos.x - vThisPos.x);
	float fHeight = fabs(vOtherPos.y - vThisPos.y);
	float fRadiusX = (vOtherScale.x / 2.f + vThisScale.x / 2.f) - fWidth;
	float fRadiusY = (vOtherScale.y / 2.f + vThisScale.y / 2.f) - fHeight;

	if (fRadiusX < fRadiusY)
	{
		if (vOtherPos.x < vThisPos.x)
			m_pTransform->Translate(D3DXVECTOR3(fRadiusX, 0.f, 0.f));
		else
			m_pTransform->Translate(D3DXVECTOR3(-fRadiusX, 0.f, 0.f));
	}
	else
	{
		if (vOtherPos.y < vThisPos.y)
			m_pTransform->Translate(D3DXVECTOR3(0.f, fRadiusY, 0.f));
		else
			m_pTransform->Translate(D3DXVECTOR3(0.f, -fRadiusY, 0.f));
	}
}

void CGroundUnit::OnCollisionStay(CCollider * _pOther)
{
	CGameObject* pOtherObj = _pOther->GetHost();

	if (OBJID::OBJ_MOUSE == pOtherObj->GetType())	return;
	if (UNIT_STATE::IDLE == m_eState)				return;

	D3DXVECTOR3 vOtherPos = pOtherObj->GetCollider()->GetPosition();
	D3DXVECTOR3 vOtherScale = pOtherObj->GetCollider()->GetScale();

	D3DXVECTOR3 vThisPos = GetCollider()->GetPosition();
	D3DXVECTOR3 vThisScale = GetCollider()->GetScale();

	float fWidth = fabs(vOtherPos.x - vThisPos.x);
	float fHeight = fabs(vOtherPos.y - vThisPos.y);
	float fRadiusX = (vOtherScale.x / 2.f + vThisScale.x / 2.f) - fWidth;
	float fRadiusY = (vOtherScale.y / 2.f + vThisScale.y / 2.f) - fHeight;

	if (fRadiusX < fRadiusY)
	{
		if (vOtherPos.x < vThisPos.x)
			m_pTransform->Translate(D3DXVECTOR3(fRadiusX, 0.f, 0.f));
		else
			m_pTransform->Translate(D3DXVECTOR3(-fRadiusX, 0.f, 0.f));
	}
	else
	{
		if (vOtherPos.y < vThisPos.y)
			m_pTransform->Translate(D3DXVECTOR3(0.f, fRadiusY, 0.f));
		else
			m_pTransform->Translate(D3DXVECTOR3(0.f, -fRadiusY, 0.f));
	}
}

void CGroundUnit::OnCollisionExit(CCollider * _pOther)
{
}

void CGroundUnit::OnCollisionEnter(TILE * _pTIle)
{
	D3DXVECTOR3 vOtherPos = _pTIle->vPos;
	D3DXVECTOR3 vOtherScale = _pTIle->vSize;

	D3DXVECTOR3 vThisPos = GetCollider()->GetPosition();
	D3DXVECTOR3 vThisScale = GetCollider()->GetScale();

	float fWidth = fabs(vOtherPos.x - vThisPos.x);
	float fHeight = fabs(vOtherPos.y - vThisPos.y);
	float fRadiusX = (vOtherScale.x / 2.f + vThisScale.x / 2.f) - fWidth;
	float fRadiusY = (vOtherScale.y / 2.f + vThisScale.y / 2.f) - fHeight;

	if (fRadiusX < fRadiusY)
	{
		if (vOtherPos.x < vThisPos.x)
			m_pTransform->Translate(D3DXVECTOR3(fRadiusX, 0.f, 0.f));
		else
			m_pTransform->Translate(D3DXVECTOR3(-fRadiusX, 0.f, 0.f));
	}
	else
	{
		if (vOtherPos.y < vThisPos.y)
			m_pTransform->Translate(D3DXVECTOR3(0.f, fRadiusY, 0.f));
		else
			m_pTransform->Translate(D3DXVECTOR3(0.f, -fRadiusY, 0.f));
	}
}

void CGroundUnit::OnCollisionStay(TILE * _pTIle)
{
	D3DXVECTOR3 vOtherPos = _pTIle->vPos;
	D3DXVECTOR3 vOtherScale = _pTIle->vSize;

	D3DXVECTOR3 vThisPos = GetCollider()->GetPosition();
	D3DXVECTOR3 vThisScale = GetCollider()->GetScale();

	float fWidth = fabs(vOtherPos.x - vThisPos.x);
	float fHeight = fabs(vOtherPos.y - vThisPos.y);
	float fRadiusX = (vOtherScale.x / 2.f + vThisScale.x / 2.f) - fWidth;
	float fRadiusY = (vOtherScale.y / 2.f + vThisScale.y / 2.f) - fHeight;

	if (fRadiusX < fRadiusY)
	{
		if (vOtherPos.x < vThisPos.x)
			m_pTransform->Translate(D3DXVECTOR3(fRadiusX, 0.f, 0.f));
		else
			m_pTransform->Translate(D3DXVECTOR3(-fRadiusX, 0.f, 0.f));
	}
	else
	{
		if (vOtherPos.y < vThisPos.y)
			m_pTransform->Translate(D3DXVECTOR3(0.f, fRadiusY, 0.f));
		else
			m_pTransform->Translate(D3DXVECTOR3(0.f, -fRadiusY, 0.f));
	}
}

void CGroundUnit::OnCollisionExit(TILE * _pTIle)
{
}

void CGroundUnit::Move()
{
	D3DXVECTOR3 vDistance = m_vTargetPos - m_pTransform->Position();
	float&	fSpeed = m_tData.fMovefSpeed;

	D3DXVECTOR3 vDistNorm;
	D3DXVec3Normalize(&vDistNorm, &vDistance);
	m_pTransform->Translate(0.5f * fSpeed * vDistNorm);
}

bool CGroundUnit::Movable(Pos pos)
{
	if (pos.x < 0 || pos.y < 0 || pos.x >= TILEX || pos.y >= TILEY || CObjectMgr::Get_Instance()->GetTerrain().Get_TileList()[pos.y * TILEX + pos.x]->bCollider)
		return false;
	return true;
}

void CGroundUnit::AStar()
{
	Pos start;
	start.x = ((int)m_pTransform->Position().x / TILECX);
	start.y = ((int)m_pTransform->Position().y / TILECY);
	Pos dest;
	dest.x = (int)m_vTargetPos.x / TILECX;
	dest.y = (int)m_vTargetPos.y / TILECY;

	enum
	{
		DIR_COUNT = 8
	};

	Pos front[] =
	{
		Pos{ 0, -1 },	// UP
		Pos{ -1, 0 },	// LEFT
		Pos{ 0, 1 },	// DOWN
		Pos{ 1, 0 },	// RIGHT
		Pos{ -1, -1 },	// UP_LEFT
		Pos{ -1, 1 },	// DOWN_LEFT
		Pos{ 1, 1 },	// DOWN_RIGHT
		Pos{ 1, -1 },	// UP_RIGHT
	};

	int cost[] =
	{
		10, // UP
		10, // LEFT
		10, // DOWN
		10, // RIGHT
		14,
		14,
		14,
		14
	};

	// ClosedList
	vector<vector<bool>> closed(TILEY, vector<bool>(TILEX, false));

	// best[y][x] -> ���ݱ��� (y, x)�� ���� ���� ���� ��� (���� ���� ����)
	vector<vector<int>> best(TILEY, vector<int>(TILEX, INT32_MAX));

	// �θ� ���� �뵵
	map<Pos, Pos> parent;

	// OpenList
	priority_queue<PQNode, vector<PQNode>, greater<PQNode>> pq;

	// �ʱⰪ
	{
		int g = 0;
		int h = 10 * (abs(dest.y - start.y) + abs(dest.x - start.x));
		/*D3DXVECTOR3 vHeuristic(m_vTargetPos - m_pTransform->Position());
		vHeuristic *= (10.f / 32.f);
		D3DXVec3Length(&vHeuristic);
		int h = D3DXVec3Length(&vHeuristic);*/
		pq.push(PQNode{ g + h, g, start });
		best[start.x][start.y] = g + h;
		parent[start] = start;
	}

	while (pq.empty() == false)
	{
		// ���� ���� �ĺ��� ã�´�
		PQNode node = pq.top();
		pq.pop();

		// �湮
		closed[node.pos.x][node.pos.y] = true;

		// �������� ���������� �ٷ� ����
		if (node.pos == dest)
			break;

		for (int dir = 0; dir < DIR_COUNT; dir++)
		{
			Pos nextPos = node.pos + front[dir];

			if (Movable(nextPos) == false)
				continue;
			if (closed[nextPos.x][nextPos.y])
				continue;

			int g = node.g + cost[dir];

			/*float fX = TILECX * (nextPos.x * TILEX) - 0.5f * TILECX;
			float fY = TILECY * (nextPos.y * TILEY) - 0.5f * TILECY;
			D3DXVECTOR3 vNextPos(fX, fY, 0.f);
			D3DXVECTOR3 vHeuristic(m_vTargetPos - vNextPos);
			vHeuristic *= (10.f / 32.f);
			D3DXVec3Length(&vHeuristic);
			int h = D3DXVec3Length(&vHeuristic);*/
			int h = 10 * (abs(dest.x - nextPos.x) + abs(dest.y - nextPos.y));
			// �ٸ� ��ο��� �� ���� ���� ã������ ��ŵ
			if (best[nextPos.x][nextPos.y] <= g + h)
				continue;

			// ���� ����
			best[nextPos.x][nextPos.y] = g + h;
			pq.push(PQNode{ g + h, g, nextPos });
			parent[nextPos] = node.pos;
		}
	}

	// �Ųٷ� �Ž��� �ö󰣴�
	Pos pos = dest;

	InitPath();

	while (true)
	{
		m_vecPath.push_back(pos);

		// �������� �ڽ��� �� �θ��̴�
		if (pos == parent[pos])
			break;

		pos = parent[pos];
	}

	std::reverse(m_vecPath.begin(), m_vecPath.end());
	int a = 0;
}
