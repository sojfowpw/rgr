#include "vizhener.h"

int Vizhener(int begin_abc, int end_abc, int first_letter) { // диапазон кода аски, код первой буквы алфавита
    cout << "Введите ключ: ";
    string key; // вводим ключ
    cin >> key;
    cin.ignore();
    cout << "\nВведите сообщение: ";
    string text; // вводим сообщение для шифрования
    getline(cin, text); // ввод с пробелами
    try {
        ofstream out;
        out.open("input.txt"); // открываем файл для записи исходного сообщения
        if (out.is_open())
        {
            out << text; // запись в файл
        }
        else {
            throw 0;
        }
        out.close(); // закрываем файл
        text = "";
        ifstream in("input.txt"); // открываем файл для чтения сообщения
        if (in.is_open()) {
            getline(in, text); // читаем сообщение с пробелами
        }
        else {
            throw 0;
        }
        in.close(); // закрываем файл
        transform(text.begin(), text.end(), text.begin(), [](char c) {
            return tolower(c); }); // переводим все буквы в нижний регистр в сообщении
        transform(key.begin(), key.end(), key.begin(), [](char c) {
            return tolower(c); }); // переводим все буквы в нижний регистр в ключе
        vector<int> ascii_text, ascii_key; // вектор для кода аски сообщения, ключа
        for (auto symbol : text) {
            ascii_text.push_back((int)(char)symbol - first_letter); // находим порядковый номер буквы сообщения в алфавите
            if ((int)(char)symbol - first_letter < begin_abc || (int)(char)symbol - first_letter > end_abc) {
                if (!(31 < (int)(char)symbol && (int)(char)symbol < 65) && !(90 < (int)(char)symbol && (int)(char)symbol < 97) && !(122 < (int)(char)symbol && (int)(char)symbol < 128)) {
                    try {
                        throw "Некорректное сообщение."; // исключение: в тексте встречаются символы из другого алфавита
                    }
                    catch (const char* text_error) {
                        cout << "Текст должен состоять только из букв алфавита выбранного языка, цифр и других символов.\n\n";
                        return 1;
                    }
                }
            }
        }
        for (auto symbol : key) {
            ascii_key.push_back((int)(char)symbol - first_letter); // находим порядковый номер буквы ключа в алфавите
            if ((int)(char)symbol - first_letter < begin_abc || (int)(char)symbol - first_letter > end_abc) {
                try {
                    throw string{ "Некорректный ключ." }; // исключение: ключ не состоит из выбранного алфавита
                }
                catch (string key_error) {
                    cout << "Ключ должен состоять только из букв алфавита выбранного языка.\n\n";
                    return 1;
                }
            }
        }
        vector<int> cypher; // вектор для зашифрованного сообщения
        int index_key = 0; // текущий индекс ключа
        for (auto symbol : ascii_text) {
            if (begin_abc <= symbol && symbol <= end_abc) { // если символ - буква
                cypher.push_back((symbol + ascii_key[index_key]) % (end_abc + 1)); // шифруем cypher = (номер буквы сообщения + ключа) % мощность алфавита
                index_key++;
                if (index_key == key.size()) { // обнуляем индекс ключа, если слово ключа закончилось
                    index_key = 0;
                }
            }
            else {
                cypher.push_back(symbol);
            }
        }
        cout << "\nЗашифрованное сообщение: ";
        out.open("output.txt"); // открываем файл для записи зашифрованного сообщения
        if (out.is_open()) {
            for (auto symbol : cypher) {
                out << static_cast<char>(symbol + first_letter); // записываем зашифрованное сообщение, переводя код аски в символы
                cout << static_cast<char>(symbol + first_letter);
            }
        }
        else {
            throw 0;
        }
        out.close(); // закрываем файл
        cout << endl;
        string message; // строка для считывания с файла
        ascii_text.clear();
        ifstream input("output.txt"); // открываем файл для считывания зашифрованного сообщения
        if (input.is_open()) {
            getline(input, message); // считываем с пробелами
        }
        else {
            throw 0;
        }
        input.close(); // закрываем файл
        for (auto symbol : message) {
            ascii_text.push_back((int)(char)symbol - first_letter); // снова находим порядковый номер буквы в алфавите
        }
        index_key = 0; // текущий индекс ключа
        cout << "\nРасшифрованное сообщение: ";
        for (auto symbol : ascii_text) {
            if (begin_abc <= symbol && symbol <= end_abc) { // если символ - буква из алфавита
                cout << static_cast<char>((symbol + (end_abc + 1) - ascii_key[index_key]) % (end_abc + 1) + first_letter);
                index_key++; // расшифровываем: (шифр - ключ + мощность алфавита) % мощность алфавита
                if (index_key == key.size()) { // обнуляем индекс ключа, если слово ключа закончилось
                    index_key = 0;
                }
            }
            else {
                cout << static_cast<char>(symbol + first_letter); // выводим сообщение
            }
        }
        cout << "\n\n";
    }
    catch (int file_error) {
        cout << "Произошла ошибка при открытии файла.";
    }
    return 0;
}