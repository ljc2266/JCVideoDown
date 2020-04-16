#include "StdAfx.h"
#include "JCEmbedFormat.h"


CJCEmbedFormat::CJCEmbedFormat(void)
{
}


CJCEmbedFormat::~CJCEmbedFormat(void)
{
}

vector<CString> CJCEmbedFormat::GetVideoUrls(CString strUrlCode)
{
	CString strElement;
	vector<CString> vecUrl,vecAllUrl;
	while(!(strElement = SeparateLabel(strUrlCode,_T("embed"))).IsEmpty())
	{
		vecUrl = GetElementVideoUrl(strElement,_T("src="));
		AddSrcVector2Dest(vecUrl,vecAllUrl);
	}
	return vecAllUrl;
}