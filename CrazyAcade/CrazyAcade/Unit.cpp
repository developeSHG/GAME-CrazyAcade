#include "stdafx.h"
#include "Unit.h"

CUnit::CUnit()
	: m_dwGameStartTime(NULL)
	, m_fSpeed(0.f)
	, m_bBallonOn(FALSE)
	, m_bBubbleState(FALSE)
	, m_bPushState(FALSE)
	, m_bCreateTime(NULL)
	, m_bActingCreate(false)
{
}


CUnit::~CUnit()
{
}

