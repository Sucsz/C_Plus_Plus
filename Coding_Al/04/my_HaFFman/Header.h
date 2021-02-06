#pragma once
#include <map>
#include <queue>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;
struct Node // Узел дерева Хаффмана
{
	int rib;
	string code;
	char symbol;
	string value; // Здесь будет лежать конкатенация символов узлов
	unsigned amount;
	Node* left;
	Node* right;
	Node(char sym, unsigned am) { symbol = sym; value = sym; amount = am; left = right = 0; } // Конструктов по-умолчнанию для создания объекта-компоратора
	Node(Node* l, Node* r) { symbol = NULL; rib = -1; value += l->value; value += r->value; left = l; right = r; amount = l->amount + r->amount; } // Объединение узлов в один, нам безразлично, как называется данный узел
};							 // Инициализация "невозможными" случаями

struct Compare
{
	bool operator() (Node* x, Node* y) { return x->amount > y->amount; }	// Компаратор
};

// Сигнатуры функций
map<char, int> frequency_analysis(string);
void show_freq_table(map<char, int>);
void show_table_codes(map<char, string>);
priority_queue<Node*, vector<Node*>, Compare> fill_tree(map<char, int>);
priority_queue<Node*, vector<Node*>, Compare> to_haffamn(priority_queue<Node*, vector<Node*>, Compare>);
void traversal_tree(map<char, string>*, Node*, string, unsigned k = 0);
void check_kraft(map<char, string>);
string encoding_to_code(string input, map<char, string>);
string decoding_to_decode(string code, map<char, string>);
double avg(map <char, string>);
// Сигнатуры тестов
void test_encode_1();
void test_encode_2();
void test_encode_3();
void test_encode_4();
void test_encode_5();
void tests_encode(); // Тесты кодирования
void test_decode_1();
void test_decode_2();
void test_decode_3();
void test_decode_4();
void test_decode_5();
void tests_decode(); // Тесты декодирования