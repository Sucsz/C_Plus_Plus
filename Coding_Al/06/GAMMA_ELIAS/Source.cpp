//10 минут
#include "Header.h"

int main()
{
    system("chcp 1251");  // ѕереходим на русский ¤зык в консоли
    system("cls");
    loop_test();
    unsigned input;
    cout << "¬ведите целое положительное число, которое вы желаете кодировать: \n\t\t";
    cin >> input;
    cout << "\n«акодированное сообщение:\n";
    string code = to_gamma_elias(input);
    cout << "\t\t" << code << "\n\n";
    cout << "ƒекодированное закодированное сообщение:\n";
    unsigned decode = decode_gamma_elias(code);
    cout << "\t\t" << decode << "\n\n";
    if (input == decode) cout << "»сходное сообщение совпало c декодированным!\n\n";
    else cout << "»сходное сообщение не совпало c декодированным!\n\n";
    system("pause");
    return 0;
}
// ‘ункци¤ переводит число в двоичную систему счислени¤
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
// ‘ункци¤ переводит число в дес¤тичную систему счислени¤
unsigned to_dec(string bin)
{
    unsigned res = 0;
    for (int counter = 0; counter < bin.size(); counter++)
    {
        res += (bin[bin.size() - counter - 1] - '0') * pow(2, counter);
    }
    return res;
}
// ѕеревод чичло в код √амма-Ёлайеса
string to_gamma_elias(unsigned num)
{
    vector <bool> bin_num = to_binary(num);
    vector <bool> code;
    string to_string;
    for (int counter = 0; counter < bin_num.size() - 1; counter++)
    {
        code.push_back(false);  // ¬место унарного кода будем приписывать необходимое число нулей, а вместо усеченного двоичного представлени¤, будем дописывать полное
                                // “ем самым образу¤ унарный код и усека¤ двоичное представление
    }
    // ƒописываем двоичное представление числа
    for (int counter = bin_num.size() - 1; counter >= 0; counter--)
        code.push_back(bin_num[counter]); // ’од цикла в обратном пор¤дке потому, что число при конвертации записано в обратном пор¤дке

    for (int counter = 0; counter < code.size(); counter++)      // ѕереводим в строку
        to_string += (int)code[counter] + '0';
    return to_string;
}
// ѕеревод кода √амма-Ёлайса в дес¤тичное представление
unsigned decode_gamma_elias(string code)
{
    while (code[0] == '0') //—тираем нули унарного представлени¤ 
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
        if (counter == decode_gamma_elias(to_gamma_elias(counter)))
        {
            cout << counter << " -> decode_gamma_elias(to_gamma_elias(" << counter << ")) = " << counter;
            cout << "\nTEST TRUE\n\n";
        }
        else
        {
            cout << "\nTEST FALSE\n\n";
        }
    }
}