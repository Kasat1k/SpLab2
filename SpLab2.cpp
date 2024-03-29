﻿#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <locale> 

using namespace std;

// Структура, яка представляє скінчений автомат
struct Automaton {
    int start_state; // Початковий стан автомата
    unordered_set<int> final_states; // Множина фінальних станів автомата
    unordered_map<int, unordered_map<char, int>> transitions; // Відображення для функції переходів
};

// Функція для зчитування опису автомата з файлу
Automaton read_automaton(const string& filename) {
    Automaton automaton;
    ifstream file(filename);

    // Перевірка, чи вдалося відкрити файл
    if (!file.is_open()) {
        throw runtime_error("Помилка при відкритті файлу");
    }

    int alphabet_size, states_size;
    file >> alphabet_size;
   // cout << "alphabet_size " << alphabet_size << endl;

    // Зчитування символів алфавіту
   //vector<char> alphabet(alphabet_size);
   // for (int i = 0; i < alphabet_size; i++) {
    //    file >> alphabet[i];
    //}
    

    file >> states_size >> automaton.start_state;
   // cout << "states_size " << states_size << endl;
    //cout << "automaton.start_state " << automaton.start_state << endl;
    int final_states_size;
    file >> final_states_size;
   // cout << "final_states_size " << final_states_size << endl;
    // Зчитування фінальних станів
    for (int i = 0; i < final_states_size; ++i) {
        int state;
        file >> state;
        automaton.final_states.insert(state);
      //  cout << "final_state " << state << endl;
    }

    int from, to;
    char symbol;
    while (file >> from >> symbol >> to) {
        // Зчитування інформації про переходи між станами
        automaton.transitions[from][symbol] = to;
    }

    file.close();
    return automaton;
}

// Функція для перевірки, чи автомат приймає дане слово
bool is_accepted(const Automaton& automaton, const string& word) {
    int current_state = automaton.start_state;
    for (char symbol : word) {
        auto it = automaton.transitions.find(current_state);
        if (it == automaton.transitions.end()) {
            return false; // Немає переходів з поточного стану
        }

        auto symbol_it = it->second.find(symbol);
        if (symbol_it == it->second.end()) {
            return false; // Немає переходу по поточному символу
        }

        current_state = symbol_it->second;
    }

    return automaton.final_states.count(current_state) > 0;
}

int main() {
    setlocale(LC_ALL, "Ukrainian");
    try {
        Automaton automaton = read_automaton("H:\\SPLab2.txt");

        string w0, w1;
        cout << "Введіть фіксовану частину слова w0: ";
        cin >> w0;
        cout << "Введіть слово w1: ";
        cin >> w1;

        string w = w0 + w1;
        if (is_accepted(automaton, w)) {
            cout << "Слово " << w << " приймається автоматом.\n";
        }
        else {
            cout << "Слово " << w << " не приймається автоматом.\n";
        }

    }
    catch (const exception& e) {
        cerr << "Помилка: " << e.what() << "\n";
    }

    return 0;
}