// 5 �����
#include "Header.h"

int main()
{
    system("chcp 1251");  // ��������� �� ������� ���� � �������
    system("cls");
    loop_test();
    unsigned input, param;
    cout << "������� ����� ������������� �����, ������� �� ������� ����������: \n\t\t";
    cin >> input;
    cout << "������� ���� �������������� �����, �������� ����������������� ���� �������\n\t\t";
    cin >> param;
    cout << "\n�������������� ���������:\n";
    string code = to_exp_golomb(input, param);
    cout << "\t\t" << code << "\n\n";
    cout << "�������������� �������������� ���������:\n";
    unsigned decode = decode_exp_golomb(code, param);
    cout << "\t\t" << decode << "\n\n";
    if (input == decode) cout << "�������� ��������� ������� c ��������������!\n\n";
    else cout << "�������� ��������� �� ������� c ��������������!\n\n";
    //system("pause");
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
string to_exp_golomb(unsigned num, unsigned param)
{
    vector <bool> bin_num = to_binary(num);
    vector <bool> code;
    string to_string;
    int w = 1 + floor(num / pow(2, param));
    int f = floor(log2(1 + num / pow(2, param)));
    for (int counter = 0; counter < f; counter++)
        code.push_back(true);
    code.push_back(false); // �������� ������� ������������� f
    vector <bool> bin_w = to_binary(w);
    bin_w.resize(f); // ������������ ���������� ����� �� f
    for (int counter = bin_w.size() - 1; counter >= 0; counter--) // ���������� ����
        code.push_back(bin_w[counter]);
    // ����������� ������ �������� ��� num
    // ������� �������� k ���
    bin_num.resize(param); //������������ ���������� ����� �� param
    for (int counter = bin_num.size() - 1; counter >= 0; counter--)
        code.push_back(bin_num[counter]);
    for (int counter = 0; counter < code.size(); counter++)      // ��������� � ������
        to_string += (int)code[counter] + '0';
    return to_string;
}
// ������� ����������������� ���� ������� � ���������� �������������
unsigned decode_exp_golomb(string code, unsigned param)
{
    string decode;
    if (code[0] == '0')
    {
        for (int counter = 1; counter <= param; counter++)
            decode += code[counter];
        return(to_dec(decode));

    }
    int unar_f = 0;
    string w;
    // �����
    while (code[0] != '0')
    {
        unar_f++;
        code.erase(code.begin());
    }
    code.erase(code.begin()); // ���������� �� �������� ������������� f
    w += '1'; // ��������� ����� 1
    int temp = 0;
    for (int counter = 0; counter < unar_f; counter++)
    {
        temp++;
        w += code[counter];
    }
    for (int counter = 0; counter < temp; counter++) // ���������� �� ����� ����������� �����
    {
        code.erase(code.begin());
    }
    unsigned num_w = to_dec(w);
    num_w -= 1;
    num_w = num_w << param;
    vector <bool> n_l; // ������� ���� ����� n
    for (int counter = 0; counter < param; counter++) // ������ param ����� ��������� �����
    {
        n_l.push_back((code[counter]) - '0');
    }
    vector <bool> w_bin = to_binary(num_w);
    unsigned res = 0;
    string to_string;
    for (int counter = w_bin.size() - 1; counter >= 0; counter--)      // ��������� � ������
        to_string += (int)w_bin[counter] + '0';

    res += to_dec(to_string);
    to_string = "";
    for (int counter = 0; counter < n_l.size(); counter++)      // ��������� � ������
        to_string += (int)n_l[counter] + '0';
    res += to_dec(to_string);
    return(res);
}
void loop_test()
{
    for (int counter = 0; counter <= 10; counter++)
    {
        for (int counter2 = 1; counter2 <= 8; counter2++)
        {
            if (counter == decode_exp_golomb(to_exp_golomb(counter, counter2), counter2))
            {
                cout << counter << " -> decode_exp_golomb(to_exp_golomb(" << counter << ")," << counter2 << ") = " << counter;
                cout << "\nTEST TRUE\n\n";
            }
            else
            {
                cout << "\nTEST FALSE\n\n";
            }
        }
    }
}