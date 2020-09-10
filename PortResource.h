//
// Created by taylor on 2020/9/10.
//

#ifndef FASTDNS_PORT_RUN_ENV_H
#define FASTDNS_PORT_RUN_ENV_H

#include <boost/noncopyable.hpp>
#include <memory>
#include "PortConfig.h"
#include <unordered_map>
#include <vector>

namespace fastdns
{

// port run time resources
struct PortResource
{
    PortResource();
    PortResource(const PortConfig* config,
            std::vector<struct rte_kni*>& knis,
            std::vector<struct rte_ring*>& rx_rings,
            std::vector<struct rte_ring*>& tx_rings,
            std::vector<struct rte_ring*>& kni_rings);
    PortResource(PortResource&& res);
    PortResource& operator=(PortResource&& res);

    const PortConfig* config_;
    std::vector<struct rte_kni*> knis_;
    std::vector<struct rte_ring*> rx_rings_;
    std::vector<struct rte_ring*> tx_rings_;
    std::vector<struct rte_ring*> kni_rings_;
};

class PortResources: boost::noncopyable
{
public:
    PortResources();
    ~PortResources();
    bool init(const PortConfigs& configs);
private:
    PortResource& operator[](int port_id);
    bool init_knis(PortResource& res);
    bool init_rx_rings(PortResource& res);
    bool init_tx_rings(PortResource& res);
    bool init_kni_rings(PortResource& res);
    bool init_port(PortResource& res);
private:
    std::unordered_map<int, std::unique_ptr<PortResource>> resources;
};

extern PortResources port_resources;

} // namespace fastdns

#endif //FASTDNS_PORT_RUN_ENV_H
