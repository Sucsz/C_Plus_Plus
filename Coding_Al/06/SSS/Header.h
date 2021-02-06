#pragma once
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Сигнатуры функций
vector<bool> to_binary(unsigned);
unsigned to_dec(string);
string to_sss(unsigned, unsigned, unsigned, unsigned);
unsigned decode_sss(unsigned, unsigned, string code);

// Сигнатуры тестов
void loop_test();
