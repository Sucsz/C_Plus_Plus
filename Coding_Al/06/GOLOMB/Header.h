#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

// Сигнатуры функций
vector<bool> to_binary(unsigned);
unsigned to_dec(string);
string to_golomb(unsigned, unsigned);
unsigned decode_golomb(string, unsigned);
//Сигнатуры тестов
void loop_test();