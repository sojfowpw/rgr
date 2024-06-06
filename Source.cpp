#include "rsa.h"
#include "shamir.h"
#include "vizhener.h"

bool isPassword(const string& userpassword) { // функция для проверки пароля
    string cypherpassword, result = ""; // пароль с файла, расшифрованный пароль
    int step; // шаг сдвига для шифровки
    ifstream in("password.txt"); // открываем файл для чтения пароля и шага сдвига
    if (in.is_open()) {
        in >> cypherpassword >> step;
    }
    else {
        try {
            throw string{ "Не удалось открыть файл." };
        }
        catch (string file_error) {
            cout << "Произошла ошибка при открытии файла.";
        }
    }
    in.close(); // закрываем файл
    for (int i = 0; i < cypherpassword.size(); i++) {
        if (cypherpassword[i] >= step && cypherpassword[i] <= 127) {
            result += static_cast<char>((cypherpassword[i] - step) % 128); // расшифровываем пароль
        }
        else {
            result += static_cast<char>(cypherpassword[i]);
        }
    }
    return userpassword == result; // сравниваем пароль с введённым пользователем
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
    string userpassword;
    while (true) { // ввод пароля
        cout << "Введите пароль: ";
        cin >> userpassword;
        if (isPassword(userpassword)) { // проверка пароля на правильность
            cout << "Пароль верный.\n\n";
            break;
        }
        else {
            cout << "Пароль неверный. Повторите попытку.\n\n";
        }
    }
    string comand, language; // переменная для выбора команды, выбора языка
    int begin_abc, end_abc, first_letter; // интервал кода аски для виженера, код первой буквы алфавита
    string enter;
    while (true) {
        cout << "Введите команду:\n1. RSA\n2. Шамир\n3. Виженер\n4. Выход\n\n";
        try {
            cin >> comand; // ввод команды
            cin.ignore();
            if (comand == "4") { // выход
                break;
            }
            else if (comand == "1") { // рса
                RSA();
            }
            else if (comand == "2") { // шамир
                Shamir();
            }
            else if (comand == "3") { // виженер
                cout << "Выберите язык:\n1. Русский\n2. Английский\n\n";
                cin >> language; // ввод языка
                try {
                    if (language == "2") { // английский
                        begin_abc = 0;
                        end_abc = 25;
                        first_letter = 97;
                    }
                    else if (language == "1") { // русский
                        begin_abc = 0;
                        end_abc = 31;
                        first_letter = -32;
                    }
                    else {
                        throw string{ "Неизвестный язык." }; // исключение: выбран язык, которого нет в списке
                    }
                    Vizhener(begin_abc, end_abc, first_letter);
                }
                catch (string language_error) {
                    cout << "Такого языка нет.\n\n";
                }
            }
            else {
                throw "Неизвестная команда."; // исключение: введена команда, которой нет в списке
            }
        }
        catch (const char* comand_error) {
            cout << "Неизвестная команда.\n\n";
        }
    }
    return 0;
}