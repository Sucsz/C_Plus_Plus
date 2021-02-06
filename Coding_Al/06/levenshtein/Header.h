#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

// Сигнатуры функций
vector<bool> to_binary_sub(unsigned);
unsigned to_dec(string);
string to_levenshtein(unsigned);
unsigned decode_levenshtein(string);
// Сигнатуры тестов
void loop_test();
