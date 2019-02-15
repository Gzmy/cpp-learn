#include <curl/curl.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
using namespace std;

/*
 * 1.借助libcurl第三方库实现获取网页功能
 * 输入是目标 url
 * 输出结果是 html
 */

//这个函数将在libcurl接收到响应的时候进行调用
//会获取到目标的html界面
//ptr: libcurl接收到响应的html页面的缓冲区
//size * nmemb: 缓冲区长度
//userdata: 用户自定义缓冲区
//本函数功能:把ptr里的数据拷贝至用户自定义空间
size_t WriteData(char *ptr, size_t size, size_t nmemb, void *userdata)
{
	std::string *output = (std::string*)userdata;
	output->append(ptr, size * nmemb);
	return size * nmemb;
}

class ScopedHandler
{
public:
	ScopedHandler(CURL *h) : handler(h){}
	~ScopedHandler(){ curl_easy_cleanup(handler); }
private:
	CURL* handler;
};


bool OpenPage(const std::string& url, std::string* html)
{
	//初始化句柄
	CURL *handler = curl_easy_init();
	ScopedHandler scoped_handler(handler);

	//构造http请求,第三个参数是转化成C风格字符串
	//最核心的设置url,http请求中的其他handler , libcurl也是支持的
	curl_easy_setopt(handler, CURLOPT_URL, url.c_str());
	//设置响应如何处理,第三个参数是函数指针
	curl_easy_setopt(handler, CURLOPT_WRITEFUNCTION, WriteData);
	curl_easy_setopt(handler, CURLOPT_WRITEDATA, html);

	//发送请求
	CURLcode ret = curl_easy_perform(handler);
	if(ret != CURLE_OK)
	{
		fprintf(stderr, "curl_easy_perform faild!\n");
		return false;
	}
	return true;
}


void test()
{
	std::string html;
	OpenPage("https://www.qu.la/book/96524/", &html);
	printf("%s\n", html.c_str());
}

//2.把主页的章节url解析出来
//实际上是字符串解析的操作
//借助正则表达式 基于boost

void ParseMainPage(const std::string &html, std::vector<std::string>*url_list)
{
	boost::regex reg("/96524/\\S+html");
	//借助reg对象进行字符串查找
	std::string::const_iterator cul = html.begin(); //查找的开头
	std::string::const_iterator end = html.end(); //查找的结尾
	boost::smatch result; //结果存放的空间
	while(boost::regex_search(cul, end, result, reg))
	{
		//result[0]是boost中内置的对象,可以隐式转换成string
		//这个对象中的取到的second属性,对应了接下来的查找位置
		url_list->push_back("https://www.qu.la/book" + result[0]);
		cul = result[0].second;
	}
}

void test1()
{
	std::string html;
	std::vector<std::string> url_list;
	OpenPage("https://www.qu.la/book/96524/", &html);
	ParseMainPage(html, &url_list);
	for(size_t i = 0; i < url_list.size(); ++i)
	{
		printf("%s\n", url_list[i].c_str());
	}
}

//3.获取到小说详情页的html
//这一步和第一步完全相同
void test2()
{
	std::string html;
	OpenPage("https://www.qu.la/book/96524/4955309.html", &html);
	printf("%s\n", html.c_str());
}

//4.解析小说详情页html,获取其中正文内容
void ParseDetailPage(const std::string& html, std::string *content)
{
	//基于字符串查找的方式解析
	//使用正则表达式不是很方便
	//找到开始和结束,取字符串子串即可
	std::string beg_flag = "<div id=\"content\">";
	size_t beg = html.find(beg_flag);
	if(beg == std::string::npos)
	{
		fprintf(stderr, "找不到开始标记\n");
		return;
	}
	beg += beg_flag.size();

	std::string end_flag = "<script>chaptererror();</script>";
	size_t end = html.find(end_flag);
	if(end == std::string::npos)
	{
		fprintf(stderr, "找不到结束标记\n");
		return;
	}

	if(beg >= end)
	{
		fprintf(stderr, "开始结束标记有问题!beg = %lu, end = %lu\n", beg, end);
		return;
	}

	*content = html.substr(beg, end - beg);

	//替换掉转义字符
	boost::algorithm::replace_all(*content, "&nbsp;", " ");	
	boost::algorithm::replace_all(*content, "<br />", " ");	
	boost::algorithm::replace_all(*content, "</br>", " ");	
	return;
}

void test3()
{
	std::string html;
	OpenPage("https://www.qu.la/book/96524/4955309.html", &html);
	std::string content;
	ParseDetailPage(html, &content);
	printf("%s\n", content.c_str());
}

//实现整体框架
void Run()
{
	//1.获取主页html
	std::string html;
	OpenPage("https://www.qu.la/book/96524/", &html);
	//2.解析所有章节的url列表
	std::vector<std::string> url_list;
	ParseMainPage(html, &url_list);
	//3.遍历url列表,一次获取每个章节的html
	for(size_t i = 0; i < url_list.size(); ++i)
	{
		fprintf(stderr, "%s\n", url_list[i].c_str());
		OpenPage(url_list[i], &html);
	
		//4.解析每个章节内容
		std::string content;
		ParseDetailPage(html, &content);
		printf("%s\n", content.c_str());
	}
}

int main()
{
	//test3();
	Run();
	return 0;
}
