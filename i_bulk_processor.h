#pragma once

#include <vector>
#include <string>

class IBulkProcessor {
public:
    virtual ~IBulkProcessor() = default;
    virtual void process(const std::vector<std::string>& commands) = 0;
};
