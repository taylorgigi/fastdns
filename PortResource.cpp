//
// Created by taylor on 2020/9/10.
//

#include "logger.h"
#include "PortResource.h"

namespace fastdns
{

// port resource
PortResource::PortResource()
{}

PortResource::PortResource(const PortConfig *config,
        std::vector<rte_kni*>& knis,
        std::vector<rte_ring*>& rx_rings,
        std::vector<rte_ring*>& tx_rings,
        std::vector<rte_ring*>& kni_rings)
: config_(config),
  knis_(std::move(knis)),
  rx_rings_(std::move(rx_rings)),
  tx_rings_(std::move(tx_rings)),
  kni_rings_(std::move(kni_rings))
{}

PortResource::PortResource(fastdns::PortResource&& pr)
: config_(pr.config_),
  knis_(std::move(pr.knis_)),
  rx_rings_(std::move(pr.rx_rings_)),
  tx_rings_(std::move(pr.tx_rings_)),
  kni_rings_(std::move(pr.kni_rings_))
{}

PortResource& PortResource::operator=(PortResource&& res)
{
    config_ = pr.config_;
    knis_ = std::move(pr.knis_);
    rx_rings_=std::move(pr.rx_rings_);
    tx_rings_=std::move(pr.tx_rings_);
    kni_rings_=std::move(pr.kni_rings_);
    return *this;
}

// PortResources
PortResources::PortResources()
{
    resources.reserve(MAX_NUM_PORTS);
}

PortResources::~PortResources()
{}

bool PortResources::init(const fastdns::PortConfigs& port_configs)
{
    for(auto it : port_configs) {
        const PortConfig& config = it->second;
        resources[config.id_].config_ = &config;
        if(!init_knis(resources[config.id_].knis_)) {
            logger->error("[fastdns] port{} could not init knis", config.id_);
            return false;
        }
        if(!init_rx_rings(resources[config.id_].rx_rings_)) {
            logger->error("[fastdns] port{} could not init rx rings", config.id_);
            return false;
        }
        if(!init_tx_rings(resources[config.id_].tx_rings_)) {
            logger->error("[fastdns] port{} could not init tx rings", config.id_);
            return false;
        }
        if(!init_kni_rings(resources[config.id_].kni_rings_)) {
            logger->error("[fastdns] port{} could not init kni rings", config.id_);
            return false;
        }
        if(!init_port(resources[config.id_].kni_rings_)) {
            logger->error("[fastdns] port{} could not init port", config.id_);
            return false;
        }
    }
    return true;
}

PortResource& PortResources::operator[](int port_id)
{
    auto it = resources.find(port_id);
    if(it != resources.end())
        return *it;
    resources[port_id] = std::make_unique<PortResource>();
    return resources[port_id];
}

PortResource port_resources;

}
