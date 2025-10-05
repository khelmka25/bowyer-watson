#include "src/Application.h"

#include <iostream>
#include <string>

using namespace std::literals::string_literals;

int main()
{
    try {
        std::srand((unsigned int)time(0));
        Application app("Bowyer Watson Algorithm"s, 500, 250);
        do {
            app.run();
        } while (app.active());
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
