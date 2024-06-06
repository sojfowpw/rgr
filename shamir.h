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

vector<int64_t> digitsPrimeSh(); // генерация простых чисел в диапазоне от 100.000 до 1.000.000
uint64_t inverseElementSh(int64_t a, int64_t b); // нахождение обратного элемента 
int64_t gcdSh(int64_t dig_1, int64_t dig_2); // НОД 
int64_t modPowSh(int64_t base, int64_t exponent, int64_t module); // возведение в степень по модулю
void Shamir();