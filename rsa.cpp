#include "rsa.h"

int RSA() {
    random_device rd;
    knuth_b gen(rd());
    vector<int> prime_dig = digitsPrime(); // ������ ������� ����� [100; 999]
    int64_t p = prime_dig[rd() % prime_dig.size()]; // ��������� ������� p
    int64_t q = prime_dig[rd() % prime_dig.size()]; // ��������� ������� q
    int64_t n = p * q; // �� ������������ n
    int64_t funEuler = (p - 1) * (q - 1); // ������� ������
    int64_t e = 0;
    while (true) { // ��������� ����� � ������ ������� ������ � �������������� � ���
        e = rd() % (funEuler - 10 + 1);
        if (gcd(funEuler, e) == 1) { // �������� �� ����������������
            break;
        }
    }
    int64_t d = inverseElement(e, funEuler); // d - �������� ������� d*e mod funEuler = 1
    cout << "������� ���������: ";
    string text; // ��������� ��� ����������
    getline(cin, text); // ���� � ���������
    try {
        ofstream out;
        out.open("input.txt"); // ��������� ���� ��� ����� ��������� ���������
        if (out.is_open())
        {
            out << text; // ���������� ����� � ����
        }
        else {
            throw string{ "�� ������� ������� ����." };
        }
        out.close(); // ��������� ����
        text = "";
        ifstream in("input.txt");
        if (in.is_open()) { // ��������� ���� ��� ���������� ��������� ���������
            getline(in, text); // ��������� � ���������
        }
        else {
            throw string{ "�� ������� ������� ����." };
        }
        in.close(); // ��������� ����
        vector<int64_t> ascii, cypher; // ������ ��� ���� ����, ������ ��� ������������� ��������
        for (auto symbol : text) {
            ascii.push_back(int(symbol)); // ��������� ������� � �� ��� ����
        }
        cout << endl << "������������� ���������: ";
        for (size_t i = 0; i < ascii.size(); i++) {
            cypher.push_back(modPow(ascii[i], e, n)); // ������� ��������: cypher = ascii^e mod n
            cout << cypher[i] << " ";
        }
        cout << endl;
        out.open("output.txt"); // ��������� ���� ��� ������ �������������� ����������
        if (out.is_open()) {
            for (auto symbol : cypher) {
                out << symbol << " "; // ���������� ������������� ���������
            }
        }
        else {
            throw string{ "�� ������� ������� ����." };
        }
        out.close(); // ��������� ����
        cypher.clear();
        ifstream input("output.txt"); // ��������� ���� ��� ���������� �������������� ��������� � �����
        if (input.is_open()) {
            copy(istream_iterator<int>(input), istream_iterator<int>(), inserter(cypher, cypher.begin())); // ��������� - �������� � ������ cypher
        }
        else {
            throw string{ "�� ������� ������� ����." };
        }
        input.close();
        cout << endl << "�������������� ���������: ";
        for (auto symbol : cypher) {
            cout << static_cast<unsigned char>(modPow(symbol, d, n)); // ��������������: ascii = cypher^d mod n
        }
        cout << "\n\n";
    }
    catch (string file_error) {
        cout << "��������� ������ ��� �������� �����.";
    }
    return 0;
}

vector<int> digitsPrime() { // ��������� ������� ����� � ��������� �� 100 �� 999
    vector<int> prime_dig; // ������ ��� ������� �����
    for (int i = 100; i <= 999; i++) {
        if (i % 2 == 1) {
            bool is_prime = true;
            for (int j = 3; j <= sqrt(i); j += 2) { // ���������� �� ��������� �� 3 �� ����� �� ��������
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

int64_t inverseElement(int64_t a, int64_t b) { // ���������� ��������� �������� d
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

int64_t modPow(int64_t base, int64_t exponent, int64_t module) { // ���������� � ������� �� ������
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

int64_t gcd(int64_t dig_1, int64_t dig_2) { // ��� 
    if (dig_2 == 0) { // ���� ������� = 0, �� ��� = ��������
        return dig_1; // ���������� ���
    }
    else {
        return gcd(dig_2, dig_1 % dig_2);  // ����� gcd, �������� ���������� �������, � ������� - ���������
    }
}