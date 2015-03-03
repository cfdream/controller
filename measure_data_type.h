#ifndef MEASURE_DATA_TYPE_H
#define MEASURE_DATA_TYPE_H

#include <stdint.h>
#include <map>

using namespace std;

#define PORT_SIZE 5

//typedef unsigned int uint32_t;
//typedef unsigned long long uint64_t;

struct flow_key_s {
    uint32_t srcip;

    bool const operator==(const flow_key_s &o) const {
        return srcip == o.srcip;
    }

    bool const operator<(const flow_key_s &o) const {
        return srcip < o.srcip;
    }
};

typedef flow_key_s flow_key_t;

typedef struct sampled_volume_record_s {
    flow_key_t flow_key;
    uint64_t port_volumes[PORT_SIZE];      //attention: at most 5 outports for one ovs
} sampled_record_t;

//data from different switches. One switch has one ip different from others
map<uint32_t, map<flow_key_t, sampled_record_t>* > ip_flow_sampled_record_map;  

void insert_sampled_record_into_map(uint32_t client_ip, sampled_record_t sampled_record);

void insert_sampled_record_into_map(uint32_t client_ip, sampled_record_t sampled_record) {
    map<flow_key_t, sampled_record_t>* p_sampled_record_map;
    if (ip_flow_sampled_record_map.find(client_ip) == ip_flow_sampled_record_map.end()) {
        p_sampled_record_map = new map<flow_key_t, sampled_record_t>();
        ip_flow_sampled_record_map[client_ip] = p_sampled_record_map;
    } else {
        p_sampled_record_map = ip_flow_sampled_record_map[client_ip];
    }

    (*p_sampled_record_map)[sampled_record.flow_key] = sampled_record;
}


#endif
