#pragma once

#include "i_bulk_processor.h"

#include <functional>

using BulkProcessorFunc = std::function<void(const std::vector<std::string>&)>;

class FuncBulkProcessor : public IBulkProcessor {
public:
    explicit FuncBulkProcessor(const BulkProcessorFunc &func)
        : func(func) {}

    void process(const std::vector<std::string> & commands) override {
        func(commands);
    }
private:
    const BulkProcessorFunc func;
};
