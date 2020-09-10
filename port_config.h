//
// Created by taylor on 2020/9/9.
//

#ifndef FASTDNS_PORT_CONFIG_H
#define FASTDNS_PORT_CONFIG_H

#include <boost/noncopyable.hpp>
#include <unordered_map>

namespace fastdns
{

struct port_config
{
public:
    port_config();
    port_config(int id, int queue_num, std::vector<int>& rx_lcores, std::vector<int>& tx_lcores, std::vector<int>& kni_lcores);
    port_config(port_config&& pc);
    ~port_config();

    port_config& operator=(port_config&& pc);

    int id_;
    int queue_num_;
    std::vector<int> rx_lcores_;
    std::vector<int> tx_lcores_;
    std::vector<int> kni_lcores_;
};

// thread-unsafe, just for read
class PortConfigMap: public boost::noncopyable
{
public:
    PortConfigMap();
    ~PortConfigMap();
    auto& operator[](int port_id);
private:
    std::unordered_map<int, std::unique_ptr<port_config>> config;
};

extern PortConfigMap config_map;

}



#endif //FASTDNS_PORT_CONFIG_H
