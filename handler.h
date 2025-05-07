#include <iostream>
#include <string>
#include <ctime>
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
        time_t now = time(0);
        if (difftime(now, lastCheckIn) >= 86400) {
            streak++;
            lastCheckIn = now;
            cout << "Habit checked in! Streak: " << streak << endl;
        }
        else{
            cout << "Already checked in today." << endl;
        }
    }
};

class User {
    public:
        string username;
        string password;
        Habit habits[MAX_HABITS];
        int habitCount;
        User(): username(""), password(""), habitCount(0) {}
        User(string u, string p) : username(u), password(p), habitCount(0) {}

        void addHabit(string name, string category) {
            if(habitCount< MAX_HABITS){
                habits[habitCount++]= Habit(name,category);
            }
            else{
                cout<<"Maximum number of habits reached.\n";
            }
        }

        void editHabit(string oldName) {
            for (int i = 0;i< habitCount; ++i) {
                if (habits[i].name== oldName) {
                    cout << "New name: "; 
                    cin >> habits[i].name;
                    cout << "New category: "; 
                    cin >> habits[i].category;
                    cout << "Habit updated.\n";
                    return;
                }
            }
            cout << "Habit not found.\n";
        }
        
        void deleteHabit(string name) {
            for (int i=0; i< habitCount; ++i) {
                if (habits[i].name ==name) {
                    for (int j =i;j <habitCount-1; ++j) {
                        habits[j] = habits[j+1];
                    }
                    habitCount--;
                    cout << "Habit deleted.\n";
                    return;
                }
            }
            cout << "Habit not found.\n";
        }
        void checkIn(string name) {
            for (int i=0;i< habitCount; ++i) {
                if(habits[i].name ==name){
                    habits[i].markComplete();
                    return;
                }
            }
            cout << "Habit not found.\n";
        }

        void showProgress() {
            for (int i =0; i< habitCount;++i) {
                cout << habits[i].name << " | Streak: " << habits[i].streak << endl;
            }
        }
};

class Handler {
    static User users[MAX_USERS];
    static int userCount;
    static User* currentUser;
public:
    static int print_and_get_choices() {
        int choice;
        cout << "Please choose one of the following options:\n";
        cout << "(1) Register & Login\n";
        cout << "(2) Add Habit\n";
        cout << "(3) Edit Habit\n";
        cout << "(4) Delete Habit\n";
        cout << "(5) Daily Check-In\n";
        cout << "(6) View Progress\n";
        cout << "(7) Quit\n";
        cout << "============================================\n";
        cout << "Your choice: ";
        cin >> choice;
        return choice;
    }

    static void register_user() {
        if (userCount >= MAX_USERS) {
            cout << "User limit reached.\n";
            return;
        }
        int choice;
        cout << "Choose an option:\n (1) Register\n(2) Login\nYour choice: ";
        cin >> choice;
        string uname, pass;
        cout << "Enter username: "; cin >> uname;
        
        if (choice==1) {
            for (int i=0; i< userCount; ++i) {
                if (users[i].username == uname) {
                    cout << "Username already taken.";
                    return;
                }
            }
            cout << "Enter password: ";
            cin >> pass;
            users[userCount] =User(uname, pass);
            currentUser=&users[userCount];
            userCount++;
            cout << "Registration complete.\n";
        }
        else if (choice==2){
            for (int i= 0; i< userCount;++i) {
                cout << "Enter password: "; 
                cin >> pass;
                if (users[i].username ==uname&& users[i].password== pass) {
                currentUser= &users[i];
                cout << "Login successful.";
                return;
                }
            } 
            cout << "Invalid credentials";
        }
        else{
            cout << "Invalid option.";
        } 
    }

    static void add_habit() {
        if (!currentUser) return;
        string name, cat;
        int choice;
        string categories[5]={"Health/Fitness","Social","Wellness","Study/Work","Chores"};
        cout << "Habit name: ";
        cin >> name;
        cout << "Choose Category:\n(1) Health/Fitness\n(2) Social\n(3) Wellness\n(4) Study/Work\n(5) Chores\n";
        cin >> choice;
        cout << "Category: " <<categories[choice-1]<<endl;
        currentUser->addHabit(name, categories[choice-1]);
    }

    static void edit_habit() {
        if (!currentUser||currentUser->habitCount== 0) {
            cout << "No habits to edit.\n";
            return;
        }
        cout << "Your Habits:\n";
        for (int i= 0; i< currentUser->habitCount; ++i) {
            cout << "(" << (i + 1) << ") " << currentUser->habits[i].name << " - " << currentUser->habits[i].category << endl;
        }
        int index;
        cout << "Enter habit number to edit: ";
        cin >> index;
        if (index < 1 || index > currentUser->habitCount) {
            cout << "Invalid choice.\n";
            return;
        }
        cout << "New name: "; cin >> currentUser->habits[index - 1].name;
        int newCat;
        string categories[5]={"Health/Fitness","Social","Wellness","Study/Work","Chores"};
        cout << "Choose New Category:\n(1) Health/Fitness\n(2) Social\n(3) Wellness\n(4) Study/Work\n(5) Chores\n";
        cin >> newCat;
        cout << "New Category: " <<categories[newCat-1]<<endl;
        categories[newCat-1]=currentUser->habits[index - 1].category;
        cout << "Habit updated.\n";
    }
    
    static void delete_habit() {
        if (!currentUser||currentUser->habitCount== 0) {
            cout << "No habits to delete.\n";
            return;
        }
        cout << "Your Habits:\n";
        for (int i= 0; i< currentUser->habitCount; ++i) {
            cout << "(" << (i + 1) << ") " << currentUser->habits[i].name << " - " << currentUser->habits[i].category << endl;
        }
        int index;
        cout << "Enter habit number to delete: ";
        cin >> index;
        if (index < 1 || index > currentUser->habitCount) {
            cout << "Invalid choice.\n";
            return;
        }
        for (int j = index - 1; j < currentUser->habitCount - 1; ++j) {
            currentUser->habits[j] = currentUser->habits[j + 1];
        }
        currentUser->habitCount--;
        cout << "Habit deleted.\n";
    }

    static void check_in() {
        if (!currentUser || currentUser->habitCount == 0) {
            cout << "No habits to check in.\n";
            return;
        }
        cout << "Your Habits:\n";
        for (int i = 0; i < currentUser->habitCount; ++i) {
            cout << "(" << (i + 1) << ") " << currentUser->habits[i].name << endl;
        }
        int index;
        cout << "Enter habit number to check in: "; cin >> index;
        if (index < 1 || index > currentUser->habitCount) {
            cout << "Invalid choice.\n";
            return;
        }
        currentUser->habits[index - 1].markComplete();
    }

    static void view_progress() {
        if (!currentUser) return;
        currentUser->showProgress();
    }
};

User Handler::users[MAX_USERS];
int Handler::userCount = 0;
User* Handler::currentUser = nullptr;

