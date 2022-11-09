#pragma once

class CObj;
class CUnit;
template<typename T>
class CAbstractFactory
{
public:
	static CObj* Create()
	{
		CObj* pObj = new T;
		pObj->Initialize();
		return pObj;
	}
	static CObj* Create(float _x, float _y)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_x, _y);
		return pObj;
	}
	// Ÿ�� ����
	static CObj* Create_Tile(float _x, float _y)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_x, _y);
		return pObj;
	}
	// �� ����
	static CUnit* Create_Block(float _x, float _y, const BLOCK::PROPERTY& _eProperty)
	{
		CUnit* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_x, _y);
		SCAST<class CBlock*>(pObj)->Set_BlockPro(_eProperty);
		return pObj;
	}
	
};
// __ABSCRACTFACTORY
