#include "StdAfx.h"
#include "JCVideoStrategy.h"


CJCVideoStrategy::CJCVideoStrategy(void)
{
}


CJCVideoStrategy::~CJCVideoStrategy(void)
{
}

CString CJCVideoStrategy::FormatElement(CString strElement)
{
	int length = strElement.GetLength();
	for (int i = length;i>=0;i--)
	{
		if (strElement[i]=='\t'||strElement[i]==' '||strElement[i]=='\r'||strElement[i]=='\n')
		{
			strElement.Delete(i,1);
		}
	}
	int nPos = -1;
	strElement.Replace(_T("&amp;"),_T("&"));
	return strElement;
}

vector<CString> CJCVideoStrategy::GetElementVideoUrl(CString strElement,CString strLabel)
{
	vector<CString> vecUrl;
	int nPos = strElement.Find(strLabel);
	while ((nPos = strElement.Find(strLabel)) > -1)
	{
		strElement = strElement.Mid(nPos+strLabel.GetLength());
		if (strElement[0] == '\"')
		{
			strElement = strElement.Mid(1);
			int nElementPos = strElement.Find(_T("\""));
			if (nElementPos > -1)
			{
				vecUrl.push_back(strElement.Left(nElementPos));
				strElement = strElement.Mid(nElementPos + 1);
			}
		}
		else if (strElement[0] == '\'')
		{
			int nElementPos = strElement.Find(_T("\'"));
			if (nElementPos > -1)
			{
				vecUrl.push_back(strElement.Left(nElementPos));
				strElement = strElement.Mid(nElementPos + 1);
			}
		}
		else
			break;
	}
	return vecUrl;
}

CString CJCVideoStrategy::SeparateLabel(CString& strUrlCode,CString strLabel)
{
	CString strElement;
	int nPos = strUrlCode.Find(_T("<")+strLabel);
	if (nPos > -1)
	{
		if (strUrlCode.GetLength()>strLabel.GetLength())
		{
			strElement = strUrlCode.Mid(nPos);
			nPos = strElement.Find('>');
			if (nPos > 0)
			{
				if (strElement[nPos-1]=='/')
				{
					strUrlCode = strElement.Mid(nPos+1);
					strElement = strElement.Left(nPos);
					return FormatElement(strElement);
				}
				else
				{
					nPos = strElement.Find(_T("</")+strLabel+_T(">"));
					if (nPos > -1)
					{
						strUrlCode = strElement.Mid(nPos+1);
						strElement = strElement.Left(nPos);
						return FormatElement(strElement);
					}
				}
			}
		}
	}
	return _T("");
}

void CJCVideoStrategy::AddSrcVector2Dest(vector<CString> vecSrc,vector<CString>& vecDest)
{
	for (int i=0;i<(int)vecSrc.size();i++)
	{
		vecDest.push_back(vecSrc[i]);
	}
}