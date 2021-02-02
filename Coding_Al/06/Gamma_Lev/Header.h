#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

// Сигнатуры функций
vector<bool> to_binary(unsigned);
unsigned to_dec(string);
string to_gam_lev(unsigned);
unsigned decode_gam_lev(string);
// Сигнатуры тестов
void loop_test();