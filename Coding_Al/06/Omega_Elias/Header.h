#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

// Сигнатуры тестов
vector<bool> to_binary(unsigned);
unsigned to_dec(string);
string to_omega_elias(unsigned);
unsigned decode_omega_elias(string);
void loop_test();