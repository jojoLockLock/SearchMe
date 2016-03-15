#include "StdAfx.h"
#include "GetInternetSearch.h"

CGetInternetSearch::CGetInternetSearch(void)
{
}

CGetInternetSearch::~CGetInternetSearch(void)
{
}
//初始化
vector<SearchListInfo> CGetInternetSearch::vListInfo;


/*******************************************
*函数名称：SearchItem
*函数功能：访问网络 搜索关键字
*参数列表: 输入：搜索关键字，输出：获取的网页信息
*搜索字符有时间出问题，xp有不正常情况。
********************************************/
BOOL CGetInternetSearch::SearchItem(CString strKeyWord,CString &html)
{
		CString strBaiduSearch;
		//strBaiduSearch.Format(_T("http://www.baidu.com/s?wd=%s/"),strKeyWord);
		strBaiduSearch.Format(_T("http://119.29.40.159/search/%s.html"),strKeyWord);
		//MessageBox(NULL,strBaiduSearch,NULL,NULL);
		CInternetSession session;
		CHttpFile * file = NULL;
		try
		{
			file = (CHttpFile *)session.OpenURL(strBaiduSearch);
			if(file)
			{
				TCHAR line[512];
				while(file->ReadString(line,512) != NULL)
				{
					int nBufferSize = MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)line, -1, NULL, 0);
					wchar_t *pBuffer = new wchar_t[nBufferSize+1];
					MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)line, -1 , pBuffer, nBufferSize*sizeof(wchar_t));  
					html += pBuffer;
					delete[] pBuffer;
				}
				file->Close();
			}
		}
		catch (CInternetException* e)
		{
			e->Delete();
			html = "CInternet Exception";
		}
		file = NULL;
		session.Close();
		//printf("%d\n",html.GetLength());
		return 1;
}

unsigned int __stdcall CGetInternetSearch::ParserInsertThread(void *param)
{
	SearchPageTmp *pThis = NULL;
	if (param == NULL)
		return -1;
	pThis = (SearchPageTmp *)param;
	CString strTmp,strTmpPage;
	strTmpPage.Format(_T("%s/%s"),pThis->strSearchItem,pThis->strPage);
	SearchItem(strTmpPage,strTmp);
	ParserHtmlListName(strTmp);
	//Sleep(50);
	//MessageBox(NULL,strTmp,NULL,NULL);
	return 0;
}
/************************************
* 函数名称:    NextOrMorePage
* 功能描述:   读取bthand获取的数据 打开下几页 
* 参数列表:  输入 搜索关键字  输出 页面信息
* 返回值:  
/************************************/
BOOL CGetInternetSearch::NextOrMorePage(CString strSearchItem)
{
	CString secondPageItem;	//第二页搜索 简单实现
	CString thridPageItem;	//第三页搜索 简单实现
	CString fourthPageItem;	//第四页搜索 简单实现
	CString fifthPageItem; //第五页
	CString nPageItem[5] = {_T("1-3"),_T("2-3"),_T("3-3"),_T("4-3"),_T("5-3")};
	CString strtmp,strhtml;
	//解析网页
	/*
	strtmp.Format(_T("%s/1-3"),strSearchItem);
	SearchItem(strtmp,strhtml);
	ParserHtmlListName(strhtml);
	*/
	HANDLE  handle[5];
	for (int i = 0; i < 5 ;i++)
	{

			//HANDLE  handle;  
			//MessageBox(NULL,nPageItem[i],NULL,NULL);
			SearchPageTmp sitem;
			sitem.strSearchItem = strSearchItem;
			sitem.strPage = nPageItem[i];
			handle[i] =(HANDLE)_beginthreadex(NULL, 0, ParserInsertThread, &sitem, 0, NULL);
			//handle[i] = AfxBeginThread((AFX_THREADPROC)ParserInsertThread,&sitem,0,0,0,NULL);
			//handle[i]=CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ParserInsertThread, &sitem, 0, NULL);
			Sleep(50);
	}
	
	WaitForMultipleObjects(5, handle, TRUE, INFINITE); 
	return 1;
}
/************************************
* 函数名称:    ParserHtmlListName
* 功能描述:   解析网页数据
* 参数列表:  输入 网页数据 保存到vector中
* 返回值:  
/************************************/
BOOL CGetInternetSearch::ParserHtmlListName(CString testbuffer)
{
	while(testbuffer.Find(_T("<li>")) >=0 )
	{
		SearchListInfo m_Search;
		CString strTmpName;
		// ListName
		cout<<"***********************"<<endl;
		int splace = testbuffer.Find(_T("target=\"_blank\">"));
		int eplace =testbuffer.Mid(splace).Find(_T("</a>"));
		//cout<<testbuffer.Mid(splace+4,eplace-splace-10)<<endl;
		strTmpName = testbuffer.Mid(splace+16,eplace-16);
		strTmpName.Replace(_T("<b>"),_T(""));
		strTmpName.Replace(_T("</b>"),_T(""));
		//Size
		int sSize = testbuffer.Find(_T("\"lightColor\">"));
		int eSize = testbuffer.Find(_T("</span></li>"));
		//cout<<testbuffer.Mid(sSize+13,eSize-sSize-13)<<endl;
		//Link
		int smagnet = testbuffer.Find(_T("<a href=\"magnet"));
		int emagnet = testbuffer.Find(_T("</a> <a"));
		//cout<<testbuffer.Mid(smagnet+9,emagnet-smagnet-32)<<endl;
		//link_hot
		int shot = testbuffer.Find(_T("<span>下载热度"));
		int ehot = testbuffer.Find(_T("</b></span>"));
		//cout<<testbuffer.Mid(shot+19,ehot-shot-19)<<endl;
		CString temp;
		temp.Format(_T("%d,%d"),shot,ehot);
		//MessageBox(NULL,temp,NULL,NULL);
		//break;

		m_Search.SearchListName = strTmpName;
		m_Search.SearchLink = testbuffer.Mid(smagnet+9,emagnet-smagnet-32);
		m_Search.SearchSize = testbuffer.Mid(sSize+13,eSize-sSize-13);
		m_Search.SearchHotPoint = testbuffer.Mid(shot+14,ehot-shot-14);
		
		
		vListInfo.push_back(m_Search);

		testbuffer = testbuffer.Mid(emagnet+9);
		//testbuffer = testbuffer.Mid(eplace+4);
		//Sleep(1000);
	}

	return TRUE;
}