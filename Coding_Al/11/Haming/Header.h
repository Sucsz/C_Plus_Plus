#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

// ��������� �������
vector<bool> to_binary(unsigned);
unsigned to_dec(string);
string to_haming(unsigned);
string do_wrong_code(string);
string fix_wrong(string);
unsigned decode_ham(string);
// ��������� ������
void loop_tests();