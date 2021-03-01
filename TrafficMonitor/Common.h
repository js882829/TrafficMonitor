#pragma once
#include "CommonData.h"
#include "CVariant.h"

class CCommon
{
public:
	CCommon();
	~CCommon();
	//��const char*�ַ���ת���ɿ��ַ��ַ���
	static wstring StrToUnicode(const char* str, bool utf8 = false);

	static string UnicodeToStr(const wchar_t* wstr, bool utf8 = false);

    template<class T>
    static void StringNormalize(T& str)
    {
        if (str.empty()) return;

        int size = str.size();	//�ַ����ĳ���
        if (size < 0) return;
        int index1 = 0;		//�ַ����е�1�����ǿո������ַ���λ��
        int index2 = size - 1;	//�ַ��������һ�����ǿո������ַ���λ��
        while (index1 < size && str[index1] >= 0 && str[index1] <= 32)
            index1++;
        while (index2 >= 0 && str[index2] >= 0 && str[index2] <= 32)
            index2--;
        if (index1 > index2)	//���index1 > index2��˵���ַ���ȫ�ǿո������ַ�
            str.clear();
        else if (index1 == 0 && index2 == size - 1)	//���index1��index2��ֵ�ֱ�Ϊ0��size - 1��˵���ַ���ǰ��û�пո������ַ���ֱ�ӷ���
            return;
        else
            str = str.substr(index1, index2 - index1 + 1);
    }

    //��һ���ַ����ָ�����ɸ��ַ���ģ������ֻ��Ϊstring��wstring��
    //str: ԭʼ�ַ���
    //div_ch: ���ڷָ���ַ�
    //result: ���շָ��Ľ��
    template<class T>
    static void StringSplit(const T& str, wchar_t div_ch, vector<T>& results, bool skip_empty = true, bool trim = true)
    {
        results.clear();
        size_t split_index = -1;
        size_t last_split_index = -1;
        while (true)
        {
            split_index = str.find(div_ch, split_index + 1);
            T split_str = str.substr(last_split_index + 1, split_index - last_split_index - 1);
            if (trim)
                StringNormalize(split_str);
            if (!split_str.empty() || !skip_empty)
                results.push_back(split_str);
            if (split_index == wstring::npos)
                break;
            last_split_index = split_index;
        }
    }
    
    template<class T>
    static void StringSplit(const T& str, const T& div_str, vector<T>& results, bool skip_empty = true, bool trim = true)
    {
        results.clear();
        size_t split_index = 0 - div_str.size();
        size_t last_split_index = 0 - div_str.size();
        while (true)
        {
            split_index = str.find(div_str, split_index + div_str.size());
            T split_str = str.substr(last_split_index + div_str.size(), split_index - last_split_index - div_str.size());
            if (trim)
                StringNormalize(split_str);
            if (!split_str.empty() || !skip_empty)
                results.push_back(split_str);
            if (split_index == wstring::npos)
                break;
            last_split_index = split_index;
        }
    }


    template<class T>
    static bool StringTransform(T & str, bool upper)
    {
        if (str.empty()) return false;
        if (upper)
        {
            for (auto& ch : str)
            {
                {
                    if (ch >= 'a'&&ch <= 'z')
                        ch -= 32;
                }
            }
        }
        else
        {
            for (auto& ch : str)
            {
                if (ch >= 'A'&&ch <= 'Z')
                    ch += 32;
            }
        }
        return true;
    }

    //��ȡ�ļ�����
    static bool GetFileContent(const wchar_t* file_path, string& contents_buff, bool binary = true);

    //��ȡ�ļ�����
    //file_path: �ļ���·��
    //length: �ļ��ĳ���
    //binary: �Ƿ��Խ��Ʒ�ʽ��ȡ
    //����ֵ: ��ȡ�ɹ����ض�ȡ�����ļ����ݵ�const char���͵�ָ�룬��ʹ����Ϻ����ָ����Ҫ����ʹ��delete�ͷš���ȡʧ�ܷ���nullptr
    static const char* GetFileContent(const wchar_t* file_path, size_t& length, bool binary = true);

	/*�������ݵĴ�Сת������KB��MB��GBΪ��λ���ַ���
	size�����ݵ��ֽ���
	����ֵ��ת������ַ���
	*/
	static CString DataSizeToString(unsigned int size, const PublicSettingData& cfg);
	static CString DataSizeToString(unsigned long long size);

	//static CString KBytesToString(unsigned int kb_size);
	static CString KBytesToString(unsigned __int64 kb_size);

	//��������FILETIME�ṹ��ʱ���
	static __int64 CompareFileTime2(FILETIME time1, FILETIME time2);

	//��һ����־��Ϣstr_textд�뵽file_path�ļ���
	static void WriteLog(const char* str_text, LPCTSTR file_path);
	static void WriteLog(const wchar_t* str_text, LPCTSTR file_path);

	/*
	�������ܣ���ָ���ļ���ָ����Ŀ¼�´������ݷ�ʽ
	����������
	lpszLnkFileDir  ָ��Ŀ¼������ΪNULL��
	lpszFileName    ָ���ļ���ΪNULL��ʾ��ǰ���̵�EXE�ļ���
	lpszLnkFileName ��ݷ�ʽ���ƣ�ΪNULL��ʾEXE�ļ�����
	wHotkey         Ϊ0��ʾ�����ÿ�ݼ�
	pszDescription  ��ע
	iShowCmd        ���з�ʽ��Ĭ��Ϊ���洰��
	*/
	static BOOL CreateFileShortcut(LPCTSTR lpszLnkFileDir, LPCTSTR lpszFileName = NULL, LPCTSTR lpszLnkFileName = NULL, LPCTSTR lpszWorkDir = NULL, WORD wHotkey = 0, LPCTSTR lpszDescription = NULL, int iShowCmd = SW_SHOWNORMAL);

	//��ȡ��ʼ�˵������г����еġ�������Ŀ¼��·��
	static wstring GetStartUpPath();

	//��ȡpath·���µ��ļ����ļ��У������ļ����ļ������Ʊ�����files�����С�
	static void GetFiles(const wchar_t* path, vector<wstring>& files);

	//�ж�һ���ļ��Ƿ����
	static bool FileExist(LPCTSTR file_name);

	static bool MoveAFile(LPCTSTR exist_file, LPCTSTR new_file);

	//��������SYSTEMTIME�ṹʱ��Ĳa-b��ֻ����ʱ���֡��룩
	static SYSTEMTIME CompareSystemTime(SYSTEMTIME a, SYSTEMTIME b);

	//��ȡ��ǰ�����Ŀ¼
	static wstring GetModuleDir();

	//��ȡsystem32�ļ��е�·��
	static wstring GetSystemDir();

	//��ȡ��ʱ�ļ��е�·��
	static wstring GetTemplateDir();

	//��ȡAppdata/Local/TrafficMonitor��Ŀ¼����������ڣ�����Զ�����
	static wstring GetAppDataConfigDir();

	//��ָ��λ�û����ı�
	static void DrawWindowText(CDC* pDC, CRect rect, LPCTSTR lpszString, COLORREF color, COLORREF back_color);

	////���û�ͼ�ļ�������
	//static void SetDrawArea(CDC* pDC, CRect rect);

	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	* �������ƣ�IsForegroundFullscreen
	* ����˵�����жϵ�ǰ�������û�������ǰ̨�����Ƿ���ȫ���ġ�
	* ����˵������
	* ����˵����true���ǡ�
	false����
	* �̰߳�ȫ����
	* ����������IsForegroundFullscreen ()����ʾ�жϵ�ǰ�������û�������ǰ̨�����Ƿ���ȫ���ġ�
	* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
	static bool IsForegroundFullscreen();

	//��һ���ַ������浽������
	static bool CopyStringToClipboard(const wstring& str);

    static wstring GetJsonValueSimple(const wstring& json_str, const wstring& name);

	//��ȡURL������
	static bool GetURL(const wstring& url, wstring& result, bool utf8 = false, const wstring& user_agent = wstring());

	//��ȡ����IP��ַ��IP������
	static void GetInternetIp(wstring& ip_address, wstring& ip_location, bool global);

    static void GetInternetIp2(wstring& ip_address, wstring& ip_location, bool ipv6);

	static void SetRect(CRect& rect, int x, int y, int width, int height);

	//����Դ�ļ������ַ��������У�front_str��back_strΪ�����ַ���ʱ��Ҫ��ǰ��������ӵ��ַ���
	static CString LoadText(UINT id, LPCTSTR back_str = nullptr);
	static CString LoadText(LPCTSTR front_str, UINT id, LPCTSTR back_str = nullptr);

	//��ȫ�ĸ�ʽ���ַ�������format_str������<%���%>���ַ����滻�ɳ�ʼ���б�paras�е�Ԫ�أ�Ԫ��֧��int/double/LPCTSTR/CString��ʽ����Ŵ�1��ʼ
	static CString StringFormat(LPCTSTR format_str, const std::initializer_list<CVariant>& paras);

	//����Դ�ļ��������ַ�����������Դ�ַ���������<%���%>���ַ����滻�ɿɱ�����б��еĲ���
	static CString LoadTextFormat(UINT id, const std::initializer_list<CVariant>& paras);

	//��int����ת�����ַ���
	//n��Ҫת������ֵ
	//thousand_separation���Ƿ�Ҫÿ��3λ��ʹ�ö��ŷָ�
	//is_unsigned����ֵ�Ƿ����޷��ŵ�
	static CString IntToString(int n, bool thousand_separation = false, bool is_unsigned = false);

	//ɾ���������ƺ����Bold��Light���ַ�������������Щ�ַ������������ϸ
	static void NormalizeFont(LOGFONT& font);

	//��ȫ���ַ������ƺ���
	static void WStringCopy(wchar_t* str_dest, int dest_size, const wchar_t* str_source, int source_size = INT_MAX);

	/// <summary>
	/// �ַ������ƶ��㷨-�༭���뷨
	/// </summary>
	/// <returns>���ص�ֵΪ0~1��Խ�����ƶ�Խ��</returns>
	static double StringSimilarDegree_LD(const string& srcString, const string& matchString);

	//�����߳�����
	static void SetThreadLanguage(Language language);

	//������ɫģʽ
	static void SetColorMode(ColorMode mode);

	//�������Է��֣��ƺ���͸��ɫ��R��Bֵ���ʱ��������һ�����������ʱ�޷������Ҽ��˵������ǵ���ϵͳ�������Ҽ��˵�������
	//Ϊ�˽��������⣬��Ҫ����ɫֵ����ת��
	//�˺������������ж�һ����ɫ��R��Bֵ�Ƿ���ȣ����������ɫ��Bֵ��1�����B==255�����1��
	static void TransparentColorConvert(COLORREF& transparent_color);

	static void SetDialogFont(CWnd* pDlg, CFont* pFont);

    //����Դ�����Զ����ı���Դ��id����Դ��ID��code_type���ı��ı����ʽ��0:ANSI, 1:UTF8, 2:UTF16
    static CString GetTextResource(UINT id, int code_type);

    //����Դ����һ��ͼ��
    static HICON LoadIconResource(UINT id, int size);

    //��ȡһ���˵�������
    static int GetMenuItemPosition(CMenu* pMenu, UINT id);

    static bool IsColorSimilar(COLORREF color1, COLORREF color2);

    //�����������1�ĸ���
    static int CountOneBits(unsigned int value);

    //����һ�����ֵ�ĳ��bitλ
    static void SetNumberBit(unsigned int& num, int bit, bool value);

    //��ȡһ�����ֵ�ĳ��bitλ
    static bool GetNumberBit(unsigned int num, int bit);

};

