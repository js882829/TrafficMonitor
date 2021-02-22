#pragma once
#include "Common.h"
#include "afxwin.h"
#include "DrawCommon.h"
#include "IniHelper.h"
#include "CommonData.h"

// CTaskBarDlg �Ի���
#define TASKBAR_WND_HEIGHT theApp.DPI(32)				//���������ڵĸ߶�
#define WM_TASKBAR_MENU_POPED_UP (WM_USER + 1004)		//���������������Ҽ��˵�����ʱ��������Ϣ
//#define TASKBAR_GRAPH_MAX_LEN 600						//��ʷ���ݴ洢��󳤶�
#define TASKBAR_GRAPH_STEP 5							//�����ӻ�һ����

class CTaskBarDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTaskBarDlg)

public:
	CTaskBarDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTaskBarDlg();

	CToolTipCtrl m_tool_tips;

	void ShowInfo(CDC* pDC); 	//����Ϣ���Ƶ��ؼ���
	void TryDrawStatusBar(CDrawCommon& drawer, const CRect& rect_bar, int usage_percent); //����CPU/�ڴ�״̬��

	void TryDrawGraph(CDrawCommon& drawer, const CRect &value_rect, DisplayItem item_type);		// ����CPU/�ڴ涯̬ͼ

	bool AdjustWindowPos();	//���ô������������е�λ��
	void ApplyWindowTransparentColor();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TASK_BAR_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	HWND m_hTaskbar;	//���������ھ��
	HWND m_hBar;		//���������ڶ��������ľ��
	HWND m_hMin;		//��С�����ڵľ��
	CRect m_rcBar;		//��ʼ״̬ʱ���������ڵľ�������
	CRect m_rcMin;		//��ʼ״̬ʱ��С�����ڵľ�������
	CRect m_rect;		//��ǰ���ڵľ�������
    int m_window_width{};
    int m_window_height{};

    //�������������ֵĿ��
    struct ItemWidth
    {
        int label_width{};      //��ǩ���ֿ��
        int value_width{};      //��ֵ���ֿ��

        int TotalWidth() const  //�ܿ��
        {
            return label_width + value_width;
        }
    };

    std::map<DisplayItem, ItemWidth> m_item_widths;   //����������ÿ�����ֵĿ��
    std::map<DisplayItem, int> m_item_display_width;    //����������ÿ������ʵ����ʾ�Ŀ��

	int m_min_bar_width;	//��С��������С��Ⱥ�Ŀ��
	int m_min_bar_height;	//��С��������С�߶Ⱥ�ĸ߶ȣ���������������Ļ�����Ҳ�ʱ��

    std::map<DisplayItem, CList<int, int>> m_map_history_data;  //�������������ʷ���ݵ����������水��ʱ��˳��Խ����ͷ������Խ��

	int m_left_space{};			//��С�����ںͶ������ڴ������ı߾�
	int m_top_space{};			//��С�����ںͶ������ڴ��ڶ����ı߾ࣨ��������������Ļ�����Ҳ�ʱ��

	bool m_connot_insert_to_task_bar{ false };	//��������޷�Ƕ������������Ϊtrue
	bool m_taskbar_on_top_or_bottom{ true };		//�������������Ļ������ײ�����Ϊture
	int m_error_code{};

	CFont m_font;			//����

	CDC* m_pDC{};		//���ڵ�DC���������㴰�ڵĿ��

	void CheckTaskbarOnTopOrBottom();		//����������Ƿ�����Ļ�Ķ�����ײ����������������m_taskbar_on_top_or_bottom��
	CString GetMouseTipsInfo();		//��ȡ�����ʾ

	void AddHisToList(DisplayItem item_type, int current_usage_percent);		//����ǰ��������ֵ��ӽ�����

    //���������������е�һ����ʾ��Ŀ
    //  drawer: ��ͼ��Ķ���
    //  type: ��Ŀ������
    //  rect: ���ƾ�������
    //  label_width: ��ǩ����Ŀ��
    void DrawDisplayItem(CDrawCommon& drawer, DisplayItem type, CRect rect, int label_width);

public:
	void SetTextFont();
	void ApplySettings();
    void CalculateWindowSize();		//���㴰��ÿ���ֵĴ�С�����������ֵĿ�ȡ����ڴ�С���浽m_window_width��m_window_height�У������ֿ�ȱ��浽m_item_widths��

	void SetToolTipsTopMost();			//���������ʾ�ö�
	void UpdateToolTips();

	bool GetCannotInsertToTaskBar() const { return m_connot_insert_to_task_bar; }
	int GetErrorCode() const { return m_error_code; }
    bool IsTasksbarOnTopOrBottom() { return m_taskbar_on_top_or_bottom; }

	static bool IsShowCpuMemory();
	static bool IsShowNetSpeed();
	static bool IsShowUp();
	static bool IsShowDown();
	static bool IsShowCpu();
	static bool IsShowMemory();
    static bool IsShowCpuTemperature();
    static bool IsShowGpuTemperature();
    static bool IsShowHddTemperature();
    static bool IsShowMainboardTemperature();

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//afx_msg void OnSetBackgroundColor();
	//afx_msg void OnSetTextColor();
	afx_msg void OnInitMenu(CMenu* pMenu);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//afx_msg void OnSetFont();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	afx_msg void OnPaint();
};
