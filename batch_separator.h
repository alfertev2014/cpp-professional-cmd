#pragma once

#include <vector>
#include <string>
#include <cstdint>

#include "i_batch_separator.h"
#include "i_bulk_processor.h"

class BatchSeparator : public IBatchSeparator {
public:
    BatchSeparator(std::uint32_t batchSize, IBulkProcessor &processor)
        : batchSize(batchSize), processor(processor) {
        commands.reserve(batchSize);
        reset();
    }

    void pushCommand(const std::string &command) override {
        commands.push_back(command);
        if (braceCounter == 0 && commands.size() == batchSize) {
            process();
        }
    }

    void pushOpenBrace() override {
        if (braceCounter == 0 && commands.size() > 0) {
            process();
        }
        ++braceCounter;
    }

    void pushCloseBrace() override {
        if (braceCounter == 0) {
            // ignore
            return;
        }
        --braceCounter;
        if (braceCounter == 0) {
            process();
        }
    }

    void end() override {
        process();
    }

    void reset() {
        braceCounter = 0;
        commands.clear();
    }

private:
    const std::uint32_t batchSize;
    IBulkProcessor &processor;

    std::vector<std::string> commands;
    std::uint32_t braceCounter {};

    void process() {
        if (commands.size() != 0) {
            processor.process(commands);
        }
        commands.clear();
    }
};

