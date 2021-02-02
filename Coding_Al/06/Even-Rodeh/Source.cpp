#include "Header.h";

int main()
{
    system("chcp 1251");  // ��������� �� ������� ���� � �������
    system("cls");
    loop_test();
    unsigned input;
    cout << "������� ����� ������������� �����, ������� �� ������� ����������: \n\t\t";
    cin >> input;
    cout << "\n�������������� ���������:\n";
    string code = to_even_rodeh(input);
    cout << "\t\t" << code << "\n\n";
    cout << "�������������� �������������� ���������:\n";
    unsigned decode = decode_even_rodeh(code);
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

string to_even_rodeh(unsigned num)
{
    switch (num)
    {
    case 0:
        return "000";
    case 1:
        return "001";
    case 2:
        return "010";
    case 3:
        return "011";
    }
    vector <bool> bin_num = to_binary(num);
    vector <bool> code;
    code.push_back(false); // ����������� � ����� 0
    while (bin_num.size() != 3)
    {
        for (int counter = 0; counter < bin_num.size(); counter++) // ����������� �������� ������������� ������ ����� �����
            code.insert(code.begin(), bin_num[counter]);
        bin_num = to_binary(bin_num.size());
    }
    for (int counter = 0; counter < bin_num.size(); counter++)    // ����������� �������� ������������� ������ ������ ����� �����,�� ���� ���� �� �� ��������� 
        code.insert(code.begin(), bin_num[counter]);
    string to_string;
    for (int counter = 0; counter < code.size(); counter++)      // ��������� � ������
        to_string += (int)code[counter] + '0';
    return to_string;
}

unsigned decode_even_rodeh(string code)
{
    if (code == "000")
        return 0;
    else if (code == "001")
        return 1;
    else if (code == "010")
        return 2;
    else if (code == "011")
        return 3;
    unsigned num = 3;
    code = code.substr(0,code.size()-1); // ������� ��������� 0 pop_back() � string � �++11 ���
    while (code.size())
    {
        string current_code = code.substr(0, num);
        for (int counter = 0; counter < num; counter++)
            code.erase(code.begin());
        num = to_dec(current_code);
    }
    return num;
}

void loop_test()
{
    for (int counter = 1; counter <= 100; counter++)
    {
        if (counter == decode_even_rodeh(to_even_rodeh(counter)))
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