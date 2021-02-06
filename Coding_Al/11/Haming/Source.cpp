// Работу выполнил студент 3го курса РГПУ им. А. И. Герцена Семыкин В.В.
// Время написания 5 часов
// Данная программа реализует алгоритмы кодирования, исправления ошибки и декодирования кодов Хэминга 

#include "Header.h"

int main()
{
    system("chcp 1251");  // Переходим на русский язык в консоли
    system("cls");
    loop_tests();
    unsigned input;
    cout << "Введите целое неотрицательное число, которое вы желаете кодировать: \n\t\t";
    cin >> input;
    string code(to_haming(input));
    cout << "\nЗакодированное сообщение: " << code << endl;
    cout << "\nДопустим случайную ошишбку\n";
    string wrong_code = do_wrong_code(code);
    cout << "\nСообщение без ошибки: " << code << "\n\nСообщение с ошибкой: " << wrong_code;
    string fix_code(fix_wrong(wrong_code));
    cout << "\n\nИсправленное сообщение: " << fix_code;
    unsigned decode = decode_ham(fix_code);
    cout << "\n\nДекодированное исправленное сообщение: " << decode;
    if (input == decode) cout << "\n\nИсходное сообщение совпало c декодированным!\n\n";
    else cout << "\n\nИсходное сообщение не совпало c декодированным!\n\n";
    system("pause");
    return 0;
}

// Функция переводит число в двоичную систему счисления
vector<bool> to_binary(unsigned num)
{
    vector<bool> res;
    while (num)
    {
        res.insert(res.begin(), num % 2);
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

string to_haming(unsigned num)
{
    // Функция принимает на вход целое положительное число и возвращает строку - код Хэминга
    vector<bool> bin = to_binary(num);
    unsigned m = bin.size(); // длина исходного слова
    unsigned l = m; // длина кодового слова
    while (pow(2, m) > pow(2, l) / (l + 1))
        l++;
    // cout << l << ' ' << m << '\n'; Строка для проверки l m 
    unsigned k = l - m; // разница длин кодового и исходного слова.
    for (int counter = 0; counter < k; counter++)
        bin.insert(bin.begin() + pow(2, counter) - 1, 0); // расширяет двоичное представление числа контрольными битами со значением 0
    for (int counter = 0; counter < bin.size(); counter++)
    {
        if (counter == 0 || ((counter + 1) & (counter)) == 0) // Проверка на степень 2ки, 0 - особый случай
        {
            unsigned group_size = counter + 1;
            unsigned number_ones = 0;
            for (int counter2 = counter; counter2 < bin.size(); counter2++)
            {
                if (group_size)
                {
                    group_size--;
                    if (bin[counter2])
                        number_ones++;
                    continue;
                }
                group_size = counter + 1;
                counter2 += group_size - 1;
            }
            //cout << number_ones << "|\n"; строка для проверки количества единиц после контрольного бита
            if (number_ones % 2 != 0)
                bin[counter] = 1;
        }
        else
            continue;
    }
    string to_string;
    for (int counter = 0; counter < bin.size(); counter++)  // Переводим в строку
        to_string += (int)bin[counter] + '0';
    return to_string;
}

string do_wrong_code(string code)
{
    // Функция принимает на вход строку - код Хэминга и допускает в нем одну псевдо-случайную ошибку. Возвращает строку с ошибкой.
    srand((unsigned int)time(NULL));
    unsigned num_sybmol = rand() % code.size();
    cout << "\nОшибка допущена в позиции номер:" << num_sybmol << '\n';
    code[num_sybmol] = !(code[num_sybmol] - '0') + '0';
    return code;
}

string fix_wrong(string wrong_code)
{
    // Функция принимает на вход строку - код Хэминга, с допущенной в нем ошибкой, и возвращает строку - исправленный код Хэминга.
    string copy_wrong_code = string(wrong_code);
    int position = 0; // Позиция ошибки
    for (int counter = 0; counter < wrong_code.size(); counter++) // Обнуляем контрольные биты
        if (counter == 0 || ((counter + 1) & (counter)) == 0)
            copy_wrong_code[counter] = '0';
    for (int counter = 0; counter < copy_wrong_code.size(); counter++) // Восстанавливаем контрольные биты
    {
        if (counter == 0 || ((counter + 1) & (counter)) == 0) // Проверка на степень 2ки, 0 - особый случай
        {
            unsigned group_size = counter + 1;
            unsigned number_ones = 0;
            for (int counter2 = counter; counter2 < copy_wrong_code.size(); counter2++)
            {
                if (group_size)
                {
                    group_size--;
                    if (copy_wrong_code[counter2] - '0')
                        number_ones++;
                    continue;
                }
                group_size = counter + 1;
                counter2 += group_size - 1;
            }
            //cout << number_ones << "|\n"; строка для проверки количества единиц после контрольного бита
            if (number_ones % 2 != 0)
                copy_wrong_code[counter] = '1';
        }
        else
            continue;
    }
    for (int counter = 0; counter < copy_wrong_code.size(); counter++)
    {
        if (counter == 0 || ((counter + 1) & (counter)) == 0) // Проверка на степень 2ки, 0 - особый случай
            if (copy_wrong_code[counter] != wrong_code[counter])
                position += counter + 1; // это приходится делать, потому что мы идем от нуля, а не от единицы, тем самым складывая, к примеру, первый и второй элемент
                                         // мы получим разницу больше, чем в единицу. |0+1 = 1| |1 + 2 = 2|
        continue;
    }
    position -= 1; // а тут мы отнимаем единицу, чтобы перейти к отсчету от нуля.
    wrong_code[position] = !(wrong_code[position] - '0') + '0'; // Исправление ошибки
    return wrong_code;
}

unsigned decode_ham(string code)
{
    // Функция принимает на вход строку - код Хэминга, возвращает целое положительное число
    string decode;
    for (int counter = 0; counter < code.size(); counter++) // удаляем контрольные биты
    {
        if (!(counter == 0 || ((counter + 1) & (counter)) == 0)) // Проверка на степень 2ки, 0 - особый случай
        {
            decode += code[counter];
        }
    }
    return to_dec(decode);
}

void loop_tests()
{
    int stop = 100;
    for (int counter = 1; counter < stop; counter++)
    {
        string code(to_haming(counter));
        string wrong_code = do_wrong_code(code);
        string fix_code(fix_wrong(wrong_code));
        unsigned decode = decode_ham(fix_code);
        if (counter == decode)
            cout << "\nTEST TRUE\n";
        else
            cout << "\nTEST FALSE\n";
    }
}