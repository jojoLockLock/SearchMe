
// SeachMEDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "Resource.h"
#include "afxwin.h"

// CSeachMEDlg �Ի���
class CSeachMEDlg : public CDialog
{
// ����
public:
	CSeachMEDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SEACHME_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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