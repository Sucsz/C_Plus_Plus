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
    string code = to_omega_elias(input);
    cout << "\t\t" << code << "\n\n";
    cout << "Декодированное закодированное сообщение:\n";
    unsigned decode = decode_omega_elias(code);
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

string to_omega_elias(unsigned num)
{
    vector <bool> bin_num = to_binary(num);
    vector <bool> code;
    code.push_back(false);
    while (num != 1)
    {
        //приписываем двоичное предаствление числа слева
        for (int count = 0; count < bin_num.size(); count++)
            code.insert(code.begin(), bin_num[count]); // Вставляем в начало кода довичное представление числа
        num = bin_num.size() - 1;
        bin_num = to_binary(num);
    }
    string to_string;
    for (int counter = 0; counter < code.size(); counter++)  // Переводим в строку
        to_string += (int)code[counter] + '0';
    return to_string;
}

unsigned decode_omega_elias(string code)
{
    unsigned num = 1;
    while (code[0] != '0')
    {
        string current_code = code.substr(0, num + 1);
        for (int counter = 0; counter <= num; counter++)
            code.erase(code.begin());
        num = to_dec(current_code);
    }
    return num;
}

void loop_test()
{
    for (int counter = 1; counter <= 100; counter++)
    {
        if (counter == decode_omega_elias(to_omega_elias(counter)))
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