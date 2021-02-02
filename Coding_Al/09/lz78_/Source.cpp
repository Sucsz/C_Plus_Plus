// ������ �������� ������� 3�� ����� ���� ��. �. �. ������� ������� �.�.
// ����� ��������� 1 ��� 10 �����
// ������ ��������� ��������� ��������� ����������� � ������������� LZ78 
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
    vector<vector<int>> code = to_lz78(input);
    cout << "\n�������������� ���������:\n";
    show_code(code);
    cout << "\n�������������� �������������� ���������:\n";
    string decode = decode_lz78(code);
    cout << "\t\t" << decode << "\n\n";
    if (input == decode)
        cout << "�������� ��������� ������� c ��������������!\n\n";
    else
        cout << "�������� ��������� �� ������� c ��������������!\n\n";
    system("pause");
    return 0;
}

vector<vector<int>> to_lz78(string input)
{
    // �������, � ��������� ����� ��������� ��� ���, � ���� ���� ��������� ����������� ������������� �������, � ������ ��������� �����������(������ 1).
    vector<vector<int>> codes; // ������� �����, ������ ������� ����� ��� �������
    map<string, int> buffer; // ������ ������ �� �������, ��� ��� ������ ����� ������� �������� ���������� ������ �������, string - ���������, int - �������
    for (int counter = 0; counter < input.size(); counter++)
    {
        int is_find = buffer.count(string(1, input[counter])); // find �� ��������, ������ ��� find ���������� ���������, ��� �������� count, count > 0 => is_find ����� !is_find
        while (!is_find && counter < input.size())
        {
            codes.push_back({ 0,input[counter] }); // ���������, �� ������������� ����� ������ ����� ����� 0,0
            buffer.insert(make_pair(string(1, input[counter]), buffer.size() + 1)); // size() + 1, ������ ��� ������� ������� �����
            is_find = buffer.count(string(1, input[++counter]));
        }
        if (counter >= input.size()) // ��� ������� �������(� ��� ����� � � while) �������� ���������� ������ ������������������ ���� �� � ����� �����������
            return codes;
        string substr;
        do
        {
            substr += input[counter];
            is_find = buffer.count(substr + input[++counter]); // ����� �������� �������� ��������� �����, ��� ����� ����� do while
        } while (is_find && counter < input.size());
        // ��� ������������� ������ ��������� � �������, ����� ������� ����� �� �������, ��� ��� ��������� ����� ������� ����� � ���� ���������-�������
        codes.push_back({ buffer[substr], input[counter] });
        buffer.insert(make_pair(substr + input[counter], buffer.size() + 1));
    }
    return codes;
}

void show_code(vector<vector<int>> code)
{
    for (int counter = 0; counter < code.size(); counter++)
    {
        cout << '(' << code[counter][0] << ',' << (char)code[counter][1] << ")\n";
    }
}

string decode_lz78(vector<vector<int>> code)
{
    string decode;
    map<int, string> buffer;
    for (int counter = 0; counter < code.size(); counter++)
    {
        string substr;
        if (code[counter][0])
        {
            substr = buffer[code[counter][0]];
            decode += substr;
        }
        decode += code[counter][1];
        buffer[buffer.size() + 1] = substr + string(1, code[counter][1]);
    }
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
    if (input == decode_lz78(to_lz78(input)))
        cout << "TEST TRUE\n";
    else
        cout << "TEST FALSE\n";
}
void test_2()
{
    string input = "�������_������"; // ��� ����� ��, ��� ����� ����������
    if (input == decode_lz78(to_lz78(input)))
        cout << "TEST TRUE\n";
    else
        cout << "TEST FALSE\n";
}
void test_3()
{
    string input = "�����������"; // ��� ����� ��, ��� ����� ����������
    if (input == decode_lz78(to_lz78(input)))
        cout << "TEST TRUE\n";
    else
        cout << "TEST FALSE\n";
}
void test_4()
{
    string input = "��� ���� �� ����� � ������ �����"; // ��� ����� ��, ��� ����� ����������
    if (input == decode_lz78(to_lz78(input)))
        cout << "TEST TRUE\n";
    else
        cout << "TEST FALSE\n";
}
void test_5() // ����� ���������� ����
{
    string input = "���\n���"; // ��� ����� ��, ��� ����� ����������
    if (input == decode_lz78(to_lz78(input)))
        cout << "TEST TRUE\n";
    else
        cout << "TEST FALSE\n";
}