// 5 ����� m <= 8
#include "Header.h"

int main()
{
    system("chcp 1251");  // ��������� �� ������� ���� � �������
    system("cls");
    loop_test();
    unsigned input, param;
    cout << "������� ����� ������������� �����, ������� �� ������� ����������: \n\t\t";
    cin >> input;
    cout << "������� ���� �������������� �����, �������� ���� �����\n\t\t";
    cin >> param;
    cout << "\n�������������� ���������:\n";
    string code = to_rayas(input, param);
    cout << "\t\t" << code << "\n\n";
    cout << "�������������� �������������� ���������:\n";
    unsigned decode = decode_rayas(code, param);
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
string to_rayas(unsigned num, unsigned param)
{
    param = pow(2, param);
    vector <bool> bin_num = to_binary(num);
    vector <bool> code;
    string to_string;

    // ���������� ������� ��� num / param
    for (int counter = 0; counter < num / param; counter++)
        code.push_back(1);
    code.push_back(0);
    // ���������� ������ �������� ��� num % param, ������� �������� log2(param) ���
    bin_num = to_binary(num % param);
    bin_num.resize(log2(param));
    for (int counter = bin_num.size() - 1; counter >= 0; counter--)
        code.push_back(bin_num[counter]);

    for (int counter = 0; counter < code.size(); counter++)      // ��������� � ������
        to_string += (int)code[counter] + '0';
    return to_string;
}
// ������� ���� ����� � ���������� �������������
unsigned decode_rayas(string code, unsigned param)
{
    param = pow(2, param);
    int n_div_param = 0; // n - decode num
    vector <vector<string>> huffman_codes; // ���������� ����� ��������, ��� ������� ����� ���������
    vector<string> code_0; code_0.push_back("#"); //� ������ ��������� ����� ������, ��� ��� ������� ���� - �������� ������� ������ => ������� ������
    vector<string> code_1; code_1.push_back("0");
    vector<string> code_2; code_2.push_back("1"); code_2.push_back("0");
    vector<string> code_3; code_3.push_back("0"); code_3.push_back("10"); code_3.push_back("11");
    vector<string> code_4; code_4.push_back("00"); code_4.push_back("01"); code_4.push_back("10"); code_4.push_back("11");
    vector<string> code_5; code_5.push_back("00"); code_5.push_back("01"); code_5.push_back("10"); code_5.push_back("110"); code_5.push_back("111");
    vector<string> code_6; code_6.push_back("00"); code_6.push_back("01"); code_6.push_back("100"); code_6.push_back("101"); code_6.push_back("110"); code_6.push_back("111");
    vector<string> code_7; code_7.push_back("00"); code_7.push_back("010"); code_7.push_back("011"); code_7.push_back("100"); code_7.push_back("101"); code_7.push_back("110"); code_7.push_back("111");
    vector<string> code_8; code_8.push_back("000"); code_8.push_back("001"); code_8.push_back("010"); code_8.push_back("011"); code_8.push_back("100"); code_8.push_back("101"); code_8.push_back("110"); code_8.push_back("111");
    huffman_codes.push_back(code_0); huffman_codes.push_back(code_1); huffman_codes.push_back(code_2); huffman_codes.push_back(code_3);
    huffman_codes.push_back(code_4); huffman_codes.push_back(code_5); huffman_codes.push_back(code_6); huffman_codes.push_back(code_7);
    huffman_codes.push_back(code_8);
    while (code[0] != '0')
    {
        code.erase(code.begin());
        n_div_param++;
    }
    int n_mod_param = 0;
    code.erase(code.begin()); // ���������� �� �������� ������������� num div m
     // �������� param �� ������� ������
        int c_l2_p = (int)ceil(log2(param));
        code.resize(c_l2_p);
        n_mod_param = to_dec(code);
        return n_div_param * param + n_mod_param;
}
void loop_test()
{
    for (int counter = 0; counter <= 10; counter++)
    {
        for (int counter2 = 1; counter2 <= 8; counter2++)
        {
            if (counter == decode_rayas(to_rayas(counter, counter2), counter2))
            {
                cout << counter << " -> decode_rayas(to_rayas(" << counter << ")," << counter2 << ") = " << counter;
                cout << "\nTEST TRUE\n\n";
            }
            else
            {
                cout << "\nTEST FALSE\n\n";
            }
        }
    }
}