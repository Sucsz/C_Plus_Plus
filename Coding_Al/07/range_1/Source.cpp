#include "Header.h"
// ������ �������� ������� 3�� ����� ���� ��. �. �. ������� ������� �.�.
// ����� ��������� 45 �����
// ������ ��������� ��������� ��������� �������������-�����������(1) � �������������-�������������(1). 
// �������� ��� �������, ��� �������� ����� ����������� ������� <= 9
// ���������� mingw-5.2.0

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
    cout << "\n�������������� ���������:\n";
    //show_freq_table(frequency_analysis(input));
    string code = to_range_1(input);
    cout << "\t\t" << code << '\n';
    cout << "������� ���������, ������� �� ������� ������������: \n\t\t";
    string decode;
    cin >> decode;
    cout << "������� ���������� �������� ��������: \n";
    vector<char> alphabet;
    int alphabet_size;
    cin >> alphabet_size;
    for (int counter = 0; counter < alphabet_size; counter++)
    {
        cout << "������� ������� ������ ��������:\n";
        char symbol;
        cin >> symbol;
        alphabet.push_back(symbol);
    }
    string result = decode_range_1(alphabet, decode);

    cout << "\t\t" << result << "\n\n";
    return 0;
}

// ������� ��������� ��������� ������ ��������  ������
map<char, int> frequency_analysis(string input) // �������, ����������� ��������� ������ �������� ������
{
    map<char, int> freq_table;
    int size = input.size();
    for (int counter = 0; counter < size; counter++)
        freq_table[input[counter]] += 1;
    return freq_table;
}
// ������� ������� ������� ������ �� �����
void show_freq_table(map<char, int> freq_table)
{
    map<char, int>::iterator it;
    for (it = freq_table.begin(); it != freq_table.end(); it++)
        cout << "������: " << it->first << "\t����������: " << it->second << '\n';
    cout << "\n\n";
}
// �������� ���������� ���������� ������������ ����� 1
string to_range_1(string input)
{
    map<char, int> freq_table = frequency_analysis(input);
    map<char, int>::reverse_iterator rit;
    string code;
    for (rit = freq_table.rbegin(); rit != freq_table.rend(); rit++) // ���������� ������� � ������ ������
        input.insert(input.begin(), rit->first);
    for (int counter = input.size() - 1; counter >= freq_table.size(); counter--)
    {
        int range = 0; // ������� ���������� �� ���������� ������������ �������
        for (int counter2 = counter - 1; counter2 >= 0; counter2--)
        {
            if (input[counter] == input[counter2])
                break;
            range++;
        }
        code.insert(code.begin(), range + '0');
    }
    return code;
}
// ���������� ���������� ���������, �������������� ������������ ����� 1
string decode_range_1(vector<char> alphabet, string code)
{
    string decode;
    for (int counter = alphabet.size() - 1; counter >= 0; counter--)
        code.insert(code.begin(), alphabet[counter]); // �������� �������
    for (int counter = alphabet.size(); counter < code.size(); counter++)
    {
        decode += code[counter - (code[counter] - '0') - 1];
        char symbol = code[counter - (code[counter] - '0') - 1];
        string res; // ����� � �������, ����� ������� ������ � ������ 
        res += symbol;
        code.replace(counter, 1, res);
    }
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
    string input = "cabbbabbac"; // ��� �����, ��� ����� ������������
    string code = to_range_1(input);
    vector<char> alphabet; // ������� ��� �������������
    alphabet.push_back('a');
    alphabet.push_back('b');
    alphabet.push_back('c');
    string decode = decode_range_1(alphabet, code);
    if (decode == input)
        cout << "\nTEST TRUE\n";
    else
        cout << "\nTEST FALSE\n";
}
void test_2()
{
    string input = "abcdabcddcba"; // ��� �����, ��� ����� ������������
    string code = to_range_1(input);
    vector<char> alphabet; // ������� ��� �������������
    alphabet.push_back('a');
    alphabet.push_back('b');
    alphabet.push_back('c');
    alphabet.push_back('d');
    string decode = decode_range_1(alphabet, code);
    if (decode == input)
        cout << "\nTEST TRUE\n";
    else
        cout << "\nTEST FALSE\n";
}
void test_3()
{
    string input = "�����������"; // ��� �����, ��� ����� ������������
    string code = to_range_1(input);
    vector<char> alphabet; // ������� ��� �������������
    alphabet.push_back('�');
    alphabet.push_back('�');
    alphabet.push_back('�');
    alphabet.push_back('�');
    alphabet.push_back('�');
    string decode = decode_range_1(alphabet, code);
    if (decode == input)
        cout << "\nTEST TRUE\n";
    else
        cout << "\nTEST FALSE\n";
}
void test_4()
{
    string input = "������"; // ��� �����, ��� ����� ������������
    string code = to_range_1(input);
    vector<char> alphabet; // ������� ��� �������������
    alphabet.push_back('�');
    alphabet.push_back('�');
    alphabet.push_back('�');
    alphabet.push_back('�');
    alphabet.push_back('�');
    string decode = decode_range_1(alphabet, code);
    if (decode == input)
        cout << "\nTEST TRUE\n";
    else
        cout << "\nTEST FALSE\n";
}
void test_5()
{
    string input = "������"; // ��� �����, ��� ����� ������������
    string code = to_range_1(input);
    vector<char> alphabet; // ������� ��� �������������
    alphabet.push_back('�');
    alphabet.push_back('�');
    alphabet.push_back('�');
    alphabet.push_back('�');
    alphabet.push_back('�');
    string decode = decode_range_1(alphabet, code);
    if (decode == input)
        cout << "\nTEST TRUE\n";
    else
        cout << "\nTEST FALSE\n";
}

