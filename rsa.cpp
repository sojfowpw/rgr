#include "rsa.h"

int RSA() {
    random_device rd;
    knuth_b gen(rd());
    vector<int> prime_dig = digitsPrime(); // вектор простых чисел [100; 999]
    int64_t p = prime_dig[rd() % prime_dig.size()]; // случайное простое p
    int64_t q = prime_dig[rd() % prime_dig.size()]; // случайное простое q
    int64_t n = p * q; // их произведение n
    int64_t funEuler = (p - 1) * (q - 1); // функция Эйлера
    int64_t e = 0;
    while (true) { // случайное число е меньше функции Эйлера и взаимообратное с ней
        e = rd() % (funEuler - 10 + 1);
        if (gcd(funEuler, e) == 1) { // проверка на взаимообратность
            break;
        }
    }
    int64_t d = inverseElement(e, funEuler); // d - обратный элемент d*e mod funEuler = 1
    cout << "Введите сообщение: ";
    string text; // сообщение для шифрования
    getline(cin, text); // ввод с пробелами
    try {
        ofstream out;
        out.open("input.txt"); // открываем файл для ввода исходного сообщения
        if (out.is_open())
        {
            out << text; // записываем текст в файл
        }
        else {
            throw string{ "Не удалось открыть файл." };
        }
        out.close(); // закрываем файл
        text = "";
        ifstream in("input.txt");
        if (in.is_open()) { // открываем файл для считывания исходного сообщения
            getline(in, text); // считываем с пробелами
        }
        else {
            throw string{ "Не удалось открыть файл." };
        }
        in.close(); // закрываем файл
        vector<int64_t> ascii, cypher; // вектор для кода аски, вектор для зашифрованных символов
        for (auto symbol : text) {
            ascii.push_back(int(symbol)); // переводим символы в их код аски
        }
        cout << endl << "Зашифрованное сообщение: ";
        for (size_t i = 0; i < ascii.size(); i++) {
            cypher.push_back(modPow(ascii[i], e, n)); // шифруем значения: cypher = ascii^e mod n
            cout << cypher[i] << " ";
        }
        cout << endl;
        out.open("output.txt"); // открываем файл для записи зашифрованного сообщениия
        if (out.is_open()) {
            for (auto symbol : cypher) {
                out << symbol << " "; // записываем зашифрованное сообщение
            }
        }
        else {
            throw string{ "Не удалось открыть файл." };
        }
        out.close(); // закрываем файл
        cypher.clear();
        ifstream input("output.txt"); // открываем файл для считывания зашифрованного сообщения с файла
        if (input.is_open()) {
            copy(istream_iterator<int>(input), istream_iterator<int>(), inserter(cypher, cypher.begin())); // считываем - копируем в вектор cypher
        }
        else {
            throw string{ "Не удалось открыть файл." };
        }
        input.close();
        cout << endl << "Расшифрованное сообщение: ";
        for (auto symbol : cypher) {
            cout << static_cast<unsigned char>(modPow(symbol, d, n)); // расшифровываем: ascii = cypher^d mod n
        }
        cout << "\n\n";
    }
    catch (string file_error) {
        cout << "Произошла ошибка при открытии файла.";
    }
    return 0;
}

vector<int> digitsPrime() { // генерация простых чисел в диапазоне от 100 до 999
    vector<int> prime_dig; // вектор для простых чисел
    for (int i = 100; i <= 999; i++) {
        if (i % 2 == 1) {
            bool is_prime = true;
            for (int j = 3; j <= sqrt(i); j += 2) { // проходимся по делителям от 3 до корня из делимого
                if (i % j == 0) {
                    is_prime = false;
                    break;
                }
            }
            if (is_prime) {
                prime_dig.push_back(i); // заполняем вектор простыми числами
            }
        }
    }
    return prime_dig;
}

int64_t inverseElement(int64_t a, int64_t b) { // нахождение обратного элемента d
    int64_t x1 = 1, y1 = 0; // x и y при r = a, значения в предпредыдущей строке
    int64_t x2 = 0, y2 = 1; // x и y при r = b, значения в предыдущей строке
    int64_t r = a, q, x, y; // r - остаток от деления, q - частное, x и y - значения в текущей строке
    int64_t mdl = b; // значение модуля
    while (r > 0) {
        r = a % b;
        q = a / b;
        x = x1 - q * x2;
        y = y1 - q * y2;
        a = b; // делитель b становится делимым a
        b = r; // остаток r становится делителем b
        x1 = x2; // значения предыдущей строки присваиваются предпредыдущей
        x2 = x; // значения текущей строки присваиваются предыдущей
        y1 = y2; // значения предыдущей строки присваиваются предпредыдущей
        y2 = y; // значения текущей строки присваиваются предыдущей
    }
    if (x1 < 0) { // если d отрицательное, прибавляем значение модуля
        x1 += mdl;
    }
    return x1; // возвращаем d
}

int64_t modPow(int64_t base, int64_t exponent, int64_t module) { // возведение в степень по модулю
    int64_t result = 1;
    base %= module;
    while (exponent > 0) {
        if (exponent % 2 == 1) { // если степень нечётная, уменьшаем её на единицу, сохраняем результат
            result = result * base % module;
            exponent--;
        }
        exponent /= 2;
        base = base * base % module; // если степень чётная, предыдущее значение возводим в квадрат
    }
    return result;
}

int64_t gcd(int64_t dig_1, int64_t dig_2) { // НОД 
    if (dig_2 == 0) { // если остаток = 0, то НОД = делитель
        return dig_1; // возвращаем НОД
    }
    else {
        return gcd(dig_2, dig_1 % dig_2);  // вызов gcd, делитель становится делимым, а остаток - делителем
    }
}