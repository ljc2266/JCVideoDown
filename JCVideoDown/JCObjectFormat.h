#pragma once
#include "jcvideostrategy.h"
class CJCObjectFormat :
	public CJCVideoStrategy
{
public:
	CJCObjectFormat(void);
	~CJCObjectFormat(void);
protected:
	vector<CString> GetVideoUrls(CString strUrlCode);
};

