#pragma once

#include <string>
#include <zmq.hpp>
#include <svc_config.pb.h>
#include <util/compare_messages.hh>
#include <util/async_worker.hh>
#include <util/zmq.hh>
#include "config_client.hh"
#include "endpoint_server.hh"

namespace virtdb { namespace connector {
  
  class config_server final
  {
    zmq::context_t               zmqctx_;
    util::zmq_socket_wrapper     cfg_pull_socket_;
    util::zmq_socket_wrapper     cfg_pub_socket_;
    util::async_worker           worker_;
    std::mutex                   mtx_;

    bool worker_function();
    
  public:
    config_server(config_client & cfg_client,
                  endpoint_server & ep_server);
    ~config_server();
    
  private:
    config_server() = delete;
    config_server(const config_server &) = delete;
    config_server & operator=(const config_server &) = delete;
  };
}}
