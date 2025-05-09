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
    Handler::load_users();

    bool running = true;
    while (running) {
        // clear before showing login menu
        system("clear");

        int choice = Handler::print_login_menu();

        switch (choice) {
            case 1:
                Handler::register_user();
                pause();
                break;

            case 2:
                if (Handler::login_user()) {
                    bool inSession = true;
                    while (inSession) {
                        system("clear");

                        int cmd = Handler::print_and_get_choices();

                        switch (cmd) {
                            case 1:
                                Handler::add_habit();
                                Handler::save_users();
                                break;
                            case 2:
                                Handler::edit_habit();
                                Handler::save_users();
                                break;
                            case 3:
                                Handler::delete_habit();
                                Handler::save_users();
                                break;
                            case 4:
                                Handler::check_in();
                                Handler::save_users();
                                break;
                            case 5:
                                Handler::view_progress();
                                break;
                            case 6:
                                Handler::set_reminder();
                                Handler::save_users();
                                break;
                            case 7:
                                Handler::logout();
                                inSession = false;
                                break;
                            default:
                                cout << "Invalid choice." << endl;
                        }
                        pause();
                    }
                }
                break;

            case 3:
                Handler::save_users();
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