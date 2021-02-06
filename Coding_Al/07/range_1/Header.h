#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

// Сигнтары функций
map<char, int> frequency_analysis(string);
void show_freq_table(map<char, int>);
string to_range_1(string);
string decode_range_1(vector<char>, string);

// Сигнатуры тестов
void tests();
void test_1();
void test_2();
void test_3();
void test_4();
void test_5();