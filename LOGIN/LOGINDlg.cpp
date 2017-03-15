
// LOGINDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LOGIN.h"
#include "LOGINDlg.h"
#include "afxdialogex.h"
#include "HttpClient.h"
#include "Func.h"
#include "Code.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void getLoginInfo();

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLOGINDlg �Ի���



CLOGINDlg::CLOGINDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LOGIN_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLOGINDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_Button);
	DDX_Control(pDX, IDC_EDIT1, m_username);
	DDX_Control(pDX, IDC_EDIT2, m_password);
}

BEGIN_MESSAGE_MAP(CLOGINDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CLOGINDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CLOGINDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CLOGINDlg ��Ϣ�������

BOOL CLOGINDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	getLoginInfo();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CLOGINDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CLOGINDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CLOGINDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



HttpClient httpClient;

CString username = L"";
CString password = L"";

CString postData = L"";


//��ע����ж�ȡ�û��������뵽username��password
void getLoginInfo() {
	HKEY  hKey;
	CString KeyName;
	CStringArray ret;


	//��ע���
	if (RegCreateKeyEx(HKEY_CURRENT_USER, TEXT("SOFTWARE\\SwuLogin"), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL) != ERROR_SUCCESS) {
		return;
	}


	DWORD lpType = REG_SZ;
	BYTE *data = new BYTE[256];
	DWORD dwSize;
	CString value;

	//��ȡ�û���
	dwSize = 256;
	KeyName = L"username";
	if (RegQueryValueEx(hKey, KeyName, NULL, &lpType, data, &dwSize) != ERROR_SUCCESS) {
		return;
	}
	value.Format(TEXT("%s"), data);
	AfxGetMainWnd()->GetDlgItem(IDC_EDIT1)->SetWindowText(value);
	UpdateWindow(AfxGetMainWnd()->GetDlgItem(IDC_EDIT1)->m_hWnd);

	
	//��ȡ����
	dwSize = 256;
	KeyName = L"password";
	if (RegQueryValueEx(hKey, KeyName, NULL, &lpType, data, &dwSize) != ERROR_SUCCESS) {
		return;
	}
	value.Format(TEXT("%s"), data);
	AfxGetMainWnd()->GetDlgItem(IDC_EDIT2)->SetWindowText(value);
	UpdateWindow(AfxGetMainWnd()->GetDlgItem(IDC_EDIT2)->m_hWnd);

	delete[]data;
	RegCloseKey(hKey);
}

//����¼��Ϣ���浽ע���
void setLoginInfo() {
	HKEY  hKey;
	CString KeyName;
	CStringArray ret;


	//��ע���
	if (RegCreateKeyEx(HKEY_CURRENT_USER, TEXT("SOFTWARE\\SWULOGIN"), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL) != ERROR_SUCCESS) {
		return;
	}

	DWORD lpType = REG_SZ;
	BYTE *data;
	DWORD dwSize;

	KeyName = L"username";
	RegSetValueEx(hKey, KeyName, NULL, REG_SZ, (BYTE*)username.GetBuffer(0), username.GetLength() * 2 + 2);
	username.ReleaseBuffer();

	KeyName = L"password";
	RegSetValueEx(hKey, KeyName, NULL, REG_SZ, (BYTE*)password.GetBuffer(0), password.GetLength() * 2 + 2);
	password.ReleaseBuffer();

	RegCloseKey(hKey);
}


//��Ϊ��һ���ܺ�ʱ�䣬���Ե�����ȡ��������
BOOL getPostData() {
	CString queryString = UrlEncode(UrlEncode(L"wlanuserip=7fe8068476a9ae5287fa52adf9118d6b&wlanacname=d3fd3003b8a92e5a0d9c924efc713c22&ssid=&nasip=f2267a27304a35841a4b2f3bbdcef5e6&snmpagentip=&mac=3eaf0c9c666b678946730b48dfc2c202&t=wireless-v2&url=bc769469379bc92a49dd39c8187326462c2c594662118267&apmac=&nasid=d3fd3003b8a92e5a0d9c924efc713c22&vid=622c44f245fcc3db&port=b7937cfdf5aa03ef&nasportid=136985ff42ef1c4528a45c84a073ddb8103c7c30674361d055125e5a7a865d356473378537f0ced6"));
	postData = L"userId=" + username + L"&password=" + password + L"&service=%25E9%25BB%2598%25E8%25AE%25A4&queryString=" + queryString + L"&operatorPwd=&operatorUserId=&validcode=";
	return TRUE;

	/*
	//��ȡ��¼��ַ
	CString ret = httpClient.Get(L"http://123.123.123.123");
	CString addr = SubString(ret, L"<script>top.self.location.href='", L"</script>");
	CString queryString = SubString(addr, L"http://222.198.127.170/eportal/index.jsp?", L"'");

	//�õ�¼��ַ�����ܶ���Ϣ����Ҫ����URL����������Ϊ��¼ʱ���post��Ϣ
	queryString = UrlEncode(UrlEncode(queryString));

	if (queryString.CompareNoCase(L"") == 0) {
		AfxMessageBox(L"��ȡ��¼��ַʧ�ܣ������Ƿ��ܷ���У԰����login.swu.edu.cn", MB_ICONERROR);
		return FALSE;
	}

	//ƴװ��¼��Ϣ
	postData = L"userId=" + username + L"&password=" + password + L"&service=%25E9%25BB%2598%25E8%25AE%25A4&queryString=" + queryString + L"&operatorPwd=&operatorUserId=&validcode=";
	OutputDebugString(postData);
	return TRUE;*/
}

//��¼
void login() {
	getPostData();

	CString loginRet = httpClient.Post(L"http://222.198.127.170/eportal/InterFace.do?method=login", postData);


	if (SubString(loginRet, L"result\":\"", L"\"").CompareNoCase(L"success") != 0) {
		AfxMessageBox(L"��¼ʧ�ܣ��������û������������", MB_ICONERROR);
		return;
	}

	setLoginInfo();
	
}

//�˳���¼
void logout() {
	httpClient.Get(L"http://login.swu.edu.cn/");
	httpClient.Get(L"http://login.swu.edu.cn/eportal/gologout.jsp");
	CString url = httpClient.GetRecvHeader(L"Location");

	url = url + L"&";
	CString userIndex = SubString(url, L"userIndex=", L"&");
	if (url.Compare(L"") == 0) {
		return;
	}
	httpClient.Post(L"http://login.swu.edu.cn/eportal/InterFace.do?method=logout", L"userIndex=" + userIndex);
}

//�Զ��߳�
bool isContinue = false;
int now = 0;
DWORD WINAPI DoThread(LPVOID pParam) {
	while (true) {
		if (isContinue == false) {
			return 0;
		}
		now = now + 1;
		int minutes = now / 60;
		if (minutes > 10) {
			logout();
			login();
			now = 0;
		}

		Sleep(1000);
	}
}


void CLOGINDlg::OnBnClickedButton1()
{
	CString _username;
	CString _password;

	m_username.GetWindowText(_username);
	m_password.GetWindowText(_password);
	_username.Replace(L" ", L"");

	if (_username.CompareNoCase(L"") == 0 || _password.CompareNoCase(L"") == 0) {
		AfxMessageBox(L"�û��������벻��Ϊ�գ�", MB_ICONERROR);
		return;
	}
	username = _username;
	password = _password;
	

	CString txt;
	m_Button.GetWindowText(txt);
	if (txt.Compare(L"����ͣ") == 0) {
		//�Ȼ�ȡһ�ε�¼��Ϣ
		if (getPostData() == FALSE) {
			return;
		}

		isContinue = true;
		AfxBeginThread((AFX_THREADPROC)DoThread, NULL);
		m_Button.SetWindowText(L"�ѿ�ʼ");
	}
	else {
		isContinue = false;
		m_Button.SetWindowText(L"����ͣ");
	}

}

void CLOGINDlg::OnBnClickedButton2()
{
	CString _username;
	CString _password;

	m_username.GetWindowText(_username);
	m_password.GetWindowText(_password);
	_username.Replace(L" ", L"");

	if (_username.CompareNoCase(L"") == 0 || _password.CompareNoCase(L"") == 0) {
		AfxMessageBox(L"�û��������벻��Ϊ�գ�", MB_ICONERROR);
		return;
	}
	username = _username;
	password = _password;

	if (getPostData() == FALSE) {
		return;
	}

	logout();
	login();

}
