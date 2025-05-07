#include <iostream>
#include "handler.h"
using namespace std;

int main() {
    int user_choice = 0;
    while (user_choice != 7) {
        user_choice = Handler::print_and_get_choices();
        switch (user_choice) {
            case 1:
                system("clear");
                Handler::register_user();
                break;
            case 2:
                system("clear");
                Handler::add_habit();
                break;
            case 3 :
                system("clear");
                Handler::edit_habit();
                break;
            case 4 :
                system("clear");
                Handler::delete_habit();
                break;
            case 5:
                system("clear");
                Handler::check_in();
                break;
            case 6:
                system("clear");
                Handler::view_progress();
                break;
        }
        cout<< "============================================" << endl;
        cout << "press enter key to continue.." << endl;
        getchar(); getchar();
        system("clear");
    }
    return 0;
}