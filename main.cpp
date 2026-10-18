// COMSC-210-5293 | Lab 24 | Yuyi Chen

#include <iostream>
#include <fstream>
#include <iomanip>
#include <set>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;

int select_goat(set<Goat> trip);
void delete_goat(set<Goat> &trip);
void add_goat(set<Goat> &trip, string [], string []);
void display_trip(set<Goat> trip);
int main_menu();

int main() {
    srand(time(0));
    bool again;

    set<Goat> trip;
    int choice;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // main menu loop
    do {
        choice = main_menu();
        switch (choice) {
            case 1:
                add_goat(trip, names, colors);
                break;

            case 2:
                delete_goat(trip);
                break;

            case 3:
                display_trip(trip);
                break;

            case 4:
                cout << "Quit selected.\nGoodbye!" << endl;
                break;
        }

        again = (choice != 4);
    } while (again);

    return 0;
}

// displays the main menu and validates the user's choice
// arguments: none
// returns: user's valid menu choice (1-4)
int main_menu() {
    int choice;

    cout << "\n*** GOAT MANAGER 3001 ***" << endl;
    cout << "[1] Add a goat" << endl;
    cout << "[2] Delete a goat" << endl;
    cout << "[3] List goats" << endl;
    cout << "[4] Quit" << endl;
    cout << "Choice --> ";
    cin >> choice;

    while (cin.fail() || choice < 1 || choice > 4) {
        cin.clear();
        cin.ignore(1000, '\n');

        cout << "Invalid choice. Please enter 1-4: ";
        cin >> choice;
    }

    return choice;
}

// creates a random Goat and adds it to the trip
// arguments: Goat set, names array, colors array
// returns: none
void add_goat(set<Goat> &trip, string names[], string colors[]) {
    string name = names[rand() % SZ_NAMES];
    string color = colors[rand() % SZ_COLORS];
    int age = rand() % (MAX_AGE + 1);

    Goat newGoat(name, age, color);

    pair<set<Goat>::iterator, bool> result = trip.insert(newGoat);

    if (result.second) {
        cout << "Goat added: " << name << " ("
             << age << ", " << color << ")" << endl;
    }
    else {
        cout << "Goat " << name
             << " already exists in the trip." << endl;
    }
}

// asks the user to select a valid goat number
// arguments: number of goats in the trip
// returns: the selected goat number
int select_goat(set<Goat> trip) {
    int choice;
    int size = trip.size();

    cout << "Enter goat number to delete: ";
    cin >> choice;

    while (cin.fail() || choice < 1 || choice > size) {
        cin.clear();
        cin.ignore(1000, '\n');

        cout << "Invalid choice. Enter a number from 1 to "
             << size << ": ";
        cin >> choice;
    }

    return choice;
}

// deletes the goat selected by the user
// arguments: Goat list passed by reference
// returns: none
void delete_goat(set<Goat> &trip) {
    if (trip.empty()) {
        cout << "The trip is empty." << endl;
        return;
    }

    display_trip(trip);

    int choice = select_goat(trip);

    auto it = trip.begin();

    for (int i = 1; i < choice; i++) {
        it++;
    }

    cout << "Goat deleted: " << it->get_name() << " ("
         << it->get_age() << ", "
         << it->get_color() << ")" << endl;

    trip.erase(it);
}

// displays all goats in the trip with their numbers
// arguments: Goat list
// returns: none
void display_trip(set<Goat> trip) {
    if (trip.empty()) {
        cout << "The trip is empty." << endl;
        return;
    }

    int count = 1;

    cout << "\nCurrent goats in the trip:\n";

    for (auto it = trip.begin(); it != trip.end(); it++) {
        cout << "[" << count << "] "
             << it->get_name() << " ("
             << it->get_age() << ", "
             << it->get_color() << ")" << endl;

        count++;
    }
}