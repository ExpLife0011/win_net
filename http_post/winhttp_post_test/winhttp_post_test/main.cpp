/**
An Example about upload file by WinHttp.

cswuyg
2013.7.11
*/
#include <windows.h>
#include <winhttp.h>
#pragma comment(lib, "winhttp.lib")

#include <string>
#include <iostream>

void WinHttpPostTest()
{
	HINTERNET hSession = ::WinHttpOpen(L"cswuyg post test/1.0", WINHTTP_ACCESS_TYPE_NO_PROXY, NULL, NULL, NULL);
	HINTERNET hConnect = ::WinHttpConnect(hSession, L"127.0.0.1", INTERNET_DEFAULT_HTTP_PORT, 0);
	if (hConnect == NULL)
	{
		int i = ERROR_WINHTTP_INCORRECT_HANDLE_TYPE;
		return;
	}
	const wchar_t* lpszAcceptedType[] = {L"*/*", NULL};
	HINTERNET hRequest = ::WinHttpOpenRequest(hConnect, L"POST", L"hfs_up", L"HTTP/1.1", WINHTTP_NO_REFERER, lpszAcceptedType, 0);
	if (hRequest == NULL)
	{
		return;
	}
	DWORD dwTime = 5000;
	::WinHttpSetOption(hRequest, WINHTTP_OPTION_CONNECT_TIMEOUT, &dwTime, sizeof(DWORD));
	std::wstring strHeader = L"Content-Type: multipart/form-data; boundary=--boundary_cswuygtest\r\n";
	::WinHttpAddRequestHeaders(hRequest, strHeader.c_str(), strHeader.length(), WINHTTP_ADDREQ_FLAG_ADD | WINHTTP_ADDREQ_FLAG_REPLACE);

	std::string strMIME = "----boundary_cswuygtest\r\n";
	strMIME += "Content-Disposition: form-data; name=\"ufile01\"; filename=\"upload_test_http_cswuyg.txt\"\r\n";
	strMIME += "Content-Type:application/octet-stream\r\n\r\n";
	strMIME += "texttextinfocswuyg\r\n";
	/////////////////////////////
	//���������֮�⣬��ͷ������Ҫ������ı���Ϣ������hfs������Ǳ��޷�д���ļ��������Ϊ���ԡ�
	//strMIME += "----boundary_cswuygtest\r\n" ;
	//strMIME += "Content-Disposition: form-data; name=\"name\"\r\n\r\n";
	//strMIME += "temp.txt\r\n";
	/////////////////////////
	strMIME += "----boundary_cswuygtest--\r\n";
	/////////////////////////
	//����ֱ��д��
	//::WinHttpSendRequest(hRequest, strHeader.c_str(), strHeader.length(), (LPVOID)strMIME.c_str(), strMIME.length(), strMIME.length(), 0);

	//Ҳ���Ժ���ֲ�д��
	::WinHttpSendRequest(hRequest, NULL, 0, NULL, 0, strMIME.length(), 0);
	DWORD dwWritten = 0;
	while(!strMIME.empty())
	{
		::WinHttpWriteData(hRequest, strMIME.c_str(), strMIME.length(), &dwWritten);
		if (strMIME.length() > dwWritten)
		{
			strMIME.substr(dwWritten);
		}
		else
		{
			strMIME = "";
		}
		
	}
	::WinHttpReceiveResponse(hRequest, NULL);

	char buf[1024] = { 0 };
	DWORD dwToRead = 1024;
	DWORD dwHaveRead = 0;
	::WinHttpReadData(hRequest, buf, dwToRead, &dwHaveRead);
	std::cout << buf << std::endl;
	::WinHttpCloseHandle(hRequest);
	::WinHttpCloseHandle(hConnect);
	::WinHttpCloseHandle(hSession);
}



int main()
{
	WinHttpPostTest();
	system("pause");
}