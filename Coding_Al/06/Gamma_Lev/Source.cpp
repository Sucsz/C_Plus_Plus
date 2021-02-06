#include "Header.h"

int main()
{
    system("chcp 1251");  // Переходим на русский язык в консоли
    system("cls");
    loop_test();
    unsigned input;
    cout << "Введите целое положительное число, которое вы желаете кодировать: \n\t\t";
    cin >> input;
    cout << "\nЗакодированное сообщение:\n";
    string code = to_gam_lev(input);
    cout << "\t\t" << code << "\n\n";
    cout << "Декодированное закодированное сообщение:\n";
    unsigned decode = decode_gam_lev(code);
    cout << "\t\t" << decode << "\n\n";
    if (input == decode) cout << "Исходное сообщение совпало c декодированным!\n\n";
    else cout << "Исходное сообщение не совпало c декодированным!\n\n";
    system("pause");

    return 0;
}

// Функция переводит число в двоичную систему счисления
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
// Функция переводит число в десятичную систему счисления
unsigned to_dec(string bin)
{
    unsigned res = 0;
    for (int counter = 0; counter < bin.size(); counter++)
    {
        res += (bin[bin.size() - counter - 1] - '0') * pow(2, counter);
    }
    return res;
}

string to_gam_lev(unsigned num)
{
    vector <bool> bin_num = to_binary(num);
    vector <bool> code;
    for (int counter = 0; counter < bin_num.size() - 1; counter++) // Для всех битов, кроме последнего приписываем 0
    {
        code.push_back(false);
        code.push_back(bin_num[counter]); // Т.к. bin_num - уже обращенный, если идти с 0го элемента, то обращение не требуется
    }
    code.push_back(bin_num[bin_num.size() - 1]); // Приписываем последний бит
    string to_string;
    for (int counter = 0; counter < code.size(); counter++)  // Переводим в строку
        to_string += (int)code[counter] + '0';
    return to_string;
}

unsigned decode_gam_lev(string code)
{
    string decode;
    for (int counter = code.size() - 2; counter > 0; counter -= 2)
    {
        decode += code[counter];
    }
    decode.insert(decode.begin(), '1');
    unsigned result = to_dec(decode);
    return result;
}

void loop_test()
{
    for (int counter = 1; counter <= 100; counter++)
    {
        if (counter == decode_gam_lev(to_gam_lev(counter)))
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
