#include "StdAfx.h"
#include "JCVideoFormat.h"


CJCVideoFormat::CJCVideoFormat(void)
{
}


CJCVideoFormat::~CJCVideoFormat(void)
{
}

vector<CString> CJCVideoFormat::GetVideoUrls(CString strUrlCode)
{
	CString strElement;
	vector<CString> vecUrl,vecAllUrl;
	while(!(strElement = SeparateLabel(strUrlCode,_T("video"))).IsEmpty())
	{
		vecUrl = GetElementVideoUrl(strElement,_T("src="));
		AddSrcVector2Dest(vecUrl,vecAllUrl);
		vecUrl = GetElementVideoUrl(strElement,_T("origin_src="));
		AddSrcVector2Dest(vecUrl,vecAllUrl);
	}
	return vecAllUrl;
}