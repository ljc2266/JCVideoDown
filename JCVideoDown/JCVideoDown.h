
// JCVideoDown.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CJCVideoDownApp:
// �йش����ʵ�֣������ JCVideoDown.cpp
//

class CJCVideoDownApp : public CWinApp
{
public:
	CJCVideoDownApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CJCVideoDownApp theApp;