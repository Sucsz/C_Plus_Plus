// ������ �������� ������� 3�� ����� ���� ��. �. �. ������� ������� �.�.
// ����� ��������� 15 �����
// ������ ��������� ��������� ��������� sss-����������� � sss-�������������.
// ���������� mingw-5.2.0

#include "Header.h"

int main()
{
    system("chcp 1251");  // ��������� �� ������� ���� � �������
    system("cls");
    loop_test();
    unsigned input;
    cout << "������� ����� ������������� �����, ������� �� ������� ����������: \n\t\t";
    cin >> input;
    cout << "\n�������������� ���������:\n";
    string code = to_fib_code(input);
    cout << "\t\t" << code << "\n\n";
    cout << "�������������� �������������� ���������:\n";
    unsigned decode = decode_fib_code(code);
    cout << "\t\t" << decode << "\n\n";
    if (input == decode) cout << "�������� ��������� ������� c ��������������!\n\n";
    else cout << "�������� ��������� �� ������� c ��������������!\n\n";
    system("pause");
    return 0;
}
// ������� �� 10-����� ������� ��������� � ���������, ������ ����� �������
vector<bool> to_fib(unsigned long long number)
{
    
    // ������ ������� ��������� �� ���� ���������� ����� � ������� ��� � ������� ��������� ���������
    // ��������� �������� � ���� ����������� �����, ��� ����� � �������� - ���� ������ ������ ����� ������ ����� � ������� ��������� ���������
    unsigned long long fib_number = 0;
    vector<bool> result;
    while (number)
    {
        unsigned long long int a = 1; // ���������� ����� ���������
        unsigned long long int b = 1; // �������� ����� ���������
        unsigned long long int j = 1; // ������� �������� ��������� ����� ���������
        while (b <= number)
        {
            a = a ^ b;                // ������ ���������� ��� �������������� ����������
            b = b ^ a;
            a = a ^ b;
            b += a;
            j *= 10;
        }
        // ����� ����� �� ����� ���������� ����� ��������� ��� ���������
        number -= a;
        fib_number += j == 1 ? 1 : j / 10; // ������������� ������������� ��������� ������ ����������� if else
                                           // ������������ �������� if (j == 1) {fib_number += 1} else {fib_number += j / 10}
                                           // j / 10 - ��� "��������������" �������� ��������, ��������� ��������� 1 � ������ �����
    }
    while (fib_number)
    {
        result.push_back(fib_number % 10);
        fib_number /= 10;
    }
    return result;
}

string to_fib_code(unsigned long long num)
{
    vector<bool> code = to_fib(num);
    code.push_back(1); //��������� ����������� �������
    string to_string;
    for (int counter = 0; counter < code.size(); counter++)      // ��������� � ������
        to_string += (int)code[counter] + '0';
    return to_string;
}

unsigned decode_fib_code(string code)
{
    unsigned long long res = 0;
    code.erase(code.end()-1); // ������� ����������� �������
    unsigned long long int a = 1;  // ���������� ����� ��������� (�������� ��������� �������)
    unsigned long long int b = 1;  // �������� ����� ��������� 
    for (int counter = 0; counter < code.size(); counter++)
    {
        res += ((code[counter] - '0') * b);
        a = a ^ b;                // ������ ���������� ��� �������������� ����������
        b = b ^ a;
        a = a ^ b;
        b += a;

    }
    return res;

}

void loop_test()
{
    for (int counter = 1; counter <= 100; counter++)
    {
        if (counter == decode_fib_code(to_fib_code(counter)))
        {
            cout << counter << " -> decode_fib_code(to_fib_code(" << counter << ")) = " << counter;
            cout << "\nTEST TRUE\n\n";
        }
        else
        {
            cout << "\nTEST FALSE\n\n";
        }
    }
}