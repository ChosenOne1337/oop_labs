#include <iostream>
#include <libgen.h>
#include "calc_modes.h"

namespace Argv {

const int PROG_NAME = 0;
const int IN_FILENAME = 1;
const int OUT_FILENAME = 2;
const int INTERACTIVE_MODE_ARGC = 1;
const int FILE_MODE_ARGC = 3;

} // namespace Argv

int main(int argc, char *argv[]) {
    if (argc == Argv::INTERACTIVE_MODE_ARGC) {
        // use standard streams
        return Calc::interactive_mode();
    }
    if (argc == Argv::FILE_MODE_ARGC) {
        // use file streams
        return Calc::file_mode(argv[Argv::IN_FILENAME], argv[Argv::OUT_FILENAME]);
    }
    Calc::print_usage(basename(argv[Argv::PROG_NAME]));
    return EXIT_FAILURE;
}
