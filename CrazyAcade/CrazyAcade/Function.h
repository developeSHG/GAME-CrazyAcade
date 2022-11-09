#pragma once

class CObj;

template <typename T>
inline T SCAST(CObj* _pObj)
{
	return static_cast<T>(_pObj);
}
template <typename T>
inline T DCAST(CObj* _pObj)
{
	return dynamic_cast<T>(_pObj);
}

class CMyStrCmp
{
public:
	CMyStrCmp() {}
	CMyStrCmp(const TCHAR* pString)
		: m_pString(pString)
	{}
	~CMyStrCmp(){}

public:
	template<typename T>
	bool operator()(T& rObj)
	{
		return !lstrcmp(rObj.first, m_pString);
	}

private:
	const TCHAR* m_pString;
};