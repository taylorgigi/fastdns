//
// Created by taylor on 2020/9/9.
//

#ifndef FASTDNS_PORT_CONFIG_H
#define FASTDNS_PORT_CONFIG_H

#include <boost/noncopyable.hpp>
#include <memory>
#include <unordered_map>
#include <vector>

namespace fastdns
{

constexpr int MAX_NUM_PORTS = 256;

struct PortConfig
{
public:
    PortConfig();
    PortConfig(int id, int queue_num, std::vector<int>& rx_lcores, std::vector<int>& tx_lcores, std::vector<int>& work_lcores, std::vector<int>& kni_lcores);
    PortConfig(PortConfig&& pc);
    ~PortConfig();

    PortConfig& operator=(PortConfig&& pc);

    int id_;
    int queue_num_;
    std::vector<int> rx_lcores_;
    std::vector<int> tx_lcores_;
    std::vector<int> work_lcores_;
    std::vector<int> kni_lcores_;
};

// thread-unsafe, just for read
class PortConfigs: public boost::noncopyable
{
public:
    PortConfigs();
    ~PortConfigs();
    PortConfig& operator[](int port_id);
    decltype(auto) begin();
    decltype(auto) end();
private:
    std::unordered_map<int, std::unique_ptr<PortConfig>> config_;
};

extern PortConfigs configs;

}



#endif //FASTDNS_PORT_CONFIG_H
