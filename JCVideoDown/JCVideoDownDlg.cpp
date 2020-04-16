
// JCVideoDownDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "JCVideoDown.h"
#include "JCVideoDownDlg.h"
#include "afxdialogex.h"
#include <afxinet.h>
#include "MD5Crypt.h"
#include "JCVideoContext.h"
#include "JCObjectFormat.h"
#include "JCVideoFormat.h"
#include "JCEmbedFormat.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CJCVideoDownDlg 对话框
#define STARTVIDEOFORMAT \
	vector<CString> CJCVideoDownDlg::GetVideoUrl(CString strUrlCode){\
	CJCVideoContext* pContext = NULL;\
	vector<CString> vecVideoUrl,vecAllVideoUrl;

#define ADDVIDEOFORMAT(Class)\
	pContext = new CJCVideoContext(new Class);\
	vecVideoUrl = pContext->GetVideoUrls(strUrlCode);\
	pContext->AddSrcVector2Dest(vecVideoUrl,vecAllVideoUrl);\
	delete pContext;

#define ENDVIDEOFORMAT \
	return vecAllVideoUrl;}


CJCVideoDownDlg::CJCVideoDownDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CJCVideoDownDlg::IDD, pParent)
	, m_tSrcUrl(_T(""))
	, m_tVideoUrl(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CJCVideoDownDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SRCURLEDIT, m_tSrcUrl);
	DDX_Control(pDX, IDC_VIDEOLIST, m_VideoListBox);
	DDX_Text(pDX, IDC_VIDEOURLEDIT, m_tVideoUrl);
	DDX_Text(pDX, IDC_DOWNPATHEDIT, m_tDownPath);
	DDX_Control(pDX, IDC_URLEXPLORER, m_UrlExplorer);
	DDX_Control(pDX, IDC_DOWNPROGRESS, m_DownLoadProgress);
	DDX_Control(pDX, IDC_DOWNSPEEDSTATIC, m_DownSpeedStatic);
	DDX_Control(pDX, IDC_DOWNPATHEDIT, m_DownPathEdit);
}

STARTVIDEOFORMAT
	ADDVIDEOFORMAT(CJCVideoFormat)
	ADDVIDEOFORMAT(CJCObjectFormat)
	ADDVIDEOFORMAT(CJCEmbedFormat)
ENDVIDEOFORMAT


BEGIN_MESSAGE_MAP(CJCVideoDownDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_LOADVIDEOBUTTON, &CJCVideoDownDlg::OnBnClickedLoadvideobutton)
	ON_BN_CLICKED(IDC_WATCHBUTTON, &CJCVideoDownDlg::OnBnClickedWatchbutton)
	ON_LBN_SELCHANGE(IDC_VIDEOLIST, &CJCVideoDownDlg::OnLbnSelchangeVideolist)
	ON_BN_CLICKED(IDC_OPENURLBUTTON, &CJCVideoDownDlg::OnBnClickedOpenurlbutton)
	ON_BN_CLICKED(IDC_FINDVIDEOBUTTON, &CJCVideoDownDlg::OnBnClickedFindvideobutton)
	ON_BN_CLICKED(IDC_DOWNTOBUTTON, &CJCVideoDownDlg::OnBnClickedDowntobutton)
	ON_MESSAGE(WM_SETPROGRESS,CJCVideoDownDlg::SetProgress)
	ON_BN_CLICKED(IDC_SETPATHBUTTON, &CJCVideoDownDlg::OnBnClickedSetpathbutton)
	ON_EN_CHANGE(IDC_VIDEOURLEDIT, &CJCVideoDownDlg::OnEnChangeVideourledit)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_OPENFOLDERBUTTON, &CJCVideoDownDlg::OnBnClickedOpenfolderbutton)
END_MESSAGE_MAP()


// CJCVideoDownDlg 消息处理程序

BOOL CJCVideoDownDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_ListBoxFont.CreatePointFont(120,_T("微软雅黑"));
	m_VideoListBox.SetFont(&m_ListBoxFont);
	m_UrlExplorer.put_Silent(TRUE);
	m_DownLoadThreadManager.InitManager(ThreadDownloadProc,this,false);
	CString strText;
	m_DownPathEdit.GetWindowText(strText);
	if (strText.IsEmpty())
	{
		m_DownPathEdit.SetWindowText(_T("D://JCVideoDown"));
	}
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CJCVideoDownDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CJCVideoDownDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CJCVideoDownDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#define  NORMAL_CONNECT             INTERNET_FLAG_KEEP_CONNECTION
#define  SECURE_CONNECT             NORMAL_CONNECT | INTERNET_FLAG_SECURE
#define  NORMAL_REQUEST             INTERNET_FLAG_RELOAD | INTERNET_FLAG_DONT_CACHE
#define  SECURE_REQUEST             NORMAL_REQUEST | INTERNET_FLAG_SECURE | \
	INTERNET_FLAG_IGNORE_CERT_CN_INVALID| \
	INTERNET_FLAG_IGNORE_CERT_DATE_INVALID 

void CJCVideoDownDlg::OnBnClickedLoadvideobutton()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if (m_tSrcUrl.IsEmpty())
	{
		MessageBox(_T("请输入需要加载的网址"),_T("提示"));
	}
	else
	{
		try
		{
			DWORD dwFlags;
			DWORD dwServiceType = 0;
			CInternetSession session;
			session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 5000); // 5000毫秒的连接超时
			session.SetOption(INTERNET_OPTION_SEND_TIMEOUT, 5000); // 5000毫秒的发送超时
			session.SetOption(INTERNET_OPTION_RECEIVE_TIMEOUT, 5000); // 5000毫秒的接收超时
			session.SetOption(INTERNET_OPTION_DATA_SEND_TIMEOUT, 5000); // 5000毫秒的发送超时
			session.SetOption(INTERNET_OPTION_DATA_RECEIVE_TIMEOUT, 5000); // 5000毫秒的接收超时
			session.SetOption(INTERNET_OPTION_RESET_URLCACHE_SESSION, 1);     
			session.SetOption(INTERNET_OPTION_REFRESH, 1);          // 刷新
			CString strServer, strObject;
			INTERNET_PORT wPort;
			AfxParseURL(m_tSrcUrl, dwServiceType, strServer, strObject, wPort);
			CHttpConnection *conn=session.GetHttpConnection(strServer,dwServiceType == AFX_INET_SERVICE_HTTP ? NORMAL_CONNECT : SECURE_CONNECT,wPort);
			CHttpFile *pHttpFile=conn->OpenRequest(CHttpConnection::HTTP_VERB_GET,strObject, 0, 1, 0, 0, (dwServiceType == AFX_INET_SERVICE_HTTP ? NORMAL_REQUEST : SECURE_REQUEST));
			if (AFX_INET_SERVICE_HTTPS == dwServiceType)
			{
				pHttpFile->QueryOption(INTERNET_OPTION_SECURITY_FLAGS, dwFlags);
				dwFlags |= SECURITY_FLAG_IGNORE_UNKNOWN_CA;
				pHttpFile->SetOption(INTERNET_OPTION_SECURITY_FLAGS, dwFlags);
			}
			pHttpFile->AddRequestHeaders(_T("Accept: *,*/*"));
			pHttpFile->AddRequestHeaders(L"Accept-Charset:UTF8");
			pHttpFile->AddRequestHeaders(_T("Content-Type: application/json"));

			if (pHttpFile->SendRequest()==TRUE)
			{
				DWORD dwFileSize = 0;   //文件传递长度
				BOOL bResult = FALSE;
				TCHAR sRecived[10240];
				CString strText;
				while(pHttpFile->ReadString(sRecived,10240))
				{
					int nBufferSize = MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)sRecived, -1, NULL, 0);
					wchar_t *pBuffer = new wchar_t[nBufferSize+1];
					MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)sRecived, -1 , pBuffer, nBufferSize*sizeof(wchar_t));               
					strText+=pBuffer;
					delete[] pBuffer;
				}
				if (strText!=_T(""))
				{
					InitVideoListBox(strText);
				}
			}
			pHttpFile->Close();
			conn->Close();
			session.Close();
			delete pHttpFile;
			delete conn;
		}
		catch (...)
		{
			MessageBox(_T("网址访问出现异常"),_T("提示"));
		}
	}
}

void CJCVideoDownDlg::InitVideoListBox(CString strUrlCode)
{
	m_VideoListBox.ResetContent();
	vector<CString> vecVideoUrl = GetVideoUrl(strUrlCode);
	for (int i=0;i<(int)vecVideoUrl.size();i++)
	{
		m_VideoListBox.AddString(vecVideoUrl[i]);
	}
}

void CJCVideoDownDlg::AddVideoListItem(CString strUrlCode)
{
	vector<CString> vecVideoUrl = GetVideoUrl(strUrlCode);
	for (int i=0;i<(int)vecVideoUrl.size();i++)
	{
		m_VideoListBox.AddString(vecVideoUrl[i]);
	}
}


void CJCVideoDownDlg::OnBnClickedWatchbutton()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if (m_tVideoUrl.IsEmpty())
	{
		MessageBox(_T("请输入视频地址或选中列表中地址"),_T("提示"));
	}
	else
	{
		CString strUrl = m_tVideoUrl;
		if (m_tVideoUrl.Find(_T("http:"))<0)
		{
			strUrl = _T("http://")+m_tVideoUrl;
		}
		ShellExecute(0,NULL,strUrl,NULL,NULL,SW_NORMAL);	
	}
}

CString CJCVideoDownDlg::FormatUrl(CString strUrl,CString strMainUrl)
{
	string suffix[] = {".com",".cn",".org",".edu",".gov",".mil",".cc",".tv",".uk","end"};
	bool isMainUrl = false;
	for (int i=0;i<100;i++)
	{
		if (suffix[i] == "end")
			break;
		if (strUrl.Find(CString(suffix[i].c_str())) > -1)
		{
			isMainUrl = true;
			break;
		}
	}

	while (strUrl.GetLength()>0&&strUrl[0]=='/')
	{
		strUrl.Delete(0,1);
	}

	if (!isMainUrl)
	{
		int nPos = strMainUrl.Find(_T("http"));
		if (nPos > -1)
		{
			nPos = strMainUrl.Find(_T("//"));
			if (nPos > -1)
			{
				strMainUrl = strMainUrl.Mid(nPos + 2);
			}
		}
		nPos = strMainUrl.Find(_T("/"));
		if (nPos>-1)
		{
			strMainUrl = strMainUrl.Left(nPos);
		}
		strUrl = strMainUrl + _T("/") + strUrl;
	}

	if (strUrl.Find(_T("http")) < 0)
	{
		strUrl = _T("http://") + strUrl;
	}
	return strUrl;
}

void CJCVideoDownDlg::OnLbnSelchangeVideolist()
{
	// TODO: 在此添加控件通知处理程序代码
	int nPos = m_VideoListBox.GetCurSel();
	if (nPos > -1)
	{
		CString strVideoUrl;
		m_VideoListBox.GetText(nPos,strVideoUrl);
		//得到主域名
		UpdateData();
		m_tVideoUrl = FormatUrl(strVideoUrl,m_tSrcUrl);
		UpdateData(FALSE);
		SetFileName();
	}
}


void CJCVideoDownDlg::OnBnClickedOpenurlbutton()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if (m_tSrcUrl.IsEmpty())
	{
		MessageBox(_T("请输入需要加载的网址"),_T("提示"));
	}
	else
	{
		m_UrlExplorer.Navigate(m_tSrcUrl,NULL,NULL,NULL,NULL);
	}
	
}

void CJCVideoDownDlg::EnumFrame( IHTMLDocument2 *pHTMLDocument ) 
{ 
	CComQIPtr<IOleContainer> spContainer( pHTMLDocument ); 
	if( spContainer ) 
	{ 
		CComPtr<IEnumUnknown> spEnumerator; // 注：参数OLECONTF_EMBEDDINGS // 表示列举容器内的所有嵌入对象
		HRESULT hr = spContainer->EnumObjects(OLECONTF_EMBEDDINGS, &spEnumerator); 
		if( spEnumerator ) 
		{ 
			CComPtr<IUnknown> spUnk; 
			while (spEnumerator->Next(1, &spUnk, NULL) == S_OK) 
			{ 
				CComQIPtr<IWebBrowser2, &IID_IWebBrowser2> spWB(spUnk); 
				spUnk=NULL; 
				if ( spWB ) 
				{ 
					CComPtr<IDispatch> spDocDisp; 
					hr = spWB->get_Document(&spDocDisp);  
					CComQIPtr<IHTMLDocument2> spHTML (spDocDisp) ; 
					ExtractHtml(spHTML);
					EnumFrame( spHTML ); 

				} 
			} 
		} 
	} 
}

void CJCVideoDownDlg::ExtractHtml(IHTMLDocument2 *pHTMLDocument)
{
	CComPtr<IHTMLElementCollection> spHTML;
	HRESULT hr = pHTMLDocument->get_all(&spHTML);
	long length = 0;
	spHTML->get_length(&length);
	if (hr == S_OK && spHTML != NULL) 
	{
		for (int i = 0; i < length ; i++)
		{
			VARIANT vIndex,vName;
			vName.vt=vIndex.vt=VT_I4;
			vName.lVal=vIndex.lVal=i;
			CComPtr<IDispatch> pDisp;
			hr=spHTML->item(vName,vIndex,&pDisp);
			if( hr==S_OK )
			{
				CComPtr<IHTMLElement> pElement;
				hr=pDisp->QueryInterface(IID_IHTMLElement,(void**)&pElement);
				if( hr==S_OK )
				{
					CComBSTR tagName;
					hr=pElement->get_tagName(&tagName);
					if(hr==S_OK)
					{
						CString str(tagName);
						if(str=="HTML")
						{
							CComBSTR pContent;
							//hr=pElement->get_outerText(&pContent);
							hr=pElement->get_outerHTML(&pContent);

							if(hr==S_OK)
							{
								AddVideoListItem(CString(pContent));
								/*CFile file;
								file.Open(_T("c://1.html"),CFile::modeWrite|CFile::modeCreate);
								file.Write(CString(pContent),CString(pContent).GetLength()*2);
								file.Close();*/

							}
						}//else if tagName isnot 'HTML'

					}//else if get_tagName failed

				}//else if don't get IHMTLElement interface

			}//if no items
		}
	}
}

void CJCVideoDownDlg::OnBnClickedFindvideobutton()
{
	// TODO: 在此添加控件通知处理程序代码
	m_VideoListBox.ResetContent();
	IHTMLDocument2 *pHTMLDocument= (IHTMLDocument2 *)m_UrlExplorer.get_Document();
	if (pHTMLDocument == NULL)
	{
		MessageBox(_T("请打开网页"),_T("提示"));
	}
	else
	{
		try
		{
			EnumFrame(pHTMLDocument);
			ExtractHtml(pHTMLDocument);
		}
		catch (...)
		{
			MessageBox(_T("发生未知错误"),_T("提示"));
		}
	}
}

CString CJCVideoDownDlg::SelFilePath()
{
	TCHAR           szFolderPath[MAX_PATH] = {0};  
	CString         strFolderPath = TEXT("");  

	BROWSEINFO      sInfo;  
	::ZeroMemory(&sInfo, sizeof(BROWSEINFO));  
	sInfo.pidlRoot   = 0;  
	sInfo.lpszTitle   = _T("请选择处理结果存储路径");  
	sInfo.ulFlags   = BIF_RETURNONLYFSDIRS|BIF_EDITBOX|BIF_DONTGOBELOWDOMAIN;  
	sInfo.lpfn     = NULL;  

	// 显示文件夹选择对话框  
	LPITEMIDLIST lpidlBrowse = ::SHBrowseForFolder(&sInfo);   
	if (lpidlBrowse != NULL)  
	{  
		// 取得文件夹名  
		if (::SHGetPathFromIDList(lpidlBrowse,szFolderPath))    
		{  
			strFolderPath = szFolderPath;  
		}  
	}  
	if(lpidlBrowse != NULL)  
	{  
		::CoTaskMemFree(lpidlBrowse);  
	}  

	return strFolderPath;  
}

void CJCVideoDownDlg::OnBnClickedDowntobutton()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if (m_tVideoUrl.IsEmpty())
	{
		MessageBox(_T("视频地址不能为空"),_T("提示"));
	}
	if (m_tDownPath.IsEmpty())
	{
		MessageBox(_T("下载路径不能为空"),_T("提示"));
	}
	if (m_tFileName.IsEmpty())
	{
		MessageBox(_T("文件名不能为空"),_T("提示"));
	}
	m_DownLoadThreadManager.Start();
}

BOOL CJCVideoDownDlg::IsFileExist(const CString& csFile)
{
	DWORD dwAttrib = GetFileAttributes(csFile);
	return INVALID_FILE_ATTRIBUTES != dwAttrib && 0 == (dwAttrib & FILE_ATTRIBUTE_DIRECTORY);
}

BOOL CJCVideoDownDlg::IsDownloadContinue(CString serverEtag)
{
	//是否继续
	bool isContinue = false;
	//临时文件
	CString tempFileName = m_tDownPath+_T("/")+m_tFileName + _T(".temp");
	//ETag信息文件
	CString tempFileInfoName = m_tDownPath+_T("/")+m_tFileName + _T(".temp.info");
	//下载到本地的临时文件和Etag信息文件都存在
	if (IsFileExist(tempFileName) && IsFileExist(tempFileInfoName))
	{
		//读取本地Etag信息
		CString strTag;
		CFile file;
		if(file.Open(tempFileInfoName,CFile::modeRead))
		{
			TCHAR buf[512]={0};
			file.Read(buf,512);
			strTag = buf;
		}
		file.Close();
		//服务器文件和本地 临时文件一致
		if (!strTag.IsEmpty() && strTag == serverEtag)
		{
			//可以续传
			isContinue = true;
		}
		else if (!serverEtag.IsEmpty())
		{
			DeleteFile(tempFileName);
			file.Open(tempFileInfoName,CFile::modeCreate|CFile::modeWrite);
			file.Write(serverEtag,serverEtag.GetLength());
			file.Close();
		}
	}
	else
	{
		//本地没有临时文件 则创建一个
		if (!serverEtag.IsEmpty())
		{
			CFile file;
			file.Open(tempFileInfoName,CFile::modeCreate|CFile::modeWrite);
			file.Write(serverEtag,serverEtag.GetLength());
			file.Close();
		}
	}
	return isContinue;
}

DWORD CJCVideoDownDlg::ThreadDownloadProc(JCThreadManager* pThreadManager)
{
	CJCVideoDownDlg* pJCVideoDownDlg = (CJCVideoDownDlg*)pThreadManager->GetParam();
	if(pJCVideoDownDlg->Download())
	{
		pJCVideoDownDlg->SetProgressMessage(_T("下载完成"));
	}
	return 0;
}

BOOL CJCVideoDownDlg::DirectoryExist(CString Path)
{
	WIN32_FIND_DATA fd;
	BOOL ret = FALSE;
	HANDLE hFind = FindFirstFile(Path, &fd);
	if ((hFind != INVALID_HANDLE_VALUE) && (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
	{
		//目录存在
		ret = TRUE;
	}
	FindClose(hFind);
	return ret;
}

BOOL CJCVideoDownDlg::CreateDirectory(CString path)
{
	SECURITY_ATTRIBUTES attrib;
	attrib.bInheritHandle = FALSE;
	attrib.lpSecurityDescriptor = NULL;
	attrib.nLength = sizeof(SECURITY_ATTRIBUTES);

	return ::CreateDirectory( path, &attrib);
}

bool CJCVideoDownDlg::Download()
{
	bool result = false;
	try
	{
		if (m_tVideoUrl.IsEmpty())
			return false;
		if (m_tDownPath.IsEmpty())
			return false;
		if (m_tFileName.IsEmpty())
			return false;
		if (!DirectoryExist(m_tDownPath))
			CreateDirectory(m_tDownPath);
		CInternetSession session;
		session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 5000); // 5000毫秒的连接超时
		session.SetOption(INTERNET_OPTION_SEND_TIMEOUT, 5000); // 5000毫秒的发送超时
		session.SetOption(INTERNET_OPTION_RECEIVE_TIMEOUT, 5000); // 5000毫秒的接收超时
		session.SetOption(INTERNET_OPTION_DATA_SEND_TIMEOUT, 5000); // 5000毫秒的发送超时
		session.SetOption(INTERNET_OPTION_DATA_RECEIVE_TIMEOUT, 5000); // 5000毫秒的接收超时
		session.SetOption(INTERNET_OPTION_RESET_URLCACHE_SESSION, 1);     
		session.SetOption(INTERNET_OPTION_REFRESH, 1);          // 刷新
		CString strServer, strObject,strParameter,strAddHeader;
		INTERNET_PORT wPort;
		DWORD dwType;
		AfxParseURL(m_tVideoUrl, dwType, strServer, strObject, wPort);
		CHttpConnection *conn=session.GetHttpConnection(strServer,wPort);
		CHttpFile *pHttpFile=conn->OpenRequest(CHttpConnection::HTTP_VERB_GET,strObject, 0, 1, 0, 0, INTERNET_FLAG_RELOAD);
		if (pHttpFile->SendRequest()==TRUE)
		{
			char szInfoBuffer[1000]={0};  //返回消息
			DWORD dwFileSize = 0;   //文件传递长度
			DWORD dwInfoBufferSize = sizeof(szInfoBuffer);
			BOOL bResult = FALSE;
			/*bResult = pHttpFile->QueryInfo(HTTP_QUERY_ETAG,
				(void*)szInfoBuffer,&dwInfoBufferSize,NULL);*/
			CString strText;
			//strText.Format(_T("%s"),szInfoBuffer);
			CMD5Crypt md5;
			md5.GetMd5String(strText,m_tVideoUrl);
			if (strText!=_T(""))
			{
				BOOL isDownloadContinue = IsDownloadContinue(strText);
				if (isDownloadContinue)
				{
					memset(szInfoBuffer,0,1000);
					bResult = pHttpFile->QueryInfo(HTTP_QUERY_ACCEPT_RANGES,
						(void*)szInfoBuffer,&dwInfoBufferSize,NULL);
					strText.Format(_T("%s"),szInfoBuffer);
					if (strText==_T("none"))
						isDownloadContinue = FALSE;
				}
				m_DownLoadProgress.SetRange(0,100);
				CFile file;
				if(file.Open(m_tDownPath+_T("/")+m_tFileName+_T(".temp"),CFile::modeWrite|CFile::modeCreate|CFile::modeNoTruncate))
				{
					file.SeekToEnd();
					ULONGLONG downLen = 0;
					if (isDownloadContinue)
					{
						downLen = file.GetLength();
						pHttpFile->Close();
						pHttpFile=conn->OpenRequest(CHttpConnection::HTTP_VERB_GET,strObject ,0, 1, 0, 0, INTERNET_FLAG_RELOAD); 
						//pHttpFile->AddRequestHeaders(strAddHeader);
						strAddHeader.Format(_T("Range:bytes=%ld-"),downLen);
						pHttpFile->AddRequestHeaders(strAddHeader);
						pHttpFile->SendRequest();
						memset(szInfoBuffer,0,1000);
						bResult = pHttpFile->QueryInfo(HTTP_QUERY_CONTENT_LENGTH,
							(void*)szInfoBuffer,&dwInfoBufferSize,NULL);
						strText=_T("");
						for (int i=0;i<dwInfoBufferSize;i++)
							strText += szInfoBuffer[i];
					}
					else
					{
						memset(szInfoBuffer,0,1000);
						bResult = pHttpFile->QueryInfo(HTTP_QUERY_CONTENT_LENGTH,
							(void*)szInfoBuffer,&dwInfoBufferSize,NULL);
						strText.Format(_T("%s"),szInfoBuffer);
					}

					dwFileSize = atol(CStringA(strText));
					dwFileSize = dwFileSize + downLen;
					CString strResult;
					char sRecived[10240];
					UINT len = 0;
					long t0=GetTickCount();
					while(!m_DownLoadThreadManager.IsClose())
					{
						len = pHttpFile->Read(sRecived,10240);
						downLen+=len;
						file.Write(sRecived,len);
						long t=GetTickCount();
						if (t-t0>100)
						{
							PostMessage(WM_SETPROGRESS,(WPARAM)downLen,(LPARAM)dwFileSize);
							t0 = t;
						}
						if (downLen >= dwFileSize)
							break;
					}
					file.Close();
					if (downLen == dwFileSize)
					{
						m_DownLoadProgress.SetPos(100);
						SetProgressMessage(GetDownloadSpeed(downLen)+_T("/")+GetDownloadSpeed(dwFileSize));
						CopyFile(m_tDownPath+_T("/")+m_tFileName+_T(".temp"),m_tDownPath+_T("/")+m_tFileName,TRUE);
						DeleteFile(m_tDownPath+_T("/")+m_tFileName+_T(".temp"));
						DeleteFile(m_tDownPath+_T("/")+m_tFileName+_T(".temp.info"));
						result = true;
					}
					else if (downLen>dwFileSize)
					{
						DeleteFile(m_tDownPath+_T("/")+m_tFileName+_T(".temp"));
						DeleteFile(m_tDownPath+_T("/")+m_tFileName+_T(".temp.info"));
						SetProgressMessage(_T("下载异常请重新下载"));
					}
				}
			}
			else
				SetProgressMessage(_T("未找到更新信息"));
		}
		else
		{
			SetProgressMessage(_T("网络链接失败请稍后尝试"));
		}
		pHttpFile->Close();
		conn->Close();
		session.Close();
		delete pHttpFile;
		delete conn;
	}
	catch (...)
	{
	}
	return result;
}

LRESULT CJCVideoDownDlg::SetProgress(WPARAM wPARAM,LPARAM lPARAM)
{
	int downLen = wPARAM;
	int dwFileSize = lPARAM;
	double pos = (double)downLen / (double)dwFileSize * 100;
	m_DownLoadProgress.SetPos(pos);
	SetProgressMessage(GetDownloadSpeed(downLen)+_T("/")+GetDownloadSpeed(dwFileSize));
	return 0;
}

void CJCVideoDownDlg::SetProgressMessage(CString strProgress)
{
	m_DownSpeedStatic.SetWindowText(strProgress);
}

CString CJCVideoDownDlg::GetDownloadSpeed(int speed)
{
	CString strText;
	if (speed/1024/1024>0)
	{
		strText.Format(_T("%dMB"),speed/1024/1024);
	}
	else if (speed/1024>0)
	{
		strText.Format(_T("%dKB"),speed/1024);
	}
	else
		strText.Format(_T("%dB"),speed);
	return strText;
}

void CJCVideoDownDlg::OnBnClickedSetpathbutton()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strPath = SelFilePath();
	if (!strPath.IsEmpty())
	{
		m_tDownPath = strPath;
	}
	else
		m_tDownPath = _T("");
	UpdateData(FALSE);
}

void CJCVideoDownDlg::SetFileName()
{
	UpdateData();
	int nPos = m_tVideoUrl.ReverseFind('/');
	if (nPos>-1)
	{
		m_tFileName = m_tVideoUrl.Mid(nPos+1);
		nPos = m_tFileName.Find(_T("?"));
		if (nPos>-1)
		{
			m_tFileName = m_tFileName.Left(nPos);
		}
	}
}

void CJCVideoDownDlg::OnEnChangeVideourledit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	SetFileName();
}


void CJCVideoDownDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_DownLoadThreadManager.End();
	m_DownLoadThreadManager.WaitForClose(5000);
	CDialogEx::OnClose();
}


void CJCVideoDownDlg::OnBnClickedOpenfolderbutton()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if (m_tDownPath.IsEmpty())
	{
		MessageBox(_T("请选择或输入下载目录"),_T("提示"));
	}
	else
	{
		ShellExecute(NULL, _T("open"), m_tDownPath, NULL, NULL, SW_SHOW);
	}
}
