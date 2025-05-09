#ifndef HANDLER_H
#define HANDLER_H

#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
using namespace std;

const int MAX_USERS = 20;
const int MAX_HABITS = 20;

struct Habit {
    string name;
    string category;
    int streak;
    time_t lastCheckIn;

    Habit(): name(""), category(""), streak(0), lastCheckIn(0) {}
    Habit(string n, string c): name(n), category(c), streak(0), lastCheckIn(0) {}

    void markComplete() {
        time_t now = time(nullptr);
        if (difftime(now, lastCheckIn) >= 86400) {
            streak++;
            lastCheckIn = now;
            cout << "Habit checked in!  Streak: " << streak << "\n";
        } else {
            cout << "Already checked in today.\n";
        }
    }
};

class User {
public:
    string   username;
    string   password;
    Habit    habits[MAX_HABITS];
    int      habitCount;

    User(): username(""), password(""), habitCount(0) {}
    User(string u, string p): username(u), password(p), habitCount(0) {}

    void addHabit(const string& n, const string& c) {
        if (habitCount < MAX_HABITS) {
            habits[habitCount++] = Habit(n, c);
            cout << "Added \"" << n << "\" in [" << c << "]\n";
        } else {
            cout << "Max habits reached.\n";
        }
    }

    void editHabit(int idx, const string& n, const string& c) {
        if (idx >= 0 && idx < habitCount) {
            habits[idx].name     = n;
            habits[idx].category = c;
            cout << "Habit updated.\n";
        } else {
            cout << "Invalid habit number.\n";
        }
    }

    void deleteHabit(int idx) {
        if (idx >= 0 && idx < habitCount) {
            for (int j = idx; j + 1 < habitCount; ++j)
                habits[j] = habits[j+1];
            habitCount--;
            cout << "Habit deleted.\n";
        } else {
            cout << "Invalid habit number.\n";
        }
    }

    void checkIn(int idx) {
        if (idx >= 0 && idx < habitCount)
            habits[idx].markComplete();
        else
            cout << "Invalid habit number.\n";
    }

    void showProgress() {
        if (habitCount == 0) {
            cout << "No habits to show.\n";
            return;
        }
        for (int i = 0; i < habitCount; ++i) {
            cout << "- " << habits[i].name
                 << " | Streak: " << habits[i].streak
                 << "\n";
        }
    }
};

class Handler {
    static User   users[MAX_USERS];
    static int    userCount;
    static User*  currentUser;

public:
    static void load_users();
    static void save_users();

    static int  print_login_menu();
    static int  print_and_get_choices();

    static void register_user();
    static bool login_user();
    static void logout();

    static void add_habit();
    static void edit_habit();
    static void delete_habit();
    static void check_in();
    static void view_progress();
};

User  Handler::users[MAX_USERS];
int   Handler::userCount    = 0;
User* Handler::currentUser  = nullptr;

void Handler::load_users() {
    ifstream in("users.txt");
    if (!in.is_open()) return;

    in >> userCount;
    for (int i = 0; i < userCount; ++i) {
        int hcount;
        in >> users[i].username
           >> users[i].password
           >> hcount;
        users[i].habitCount = hcount;

        for (int j = 0; j < hcount; ++j) {
            in >> users[i].habits[j].name
               >> users[i].habits[j].category
               >> users[i].habits[j].streak
               >> users[i].habits[j].lastCheckIn;
        }
    }
}

void Handler::save_users() {
    ofstream out("users.txt");
    out << userCount << "\n";
    for (int i = 0; i < userCount; ++i) {
        out << users[i].username << " "
            << users[i].password << " "
            << users[i].habitCount << "\n";
        for (int j = 0; j < users[i].habitCount; ++j) {
            auto& h = users[i].habits[j];
            out << h.name << " "
                << h.category << " "
                << h.streak << " "
                << h.lastCheckIn << "\n";
        }
    }
}

int Handler::print_login_menu() {
    int choice;
    cout << "Please choose:\n"
         << "(1) Register\n"
         << "(2) Login\n"
         << "(3) Quit\n"
         << "============================================\n"
         << "Your choice: ";
    cin  >> choice;
    return choice;
}

int Handler::print_and_get_choices() {
    int choice;
    cout << "Please choose:\n"
         << "(1) Add Habit\n"
         << "(2) Edit Habit\n"
         << "(3) Delete Habit\n"
         << "(4) Daily Check‑In\n"
         << "(5) View Progress\n"
         << "(6) Logout\n"
         << "============================================\n"
         << "Your choice: ";
    cin  >> choice;
    return choice;
}

void Handler::register_user() {
    if (userCount >= MAX_USERS) {
        cout << "User limit reached.\n";
        return;
    }
    string u,p;
    cout << "New username: "; 
    cin  >> u;
    for (int i = 0; i < userCount; ++i)
        if (users[i].username == u) {
            cout << "That name’s taken.\n";
            return;
        }
    cout << "New password: ";
    cin  >> p;

    users[userCount] = User(u,p);
    currentUser     = &users[userCount++];
    cout << "Registered AND logged in as “" << u << "”\n";
    save_users();
}

bool Handler::login_user() {
    string u,p;
    cout << "Username: "; 
    cin  >> u;
    for (int i = 0; i < userCount; ++i) {
        if (users[i].username == u) {
            cout << "Password: ";
            cin  >> p;
            if (users[i].password == p) {
                currentUser = &users[i];
                cout << "Welcome back, " << u << "!\n";
                return true;
            }
            cout << "Wrong password.\n";
            return false;
        }
    }
    cout << "No such user.\n";
    return false;
}

void Handler::logout() {
    currentUser = nullptr;
    cout << "Logged out.\n";
}

void Handler::add_habit() {
    if (!currentUser) return;
    static const string cats[5] = {
        "Health/Fitness","Social","Wellness","Study/Work","Chores"
    };
    string name;
    int    c;
    cout << "Habit name: "; 
    cin  >> name;
    cout << "Category:\n";
    for (int i = 0; i < 5; ++i)
        cout << "(" << i+1 << ") " << cats[i] << "\n";
    cout << "> "; 
    cin  >> c;
    if (c<1||c>5) c = 1;
    currentUser->addHabit(name, cats[c-1]);
}

void Handler::edit_habit() {
    if (!currentUser || currentUser->habitCount == 0) {
        cout << "No habits.\n"; 
        return;
    }
    cout << "Your habits:\n";
    for (int i = 0; i < currentUser->habitCount; ++i)
        cout << "(" << i+1 << ") "
             << currentUser->habits[i].name
             << " [" << currentUser->habits[i].category
             << "]\n";

    int idx; 
    cout << "Which to edit? "; 
    cin  >> idx;
    if (idx<1||idx>currentUser->habitCount) {
        cout << "Invalid.\n"; 
        return;
    }

    static const string cats[5] = {
        "Health/Fitness","Social","Wellness","Study/Work","Chores"
    };
    string newName;
    int    newCat;
    cout << "New name: "; 
    cin  >> newName;
    cout << "New category:\n";
    for (int i = 0; i < 5; ++i)
        cout << "(" << i+1 << ") " << cats[i] << "\n";
    cout << "> "; 
    cin  >> newCat;
    if (newCat<1||newCat>5) newCat = 1;

    currentUser->editHabit(idx-1, newName, cats[newCat-1]);
}

void Handler::delete_habit() {
    if (!currentUser || currentUser->habitCount == 0) {
        cout << "No habits.\n"; 
        return;
    }
    cout << "Your habits:\n";
    for (int i = 0; i < currentUser->habitCount; ++i)
        cout << "(" << i+1 << ") "
             << currentUser->habits[i].name << "\n";

    int idx;
    cout << "Which to delete? "; 
    cin  >> idx;
    currentUser->deleteHabit(idx-1);
}

void Handler::check_in() {
    if (!currentUser || currentUser->habitCount == 0) {
        cout << "No habits.\n"; 
        return;
    }
    cout << "Your habits:\n";
    for (int i = 0; i < currentUser->habitCount; ++i)
        cout << "(" << i+1 << ") "
             << currentUser->habits[i].name << "\n";

    int idx;
    cout << "Which to check‑in? "; 
    cin  >> idx;
    currentUser->checkIn(idx-1);
}

void Handler::view_progress() {
    if (!currentUser) return;
    currentUser->showProgress();
}

#endif 
