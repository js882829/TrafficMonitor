#include "stdafx.h"
#include "ColorSettingListCtrl.h"

IMPLEMENT_DYNAMIC(CColorSettingListCtrl, CListCtrl)

CColorSettingListCtrl::CColorSettingListCtrl()
{
}


CColorSettingListCtrl::~CColorSettingListCtrl()
{
}

void CColorSettingListCtrl::SetItemColor(int row, int col, COLORREF color)
{
    m_colors[row][col] = color;
}


COLORREF CColorSettingListCtrl::GetItemColor(int row, int col)
{
    return m_colors[row][col];
}

BEGIN_MESSAGE_MAP(CColorSettingListCtrl, CListCtrl)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CColorSettingListCtrl::OnNMCustomdraw)
END_MESSAGE_MAP()


void CColorSettingListCtrl::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = CDRF_DODEFAULT;
	LPNMLVCUSTOMDRAW lplvdr = reinterpret_cast<LPNMLVCUSTOMDRAW>(pNMHDR);
	NMCUSTOMDRAW& nmcd = lplvdr->nmcd;
	switch (lplvdr->nmcd.dwDrawStage)	//�ж�״̬   
	{
	case CDDS_PREPAINT:
		*pResult = CDRF_NOTIFYITEMDRAW;
		break;
	case CDDS_ITEMPREPAINT:			//���Ϊ��ITEM֮ǰ��Ҫ������ɫ�ĸı�
		if (nmcd.dwItemSpec >= 0 && nmcd.dwItemSpec < GetItemCount())
		{
			//double range = m_item_rage_data[nmcd.dwItemSpec].data_value;
			//CDC* pDC = CDC::FromHandle(nmcd.hdc);		//��ȡ��ͼDC
			//CRect item_rect, draw_rect;
			//GetSubItemRect(nmcd.dwItemSpec,m_draw_item_range_row, LVIR_BOUNDS, item_rect);	//��ȡ��ͼ��Ԫ��ľ�������
			//CDrawCommon::SetDrawRect(pDC, item_rect);		//���û�ͼ����Ϊ��ǰ��
			//draw_rect = item_rect;
			//if (draw_rect.Height() > 2 * m_margin)
			//{
			//	draw_rect.top += m_margin;
			//	draw_rect.bottom -= m_margin;
			//}
			//int width;
			//if (m_use_log_scale)	//ʹ�ö���������y=ln(x+1)��
			//{
			//	range = std::log(range + 1);
			//	width = static_cast<int>(range*draw_rect.Width() / std::log(1000 + 1));
			//}
			//else		//ʹ�����Ա�����y=x��
			//{
			//	width = static_cast<int>(range*draw_rect.Width() / 1000);
			//}
			//draw_rect.right = draw_rect.left + width;
			//pDC->FillSolidRect(draw_rect, m_item_rage_data[nmcd.dwItemSpec].color);

			////��ǰ�л�����ɺ󽫻�ͼ��������Ϊ��ߵ����򣬷�ֹ��ǰ�е����򱻸���
			//CRect rect1{ item_rect };
			//rect1.left = 0;
			//rect1.right = item_rect.left;
			//CDrawCommon::SetDrawRect(pDC, rect1);

            CDC* pDC = CDC::FromHandle(nmcd.hdc);		//��ȡ��ͼDC
            CRect item_rect;
            auto& col_color_map = m_colors[nmcd.dwItemSpec];
            for (auto iter = col_color_map.begin(); iter != col_color_map.end(); ++iter)
            {
                GetSubItemRect(nmcd.dwItemSpec, iter->first, LVIR_BOUNDS, item_rect);	//��ȡ��ͼ��Ԫ��ľ�������
                CDrawCommon::SetDrawRect(pDC, item_rect);
                item_rect.DeflateRect(m_margin, m_margin);
                pDC->FillSolidRect(item_rect, iter->second);
            }
            //��ǰ�л�����ɺ󽫻�ͼ��������Ϊ��һ�е����򣬷�ֹ��ɫ�е����򱻸���
            CRect rect1{};
            GetSubItemRect(nmcd.dwItemSpec, 1, LVIR_BOUNDS, rect1);	//��ȡ��1�е�Ԫ��ľ�������
            rect1.right = rect1.left;
            rect1.left = 0;
            CDrawCommon::SetDrawRect(pDC, rect1);

		}
		*pResult = CDRF_DODEFAULT;
		break;
	}
}
