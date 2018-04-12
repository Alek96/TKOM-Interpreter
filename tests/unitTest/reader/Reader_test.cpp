#include <catch.hpp>
#include <string>
#include <sstream>
#include <cctype>
#include <memory>
#include <iostream>

#include "reader/Reader.hpp"
#include "exception/Exception.hpp"

using namespace tkom;

SCENARIO("Test for Reader", "[Reader]") {

    GIVEN("Stream with some characters") {

        std::string streamValue = "12345\n"
                                  "12345\n"
                                  "1234\n\r"
                                  "1234\n\r"
                                  "1234\r\n"
                                  "1234\r\n";
        std::istringstream istream(streamValue);

        Reader reader(istream);
        WHEN("Read the stream") {
            THEN("All characters are read by get") {
                for (auto &&value : streamValue) {
                    REQUIRE(reader.get() == value);
                }
            }
            THEN("All characters are read by peek") {
                for (auto &&value : streamValue) {
                    REQUIRE(reader.peek() == value);
                    reader.get();
                }
            }
            THEN("All lines number are read") {
                for (unsigned int i = 0; i < streamValue.size(); ++i) {
                    reader.get();
                    if (!std::isspace(streamValue[i]))
                        REQUIRE(reader.getPosition().lineNumber == i / 6 + 1);
                }
            }
            THEN("All signs number are read") {
                for (auto &&value : streamValue) {
                    reader.get();
                    if (!std::isspace(value))
                        REQUIRE(reader.getPosition().signNumber == static_cast<int>(value) - static_cast<int>('0'));
                }
            }
        }
    }
}
