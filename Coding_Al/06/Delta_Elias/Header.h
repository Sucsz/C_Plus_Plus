#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

// ��������� �������
vector<bool> to_binary(unsigned);
unsigned to_dec(string);
string to_delta_elias(unsigned);
unsigned decode_delta_elias(string);
//��������� ������
void loop_test();