#include <windows.h>

/*
 ��� 25

 ����� ������� �� ������ ������� ���� ��� ������� �������� ����
 � ������ ������ ���� ������� ���������� ��������� ���� �������� � �������� �������.
 ��������� ���� ������ ����� ���������� ������� � ����� ����� ������

 */

const int defaultWindowXPost = 480;
const int defaultWindowYPost = 220;

const int defaultWindowHeight = 350;
const int defaultWindowLength = 600;

LPCTSTR lpzChildClass;
HWND childHWnd;


LRESULT CALLBACK MainWndProcessor(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK ChildWndProcessor(HWND, UINT, WPARAM, LPARAM);

ATOM RegMainWindowClass(HINSTANCE, LPCTSTR);

ATOM RegChildWindowClass(HINSTANCE, LPCTSTR);

int ProcessWinMsg();

void CreateChildWindow(int childWindowXPos, int childWindowYPos, int childWLength, int childWHeight);

void DestroyChildWindow();

// ������� ��������� ��������� WinMain
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpCmdLine,
                     int nCmdShow) {

    LPCTSTR lpzMainClass = TEXT("Main Window Class");
    lpzChildClass = TEXT("Child Window Class");

    // ����������� ������ �������� ����
    if (!RegMainWindowClass(hInstance, lpzMainClass))
        return 1;

    // ����������� ������ ��������� ����
    if (!RegChildWindowClass(hInstance, lpzChildClass))
        return 1;


    // �������� ����������� ����
    HWND hWnd = CreateWindow(lpzMainClass, TEXT("Dialog Window"),
                             WS_OVERLAPPEDWINDOW | WS_VISIBLE, defaultWindowXPost, defaultWindowYPost,
                             defaultWindowLength, defaultWindowHeight, NULL, NULL, hInstance, NULL);

    // ���� ���� �� �������, ��������� ����� ����� 0
    if (!hWnd) return 2;


    return ProcessWinMsg();
}

int ProcessWinMsg() {
    // ���� ��������� ����������
    MSG msg = {0};    // ��������� ���������
    int iGetOk = 0;   // ���������� ���������
    while ((iGetOk = GetMessage(&msg, NULL, 0, 0)) != 0) // ���� ���������
    {
        if (iGetOk == -1) return 3;  // ���� GetMessage ������ ������ - �����
        TranslateMessage(&msg); // ��������� ��������� ������� ����������� ������ � ��������� �������.
        DispatchMessage(&msg); // ���������� ��������� ������� ���������.
    }

    return msg.wParam;  // ���������� ��� ���������� ���������
}

// ������� ����������� ������ �������� ����
ATOM RegMainWindowClass(HINSTANCE hInst, LPCTSTR lpzClassName) {
    WNDCLASS wcWindowClass = {0};
    // ����� �-��� ��������� ���������
    wcWindowClass.lpfnWndProc = (WNDPROC) MainWndProcessor;
    // ����� ����
    wcWindowClass.style = CS_HREDRAW | CS_VREDRAW;
    // ���������� ���������� ����������
    wcWindowClass.hInstance = hInst;
    // �������� ������
    wcWindowClass.lpszClassName = lpzClassName;
    // �������� �������
    wcWindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    // �������� ����� ����
    wcWindowClass.hbrBackground = (HBRUSH) COLOR_APPWORKSPACE;
    return RegisterClass(&wcWindowClass); // ����������� ������
}

// ������� ����������� ������ ��������� ����
ATOM RegChildWindowClass(HINSTANCE hInst, LPCTSTR lpzClassName) {
    WNDCLASS wcWindowClass = {0};
    // ����� �-��� ��������� ���������
    wcWindowClass.lpfnWndProc = (WNDPROC) ChildWndProcessor;
    // ����� ����
    wcWindowClass.style = CS_HREDRAW | CS_VREDRAW;
    // ���������� ���������� ����������
    wcWindowClass.hInstance = hInst;
    // �������� ������
    wcWindowClass.lpszClassName = lpzClassName;
    // �������� �������
    wcWindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    // �������� ����� ����
    wcWindowClass.hbrBackground = (HBRUSH) COLOR_APPWORKSPACE;
    return RegisterClass(&wcWindowClass); // ����������� ������
}

// ������� ��������� ��������� �������� ����
LRESULT CALLBACK MainWndProcessor(
        HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    // ������� � ��������� ���������
    switch (message) {
        case WM_RBUTTONDOWN:
            RECT mainWndRect;
            if (GetWindowRect(hWnd, &mainWndRect)) {
                int mainWndHeight = mainWndRect.bottom - mainWndRect.top;
                int mainWndWidth = mainWndRect.right - mainWndRect.left;

                int childWndHeight = mainWndWidth / 2;
                int childWndWidth = mainWndHeight / 2;

                int childWindowXPos = mainWndRect.left + childWndHeight;
                int childWindowYPos = mainWndRect.top + childWndWidth;
                CreateChildWindow(childWindowXPos, childWindowYPos, childWndHeight, childWndWidth);
            }
            break;
        case WM_RBUTTONUP:
            DestroyChildWindow();
            break;
        case WM_DESTROY: //  ����� ���������� ���������� ���������� (������� ���� �������)
            PostQuitMessage(0);
            break;
        default:
            // ���������� ��������� Windows
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// ������� ��������� ��������� ��������� ����
LRESULT CALLBACK ChildWndProcessor(
        HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    // ������� � ��������� ���������
    switch (message) {
        case WM_RBUTTONUP:
            DestroyChildWindow();
            break;
        default:
            // ���������� ��������� Windows
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void DestroyChildWindow() {
    DestroyWindow(childHWnd);
}

void CreateChildWindow(int childWindowXPos, int childWindowYPos, int childWLength, int childWHeight) {
    HINSTANCE hInstance =
            GetModuleHandle(NULL); // ���������� ���������� ���������� ������, ��� ���������� ���������� ���� NULL
    // �������� ���������� ����
    childHWnd = CreateWindow(lpzChildClass, TEXT("Temporary Window"),
                             WS_OVERLAPPEDWINDOW | WS_VISIBLE, childWindowXPos, childWindowYPos,
                             childWLength, childWHeight, NULL, NULL, hInstance, NULL);
}