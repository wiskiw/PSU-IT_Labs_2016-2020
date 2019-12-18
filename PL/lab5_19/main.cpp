#include <Windows.h>
#include <fstream>
#include <vector>
#include <iostream>
#include "resource.h"

/*
 * кодировка кода - win1251
 * дизайн окна добавления/редактирования в файле DialogView.rc

 ФАЙЛ:
 - Имя файла (строка 30 символов);
 - Размер файла (целое число);
 - Дата создания (в формате дд.мм.гггг);
 - Время создания (в формате чч:мм).

 Формат ввода: Имя файла, Размер файла, Дата и Время создания.

 По размеру файла в порядке убывания,
 по размеру файла в порядке возрастания,
 по дате создания в порядке возрастания,
 по дате создания в порядке убывания.
 */

const int NULL_INDEX = -1;
static const std::string FILENAME = "../binary.bin";

HINSTANCE HI;
HWND mainWnd;
HWND listBox;


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

BOOL FileDlgProc(HWND, UINT, WPARAM, int);

BOOL CALLBACK DlgAddProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
    // вызов функции обработки окна добаления элемента
    // и передача в качестве индекса элемента переменной NULL_INDEX,
    // тк следует добавить новый элемент, а не редактировать из списка

    // Возвращение её значения
    return FileDlgProc(hDlg, msg, wParam, NULL_INDEX);
}

BOOL CALLBACK DlgEditProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
    // получение элемента из listbox, на который указывает курсор
    int num = SendMessage(listBox, LB_GETCURSEL, 0, 0L);

    // вызов функции обработки окна изменения элемента
    // и передача индекса элемента в списка, для которого она вызвана

    // Возвращение её значения
    return FileDlgProc(hDlg, msg, wParam, num);
}


struct File {
    char file_name[31];
    unsigned long size; // размер
    int day; // день
    int month; // месяц
    int year; // год
    int time_h; // часы
    int time_m; // минуты
};

std::vector<File> files; // вектор(массив) со списком файлов

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

    // создание listbox(списка) в окне, для отображения файлов
    listBox = CreateWindowEx(0, "listbox", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY | WS_VSCROLL, 0, 0,
                             1020, 488, (HWND) mainWnd, NULL, hInst, 0);
    ShowWindow(listBox, SW_SHOW); // отображение listbox
    UpdateWindow(listBox);

    files.clear(); // очистка списка с файлами

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}
// функция преобразования структуры "файл" в строку
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
            // создание ПКМ меню
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
                // обработка кодов команд из createMenu()

                case 1001: {
                    //открыть файл
                    SendMessage(listBox, LB_RESETCONTENT, 0, 0);
                    files.clear(); // очитка списка

                    std::ifstream fileObj;
                    fileObj.open(FILENAME, std::ios::binary); // открытие бинарного файла
                    std::string line; // переменная под строку в файле
                    int counter = 0; // счетчик строк
                    while (std::getline(fileObj, line)) counter++; // подсчет ко-ва строк в файле
                    counter /= 7; // определение кол-ва записей в файле(7 строк для каждой структуры "файл")
                    fileObj.clear();
                    fileObj.seekg(0); // перемещение по файлу в начало
                    for (int i = 0; i < counter; i++) { // цикл чтения записей
                        line = "";

                        std::getline(fileObj, line); // читаем линию из файла в line
                        strcpy_s(tmp.file_name, line.c_str()); // сохраняем значение в file_name

                        std::getline(fileObj, line);// следующая линия из файла
                        tmp.size = strtoul(line.c_str(), NULL, 10); // строка в unsigned long

                        std::getline(fileObj, line);
                        tmp.day = atoi(line.c_str()); // строка в int

                        std::getline(fileObj, line);
                        tmp.month = atoi(line.c_str());

                        std::getline(fileObj, line);
                        tmp.year = atoi(line.c_str());

                        std::getline(fileObj, line);
                        tmp.time_h = atoi(line.c_str());

                        std::getline(fileObj, line);
                        tmp.time_m = atoi(line.c_str());

                        files.push_back(tmp); // добавление только-что заполненной структуры в список структур files

                        // преобразование структуры в строку и добавление строки в listbox
                        SendMessageA(listBox, LB_ADDSTRING, 0, (LPARAM) fileToString(tmp).c_str());
                    }
                    fileObj.close(); // закрытие файла

                    break;
                }
                case 1002: {
                    //сохранить данные в бинарный файл
                    std::ofstream fileObj;
                    fileObj.open(FILENAME, std::ios::binary); // открытие файла
                    char str[256] = ""; // для конвертирования чисел в строку
                    for (int i = 0; i < files.size(); i++) { // цикл по всем структурам файлов
                        File nFile = files[i]; //чтение следующего файла из списка

                        fileObj << nFile.file_name << "\n"; // запись в файл имя файла

                        // преобразование размера файла(число) в строку и
                        // запись этой строки
                        fileObj << std::to_string(nFile.size).c_str() << "\n";

                        itoa(nFile.day, str, 10); // преобразование дня(число) в строку
                        fileObj << str << "\n";  // запись этой строки
                        strcpy_s(str, ""); // очистка строки

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
                    fileObj.close(); // закрытие файла
                    break;
                }
                case 1003:
                    // пункт меню "выход"
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
                    //  По размеру файла в порядке убывания,
                    sort(1006);
                    break;
                }
                case 1007: {
                     // по размеру файла в порядке возрастания,
                    sort(1007);
                    break;
                }
                case 1300:
                    // добавить элемент

                    DialogBoxParam(HI, MAKEINTRESOURCE(DLG_WIN), hwnd, DlgAddProc, 0); // передаем указатель на функцию,
                    // которая вызовет окно добавления элемента
                    break;
                case 1301:
                    // изменить

                    DialogBoxParam(HI, MAKEINTRESOURCE(DLG_WIN), hwnd, DlgEditProc, 0); // передаем указатель на функцию,
                    // которая вызовет окно изменения элемента
                    break;
                case 1302:
                    // удалить элемент

                    // получение элемента из listbox, на который указывает курсор
                    int num = SendMessage(listBox, LB_GETCURSEL, 0, 0L);

                    // удаление этого элемента из listbox
                    SendMessage(listBox, LB_DELETESTRING, num, 0L);

                    // удаление этого элемента из списка
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
            return DefWindowProc(hwnd, msg, wParam, lParam); // обработка системных сообщений
            break;

    }
    return 0;
}

BOOL FileDlgProc(HWND hDlg, UINT msg, WPARAM wParam, int index) {
    // функция обработки окна добавления/редактирования
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

            // ограничение по кол-ву символов для ввода
            SendMessage(Date_day, EM_LIMITTEXT, 2, 0);
            SendMessage(Date_month, EM_LIMITTEXT, 2, 0);
            SendMessage(Date_year, EM_LIMITTEXT, 4, 0);
            SendMessage(time_h, EM_LIMITTEXT, 2, 0);
            SendMessage(time_m, EM_LIMITTEXT, 2, 0);
            SendMessage(size, EM_LIMITTEXT, 9, 0);

            if (index == NULL_INDEX) {
                // если в индексе пришло значение NULL_INDEX,
                // то окно открыто для добавления элемента
            } else {
                // если в индексе пришло значение NULL_INDEX,
                // то окно открыто для редактирования элемента
                // загружаем в поля старые значения элемента

                File nFile = files[index]; // получение нужной стрктуры файла из списка
                
                SetWindowText(File_name, nFile.file_name); // название файла в заголовок окна
                
                itoa(nFile.day, buff, 10); // конвертирование числа в строку
                SetWindowText(Date_day, buff); // запись этой строки в нужное поле ввода в окне
                strcpy_s(buff, ""); // очистка буфера под строку

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
                    // обработка нажатия "сохранить"

                    // получени полей ввода с окна
                    File_name = GetDlgItem(hDlg, IDC_EDIT1);
                    Date_day = GetDlgItem(hDlg, IDC_EDIT2);
                    Date_month = GetDlgItem(hDlg, IDC_EDIT3);
                    Date_year = GetDlgItem(hDlg, IDC_EDIT4);
                    time_m = GetDlgItem(hDlg, IDC_EDIT5);
                    time_h = GetDlgItem(hDlg, IDC_EDIT6);
                    size = GetDlgItem(hDlg, IDC_EDIT7);

                    GetWindowText(File_name, bu, 100); // чтение значения поля
                    CharToOem(bu, buff); // для поддержки русских символов в поле ввода(все равно русские символы не работают :( )
                    strcpy_s(tmp.file_name, buff); // копирование временного буфера в поле структуры

                    GetWindowText(Date_day, bu, 100);
                    CharToOem(bu, buff);
                    tmp.day = atoi(buff); // конвертирование строки в число и сохранение в структуру
                    tmp.day = tmp.day == 0 ? 1 : tmp.day; // проверка значения: если 0, то меняем день на 1

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
                        // если функция работает в режими добавления
                        // то добавляем строку в конце списка listbox
                        SendMessageA(listBox, LB_ADDSTRING, 0, (LPARAM) fileToString(tmp).c_str());
                        files.push_back(tmp); // добавляем структуру к списку
                    } else {
                        // если режим редактирования
                        // перезаписываем структуру в списке
                        files[index] = tmp;

                        // перезаписываем значение в listbox
                        SendMessageA(listBox, LB_INSERTSTRING, index, (LPARAM) fileToString(tmp).c_str());
                    }

                    strcpy_s(buff, ""); // очистка буфера

                    EndDialog(hDlg, 0); // закрытие окна
                    return TRUE;
                    break;
                }
                case IDC_CANCEL:
                    // кнопка "отмена"
                    EndDialog(hDlg, 0);// закрытие окна
                    return TRUE;
                    break;
            }
            break;
        case WM_CLOSE:
            // нажатие на крестик
            EndDialog(hDlg, 0); // закрытие окна
            return TRUE;
            break;
    }
    return FALSE;
}


void sort(int x) {
    // 1004-1007
    /*
        1004 - по дате создания в порядке возрастания,
        1005 - по дате создания в порядке убывания.
        1006 - По размеру файла в порядке убывания,
        1007 - по размеру файла в порядке возрастания,
     */

    // сортировка "пузырьком"
    if (x == 1004 || x == 1005) {
        // сортировка по дате
        for (int i = 0; i < files.size(); i++) { // внешний цикл
            for (int j = i + 1; j < files.size(); j++) { // внутренний цикл
                if (x == 1004) {
                    if (files[i].year < files[j].year) {
                        std::swap(files[i], files[j]); // меняем местами значения
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

    // сортировка "пузырьком"
    //  По размеру файла
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


    SendMessage(listBox, LB_RESETCONTENT, 0, 0); // очитка listbox
    for (int i = 0; i < files.size(); i++) { // заново добавляем все элементы списка files в listbox
        SendMessageA(listBox, LB_ADDSTRING, 0, (LPARAM) fileToString(files[i]).c_str());
    }
}

void createMenu(HWND hwnd) {
    // создание верхнего меню
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
        AppendMenu(MenuSort, MF_STRING, 1006, "По размеру файла в порядке возрастания");
        AppendMenu(MenuSort, MF_STRING, 1007, "По размеру файла в порядке убывания");
    }
    SetMenu(hwnd, mainMenu);
    SetMenu(hwnd, MenuFile);
    SetMenu(hwnd, MenuSort);
}