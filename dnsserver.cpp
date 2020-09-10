//
// Created by taylor on 2020/9/8.
//

#include <cstdlib>
#include "ConfigParse.h"
#include <getopt.h>
#include "logger.h"
#include <rte_eal.h>

bool ParseArgs(int argc, char *argv[])
{
    int ret = 0;
    static struct option longopts[] = {
            {"config", required_argument, NULL, 0 },
            {0, 0, 0, 0 }
    };
    int longindex = 0;
    std::string cfg_file;
    while((ret = getopt_long(argc, argv, "", longopts, &longindex)) != -1) {
        switch(ret) {
            case 0:
                if(strcmp(longopts[longindex].name, "config") == 0)
                    cfg_file = optarg;
                break;
        }
    }
    if(cfg_file.empty())
        return false;
    return fastdns::ParseConfigFile(cfg_file.c_str());
}

int main(int argc, char *argv[])
{
    if(!logger_init("fastdns-logger",  "log", "fastdns-server")) {
        rte_exit(EXIT_FAILURE, "Could not initialize logger\n");
    }
    logger->info("Initialize logger success");
    int num = rte_eal_init(argc, argv);
    if(idx < 0) {
        rte_exit(EXIT_FAILURE, "Could not initialise EAL (%d)\n", ret);
    }
    logger->info("Initialize EAL success");
    argc -= idx;
    argv += idx;
    if(!ParseArgs(argc, argv)) {
        rte_exit(EXIT_FAILURE, "Could not parse args, see log file for error message\n");
    }
    return 0;
}
