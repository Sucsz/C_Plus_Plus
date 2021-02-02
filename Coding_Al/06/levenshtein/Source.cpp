#include "Header.h"

int main()
{
    system("chcp 1251");  // ��������� �� ������� ���� � �������
    system("cls");
    loop_test();
    unsigned input;
    cout << "������� ����� ��������������� �����, ������� �� ������� ����������: \n\t\t";
    cin >> input;
    cout << "\n�������������� ���������:\n";
    string code = to_levenshtein(input);
    cout << "\t\t" << code << "\n\n";
    cout << "�������������� �������������� ���������:\n";
    unsigned decode = decode_levenshtein(code);
    cout << "\t\t" << decode << "\n\n";
    if (input == decode) cout << "�������� ��������� ������� c ��������������!\n\n";
    else cout << "�������� ��������� �� ������� c ��������������!\n\n";
    system("pause");
	return 0;
}
// ������� ��������� ����� � �������� ������� ���������, ����� ������� ������ �������.
vector<bool> to_binary_sub(unsigned num)
{
    vector<bool> res;
    while (num)
    {
        res.push_back(num % 2);
        num /= 2;
    }
    res.pop_back(); // ��������� ������� - ���� ������ � �������� �������������
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
string to_levenshtein(unsigned num)
{
    // ���� ���������� ����� ���� 3999999999 ������������ �������� decode_levenshtein �� �� ���������
    if (num == 0) return "0";
    vector <bool> bin_num = to_binary_sub(num);
    vector <bool> code; // ���������� � ������ ���� bin' �� num �� �����, �.�. ���� ������ ������ �� ��������� num
    vector <bool> copy_bin_num(bin_num);
    unsigned count = 1;
    while (copy_bin_num.size())
    {
        for (int counter = 0; counter < copy_bin_num.size(); counter++)
            code.insert(code.begin(), copy_bin_num[counter]); // ��������� � ������ ���� bin' �� ���������� bin_num
        copy_bin_num = to_binary_sub(copy_bin_num.size());
        count++;
    }
    code.insert(code.begin(), false); // ���������  0 � ������;
    for (int counter = count; counter > 0; counter--) // ��������� count 1 � ������ ����
        code.insert(code.begin(), true);
    string to_string;
    for (int counter = 0; counter < code.size(); counter++)  // ��������� � ������
        to_string += (int)code[counter] + '0';
    return to_string;
}
unsigned decode_levenshtein(string code)
{
    // ���������� �� 11111000011111111111111111111111111111111111 ������������ 3999999999
    if (code == "0") return 0;
    unsigned c = 0; // ������� ������
    while (code[0] != '0')
    {
        c++;
        code.erase(code.begin()); // �������� �� 1
    }
    code.erase(code.begin()); // �������� �� ����
    unsigned n = 1;
    unsigned p = c - 1;
    string decode;
    while (p)
    {
        for (int counter = 0; counter < n; counter++)
        {
            decode += code[counter];
        }
        for (int counter = 0; counter < n; counter++)
        {
            code.erase(code.begin());
        }
        decode.insert(decode.begin(), '1');
        unsigned z = to_dec(decode);
        n = z;
        decode = "";
        p--;
    }
    return n;
}
void loop_test()
{
    for (int counter = 0; counter <= 100; counter++)
    {
        if (counter == decode_levenshtein(to_levenshtein(counter)))
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
