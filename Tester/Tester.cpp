// Tester.cpp : DLL アプリケーション用にエクスポートされる関数を定義します。
//

#include "stdafx.h"

#pragma warning(push)
// warning C4793(ネイティブ関数としてコンパイルされました) を抑制
#pragma warning(disable: 4793)
#include <WinUnit.h>
#pragma warning(pop)

#include <string>
#include "AssociativeVector.h"

using namespace std;
using namespace TakeAsh;

struct HostInfo {
	wstring	name;
	wstring	url;
	wstring	lang;

	HostInfo(wstring Name=L"", wstring Url=L"", wstring Lang=L""):
		name(Name), url(Url), lang(Lang)
	{}
};

typedef AssociativeVector<wstring, HostInfo> HostMap;

static const HostMap::value_type rawList[] = {
	make_pair(L"G_en", HostInfo(L"グーグル", L"https://www.google.com/", L"English")),
	make_pair(L"G_ja", HostInfo(L"グーグル", L"https://www.google.co.jp/", L"Japanese")),
	make_pair(L"Y_en", HostInfo(L"ヤフー！", L"https://www.yahoo.com/", L"English")),
	make_pair(L"Y_ja", HostInfo(L"ヤフー！", L"https://www.yahoo.co.jp/", L"Japanese")),
};

BEGIN_TEST(AssociativeVector_01_DefaultConstructor)
{
	WIN_TRACE(
		_T("AssociativeVector: DefaultConstructor -> ")
		_T("size:0\n")
	);
	HostMap hostMap;
	WIN_ASSERT_ZERO(hostMap.size());
}
END_TEST

BEGIN_TEST(AssociativeVector_02_ConstructFromArray)
{
	WIN_TRACE(
		_T("AssociativeVector(rawList) -> ")
		_T("size:%d\n"),
		_countof(rawList)
	);
	const HostMap hostMap(rawList, rawList + _countof(rawList));
	WIN_ASSERT_EQUAL(_countof(rawList), hostMap.size());
	size_t index = 0;
	for(HostMap::const_iterator itr=hostMap.begin(); itr != hostMap.end(); ++itr, ++index){
		const HostMap::value_type& expected = rawList[index];
		WIN_ASSERT_STRING_EQUAL(expected.second.name.c_str(), itr->second.name.c_str());
		WIN_ASSERT_STRING_EQUAL(expected.second.url.c_str(), itr->second.url.c_str());
		WIN_ASSERT_STRING_EQUAL(expected.second.lang.c_str(), itr->second.lang.c_str());
	}
	for(size_t i=0; i < _countof(rawList); ++i){
		const HostMap::value_type& expected = rawList[i];
		const HostInfo* pHostInfo = hostMap[expected.first];
		WIN_ASSERT_NOT_NULL(pHostInfo);
		WIN_ASSERT_STRING_EQUAL(expected.second.name.c_str(), pHostInfo->name.c_str());
		WIN_ASSERT_STRING_EQUAL(expected.second.url.c_str(), pHostInfo->url.c_str());
		WIN_ASSERT_STRING_EQUAL(expected.second.lang.c_str(), pHostInfo->lang.c_str());
	}
}
END_TEST

// EOF
