// SebBinLoader.cpp

#include <iostream>
#include <Windows.h>
#include <map>
#include <vector>
#pragma comment(lib, "comsuppw.lib")
#include <comutil.h>

std::map<std::string, std::string> socials = {
	{"Github", "https://github.com/pinkestflamingo"},
	{"Discord", "@luau_load"}
};

std::vector<std::string> seb_logo = {
" ____       _     ____  _       ",
"/ ___|  ___| |__ | __ )(_)_ __  ",
"\\___ \\ / _ \\ '_ \\|  _ \\| | '_ \\ ",
" ___) |  __/ |_) | |_) | | | | |",
"|____/ \\___|_.__/|____/|_|_| |_|"
};

/*
	You might need to modify these if SEB makes changes to their DLL in the future.
	These are based on the current version of SEB (10.x) as of 2025-09-30.
*/
typedef BSTR(__cdecl* CalculateAppSignatureKey_t)(BSTR connectionToken, BSTR salt);
typedef BSTR(__cdecl* CalculateBrowserExamKey_t)(BSTR configurationKey, BSTR salt);
typedef BOOL(__cdecl* VerifyCodeSignature_t)();


int main()
{
	SetConsoleTitleA("SebBinLoader v1.0");
	printf("Welcome to SebBinLoader v1.0 developed by Flamingo.\nYou can find my socials down below if you need to contact me regarding research or anything else.\n");
	for(auto const pair : socials) {
		printf("[%s]\t: %s\n", pair.first.c_str(), pair.second.c_str());
	}
	for(auto const line : seb_logo) {
		printf("%s\n", line.c_str());
		Sleep(100);
	}
	printf("Loading seb_x64.dll...\n");
	HMODULE seb_x64 = LoadLibraryA("seb_x64.dll");
    if(!seb_x64) {
		printf("Failed to load seb_x64.dll. Error code: %lu\n", GetLastError());
		return 1;
	}
	printf("Successfully loaded seb_x64.dll at address: %p\n", seb_x64);

	auto CalculateAppSignatureKey	= (CalculateAppSignatureKey_t)GetProcAddress(seb_x64, "CalculateAppSignatureKey");
	auto CalculateBrowserExamKey	= (CalculateBrowserExamKey_t)GetProcAddress(seb_x64, "CalculateBrowserExamKey");
	auto VerifyCodeSignature		= (VerifyCodeSignature_t)GetProcAddress(seb_x64, "VerifyCodeSignature");

	if (!CalculateAppSignatureKey || !CalculateBrowserExamKey || !VerifyCodeSignature) {
		std::cerr << "Failed to resolve one or more functions" << std::endl;
		FreeLibrary(seb_x64);
		return 1;
	}
	printf("-------------------------------------------------\n");
	printf("CalculateAppSignatureKey\t: %p\n", CalculateAppSignatureKey);
	printf("CalculateBrowserExamKey\t\t: %p\n", CalculateBrowserExamKey);
	printf("VerifyCodeSignature\t\t: %p\n", VerifyCodeSignature);
	printf("-------------------------------------------------\n");

	BSTR connectionToken	= SysAllocString(L"myToken");
	BSTR salt				= SysAllocString(L"mySalt");
	printf("Using ConnectionToken:\t%ws\n", connectionToken);
	printf("Using Salt:\t\t%ws\n", salt);
	printf("-------------------------------------------------\n");

	BOOL verified = VerifyCodeSignature();
	std::wcout << L"Code Signature Verified: " << (verified ? L"true" : L"false") << std::endl;

	BSTR appKey = CalculateAppSignatureKey(connectionToken, salt);
	if (appKey) {
		_bstr_t keyWrapper(appKey, false); // takes ownership and auto-frees
		std::wcout << L"AppSignatureKey: " << (wchar_t*)keyWrapper << std::endl;
	}

	BSTR browserKey = CalculateBrowserExamKey(connectionToken, salt);
	if (browserKey) {
		_bstr_t keyWrapper(browserKey, false);
		std::wcout << L"BrowserExamKey: " << (wchar_t*)keyWrapper << std::endl;
	}


	/* Clean up as the good guys we are :) */
	SysFreeString(connectionToken);
	SysFreeString(salt);

	FreeLibrary(seb_x64);
}
