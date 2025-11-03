#include <iostream>
#include <string>

#include "Application.h"

using namespace std::literals::string_literals;

int main() {
    try {
        std::srand((unsigned int)time(0));
        Application app("Bowyer Watson Algorithm"s, 500, 250);
        while (app.active()) {
            app.run();
        }
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
