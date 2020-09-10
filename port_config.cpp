//
// Created by taylor on 2020/9/9.
//

#include "port_config.h"

namespace fastdns
{

namespace {
   constexpr int MAX_NUM_PORTS = 256;
}

// ======== port_config =============
port_config::port_config()
: id_(-1),
queue_num_(0)
{}

port_config::port_config(int id, int queue_num, std::vector<int> &rx_lcores, std::vector<int> &tx_lcores, std::vector<int> &work_lcores, std::vector<int> &kni_lcores)
: id_(id),
queue_num_(queue_num),
rx_lcores_(std::move(rx_lcores)),
tx_lcores_(std::move(tx_lcores)),
work_lcores_(std::move(work_lcores)),
kni_lcores_(std::move(kni_lcores))
{}

port_config::port_config(fastdns::port_config &&pc)
{
    id_ = pc.id_;
    queue_num_ = pc.queue_num_;
    rx_lcores_ = std::move(pc.rx_lcores_);
    tx_lcores_ = std::move(pc.tx_lcores_);
    work_lcores_ = std::move(pc.work_lcores_);
    kni_lcores_ = std::move(pc.kni_lcores_);
}

port_config::~port_config()
{}

port_config& port_config::operator=(fastdns::port_config &&pc)
{
    id_ = pc.id_;
    queue_num_ = pc.queue_num_;
    rx_lcores_ = std::move(pc.rx_lcores_);
    tx_lcores_ = std::move(pc.tx_lcores_);
    work_lcores_ = std::move(pc.work_lcores_);
    kni_lcores_ = std::move(pc.kni_lcores_);
    return *this;
}

// ============== PortConfigMap ==================
PortConfigMap::PortConfigMap()
{
    config.reserve(MAX_NUM_PORTS);
}

PortConfigMap::~PortConfigMap()
{}

port_config& PortConfigMap::operator[](int port_id)
{
    auto it = config.find(port_id);
    if(it != config.end())
        return *(it->second);
    config[port_id] = std::make_unique<port_config>();
    return *config[port_id];
}

PortConfigMap config_map;

} // namespace fastdns
