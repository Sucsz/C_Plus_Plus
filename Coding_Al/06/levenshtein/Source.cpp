#include "Header.h"

int main()
{
    system("chcp 1251");  // Переходим на русский язык в консоли
    system("cls");
    loop_test();
    unsigned input;
    cout << "Введите целое неотрицательное число, которое вы желаете кодировать: \n\t\t";
    cin >> input;
    cout << "\nЗакодированное сообщение:\n";
    string code = to_levenshtein(input);
    cout << "\t\t" << code << "\n\n";
    cout << "Декодированное закодированное сообщение:\n";
    unsigned decode = decode_levenshtein(code);
    cout << "\t\t" << decode << "\n\n";
    if (input == decode) cout << "Исходное сообщение совпало c декодированным!\n\n";
    else cout << "Исходное сообщение не совпало c декодированным!\n\n";
    system("pause");
	return 0;
}
// Функция переводит число в двоичную систему счисления, после удаляет первую единицу.
vector<bool> to_binary_sub(unsigned num)
{
    vector<bool> res;
    while (num)
    {
        res.push_back(num % 2);
        num /= 2;
    }
    res.pop_back(); // Последний элемент - есть первый в двоичном представлении
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
string to_levenshtein(unsigned num)
{
    // если кодировать числа выше 3999999999 декодировать функцией decode_levenshtein их не получится
    if (num == 0) return "0";
    vector <bool> bin_num = to_binary_sub(num);
    vector <bool> code; // Вставляеть в начало кода bin' от num не нужно, т.к. цикл делает проход от исходного num
    vector <bool> copy_bin_num(bin_num);
    unsigned count = 1;
    while (copy_bin_num.size())
    {
        for (int counter = 0; counter < copy_bin_num.size(); counter++)
            code.insert(code.begin(), copy_bin_num[counter]); // Вставляем в начало кода bin' от количества bin_num
        copy_bin_num = to_binary_sub(copy_bin_num.size());
        count++;
    }
    code.insert(code.begin(), false); // Вставляем  0 в начало;
    for (int counter = count; counter > 0; counter--) // Вставляем count 1 в начало кода
        code.insert(code.begin(), true);
    string to_string;
    for (int counter = 0; counter < code.size(); counter++)  // Переводим в строку
        to_string += (int)code[counter] + '0';
    return to_string;
}
unsigned decode_levenshtein(string code)
{
    // декодирует до 11111000011111111111111111111111111111111111 включительно 3999999999
    if (code == "0") return 0;
    unsigned c = 0; // Счетчик единиц
    while (code[0] != '0')
    {
        c++;
        code.erase(code.begin()); // Очистили от 1
    }
    code.erase(code.begin()); // Очистили от нуля
    unsigned n = 1;
    unsigned p = c - 1;
    string decode;
    while (p)
    {
        for (int counter = 0; counter < n; counter++)
        {
            decode += code[counter];
        }
        for (int counter = 0; counter < n; counter++)
        {
            code.erase(code.begin());
        }
        decode.insert(decode.begin(), '1');
        unsigned z = to_dec(decode);
        n = z;
        decode = "";
        p--;
    }
    return n;
}
void loop_test()
{
    for (int counter = 0; counter <= 100; counter++)
    {
        if (counter == decode_levenshtein(to_levenshtein(counter)))
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
