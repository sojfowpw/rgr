#include "rsa.h"
#include "shamir.h"
#include "vizhener.h"

bool isPassword(const string& userpassword) { // ������� ��� �������� ������
    string cypherpassword, result = ""; // ������ � �����, �������������� ������
    int step; // ��� ������ ��� ��������
    ifstream in("password.txt"); // ��������� ���� ��� ������ ������ � ���� ������
    if (in.is_open()) {
        in >> cypherpassword >> step;
    }
    else {
        try {
            throw string{ "�� ������� ������� ����." };
        }
        catch (string file_error) {
            cout << "��������� ������ ��� �������� �����.";
        }
    }
    in.close(); // ��������� ����
    for (int i = 0; i < cypherpassword.size(); i++) {
        if (cypherpassword[i] >= step && cypherpassword[i] <= 127) {
            result += static_cast<char>((cypherpassword[i] - step) % 128); // �������������� ������
        }
        else {
            result += static_cast<char>(cypherpassword[i]);
        }
    }
    return userpassword == result; // ���������� ������ � �������� �������������
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
    string userpassword;
    while (true) { // ���� ������
        cout << "������� ������: ";
        cin >> userpassword;
        if (isPassword(userpassword)) { // �������� ������ �� ������������
            cout << "������ ������.\n\n";
            break;
        }
        else {
            cout << "������ ��������. ��������� �������.\n\n";
        }
    }
    string comand, language; // ���������� ��� ������ �������, ������ �����
    int begin_abc, end_abc, first_letter; // �������� ���� ���� ��� ��������, ��� ������ ����� ��������
    string enter;
    while (true) {
        cout << "������� �������:\n1. RSA\n2. �����\n3. �������\n4. �����\n\n";
        try {
            cin >> comand; // ���� �������
            cin.ignore();
            if (comand == "4") { // �����
                break;
            }
            else if (comand == "1") { // ���
                RSA();
            }
            else if (comand == "2") { // �����
                Shamir();
            }
            else if (comand == "3") { // �������
                cout << "�������� ����:\n1. �������\n2. ����������\n\n";
                cin >> language; // ���� �����
                try {
                    if (language == "2") { // ����������
                        begin_abc = 0;
                        end_abc = 25;
                        first_letter = 97;
                    }
                    else if (language == "1") { // �������
                        begin_abc = 0;
                        end_abc = 31;
                        first_letter = -32;
                    }
                    else {
                        throw string{ "����������� ����." }; // ����������: ������ ����, �������� ��� � ������
                    }
                    Vizhener(begin_abc, end_abc, first_letter);
                }
                catch (string language_error) {
                    cout << "������ ����� ���.\n\n";
                }
            }
            else {
                throw "����������� �������."; // ����������: ������� �������, ������� ��� � ������
            }
        }
        catch (const char* comand_error) {
            cout << "����������� �������.\n\n";
        }
    }
    return 0;
}