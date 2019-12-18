#include <iostream>
#include <windows.h>
#include <string>
#include <cstdio>
#include <fstream>


using namespace std;

/*
 * ��� 23
 ������������ ������ ���� � ������� ���� ������� ������ � ���������� ����.
 � ������ ������ ������ �������� ���� ������, �� ������ ������ - �����.
 ��� ������ ������ ������ ���� ������ �������� � ������������ � ����������� ���� � ������.
 ��� ������� ������ "���������" ���� ������������ � ���� dates.txt � ������� DD/MM/YYYY.
 ���� ��� ������ �����������, �� � ���� ���� ������ ���������� ����� "������!"
 */

const int ERR_CANT_CREATE_WINDOW = 10;
const int ERR_CANT_CREATE_FILE = 11;

const int DEFAULT_WINDOW_HEIGHT = 200;
const int DEFAULT_WINDOW_LENGTH = 300;

const int DEFAULT_VIEW_X_POST = 10;
const int DEFAULT_VIEW_LENGTH = DEFAULT_WINDOW_LENGTH - 25;
const int DEFAULT_VIEW_HEIGHT = 22;


const TCHAR MONTHS[12][10] = {
        TEXT("������"), TEXT("�������"), TEXT("����"), TEXT("������"),
        TEXT("���"), TEXT("����"), TEXT("����"), TEXT("������"),
        TEXT("��������"), TEXT("�������"), TEXT("������"), TEXT("�������")
};


const int DAY_COMBO_ID = 3002;
const int MONTH_COMBO_ID = 3003;
const int YEAR_EDIT_ID = 3004;
const int SAVE_BTN_ID = 3001;


HWND hSaveButton;
HWND hDayList;
HWND hMonthList;
HWND hYearEditText;

LRESULT CALLBACK MainWndProcessor(HWND, UINT, WPARAM, LPARAM);

ATOM RegMainWindowClass(HINSTANCE, LPCTSTR);

int ProcessWinMsg();


int initDaySelector(HWND hWnd, HINSTANCE hInstance);

int initMonthSelector(HWND hWnd, HINSTANCE hInstance);

int initYearSelector(HWND hWnd, HINSTANCE hInstance);

void initSaveButton(HWND hWnd, HINSTANCE hInstance);

void getDate();

int saveToFile(char dateString[11]);

void fillDayList(int daysN, int selectIndex);

// ������� ��������� ��������� WinMain
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpCmdLine,
                     int nCmdShow) {

    LPCTSTR lpzMainClass = TEXT("Main Window Class");

    // ����������� ������ �������� ����
    if (!RegMainWindowClass(hInstance, lpzMainClass))
        return 1;


    // ���������� ��������� ������ ������
    RECT screen_rect;
    GetWindowRect(GetDesktopWindow(), &screen_rect); // ���������� ������
    int windowXPos = screen_rect.right / 2 - DEFAULT_WINDOW_LENGTH / 2;
    int windowYPos = screen_rect.bottom / 2 - DEFAULT_WINDOW_HEIGHT / 2;

    // �������� ����������� ����
    HWND hWnd = CreateWindow(lpzMainClass, TEXT("Date Selector (v.23)"),
                             WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE, windowXPos, windowYPos,
                             DEFAULT_WINDOW_LENGTH, DEFAULT_WINDOW_HEIGHT, NULL, NULL, hInstance, NULL);

    // ���� ���� �� �������, ��������� ����� ����� 0
    if (!hWnd) return ERR_CANT_CREATE_WINDOW;


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

// ������� ��������� ��������� �������� ����
LRESULT CALLBACK MainWndProcessor(
        HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    // ������� � ��������� ���������
    HINSTANCE hInstance;
    switch (message) {
        case WM_CREATE:
            hInstance = GetModuleHandle(NULL);

            initDaySelector(hWnd, hInstance);
            initMonthSelector(hWnd, hInstance);
            initYearSelector(hWnd, hInstance);
            initSaveButton(hWnd, hInstance);

            break;
        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case SAVE_BTN_ID:
                    getDate();

                    break;
                case MONTH_COMBO_ID:
                    if (HIWORD(wParam) == CBN_SELCHANGE) {
                        int dayIndex = SendMessage(hDayList, CB_GETCURSEL, 0, 0);
                        int month = SendMessage(hMonthList, CB_GETCURSEL, 0, 0) + 1;
                        SendMessage(hDayList, CB_RESETCONTENT, 0, 0);

                        //https://tproger.ru/problems/days-in-month-formula/
                        int daysN = 28 + (month + month / 8) % 2 + 2 % month + 1 / month * 2;
                        if (dayIndex + 1 > daysN) {
                            dayIndex = daysN - 1;
                        }
                        //printf("days: %d dayIndex: %d\n", daysN, dayIndex);
                        fillDayList(daysN, dayIndex);
                    }
                    break;
            }
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


void getDate() {
    int dayComboIndex = SendMessage(hDayList, CB_GETCURSEL, 0, 0);
    int monthComboIndex = SendMessage(hMonthList, CB_GETCURSEL, 0, 0);


    char yearBuff[1024];
    GetWindowText(hYearEditText, yearBuff, 1024);
    int year = atoi(yearBuff);

    if (year == 0 || year > 9999 || year < 0) {
        SetWindowText(hYearEditText, "Incorrect year!");
        return;
    } else {
        //printf("year: %d\n" + year);
        char backYearBuff[5] = "";
        sprintf(backYearBuff, "%d", year);
        SetWindowText(hYearEditText, backYearBuff);
    }

    char dateString[11];
    sprintf(dateString, "%02d.%02d.%04d", dayComboIndex + 1, monthComboIndex + 1, year);
    saveToFile(dateString);
}

int saveToFile(char dateString[11]) {
    printf("saving... %s\n", dateString);
    ofstream resultFile;
    resultFile.open("result.txt");
    if (!resultFile.is_open()) {
        printf("Cannot create the database file!\n");
        return ERR_CANT_CREATE_FILE;
    }
    resultFile << dateString;
    resultFile.close();
}


int initDaySelector(HWND hWnd, HINSTANCE hInstance) {
    HWND text = CreateWindow(TEXT("static"), TEXT("Day:"), WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                             DEFAULT_VIEW_X_POST, 10,
                             DEFAULT_VIEW_LENGTH / 4, 25,
                             hWnd, NULL, hInstance, NULL);
    if (!text) {
        return ERR_CANT_CREATE_WINDOW;
    }
    hDayList = CreateWindow(TEXT("COMBOBOX"), TEXT(""),
                            WS_VISIBLE | WS_CHILD | CBS_DROPDOWN | CBS_HASSTRINGS | WS_VSCROLL,
                            DEFAULT_VIEW_X_POST + DEFAULT_VIEW_LENGTH / 4 + 10, 10,
                            DEFAULT_VIEW_LENGTH - DEFAULT_VIEW_X_POST - DEFAULT_VIEW_LENGTH / 4,
                            DEFAULT_WINDOW_HEIGHT * 1.5,
                            hWnd, (HMENU) DAY_COMBO_ID, hInstance, NULL);
    if (!hDayList) {
        return ERR_CANT_CREATE_WINDOW;
    }

    fillDayList(31, 0);
}

void fillDayList(int daysN, int selectIndex) {
    char buffer[3];
    for (int i = 1; i <= daysN; i++) {
        sprintf(buffer, "%d", i);
        SendMessage(hDayList, CB_ADDSTRING, 0, (LPARAM) buffer);
    }
    SendMessage(hDayList, CB_SETCURSEL, selectIndex, 0);
}

int initMonthSelector(HWND hWnd, HINSTANCE hInstance) {
    HWND text = CreateWindow(TEXT("static"), TEXT("Month:"), WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                             DEFAULT_VIEW_X_POST, 20 + DEFAULT_VIEW_HEIGHT,
                             DEFAULT_VIEW_LENGTH / 4, 25,
                             hWnd, NULL, hInstance, NULL);
    if (!text) {
        return ERR_CANT_CREATE_WINDOW;
    }
    hMonthList = CreateWindow(TEXT("COMBOBOX"), TEXT(""),
                              WS_VISIBLE | WS_CHILD | CBS_DROPDOWN | CBS_HASSTRINGS | WS_VSCROLL,
                              DEFAULT_VIEW_X_POST + DEFAULT_VIEW_LENGTH / 4 + 10, 20 + DEFAULT_VIEW_HEIGHT,
                              DEFAULT_VIEW_LENGTH - DEFAULT_VIEW_X_POST - DEFAULT_VIEW_LENGTH / 4,
                              DEFAULT_WINDOW_HEIGHT * 1.5,
                              hWnd, (HMENU) MONTH_COMBO_ID, hInstance, NULL);
    if (!hMonthList) {
        return ERR_CANT_CREATE_WINDOW;
    }
    for (int i = 0; i < 12; i++) {
        SendMessage(hMonthList, CB_ADDSTRING, 0, (LPARAM) MONTHS[i]);
    }
    SendMessage(hMonthList, CB_SETCURSEL, 0, 0);
}

int initYearSelector(HWND hWnd, HINSTANCE hInstance) {
    HWND text = CreateWindow(TEXT("static"), TEXT("Year:"), WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                             DEFAULT_VIEW_X_POST, 30 + DEFAULT_VIEW_HEIGHT * 2,
                             DEFAULT_VIEW_LENGTH / 4, 25,
                             hWnd, NULL, hInstance, NULL);
    if (!text) {
        return ERR_CANT_CREATE_WINDOW;
    }
    hYearEditText = CreateWindow(TEXT("edit"), TEXT("2017"),
                                 WS_EX_CLIENTEDGE | WS_CHILD | WS_VISIBLE | WS_BORDER,
                                 DEFAULT_VIEW_X_POST + DEFAULT_VIEW_LENGTH / 4 + 10, 30 + DEFAULT_VIEW_HEIGHT * 2,
                                 DEFAULT_VIEW_LENGTH - DEFAULT_VIEW_X_POST - DEFAULT_VIEW_LENGTH / 4,
                                 DEFAULT_VIEW_HEIGHT,
                                 hWnd, (HMENU) YEAR_EDIT_ID, hInstance, NULL);
    if (!hYearEditText) {
        return ERR_CANT_CREATE_WINDOW;
    }
}

void initSaveButton(HWND hWnd, HINSTANCE hInstance) {
    hSaveButton = CreateWindow(TEXT("button"), TEXT("Save"), WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
                               DEFAULT_VIEW_X_POST, DEFAULT_WINDOW_HEIGHT - 60,
                               DEFAULT_VIEW_LENGTH, DEFAULT_VIEW_HEIGHT,
                               hWnd, (HMENU) SAVE_BTN_ID, hInstance, NULL);
}
