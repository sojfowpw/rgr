#include "vizhener.h"

int Vizhener(int begin_abc, int end_abc, int first_letter) { // �������� ���� ����, ��� ������ ����� ��������
    cout << "������� ����: ";
    string key; // ������ ����
    cin >> key;
    cin.ignore();
    cout << "\n������� ���������: ";
    string text; // ������ ��������� ��� ����������
    getline(cin, text); // ���� � ���������
    try {
        ofstream out;
        out.open("input.txt"); // ��������� ���� ��� ������ ��������� ���������
        if (out.is_open())
        {
            out << text; // ������ � ����
        }
        else {
            throw 0;
        }
        out.close(); // ��������� ����
        text = "";
        ifstream in("input.txt"); // ��������� ���� ��� ������ ���������
        if (in.is_open()) {
            getline(in, text); // ������ ��������� � ���������
        }
        else {
            throw 0;
        }
        in.close(); // ��������� ����
        transform(text.begin(), text.end(), text.begin(), [](char c) {
            return tolower(c); }); // ��������� ��� ����� � ������ ������� � ���������
        transform(key.begin(), key.end(), key.begin(), [](char c) {
            return tolower(c); }); // ��������� ��� ����� � ������ ������� � �����
        vector<int> ascii_text, ascii_key; // ������ ��� ���� ���� ���������, �����
        for (auto symbol : text) {
            ascii_text.push_back((int)(char)symbol - first_letter); // ������� ���������� ����� ����� ��������� � ��������
            if ((int)(char)symbol - first_letter < begin_abc || (int)(char)symbol - first_letter > end_abc) {
                if (!(31 < (int)(char)symbol && (int)(char)symbol < 65) && !(90 < (int)(char)symbol && (int)(char)symbol < 97) && !(122 < (int)(char)symbol && (int)(char)symbol < 128)) {
                    try {
                        throw "������������ ���������."; // ����������: � ������ ����������� ������� �� ������� ��������
                    }
                    catch (const char* text_error) {
                        cout << "����� ������ �������� ������ �� ���� �������� ���������� �����, ���� � ������ ��������.\n\n";
                        return 1;
                    }
                }
            }
        }
        for (auto symbol : key) {
            ascii_key.push_back((int)(char)symbol - first_letter); // ������� ���������� ����� ����� ����� � ��������
            if ((int)(char)symbol - first_letter < begin_abc || (int)(char)symbol - first_letter > end_abc) {
                try {
                    throw string{ "������������ ����." }; // ����������: ���� �� ������� �� ���������� ��������
                }
                catch (string key_error) {
                    cout << "���� ������ �������� ������ �� ���� �������� ���������� �����.\n\n";
                    return 1;
                }
            }
        }
        vector<int> cypher; // ������ ��� �������������� ���������
        int index_key = 0; // ������� ������ �����
        for (auto symbol : ascii_text) {
            if (begin_abc <= symbol && symbol <= end_abc) { // ���� ������ - �����
                cypher.push_back((symbol + ascii_key[index_key]) % (end_abc + 1)); // ������� cypher = (����� ����� ��������� + �����) % �������� ��������
                index_key++;
                if (index_key == key.size()) { // �������� ������ �����, ���� ����� ����� �����������
                    index_key = 0;
                }
            }
            else {
                cypher.push_back(symbol);
            }
        }
        cout << "\n������������� ���������: ";
        out.open("output.txt"); // ��������� ���� ��� ������ �������������� ���������
        if (out.is_open()) {
            for (auto symbol : cypher) {
                out << static_cast<char>(symbol + first_letter); // ���������� ������������� ���������, �������� ��� ���� � �������
                cout << static_cast<char>(symbol + first_letter);
            }
        }
        else {
            throw 0;
        }
        out.close(); // ��������� ����
        cout << endl;
        string message; // ������ ��� ���������� � �����
        ascii_text.clear();
        ifstream input("output.txt"); // ��������� ���� ��� ���������� �������������� ���������
        if (input.is_open()) {
            getline(input, message); // ��������� � ���������
        }
        else {
            throw 0;
        }
        input.close(); // ��������� ����
        for (auto symbol : message) {
            ascii_text.push_back((int)(char)symbol - first_letter); // ����� ������� ���������� ����� ����� � ��������
        }
        index_key = 0; // ������� ������ �����
        cout << "\n�������������� ���������: ";
        for (auto symbol : ascii_text) {
            if (begin_abc <= symbol && symbol <= end_abc) { // ���� ������ - ����� �� ��������
                cout << static_cast<char>((symbol + (end_abc + 1) - ascii_key[index_key]) % (end_abc + 1) + first_letter);
                index_key++; // ��������������: (���� - ���� + �������� ��������) % �������� ��������
                if (index_key == key.size()) { // �������� ������ �����, ���� ����� ����� �����������
                    index_key = 0;
                }
            }
            else {
                cout << static_cast<char>(symbol + first_letter); // ������� ���������
            }
        }
        cout << "\n\n";
    }
    catch (int file_error) {
        cout << "��������� ������ ��� �������� �����.";
    }
    return 0;
}