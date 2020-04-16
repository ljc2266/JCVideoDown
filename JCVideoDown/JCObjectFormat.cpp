#include "StdAfx.h"
#include "JCObjectFormat.h"


CJCObjectFormat::CJCObjectFormat(void)
{
}


CJCObjectFormat::~CJCObjectFormat(void)
{
}

vector<CString> CJCObjectFormat::GetVideoUrls(CString strUrlCode)
{
	CString strElement;
	vector<CString> vecUrl,vecAllUrl;
	while(!(strElement = SeparateLabel(strUrlCode,_T("object"))).IsEmpty())
	{
		vecUrl = GetElementVideoUrl(strElement,_T("paramname=\"filename\"value="));
		AddSrcVector2Dest(vecUrl,vecAllUrl);
	}
	return vecAllUrl;
}