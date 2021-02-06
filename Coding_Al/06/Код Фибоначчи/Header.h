#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

// Сигнатуры функций
vector<bool> to_fib(unsigned long long);
string to_fib_code(unsigned long long);
unsigned decode_fib_code(string);
// Сигнатуры тестов
void loop_test();