#include "shamir.h"

vector<int64_t> digitsPrimeSh() { // ��������� ������� ����� � ��������� �� 100.000 �� 1.000.000
    vector<int64_t> prime_dig; // ������ ��� ������� �����
    for (size_t i = 100'000; i <= 1'000'000; i++) {
        if (i % 2 == 1) {
            bool is_prime = true;
            for (size_t j = 3; j <= sqrt(i); j += 2) { // ���������� �� ��������� �� 3 �� ����� �� ��������
                if (i % j == 0) {
                    is_prime = false;
                    break;
                }
            }
            if (is_prime) {
                prime_dig.push_back(i); // ��������� ������ �������� �������
            }
        }
    }
    return prime_dig;
}

uint64_t inverseElementSh(int64_t a, int64_t b) { // ���������� ��������� �������� 
    int64_t x1 = 1, y1 = 0; // x � y ��� r = a, �������� � �������������� ������
    int64_t x2 = 0, y2 = 1; // x � y ��� r = b, �������� � ���������� ������
    int64_t r = a, q, x, y; // r - ������� �� �������, q - �������, x � y - �������� � ������� ������
    int64_t mdl = b; // �������� ������
    while (r > 0) {
        r = a % b;
        q = a / b;
        x = x1 - q * x2;
        y = y1 - q * y2;
        a = b; // �������� b ���������� ������� a
        b = r; // ������� r ���������� ��������� b
        x1 = x2; // �������� ���������� ������ ������������� ��������������
        x2 = x; // �������� ������� ������ ������������� ����������
        y1 = y2; // �������� ���������� ������ ������������� ��������������
        y2 = y; // �������� ������� ������ ������������� ����������
    }
    if (x1 < 0) { // ���� d �������������, ���������� �������� ������
        x1 += mdl;
    }
    return x1; // ���������� d
}

int64_t gcdSh(int64_t dig_1, int64_t dig_2) { // ��� 
    if (dig_2 == 0) { // ���� ������� = 0, �� ��� = ��������
        return dig_1; // ���������� ���
    }
    else {
        return gcdSh(dig_2, dig_1 % dig_2);  // ����� gcd, �������� ���������� �������, � ������� - ���������
    }
}

int64_t modPowSh(int64_t base, int64_t exponent, int64_t module) { // ���������� � ������� �� ������
    int64_t result = 1;
    base %= module;
    while (exponent > 0) {
        if (exponent % 2 == 1) { // ���� ������� ��������, ��������� � �� �������, ��������� ���������
            result = result * base % module;
            exponent--;
        }
        exponent /= 2;
        base = base * base % module; // ���� ������� ������, ���������� �������� �������� � �������
    }
    return result;
}

void Shamir() {
    random_device rd; // ����������� �������
    mt19937_64 random_(rd());
    vector<int64_t> prime_digits = digitsPrimeSh(); // ������� ����� �� 100.000 �� 1.000.000
    int64_t p = prime_digits[random_() % prime_digits.size() + 1]; // ��������� ������� ����� p
    int64_t Ca = 0, Cb = 0;
    while (true) {
        Ca = random_() % (p - 100'000) + 100'000; // ��������� ������� ����� ������ p, �������������� � ���
        Cb = random_() % (p - 100'000) + 100'000;
        if (gcdSh(Ca, p - 1) == 1 && gcdSh(Cb, p - 1) == 1) { // �������� �� ����������������
            break;
        }
    }
    int64_t Da = inverseElementSh(Ca, p - 1); // �������� �������� Da*Ca mod (p - 1) = 1
    int64_t Db = inverseElementSh(Cb, p - 1); // Db*Cb mod (p - 1) = 1
    cout << "������� ���������: ";
    string str; // ��������� ��� ����������
    getline(cin, str); // ���� � ���������
    try {
        ofstream out;
        out.open("input.txt"); // ��������� ���� ��� ������ ��������� ���������
        if (out.is_open())
        {
            out << str; // ������ ���������
        }
        else {
            throw string{ "�� ������� ������� ����." };
        }
        out.close(); // ��������� ����
        string stringfromfile; // ������ ��� ���������� � �����
        ifstream in("input.txt"); // ��������� ���� ��� ����������
        if (in.is_open()) {
            getline(in, stringfromfile); // ��������� � ���������
        }
        else {
            throw string{ "�� ������� ������� ����." };
        }
        in.close(); // ��������� ����
        vector<int64_t> ascii, cypher; // ������ ��� ���� ����, ������ ��� �������������� ���������
        for (auto symbol : stringfromfile) {
            ascii.push_back((int)(char)symbol); // ������� � ��� ����
        }
        cout << "\n������������� ���������: ";
        out.open("output.txt"); // ��������� ���� ��� ������ �������������� ���������
        if (out.is_open()) {
            for (auto symbol : ascii) {
                int32_t x1 = modPowSh(symbol, Ca, p); // ascii^Ca mod p
                int32_t x2 = modPowSh(x1, Cb, p); // x1^Cb mod p
                int32_t x3 = modPowSh(x2, Da, p); // x2^Da mod p, �3 - ������������� �����
                cout << x3 << " ";
                out << x3 << " "; // ������ � ����
            }
        }
        else {
            throw string{ "�� ������� ������� ����." };
        }
        out.close(); // ��������� ����
        cout << endl;
        ifstream input("output.txt"); // ��������� ���� ��� ������ �������������� ������
        if (input.is_open()) {
            copy(istream_iterator<int>(input), istream_iterator<int>(), inserter(cypher, cypher.begin())); // ������ ��������� - �������� � cypher
        }
        else {
            throw string{ "�� ������� ������� ����." };
        }
        input.close(); // ��������� ����
        cout << "\n�������������� ���������: ";
        for (auto symbol : cypher) { // �������������� ���������
            int32_t x4 = modPowSh(symbol, Db, p); // cupher^Db mod p
            cout << static_cast<char>(x4); // ��������� �� ���� � �������
        }
        cout << "\n\n";
    }
    catch (string file_error) {
        cout << "��������� ������ ��� �������� �����.";
    }
}