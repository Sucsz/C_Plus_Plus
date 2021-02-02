#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

// Сигнатуры функций
vector<vector<int>> to_lz78(string);
void show_code(vector<vector<int>>);
string decode_lz78(vector<vector<int>>);
// Сигнатуры тестов
void test_1();
void test_2();
void test_3();
void test_4();
void test_5();
void tests();