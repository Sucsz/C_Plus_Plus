#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

// Сигнатуры функций
vector<bool> to_binary(unsigned);
unsigned to_dec(string);
string to_gamma_elias(unsigned);
unsigned decode_gamma_elias(string);
//Сигнатуры тестов
void loop_test();