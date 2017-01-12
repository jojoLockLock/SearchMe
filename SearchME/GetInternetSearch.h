
#pragma once
#include <afxinet.h>
#include <iostream>
#include <fstream>
#include <vector>
//#include "html/ParserDom.h"  
//#include "html/utils.h" 

using namespace std;
//using namespace htmlcxx;


#define IsHexNum(c) ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'))
#define SEARCH_URL _T("http://www.btbook.net/search/%s.html")
#define MAIN_URL	_T("http://www.btmeet.org")

class SearchListInfo
{
public:
	CString SearchListName;
	CString SearchSize;
	CString SearchLink;
	CString SearchHotPoint;
};


class SearchPageTmp
{
public:
	CString strSearchItem;
	CString strPage;
	void* param;
};

class CGetInternetSearch
{
public:
	CGetInternetSearch(void);
	~CGetInternetSearch(void);
public:
	 BOOL SearchItem(CString strKeyWord,CString &html);
	 BOOL ParserHtmlListName(CString testbuffer);
	BOOL NextOrMorePage(CString strSearchItem);
	bool DownloadStrings(LPCTSTR szUrl, CString &str);
	CString Utf8ToStringT(LPSTR str);
	CString UrlDecode(LPCTSTR url);
	CString GetParseMagnet(CString wiki);
	static unsigned int __stdcall CGetInternetSearch::ParserInsertThread(void *param);
public:
	vector<char> v;
	static vector<SearchListInfo> vListInfo;
public:
	static HANDLE	g_hThreadEvent;
};
