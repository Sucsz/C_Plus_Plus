/*
Общее время выполнения работы ~4 часа
 
Работа выполнена студентом 3 курса ИИТО ИСиТ
   Семыкиным В.В.

Данная программа реализует алгоритм построения кодов Шеннона

*/
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>
using namespace std;

// Сигнатуры функций
vector<int> get_lengths_code(vector<double>*);
void out_vector(vector<double>);
void out_vector_s(vector<string>);
vector<string> to_2(vector<double>);
vector<string> to_sh(vector<string> q, vector<int>);
bool check_prefix(vector<string>);
bool check_2(vector<string>);
//Сигнатуры тестов
/*
Данная программа создает двоичные префиксные коды заданных длин. Оператор  if (is_prefix && is_2) return 0; в модуле main() проверят данные коды на
условие префиксности и двоичности, поэтому будем считать, что нет необходимости проводить тестирование программы как такового. 
*/

int main()
{
	system("chcp 1251");  // Переходим на русский язык в консоли
	system("cls");
	vector<double>  q; // Набор значений q
	vector<int> lengths_code = get_lengths_code(&q);
	cout << "\nНабор кумулятивных значений (2^(-l[i]), где l[i] - длинна i-го кода\n";
	out_vector(q);
	vector<string> imperfect_sh_codes = to_2(q); // Данные коды несовершенны, так им не хватает длинны, иначе говоря вместо 0100 мы имеем запись 0.1
	cout << "\nНабор несовершенных кодов\n";
	out_vector_s(imperfect_sh_codes);
	vector<string> sh_codes = to_sh(imperfect_sh_codes, lengths_code);
	cout << "\nНабор двоичных префиксных кодов\n";
	out_vector_s(sh_codes);
	bool is_prefix = check_prefix(sh_codes);
	bool is_2 = check_2(sh_codes);
	if (is_prefix && is_2)
	{
		system("pause");
		return 0;
	}
	return(-5);
}
// Функция, позволяющая пользователю ввести длины кодовых слов. Также выполняет различные проверки на корректность данных длин.
// "Возвращает" два значения(одно изменяем через указатель) длины слов и набор значений q
vector<int> get_lengths_code(vector<double>*  q)
{
	(*q).push_back(0);
	int count_codes;
	cout << "Введите количество кодовых слов:\n";
	cin >> count_codes;
	if (count_codes < 1)
	{
		cout << "Введено неверное количество\n";
		exit(-1);
	}
	vector<int> lengths_codes;
	int length_code;
	int current_max_length = -1; // Инициализируем "невозможным" значением, чтобы значение сразу же сменилось на значение длины первого кода
	double kraft_condition = 0;
	for (int counter = 1; counter <= count_codes; counter++)
	{
		printf("Введите длину %d-го кода:\n", counter);
		cin >> length_code;
		if (length_code < 1)
		{
			cout << "Введена неверная длина\n";
			exit(-2);
		}
		if (current_max_length > length_code)
		{
			cout << "Не удовлетворяет условию l1 <= l2 <= l3..., где l1,l2,l3... - длины кодов\n";
			exit(-3);
		}
		current_max_length = length_code;
		double current_denominator = pow(2, -length_code);
		kraft_condition += current_denominator;
		(*q).push_back((*q)[counter - 1] + current_denominator);
		if (kraft_condition > 1)
		{
			cout << "Не удовлетворяет условию неравенства Крафта\n";
			exit(-4);
		}
		lengths_codes.push_back(length_code);
	}
	(*q).pop_back(); // Так как в начале мы добавляем 0, остается добавить n-1 кодов, где n-кол-во кодов, но цикл добавляет n кодов, так как это удобно
					 // Для другой задачи, поэтому просто удалим последний n+1 код
	return lengths_codes;
}

// Вывод вектора на экран с типом double
void out_vector(vector<double> container)
{
	int size = container.size();
	for (int counter = 0; counter < size; counter++)
	{
		cout << "Значение: " << container[counter] << '\n';
	}
}
// Вывод вектора на экран c типом string
void out_vector_s(vector<string> container)
{
	int size = container.size();
	for (int counter = 0; counter < size; counter++)
	{
		cout << "Значение: " << container[counter] << '\n';
	}
}

// Функция перевод число из десятичной системы счисления в двоичную
vector<string> to_2(vector<double> q)
{
	vector<string> codes;
	codes.push_back("0");
	int size = q.size();
	for (int counter = 1; counter < size; counter++) // Для каждого десятичного числа, начиная со второго, т.к. первое 0
	{
		vector<int> code;
		while (q[counter] != 1) // Это сработает, потому что q - отрицательные степени двойки
		{
			q[counter] *= 2;
			code.push_back(floor(q[counter]));
			if (q[counter] > 1)
			{
				q[counter]--;
			}
		}
		// Переводим в строку
		string result;
		for (int counter2 = 0; counter2 < code.size(); counter2++)
		{
			result += code[counter2] ? '1' : '0';
		}
		codes.push_back(result);
	}
	return codes;
}

// Функция, образующая коды Шеннона
vector<string> to_sh(vector<string> q, vector<int> lengths)
{
	/*
	Завершающий штрих, функция добавляет необходимое количество нулей до необходимой длины кода.
	*/
	vector<string> sh_codes;
	int size = lengths.size(); // В данном случае размеры q и lengths совпадают
	for (int counter = 0; counter < size; counter++)
	{
		string code = q[counter];
		while (code.size() < lengths[counter])
		{
			code += "0";
		}
		sh_codes.push_back(code);
	}
	return sh_codes;
}

// Функция, проверяющая префиксность кодов
bool check_prefix(vector<string> codes)
{
	int size = codes.size();
	for (int counter = 0; counter < size; counter++) // Проход по всем кодам
	{
		for (int counter2 = counter + 1; counter2 < size; counter2++) // Проход по всем кодам, которые следует после нынешнего 
		{
			bool flag = false; // Индикатор совпадения кодов, если они нe совпали меняем значение на false
			for (int counter3 = 0; counter3 < codes[counter].size(); counter3++) // Проход по буквам текущих сравниваемых кодов 
			{
				/*
				Здесь не возникает проблемы выхода за границы массива-кода, тк изначально длинны расположены по неубыванию
				*/
				if (codes[counter] != codes[counter2])
				{
					flag = true;
				}
			}
			if (!flag)
			{
				cout << "\nДанные коды не являются префиксными\n";
				return false;
			}
		}
	}
	cout << "\nДанные коды являются префиксными\n";
	return true;
} // По факту мы проверяем префиксность неравенством крафта, но добавим еще и такую проверку
bool check_2(vector<string> codes)
{
	int size = codes.size();
	for (int counter = 0; counter < size; counter ++) // Для каждого кода
		for (int counter2 = 0; counter2 < codes[counter].size(); counter2++) // Для каждого символа кода
		{
			if ((codes[counter][counter2] != '1') && (codes[counter][counter2] != '0'))
			{
				cout << "\nДанные коды не являются двоичными\n";
				return false;
			}
		}
	cout << "\nДанные коды являются двоичными\n";
	return true;
}