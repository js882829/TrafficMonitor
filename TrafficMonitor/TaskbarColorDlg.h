#pragma once
#include "ColorStatic.h"
#include "afxwin.h"
#include "ColorSettingListCtrl.h"
#include "BaseDialog.h"

// CTaskbarColorDlg �Ի���

class CTaskbarColorDlg : public CBaseDialog
{
	DECLARE_DYNAMIC(CTaskbarColorDlg)

public:
	CTaskbarColorDlg(const std::map<DisplayItem, TaskbarItemColor>& colors, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTaskbarColorDlg();

    const std::map<DisplayItem, TaskbarItemColor>& GetColors() const { return m_colors; }

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TASKBAR_COLOR_DIALOG };
#endif

protected:
    std::map<DisplayItem, TaskbarItemColor> m_colors;
    CColorSettingListCtrl m_list_ctrl;

    virtual CString GetDialogName() const override;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
    afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
};
