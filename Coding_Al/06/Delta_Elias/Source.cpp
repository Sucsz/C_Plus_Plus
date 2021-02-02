//5 минут
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
    string code = to_delta_elias(input);
    cout << "\t\t" << code << "\n\n";
    cout << "Декодированное закодированное сообщение:\n";
    unsigned decode = decode_delta_elias(code);
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
// Перевод чичло в код Дельта-Элайеса
string to_delta_elias(unsigned num)
{
    vector <bool> bin_num = to_binary(num);
    vector <bool> bin_size_bn = to_binary(bin_num.size()); // Двоичное представление длины двоичного представления исходного числа
    vector <bool> code;
    string to_string;

    for (int counter = 0; counter < bin_size_bn.size() - 1; counter++)
    {
        code.push_back(false);  // Вместо унарного кода будем приписывать необходимое число нулей, а вместо усеченного двоичного представления, будем дописывать полное
                                // Тем самым образуя унарный код и усекая двоичное представление
    }
    // Дописываем двоичное представление Длинны числа без значащей единицы
    for (int counter = bin_size_bn.size() - 1; counter > 0; counter--)
        code.push_back(bin_size_bn[counter]); // Ход цикла в обратном порядке потому, что число при конвертации записано в обратном порядке

    // Дописываем двоичное представление числа
    for (int counter = bin_num.size() - 1; counter >= 0; counter--)
        code.push_back(bin_num[counter]); // Ход цикла в обратном порядке потому, что число при конвертации записано в обратном порядке

    for (int counter = 0; counter < code.size(); counter++)      // Переводим в строку
        to_string += (int)code[counter] + '0';
    return to_string;
}
// Перевод кода Гамма-Элайса в десятичное представление
unsigned decode_delta_elias(string code)
{
    int counter_0 = 0;
    while (code[0] == '0') //Стираем нули унарного представления и считаем их количество
    {
        code.erase(code.begin());
        counter_0++;
    }
    for (int counter = 0; counter < counter_0; counter++) // Удаляем столько битов, сколько нулей насчитали в предыдущем пункте
    {
        code.erase(code.begin());
    }
    unsigned decode = to_dec(code);
    return decode;
}
void loop_test()
{
    for (int counter = 1; counter <= 100; counter++)
    {
        if (counter == decode_delta_elias(to_delta_elias(counter)))
        {
            cout << counter << " -> decode_delta_elias(to_delta_elias(" << counter << ")) = " << counter;
            cout << "\nTEST TRUE\n\n";
        }
        else
        {
            cout << "\nTEST FALSE\n\n";
        }
    }
}