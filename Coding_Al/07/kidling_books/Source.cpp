// ������ �������� ������� 3�� ����� ���� ��. �. �. ������� ������� �.�.
// ����� ��������� 20 �����
// ������ ��������� ��������� ��������� ����������� � ������������� ������� ���� 
// ���������� mingw-5.2.0

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
    string alphabet;
    cout << "������� ������� ����������� ����� ������� ��� ������������\n\t\t";
    cin >> alphabet;
    cout << "\n�������������� ���������:\n";
    string code = to_kidling_books(input, alphabet);
    cout << "�������������� �������������� ���������:\n";
    string decode = decode_kidling_books(code, alphabet);
    cout << "\t\t" << decode << "\n\n";
    if (input == decode) cout << "�������� ��������� ������� c ��������������!\n\n";
    else cout << "�������� ��������� �� ������� c ��������������!\n\n";
    system("pause");
    return 0;
}

string to_kidling_books(string input, string alphabet)
{
    string code;
    for (int counter = 0; counter < input.size(); counter++)
    {
        for (int counter2 = 0; counter2 < alphabet.size(); counter2++)
        {
            if (input[counter] == alphabet[counter2])
            {
                code += (counter2 + 1) + '0'; // +1 �.�. � ����� �� ���� �� 0��
                alphabet.insert(alphabet.begin(), alphabet[counter2]);
                alphabet.erase(counter2 + 1,1); // +1 �.�. ����� ������� � ������ ����������� ����������� �� 1��
                break;
            }
        }
    }
    return code;
}

string decode_kidling_books(string code, string alphabet)
{
    string decode;
    for (int counter = 0; counter < code.size(); counter++)
    {
        decode += alphabet[(code[counter] - '0') - 1];
        alphabet.insert(alphabet.begin(), alphabet[(code[counter] - 1) - '0']);
        alphabet.erase((code[counter] - '0'), 1); // +1 �.�. ����� ������� � ������ ����������� ����������� �� 1��
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
    string alphabet = "abc"; // �������
    string code = to_kidling_books(input,alphabet);
    string decode = decode_kidling_books(code, alphabet);
    if (decode == input)
        cout << "\nTEST TRUE\n";
    else
        cout << "\nTEST FALSE\n";
}
void test_2()
{
    string input = "abcdabcddcba"; // ��� �����, ��� ����� ������������
    string alphabet = "abcd";
    string code = to_kidling_books(input, alphabet);
    string decode = decode_kidling_books(code, alphabet);
    if (decode == input)
        cout << "\nTEST TRUE\n";
    else
        cout << "\nTEST FALSE\n";
}
void test_3()
{
    string input = "�����������"; // ��� �����, ��� ����� ������������
    string alphabet = "�����";
    string code = to_kidling_books(input, alphabet);
    string decode = decode_kidling_books(code, alphabet);
    if (decode == input)
        cout << "\nTEST TRUE\n";
    else
        cout << "\nTEST FALSE\n";
}
void test_4()
{
    string input = "������"; // ��� �����, ��� ����� ������������
    string alphabet = "�����";
    string code = to_kidling_books(input, alphabet);
    string decode = decode_kidling_books(code, alphabet);
    if (decode == input)
        cout << "\nTEST TRUE\n";
    else
        cout << "\nTEST FALSE\n";
}
void test_5()
{
    string input = "������"; // ��� �����, ��� ����� ������������
    string alphabet = "�����";
    string code = to_kidling_books(input, alphabet);
    string decode = decode_kidling_books(code, alphabet);
    if (decode == input)
        cout << "\nTEST TRUE\n";
    else
        cout << "\nTEST FALSE\n";
}
