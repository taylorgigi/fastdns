//
// Created by taylor on 2020/9/10.
//

#include "../config_parse.h"
#include <cstdlib>
#include <libgen.h>
#include "../logger.h"
#include <iostream>

int main(int argc, char *argv[])
{
    if(argc < 2) {
        std::cout << "Usage " << basename(argv[0]) << "<config file path" << std::endl;
        exit(-1);
    }
    if(!logger_init("config-pars-test-logger", "log", "config-parse-test")) {
        std::cout << "Could not initialize logger" << std::endl;
        exit(-1);
    }
    fastdns::parse_config_file(argv[1]);

    return 0;
}
