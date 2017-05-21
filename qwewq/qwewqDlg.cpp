﻿
// qwewqDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "qwewq.h"
#include "qwewqDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CqwewqDlg 对话框




CqwewqDlg::CqwewqDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CqwewqDlg::IDD, pParent)
	, m_EditReceive(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CqwewqDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSCOMM1, m_mscomm);
	DDX_Text(pDX, IDC_EDIT1, m_EditReceive);
	DDX_Control(pDX, IDC_COMBO1, m_combol1);
	DDX_Control(pDX, IDC_COMBO2, m_combol2);
	DDX_Control(pDX, IDC_COMBO3, m_combol3);
	DDX_Control(pDX, IDC_COMBO4, m_combol4);
	DDX_Control(pDX, IDC_COMBO5, m_combol5);
}

BEGIN_MESSAGE_MAP(CqwewqDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CqwewqDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CqwewqDlg::OnBnClickedButtonClose)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CqwewqDlg::OnCbnSelchangeCombo1)
	ON_EN_CHANGE(IDC_EDIT1, &CqwewqDlg::OnEnChangeEdit1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CqwewqDlg::OnCbnSelchangeCombo2)
END_MESSAGE_MAP()


// CqwewqDlg 消息处理程序

BOOL CqwewqDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	((CComboBox*)GetDlgItem(IDC_COMBO2))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COMBO3))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COMBO4))->SetCurSel(3);
	((CComboBox*)GetDlgItem(IDC_COMBO5))->SetCurSel(0);
	 CImage myImage;
	myImage.Load(_T("d:\\bs\\qwewq\\qwewq\\qwewq\\res\\nuc.bmp"));

	CRect rect;
	CWnd *pWnd = GetDlgItem(IDC_STATIC); // (这是在此资源创建的类的内部, 若是在外部, 可先通过获得CMainFrame的指针, 再通过pMianFrame->GetDlgItem(IDCk_MY_PIC)来获取)
	CDC *pDC = pWnd->GetDC();
	pWnd->GetClientRect(&rect);
	pDC->SetStretchBltMode(STRETCH_HALFTONE);
	myImage.Draw(pDC->m_hDC, rect);
	long lReg;
HKEY hKey;
DWORD MaxValueLength;
DWORD dwValueNumber;


lReg = RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("HARDWARE\\DEVICEMAP\\SERIALCOMM"),
0, KEY_QUERY_VALUE, &hKey);


if (lReg != ERROR_SUCCESS) //成功时返回ERROR_SUCCESS，
{
//MessageBox(TEXT("未自动找到串口!\nOpen Registry Error!\n"));
return FALSE;
}


lReg = RegQueryInfoKey(hKey, NULL, NULL, NULL, NULL, NULL, NULL,
&dwValueNumber, &MaxValueLength, NULL, NULL, NULL);


if (lReg != ERROR_SUCCESS) //没有成功
{
//MessageBox(TEXT("未自动找到串口!\nGetting Info Error!\n"));
return FALSE;
}


TCHAR *pValueName, *pCOMNumber;
DWORD cchValueName, dwValueSize = 10;


for (int i = 0; i < dwValueNumber; i++)
{
cchValueName = MaxValueLength + 1;
dwValueSize = 10;
pValueName = (TCHAR*)VirtualAlloc(NULL, cchValueName, MEM_COMMIT, PAGE_READWRITE);
lReg = RegEnumValue(hKey, i, pValueName,
&cchValueName, NULL, NULL, NULL, NULL);


if ((lReg != ERROR_SUCCESS) && (lReg != ERROR_NO_MORE_ITEMS))
{
//MessageBox(TEXT("未自动找到串口!\nEnum Registry Error or No More Items!\n"));
return FALSE;
}


pCOMNumber = (TCHAR*)VirtualAlloc(NULL, 6, MEM_COMMIT, PAGE_READWRITE);
lReg = RegQueryValueEx(hKey, pValueName, NULL,
NULL, (LPBYTE)pCOMNumber, &dwValueSize);


if (lReg != ERROR_SUCCESS)
{
//MessageBox(TEXT("未自动找到串口!\nCan not get the name of the port"));
return FALSE;
}


CString str(pCOMNumber);
int len=str.GetLength();
str = str.Right(len - 3);
((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(_ttoi(str)-1);//把获取的值加入到ComBox控件中
VirtualFree(pValueName, 0, MEM_RELEASE);
VirtualFree(pCOMNumber, 0, MEM_RELEASE);
}


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CqwewqDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CqwewqDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CqwewqDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BEGIN_EVENTSINK_MAP(CqwewqDlg, CDialogEx)
	ON_EVENT(CqwewqDlg, IDC_MSCOMM1, 1, CqwewqDlg::OnCommMscomm1, VTS_NONE)
END_EVENTSINK_MAP()


void CqwewqDlg::OnCommMscomm1()
{
	// TODO: ÔÚ´Ë´¦Ìí¼ÓÏûÏ¢´¦Àí³ÌÐò´úÂë
    static unsigned int cnt = 0;  
    VARIANT variant_inp;  
    COleSafeArray safearryay_inp;  
    long len,k;  
    unsigned int data[1024]={0};  
    byte rxdata[1024];  
    CString stremp;  
    if(m_mscomm.get_CommEvent() == 2)  
    {  
        cnt++;  
        variant_inp = m_mscomm.get_Input();  
        safearryay_inp = variant_inp;  
        len = safearryay_inp.GetOneDimSize();  
        for(k=0;k<len;k++)  
        {  
            safearryay_inp.GetElement(&k,rxdata+k);  
        }  
        for (k=0;k<len;k++)  
        {  
            stremp.Format(_T("%c"),*(rxdata+k));  
            m_EditReceive += stremp;  
            CString temp=_T("\n");  
            m_EditReceive += temp;  
        }  
    }  
    UpdateData(FALSE);
}


void CqwewqDlg::OnBnClickedButtonOpen()
{
	int p,q;
	CString a;
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	if(m_mscomm.get_PortOpen())//如果串口是打开的，则行关闭串口 
	{
		m_mscomm.put_PortOpen(FALSE);
	}
	p=m_combol1.GetCurSel();//get port
	q=m_combol2.GetCurSel();
	m_mscomm.put_CommPort(p+1);//选择COM1  m_mscomm.put_InBufferSize(1024); //接收缓冲区  
	m_mscomm.put_OutBufferSize(1024);//发送缓冲区 
	m_mscomm.put_InputLen(0);//设置当前接收区数据长度为0,表示全部读取  
	m_mscomm.put_InputMode(1);//以二进制方式读写数据 
	m_mscomm.put_RThreshold(1);//接收缓冲区有1个及1个以上字符时，将引发接收数据的OnComm
	int selectedPos = m_combol2.GetCurSel();
	//m_combol2.GetLBText
	CString str;
	int m_Combo_BOTELV = GetDlgItemInt(IDC_COMBO2);
	str.Format(_T("%d,"), m_Combo_BOTELV);
	CString m_Combo_JIAOYANWEI, m_Combo_SHUJUWEI, m_Combo_TINGZHIWEI;
	GetDlgItemText(IDC_COMBO3, m_Combo_JIAOYANWEI);
	GetDlgItemText(IDC_COMBO4, m_Combo_SHUJUWEI);
	GetDlgItemText(IDC_COMBO5, m_Combo_TINGZHIWEI);
	str = str + m_Combo_JIAOYANWEI+_T(",")+ m_Combo_SHUJUWEI+_T(",")+ m_Combo_TINGZHIWEI;
	m_mscomm.put_Settings(str);//波特率，无校验，个数据位，个停止位
//	m_mscomm.put_Settings(_T("9600,n,8,1"));//波特率9600无检验位，8个数据位，1个停止位  

	if(!m_mscomm.get_PortOpen())//如果串口没有打开则打开  
	{
		m_mscomm.put_PortOpen(TRUE);//打开串口  
		AfxMessageBox(_T("串口打开成功"));
	}
	else
	{	
		m_mscomm.put_OutBufferCount(0);
		AfxMessageBox(_T("串口打开失败"));
	}
}

void CqwewqDlg::OnBnClickedButtonClose()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	 m_mscomm.put_PortOpen(FALSE);//关闭串口  
	 AfxMessageBox(_T("串口已关闭")); 
}


void CqwewqDlg::OnCbnSelchangeCombo1()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
int nIndex = m_combol1.GetCurSel();

CString strCBText;

 m_combol1.GetLBText( nIndex, strCBText);
}


void CqwewqDlg::OnEnChangeEdit1()
{
	// TODO:  Èç¹û¸Ã¿Ø¼þÊÇ RICHEDIT ¿Ø¼þ£¬Ëü½«²»
	// ·¢ËÍ´ËÍ¨Öª£¬³ý·ÇÖØÐ´ CDialogEx::OnInitDialog()
	// º¯Êý²¢µ÷ÓÃ CRichEditCtrl().SetEventMask()£¬
	// Í¬Ê±½« ENM_CHANGE ±êÖ¾¡°»ò¡±ÔËËãµ½ÑÚÂëÖÐ¡£

	// TODO:  ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë

}


void CqwewqDlg::OnCbnSelchangeCombo2()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
}
