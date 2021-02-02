// ������ �������� ������� 3�� ����� ���� ��. �. �. ������� ������� �.�.
// ����� ��������� 3 ����
// ������ ��������� ��������� ��������� ����������� � ������������� LZ77 
// ���������� mingw-5.2.0, ���������� ������������ ���� -std=gnu++11

#include "Header.h"
int main()
{
    system("chcp 1251");  // ��������� �� ������� ���� � �������
    system("cls");
    cout << "\t\t������������:\n";
    tests();
    string input;
    cout << "\t\t��������:\n";
    cout << "������� ���������, ������� �� ������� ����������: \n\t\t";
    cin >> input;
    vector<vector<int> > code = to_lz77(input);
    cout << "\n�������������� ���������:\n";
    show_code(code);
    cout << "\n�������������� �������������� ���������:\n";
    string decode = decode_lz77(code);
    cout << "\t\t" << decode << "\n\n";
    if (input == decode)
        cout << "�������� ��������� ������� c ��������������!\n\n";
    else
        cout << "�������� ��������� �� ������� c ��������������!\n\n";
    system("pause");
    return 0;
}

vector<vector<int> > to_lz77(string input)
{
    // �������, � ��������� ����� ��������� ��� ���, � ���� ���� ��������� ����������� ������������� �������, � ������ ��������� �����������(������ 1).
    vector<vector<int> > codes; // ������� ������, ������ ������� ����� ��� �������
    string buffer;
    for (int counter = 0; counter < input.size(); counter++)
    {
        int is_find = buffer.rfind(input[counter]); // ���� ��������� �� ������� �������� string::npos (-1)
        while (is_find == -1 && counter < input.size())
        {
            codes.push_back({ 0,0,input[counter] }); // ���������, �� ������������� ����� ������ ����� ����� 0,0
            buffer += input[counter];
            is_find = buffer.rfind(input[++counter]);
        }
        if (counter >= input.size()) // ��� ������� �������(� ��� ����� � � while) �������� ���������� ������ ������������������ ���� �� � ����� �����������
            return codes;
        string substr;
        do
        {
            substr += input[counter];
            is_find = buffer.rfind(substr + input[++counter]); // ����� �������� �������� ��������� �����, ��� ����� ����� do while
        } while (is_find != -1 && counter < input.size());
        is_find = buffer.rfind(substr);
        codes.push_back({ counter - is_find - (int)substr.size(), (int)substr.size(), input[counter]});
        buffer += substr + input[counter];
    }
    return codes;
}

void show_code (vector<vector<int> > code)
{
    for (int counter = 0; counter < code.size(); counter++)
    {
        cout << '(' << code[counter][0] << ',' << code[counter][1] << ',' << (char)code[counter][2] << ")\n";
    }
}

string decode_lz77(vector<vector<int> > code)
{
    string decode;
    for (int counter = 0; counter < code.size(); counter++)
    {
        decode += decode.substr(decode.size() - code[counter][0], code[counter][1]);
        decode += code[counter][2];
    }
    decode = decode.substr(0, decode.size());
    if (decode[decode.length() - 1] == '\0')
        return decode.substr(0, decode.length() - 1); // ������ �������� ���������� �������� \0
    else
        return decode;
}

void tests()
{
    test_1();
    test_2();
    test_3();
    test_4();
    test_5();
}
void test_1()
{
    string input = "abcdef"; // ��� ����� ��, ��� ����� ����������
    if (input == decode_lz77(to_lz77(input)))
        cout << "TEST TRUE\n";
    else
        cout << "TEST FALSE\n";
}
void test_2()
{
    string input = "�������_������"; // ��� ����� ��, ��� ����� ����������
    if (input == decode_lz77(to_lz77(input)))
        cout << "TEST TRUE\n";
    else
        cout << "TEST FALSE\n";
}
void test_3()
{
    string input = "�����������"; // ��� ����� ��, ��� ����� ����������
    if (input == decode_lz77(to_lz77(input)))
        cout << "TEST TRUE\n";
    else
        cout << "TEST FALSE\n";
}
void test_4()
{
    string input = "��� ���� �� ����� � ������ �����"; // ��� ����� ��, ��� ����� ����������
    if (input == decode_lz77(to_lz77(input)))
        cout << "TEST TRUE\n";
    else
        cout << "TEST FALSE\n";
}
void test_5() // ����� ���������� ����
{
    string input = "���\n���"; // ��� ����� ��, ��� ����� ����������
    if (input == decode_lz77(to_lz77(input)))
        cout << "TEST TRUE\n";
    else
        cout << "TEST FALSE\n";
}