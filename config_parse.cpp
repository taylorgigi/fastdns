//
// Created by taylor on 2020/9/10.
//

#include "config_parse.h"
#include "logger.h"
#include "port_config.h"
#include <utility>
#include <yaml-cpp/yaml.h>

namespace fastdns
{

bool parse_config_file(const char *file_path)
{
    YAML::Node config;
    try {
        config = YAML::LoadFile(file_path);
    }
    catch (YAML::BadFile &e) {
        logger->error("[fastdns] YAML::LoadFile({}) failed:{}!", file_path, e.what());
        return false;
    }
    catch (YAML::ParserException &e) {
        logger->error("[fastdsn] YAML::LoadFile({}) failed:{}!", file_path, e.what());
        return false;
    }
    // spdlog level
    YAML::Node spdlog_cfg = config["spdlog"];
    if (!spdlog_cfg) {
        logger->error("[fastdsn] spdlog item not found,{}", file_path);
        return false;
    }
    YAML::Node log_level_cfg = spdlog_cfg["level"];
    if (!log_level_cfg) {
        logger->error("[fastdsn] spdlog.level item not found,{}", file_path);
        return false;
    }
    std::string log_level = log_level_cfg.as<std::string>();
    logger->info("[fastdsn] spdlog.level = {}", log_level.c_str());
    // ports
    YAML::Node ports = config["ports"];
    if(!ports) {
        logger->error("[fastdsn] ports item not found,{}", file_path);
        return false;
    }
    logger->info("[fastdsn] There have {} ports", ports.size());
    for(int i=0; i<ports.size(); ++i) {
        // id
        YAML::Node id = ports[i]["id"];
        if(!id) {
            logger->error("[fastdsn] ports.id item not found,{}", file_path);
            return false;
        }
        int port_id = id.as<int>();
        // queue-num
        YAML::Node queue = ports[i]["queue"];
        if(!queue) {
            logger->error("[fastdsn] ports[{}].queue item not found,{}", i, file_path);
            return false;
        }
        int queue_num = queue.as<int>();
        // rx-lcores
        YAML::Node rx_lcores = ports[i]["rx-lcores"];
        if(!rx_lcores) {
            logger->error("[fastdsn] ports[{}].rx-lcores item not found,{}", i, file_path);
            return false;
        }
        std::vector<int> rxlcores;
        for(int i=0; i<rx_lcores.size(); ++i) {
            rxlcores.push_back(rx_lcores[i].as<int>());
        }
        // tx-lcores
        YAML::Node tx_lcores = ports[i]["tx-lcores"];
        if(!tx_lcores) {
            logger->error("[fastdsn] ports[{}].tx-lcores item not found,{}", i, file_path);
            return false;
        }
        std::vector<int> txlcores;
        for(int i=0; i<tx_lcores.size(); ++i) {
            txlcores.push_back(tx_lcores[i].as<int>());
        }
        // work-lcores
        YAML::Node work_lcores = ports[i]["work-lcores"];
        if(!work_lcores) {
            logger->error("[fastdsn] ports[{}].work-lcores item not found,{}", i, file_path);
            return false;
        }
        std::vector<int> worklcores;
        for(int i=0; i<work_lcores.size(); ++i) {
            worklcores.push_back(work_lcores[i].as<int>());
        }
        // kni-lcores
        YAML::Node kni_lcores = ports[i]["kni-lcores"];
        if(!kni_lcores) {
            logger->error("[fastdsn] ports[{}].kni-lcores item not found,{}", i, file_path);
            return false;
        }
        std::vector<int> knilcores;
        for(int i=0; i<kni_lcores.size(); ++i) {
            knilcores.push_back(kni_lcores[i].as<int>());
        }
        config_map[port_id] = port_config(port_id, queue_num, rxlcores, txlcores, worklcores, knilcores);
    }
}

}

