#define menu_items_count 19

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "menu.h"

#ifndef ushort
#define ushort unsigned short
#endif
#ifndef uint
#define uint unsigned int
#endif

typedef struct student {
    char group[7];           // Шифр группы (6 символов)
    char surname[16];        // Фамилия студента (15 символов)
    ushort birth_year;       // Год рождения студента (0 - 65535)
    byte woman;              // Пол студента (0 или 1)
    ushort skipped_hours;    // Пропущенные часы
    ushort acquitted_skips;  // Оправданные часы
} student;

typedef struct list_item {
    student data;
    struct list_item* prev;
    struct list_item* next;
} list_item;

typedef struct list_header {
    list_item* first;
    uint len;
} list_header;

/// <summary>
/// Функция для создания пустого списка.
/// </summary>
/// <returns>Указатель на заголовок созданного списка</returns>
list_header* create_empty_list() {
    list_header* res = (list_header*)calloc(1, sizeof(list_header));
    if (!res) return NULL;
    res->first = NULL;
    res->len = 0;
    return res;
}

/// <summary>
/// Функция для удаления списка, включая все его элементы
/// </summary>
/// <param name="_lh">Указатель на заголовок удаляемого списка</param>
void delete_list(list_header* _lh) {
    if (!_lh) return;
    list_item* first = _lh->first;
    for (int _i = 0; _i < _lh->len;) {
        if (!(_lh->first)) break;
        list_item* first = _lh->first;
        _lh->first = first->next;
        free(first);
        _lh->len--;
    }
    free(_lh);
}

int add_new_item_to_list(list_header* _lh, student _stud) {
    if (!_lh) return 0;
    list_item* first = _lh->first;
    if (!first) {
        _lh->first = (list_item*)calloc(1, sizeof(list_item));
        if (!(_lh->first)) {
            _lh->first = NULL;
            return 0;
        }
        _lh->first->data = _stud;
        _lh->first->prev = NULL;
        _lh->first->next = NULL;
        _lh->len = 1;
        return 1;
    }
    while (first->next) first = first->next;
    first->next = (list_item*)calloc(1, sizeof(list_item));
    if (!(first->next)) {
        first->next = NULL;
        return 0;
    }
    first->next->data = _stud;
    first->next->prev = first;
    first->next->next = NULL;
    _lh->len++;
    return 1;
}

student create_student_from_data(char group[7], char surname[16], ushort birth_year, byte woman, ushort skipped_hours, ushort acquitted_skips) {
    student res = { group, surname, birth_year, woman, skipped_hours, acquitted_skips };
    return res;
}

//

int main() {
    SetConsoleOutputCP(1251);
    const char* menu[menu_items_count] = {
        "Создать пустой список",
        "Загрузить список из файла",
        "Выгрузить список в файл",
        "Показать список",
        "Выйти из программы"
    };

    const char* headers[6] = {
        "Шифр группы (6)",
        "Фамилия студента (15)",
        "Год рождения студента",
        "Пол студента",
        "Пропущенные часы",
        "Оправданные часы"
    };
    // test_input();
    _getch();
    enter_data(headers, 6, NULL);
    list_header* list = NULL;
    /*
    for (uint _i = 0; _i < 4294967295; _i++) {
        list = create_empty_list();
        uint c = rand() % 999 + 1;
        printf("Creating list with %d elements\n", c);
        for (uint _j = 0; _j < c; _j++)
            add_new_item_to_list(list, create_student_from_data("IS21-3", "Kontarev VadimV", rand()%65535, rand()%2, rand()%65535, rand()%65535));

        delete_list(list);
    }
    */

    return 0;
}
