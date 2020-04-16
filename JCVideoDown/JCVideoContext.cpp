#include "StdAfx.h"
#include "JCVideoContext.h"


CJCVideoContext::CJCVideoContext(CJCVideoStrategy* pStrategy)
	:m_pJCVideoStrategy(pStrategy)
{
}


CJCVideoContext::~CJCVideoContext(void)
{
	if (m_pJCVideoStrategy)
	{
		delete m_pJCVideoStrategy;
		m_pJCVideoStrategy = NULL;
	}
}

vector<CString> CJCVideoContext::GetVideoUrls(CString strUrlCode)
{
	if (m_pJCVideoStrategy)
	{
		return m_pJCVideoStrategy->GetVideoUrls(strUrlCode);
	}
	else
		return vector<CString>();
}

void CJCVideoContext::AddSrcVector2Dest(vector<CString> vecSrc,vector<CString>& vecDest)
{
	if (m_pJCVideoStrategy)
	{
		return m_pJCVideoStrategy->AddSrcVector2Dest(vecSrc,vecDest);
	}
}