#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ��������� �������
vector<vector<int>> to_lzss(string);
void show_code(vector<vector<int>>);
string decode_lzss(vector<vector<int>>);
// ��������� ������
void test_1();
void test_2();
void test_3();
void test_4();
void test_5();
void tests();