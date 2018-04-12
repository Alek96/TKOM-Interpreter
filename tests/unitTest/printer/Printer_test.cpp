#include <catch.hpp>
#include "printer/Printer.hpp"
#include <sstream>

using namespace tkom;

TEST_CASE("test for Printer", "[Printer]") {

    GIVEN("Output stream for Printer") {
        std::ostringstream oss;
        Printer::instance().setOutputStream(&oss);
        WHEN("Print message is sent") {
            std::string message = "Normal text";
            Printer::instance().print(message);
            THEN("Print message comes") {
                REQUIRE(oss.str().find(message) != std::string::npos);
            }
        }
        WHEN("Notice message is sent") {
            std::string message = "Notice text";
            Printer::instance().notice(message);
            THEN("Print message comes") {
                REQUIRE(oss.str().find(message) != std::string::npos);
            }
        }
        WHEN("Warning message is sent") {
            std::string message = "Warning text";
            Printer::instance().warning(message);
            THEN("Print message comes") {
                REQUIRE(oss.str().find(message) != std::string::npos);
            }
        }
        WHEN("Error message is sent") {
            std::string message = "Error text";
            Printer::instance().error(message);
            THEN("Print message comes") {
                REQUIRE(oss.str().find(message) != std::string::npos);
            }
        }
    }
}
