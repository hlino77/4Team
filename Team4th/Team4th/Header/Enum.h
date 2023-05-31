#pragma once

enum TEXTYPE	{ TEX_SINGLE, TEX_MULTI, TEX_END };

enum  class OBJID { OBJ_BUILDING, OBJ_UNIT_GROUND, OBJ_UNIT_AIR, OBJ_ONCURSOR, OBJ_TILE, OBJ_MOUSE ,OBJ_END };
//enum  class OBJID     {  OBJ_BUILDING, OBJ_UNIT_GROUND, OBJ_UNIT_AIR, OBJ_ONCURSOR, OBJ_END };
//enum  OBJID		{ OBJ_PLAYER, OBJ_BULLET, OBJ_MONSTER, OBJ_MOUSE, OBJ_SHIELD, OBJ_UI, OBJ_END };

enum class TOOLTYPE	{ TOOL_TERRAIN, TOOL_BUILDING, TOOL_UNIT, TOOL_END};

enum class GRID_STATE { NORMAL, SMALL, NONE, TYPEEND };

enum class SETCOL_STATE { NONE, DELETECOL, COLLIDER, TYPEEND };