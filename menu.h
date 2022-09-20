#pragma once

/// <summary>
/// Функция для получения размеров консольного окна
/// Код выхода является кодом последней ошибки в функции
/// </summary>
/// <returns>Указатель типа int*, с массивом из трёх чисел (код выхода, число столбцов, число строк)</returns>
int* get_size();

/// <summary>
/// Функция для исследования кодов, получаемых функцией _getch()
/// </summary>
/// <returns>Всегда 0</returns>
int test_input();

/// <summary>
/// Функция для реализации меню старого образца (две колонки)
/// </summary>
/// <param name="_menu">Список элементов меню</param>
/// <param name="_mic">Число элементов меню</param>
/// <param name="_exit_code">Код, который нужно вернуть для выхода из программы</param>
/// <returns>Индекс выбранного пункта меню</returns>
int select_from_menu(const char** _menu, const int _mic, int _exit_code);

/// <summary>
/// Функция для ввода данных, реализуется с использованием WinAPI.
/// Создаёт большое окно в консоли для ввода строковых параметров.
/// Некорректное использование параметров может привести к попытке чтения из невыделенной области памяти
/// </summary>
/// <param name="_headers">Наименования требуемых данных</param>
/// <param name="_items_count">Количество строк, соответствующее числу наименований выше</param>
/// <param name="_res">Значения параматров. Используйте NULL для первичного ввода данных</param>
/// <returns>Указатель на указатели типа char**, в областях хранятся полученные от пользователя строки</returns>
char** enter_data(const char** _headers, const int _items_count, char** _res);

/// <summary>
/// В разработке.
/// Функция для реализации нового меню
/// </summary>
/// <param name="_menu_item_list">Список элементов меню</param>
/// <param name="_menu_items_count">Число элементов меню</param>
/// <param name="_exit_answer">Код, который нужно вернуть для выхода из программы</param>
/// <returns>Индекс выбранного пункта меню</returns>
int menu_new(const char** _menu_item_list, const int _menu_items_count, const int _exit_answer);
