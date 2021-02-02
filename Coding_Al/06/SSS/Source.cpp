// ������ �������� ������� 3�� ����� ���� ��. �. �. ������� ������� �.�.
// ����� ��������� 3 ���� 10 �����
// ������ ��������� ��������� ��������� sss-����������� � sss-�������������.
// ���������� mingw-5.2.0

#include "header.h"

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
// ������� ������� ����� � ���������� ������� ���������
unsigned to_dec(string bin)
{
    unsigned res = 0;
    for (int counter = 0; counter < bin.size(); counter++)
    {
        res += (bin[bin.size() - counter - 1] - '0') * pow(2, counter);
    }
    return res;
}

string to_sss(unsigned i, unsigned j,  unsigned k, unsigned num)
{
    vector<bool> code;
    unsigned min_value = 0; // ����������� ����� �������� ���������
    unsigned max_value = 0; // ������������ ����� �������� ���������
    unsigned num_of_range = 0;
    unsigned c_i = i; // �������� �������� i
    cout << "����� ����� ��� ������ ���������� i,j,k:\n\n";
    for (i; i <= k; i += j, num_of_range++)
    {
        min_value = max_value + 1;
        max_value += pow(2, i);
        // �������� ����� ����������� ��� ������ i,j,k
        string scheme_codes;
        // ����������� �������� ���� n-1�� �����, �������
        for (int counter = 0; counter < num_of_range; counter++)
            scheme_codes += '1';

        scheme_codes += '0'; // ������� 0
        for (int counter = 0; counter < i; counter++) // �������� �������������, ��������
            scheme_codes += 'x';
        cout << scheme_codes << "\n";
        
        // �������� �����, ���� ��� ������ � ������� ��������
        if (num <= max_value)
        {
            // ����������� �������� ���� n-1�� �����, �������
            for (int counter = 0; counter < num_of_range; counter++)
                code.push_back(1);
            code.push_back(0);
            vector<bool> mantis; // ��������
            mantis = to_binary(num - min_value);
            if (mantis.size() < c_i + (num_of_range)*j)
            {
                for (int counter = 0; counter < (c_i + (num_of_range)*j - mantis.size()); counter ++)
                {
                    // �������� ������������� �������� ����� ������ ������ ������, � �� �����, ��� ���������� ���� ����� �������
                    // ����� ������� ����� ���������� 0-�� ����� � ���, � �� � ��������.
                    code.push_back(0);
                }
            }
            else
                mantis.resize(c_i + (num_of_range) * j);
            for (int counter = mantis.size() - 1; counter >= 0; counter--)
                code.push_back(mantis[counter]);
            string to_string;
            for (int counter = 0; counter < code.size(); counter++)// ��������� � ������
                to_string += (int)code[counter] + '0';
            return to_string;
        }
    }
}

unsigned decode_sss(unsigned i, unsigned j, string code)
{
    string mantis;
    int unar = 0;
    unsigned result;
    while (code[0] !=  '0')
    {
        unar++;
        code.erase(code.begin());
    }
    code.erase(code.begin()); // ��������� ������� �������������
    unar++; // ���������� � ����������� ���������� �������, ��������� ��������� �� n
    int left_bound = 1;
    for (int counter = 0; counter < unar - 1; counter++) // unar - 1, ������ ��� ������ �������� ���������� �������������� ������� 1
        left_bound += pow(2, i + j * counter);
    for (int counter = 0; counter < (i + (unar - 1) * j); counter++)
        mantis += code[counter];
    result = to_dec(mantis) + left_bound;
    return result;
}

void loop_test()
{
    unsigned i = 3; 
    unsigned j = 2;
    unsigned k = 11; // ��������� sss-�����������
    for (int counter = 1; counter <= 100; counter++)
    {
        if (counter == decode_sss(i, j, to_sss(i, j, k, counter)))
            {
            cout << counter << " -> decode_sss(" << i << ", " << j << ", to_sss(" << i << ", " << j << ", " << k << ")) == " << counter;
                cout << "\nTEST TRUE\n\n";
            }
            else
            {
                cout << "\nTEST FALSE\n\n";
            }
    }
}

int main()
{
    unsigned i,j,k, num;
    system("chcp 1251");  // ��������� �� ������� ���� � �������
    system("cls");
    loop_test();
    cout << "\t\t\t\t\t������� ��������� SSS �����������:\n";
    cout << "������� i: ";
    cin >> i;
    cout << "\n������� j: ";
    cin >> j;
    cout << "\n������� k: ";
    cin >> k;
    cout << "\n\t\t\t\t\t������� �����, ������� ������� ������������:\n";
    cin >> num;
    cout << "\n\t\t\t\t\t�������������� ���������:\n";
    string code = to_sss(i, j, k, num);
    cout << "\t\t" << code << "\n\n";
    cout << "�������������� �������������� ���������:\n";
    unsigned decode = decode_sss(i, j, code);
    cout << "\t\t" << decode << "\n\n";
    if (num == decode) cout << "�������� ��������� ������� c ��������������!\n\n";
    else cout << "�������� ��������� �� ������� c ��������������!\n\n";
    system("pause");
    return 0;
}
