
// JCVideoDownDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include <vector>
#include "urlexplorer.h"
#include <MsHTML.h>
#include "afxcmn.h"
#include "JCThreadManager.h"
using namespace std;
// CJCVideoDownDlg 对话框
class CJCVideoDownDlg : public CDialogEx
{
// 构造
public:
	CJCVideoDownDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_JCVIDEODOWN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CString m_tSrcUrl;
	CListBox m_VideoListBox;
	CString m_tVideoUrl;
	CFont m_ListBoxFont;
	CString m_tDownPath;
	CString m_tFileName;
	CProgressCtrl m_DownLoadProgress;
	CUrlexplorer m_UrlExplorer;
	JCThreadManager m_DownLoadThreadManager;
private:
	void InitVideoListBox(CString strUrlCode);
	void AddVideoListItem(CString strUrlCode);
	vector<CString> GetVideoUrl(CString strUrlCode);
	void EnumFrame(IHTMLDocument2 *pHTMLDocument );
	void ExtractHtml(IHTMLDocument2 *pHTMLDocument);
	CString SelFilePath();
	bool Download();
	BOOL IsDownloadContinue(CString serverEtag);
	BOOL IsFileExist(const CString& csFile);
	static DWORD WINAPI ThreadDownloadProc(JCThreadManager* pThreadManager);
	LRESULT SetProgress(WPARAM wPARAM,LPARAM lPARAM);
	void SetProgressMessage(CString strProgress);
	CString GetDownloadSpeed(int speed);
	void SetFileName();
	BOOL DirectoryExist(CString Path);
	BOOL CreateDirectory(CString path);
	CString Base64Encode(CString src);
	CString FormatUrl(CString strUrl,CString strMainUrl);
public:
	afx_msg void OnBnClickedLoadvideobutton();
	afx_msg void OnBnClickedWatchbutton();
	afx_msg void OnLbnSelchangeVideolist();
	afx_msg void OnBnClickedOpenurlbutton();
	afx_msg void OnBnClickedFindvideobutton();
	afx_msg void OnBnClickedDowntobutton();
private:
	CStatic m_DownSpeedStatic;
public:
	afx_msg void OnBnClickedSetpathbutton();
	afx_msg void OnEnChangeVideourledit();
private:
	CEdit m_DownPathEdit;
public:
	afx_msg void OnClose();
	afx_msg void OnBnClickedOpenfolderbutton();
};
