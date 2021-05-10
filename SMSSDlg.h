﻿
// SMSSDlg.h: 头文件
//

#pragma once


// CSMSSDlg 对话框
class CSMSSDlg : public CDialogEx
{
// 构造
public:
	CSMSSDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SMSS_DIALOG };
#endif

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
	CStatic m_SetFontZH;
	CStatic m_SetFontmm;
	afx_msg void OnBnClickedButtonRegister();
//	BOOL m_LoginISAdmin;
	CString m_LoginZH;
	CString m_LoginMM;
	afx_msg void OnBnClickedCheckLoginshow();
	afx_msg void OnBnClickedButtonLogin();
	BOOL m_ISAdmin;
	static CSMSSDlg* pUser;
};
