#pragma once
#include <vector>
using namespace std;
class CJCVideoStrategy
{
public:
	CJCVideoStrategy(void);
	virtual ~CJCVideoStrategy(void);
	virtual vector<CString> GetVideoUrls(CString strUrlCode) = 0;
	void AddSrcVector2Dest(vector<CString> vecSrc,vector<CString>& vecDest);
protected:
	CString SeparateLabel(CString& strUrlCode,CString strLabel);
	vector<CString> GetElementVideoUrl(CString strElement,CString strLabel);
private:
	CString FormatElement(CString strElement);
};

