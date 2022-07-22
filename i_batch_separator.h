#pragma once

#include <string>

class IBatchSeparator {
public:
    virtual ~IBatchSeparator() = default;
    virtual void pushCommand(const std::string &command) = 0;
    virtual void pushOpenBrace() = 0;
    virtual void pushCloseBrace() = 0;
    virtual void end() = 0;
};
