// Работу выполнил студент 3го курса РГПУ им. А. И. Герцена Семыкин В.В.
// Время написания 15 минут
// Данная программа реализует алгоритмы sss-кодирования и sss-декодирования.
// Компилятор mingw-5.2.0

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
    string code = to_fib_code(input);
    cout << "\t\t" << code << "\n\n";
    cout << "Декодированное закодированное сообщение:\n";
    unsigned decode = decode_fib_code(code);
    cout << "\t\t" << decode << "\n\n";
    if (input == decode) cout << "Исходное сообщение совпало c декодированным!\n\n";
    else cout << "Исходное сообщение не совпало c декодированным!\n\n";
    system("pause");
    return 0;
}
// Перевод из 10-ичной системы счисления в Фибоначчи, запись задом наперед
vector<bool> to_fib(unsigned long long number)
{
    
    // Данная функция принимает на вход десятичное число и перевод его в систему счисления Фибоначчи
    // Результат выдается в виде десятичного числа, где цифры в разрядах - есть подряд идущие цифры записи числа в системе счисления Фибоначчи
    unsigned long long fib_number = 0;
    vector<bool> result;
    while (number)
    {
        unsigned long long int a = 1; // Предыдущее число Фибоначчи
        unsigned long long int b = 1; // Нынешнее число Фибоначчи
        unsigned long long int j = 1; // Счетчик разрядов нынешнего числа Фибоначчи
        while (b <= number)
        {
            a = a ^ b;                // Замена переменных без дополнительной переменной
            b = b ^ a;
            a = a ^ b;
            b += a;
            j *= 10;
        }
        // После цикла мы имеем актуальное число Фибоначчи для вычитания
        number -= a;
        fib_number += j == 1 ? 1 : j / 10; // Использование тернарнорного оператора вместо конструкции if else
                                           // Эквивалентно варианту if (j == 1) {fib_number += 1} else {fib_number += j / 10}
                                           // j / 10 - это "разворачивание" счетчика разрядов, позволяет поставить 1 в нужном месте
    }
    while (fib_number)
    {
        result.push_back(fib_number % 10);
        fib_number /= 10;
    }
    return result;
}

string to_fib_code(unsigned long long num)
{
    vector<bool> code = to_fib(num);
    code.push_back(1); //Добавляем разделяющую единицу
    string to_string;
    for (int counter = 0; counter < code.size(); counter++)      // Переводим в строку
        to_string += (int)code[counter] + '0';
    return to_string;
}

unsigned decode_fib_code(string code)
{
    unsigned long long res = 0;
    code.erase(code.end()-1); // Удаляем приписанную единицу
    unsigned long long int a = 1;  // Предыдущее число Фибоначчи (Служащее счетчиком разряда)
    unsigned long long int b = 1;  // Нынешнее число Фибоначчи 
    for (int counter = 0; counter < code.size(); counter++)
    {
        res += ((code[counter] - '0') * b);
        a = a ^ b;                // Замена переменных без дополнительной переменной
        b = b ^ a;
        a = a ^ b;
        b += a;

    }
    return res;

}

void loop_test()
{
    for (int counter = 1; counter <= 100; counter++)
    {
        if (counter == decode_fib_code(to_fib_code(counter)))
        {
            cout << counter << " -> decode_fib_code(to_fib_code(" << counter << ")) = " << counter;
            cout << "\nTEST TRUE\n\n";
        }
        else
        {
            cout << "\nTEST FALSE\n\n";
        }
    }
}