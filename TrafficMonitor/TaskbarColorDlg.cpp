// TaskbarColorDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TrafficMonitor.h"
#include "TaskbarColorDlg.h"
#include "afxdialogex.h"
#include "CMFCColorDialogEx.h"


// CTaskbarColorDlg �Ի���

IMPLEMENT_DYNAMIC(CTaskbarColorDlg, CDialog)

CTaskbarColorDlg::CTaskbarColorDlg(COLORREF colors[TASKBAR_COLOR_NUM], CWnd* pParent /*=NULL*/)
	: CDialog(IDD_TASKBAR_COLOR_DIALOG, pParent)
{
	for (int i{}; i < TASKBAR_COLOR_NUM; i++)
		m_colors[i] = colors[i];
}

CTaskbarColorDlg::~CTaskbarColorDlg()
{
}

void CTaskbarColorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_UP_LABLE_STATIC, m_statics[0]);
	DDX_Control(pDX, IDC_UP_VALUE_STATIC, m_statics[1]);
	DDX_Control(pDX, IDC_DWON_LABLE_STATIC, m_statics[2]);
	DDX_Control(pDX, IDC_DWON_VALUE_STATIC, m_statics[3]);
	DDX_Control(pDX, IDC_CPU_LABLE_STATIC, m_statics[4]);
	DDX_Control(pDX, IDC_CPU_VALUE_STATIC, m_statics[5]);
	DDX_Control(pDX, IDC_MEMORY_LABLE_STATIC, m_statics[6]);
	DDX_Control(pDX, IDC_MEMORY_VALUE_STATIC, m_statics[7]);

    DDX_Control(pDX, IDC_CPU_TEMP_LABLE_STATIC, m_statics[8]);
    DDX_Control(pDX, IDC_CPU_TEMP_VALUE_STATIC, m_statics[9]);
    DDX_Control(pDX, IDC_GPU_TEMP_LABLE_STATIC, m_statics[10]);
    DDX_Control(pDX, IDC_GPU_TEMP_VALUE_STATIC, m_statics[11]);
    DDX_Control(pDX, IDC_HDD_TEMP_LABLE_STATIC, m_statics[12]);
    DDX_Control(pDX, IDC_HDD_TEMP_VALUE_STATIC, m_statics[13]);
    DDX_Control(pDX, IDC_MAIN_BOARD_TEMP_LABLE_STATIC, m_statics[14]);
    DDX_Control(pDX, IDC_MAIN_BOARD_TEMP_VALUE_STATIC, m_statics[15]);
}


BEGIN_MESSAGE_MAP(CTaskbarColorDlg, CDialog)
	ON_MESSAGE(WM_STATIC_CLICKED, &CTaskbarColorDlg::OnStaticClicked)
END_MESSAGE_MAP()


// CTaskbarColorDlg ��Ϣ�������


BOOL CTaskbarColorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	for (int i{}; i < TASKBAR_COLOR_NUM; i++)
	{
		m_statics[i].SetFillColor(m_colors[i]);
		m_statics[i].SetLinkCursor();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


afx_msg LRESULT CTaskbarColorDlg::OnStaticClicked(WPARAM wParam, LPARAM lParam)
{
	int item_id = ::GetDlgCtrlID(((CWnd*)wParam)->GetSafeHwnd());
	int index{};
	switch (item_id)
	{
	case IDC_UP_LABLE_STATIC:
		index = 0;
		break;
	case IDC_UP_VALUE_STATIC:
		index = 1;
		break;
	case IDC_DWON_LABLE_STATIC:
		index = 2;
		break;
	case IDC_DWON_VALUE_STATIC:
		index = 3;
		break;
	case IDC_CPU_LABLE_STATIC:
		index = 4;
		break;
	case IDC_CPU_VALUE_STATIC:
		index = 5;
		break;
	case IDC_MEMORY_LABLE_STATIC:
		index = 6;
		break;
	case IDC_MEMORY_VALUE_STATIC:
		index = 7;
		break;
	case IDC_CPU_TEMP_LABLE_STATIC:
		index = 8;
		break;
	case IDC_CPU_TEMP_VALUE_STATIC:
		index = 9;
		break;
	case IDC_GPU_TEMP_LABLE_STATIC:
		index = 10;
		break;
	case IDC_GPU_TEMP_VALUE_STATIC:
		index = 11;
		break;
	case IDC_HDD_TEMP_LABLE_STATIC:
		index = 12;
		break;
	case IDC_HDD_TEMP_VALUE_STATIC:
		index = 13;
		break;
	case IDC_MAIN_BOARD_TEMP_LABLE_STATIC:
		index = 14;
		break;
	case IDC_MAIN_BOARD_TEMP_VALUE_STATIC:
		index = 15;
		break;
	default:
		return 0;
	}

	CMFCColorDialogEx colorDlg(m_colors[index], 0, this);
	if (colorDlg.DoModal() == IDOK)
	{
		m_colors[index] = colorDlg.GetColor();
		m_statics[index].SetFillColor(m_colors[index]);
	}
	return 0;
}
