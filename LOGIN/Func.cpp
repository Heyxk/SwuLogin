#include "stdafx.h"
#include "Func.h"
#include "Code.h"
//Զ�̷�����������Ұ��IP��ַ�ж���λ
#define IP_LEN 2

CString GetRandWord(DWORD n)//��ȡn�������ĸ
{
	//srand((unsigned)time(NULL));
	int i;
	CString str;
	char c;
	int t;
	for (i = 0; i < n; i++)
	{
		t = rand() % 3;
		if (t>1)
		{
			t = 'a';
		}
		else
		{
			t = 'A';
		}
		c = t + rand() % 26;
		str = str + c;
	}
	return str;
}
DWORD GetRand(DWORD m, DWORD n)//m <= rand() % (n - m + 1) + m <= n
{
	//srand((unsigned)time(NULL));
	return rand() % (n - m + 1) + m;
}
DOUBLE GetRandZeroToOne()
{
	//srand((unsigned)time(NULL));
	return  (rand() % 10) / (float)10;//����0-1����������
}
CString GetRandStr(DWORD m, DWORD n)//m <= rand() % (n - m + 1) + m <= n
{
	CString str;
	str.Format(TEXT("%d"), GetRand(m, n));
	return str;
}

CString UnipusIp;
CString GetString(DWORD id)//����Դ����ȡ�ַ���
{
	CString ss;
	/*
	int c;
	c = LoadString(NULL, id, ss.GetBuffer(1024000), 1024000);
	ss.ReleaseBuffer();
	ss.Left(c);
	*/
	ss.LoadString(id);
	ss.Replace(TEXT("UnipusIp"), UnipusIp);
	return ss;
}
void SetUnipusIp(CString ip) {
	UnipusIp = ip;
}
CString GetUnipusIp() {
	return UnipusIp;
}

CString LoadResource(DWORD ID,CString type) {
	CString result;
	HINSTANCE hInstance = AfxFindResourceHandle(MAKEINTRESOURCE(ID), RT_RCDATA);    //��Դ��ID��  
	HRSRC hRes = FindResource(hInstance, MAKEINTRESOURCE(ID), type);    //type����Դ�����ͣ�һ��Ҫд��  
	HGLOBAL hResData = LoadResource(hInstance, hRes);
	void * lpvData = LockResource(hResData);

	result = (char*)lpvData;
	//int cbSize = SizeofResource(hInstance, hRes);
	return result;
}

CString SubString(CString s, CString head, CString tail)
{
	int iPos = s.Find(head);
	if (iPos == -1)return TEXT("");
	iPos += head.GetLength();
	int iPos1 = s.Find(tail, iPos);
	if (iPos1 == -1)return TEXT("");
	return s.Mid(iPos, iPos1 - iPos);
}
CString SubString(CString s, CString head, CString tail,DWORD &t)
{
	int iPos = s.Find(head, t);
	if (iPos == -1)return TEXT("");
	iPos += head.GetLength();
	int iPos1 = s.Find(tail, iPos);
	if (iPos1 == -1)return TEXT("");
	t = iPos1;
	return s.Mid(iPos, iPos1 - iPos);
}
long long getCurrentTime()
{
	long long time_last;
	time_last = time(NULL);     //������  
	struct timeb t1;
	ftime(&t1);
	//CString strTime;
	//strTime.Format(_T("%lldms"), t1.time * 1000 + t1.millitm);  //�ܺ�����  
	//OutputDebugString(strTime);
	return t1.time * 1000 + t1.millitm;
}
BOOL TestUserName(CString User, int n) {
	/*�򵥵�����ÿ̨�����������n���˺ţ���ֹ���������
	����ʹ�÷����棬����ʹ�÷��ؼ�*/
	HKEY  hKey;
	CString KeyName;
	CStringArray ret;


	//��ע���
	if (RegCreateKeyEx(HKEY_CURRENT_USER, TEXT("SOFTWARE\\SKSoftware"), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL) != ERROR_SUCCESS) {
		return TRUE;
	}

	//��ѯ��ǰ�����Ѿ��ù����û�
	CString Value;
	DWORD dwSize;
	BYTE *data;
	DWORD lpType = REG_SZ;
	for (int i = 0; i < n; i++) {
		KeyName.Format(TEXT("%d"), i);

		data = new BYTE[256];
		dwSize = 256;
		
		//��ȡ��ֵ����
		if (RegQueryValueEx(hKey, KeyName, NULL, &lpType, data, &dwSize) != ERROR_SUCCESS) {
			continue;
		}
		
		//��ȡ��һ��ʹ�ù����û���
		Value.Format(TEXT("%s"), data);
		ret.Add(Value);

		delete[]data;
	}

	//RegCloseKey(hKey);

	for (int i = 0; i < ret.GetSize(); i++) {
		//����Ѿ���ע���,ֱ�ӷ��سɹ�
		if (User == ret[i]) {
			RegCloseKey(hKey);
			return TRUE;
		}
		//ע�����û�У�����һ�����û�
		if (i == ret.GetSize() - 1) {

			if (i == n - 1) {
				//�������ܹ�ʹ�õ�����û���
				RegCloseKey(hKey);
				return FALSE;
			}
			else {
				//���ܽ���һ�����û�
				break;
			}

		}
	}

	//��ע�����д�����û�����Ϣ
	KeyName.Format(TEXT("%d"), ret.GetSize());

	RegSetValueEx(hKey, KeyName, NULL, REG_SZ,(BYTE*)User.GetBuffer(0), User.GetLength()*2+2);
	User.ReleaseBuffer();

	RegCloseKey(hKey);
	return TRUE;
}

BOOL GetBoolByRate(int rate) {
	/*rate�����ؼٵĸ���
	  rate: rateΪ���ͣ�����97%����97%�ĸ��ʷ��ؼ�
	*/

	//srand((unsigned)time(NULL));
	if (rate > 100 || rate < 0)return FALSE;
	int n = rand() % 100;
	if (n > rate) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

CString simpleEncrypt(CString str) {
	 CString code = L"3yg945v6wnop70qcderxfbshijlztuma812k";
	 CString decode = L"n4d0qhtmcu5vi38k1x7fabjw2rsozeyg69pl";
	 int pos = 0;
	 CString ret;
	 for (int i = 0; i < str.GetLength(); i++) {
		 pos = code.Find(str.GetAt(i));
		 if (pos == -1)
			 continue;
		 ret = ret + decode.GetAt(pos);
	 }
	 return ret;

}
CString simpleDecrypt(CString str) {
	CString code = L"3yg945v6wnop70qcderxfbshijlztuma812k";
	CString decode = L"n4d0qhtmcu5vi38k1x7fabjw2rsozeyg69pl";
	int pos = 0;
	CString ret;
	for (int i = 0; i < str.GetLength(); i++) {
		pos = decode.Find(str.GetAt(i));
		if (pos == -1)
			continue;
		ret = ret + code.GetAt(pos);
	}
	return ret;

}

BOOL localAuthorize(CString activeCode,CString userName,CString &retIp)
{
	if (activeCode.GetLength() < 5) {
		return FALSE;
	}
	//IP��֤
	//��ߵ�һλΪIP�ļ��ܴ���
	CString ip;
	int num = _ttoi(activeCode.Left(1));
	ip = simpleDecrypt(activeCode.Mid(1, IP_LEN));
	for (int i = 0; i < num-1; i++) {
		ip=simpleDecrypt(ip);
	}
	if (_ttoi(ip) > 50 || _ttoi(ip) < 30) {
		//2016��Ϊ37,2017��Ϊ38���Դ�����
		return FALSE;
	}
	//����֮��Ȼ����Ȩ���б����IP��ַ��ȡ����
	retIp = ip;

	//���������˺���֤
	//ȡ���˺ŵļ��ܴ���
	CString name;
	num = _ttoi(activeCode.Mid(3,1));
	name = simpleDecrypt(activeCode.Mid(4, activeCode.GetLength() - 4));
	for (int i = 0; i < num - 1; i++) {
		name = simpleDecrypt(name);
	}
	if (userName.Compare(name) == 0) {
		return TRUE;
	}

	return FALSE;
}
