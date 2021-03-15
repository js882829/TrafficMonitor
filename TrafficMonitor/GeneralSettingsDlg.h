﻿#pragma once
#include "TabDlg.h"
#include "SpinEdit.h"
#include "ComboBox2.h"

// CGeneralSettingsDlg dialog

class CGeneralSettingsDlg : public CTabDlg
{
	DECLARE_DYNAMIC(CGeneralSettingsDlg)

public:
	CGeneralSettingsDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CGeneralSettingsDlg();

	//选项设置数据
	GeneralSettingData m_data;

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GENERAL_SETTINGS_DIALOG };
#endif

public:
	bool IsAutoRunModified() const { return m_auto_run_modified; }
	bool IsShowAllInterfaceModified() const { return m_show_all_interface_modified; }
    bool IsMonitorTimeSpanModified() const;

protected:
	bool m_auto_run_modified{ false };		//如果更改了开机自动运行的设置，则会置为true
	bool m_show_all_interface_modified{ false };
    int m_monitor_time_span_ori{};

	//控件变量
	CSpinEdit m_traffic_tip_edit;
	CComboBox2 m_traffic_tip_combo;
	CSpinEdit m_memory_tip_edit;
	CComboBox2 m_language_combo;
	CToolTipCtrl m_toolTip;
    CSpinEdit m_monitor_span_edit;
    CSpinEdit m_cpu_temp_tip_edit;
    CSpinEdit m_gpu_temp_tip_edit;
    CSpinEdit m_hdd_temp_tip_edit;
    CSpinEdit m_mbd_temp_tip_edit;


	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	//设置控件的启用和禁用
    void SetControlEnable();

    virtual void SetControlMouseWheelEnable(bool enable) override;

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCheckNowButton();
	afx_msg void OnBnClickedCheckUpdateCheck();
	afx_msg void OnBnClickedAutoRunCheck();
	afx_msg void OnBnClickedAllowSkinFontCheck();
	afx_msg void OnBnClickedAllowSkinDispStrCheck();
	virtual void OnOK();
	afx_msg void OnBnClickedTodayTrafficTipCheck();
	afx_msg void OnBnClickedMemoryUsageTipCheck();
	afx_msg void OnBnClickedOpenConfigPathButton();
	afx_msg void OnBnClickedShowAllConnectionCheck();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedUseCpuTimeRadio();
	afx_msg void OnBnClickedUsePdhRadio();
    afx_msg void OnDeltaposSpin(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnEnKillfocusMonitorSpanEdit();
    afx_msg void OnBnClickedCpuTempTipCheck();
    afx_msg void OnBnClickedGpuTempTipCheck();
    afx_msg void OnBnClickedHddTempTipCheck();
    afx_msg void OnBnClickedMbdTempTipCheck();
};
