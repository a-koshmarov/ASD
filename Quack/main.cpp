#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <queue>

using namespace std;

int main() {
    long long a, b;
    string command, label;
    char reg;
    vector<string> commands;
    queue<long long> values;
    map<string, long long> labels;
    map<char, long long> registers;


    ifstream fin("quack.in");
//    ofstream fout("quack.out");
    freopen("quack.out", "w", stdout);

    // Записываем текст программы и индексы для переходов
    long long index = 0;
    while (true) {
        fin >> command;
        if (fin.eof()) break;
        commands.push_back(command);
        if (command[0] == ':') {
            label = command.substr(1, command.size() - 1);
            labels[label] = index;
        }
        index++;

    }

    // Исполнение программы
    for (long long i = 0; i < commands.size(); i++) {
        command = commands[i];
        if (isdigit(command[0])) {
            values.push(stoi(command));
        } else if (command[0] == '+') {
            a = values.front();
            values.pop();
            b = values.front();
            values.pop();
            long long val = a + b;
            values.push(val % 65536);
        } else if (command[0] == '-') {
            a = values.front();
            values.pop();
            b = values.front();
            values.pop();
            long long val = ((a - b) % 65536 + 65536);
            values.push(val % 65536);
        } else if (command[0] == '/') {
            a = values.front();
            values.pop();
            b = values.front();
            values.pop();
            if (a == 0 || b == 0) {
                values.push(0);
            } else {
                values.push((a / b) % 65536);
            }
        } else if (command[0] == '*') {
            a = values.front();
            values.pop();
            b = values.front();
            values.pop();

            long long val = a * b;
            values.push(val % 65536);
        } else if (command[0] == '%') {
            a = values.front();
            values.pop();
            b = values.front();
            values.pop();
            if (a== 0 || b == 0) {
                values.push(0);
            } else {
                values.push((a % b) % 65536);
            }
        } else if (command[0] == '>') {
            reg = command[1];
            a = values.front();
            values.pop();

            registers[reg] = a;
//            cout << "getting "<< a << endl;
        } else if (command[0] == '<') {
            reg = command[1];
            a = registers[reg];
//            cout << "setting " << reg << " to " << a << endl;
            values.push(a);
        } else if (command[0] == 'P') {
            if (command.size() == 1) {
                a = values.front();
                values.pop();
                cout << a << endl;
            } else {
                reg = command[1];
                a = registers[reg];
                cout << a << endl;
            }
        } else if (command[0] == 'C') {
            if (command.size() == 1) {
                a = values.front();
                values.pop();
                printf("%c", (a % 256));
            } else {
                reg = command[1];
                a = registers[reg];
                printf("%c", (a % 256));
            }
        } else if (command[0] == 'J') {
            label = command.substr(1, command.size() - 1);
            i = labels[label];
//            cout << "going to " << label << " of index "<< i << endl;
        } else if (command[0] == 'Z') {
            reg = command[1];
            if (!registers[reg]) {
                label = command.substr(2, command.size() - 2);
                i = labels[label];
            }
        } else if (command[0] == 'E') {
            char reg1, reg2;
            reg1 = command[1];
            reg2 = command[2];
            if (registers[reg1] == registers[reg2]) {
                label = command.substr(3, command.size() - 3);
                i = labels[label];
            }
        } else if (command[0] == 'G') {
            char reg1, reg2;
            reg1 = command[1];
            reg2 = command[2];
            if (registers[reg1] > registers[reg2]) {
                label = command.substr(3, command.size() - 3);
                i = labels[label];
            }
        } else if (command[0] == 'Q') {
            fin.close();
            fclose(stdout);
            return 0;
        }
    }
//    long long f = 2, x = 10;
//    cout << ((f - x) % 65536 + 65536) % 65536 << endl << (f - x) % 65536 << endl;
    fin.close();
    fclose(stdout);
    return 0;
}