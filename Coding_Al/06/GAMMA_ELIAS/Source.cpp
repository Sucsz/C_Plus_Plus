//10 �����
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
    string code = to_gamma_elias(input);
    cout << "\t\t" << code << "\n\n";
    cout << "�������������� �������������� ���������:\n";
    unsigned decode = decode_gamma_elias(code);
    cout << "\t\t" << decode << "\n\n";
    if (input == decode) cout << "�������� ��������� ������� c ��������������!\n\n";
    else cout << "�������� ��������� �� ������� c ��������������!\n\n";
    system("pause");
    return 0;
}
// ������� ��������� ����� � �������� ������� ���������
vector<bool> to_binary(unsigned num)
{
    vector<bool> res;
    while (num)
    {
        res.push_back(num % 2);
        num /= 2;
    }
    return res;
}
// ������� ��������� ����� � ���������� ������� ���������
unsigned to_dec(string bin)
{
    unsigned res = 0;
    for (int counter = 0; counter < bin.size(); counter++)
    {
        res += (bin[bin.size() - counter - 1] - '0') * pow(2, counter);
    }
    return res;
}
// ������� ����� � ��� �����-�������
string to_gamma_elias(unsigned num)
{
    vector <bool> bin_num = to_binary(num);
    vector <bool> code;
    string to_string;
    for (int counter = 0; counter < bin_num.size() - 1; counter++)
    {
        code.push_back(false);  // ������ �������� ���� ����� ����������� ����������� ����� �����, � ������ ���������� ��������� �������������, ����� ���������� ������
                                // ��� ����� ������� ������� ��� � ������ �������� �������������
    }
    // ���������� �������� ������������� �����
    for (int counter = bin_num.size() - 1; counter >= 0; counter--)
        code.push_back(bin_num[counter]); // ��� ����� � �������� ������� ������, ��� ����� ��� ����������� �������� � �������� �������

    for (int counter = 0; counter < code.size(); counter++)      // ��������� � ������
        to_string += (int)code[counter] + '0';
    return to_string;
}
// ������� ���� �����-������ � ���������� �������������
unsigned decode_gamma_elias(string code)
{
    while (code[0] == '0') //������� ���� �������� ������������� 
    {
        code.erase(code.begin());
    }
    unsigned decode = to_dec(code);
    return decode;
}
void loop_test()
{
    for (int counter = 1; counter <= 100; counter++)
    {
        if (counter == decode_gamma_elias(to_gamma_elias(counter)))
        {
            cout << counter << " -> decode_gamma_elias(to_gamma_elias(" << counter << ")) = " << counter;
            cout << "\nTEST TRUE\n\n";
        }
        else
        {
            cout << "\nTEST FALSE\n\n";
        }
    }
}