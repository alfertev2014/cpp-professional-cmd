#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include <functional>

using BulkProcessor = std::function<void(const std::vector<std::string>&)>;

class BatchSeparator {
public:
    BatchSeparator(std::uint32_t batchSize, const BulkProcessor &processor)
        : batchSize(batchSize), processor(processor) {
        commands.reserve(batchSize);
        reset();
    }

    void pushCommand(const std::string &command) {
        commands.push_back(command);
        if (braceCounter == 0 && commands.size() == batchSize) {
            process();
        }
    }

    void pushOpenBrace() {
        if (braceCounter == 0 && commands.size() > 0) {
            process();
        }
        ++braceCounter;
    }

    void pushCloseBrace() {
        if (braceCounter == 0) {
            // ignore
            return;
        }
        --braceCounter;
        if (braceCounter == 0) {
            process();
        }
    }

    void end() {
        process();
    }

    void reset() {
        braceCounter = 0;
        commands.clear();
    }

private:
    const std::uint32_t batchSize;
    const BulkProcessor processor;

    std::vector<std::string> commands;
    std::uint32_t braceCounter {};

    void process() {
        if (commands.size() != 0) {
            processor(commands);
        }
        commands.clear();
    }
};
