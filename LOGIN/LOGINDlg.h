
// LOGINDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CLOGINDlg �Ի���
class CLOGINDlg : public CDialogEx
{
// ����
public:
	CLOGINDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CButton m_Button;
	afx_msg void OnBnClickedButton2();
	CEdit m_username;
	CEdit m_password;

};
