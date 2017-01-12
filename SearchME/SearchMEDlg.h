
// SeachMEDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "Resource.h"
#include "afxwin.h"

// CSeachMEDlg 对话框
class CSeachMEDlg : public CDialog
{
// 构造
public:
	CSeachMEDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SEACHME_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint point);
	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickCOPY();
protected:
	afx_msg LRESULT OnMsgInsertlist(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsgSearchSucess(WPARAM wParam, LPARAM lParam);
public:
	CString strCLICK;
	CListCtrl m_listctrl;
	CString m_strSeachItem;
	CString strClickList;
	DWORD nList;
	CButton m_btnSearch;
	
};
extern CSeachMEDlg *pSeachMEDlg;