#include <iostream>
#include <string>

#include "Application.h"


int main() {
    try {
        std::srand((unsigned int)time(0));
        using namespace std::literals::string_view_literals;
        Application app("Bowyer Watson Algorithm"sv, 500, 250);
        while (app.active()) {
            app.run();
        }
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
