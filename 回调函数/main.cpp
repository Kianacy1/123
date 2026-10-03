#include<windows.h>
#include<string.h>
#include<stdio.h>
HWND hNotepad = NULL;
BOOL CALLBACK EnumFunction(HWND hWnd, LPARAM lParam)
{
	WCHAR strTitle[255];
	GetWindowText(hWnd, strTitle, 255);
	if (lstrcmpW(strTitle, L"NOTE.txt - Notepad")==0)
	{
		hNotepad = hWnd;
		return FALSE;
	}
	else {
		return TRUE;
	}

}

BOOL CALLBACK DebugEnum(HWND hWnd, LPARAM lParam)
{
	char strTitle[255];
	GetWindowTextA(hWnd, strTitle, 255);  // 使用 ANSI 版本
	if (strlen(strTitle) > 0)
		printf("窗口: %s\n", strTitle);
	return TRUE;
}

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	EnumWindows(EnumFunction, NULL);
	printf("%x", hNotepad);
	
}