#include <catch.hpp>
#include "printer/console_colour/ConsoleColour.h"

#include <iostream>

using namespace tkom;

TEST_CASE("Check available colors in Colour", "[Colour]") {
    if (false) {
        std::cout << Colour(Colour::None) << "None" << Colour(Colour::None) << "\n";
        std::cout << Colour(Colour::White) << "White" << Colour(Colour::None) << "\n";
        std::cout << Colour(Colour::Red) << "Red" << Colour(Colour::None) << "\n";
        std::cout << Colour(Colour::Green) << "Green" << Colour(Colour::None) << "\n";
        std::cout << Colour(Colour::Blue) << "Blue" << Colour(Colour::None) << "\n";
        std::cout << Colour(Colour::Cyan) << "Cyan" << Colour(Colour::None) << "\n";
        std::cout << Colour(Colour::Yellow) << "Yellow" << Colour(Colour::None) << "\n";
        std::cout << Colour(Colour::Grey) << "Grey" << Colour(Colour::None) << "\n";

        std::cout << Colour(Colour::BrightRed) << "BrightRed" << Colour(Colour::None) << "\n";
        std::cout << Colour(Colour::BrightGreen) << "BrightGreen" << Colour(Colour::None) << "\n";
        std::cout << Colour(Colour::LightGrey) << "LightGrey" << Colour(Colour::None) << "\n";
        std::cout << Colour(Colour::BrightWhite) << "BrightWhite" << Colour(Colour::None) << "\n";
        std::cout << Colour(Colour::BrightYellow) << "BrightYellow" << Colour(Colour::None) << "\n";
    }
}