//
// Created by taylor on 2020/9/9.
//

#include "PortConfig.h"

namespace fastdns
{

// ======== PortConfig =============
PortConfig::PortConfig()
: id_(-1),
queue_num_(0)
{}

PortConfig::PortConfig(int id, int queue_num, std::vector<int> &rx_lcores, std::vector<int> &tx_lcores, std::vector<int> &work_lcores, std::vector<int> &kni_lcores)
: id_(id),
  queue_num_(queue_num),
  rx_lcores_(std::move(rx_lcores)),
  tx_lcores_(std::move(tx_lcores)),
  work_lcores_(std::move(work_lcores)),
  kni_lcores_(std::move(kni_lcores))
{}

PortConfig::PortConfig(fastdns::PortConfig &&pc)
: id_(pc.id_),
  queue_num_(pc.queue_num_),
  rx_lcores_(std::move(pc.rx_lcores_)),
  tx_lcores_(std::move(pc.tx_lcores_)),
  work_lcores_(std::move(pc.work_lcores_)),
  kni_lcores_(std::move(pc.kni_lcores_))
{}

PortConfig::~PortConfig()
{}

PortConfig& PortConfig::operator=(fastdns::PortConfig &&pc)
{
    id_ = pc.id_;
    queue_num_ = pc.queue_num_;
    rx_lcores_ = std::move(pc.rx_lcores_);
    tx_lcores_ = std::move(pc.tx_lcores_);
    work_lcores_ = std::move(pc.work_lcores_);
    kni_lcores_ = std::move(pc.kni_lcores_);
    return *this;
}

// ============== PortConfigs ==================
PortConfigs::PortConfigs()
{
    config_.reserve(MAX_NUM_PORTS);
}

PortConfigs::~PortConfigs()
{}

PortConfig& PortConfigs::operator[](int port_id)
{
    auto it = config_.find(port_id);
    if(it != config_.end())
        return *(it->second);
    config_[port_id] = std::make_unique<PortConfig>();
    return *config_[port_id];
}

decltype(auto) PortConfigs::begin()
{
    return config_.begin();
}

decltype(auto) PortConfigs::end()
{
    return config_.end();
}

PortConfigs configs;

} // namespace fastdns
