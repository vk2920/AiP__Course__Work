#pragma once

/// <summary>
/// ������� ��� ��������� �������� ����������� ����
/// ��� ������ �������� ����� ��������� ������ � �������
/// </summary>
/// <returns>��������� ���� int*, � �������� �� ��� ����� (��� ������, ����� ��������, ����� �����)</returns>
int* get_size();

/// <summary>
/// ������� ��� ������������ �����, ���������� �������� _getch()
/// </summary>
/// <returns>������ 0</returns>
int test_input();

/// <summary>
/// ������� ��� ���������� ���� ������� ������� (��� �������)
/// </summary>
/// <param name="_menu">������ ��������� ����</param>
/// <param name="_mic">����� ��������� ����</param>
/// <param name="_exit_code">���, ������� ����� ������� ��� ������ �� ���������</param>
/// <returns>������ ���������� ������ ����</returns>
int select_from_menu(const char** _menu, const int _mic, int _exit_code);

/// <summary>
/// ������� ��� ����� ������, ����������� � �������������� WinAPI.
/// ������ ������� ���� � ������� ��� ����� ��������� ����������.
/// ������������ ������������� ���������� ����� �������� � ������� ������ �� ������������ ������� ������
/// </summary>
/// <param name="_headers">������������ ��������� ������</param>
/// <param name="_items_count">���������� �����, ��������������� ����� ������������ ����</param>
/// <param name="_res">�������� ����������. ����������� NULL ��� ���������� ����� ������</param>
/// <returns>��������� �� ��������� ���� char**, � �������� �������� ���������� �� ������������ ������</returns>
char** enter_data(const char** _headers, const int _items_count, char** _res);

/// <summary>
/// � ����������.
/// ������� ��� ���������� ������ ����
/// </summary>
/// <param name="_menu_item_list">������ ��������� ����</param>
/// <param name="_menu_items_count">����� ��������� ����</param>
/// <param name="_exit_answer">���, ������� ����� ������� ��� ������ �� ���������</param>
/// <returns>������ ���������� ������ ����</returns>
int menu_new(const char** _menu_item_list, const int _menu_items_count, const int _exit_answer);
