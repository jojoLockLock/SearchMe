
// SeachMEDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SearchME.h"
#include "SearchMEDlg.h"
#include "GetInternetSearch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CSeachMEDlg *pSeachMEDlg;
// CSeachMEDlg 对话框


CSeachMEDlg::CSeachMEDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSeachMEDlg::IDD, pParent)
	, m_strSeachItem(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	nList = 0;
}

void CSeachMEDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listctrl);
	DDX_Text(pDX, IDC_EDIT4, m_strSeachItem);
	DDX_Control(pDX, IDC_BUTTON1, m_btnSearch);
}

BEGIN_MESSAGE_MAP(CSeachMEDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CSeachMEDlg::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDC_BUTTON1, &CSeachMEDlg::OnBnClickedButton1)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CSeachMEDlg::OnNMClickList1)       //选中
	ON_WM_CONTEXTMENU()
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CSeachMEDlg::OnNMRClickList1)		//右键单击
	ON_COMMAND(ID_32774, &CSeachMEDlg::OnClickCOPY)
	ON_MESSAGE(MSG_INSERTlIST, &CSeachMEDlg::OnMsgInsertlist)
	ON_MESSAGE(MSG_SEARCH_SUCESS, &CSeachMEDlg::OnMsgSearchSucess)
END_MESSAGE_MAP()


// CSeachMEDlg 消息处理程序

BOOL CSeachMEDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	CRect rect;
	//m_listctrl.Create(LVS_LIST,NULL,)
	m_listctrl.GetClientRect(&rect);   
	
	// 为列表视图控件添加全行选中和栅格风格   
	m_listctrl.SetExtendedStyle(m_listctrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);  
	m_listctrl.InsertColumn(0, _T("名称"), LVCFMT_CENTER, rect.Width()/1.5, 0);   
	m_listctrl.InsertColumn(1, _T("文件大小"), LVCFMT_CENTER, rect.Width()/7, 1);   
	m_listctrl.InsertColumn(2, _T("下载热度"), LVCFMT_CENTER, rect.Width()/5, 2);   
	m_listctrl.InsertColumn(3, _T("Link"), LVCFMT_CENTER, 0, 3);
	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSeachMEDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSeachMEDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSeachMEDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}


void CSeachMEDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}




void CSeachMEDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CGetInternetSearch mget;
	
	UpdateData(TRUE);
	if (m_strSeachItem.GetLength() == 0)
	{
		MessageBox(_T("重新输入"));
		return;
	}
	//MessageBox(m_strSeachItem);
	//禁止点击 清空list
	nList = 0;
	m_btnSearch.EnableWindow(FALSE);
	m_listctrl.DeleteAllItems();
	mget.NextOrMorePage(m_strSeachItem); //new result
	Sleep(5);
	UpdateData(FALSE);
}

void CSeachMEDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	//CString strLandLink;
	//CGetInternetSearch mget;
	NM_LISTVIEW *pmlist = (NM_LISTVIEW*) pNMHDR;
	if ( -1 != pmlist->iItem)
	{
		strClickList = m_listctrl.GetItemText(pmlist->iItem, 3);
		//strLandLink.Format(_T("%d"),pmlist->iItem);
	//	MessageBox(strLandLink);
		//strLandLink =
	//	strClickList =  v_list[pmlist->iItem].SearchLink;
		//SetDlgItemText(IDC_EDIT3,strLandLink);
	}
}

void CSeachMEDlg::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	// TODO: 在此处添加消息处理程序代码

}

void CSeachMEDlg::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CMenu   oMenu;  
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if(pNMListView->iItem != -1)
	{
		// 右击在一个item上
		if   (oMenu.LoadMenu(IDR_MENU1))                  
		{  
			CMenu*   pPopup   =   oMenu.GetSubMenu(0);  
			ASSERT(pPopup   !=   NULL);  
			CPoint   oPoint;  
			GetCursorPos(   &oPoint   );  
			SetForegroundWindow();  
			pPopup->TrackPopupMenu(  
				TPM_LEFTALIGN   |   TPM_RIGHTBUTTON,  
				oPoint.x,   oPoint.y,   this);
			NM_LISTVIEW *pmlist = (NM_LISTVIEW*)pNMHDR;
			if (-1 != pmlist->iItem)
			{
				strClickList = m_listctrl.GetItemText(pmlist->iItem, 3);
			}
		}   
	}
	*pResult = 0;
}

void CSeachMEDlg::OnClickCOPY()
{
	// TODO: 在此添加命令处理程序代码
    //MessageBox(strClickList);
	if(OpenClipboard())
	{
		if (strClickList.GetLength() == 0)
		{
			AfxMessageBox(_T("获取链接失败"));
		}
		HGLOBAL clipbuffer;
		char * buffer;
		EmptyClipboard();
		clipbuffer = GlobalAlloc(GMEM_DDESHARE, strClickList.GetLength()+1);
		buffer = (char*)GlobalLock(clipbuffer);

		strcpy(buffer, CW2A(strClickList));	//copy
		GlobalUnlock(clipbuffer);
		SetClipboardData(CF_TEXT,clipbuffer);
		CloseClipboard();
	}
}


afx_msg LRESULT CSeachMEDlg::OnMsgInsertlist(WPARAM wParam, LPARAM lParam)
{
	if (lParam == NULL)
	{
		return -1;
	}
	SearchListInfo* ptmp = NULL;
	ptmp = (SearchListInfo*)lParam;

	//m_listctrl.DeleteAllItems();

	m_listctrl.InsertItem(nList, ptmp->SearchListName);
	m_listctrl.SetItemText(nList, 1, ptmp->SearchSize);
	m_listctrl.SetItemText(nList, 2, ptmp->SearchHotPoint);
	m_listctrl.SetItemText(nList, 3, ptmp->SearchLink);
	nList++;
	return 0;
}


BOOL CSeachMEDlg::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// TODO:  在此添加专用代码和/或调用基类
	switch (((NMHDR*)lParam)->code)
	{
	case HDN_BEGINTRACKW:
	case HDN_BEGINTRACKA:
		*pResult = TRUE;                // disable tracking
		return TRUE;                    // Processed message
	}

	return CDialog::OnNotify(wParam, lParam, pResult);
}


afx_msg LRESULT CSeachMEDlg::OnMsgSearchSucess(WPARAM wParam, LPARAM lParam)
{
	 
	m_btnSearch.EnableWindow(TRUE);
	return 0;
}
