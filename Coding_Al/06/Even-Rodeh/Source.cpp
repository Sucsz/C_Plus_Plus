#include "Header.h";

int main()
{
    system("chcp 1251");  // Переходим на русский язык в консоли
    system("cls");
    loop_test();
    unsigned input;
    cout << "Введите целое положительное число, которое вы желаете кодировать: \n\t\t";
    cin >> input;
    cout << "\nЗакодированное сообщение:\n";
    string code = to_even_rodeh(input);
    cout << "\t\t" << code << "\n\n";
    cout << "Декодированное закодированное сообщение:\n";
    unsigned decode = decode_even_rodeh(code);
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

string to_even_rodeh(unsigned num)
{
    switch (num)
    {
    case 0:
        return "000";
    case 1:
        return "001";
    case 2:
        return "010";
    case 3:
        return "011";
    }
    vector <bool> bin_num = to_binary(num);
    vector <bool> code;
    code.push_back(false); // Приписываем в конец 0
    while (bin_num.size() != 3)
    {
        for (int counter = 0; counter < bin_num.size(); counter++) // Приписываем двоичное представление группы битов слева
            code.insert(code.begin(), bin_num[counter]);
        bin_num = to_binary(bin_num.size());
    }
    for (int counter = 0; counter < bin_num.size(); counter++)    // Приписываем двоичное представление первой группы битов слева,тк цикл выше ее не покрывает 
        code.insert(code.begin(), bin_num[counter]);
    string to_string;
    for (int counter = 0; counter < code.size(); counter++)      // Переводим в строку
        to_string += (int)code[counter] + '0';
    return to_string;
}

unsigned decode_even_rodeh(string code)
{
    if (code == "000")
        return 0;
    else if (code == "001")
        return 1;
    else if (code == "010")
        return 2;
    else if (code == "011")
        return 3;
    unsigned num = 3;
    code = code.substr(0,code.size()-1); // Удаляем последний 0 pop_back() у string в с++11 нет
    while (code.size())
    {
        string current_code = code.substr(0, num);
        for (int counter = 0; counter < num; counter++)
            code.erase(code.begin());
        num = to_dec(current_code);
    }
    return num;
}

void loop_test()
{
    for (int counter = 1; counter <= 100; counter++)
    {
        if (counter == decode_even_rodeh(to_even_rodeh(counter)))
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