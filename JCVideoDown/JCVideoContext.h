#pragma once
#include "JCVideoStrategy.h"
class CJCVideoContext
{
private:
	CJCVideoStrategy* m_pJCVideoStrategy;
public:
	CJCVideoContext(CJCVideoStrategy* pStrategy);
	~CJCVideoContext(void);
	vector<CString> GetVideoUrls(CString strUrlCode);
	void AddSrcVector2Dest(vector<CString> vecSrc,vector<CString>& vecDest);
};

