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
    list_item* prev;
    list_item* next;
} list_item;

typedef struct list_header {
    list_item* first;
    list_item* last;
    uint len;
} list_header;

/// <summary>
/// Функция для создания пустого списка.
/// </summary>
/// <returns>Указатель на заголовок созданного списка</returns>
list_header* create_empty_list() {
    list_header* res = (list_header*)calloc(1, sizeof(list_header));
    res->first = NULL;
    res->last = NULL;
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
    while (first) {
        list_item* second = first->next;
        free(first);
        first = second;
        first->prev = NULL;
    }
    free(_lh);
}

int add_new_item_to_list(list_header* _lh, student _stud) {
    if (!_lh) return 0;
    list_item* first = _lh->first;
    while (first) first = first->next;
    first->next = (list_item*)calloc(1, sizeof(list_item));
    if (!(first->next)) {
        first->next = NULL;
        return 0;
    }
    first->next->data = _stud;
    first->next->prev = first;
    first->next->next = NULL;
    _lh->last = first->next;
    return 1;
}

student create_student_from_data(char group[7], char surname[16], ushort birth_year, byte woman, ushort skipped_hours, ushort acquitted_skips) {
    student res = { group, surname, birth_year, woman, skipped_hours, acquitted_skips };
    return res;
}

int main() {
    SetConsoleOutputCP(1251);
    const char* menu[menu_items_count] = {
        "Создать очередь",
        "Копировать очередь",
        "Добавить элемент в первую очередь",
        "Добавить элемент во вторую очередь",
        "Взять элемент из первой очереди",
        "Взять элемент из второй очереди",
        "Посмотреть элемент из первой очереди",
        "Посмотреть элемент из второй очереди",
        "Проверить первую очередь на одинаковые заряды",
        "Проверить вторую очередь на одинаковые заряды",
        "Просмотреть поля первого класса",
        "Просмотреть поля второго класса",
        "Изменить поле первого класса",
        "Изменить поле второго класса",
        "Очистить первую очередь",
        "Очистить вторую очередь",
        "Удалить первый класс",
        "Удалить второй класс",
        "Выйти из программы"
    };
    list_header* header = NULL;
    for (uint _i = 0; _i < 4294967295; _i++) {
        header = create_empty_list();
        for (uint _j = 0; _j < rand()%999 + 1; _j++)
            add_new_item_to_list(header, create_student_from_data("IS21-3", "Kontarev VadimV", rand()%65535, rand()%2, rand()%65535, rand()%65535));

        delete_list(header);
    }
    return 0;
}
