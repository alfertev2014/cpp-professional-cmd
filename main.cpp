
#include <iostream>
#include <string>

#include "cmd_reader.h"
#include "bulk_processor.h"
#include "batch_separator.h"

int main(int argc, char * argv[]) {

    if (argc < 2) {
        std::cerr << "ERROR: First argument required." << std::endl;
        std::cerr << "Please specify default batch size." << std::endl;
        return -1;
    }

    const std::uint32_t N = static_cast<std::uint32_t>(std::stoul(argv[1]));

    if (N == 0) {
        std::cerr << "ERROR: Batch size cannot be 0." << std::endl;
        return -2;
    }


    // Handmade dependency injection

    FuncBulkProcessor processor {[](const std::vector<std::string>&commands) {
        std::cout << "bulk: ";
        bool comma = false;
        for (const auto &command : commands) {
            if (comma) {
                std::cout << ", ";
            }
            comma = true;
            std::cout << command;
        }
        std::cout << std::endl;
    }};

    BatchSeparator separator {N, processor};

    CommandReader reader {std::cin, separator};


    // ... and start!

    reader.readTillEnd();

    return 0;
}
