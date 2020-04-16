#pragma once
#include "jcvideostrategy.h"
class CJCEmbedFormat :
	public CJCVideoStrategy
{
public:
	CJCEmbedFormat(void);
	~CJCEmbedFormat(void);
protected:
	vector<CString> GetVideoUrls(CString strUrlCode);
};

