#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Сигнатуры функций
vector<pair<int, char> > to_rle(string);
void show_code(vector<pair<int, char> >);
string decode_rle(vector<pair<int, char> >);
void test_1();
void test_2();
void test_3();
void test_4();
void test_5();
void tests();
