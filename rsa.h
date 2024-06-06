#pragma once
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <random>
#include "Windows.h"

using namespace std;

vector<int> digitsPrime(); // генерация простых чисел в диапазоне от 100 до 999
int64_t inverseElement(int64_t a, int64_t b); // нахождение обратного элемента d
int64_t modPow(int64_t base, int64_t exponent, int64_t module); // возведение в степень по модулю
int64_t gcd(int64_t dig_1, int64_t dig_2); // НОД
int RSA();