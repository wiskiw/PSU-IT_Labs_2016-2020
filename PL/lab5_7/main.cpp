#include <Windows.h>
#include <fstream>
#include <vector>
#include "resource.h"

const int NULL_INDEX = -1;
static const std::string FILENAME = "../binary.bin";

HINSTANCE HI;
HWND mainWnd;
HWND listBox;


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

BOOL TicketDlgProc(HWND, UINT, WPARAM, int);

BOOL CALLBACK DlgAddProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
    return TicketDlgProc(hDlg, msg, wParam, NULL_INDEX);
}

BOOL CALLBACK DlgEditProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
    return TicketDlgProc(hDlg, msg, wParam, SendMessage(listBox, LB_GETCURSEL, 0, 0));
}

struct Ticket {
    char film_name[31];
    int day;
    int month;
    int year;
    int time_h, time_m;
    int num_row;
    int num_place;
};

std::vector<Ticket> tickets;

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

    //HWND cap = CreateWindowEx(0, "static", "Ќазвание сеанса - дата и врем¤ - номер р¤да - номер места", WS_CHILD | WS_DLGFRAME | ES_CENTER, 0, 0, 1010, 25, (HWND) mainWnd, NULL, hInst, 0);
    //ShowWindow(cap, SW_SHOW);
    //UpdateWindow(cap);

    listBox = CreateWindowEx(0, "listbox", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY | WS_VSCROLL, 0, 0,
                             1020, 488, (HWND) mainWnd, NULL, hInst, 0);
    ShowWindow(listBox, SW_SHOW);
    UpdateWindow(listBox);

    tickets.clear();

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

std::string ticketToString(Ticket t) {
    std::string line = "";
    line = line + "\"" + t.film_name + "\" - ";
    line = line + std::to_string(t.day) + ".";
    line = line + std::to_string(t.month) + ".";
    line = line + std::to_string(t.year) + "   ";
    line = line + std::to_string(t.time_h) + ":";
    line = line + std::to_string(t.time_m) + " - ";
    line = line + std::to_string(t.num_row) + "x";
    line = line + std::to_string(t.num_place);
    return line;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    Ticket tmp;
    switch (msg) {
        case WM_CONTEXTMENU: {
            HMENU contMenu = CreatePopupMenu();
            AppendMenu(contMenu, MFT_STRING, 1300, "&Добавить");

            UINT menuKeys = MFT_STRING;
            if (SendMessage(listBox, LB_GETCURSEL, 0, 0) == LB_ERR) {
                // nothing select
                menuKeys = MFT_STRING | MF_DISABLED;
            }
            AppendMenu(contMenu, menuKeys, 1301, "&Изменить");
            AppendMenu(contMenu, menuKeys, 1302, "&Удалить");

            TrackPopupMenu(contMenu, TPM_RIGHTBUTTON | TPM_TOPALIGN | TPM_LEFTALIGN, LOWORD(lParam), HIWORD(lParam), 0,
                           hwnd, NULL);
            DestroyMenu(contMenu);
            break;
        }
        case WM_COMMAND:
            switch (wParam) {
                case 1001: {
                    //открыть файл
                    SendMessage(listBox, LB_RESETCONTENT, 0, 0);
                    tickets.clear();

                    std::ifstream fileObj;
                    fileObj.open(FILENAME, std::ios::binary);
                    std::string line;
                    int counter = 0;
                    while (std::getline(fileObj, line)) counter++;
                    counter /= 8;
                    fileObj.clear();
                    fileObj.seekg(0);
                    for (int i = 0; i < counter; i++) {
                        line = "";

                        std::getline(fileObj, line);
                        strcpy_s(tmp.film_name, line.c_str());

                        std::getline(fileObj, line);
                        tmp.day = atoi(line.c_str());

                        std::getline(fileObj, line);
                        tmp.month = atoi(line.c_str());

                        std::getline(fileObj, line);
                        tmp.year = atoi(line.c_str());

                        std::getline(fileObj, line);
                        tmp.time_h = atoi(line.c_str());

                        std::getline(fileObj, line);
                        tmp.time_m = atoi(line.c_str());

                        std::getline(fileObj, line);
                        tmp.num_row = atoi(line.c_str());

                        std::getline(fileObj, line);
                        tmp.num_place = atoi(line.c_str());

                        tickets.push_back(tmp);
                        SendMessageA(listBox, LB_ADDSTRING, 0, (LPARAM) ticketToString(tmp).c_str());
                    }
                    fileObj.close();

                    break;
                }
                case 1002: {
                    //сохранить данные в бинарный файл
                    std::ofstream fileObj;
                    fileObj.open(FILENAME, std::ios::binary);
                    char str[256] = "";
                    for (int i = 0; i < tickets.size(); i++) {
                        fileObj << tickets[i].film_name << "\r\n";
                        itoa(tickets[i].day, str, 10);
                        fileObj << str << "\r\n";
                        strcpy_s(str, "");
                        itoa(tickets[i].month, str, 10);
                        fileObj << str << "\r\n";
                        strcpy_s(str, "");
                        itoa(tickets[i].year, str, 10);
                        fileObj << str << "\r\n";
                        strcpy_s(str, "");
                        itoa(tickets[i].time_h, str, 10);
                        fileObj << str << "\r\n";
                        strcpy_s(str, "");
                        itoa(tickets[i].time_m, str, 10);
                        fileObj << str << "\r\n";
                        strcpy_s(str, "");
                        itoa(tickets[i].num_row, str, 10);
                        fileObj << str << "\r\n";
                        strcpy_s(str, "");
                        itoa(tickets[i].num_place, str, 10);
                        fileObj << str << "\r\n";
                        strcpy_s(str, "");
                    }
                    fileObj.close();
                    break;
                }
                case 1003:
                    PostQuitMessage(0);
                    break;
                case 1004: {
                    // сортировка по дате и времени в пор¤дке убывани¤
                    sort(1004);
                    break;
                }
                case 1005: {
                    //сортировка по дате и времени в пор¤дке возрастани¤
                    sort(1005);
                    break;
                }
                case 1006: {
                    //сортировка по номеру места в пор¤дке возрастани¤
                    sort(1006);
                    break;
                }
                case 1007: {
                    //сортировка по номеру места в пор¤дке убывани¤
                    sort(1007);
                    break;
                }
                case 1300:
                    DialogBoxParam(HI, MAKEINTRESOURCE(DLG_WIN), hwnd, DlgAddProc, 0);
                    break;
                case 1301:
                    DialogBoxParam(HI, MAKEINTRESOURCE(DLG_WIN), hwnd, DlgEditProc, 0);
                    break;
                case 1302:
                    int num = SendMessage(listBox, LB_GETCURSEL, 0, 0L);
                    SendMessage(listBox, LB_DELETESTRING, num, 0L);
                    tickets.erase(tickets.begin() + num);
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
            return DefWindowProc(hwnd, msg, wParam, lParam);
            break;

    }
    return 0;
}

BOOL TicketDlgProc(HWND hDlg, UINT msg, WPARAM wParam, int index) {
    HWND Seans;
    HWND Date_day;
    HWND Date_month;
    HWND Date_year;
    HWND time_m;
    HWND time_h;
    HWND num_line;
    HWND num_sit;

    TCHAR bu[101] = "";
    char buff[256] = "";

    Ticket tmp;

    switch (msg) {
        case WM_INITDIALOG: {
            HI = GetModuleHandle(NULL);
            Seans = GetDlgItem(hDlg, IDC_EDIT1);
            Date_day = GetDlgItem(hDlg, IDC_EDIT2);
            Date_month = GetDlgItem(hDlg, IDC_EDIT3);
            Date_year = GetDlgItem(hDlg, IDC_EDIT4);
            time_m = GetDlgItem(hDlg, IDC_EDIT5);
            time_h = GetDlgItem(hDlg, IDC_EDIT6);
            num_line = GetDlgItem(hDlg, IDC_EDIT7);
            num_sit = GetDlgItem(hDlg, IDC_EDIT8);
            SendMessage(Date_day, EM_LIMITTEXT, 2, 0);
            SendMessage(Date_month, EM_LIMITTEXT, 2, 0);
            SendMessage(Date_year, EM_LIMITTEXT, 4, 0);
            SendMessage(time_h, EM_LIMITTEXT, 2, 0);
            SendMessage(time_m, EM_LIMITTEXT, 2, 0);

            if (index == NULL_INDEX) {
                // add
            } else {
                //edit;
                SetWindowText(Seans, tickets[index].film_name);
                itoa(tickets[index].day, buff, 10);
                SetWindowText(Date_day, buff);
                strcpy_s(buff, "");
                itoa(tickets[index].month, buff, 10);
                SetWindowText(Date_month, buff);
                strcpy_s(buff, "");
                itoa(tickets[index].year, buff, 10);
                SetWindowText(Date_year, buff);
                strcpy_s(buff, "");
                itoa(tickets[index].time_h, buff, 10);
                SetWindowText(time_h, buff);
                strcpy_s(buff, "");
                itoa(tickets[index].time_m, buff, 10);
                SetWindowText(time_m, buff);
                strcpy_s(buff, "");
                itoa(tickets[index].num_row, buff, 10);
                SetWindowText(num_line, buff);
                strcpy_s(buff, "");
                itoa(tickets[index].num_place, buff, 10);
                SetWindowText(num_sit, buff);
                strcpy_s(buff, "");
            };

        }
        case WM_COMMAND:
            switch (wParam) {
                case IDC_SAVE: {
                    Seans = GetDlgItem(hDlg, IDC_EDIT1);
                    Date_day = GetDlgItem(hDlg, IDC_EDIT2);
                    Date_month = GetDlgItem(hDlg, IDC_EDIT3);
                    Date_year = GetDlgItem(hDlg, IDC_EDIT4);
                    time_m = GetDlgItem(hDlg, IDC_EDIT5);
                    time_h = GetDlgItem(hDlg, IDC_EDIT6);
                    num_line = GetDlgItem(hDlg, IDC_EDIT7);
                    num_sit = GetDlgItem(hDlg, IDC_EDIT8);

                    GetWindowText(Seans, bu, 100);
                    CharToOem(bu, buff);
                    strcpy_s(tmp.film_name, buff);

                    GetWindowText(Date_day, bu, 100);
                    CharToOem(bu, buff);
                    tmp.day = atoi(buff);
                    tmp.day = tmp.day == 0 ? 1 : tmp.day;

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

                    GetWindowText(num_line, bu, 100);
                    CharToOem(bu, buff);
                    tmp.num_row = atoi(buff);
                    tmp.num_row = tmp.num_row == 0 ? 1 : tmp.num_row;

                    GetWindowText(num_sit, bu, 100);
                    CharToOem(bu, buff);
                    tmp.num_place = atoi(buff);
                    tmp.num_place = tmp.num_place == 0 ? 1 : tmp.num_place;

                    SendMessage(listBox, LB_DELETESTRING, index, 0);
                    if (index == NULL_INDEX) {
                        // add
                        SendMessageA(listBox, LB_ADDSTRING, 0, (LPARAM) ticketToString(tmp).c_str());
                        tickets.push_back(tmp);
                    } else {
                        // edit
                        tickets[index] = tmp;
                        SendMessageA(listBox, LB_INSERTSTRING, index, (LPARAM) ticketToString(tmp).c_str());
                    }

                    strcpy_s(buff, "");

                    EndDialog(hDlg, 0);
                    return TRUE;
                    break;
                }
                case IDC_CANCEL:
                    EndDialog(hDlg, 0);
                    return TRUE;
                    break;
            }
            break;
        case WM_CLOSE:
            EndDialog(hDlg, 0);
            return TRUE;
            break;
    }
    return FALSE;
}


void sort(int x) {
    // 1004-1007
    // 1004 - сортировка по дате и времени в пор¤дке убывани¤
    // 1005 - сортировка по дате и времени в пор¤дке возрастани¤
    // 1006 - сортировка по номеру места в пор¤дке возрастани¤
    // 1007 - сортировка по номеру места в пор¤дке убывани¤
    if (x == 1004 || x == 1005) {
        for (int i = 0; i < tickets.size(); i++) {
            for (int j = i + 1; j < tickets.size(); j++) {
                if (x == 1004) {
                    if (tickets[i].year < tickets[j].year) {
                        std::swap(tickets[i], tickets[j]);
                    }
                    if (tickets[i].year == tickets[j].year) {
                        if (tickets[i].month < tickets[j].month) {
                            std::swap(tickets[i], tickets[j]);
                        }
                        if (tickets[i].month == tickets[j].month) {
                            if (tickets[i].day < tickets[j].day) {
                                std::swap(tickets[i], tickets[j]);
                            }
                            if (tickets[i].day == tickets[j].day) {
                                if (tickets[i].time_h < tickets[j].time_h) {
                                    std::swap(tickets[i], tickets[j]);
                                }
                                if (tickets[i].time_h == tickets[j].time_h) {
                                    if (tickets[i].time_m < tickets[j].time_m) {
                                        std::swap(tickets[i], tickets[j]);
                                    }
                                }
                            }
                        }
                    }
                }
                if (x == 1005) {
                    if (tickets[i].year > tickets[j].year) {
                        std::swap(tickets[i], tickets[j]);
                    }
                    if (tickets[i].year == tickets[j].year) {
                        if (tickets[i].month > tickets[j].month) {
                            std::swap(tickets[i], tickets[j]);
                        }
                        if (tickets[i].month == tickets[j].month) {
                            if (tickets[i].day > tickets[j].day) {
                                std::swap(tickets[i], tickets[j]);
                            }
                            if (tickets[i].day == tickets[j].day) {
                                if (tickets[i].time_h > tickets[j].time_h) {
                                    std::swap(tickets[i], tickets[j]);
                                }
                                if (tickets[i].time_h == tickets[j].time_h) {
                                    if (tickets[i].time_m > tickets[j].time_m) {
                                        std::swap(tickets[i], tickets[j]);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if (x == 1006 || x == 1007) {
        for (int i = 0; i < tickets.size(); i++) {
            for (int j = i + 1; j < tickets.size(); j++) {
                if (x == 1006) {
                    if (tickets[i].num_place > tickets[j].num_place) {
                        std::swap(tickets[i], tickets[j]);
                    }
                }
                if (x == 1007) {
                    if (tickets[i].num_place < tickets[j].num_place) {
                        std::swap(tickets[i], tickets[j]);
                    }
                }
            }
        }
    }

    SendMessage(listBox, LB_RESETCONTENT, 0, 0);
    for (int i = 0; i < tickets.size(); i++) {
        SendMessageA(listBox, LB_ADDSTRING, 0, (LPARAM) ticketToString(tickets[i]).c_str());
    }
}

void createMenu(HWND hwnd) {
    HMENU mainMenu = CreateMenu();
    HMENU MenuFile = CreateMenu();
    HMENU MenuSort = CreateMenu();
    AppendMenu(mainMenu, MF_STRING | MF_POPUP, (UINT) MenuFile, "Файл");
    {
        AppendMenu(MenuFile, MF_STRING, 1001, "Открыть");
        AppendMenu(MenuFile, MF_STRING, 1002, "Сохранить");
        AppendMenu(MenuFile, MF_SEPARATOR, 1000, "");
        AppendMenu(MenuFile, MF_STRING, 1003, "Выход");

    }
    AppendMenu(mainMenu, MF_STRING | MF_POPUP, (UINT) MenuSort, "&Сортировка");
    {
        AppendMenu(MenuSort, MF_STRING, 1004, "По дате и времени в порядке убывания");
        AppendMenu(MenuSort, MF_STRING, 1005, "По дате и времени в порядке возрастания");
        AppendMenu(MenuSort, MF_STRING, 1006, "По номеру места в порядке возрастания");
        AppendMenu(MenuSort, MF_STRING, 1007, "По номеру места в порядке убывания");
    }
    SetMenu(hwnd, mainMenu);
    SetMenu(hwnd, MenuFile);
    SetMenu(hwnd, MenuSort);
}