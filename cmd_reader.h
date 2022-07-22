#pragma once

#include <iostream>
#include <string>
#include "bulk_processor.h"

class CommandReader {
public:
    explicit CommandReader(std::istream &stream, BatchSeparator &separator)
        : stream(stream), separator(separator) {}

    void readTillEnd() {
        std::string cmd;
        while (std::getline(stream, cmd)) {
            if (cmd == "{") {
                separator.pushOpenBrace();
            } else if (cmd == "}") {
                separator.pushCloseBrace();
            } else {
                separator.pushCommand(cmd);
            }
        }
        if (stream.eof()) {
            separator.end();
        }
    }
private:
    std::istream &stream;
    BatchSeparator &separator;
};
