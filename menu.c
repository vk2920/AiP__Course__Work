#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef printf
#include <stdio.h>
#endif

#if !defined(HANDLE) || !defined(system)
#include <windows.h>
#endif

#ifndef _getch
#include <conio.h>
#endif

#ifndef uint
#define uint unsigned int
#endif

#include "menu.h"

/// <summary>
/// Функция для определения размеров окна консоли
/// </summary>
/// <returns></returns>
int* get_size() {
    int* res = (int*)calloc(3, sizeof(int));
    if (!res) return NULL;
    HANDLE hWndConsole;
    if (hWndConsole = GetStdHandle(-12)) {
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        if (GetConsoleScreenBufferInfo(hWndConsole, &consoleInfo)) {
            res[1] = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;
            res[2] = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1;
        }
        else res[0] = GetLastError();
    }
    else res[0] = GetLastError();
    return res;
}

/// <summary>
/// Простая функция для тестирования ввода при помощи _getch()
/// Используется для определения кодов, посылаемых клавишами клавиатуры.
/// </summary>
/// <returns></returns>
int test_input() {
    for (int _i = 0; _i < 200; _i++) printf("%d ", _getch());
    return 0;
}

/// <summary>
/// Какие строки документации? Это засекреченная функция
/// </summary>
void start_egg() {
    system("cls");
    FILE* egg = fopen("egg.txt", "rt");
    if (!egg) return;
    char* c = (char*)malloc(1024 * sizeof(char));
    if (c) {
        c[1023] = '\0';
        while (fread(c, sizeof(char), 1023, egg))
            printf("%s", c);
    }
    printf("\n");
    Sleep(2000);
}

/// <summary>
/// Функция для интерактивного выбора действия
/// </summary>
/// <param name="_menu">Массив C-строк с названиями действий</param>
/// <param name="_mic">Количество элементов массива</param>
/// <param name="_exit_code">ID действия, интерпретируемого как выход</param>
/// <returns>ID выбранного действия</returns>
int select_from_menu(const char** _menu, const int _mic, int _exit_code) {
    int old_cp = GetConsoleOutputCP();
    SetConsoleOutputCP(1251);
    int s = 0;
    int* size = get_size();
    int* old_size = (int*)calloc(2, sizeof(int));
    old_size[0] = size[0];
    old_size[1] = size[1];
    int htab, vtab;
    bool sized = false;
    const char _sep1[] = "\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xD1\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\n";
    const char _sep2[] = "\xC7\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC5\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xB6\n";
    const char _sep3[] = "\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCF\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC\n";
    COORD position = { 0, 0 };
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    char* ttab = NULL, * ltab = NULL;

    size = get_size();
    if (size && !size[0]) htab = (get_size()[1] - 80) / 2;
    else htab = 0;
    if (size && !size[0]) vtab = (get_size()[2] - _mic - 1) / 2;
    else vtab = 0;

    ltab = (char*)malloc(htab);
    //#pragma clang loop unroll_count(4)
    for (int _i = 0; _i < htab; _i++) ltab[_i] = ' ', ltab[_i + 1] = '\0';

    ttab = (char*)malloc(vtab);
    //#pragma clang loop unroll_count(4)
    for (int _i = 0; _i < vtab; _i++) ttab[_i] = '\n', ttab[_i + 1] = '\0';

    while (1) {
        size = get_size();
        if ((size && old_size && (size[0] != old_size[0] || size[1] != old_size[1])) || !size || !old_size || !sized) {
            sized = true;
            free(old_size);
            old_size = size;
            system("cls");
            if (size && !size[0]) htab = (get_size()[1] - 80) / 2;
            else htab = 0;
            if (size && !size[0]) vtab = (get_size()[2] - _mic - 1) / 2;
            else vtab = 0;

            ltab = (char*)malloc(htab);
            //#pragma clang loop unroll_count(4)
            for (int _i = 0; _i < htab; _i++) ltab[_i] = ' ', ltab[_i + 1] = '\0';

            ttab = (char*)malloc(vtab);
            //#pragma clang loop unroll_count(4)
            for (int _i = 0; _i < vtab; _i++) ttab[_i] = '\n', ttab[_i + 1] = '\0';
        }

        // Вывод менюшки
        SetConsoleCursorPosition(hConsole, position);
        SetConsoleOutputCP(866);
        printf("%s%s%s", ttab, ltab, _sep1);
        SetConsoleOutputCP(old_cp);
        for (int _i = 0; _i < (_mic + 1) / 2; _i++) {
            for (int _j = 0; _j < htab; _j++) printf(" ");
            SetConsoleOutputCP(866);
            printf((2 * _i == s) ? "\xBA\x1b[47;30m" : "\xBA");
            SetConsoleOutputCP(old_cp);
            printf("%38.38s \x1b[0m", _menu[2 * _i]);
            SetConsoleOutputCP(866);
            printf("\xB3");
            SetConsoleOutputCP(old_cp);
            if (2 * _i + 1 < _mic) {
                printf((2 * _i + 1 == s) ? "\x1b[47;30m" : "");
                printf(" %-38.38s", _menu[2 * _i + 1]);
                SetConsoleOutputCP(866);
                printf("\x1b[0m\xBA\n");
                SetConsoleOutputCP(old_cp);
            }
            else {
                SetConsoleOutputCP(866);
                printf("                                       \xBA\n");
                SetConsoleOutputCP(old_cp);
            }
            if (2 * _i + 2 < _mic) {
                SetConsoleOutputCP(866);
                printf("%s%s", ltab, _sep2);
                SetConsoleOutputCP(old_cp);
            }
        }
        SetConsoleOutputCP(866);
        printf("%s%s", ltab, _sep3);
        SetConsoleOutputCP(old_cp);

        // Исключим ложные срабатывания
        int a = _getch();

        // 115 121 115 116 101 109
        if (a == 115 && (a = _getch()) == 121 && (a = _getch()) == 115 && (a = _getch()) == 116 && (a = _getch()) == 101 && (a = _getch()) == 109) {
            start_egg();
        }
        // 251 237 251 229 243 252
        else if (a == 251 && (a = _getch()) == 237 && (a = _getch()) == 251 && (a = _getch()) == 229 && (a = _getch()) == 243 && (a = _getch()) == 252) {
            start_egg();
        }

        else if (a == 13) { system("cls"); SetConsoleOutputCP(old_cp); return s; }
        else if (a == 27 || a == 107) {
            system("cls");
            printf("Вы действительно хотите выйти? [Y / Any]");
            int b = _getch();
            if (b == 121 || b == 237) { SetConsoleOutputCP(old_cp); return _exit_code; }
            else continue;
        }

        // Получим нажатие клавиши и интерпретируем его в действие
        else if (a == 224)
            switch (_getch()) {
            case 71: s = 0; break;         // Home
            case 79: s = _mic - 1; break;  // End
            case 72: s -= 2; break;        // Up
            case 75: s -= 1; break;        // Left
            case 80: s += 2; break;        // Down
            case 77: s += 1; if (_mic % 2 && s == _mic) s = _mic - 2; break;        // Right
            case 107:                      // <Alt+F4>
                system("cls");
                printf("Вы действительно хотите выйти? [Y / <Alt+F4> / Any]");
                if (_getch() == 121 || _getch() == 107) { SetConsoleOutputCP(old_cp); return _exit_code; }
            }

        // Не позволим выйти за пределы допустимых значений
        if (s < 0) s = 0; else if (s >= _mic) s = _mic - 1;
    }
    free(size);
}

char* delete_last_char(char* _str) {
    if (!_str) return _str;
    unsigned int len = strlen(_str);
    if (len <= 1) return NULL;
    char* res = (char*)calloc(len+1, sizeof(char));
    if (!res) return _str;
    for (unsigned int _i = 0; _i < len-1; _i++) res[_i] = _str[_i];
    free(_str);
    return res;
}

char* add_new_char(char* _str, char _c) {
    if (!_str) return _str;
    uint len = strlen(_str);
    char* res = (char*)calloc(len + 2, sizeof(char));
    if (!res) return _str;
    for (uint _i = 0; _i < len; _i++) res[_i] = _str[_i];
    res[len] = _c;
    return res;
}

char** enter_data(const char** _headers, const int _items_count) {
    if (!_headers) {
        return NULL;
    }
    char** res = (char**)calloc(_items_count, sizeof(char*));
    system("cls");
    COORD left_top_corner = {
        (get_size()[1] - 160) / 2,
        (get_size()[2] - _items_count*2 - 2) / 2
    };
    COORD current_position = left_top_corner;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), current_position);
    int main_cp = GetConsoleOutputCP();
    SetConsoleOutputCP(866);
    printf("\xC9");
    for (int _i = 1; _i < 159; _i++) printf("\xCD");
    printf("\xBB");
    current_position.Y++;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), current_position);
    printf("\xBA");
    for (int _j = 0; _j < 158; _j++) printf(" ");
    printf("\xBA");
    for (int _i = 0; _i < _items_count; _i++) {
        current_position.Y++;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), current_position);
        printf("\xBA ");
        SetConsoleOutputCP(main_cp);
        printf("%40.40s  ", _headers[_i]);
        for (int _j = 0; _j < 114; _j++) printf("_");
        SetConsoleOutputCP(866);
        printf(" \xBA");
        current_position.Y++;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), current_position);
        printf("\xBA");
        for (int _j = 0; _j < 158; _j++) printf(" ");
        printf("\xBA");
    }
    current_position.Y++;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), current_position);
    printf("\xC8");
    for (int _i = 0; _i < 158; _i++) printf("\xCD");
    printf("\xBC");
    current_position.X += 44;
    current_position.Y -= _items_count * 2;
    int top = current_position.Y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), current_position);
    // printf("X");
    int selected = 0;
    uint len = 0;
    while (1) {
        // 13 - Enter
        // 10 - Ctrl + Enter
        int a = _getch();
        if (a == 224) {
            a = _getch();
        }

        if (a == 72) selected--;
        else if (a == 80 || a == 13) selected++;
        else if (a == 8) {
            if (res[selected]) res[selected] = delete_last_char(res[selected]);
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), current_position);
            len = 0;
            if (res[selected]) len = strlen(res[selected]);
            SetConsoleOutputCP(main_cp);
            if (res[selected]) printf("%s", res[selected]);
            else printf("");
            for (int _i = 0; _i < 114 - len; _i++) printf("_");
            SetConsoleOutputCP(866);
        }
        else if (a == 9) return res;
        else if (a <= 126 && a >= 32) {
            if (!res[selected]) {
                res[selected] = (char*)calloc(2, sizeof(char));
                if (res[selected])
                    res[selected][0] = a;
            }
            else res[selected] = add_new_char(res[selected], a);
            len = 0;
            if (res[selected]) len = strlen(res[selected]);
            SetConsoleOutputCP(main_cp);
            if (res[selected]) printf("%s", res[selected]);
            for (int _i = 0; _i < 114 - len; _i++) printf("_");
            SetConsoleOutputCP(866);
        }

        if (selected >= _items_count) selected = _items_count - 1;
        else if (selected < 0) selected = 0;
        current_position.Y = top + selected * 2;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), current_position);
    }
    return res;
}

void create_background() {
    system("cls");
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    for (int _r = 0; _r < 2; _r++)
        for (int _c = 0; _c < cols; _c++)
            // printf("%d", rand() % 2);
            printf(" ");
}

int menu_new(const char** _menu_item_list, const int _menu_items_count, const int _exit_answer) {
    int bd_cp = 866;
    int cp = GetConsoleOutputCP();
    int selected = 0;
    SetConsoleOutputCP(bd_cp);
    COORD border_tl = { 5, 2 };
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    while (1) {
    create_background();
        SetConsoleCursorPosition(hConsole, border_tl);
        printf("\xC9");
        for (int _i = 0; _i < 40; _i++) printf("\xCD");
        printf("\xD1");
        for (int _i = 0; _i < 120; _i++) printf("\xCD");
        printf("\xBB");
        for (byte _i = 0; _i < _menu_items_count; _i++) {
            printf("\n     \xBA");
            SetConsoleOutputCP(cp);
            if (_i == selected) {
                printf("\x1B[47;30m %-38.38s \x1B[0m", _menu_item_list[_i]);
            }
            else printf(" %-38.38s ", _menu_item_list[_i]);
            SetConsoleOutputCP(bd_cp);
            printf("\xB3                                                                             ");
            printf("                                                                                \xBA");
        }
        int a = _getch();
        while (a != 72 && a != 80 && a != 71 && a != 79) { a = _getch(); }
        switch (a) {
        case 72: // Up
            selected -= 1;
            break;
        case 80: // Down
            selected += 1;
            break;
        case 71: // PgUp
            selected = 0;
            break;
        case 79: // PgDown
            selected = _menu_items_count - 1;
            break;
        }
        if (selected < 0) selected = 0;
        else if (selected >= _menu_items_count) selected = _menu_items_count - 1;
    }
    return -1;
}
