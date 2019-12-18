#include <windows.h>
#include <cstdio>

/*
 ВАр 25

 После нажатия на правую клавишу мыши над рабочей областью окна
 в правом нижнем углу области отобразить временное окно размером в четверть области.
 Временное окно скрыть после отпускания клавиши в любом месте экрана

 */

const int defaultWindowXPost = 480;
const int defaultWindowYPost = 60;

const int defaultWindowHeight = 600;
const int defaultWindowLength = 350;

const COLORREF OFF_LIGHT_COLOR = RGB(200, 200, 200);

const COLORREF RED_LIGHT_BORDER_COLOR = RGB(200, 0, 0);
const COLORREF RED_LIGHT_COLOR = RGB(255, 0, 0);

const COLORREF YELLOW_LIGHT_BORDER_COLOR = RGB(170, 175, 0);
const COLORREF YELLOW_LIGHT_COLOR = RGB(252, 255, 50);

const COLORREF GREEN_LIGHT_BORDER_COLOR = RGB(0, 190, 0);
const COLORREF GREEN_LIGHT_COLOR = RGB(0, 255, 0);

const int LIGHT_RADIUS = 70;

const int LIGHTS_BOTTOM_PADDING = 20;

const int RED_LIGHT_X = 105;
const int RED_LIGHT_Y = 50;

const int YELLOW_LIGHT_X = 105;
const int YELLOW_LIGHT_Y = RED_LIGHT_Y + 2 * LIGHT_RADIUS + LIGHTS_BOTTOM_PADDING;

const int GREEN_LIGHT_X = 105;
const int GREEN_LIGHT_Y = YELLOW_LIGHT_Y + 2 * LIGHT_RADIUS + LIGHTS_BOTTOM_PADDING;

/*
 RED: 1
 YELLOW: 2
 GREEN: 3
 */
int color = 3;

LRESULT CALLBACK MainWndProcessor(HWND, UINT, WPARAM, LPARAM);

ATOM RegMainWindowClass(HINSTANCE, LPCTSTR);

int ProcessWinMsg();

void redrawLight(HWND hWnd, COLORREF borderColor, COLORREF color, int ax, int ay, int bx, int by) {
    HDC hdc = GetDC(hWnd);

    HPEN hPen = CreatePen(PS_SOLID, 5, borderColor);
    HBRUSH hBrush = CreateSolidBrush(color);

    SelectObject(hdc, hPen);
    SelectObject(hdc, hBrush);
    Ellipse(hdc, ax, ay, bx, by);

    DeleteObject(hPen);
    DeleteObject(hBrush);

    GetStockObject(DC_PEN);
    GetStockObject(WHITE_BRUSH);

    ReleaseDC(hWnd, hdc);
}

void redrawRedLight(HWND hWnd, boolean isOn) {
    COLORREF color = isOn ? RED_LIGHT_COLOR : OFF_LIGHT_COLOR;
    redrawLight(hWnd, RED_LIGHT_BORDER_COLOR, color, RED_LIGHT_X, RED_LIGHT_Y, RED_LIGHT_X + LIGHT_RADIUS * 2,
                RED_LIGHT_Y + LIGHT_RADIUS * 2);
}

void redrawYellowLight(HWND hWnd, boolean isOn) {
    COLORREF color = isOn ? YELLOW_LIGHT_COLOR : OFF_LIGHT_COLOR;
    redrawLight(hWnd, YELLOW_LIGHT_BORDER_COLOR, color, YELLOW_LIGHT_X, YELLOW_LIGHT_Y,
                YELLOW_LIGHT_X + LIGHT_RADIUS * 2,
                YELLOW_LIGHT_Y + LIGHT_RADIUS * 2);
}

void redrawGreenLight(HWND hWnd, boolean isOn) {
    COLORREF color = isOn ? GREEN_LIGHT_COLOR : OFF_LIGHT_COLOR;
    redrawLight(hWnd, GREEN_LIGHT_BORDER_COLOR, color, GREEN_LIGHT_X, GREEN_LIGHT_Y,
                GREEN_LIGHT_X + LIGHT_RADIUS * 2,
                GREEN_LIGHT_Y + LIGHT_RADIUS * 2);
}

// функция вхождений программы WinMain
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpCmdLine,
                     int nCmdShow) {

    LPCTSTR lpzMainClass = TEXT("Main Window Class");

    // регистрация класса главного окна
    if (!RegMainWindowClass(hInstance, lpzMainClass))
        return 1;

    // создание диалогового окна
    HWND hWnd = CreateWindow(lpzMainClass, TEXT("Road Light"),
                             WS_CAPTION|WS_SYSMENU|WS_VISIBLE|WS_MINIMIZEBOX, defaultWindowXPost, defaultWindowYPost,
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


// функция обработки сообщений главного окна
LRESULT CALLBACK MainWndProcessor(
        HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

    // выборка и обработка сообщений
    switch (message) {
        case WM_PAINT:
            switch (color) {
                case 1:
                    redrawRedLight(hWnd, TRUE);
                    redrawYellowLight(hWnd, FALSE);
                    redrawGreenLight(hWnd, FALSE);
                    break;
                case 2:
                    redrawRedLight(hWnd, FALSE);
                    redrawYellowLight(hWnd, TRUE);
                    redrawGreenLight(hWnd, FALSE);
                    break;
                case 3:
                    redrawRedLight(hWnd, FALSE);
                    redrawYellowLight(hWnd, FALSE);
                    redrawGreenLight(hWnd, TRUE);
                    break;
            }
            break;
        case WM_LBUTTONUP:
            POINT p;
            GetCursorPos(&p);
            ScreenToClient(hWnd, &p);
            if (p.x > RED_LIGHT_X && p.x < RED_LIGHT_X + 2 * LIGHT_RADIUS) {
                const int d = 2 * LIGHT_RADIUS;
                const int y = p.y;

                if (y > RED_LIGHT_Y && y < RED_LIGHT_Y + d) {
                    color = 1;
                } else if (y > YELLOW_LIGHT_Y && y < YELLOW_LIGHT_Y + d) {
                    color = 2;
                } else if (y > GREEN_LIGHT_Y && y < GREEN_LIGHT_Y + d) {
                    color = 3;
                }
                UpdateWindow(hWnd);
            }


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