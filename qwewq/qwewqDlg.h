
// qwewqDlg.h : 头文件
//

#pragma once
#include "mscomm1.h"
#include "afxwin.h"


// CqwewqDlg 对话框
class CqwewqDlg : public CDialogEx
{
// 构造
public:
	CqwewqDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_QWEWQ_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CMscomm1 m_mscomm;
	DECLARE_EVENTSINK_MAP()
	void OnCommMscomm1();
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonClose();
	CString m_EditReceive;
	afx_msg void OnCbnSelchangeCombo1();
	CComboBox m_combol1;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnCbnSelchangeCombo2();
	CComboBox m_combol2;
	CComboBox m_combol3;
	CComboBox m_combol4;
	CComboBox m_combol5;
	CEdit m_EditSend;
	afx_msg void OnBnClickedButton1();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButton2();
	int String2Hex(CString str, CByteArray &senddata);
	char ConvertHexChar(char ch);
	//void OnBnClickedCheckAutosend()
	CEdit m_cEditReceive;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	POINT Old;
	void resize();
};
