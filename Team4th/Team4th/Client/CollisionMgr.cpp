#include "stdafx.h"
#include "CollisionMgr.h"
#include "GameObject.h"
#include "Collider.h"
#include "ObjectMgr.h"
#include "Terrain.h"

IMPLEMENT_SINGLETON(CCollisionMgr)

CCollisionMgr::CCollisionMgr()
{
}

CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::LateUpdate()
{
	for (UINT iRow = 0; iRow < (UINT)OBJID::OBJ_END; ++iRow)
	{
		for (UINT iCol = iRow; iCol < (UINT)OBJID::OBJ_END; ++iCol)
		{
			if (m_arrCheck[iRow] & (1 << iCol))
			{
				CheckCollisionByType((OBJID)iRow, (OBJID)iCol);
			}
		}
	}
}

void CCollisionMgr::CheckGroup(OBJID _eLeft, OBJID _eRight)
{
	UINT iRow = (UINT)_eLeft;
	UINT iCol = (UINT)_eRight;

	if (iCol < iRow)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}

	if (m_arrCheck[iRow] & (1 << iCol))
	{
		m_arrCheck[iRow] &= ~(1 << iCol);
	}
	else
	{
		m_arrCheck[iRow] |= (1 << iCol);
	}
}

void CCollisionMgr::Reset()
{
	memset(m_arrCheck, 0, sizeof(UINT) * (UINT)OBJID::OBJ_END);
}

bool CCollisionMgr::IsCollision(CCollider * _pLeft, CCollider * _pRight)
{
	D3DXVECTOR3 vLeftPos = _pLeft->GetPosition();
	D3DXVECTOR3 vLeftScale = _pLeft->GetScale();

	D3DXVECTOR3 vRightPos = _pRight->GetPosition();
	D3DXVECTOR3 vRightScale = _pRight->GetScale();

	if ((abs(vRightPos.x - vLeftPos.x) <= (vLeftScale.x + vRightScale.x) / 2.f
		&& (abs(vRightPos.y - vLeftPos.y) <= (vLeftScale.y + vRightScale.y) / 2.f)))
	{
		return true;
	}
	return false;
}

bool CCollisionMgr::IsTileCollision(CCollider * _pLeft, TILE* _pRight)
{
	D3DXVECTOR3 vLeftPos = _pLeft->GetPosition();
	D3DXVECTOR3 vLeftScale = _pLeft->GetScale();

	D3DXVECTOR3 vRightPos = _pRight->vPos;
	D3DXVECTOR3 vRightScale = _pRight->vSize;

	if ((abs(vRightPos.x - vLeftPos.x) <= (vLeftScale.x + vRightScale.x) / 2.f
		&& (abs(vRightPos.y - vLeftPos.y) <= (vLeftScale.y + vRightScale.y) / 2.f)))
	{
		return true;
	}
	return false;
}

void CCollisionMgr::CheckCollisionByType(OBJID _eTypeLeft, OBJID _eTypeRight)
{
	const vector<CGameObject*>& vecLeft = CObjectMgr::Get_Instance()->GetObjList(_eTypeLeft);
	if (OBJID::OBJ_TILE != _eTypeRight)
	{
		const vector<CGameObject*>& vecRight = CObjectMgr::Get_Instance()->GetObjList(_eTypeRight);

		map<ULONGLONG, bool>::iterator iter;

		for (size_t i = 0; i < vecLeft.size(); ++i)
		{
			CCollider* pLeftCol = vecLeft[i]->GetCollider();

			if (nullptr == pLeftCol)
				continue;

			for (size_t j = 0; j < vecRight.size(); ++j)
			{
				if (nullptr == vecRight[j]->GetCollider() || vecLeft[i] == vecRight[j])
				{
					continue;
				}

				CCollider* pRightCol = vecRight[j]->GetCollider();

				COLLIDER_ID ID;
				ID.Left_id = pLeftCol->GetID();
				ID.Right_id = pRightCol->GetID();

				iter = m_mapColInfo.find(ID.ID);

				if (m_mapColInfo.end() == iter)
				{
					m_mapColInfo.insert(make_pair(ID.ID, false));
					iter = m_mapColInfo.find(ID.ID);
				}

				if (IsCollision(pLeftCol, pRightCol))
				{	// 현재 충돌 중
					if (iter->second)
					{	// 이전에도 충돌
						if (vecLeft[i]->IsDead() || vecRight[j]->IsDead())
						{	// 둘 중 하나 삭제 예정이면 충돌 해제
							pLeftCol->OnCollisionExit(pRightCol);
							pRightCol->OnCollisionExit(pLeftCol);
							iter->second = false;
						}
						else
						{
							pLeftCol->OnCollisionStay(pRightCol);
							pRightCol->OnCollisionStay(pLeftCol);
						}
					}
					else
					{	// 이전에는 충돌 x	// 근데 둘 중 하나 삭제 예정이면 충돌하지 않은 것으로 취급
						if (!vecLeft[i]->IsDead() && !vecRight[j]->IsDead())
						{
							pLeftCol->OnCollisionEnter(pRightCol);
							pRightCol->OnCollisionEnter(pLeftCol);
							iter->second = true;
						}
						else
						{
							pLeftCol->OnCollisionExit(pRightCol);
							pRightCol->OnCollisionExit(pLeftCol);
							iter->second = false;
						}
					}
				}
				else
				{		// 현재 충돌 x면
					if (iter->second)
					{	//이전에는 충돌하고 있었다.
						pLeftCol->OnCollisionExit(pRightCol);
						pRightCol->OnCollisionExit(pLeftCol);
						iter->second = false;
					}
				}
			}
		}
	}
	// -----------------구분선-----------------//
	else
	{
		const vector<TILE*>&  vecRight = CObjectMgr::Get_Instance()->GetTerrain().Get_TileList();

		map<ULONGLONG, bool>::iterator iter;

		for (size_t i = 0; i < vecLeft.size(); ++i)
		{
			CCollider* pLeftCol = vecLeft[i]->GetCollider();
			if (nullptr == pLeftCol)
				continue;

			D3DXVECTOR3 vPos = vecLeft[i]->GetCollider()->GetPosition();
			D3DXVECTOR3 vScale = vecLeft[i]->GetCollider()->GetScale();
			
			D3DXVECTOR3 vLT = vPos - vScale / 2.f;
			D3DXVECTOR3 vRB = vPos + vScale / 2.f;

			int iCX = (int)vScale.x / TILECX + 1;
			int iCY = (int)vScale.y / TILECY + 1;

			int iIndexLT_X = (int)vLT.x / TILECX;
			int iIndexLT_Y = (int)vLT.y / TILECY;

			for (int k = iIndexLT_Y - 1; k < iIndexLT_Y + iCY + 1; ++k)
			{
				for (int j = iIndexLT_X - 1; j < iIndexLT_X + iCX + 1; ++j)
				{
					if (k < 0 || j < 0)
						continue;

					int iIndex = k * TILEX + j;
					if (!vecRight[iIndex]->bCollider)
						continue;

					COLLIDER_ID ID;
					ID.Left_id = pLeftCol->GetID();
					ID.Right_id = vecRight[iIndex]->m_iID;

					iter = m_mapColInfo.find(ID.ID);

					if (m_mapColInfo.end() == iter)
					{
						m_mapColInfo.insert(make_pair(ID.ID, false));
						iter = m_mapColInfo.find(ID.ID);
					}

					if (IsTileCollision(pLeftCol, vecRight[iIndex]))
					{	// 현재 충돌 중
						if (iter->second)
						{	// 이전에도 충돌
							if (vecLeft[i]->IsDead() || !vecRight[iIndex]->bCollider)
							{	// 둘 중 하나 삭제 예정이면 충돌 해제
								pLeftCol->OnCollisionExit(vecRight[iIndex]);
								iter->second = false;
							}
							else
							{
								pLeftCol->OnCollisionStay(vecRight[iIndex]);
							}
						}
						else
						{	// 이전에는 충돌 x	// 근데 둘 중 하나 삭제 예정이면 충돌하지 않은 것으로 취급
							if (!vecLeft[i]->IsDead() && vecRight[iIndex]->bCollider)
							{
								pLeftCol->OnCollisionEnter(vecRight[iIndex]);
								iter->second = true;
							}
							else
							{
								pLeftCol->OnCollisionExit(vecRight[iIndex]);
								iter->second = false;
							}
						}
					}
					else
					{		// 현재 충돌 x면
						if (iter->second)
						{	//이전에는 충돌하고 있었다.
							pLeftCol->OnCollisionExit(vecRight[iIndex]);
							iter->second = false;
						}
					}
				}
			}
		}
	}
}
