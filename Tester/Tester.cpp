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

#define assertAssociativeVector(Expected, Actual)	\
	{	\
		WIN_TRACE(_T("    size:%d\n"), Expected.count);	\
		WIN_ASSERT_EQUAL(Expected.count, Actual.size());	\
		size_t i1 = 0;	\
		for(auto itr=Actual.begin(); itr != Actual.end(); ++itr, ++i1){	\
			const auto& value = Expected.list[i1];	\
			WIN_TRACE(_T("    %d:'%s'\n"), i1, value.second.name.c_str());	\
			WIN_ASSERT_STRING_EQUAL(value.second.name.c_str(), itr->second.name.c_str());	\
			WIN_ASSERT_STRING_EQUAL(value.second.url.c_str(), itr->second.url.c_str());	\
			WIN_ASSERT_STRING_EQUAL(value.second.lang.c_str(), itr->second.lang.c_str());	\
		}	\
		for(size_t i2=0; i2 < Expected.count; ++i2){	\
			const auto& value = Expected.list[i2];	\
			WIN_TRACE(_T("    [%s]:'%s'\n"), value.first.c_str(), value.second.name.c_str());	\
			const HostInfo* pHostInfo = Actual[value.first];	\
			WIN_ASSERT_NOT_NULL(pHostInfo);	\
			WIN_ASSERT_STRING_EQUAL(value.second.name.c_str(), pHostInfo->name.c_str());	\
			WIN_ASSERT_STRING_EQUAL(value.second.url.c_str(), pHostInfo->url.c_str());	\
			WIN_ASSERT_STRING_EQUAL(value.second.lang.c_str(), pHostInfo->lang.c_str());	\
		}	\
	}	\

struct HostInfo {
	wstring	name;
	wstring	url;
	wstring	lang;

	HostInfo(wstring Name=L"", wstring Url=L"", wstring Lang=L""):
		name(Name), url(Url), lang(Lang)
	{}
};

typedef AssociativeVector<wstring, HostInfo> HostMap;
//typedef AssociativeVector<const wstring, const HostInfo> constHostMap;

static const size_t ItemCount = 4;

static const HostMap::value_type rawList1[][ItemCount] = {
	{
		make_pair(L"G_en", HostInfo(L"グーグル", L"https://www.google.com/", L"English")),
		make_pair(L"G_ja", HostInfo(L"グーグル", L"https://www.google.co.jp/", L"Japanese")),
		make_pair(L"Y_en", HostInfo(L"ヤフー！", L"https://www.yahoo.com/", L"English")),
		make_pair(L"Y_ja", HostInfo(L"ヤフー！", L"https://www.yahoo.co.jp/", L"Japanese")),
	},
	{
		make_pair(L"Y_ja", HostInfo(L"ヤフー！", L"https://www.yahoo.co.jp/", L"Japanese")),
		make_pair(L"Y_en", HostInfo(L"ヤフー！", L"https://www.yahoo.com/", L"English")),
		make_pair(L"G_ja", HostInfo(L"グーグル", L"https://www.google.co.jp/", L"Japanese")),
		make_pair(L"G_en", HostInfo(L"グーグル", L"https://www.google.com/", L"English")),
	},
};

/*
static const constHostMap::value_type rawList2[][ItemCount] = {
	{
		make_pair(L"G_en", HostInfo(L"グーグル", L"https://www.google.com/", L"English")),
		make_pair(L"G_ja", HostInfo(L"グーグル", L"https://www.google.co.jp/", L"Japanese")),
		make_pair(L"Y_en", HostInfo(L"ヤフー！", L"https://www.yahoo.com/", L"English")),
		make_pair(L"Y_ja", HostInfo(L"ヤフー！", L"https://www.yahoo.co.jp/", L"Japanese")),
	},
	{
		make_pair(L"Y_ja", HostInfo(L"ヤフー！", L"https://www.yahoo.co.jp/", L"Japanese")),
		make_pair(L"Y_en", HostInfo(L"ヤフー！", L"https://www.yahoo.com/", L"English")),
		make_pair(L"G_ja", HostInfo(L"グーグル", L"https://www.google.co.jp/", L"Japanese")),
		make_pair(L"G_en", HostInfo(L"グーグル", L"https://www.google.com/", L"English")),
	},
};
*/

struct TestCaseNotConst {
	wstring						name;
	const HostMap::value_type*	list;
	size_t						count;
};

/*
struct TestCaseConst {
	wstring							name;
	const constHostMap::value_type*	list;
	size_t							count;
};
*/

static TestCaseNotConst testCases1[] = {
	{ L"Ascending", rawList1[0], ItemCount },
	{ L"Descending", rawList1[1], ItemCount },
};

/*
static TestCaseConst testCases2[] = {
	{ L"Ascending", rawList2[0], ItemCount },
	{ L"Descending", rawList2[1], ItemCount },
};
*/

BEGIN_TEST(AssociativeVector_01_DefaultConstructor)
{
	TestCaseNotConst expected = {
		L"NULL", NULL, 0
	};
	WIN_TRACE(
		_T("AssociativeVector: DefaultConstructor -> ")
		_T("size:%d\n"),
		expected.count
	);
	HostMap hostMap;
	WIN_ASSERT_ZERO(hostMap.size());
}
END_TEST

BEGIN_TEST(AssociativeVector_02_ConstructFromArray_NotConst)
{
	for(size_t index=0; index < _countof(testCases1); ++index){
		TestCaseNotConst expected = testCases1[index];
		WIN_TRACE(
			_T("%d: %s\n"),
			index, expected.name.c_str()
		);
		WIN_TRACE(_T("  AssociativeVector(*First, *Last)\n"));
		const HostMap tested1(expected.list, expected.list + expected.count);
		assertAssociativeVector(testCases1[0], tested1);
		WIN_TRACE(_T("  AssociativeVector(Array[])\n"));
		const HostMap tested2(rawList1[index]);
		assertAssociativeVector(testCases1[0], tested2);
	}
}
END_TEST

/*
BEGIN_TEST(AssociativeVector_03_ConstructFromArray_Const)
{
	for(size_t index=0; index < _countof(testCases2); ++index){
		TestCaseConst expected = testCases2[index];
		WIN_TRACE(
			_T("%d: %s\n"),
			index, expected.name.c_str()
		);
		WIN_TRACE(_T("  AssociativeVector(*First, *Last)\n"));
		const constHostMap tested1(expected.list, expected.list + expected.count);
		assertAssociativeVector(testCases2[0], tested1);
		WIN_TRACE(_T("  AssociativeVector(Array[])\n"));
		const constHostMap tested2(rawList2[index]);
		assertAssociativeVector(testCases2[0], tested2);
	}
}
END_TEST
*/

// EOF
