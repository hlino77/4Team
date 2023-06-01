#include "stdafx.h"
#include "GroundUnit.h"
#include "Transform.h"
#include "Collider.h"
#include "ObjectMgr.h"
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

		if (m_iPathIndex < m_vecPath.size() - 1)
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
	m_pTransform->Translate(fSpeed * vDistNorm);
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

	// best[y][x] -> 지금까지 (y, x)에 대한 가장 좋은 비용 (작을 수록 좋음)
	vector<vector<int>> best(TILEY, vector<int>(TILEX, INT32_MAX));

	// 부모 추적 용도
	map<Pos, Pos> parent;

	// OpenList
	priority_queue<PQNode, vector<PQNode>, greater<PQNode>> pq;

	// 초기값
	{
		int g = 0;
		int h = 10 * (abs(dest.y - start.y) + abs(dest.x - start.x));
		pq.push(PQNode{ g + h, g, start });
		best[start.x][start.y] = g + h;
		parent[start] = start;
	}

	while (pq.empty() == false)
	{
		// 제일 좋은 후보를 찾는다
		PQNode node = pq.top();
		pq.pop();

		// 방문
		closed[node.pos.x][node.pos.y] = true;

		// 목적지에 도착했으면 바로 종료
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

			int h = 10 * (abs(dest.x - nextPos.x) + abs(dest.y - nextPos.y));
			// 다른 경로에서 더 빠른 길을 찾았으면 스킵
			if (best[nextPos.x][nextPos.y] <= g + h)
				continue;

			// 예약 진행
			best[nextPos.x][nextPos.y] = g + h;
			pq.push(PQNode{ g + h, g, nextPos });
			parent[nextPos] = node.pos;
		}
	}

	// 거꾸로 거슬러 올라간다
	Pos pos = dest;

	InitPath();

	while (true)
	{
		m_vecPath.push_back(pos);

		// 시작점은 자신이 곧 부모이다
		if (pos == parent[pos])
			break;

		pos = parent[pos];
	}

	std::reverse(m_vecPath.begin(), m_vecPath.end());
	int a = 0;
}
