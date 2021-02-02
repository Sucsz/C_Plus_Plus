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
    string code = to_gam_lev(input);
    cout << "\t\t" << code << "\n\n";
    cout << "�������������� �������������� ���������:\n";
    unsigned decode = decode_gam_lev(code);
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

string to_gam_lev(unsigned num)
{
    vector <bool> bin_num = to_binary(num);
    vector <bool> code;
    for (int counter = 0; counter < bin_num.size() - 1; counter++) // ��� ���� �����, ����� ���������� ����������� 0
    {
        code.push_back(false);
        code.push_back(bin_num[counter]); // �.�. bin_num - ��� ����������, ���� ���� � 0�� ��������, �� ��������� �� ���������
    }
    code.push_back(bin_num[bin_num.size() - 1]); // ����������� ��������� ���
    string to_string;
    for (int counter = 0; counter < code.size(); counter++)  // ��������� � ������
        to_string += (int)code[counter] + '0';
    return to_string;
}

unsigned decode_gam_lev(string code)
{
    string decode;
    for (int counter = code.size() - 2; counter > 0; counter -= 2)
    {
        decode += code[counter];
    }
    decode.insert(decode.begin(), '1');
    unsigned result = to_dec(decode);
    return result;
}

void loop_test()
{
    for (int counter = 1; counter <= 100; counter++)
    {
        if (counter == decode_gam_lev(to_gam_lev(counter)))
        {
            cout << counter << " -> decode_levenshtein(to_levenshtein(" << counter << ")) = " << counter;
            cout << "\nTEST TRUE\n\n";
        }
        else
        {
            cout << "\nTEST FALSE\n\n";
        }
    }
}
