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
void Run()
{
	SetConsoleOutputCP(CP_UTF8);
	EnumWindows(EnumFunction, NULL);
	printf("%x", hNotepad);
}




LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_DESTROY:
        PostQuitMessage(0);  // 发送退出消息
        return 0;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // 注册窗口类
    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"TestWindow";
    RegisterClass(&wc);

    // 创建窗口
    HWND hwnd = CreateWindow(
        L"TestWindow", L"我的窗口",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 2560  ,1600,
        NULL, NULL, hInstance, NULL
    );

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // 消息循环：窗口保持不消失的关键
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}