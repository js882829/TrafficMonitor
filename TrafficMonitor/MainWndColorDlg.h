#pragma once
#include "ColorStatic.h"
#include "afxwin.h"
#include "ColorSettingListCtrl.h"

// CMainWndColorDlg �Ի���

class CMainWndColorDlg : public CDialog
{
	DECLARE_DYNAMIC(CMainWndColorDlg)

public:
	CMainWndColorDlg(COLORREF colors[MAIN_WND_COLOR_NUM], CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMainWndColorDlg();

	const COLORREF* GetColors() const { return m_colors; }

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAIN_COLOR_DIALOG };
#endif
protected:
	COLORREF m_colors[MAIN_WND_COLOR_NUM];
    CColorSettingListCtrl m_list_ctrl;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
    afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
};
