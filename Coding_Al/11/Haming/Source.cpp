// ������ �������� ������� 3�� ����� ���� ��. �. �. ������� ������� �.�.
// ����� ��������� 5 �����
// ������ ��������� ��������� ��������� �����������, ����������� ������ � ������������� ����� ������� 

#include "Header.h"

int main()
{
    system("chcp 1251");  // ��������� �� ������� ���� � �������
    system("cls");
    loop_tests();
    unsigned input;
    cout << "������� ����� ��������������� �����, ������� �� ������� ����������: \n\t\t";
    cin >> input;
    string code(to_haming(input));
    cout << "\n�������������� ���������: " << code << endl;
    cout << "\n�������� ��������� �������\n";
    string wrong_code = do_wrong_code(code);
    cout << "\n��������� ��� ������: " << code << "\n\n��������� � �������: " << wrong_code;
    string fix_code(fix_wrong(wrong_code));
    cout << "\n\n������������ ���������: " << fix_code;
    unsigned decode = decode_ham(fix_code);
    cout << "\n\n�������������� ������������ ���������: " << decode;
    if (input == decode) cout << "\n\n�������� ��������� ������� c ��������������!\n\n";
    else cout << "\n\n�������� ��������� �� ������� c ��������������!\n\n";
    system("pause");
    return 0;
}

// ������� ��������� ����� � �������� ������� ���������
vector<bool> to_binary(unsigned num)
{
    vector<bool> res;
    while (num)
    {
        res.insert(res.begin(), num % 2);
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

string to_haming(unsigned num)
{
    // ������� ��������� �� ���� ����� ������������� ����� � ���������� ������ - ��� �������
    vector<bool> bin = to_binary(num);
    unsigned m = bin.size(); // ����� ��������� �����
    unsigned l = m; // ����� �������� �����
    while (pow(2, m) > pow(2, l) / (l + 1))
        l++;
    // cout << l << ' ' << m << '\n'; ������ ��� �������� l m 
    unsigned k = l - m; // ������� ���� �������� � ��������� �����.
    for (int counter = 0; counter < k; counter++)
        bin.insert(bin.begin() + pow(2, counter) - 1, 0); // ��������� �������� ������������� ����� ������������ ������ �� ��������� 0
    for (int counter = 0; counter < bin.size(); counter++)
    {
        if (counter == 0 || ((counter + 1) & (counter)) == 0) // �������� �� ������� 2��, 0 - ������ ������
        {
            unsigned group_size = counter + 1;
            unsigned number_ones = 0;
            for (int counter2 = counter; counter2 < bin.size(); counter2++)
            {
                if (group_size)
                {
                    group_size--;
                    if (bin[counter2])
                        number_ones++;
                    continue;
                }
                group_size = counter + 1;
                counter2 += group_size - 1;
            }
            //cout << number_ones << "|\n"; ������ ��� �������� ���������� ������ ����� ������������ ����
            if (number_ones % 2 != 0)
                bin[counter] = 1;
        }
        else
            continue;
    }
    string to_string;
    for (int counter = 0; counter < bin.size(); counter++)  // ��������� � ������
        to_string += (int)bin[counter] + '0';
    return to_string;
}

string do_wrong_code(string code)
{
    // ������� ��������� �� ���� ������ - ��� ������� � ��������� � ��� ���� ������-��������� ������. ���������� ������ � �������.
    srand((unsigned int)time(NULL));
    unsigned num_sybmol = rand() % code.size();
    cout << "\n������ �������� � ������� �����:" << num_sybmol << '\n';
    code[num_sybmol] = !(code[num_sybmol] - '0') + '0';
    return code;
}

string fix_wrong(string wrong_code)
{
    // ������� ��������� �� ���� ������ - ��� �������, � ���������� � ��� �������, � ���������� ������ - ������������ ��� �������.
    string copy_wrong_code = string(wrong_code);
    int position = 0; // ������� ������
    for (int counter = 0; counter < wrong_code.size(); counter++) // �������� ����������� ����
        if (counter == 0 || ((counter + 1) & (counter)) == 0)
            copy_wrong_code[counter] = '0';
    for (int counter = 0; counter < copy_wrong_code.size(); counter++) // ��������������� ����������� ����
    {
        if (counter == 0 || ((counter + 1) & (counter)) == 0) // �������� �� ������� 2��, 0 - ������ ������
        {
            unsigned group_size = counter + 1;
            unsigned number_ones = 0;
            for (int counter2 = counter; counter2 < copy_wrong_code.size(); counter2++)
            {
                if (group_size)
                {
                    group_size--;
                    if (copy_wrong_code[counter2] - '0')
                        number_ones++;
                    continue;
                }
                group_size = counter + 1;
                counter2 += group_size - 1;
            }
            //cout << number_ones << "|\n"; ������ ��� �������� ���������� ������ ����� ������������ ����
            if (number_ones % 2 != 0)
                copy_wrong_code[counter] = '1';
        }
        else
            continue;
    }
    for (int counter = 0; counter < copy_wrong_code.size(); counter++)
    {
        if (counter == 0 || ((counter + 1) & (counter)) == 0) // �������� �� ������� 2��, 0 - ������ ������
            if (copy_wrong_code[counter] != wrong_code[counter])
                position += counter + 1; // ��� ���������� ������, ������ ��� �� ���� �� ����, � �� �� �������, ��� ����� ���������, � �������, ������ � ������ �������
                                         // �� ������� ������� ������, ��� � �������. |0+1 = 1| |1 + 2 = 2|
        continue;
    }
    position -= 1; // � ��� �� �������� �������, ����� ������� � ������� �� ����.
    wrong_code[position] = !(wrong_code[position] - '0') + '0'; // ����������� ������
    return wrong_code;
}

unsigned decode_ham(string code)
{
    // ������� ��������� �� ���� ������ - ��� �������, ���������� ����� ������������� �����
    string decode;
    for (int counter = 0; counter < code.size(); counter++) // ������� ����������� ����
    {
        if (!(counter == 0 || ((counter + 1) & (counter)) == 0)) // �������� �� ������� 2��, 0 - ������ ������
        {
            decode += code[counter];
        }
    }
    return to_dec(decode);
}

void loop_tests()
{
    int stop = 100;
    for (int counter = 1; counter < stop; counter++)
    {
        string code(to_haming(counter));
        string wrong_code = do_wrong_code(code);
        string fix_code(fix_wrong(wrong_code));
        unsigned decode = decode_ham(fix_code);
        if (counter == decode)
            cout << "\nTEST TRUE\n";
        else
            cout << "\nTEST FALSE\n";
    }
}