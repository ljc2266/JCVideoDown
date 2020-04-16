#pragma once
#include "jcvideostrategy.h"
class CJCVideoFormat :
	public CJCVideoStrategy
{
public:
	CJCVideoFormat(void);
	~CJCVideoFormat(void);
protected:
	vector<CString> GetVideoUrls(CString strUrlCode);
};

