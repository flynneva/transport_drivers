// Copyright 2021 LeoDrive.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Developed by LeoDrive, 2021

#ifndef UDP_DRIVER__UDP_DRIVER_HPP_
#define UDP_DRIVER__UDP_DRIVER_HPP_

#include <iostream>
#include <memory>
#include <string>

#ifdef _WIN32
#include <SDKDDKVer.h>  // gets rid of boost compiler warning
#endif

#include "io_context/io_context.hpp"

#include "udp_driver/udp_socket.hpp"
#include "udp_driver/visibility_control.hpp"

namespace drivers
{
namespace udp_driver
{

class UdpDriver
{
public:
  UDP_DRIVER_PUBLIC
  explicit UdpDriver(const IoContext & ctx);

  UDP_DRIVER_PUBLIC
  void init_sender(const std::string & ip, uint16_t port);

  UDP_DRIVER_PUBLIC
  void init_receiver(const std::string & ip, uint16_t port);

  UDP_DRIVER_PUBLIC
  std::shared_ptr<UdpSocket> sender() const;

  UDP_DRIVER_PUBLIC
  std::shared_ptr<UdpSocket> receiver() const;

private:
  const IoContext & m_ctx;
  std::shared_ptr<UdpSocket> m_sender;
  std::shared_ptr<UdpSocket> m_receiver;
};

}  // namespace udp_driver
}  // namespace drivers

#endif  // UDP_DRIVER__UDP_DRIVER_HPP_
