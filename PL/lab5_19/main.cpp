#include <Windows.h>
#include <fstream>
#include <vector>
#include <iostream>
#include "resource.h"

/*
 * ��������� ���� - win1251
 * ������ ���� ����������/�������������� � ����� DialogView.rc

 ����:
 - ��� ����� (������ 30 ��������);
 - ������ ����� (����� �����);
 - ���� �������� (� ������� ��.��.����);
 - ����� �������� (� ������� ��:��).

 ������ �����: ��� �����, ������ �����, ���� � ����� ��������.

 �� ������� ����� � ������� ��������,
 �� ������� ����� � ������� �����������,
 �� ���� �������� � ������� �����������,
 �� ���� �������� � ������� ��������.
 */

const int NULL_INDEX = -1;
static const std::string FILENAME = "../binary.bin";

HINSTANCE HI;
HWND mainWnd;
HWND listBox;


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

BOOL FileDlgProc(HWND, UINT, WPARAM, int);

BOOL CALLBACK DlgAddProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
    // ����� ������� ��������� ���� ��������� ��������
    // � �������� � �������� ������� �������� ���������� NULL_INDEX,
    // �� ������� �������� ����� �������, � �� ������������� �� ������

    // ����������� � ��������
    return FileDlgProc(hDlg, msg, wParam, NULL_INDEX);
}

BOOL CALLBACK DlgEditProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
    // ��������� �������� �� listbox, �� ������� ��������� ������
    int num = SendMessage(listBox, LB_GETCURSEL, 0, 0L);

    // ����� ������� ��������� ���� ��������� ��������
    // � �������� ������� �������� � ������, ��� �������� ��� �������

    // ����������� � ��������
    return FileDlgProc(hDlg, msg, wParam, num);
}


struct File {
    char file_name[31];
    unsigned long size; // ������
    int day; // ����
    int month; // �����
    int year; // ���
    int time_h; // ����
    int time_m; // ������
};

std::vector<File> files; // ������(������) �� ������� ������

void createMenu(HWND);

void sort(int);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrecInst, LPSTR lpCmdLine, int nCmdShow) {

    MSG msg;
    WNDCLASS a;
    LPCSTR MyW = "MainWindowClass";
    a.cbClsExtra = 0;
    a.cbWndExtra = 0;
    a.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
    a.hCursor = NULL;
    a.hIcon = NULL;
    a.hInstance = hInst;
    a.lpfnWndProc = WndProc;
    a.lpszClassName = MyW;
    a.lpszMenuName = NULL;
    a.style = (UINT) NULL;
    if (!RegisterClass(&a)) {
        MessageBox(NULL, "Error creating class for main window", "Error", MB_OK | MB_ICONERROR);
        return -1;
    }
    mainWnd = CreateWindow(MyW, "Tickets",
                           WS_VISIBLE | WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
                           CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInst, 0);
    if (!mainWnd) {
        MessageBox(NULL, "Error creating main window", "Error", MB_OK | MB_ICONERROR);
        return -1;
    }
    createMenu(mainWnd);
    ShowWindow(mainWnd, SW_SHOW);
    UpdateWindow(mainWnd);

    //HWND cap = CreateWindowEx(0, "static", "�������� ������ - ���� � ���� - ����� ��� - ����� �����", WS_CHILD | WS_DLGFRAME | ES_CENTER, 0, 0, 1010, 25, (HWND) mainWnd, NULL, hInst, 0);
    //ShowWindow(cap, SW_SHOW);
    //UpdateWindow(cap);

    // �������� listbox(������) � ����, ��� ����������� ������
    listBox = CreateWindowEx(0, "listbox", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY | WS_VSCROLL, 0, 0,
                             1020, 488, (HWND) mainWnd, NULL, hInst, 0);
    ShowWindow(listBox, SW_SHOW); // ����������� listbox
    UpdateWindow(listBox);

    files.clear(); // ������� ������ � �������

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}
// ������� �������������� ��������� "����" � ������
std::string fileToString(File f) {
    std::string line = "";
    line = line + "\"" + f.file_name + "\" - ";
    line = line + std::to_string(f.size) + "b ";
    line = line + std::to_string(f.day) + ".";
    line = line + std::to_string(f.month) + ".";
    line = line + std::to_string(f.year) + "   ";
    line = line + std::to_string(f.time_h) + ":";
    line = line + std::to_string(f.time_m);
    return line;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    File tmp;
    switch (msg) {
        case WM_CONTEXTMENU: {
            // �������� ��� ����
            HMENU contMenu = CreatePopupMenu();
            AppendMenu(contMenu, MFT_STRING, 1300, "&��������");

            UINT menuKeys = MFT_STRING;
            if (SendMessage(listBox, LB_GETCURSEL, 0, 0) == LB_ERR) {
                // nothing select
                menuKeys = MFT_STRING | MF_DISABLED;
            }
            AppendMenu(contMenu, menuKeys, 1301, "&��������");
            AppendMenu(contMenu, menuKeys, 1302, "&�������");

            TrackPopupMenu(contMenu, TPM_RIGHTBUTTON | TPM_TOPALIGN | TPM_LEFTALIGN, LOWORD(lParam), HIWORD(lParam), 0,
                           hwnd, NULL);
            DestroyMenu(contMenu);
            break;
        }
        case WM_COMMAND:
            switch (wParam) {
                // ��������� ����� ������ �� createMenu()

                case 1001: {
                    //������� ����
                    SendMessage(listBox, LB_RESETCONTENT, 0, 0);
                    files.clear(); // ������ ������

                    std::ifstream fileObj;
                    fileObj.open(FILENAME, std::ios::binary); // �������� ��������� �����
                    std::string line; // ���������� ��� ������ � �����
                    int counter = 0; // ������� �����
                    while (std::getline(fileObj, line)) counter++; // ������� ��-�� ����� � �����
                    counter /= 7; // ����������� ���-�� ������� � �����(7 ����� ��� ������ ��������� "����")
                    fileObj.clear();
                    fileObj.seekg(0); // ����������� �� ����� � ������
                    for (int i = 0; i < counter; i++) { // ���� ������ �������
                        line = "";

                        std::getline(fileObj, line); // ������ ����� �� ����� � line
                        strcpy_s(tmp.file_name, line.c_str()); // ��������� �������� � file_name

                        std::getline(fileObj, line);// ��������� ����� �� �����
                        tmp.size = strtoul(line.c_str(), NULL, 10); // ������ � unsigned long

                        std::getline(fileObj, line);
                        tmp.day = atoi(line.c_str()); // ������ � int

                        std::getline(fileObj, line);
                        tmp.month = atoi(line.c_str());

                        std::getline(fileObj, line);
                        tmp.year = atoi(line.c_str());

                        std::getline(fileObj, line);
                        tmp.time_h = atoi(line.c_str());

                        std::getline(fileObj, line);
                        tmp.time_m = atoi(line.c_str());

                        files.push_back(tmp); // ���������� ������-��� ����������� ��������� � ������ �������� files

                        // �������������� ��������� � ������ � ���������� ������ � listbox
                        SendMessageA(listBox, LB_ADDSTRING, 0, (LPARAM) fileToString(tmp).c_str());
                    }
                    fileObj.close(); // �������� �����

                    break;
                }
                case 1002: {
                    //��������� ������ � �������� ����
                    std::ofstream fileObj;
                    fileObj.open(FILENAME, std::ios::binary); // �������� �����
                    char str[256] = ""; // ��� ��������������� ����� � ������
                    for (int i = 0; i < files.size(); i++) { // ���� �� ���� ���������� ������
                        File nFile = files[i]; //������ ���������� ����� �� ������

                        fileObj << nFile.file_name << "\n"; // ������ � ���� ��� �����

                        // �������������� ������� �����(�����) � ������ �
                        // ������ ���� ������
                        fileObj << std::to_string(nFile.size).c_str() << "\n";

                        itoa(nFile.day, str, 10); // �������������� ���(�����) � ������
                        fileObj << str << "\n";  // ������ ���� ������
                        strcpy_s(str, ""); // ������� ������

                        itoa(nFile.month, str, 10);
                        fileObj << str << "\n";
                        strcpy_s(str, "");

                        itoa(nFile.year, str, 10);
                        fileObj << str << "\n";
                        strcpy_s(str, "");

                        itoa(nFile.time_h, str, 10);
                        fileObj << str << "\n";
                        strcpy_s(str, "");

                        itoa(nFile.time_m, str, 10);
                        fileObj << str << "\n";
                        strcpy_s(str, "");
                    }
                    fileObj.close(); // �������� �����
                    break;
                }
                case 1003:
                    // ����� ���� "�����"
                    PostQuitMessage(0);
                    break;
                case 1004: {
                    // ���������� �� ���� � ������� � ������ �������
                    sort(1004);
                    break;
                }
                case 1005: {
                    //���������� �� ���� � ������� � ������ ����������
                    sort(1005);
                    break;
                }
                case 1006: {
                    //  �� ������� ����� � ������� ��������,
                    sort(1006);
                    break;
                }
                case 1007: {
                     // �� ������� ����� � ������� �����������,
                    sort(1007);
                    break;
                }
                case 1300:
                    // �������� �������

                    DialogBoxParam(HI, MAKEINTRESOURCE(DLG_WIN), hwnd, DlgAddProc, 0); // �������� ��������� �� �������,
                    // ������� ������� ���� ���������� ��������
                    break;
                case 1301:
                    // ��������

                    DialogBoxParam(HI, MAKEINTRESOURCE(DLG_WIN), hwnd, DlgEditProc, 0); // �������� ��������� �� �������,
                    // ������� ������� ���� ��������� ��������
                    break;
                case 1302:
                    // ������� �������

                    // ��������� �������� �� listbox, �� ������� ��������� ������
                    int num = SendMessage(listBox, LB_GETCURSEL, 0, 0L);

                    // �������� ����� �������� �� listbox
                    SendMessage(listBox, LB_DELETESTRING, num, 0L);

                    // �������� ����� �������� �� ������
                    files.erase(files.begin() + num);
                    break;
            }
            break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam); // ��������� ��������� ���������
            break;

    }
    return 0;
}

BOOL FileDlgProc(HWND hDlg, UINT msg, WPARAM wParam, int index) {
    // ������� ��������� ���� ����������/��������������
    HWND File_name;
    HWND Date_day;
    HWND Date_month;
    HWND Date_year;
    HWND time_m;
    HWND time_h;
    HWND size;
    HWND num_sit;

    TCHAR bu[101] = "";
    char buff[256] = "";

    File tmp;

    switch (msg) {
        case WM_INITDIALOG: {
            HI = GetModuleHandle(NULL);
            File_name = GetDlgItem(hDlg, IDC_EDIT1);
            size = GetDlgItem(hDlg, IDC_EDIT7);
            Date_day = GetDlgItem(hDlg, IDC_EDIT2);
            Date_month = GetDlgItem(hDlg, IDC_EDIT3);
            Date_year = GetDlgItem(hDlg, IDC_EDIT4);
            time_m = GetDlgItem(hDlg, IDC_EDIT5);
            time_h = GetDlgItem(hDlg, IDC_EDIT6);

            // ����������� �� ���-�� �������� ��� �����
            SendMessage(Date_day, EM_LIMITTEXT, 2, 0);
            SendMessage(Date_month, EM_LIMITTEXT, 2, 0);
            SendMessage(Date_year, EM_LIMITTEXT, 4, 0);
            SendMessage(time_h, EM_LIMITTEXT, 2, 0);
            SendMessage(time_m, EM_LIMITTEXT, 2, 0);
            SendMessage(size, EM_LIMITTEXT, 9, 0);

            if (index == NULL_INDEX) {
                // ���� � ������� ������ �������� NULL_INDEX,
                // �� ���� ������� ��� ���������� ��������
            } else {
                // ���� � ������� ������ �������� NULL_INDEX,
                // �� ���� ������� ��� �������������� ��������
                // ��������� � ���� ������ �������� ��������

                File nFile = files[index]; // ��������� ������ �������� ����� �� ������
                
                SetWindowText(File_name, nFile.file_name); // �������� ����� � ��������� ����
                
                itoa(nFile.day, buff, 10); // ��������������� ����� � ������
                SetWindowText(Date_day, buff); // ������ ���� ������ � ������ ���� ����� � ����
                strcpy_s(buff, ""); // ������� ������ ��� ������

                itoa(nFile.size, buff, 10);
                SetWindowText(size, buff);
                strcpy_s(buff, "");

                itoa(nFile.month, buff, 10);
                SetWindowText(Date_month, buff);
                strcpy_s(buff, "");
                
                itoa(nFile.year, buff, 10);
                SetWindowText(Date_year, buff);
                strcpy_s(buff, "");
                
                itoa(nFile.time_h, buff, 10);
                SetWindowText(time_h, buff);
                strcpy_s(buff, "");
                
                itoa(nFile.time_m, buff, 10);
                SetWindowText(time_m, buff);
                strcpy_s(buff, "");
            };

        }
        case WM_COMMAND:
            switch (wParam) {
                case IDC_SAVE: {
                    // ��������� ������� "���������"

                    // �������� ����� ����� � ����
                    File_name = GetDlgItem(hDlg, IDC_EDIT1);
                    Date_day = GetDlgItem(hDlg, IDC_EDIT2);
                    Date_month = GetDlgItem(hDlg, IDC_EDIT3);
                    Date_year = GetDlgItem(hDlg, IDC_EDIT4);
                    time_m = GetDlgItem(hDlg, IDC_EDIT5);
                    time_h = GetDlgItem(hDlg, IDC_EDIT6);
                    size = GetDlgItem(hDlg, IDC_EDIT7);

                    GetWindowText(File_name, bu, 100); // ������ �������� ����
                    CharToOem(bu, buff); // ��� ��������� ������� �������� � ���� �����(��� ����� ������� ������� �� �������� :( )
                    strcpy_s(tmp.file_name, buff); // ����������� ���������� ������ � ���� ���������

                    GetWindowText(Date_day, bu, 100);
                    CharToOem(bu, buff);
                    tmp.day = atoi(buff); // ��������������� ������ � ����� � ���������� � ���������
                    tmp.day = tmp.day == 0 ? 1 : tmp.day; // �������� ��������: ���� 0, �� ������ ���� �� 1

                    GetWindowText(Date_month, bu, 100);
                    CharToOem(bu, buff);
                    tmp.month = atoi(buff);
                    tmp.month = tmp.month == 0 ? 1 : tmp.month;

                    GetWindowText(Date_year, bu, 100);
                    CharToOem(bu, buff);
                    tmp.year = atoi(buff);
                    tmp.year = tmp.year == 0 ? 1 : tmp.year;

                    GetWindowText(time_h, bu, 100);
                    CharToOem(bu, buff);
                    tmp.time_h = atoi(buff);

                    GetWindowText(time_m, bu, 100);
                    CharToOem(bu, buff);
                    tmp.time_m = atoi(buff);

                    GetWindowText(size, bu, 100);
                    CharToOem(bu, buff);
                    tmp.size = atoi(buff);

                    SendMessage(listBox, LB_DELETESTRING, index, 0);
                    if (index == NULL_INDEX) {
                        // ���� ������� �������� � ������ ����������
                        // �� ��������� ������ � ����� ������ listbox
                        SendMessageA(listBox, LB_ADDSTRING, 0, (LPARAM) fileToString(tmp).c_str());
                        files.push_back(tmp); // ��������� ��������� � ������
                    } else {
                        // ���� ����� ��������������
                        // �������������� ��������� � ������
                        files[index] = tmp;

                        // �������������� �������� � listbox
                        SendMessageA(listBox, LB_INSERTSTRING, index, (LPARAM) fileToString(tmp).c_str());
                    }

                    strcpy_s(buff, ""); // ������� ������

                    EndDialog(hDlg, 0); // �������� ����
                    return TRUE;
                    break;
                }
                case IDC_CANCEL:
                    // ������ "������"
                    EndDialog(hDlg, 0);// �������� ����
                    return TRUE;
                    break;
            }
            break;
        case WM_CLOSE:
            // ������� �� �������
            EndDialog(hDlg, 0); // �������� ����
            return TRUE;
            break;
    }
    return FALSE;
}


void sort(int x) {
    // 1004-1007
    /*
        1004 - �� ���� �������� � ������� �����������,
        1005 - �� ���� �������� � ������� ��������.
        1006 - �� ������� ����� � ������� ��������,
        1007 - �� ������� ����� � ������� �����������,
     */

    // ���������� "���������"
    if (x == 1004 || x == 1005) {
        // ���������� �� ����
        for (int i = 0; i < files.size(); i++) { // ������� ����
            for (int j = i + 1; j < files.size(); j++) { // ���������� ����
                if (x == 1004) {
                    if (files[i].year < files[j].year) {
                        std::swap(files[i], files[j]); // ������ ������� ��������
                    }
                    if (files[i].year == files[j].year) {
                        if (files[i].month < files[j].month) {
                            std::swap(files[i], files[j]);
                        }
                        if (files[i].month == files[j].month) {
                            if (files[i].day < files[j].day) {
                                std::swap(files[i], files[j]);
                            }
                            if (files[i].day == files[j].day) {
                                if (files[i].time_h < files[j].time_h) {
                                    std::swap(files[i], files[j]);
                                }
                                if (files[i].time_h == files[j].time_h) {
                                    if (files[i].time_m < files[j].time_m) {
                                        std::swap(files[i], files[j]);
                                    }
                                }
                            }
                        }
                    }
                }
                if (x == 1005) {
                    if (files[i].year > files[j].year) {
                        std::swap(files[i], files[j]);
                    }
                    if (files[i].year == files[j].year) {
                        if (files[i].month > files[j].month) {
                            std::swap(files[i], files[j]);
                        }
                        if (files[i].month == files[j].month) {
                            if (files[i].day > files[j].day) {
                                std::swap(files[i], files[j]);
                            }
                            if (files[i].day == files[j].day) {
                                if (files[i].time_h > files[j].time_h) {
                                    std::swap(files[i], files[j]);
                                }
                                if (files[i].time_h == files[j].time_h) {
                                    if (files[i].time_m > files[j].time_m) {
                                        std::swap(files[i], files[j]);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // ���������� "���������"
    //  �� ������� �����
    if (x == 1006 || x == 1007) {
        for (int i = 0; i < files.size(); i++) {
            for (int j = i + 1; j < files.size(); j++) {
                if (x == 1006) {
                    if (files[i].size > files[j].size) {
                        std::swap(files[i], files[j]);
                    }
                }
                if (x == 1007) {
                    if (files[i].size < files[j].size) {
                        std::swap(files[i], files[j]);
                    }
                }
            }
        }
    }


    SendMessage(listBox, LB_RESETCONTENT, 0, 0); // ������ listbox
    for (int i = 0; i < files.size(); i++) { // ������ ��������� ��� �������� ������ files � listbox
        SendMessageA(listBox, LB_ADDSTRING, 0, (LPARAM) fileToString(files[i]).c_str());
    }
}

void createMenu(HWND hwnd) {
    // �������� �������� ����
    HMENU mainMenu = CreateMenu();
    HMENU MenuFile = CreateMenu();
    HMENU MenuSort = CreateMenu();
    AppendMenu(mainMenu, MF_STRING | MF_POPUP, (UINT) MenuFile, "����");
    {
        AppendMenu(MenuFile, MF_STRING, 1001, "�������");
        AppendMenu(MenuFile, MF_STRING, 1002, "���������");
        AppendMenu(MenuFile, MF_SEPARATOR, 1000, "");
        AppendMenu(MenuFile, MF_STRING, 1003, "�����");

    }
    AppendMenu(mainMenu, MF_STRING | MF_POPUP, (UINT) MenuSort, "&����������");
    {
        AppendMenu(MenuSort, MF_STRING, 1004, "�� ���� � ������� � ������� ��������");
        AppendMenu(MenuSort, MF_STRING, 1005, "�� ���� � ������� � ������� �����������");
        AppendMenu(MenuSort, MF_STRING, 1006, "�� ������� ����� � ������� �����������");
        AppendMenu(MenuSort, MF_STRING, 1007, "�� ������� ����� � ������� ��������");
    }
    SetMenu(hwnd, mainMenu);
    SetMenu(hwnd, MenuFile);
    SetMenu(hwnd, MenuSort);
}