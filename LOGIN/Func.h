/*
���ﶨ�����һЩ�����Ժ���
*/

#ifndef FUNC_H
#define FUNC_H

#include <afx.h>
#include<time.h>
#include<sys/timeb.h>

CString SubString(CString s, CString head, CString tail);		//��ȡ�ַ���
CString SubString(CString s, CString head, CString tail,DWORD &t);	//��T��ʼ��head��tailλ�÷��ص�t�����ڳ���Ѱ���ַ���

DOUBLE GetRandZeroToOne();		//0��1�������
DWORD GetRand(DWORD m, DWORD n);	//ȡ�����
CString GetRandStr(DWORD m, DWORD n);	//ȡ�������ֻ�����Ƿ���ֵ���ַ�������
CString GetRandWord(DWORD n);		//ȡ����ΪN�������ĸ�ַ���

void SetUnipusIp(CString ip);		//��GetString����ʹ�ã������滻�ַ��������IP
CString GetUnipusIp();
CString GetString(DWORD id);		//����Դ�ļ���ȡ�ַ���
CString LoadResource(DWORD ID, CString type);	//����Դ�м���ָ�����͵���Դ

long long getCurrentTime();		//��ȡ���ڵ�1970��1��1�յĺ�����
BOOL TestUserName(CString User, int n);	//����һ̨��������¼n���û�������������򷵻ؼ�

BOOL GetBoolByRate(int rate);		//���ݱ���rate������ķ����Ƿ�Ϊ��

CString simpleEncrypt(CString s);	//�򵥼���
CString simpleDecrypt(CString s);	//�򵥽���

BOOL localAuthorize(CString activeCode, CString userName, CString &retIp);//��Ȩ��ı�����֤
#endif