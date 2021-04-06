#pragma once
#include "ColorStatic.h"
#include "afxwin.h"
#include "ColorSettingListCtrl.h"
#include "BaseDialog.h"

// CMainWndColorDlg �Ի���

class CMainWndColorDlg : public CBaseDialog
{
	DECLARE_DYNAMIC(CMainWndColorDlg)

public:
	CMainWndColorDlg(const std::map<DisplayItem, COLORREF>& colors, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMainWndColorDlg();

    const std::map<DisplayItem, COLORREF>& GetColors() const { return m_colors; }

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAIN_COLOR_DIALOG };
#endif
protected:
    std::map<DisplayItem, COLORREF> m_colors;
    CColorSettingListCtrl m_list_ctrl;

    virtual CString GetDialogName() const override;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
    afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
};
