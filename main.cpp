#include <iostream>
#include <limits>
#include "handler.h"
using namespace std;

static void pause() {
    cout << "============================================\n"
         << "Press ENTER to continue…";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

int main() {
    Handler handler;
    handler.loadUsers();

    bool running = true;
    while (running) {
        system("clear");
        int choice = handler.printLoginMenu();
        switch (choice) {
            case 1:
                handler.registerUser();
                pause();
                break;
            case 2:
                if (handler.loginUser()) {
                    bool inSession = true;
                    while (inSession) {
                        system("clear");
                        handler.show_reminders();
                        int cmd = handler.printAndGetChoices();
                        switch (cmd) {
                            case 1:
                                handler.addHabit();
                                handler.saveUsers();
                                break;
                            case 2:
                                handler.editHabit();
                                handler.saveUsers();
                                break;
                            case 3:
                                handler.deleteHabit();
                                handler.saveUsers();
                                break;
                            case 4:
                                handler.checkIn();
                                handler.saveUsers();
                                break;
                            case 5:
                                handler.viewProgress();
                                break;
                            case 6:
                                handler.setReminder();
                                handler.saveUsers();
                                break;
                            case 7:
                                handler.logout();
                                inSession = false;
                                break;
                            default:
                                cout << "Invalid choice." << endl;
                                break;
                        }
                        pause();
                    }
                }
                break;
            case 3:
                handler.saveUsers();
                cout << "Goodbye!\n";
                running = false;
                break;
            default:
                cout << "Invalid choice." << endl;
                pause();
                break;
        }
    }

    return 0;
}
