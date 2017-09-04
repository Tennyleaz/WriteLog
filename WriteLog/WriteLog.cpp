#include "stdafx.h"
#include "afx.h"
//#include "afxwin.h"
#include "windows.h"

void WriteLog(CString szLog)
{
	SYSTEMTIME sTime;
	::GetLocalTime(&sTime);
	CFile aFile;
	WCHAR buf[512];
	memset(buf, 0x00, 512);
	GetCurrentDirectory(512, buf);
	//TCHAR szBuf[4096] = { 0 };
	//GetModuleFileName(AfxGetInstanceHandle(), szBuf, 4096);
	//*_tcsrchr(szBuf, L'\\') = 0;
	CString szFileName;
	szFileName.Format(L"WCardApp%02d%02d.log", sTime.wMonth, sTime.wDay);
	//szFileName = (CString)szBuf + (CString)"\\" + szFileName;
	if (aFile.Open(szFileName, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) {
		aFile.SeekToEnd();
		CString Msg;
		Msg.Format(L"%02d:%02d:%02d-%03d %s\r\n", sTime.wHour, sTime.wMinute, sTime.wSecond, sTime.wMilliseconds, (LPCTSTR)szLog);
		char* pChar = new char[Msg.GetLength() + 1];
		memset(pChar, 0x00, Msg.GetLength() + 1);
		WideCharToMultiByte(CP_UTF8, 0, (LPCTSTR)Msg, Msg.GetLength(), pChar, Msg.GetLength() + 1, NULL, NULL);
		aFile.Write(pChar, Msg.GetLength() + 1);
		aFile.Close();
		if (pChar != NULL) {
			delete[] pChar;
			pChar = NULL;
		}
	}
}

int main()
{
	WCHAR * pstr = L"ひろゆき\n";
	CString cstr;
	cstr.Format(L"pstr=%s, pstr[0]=%c\n", pstr, pstr[0]);
	WriteLog(cstr);
	system("pause");
	return 0;
}

