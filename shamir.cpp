#include "shamir.h"

vector<int64_t> digitsPrimeSh() { // генерация простых чисел в диапазоне от 100.000 до 1.000.000
    vector<int64_t> prime_dig; // вектор для простых чисел
    for (size_t i = 100'000; i <= 1'000'000; i++) {
        if (i % 2 == 1) {
            bool is_prime = true;
            for (size_t j = 3; j <= sqrt(i); j += 2) { // проходимся по делителям от 3 до корня из делимого
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

uint64_t inverseElementSh(int64_t a, int64_t b) { // нахождение обратного элемента 
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

int64_t gcdSh(int64_t dig_1, int64_t dig_2) { // НОД 
    if (dig_2 == 0) { // если остаток = 0, то НОД = делитель
        return dig_1; // возвращаем НОД
    }
    else {
        return gcdSh(dig_2, dig_1 % dig_2);  // вызов gcd, делитель становится делимым, а остаток - делителем
    }
}

int64_t modPowSh(int64_t base, int64_t exponent, int64_t module) { // возведение в степень по модулю
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

void Shamir() {
    random_device rd; // подключение рандома
    mt19937_64 random_(rd());
    vector<int64_t> prime_digits = digitsPrimeSh(); // простые числа от 100.000 до 1.000.000
    int64_t p = prime_digits[random_() % prime_digits.size() + 1]; // случайное простое число p
    int64_t Ca = 0, Cb = 0;
    while (true) {
        Ca = random_() % (p - 100'000) + 100'000; // случайные простые числа меньше p, взаимообратные с ним
        Cb = random_() % (p - 100'000) + 100'000;
        if (gcdSh(Ca, p - 1) == 1 && gcdSh(Cb, p - 1) == 1) { // проверка на взаимообратность
            break;
        }
    }
    int64_t Da = inverseElementSh(Ca, p - 1); // обратные элементы Da*Ca mod (p - 1) = 1
    int64_t Db = inverseElementSh(Cb, p - 1); // Db*Cb mod (p - 1) = 1
    cout << "Введите сообщение: ";
    string str; // сообщение для шифрования
    getline(cin, str); // ввод с пробелами
    try {
        ofstream out;
        out.open("input.txt"); // открываем файл для записи введённого сообщения
        if (out.is_open())
        {
            out << str; // запись сообщения
        }
        else {
            throw string{ "Не удалось открыть файл." };
        }
        out.close(); // закрываем файл
        string stringfromfile; // строка для считывания с файла
        ifstream in("input.txt"); // открываем файл для считывания
        if (in.is_open()) {
            getline(in, stringfromfile); // считываем с пробелами
        }
        else {
            throw string{ "Не удалось открыть файл." };
        }
        in.close(); // закрываем файл
        vector<int64_t> ascii, cypher; // вектор для кода аски, вектор для зашифрованного сообщения
        for (auto symbol : stringfromfile) {
            ascii.push_back((int)(char)symbol); // перевод в код аски
        }
        cout << "\nЗашифрованное сообщение: ";
        out.open("output.txt"); // открываем файл для записи зашифрованного сообщения
        if (out.is_open()) {
            for (auto symbol : ascii) {
                int32_t x1 = modPowSh(symbol, Ca, p); // ascii^Ca mod p
                int32_t x2 = modPowSh(x1, Cb, p); // x1^Cb mod p
                int32_t x3 = modPowSh(x2, Da, p); // x2^Da mod p, х3 - зашифрованный текст
                cout << x3 << " ";
                out << x3 << " "; // запись в файл
            }
        }
        else {
            throw string{ "Не удалось открыть файл." };
        }
        out.close(); // закрываем файл
        cout << endl;
        ifstream input("output.txt"); // открываем файл для чтения зашифрованного текста
        if (input.is_open()) {
            copy(istream_iterator<int>(input), istream_iterator<int>(), inserter(cypher, cypher.begin())); // читаем сообщение - копируем в cypher
        }
        else {
            throw string{ "Не удалось открыть файл." };
        }
        input.close(); // закрываем файл
        cout << "\nРасшифрованное сообщение: ";
        for (auto symbol : cypher) { // расшифровываем сообщение
            int32_t x4 = modPowSh(symbol, Db, p); // cupher^Db mod p
            cout << static_cast<char>(x4); // переводим из аски в символы
        }
        cout << "\n\n";
    }
    catch (string file_error) {
        cout << "Произошла ошибка при открытии файла.";
    }
}