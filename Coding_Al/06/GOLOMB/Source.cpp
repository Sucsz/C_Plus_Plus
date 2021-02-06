//5 минут m<=8
#include "Header.h"

int main()
{
    system("chcp 1251");  // Переходим на русский язык в консоли
    system("cls");
    loop_test();
    unsigned input, param;
    cout << "Введите целое положительное число, которое вы желаете кодировать: \n\t\t";
    cin >> input;
    cout << "Введите цело положителльное число, параметр кода Голомба\n\t\t";
    cin >> param;
    cout << "\nЗакодированное сообщение:\n";
    string code = to_golomb(input, param);
    cout << "\t\t" << code << "\n\n";
    cout << "Декодированное закодированное сообщение:\n";
    unsigned decode = decode_golomb(code,param);
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
string to_golomb(unsigned num, unsigned param)
{
    vector <bool> bin_num = to_binary(num);
    vector <bool> code;
    string to_string;

    // Дописываем унарный код num / param
    for (int counter = 0; counter < num / param; counter++)
        code.push_back(1);
    code.push_back(0);
    // Проверяем на степень двойки
    if ((param & (param - 1)) == 0) // Работа со сдвигами, двоичное представление числа,
                                    // Которое является степенью двойки, есть единица и все нули, предшествующее - все единицы
    {
        // Дописываем справа бинарный код num % param, который занимает log2(param) бит
        bin_num = to_binary(num % param);
        bin_num.resize(log2(param));
        for (int counter = bin_num.size() - 1; counter >= 0; counter--)
            code.push_back(bin_num[counter]);
    }
    else
    {
        int num_mod_param = num % param, c_l2_p = (int)ceil(log2(param));
        if (num_mod_param < pow(2, c_l2_p) - param)
        {
            // Дописываем справа бинарный код num_mod_param, который занимает c_l2_p-1 бит
            bin_num = to_binary(num_mod_param);
            bin_num.resize(c_l2_p - 1);
            for (int counter = bin_num.size() - 1; counter >= 0; counter--)
                code.push_back(bin_num[counter]);
        }
        else
        {
            // Дописываем справа бинарный код num_mod_param + (pow(2, c_l2_p) - param), который занимает c_l2_p битов
            bin_num = to_binary(num_mod_param + (pow(2, c_l2_p) - param));
            bin_num.resize(c_l2_p);
            for (int counter = bin_num.size() - 1; counter >= 0; counter--)
                code.push_back(bin_num[counter]);
        }
    }

    for (int counter = 0; counter < code.size(); counter++)      // Переводим в строку
        to_string += (int)code[counter] + '0';
    return to_string;
}
// Перевод кода Голомба в десятичное представление
unsigned decode_golomb(string code, unsigned param)
{
    int n_div_param = 0; // n - decode num
    vector <vector<string>> huffman_codes; // Мемоизация кодов хаффмана, при желании можно расширить
    vector<string> code_0; code_0.push_back("#"); //В начале добавляем любой символ, так как остаток ноль - означает деление нацело => степень двойки
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
    code.erase(code.begin()); // Избавились от унарного представления num div m
    if ((param & (param - 1)) == 0) // Проверка param на степень двойки
    {
        int c_l2_p = (int)ceil(log2(param));
        code.resize(c_l2_p);
        n_mod_param = to_dec(code);
        return n_div_param * param + n_mod_param;
    }
    // Иначе
    for (int counter = 0; counter < huffman_codes[param].size(); counter++) // Ищем нужный код хаффмана
    {
        if (code == huffman_codes[param][counter])
        {
            n_mod_param = counter;
            break;
        }
    }
    return n_div_param * param + n_mod_param;
}
void loop_test()
{
    for (int counter = 0; counter <= 10; counter++)
    {
        for (int counter2 = 1; counter2 <= 8; counter2++)
        {
            if (counter == decode_golomb(to_golomb(counter, counter2), counter2))
            {
                cout << counter << " -> decode_golomb(to_golomb(" << counter << ")," << counter2 <<") = " << counter;
                cout << "\nTEST TRUE\n\n";
            }
            else
            {
                cout << "\nTEST FALSE\n\n";
            }
        }
    }
}