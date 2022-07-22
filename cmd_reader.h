#pragma once

#include <iostream>
#include <string>
#include "i_batch_separator.h"

class CommandReader {
public:
    explicit CommandReader(std::istream &stream, IBatchSeparator &separator)
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
    IBatchSeparator &separator;
};
