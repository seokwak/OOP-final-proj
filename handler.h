#ifndef HANDLER_H
#define HANDLER_H

#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <limits>
using namespace std;

const int MAX_USERS = 20;
const int MAX_HABITS = 20;

struct Habit {
    string name;
    string category;
    int streak;
    string frequency;
    time_t lastCheckIn;
    bool reminderSet;

    Habit()
      : name(""), category(""), frequency("daily"),
        streak(0), lastCheckIn(0), reminderSet(false)
    {}

    Habit(const string& n, const string& c, const string& f)
      : name(n), category(c), frequency(f),
        streak(0), lastCheckIn(0), reminderSet(false)
    {}

    void markComplete() {
        time_t now = time(nullptr);
        double days = difftime(now, lastCheckIn) / 86400.0;
        if (lastCheckIn == 0
         || (frequency == "daily"   && days >= 1)
         || (frequency == "weekly"  && days >= 7)
         || (frequency == "monthly" && days >= 30))
        {
            streak++;
            lastCheckIn = now;
            cout << "Habit checked in! Streak: " << streak << endl;
        }
        else {
            cout << "Too early to check in again for this frequency." << endl;
        }
    }

    void toggleReminder() {
        reminderSet = !reminderSet;
        cout << "Reminder "
             << (reminderSet ? "ON" : "OFF")
             << " for " << name << "." << endl;
    }
};

class User {
public:
    string username;
    string password;
    Habit habits[MAX_HABITS];
    int habitCount;

    User() : username(""), password(""), habitCount(0) {}
    User(const string& u, const string& p)
      : username(u), password(p), habitCount(0)
    {}

    void addHabit(const string& n, const string& c, const string& f) {
        if (habitCount < MAX_HABITS) {
            habits[habitCount++] = Habit(n, c, f);
            cout << "Added \"" << n << "\" in [" << c << "]\n"
                 << "Frequency: " << f << endl;
        }
        else {
            cout << "Max habits reached." << endl;
        }
    }

    void editHabit(int idx,
                   const string& n,
                   const string& c,
                   const string& f)
    {
        if (idx >= 0 && idx < habitCount) {
            habits[idx].name      = n;
            habits[idx].category  = c;
            habits[idx].frequency = f;
            cout << "Habit updated." << endl;
        }
        else {
            cout << "Invalid habit number." << endl;
        }
    }

    void deleteHabit(int idx) {
        if (idx >= 0 && idx < habitCount) {
            for (int j = idx; j + 1 < habitCount; ++j)
                habits[j] = habits[j+1];
            habitCount--;
            cout << "Habit deleted." << endl;
        }
        else {
            cout << "Invalid habit number." << endl;
        }
    }

    void checkIn(int idx) {
        if (idx >= 0 && idx < habitCount)
            habits[idx].markComplete();
        else
            cout << "Invalid habit number." << endl;
    }

    void viewProgress() const {
        if (habitCount == 0) {
            cout << "No habits to show." << endl;
            return;
        }
        for (int i = 0; i < habitCount; ++i) {
            cout << "- " << habits[i].name
                 << " | Frequency: " << habits[i].frequency
                 << " | Streak: "     << habits[i].streak
                 << endl;
        }
    }

    void setReminder(int idx) {
        if (idx >= 0 && idx < habitCount)
            habits[idx].toggleReminder();
        else
            cout << "Invalid habit number." << endl;
    }
};

class Handler {
    User*   currentUser;
    User    users[MAX_USERS];
    int     userCount;

public:
    Handler() : currentUser(nullptr), userCount(0) {}

    void loadUsers() {
        ifstream in("users.txt");
        if (!in.is_open()) return;
        in >> userCount;
        for (int i = 0; i < userCount; ++i) {
            int h;
            in >> users[i].username
               >> users[i].password
               >> h;
            users[i].habitCount = h;
            for (int j = 0; j < h; ++j) {
                in >> users[i].habits[j].name
                   >> users[i].habits[j].category
                   >> users[i].habits[j].frequency
                   >> users[i].habits[j].streak
                   >> users[i].habits[j].lastCheckIn
                   >> users[i].habits[j].reminderSet;
            }
        }
    }

    void saveUsers() {
        ofstream out("users.txt");
        out << userCount << endl;
        for (int i = 0; i < userCount; ++i) {
            out << users[i].username << " "
                << users[i].password << " "
                << users[i].habitCount << endl;
            for (int j = 0; j < users[i].habitCount; ++j) {
                auto& h = users[i].habits[j];
                out << h.name << " "
                    << h.category << " "
                    << h.frequency << " "
                    << h.streak << " "
                    << h.lastCheckIn << " "
                    << h.reminderSet << endl;
            }
        }
    }

    int printLoginMenu() {
        int choice;
        while (true) {
            cout << "Please choose:\n"
                 << "(1) Register\n"
                 << "(2) Login\n"
                 << "(3) Quit\n"
                 << "============================================\n"
                 << "Your choice: ";
            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number.\n\n";
                continue;
            }
            if (choice >= 1 && choice <= 3) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter 1, 2, or 3.\n\n";
        }
        return choice;
    }

    int printAndGetChoices() {
        int choice;
        while (true) {
            cout << "Please choose:\n"
                 << "(1) Add Habit\n"
                 << "(2) Edit Habit\n"
                 << "(3) Delete Habit\n"
                 << "(4) Daily Check‑In\n"
                 << "(5) View Progress\n"
                 << "(6) Set Reminders\n"
                 << "(7) Logout\n"
                 << "============================================\n"
                 << "Your choice: ";
            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number.\n\n";
                continue;
            }
            if (choice >= 1 && choice <= 7) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Enter 1–7.\n\n";
        }
        return choice;
    }

    void registerUser() {
        if (userCount >= MAX_USERS) {
            cout << "User limit reached.\n";
            return;
        }
        string u, p;
        cout << "New username: ";
        cin  >> u;
        for (int i = 0; i < userCount; ++i)
            if (users[i].username == u) {
                cout << "That name’s taken.\n";
                return;
            }
        cout << "New password: ";
        cin  >> p;

        users[userCount] = User(u, p);
        currentUser     = &users[userCount++];
        cout << "Registered—ready to login!\n";
        saveUsers();
    }

    bool loginUser() {
        string u, p;
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

    void logout() {
        currentUser = nullptr;
        cout << "Logged out.\n";
    }

    void addHabit() {
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
        if (c < 1 || c > 5) c = 1;

        int freq;
        static const string freqs[3] = { "daily","weekly","monthly" };
        cout << "Frequency:\n(1) Daily\n(2) Weekly\n(3) Monthly\n> ";
        cin >> freq;
        if (freq < 1 || freq > 3) freq = 1;

        currentUser->addHabit(
          name,
          cats[c-1],
          freqs[freq-1]
        );
    }

    void editHabit() {
        if (!currentUser || currentUser->habitCount == 0) {
            cout << "No habits.\n";
            return;
        }
        cout << "Your habits:\n";
        for (int i = 0; i < currentUser->habitCount; ++i)
            cout << "(" << i+1 << ") "
                 << currentUser->habits[i].name
                 << " [" << currentUser->habits[i].category << "]\n";

        int idx;
        cout << "Which to edit? ";
        cin  >> idx;
        if (idx < 1 || idx > currentUser->habitCount) {
            cout << "Invalid.\n";
            return;
        }

        static const string cats[5] = {
            "Health/Fitness","Social","Wellness","Study/Work","Chores"
        };
        string newName;
        int    newCat, newFreq;

        cout << "New name: ";
        cin  >> newName;

        cout << "New category:\n";
        for (int i = 0; i < 5; ++i)
            cout << "(" << i+1 << ") " << cats[i] << "\n";
        cout << "> ";
        cin  >> newCat;
        if (newCat < 1 || newCat > 5) newCat = 1;

        cout << "New frequency:\n(1) Daily\n(2) Weekly\n(3) Monthly\n> ";
        cin >> newFreq;
        if (newFreq < 1 || newFreq > 3) newFreq = 1;

        currentUser->editHabit(
            idx-1,
            newName,
            cats[newCat-1],
            (newFreq==1 ? "daily"
             : newFreq==2 ? "weekly"
                          : "monthly")
        );
    }

    void deleteHabit() {
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

    void checkIn() {
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

    void viewProgress() {
        if (currentUser) currentUser->viewProgress();
    }

    void setReminder() {
        if (!currentUser|| currentUser->habitCount == 0) {
            cout << "No habits available.\n";
            return;
        }
        cout << "Select a habit to set reminder:\n";
        for (int i = 0;i <currentUser->habitCount; ++i){
            cout << "(" << i + 1 << ") "
                 << currentUser->habits[i].name
                 << " [" << (currentUser->habits[i].reminderSet ? "ON" : "OFF") << "]\n";
        }
        int idx;
        cout << "Enter habit number: ";
        cin >> idx;
        if (idx < 1|| idx >currentUser->habitCount) {
            cout << "Invalid.\n";
            return;
        }
        currentUser->habits[idx - 1].reminderSet=!currentUser->habits[idx - 1].reminderSet;
        cout << "Reminder set for "<< currentUser->habits[idx - 1].name << ".\n"; 
    }
    void show_reminders() {
        if (!currentUser||currentUser->habitCount== 0) return;
        cout << "\nHabit Reminders:\n";
        time_t now= time(0);
        for (int i=0;i<currentUser->habitCount; ++i) {
            Habit& h = currentUser->habits[i];
            if (!h.reminderSet) continue;
            double daysPassed = difftime(now, h.lastCheckIn)/86400.0; 
            if (h.lastCheckIn==0|| (h.frequency =="daily"&& daysPassed >=1) ||
                (h.frequency =="weekly"&& daysPassed >=7)||
                (h.frequency =="monthly"&& daysPassed >=30)) {
                    cout << h.name << " (" << h.frequency << ") is due for check-in!\n";
            }
        }
    
        cout << "============================================\n";
    }
};

#endif 
