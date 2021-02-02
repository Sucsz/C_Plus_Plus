// ������ �������� ������� 3�� ����� ���� ��. �. �. ������� ������� �.�.
// ����� ��������� 15 �����
// ������ ��������� ��������� ��������� ����������� � ������������� ���� ���� 
// ���������� mingw-5.2.0

#include "Header.h"
int main()
{
    system("chcp 1251");  // ��������� �� ������� ���� � �������
    system("cls");
    cout << "\t\t������������:\n";
    tests();
    unsigned input;
    cout << "\t\t��������:\n";
    cout << "������� �����, ������� �� ������� ����������: \n\t\t";
    cin >> input;
    string bin = to_binary(input);
    cout << "�������� �������������" << bin << '\n';
    unsigned gray = bin_to_gray(input);
    cout << "��� ����: " << to_binary(gray) << '\n';
    cout << "\n�������������� �������������� ���������:\n";
    unsigned decode = gray_to_bin(gray);
    cout << "\t\t" << to_binary(decode) << "\n\n";
    if (input == decode)
        cout << "�������� ����� ������� c ��������������!\n\n";
    else
        cout << "�������� ����� �� ������� c ��������������!\n\n";
    system("pause");

    return 0;
}

unsigned bin_to_gray(unsigned num)
{
    return num ^ (num >> 1);
}

unsigned gray_to_bin(unsigned num)
{
    for (int counter = 0; (1 << counter) < floor(log2(num)) + 1; counter++)
        num ^= num >> (1 << counter);
    return num;
}

string to_binary(unsigned num)
{
    vector<bool> result;
    while (num)
    {
        result.insert(result.begin(), num % 2);
        num /= 2;
    }
    string to_string;
    for (int counter = 0; counter < result.size(); counter++)  // ��������� � ������
        to_string += (int)result[counter] + '0';
    return to_string;
}

void tests()
{
    int stop = 100;
    for (unsigned counter = 0; counter < stop; counter++)
        if (to_binary(gray_to_bin(bin_to_gray(counter))) != to_binary(counter))
            cout << "TEST FALSE\n";
        else
        {
            cout << "TEST TRUE\n";
        }
}
