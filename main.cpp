#include <iostream>
#include "handler.h"
using namespace std;

int main() {
    Handler::load_users();

    bool running = true;
    while (running) {
        int choice = Handler::print_login_menu();
        system("clear");

        switch (choice) {
            case 1:
                Handler::register_user();
                break;

            case 2:
                if (Handler::login_user()) {
                    bool inSession = true;
                    while (inSession) {
                        int cmd = Handler::print_and_get_choices();
                        system("clear");

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
                                Handler::logout();
                                inSession = false;
                                break;

                            default:
                                cout << "Invalid choice.\n";
                        }

                        cout<< "============================================" << endl;
                        cout << "press enter key to continue.." << endl;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cin.get();
                        system("clear");
                    }
                }
                break;

            case 3:
                Handler::save_users();
                cout << "Goodbye!\n";
                running = false;
                break;

            default:
                cout << "Invalid choice.\n";
                break;
        }
    }

    return 0;
}
