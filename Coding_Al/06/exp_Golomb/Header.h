#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

// ��������� �������
vector<bool> to_binary(unsigned);
unsigned to_dec(string);
string to_exp_golomb(unsigned, unsigned);
unsigned decode_exp_golomb(string, unsigned);
//��������� ������
void loop_test();