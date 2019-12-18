#include <windows.h>

/*
 ВАр 25

 После нажатия на правую клавишу мыши над рабочей областью окна
 в правом нижнем углу области отобразить временное окно размером в четверть области.
 Временное окно скрыть после отпускания клавиши в любом месте экрана

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

// функция вхождений программы WinMain
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpCmdLine,
                     int nCmdShow) {

    LPCTSTR lpzMainClass = TEXT("Main Window Class");
    lpzChildClass = TEXT("Child Window Class");

    // регистрация класса главного окна
    if (!RegMainWindowClass(hInstance, lpzMainClass))
        return 1;

    // регистрация класса дочернего окна
    if (!RegChildWindowClass(hInstance, lpzChildClass))
        return 1;


    // создание диалогового окна
    HWND hWnd = CreateWindow(lpzMainClass, TEXT("Dialog Window"),
                             WS_OVERLAPPEDWINDOW | WS_VISIBLE, defaultWindowXPost, defaultWindowYPost,
                             defaultWindowLength, defaultWindowHeight, NULL, NULL, hInstance, NULL);

    // если окно не создано, описатель будет равен 0
    if (!hWnd) return 2;


    return ProcessWinMsg();
}

int ProcessWinMsg() {
    // цикл сообщений приложения
    MSG msg = {0};    // структура сообщения
    int iGetOk = 0;   // переменная состояния
    while ((iGetOk = GetMessage(&msg, NULL, 0, 0)) != 0) // цикл сообщений
    {
        if (iGetOk == -1) return 3;  // если GetMessage вернул ошибку - выход
        TranslateMessage(&msg); // переводит сообщения формата виртуальных клавиш в сообщения символы.
        DispatchMessage(&msg); // пересылает сообщение оконной процедуре.
    }

    return msg.wParam;  // возвращаем код завершения программы
}

// функция регистрации класса главного окна
ATOM RegMainWindowClass(HINSTANCE hInst, LPCTSTR lpzClassName) {
    WNDCLASS wcWindowClass = {0};
    // адрес ф-ции обработки сообщений
    wcWindowClass.lpfnWndProc = (WNDPROC) MainWndProcessor;
    // стиль окна
    wcWindowClass.style = CS_HREDRAW | CS_VREDRAW;
    // дискриптор экземпляра приложения
    wcWindowClass.hInstance = hInst;
    // название класса
    wcWindowClass.lpszClassName = lpzClassName;
    // загрузка курсора
    wcWindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    // загрузка цвета окон
    wcWindowClass.hbrBackground = (HBRUSH) COLOR_APPWORKSPACE;
    return RegisterClass(&wcWindowClass); // регистрация класса
}

// функция регистрации класса дочернего окна
ATOM RegChildWindowClass(HINSTANCE hInst, LPCTSTR lpzClassName) {
    WNDCLASS wcWindowClass = {0};
    // адрес ф-ции обработки сообщений
    wcWindowClass.lpfnWndProc = (WNDPROC) ChildWndProcessor;
    // стиль окна
    wcWindowClass.style = CS_HREDRAW | CS_VREDRAW;
    // дискриптор экземпляра приложения
    wcWindowClass.hInstance = hInst;
    // название класса
    wcWindowClass.lpszClassName = lpzClassName;
    // загрузка курсора
    wcWindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    // загрузка цвета окон
    wcWindowClass.hbrBackground = (HBRUSH) COLOR_APPWORKSPACE;
    return RegisterClass(&wcWindowClass); // регистрация класса
}

// функция обработки сообщений главного окна
LRESULT CALLBACK MainWndProcessor(
        HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    // выборка и обработка сообщений
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
        case WM_DESTROY: //  когда необходимо уничтожить приложение (главное окно закрыто)
            PostQuitMessage(0);
            break;
        default:
            // обработчик сообщений Windows
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// функция обработки сообщений дочернего окна
LRESULT CALLBACK ChildWndProcessor(
        HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    // выборка и обработка сообщений
    switch (message) {
        case WM_RBUTTONUP:
            DestroyChildWindow();
            break;
        default:
            // обработчик сообщений Windows
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void DestroyChildWindow() {
    DestroyWindow(childHWnd);
}

void CreateChildWindow(int childWindowXPos, int childWindowYPos, int childWLength, int childWHeight) {
    HINSTANCE hInstance =
            GetModuleHandle(NULL); // возвращает дискриптор указанного модуля, или дискриптор приложения если NULL
    // создание временного окна
    childHWnd = CreateWindow(lpzChildClass, TEXT("Temporary Window"),
                             WS_OVERLAPPEDWINDOW | WS_VISIBLE, childWindowXPos, childWindowYPos,
                             childWLength, childWHeight, NULL, NULL, hInstance, NULL);
}