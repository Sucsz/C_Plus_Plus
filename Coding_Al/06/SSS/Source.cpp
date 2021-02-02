// Работу выполнил студент 3го курса РГПУ им. А. И. Герцена Семыкин В.В.
// Время написания 3 часа 10 минут
// Данная программа реализует алгоритмы sss-кодирования и sss-декодирования.
// Компилятор mingw-5.2.0

#include "header.h"

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
// Функция перевод число в десятичную систему счисления
unsigned to_dec(string bin)
{
    unsigned res = 0;
    for (int counter = 0; counter < bin.size(); counter++)
    {
        res += (bin[bin.size() - counter - 1] - '0') * pow(2, counter);
    }
    return res;
}

string to_sss(unsigned i, unsigned j,  unsigned k, unsigned num)
{
    vector<bool> code;
    unsigned min_value = 0; // Минимальное число текущего диапозона
    unsigned max_value = 0; // Максимальное число текущего диапазона
    unsigned num_of_range = 0;
    unsigned c_i = i; // Исходное значение i
    cout << "Схема кодов для данных параметров i,j,k:\n\n";
    for (i; i <= k; i += j, num_of_range++)
    {
        min_value = max_value + 1;
        max_value += pow(2, i);
        // Составим схему кодирования для данных i,j,k
        string scheme_codes;
        // Дописывание унарного кода n-1го числа, порядок
        for (int counter = 0; counter < num_of_range; counter++)
            scheme_codes += '1';

        scheme_codes += '0'; // Унарный 0
        for (int counter = 0; counter < i; counter++) // Двоичное представление, мантисса
            scheme_codes += 'x';
        cout << scheme_codes << "\n";
        
        // Кодируем число, если оно попало в текущий диапазон
        if (num <= max_value)
        {
            // Дописывание унарного кода n-1го числа, порядок
            for (int counter = 0; counter < num_of_range; counter++)
                code.push_back(1);
            code.push_back(0);
            vector<bool> mantis; // Мантисса
            mantis = to_binary(num - min_value);
            if (mantis.size() < c_i + (num_of_range)*j)
            {
                for (int counter = 0; counter < (c_i + (num_of_range)*j - mantis.size()); counter ++)
                {
                    // Бинарное представление мантиссы стоит читать справа налево, в то время, как дописанные нули слева направо
                    // Таким образом будем дописывать 0-ли прямо в код, а не в мантиссу.
                    code.push_back(0);
                }
            }
            else
                mantis.resize(c_i + (num_of_range) * j);
            for (int counter = mantis.size() - 1; counter >= 0; counter--)
                code.push_back(mantis[counter]);
            string to_string;
            for (int counter = 0; counter < code.size(); counter++)// Переводим в строку
                to_string += (int)code[counter] + '0';
            return to_string;
        }
    }
}

unsigned decode_sss(unsigned i, unsigned j, string code)
{
    string mantis;
    int unar = 0;
    unsigned result;
    while (code[0] !=  '0')
    {
        unar++;
        code.erase(code.begin());
    }
    code.erase(code.begin()); // Отбросили унарное представление
    unar++; // Прибавляем к полученному результату единицу, обозначим результат за n
    int left_bound = 1;
    for (int counter = 0; counter < unar - 1; counter++) // unar - 1, потому что первый диапазон пропускаем инициализацией границы 1
        left_bound += pow(2, i + j * counter);
    for (int counter = 0; counter < (i + (unar - 1) * j); counter++)
        mantis += code[counter];
    result = to_dec(mantis) + left_bound;
    return result;
}

void loop_test()
{
    unsigned i = 3; 
    unsigned j = 2;
    unsigned k = 11; // Параметры sss-кодирования
    for (int counter = 1; counter <= 100; counter++)
    {
        if (counter == decode_sss(i, j, to_sss(i, j, k, counter)))
            {
            cout << counter << " -> decode_sss(" << i << ", " << j << ", to_sss(" << i << ", " << j << ", " << k << ")) == " << counter;
                cout << "\nTEST TRUE\n\n";
            }
            else
            {
                cout << "\nTEST FALSE\n\n";
            }
    }
}

int main()
{
    unsigned i,j,k, num;
    system("chcp 1251");  // Переходим на русский язык в консоли
    system("cls");
    loop_test();
    cout << "\t\t\t\t\tВведите параметры SSS кодирования:\n";
    cout << "Введите i: ";
    cin >> i;
    cout << "\nВведите j: ";
    cin >> j;
    cout << "\nВведите k: ";
    cin >> k;
    cout << "\n\t\t\t\t\tВведите число, которое желаете закодировать:\n";
    cin >> num;
    cout << "\n\t\t\t\t\tЗакодированное сообщение:\n";
    string code = to_sss(i, j, k, num);
    cout << "\t\t" << code << "\n\n";
    cout << "Декодированное закодированное сообщение:\n";
    unsigned decode = decode_sss(i, j, code);
    cout << "\t\t" << decode << "\n\n";
    if (num == decode) cout << "Исходное сообщение совпало c декодированным!\n\n";
    else cout << "Исходное сообщение не совпало c декодированным!\n\n";
    system("pause");
    return 0;
}
