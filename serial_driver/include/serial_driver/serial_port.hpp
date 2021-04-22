// Copyright 2021 LeoDrive, Copyright 2021 The Autoware Foundation
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

#ifndef SERIAL_DRIVER__SERIAL_PORT_HPP_
#define SERIAL_DRIVER__SERIAL_PORT_HPP_

#include <array>
#include <string>
#include <vector>

#include "io_context/common.hpp"
#include "io_context/io_context.hpp"

#include "serial_driver/visibility_control.hpp"

using spb = asio::serial_port_base;
using drivers::common::IoContext;

namespace drivers
{
namespace serial_driver
{

using Functor = std::function<void (std::vector<uint8_t> &)>;

enum class FlowControl
{
  NONE,
  HARDWARE,
  SOFTWARE
};

enum class Parity
{
  NONE,
  ODD,
  EVEN
};

enum class StopBits
{
  ONE,
  ONE_POINT_FIVE,
  TWO
};

class SerialPortConfig
{
public:
  /// \brief Default constructor
  SERIAL_DRIVER_PUBLIC
  SerialPortConfig(
    uint32_t baud_rate,
    FlowControl flow_control,
    Parity parity,
    StopBits stop_bits)
  : m_baud_rate{baud_rate},
    m_flow_control{flow_control},
    m_parity{parity},
    m_stop_bits{stop_bits}
  {
  }

  /// \brief Function that returns the configured buad rate
  /// \returns The configured buad rate in bps
  SERIAL_DRIVER_PUBLIC
  uint32_t get_baud_rate() const
  {
    return m_baud_rate;
  }

  /// \brief Function that returns the configured baud rate as an ASIO object
  /// \returns The configured baud rate as an ASIO baud_rate object
  SERIAL_DRIVER_PUBLIC
  spb::baud_rate get_baud_rate_asio() const
  {
    return spb::baud_rate{m_baud_rate};
  }

  /// \breif Function that returns the configured flow control
  /// \returns The configured flow control type
  SERIAL_DRIVER_PUBLIC
  FlowControl get_flow_control() const
  {
    return m_flow_control;
  }

  /// \breif Function that returns the configured flow control as an ASIO object
  /// \returns The configured flow control type as an ASIO flow_control object
  SERIAL_DRIVER_PUBLIC
  spb::flow_control::type get_flow_control_asio() const
  {
    switch (m_flow_control) {
      case FlowControl::HARDWARE:
        return spb::flow_control::hardware;
        break;
      case FlowControl::SOFTWARE:
        return spb::flow_control::software;
        break;
      case FlowControl::NONE:
      default:
        return spb::flow_control::none;
    }
  }

  /// \brief Function that returns the configured parity type
  /// \returns The configured parity type
  SERIAL_DRIVER_PUBLIC
  Parity get_parity() const
  {
    return m_parity;
  }

  /// \brief Function that returns the configured parity type as an ASIO object
  /// \returns The configured parity type as an ASIO parity object
  SERIAL_DRIVER_PUBLIC
  spb::parity::type get_parity_asio() const
  {
    switch (m_parity) {
      case Parity::ODD:
        return spb::parity::odd;
        break;
      case Parity::EVEN:
        return spb::parity::even;
        break;
      case Parity::NONE:
      default:
        return spb::parity::none;
    }
  }

  /// \brief Function that returns the configured stop bits
  /// \returns The configured stop bits
  SERIAL_DRIVER_PUBLIC
  StopBits get_stop_bits() const
  {
    return m_stop_bits;
  }

  /// \brief Function that returns the configured stop bits as an ASIO object
  /// \returns The configured stop bits as an ASIO stop_bits object
  SERIAL_DRIVER_PUBLIC
  spb::stop_bits::type get_stop_bits_asio() const
  {
    switch (m_stop_bits) {
      case StopBits::ONE_POINT_FIVE:
        return spb::stop_bits::onepointfive;
        break;
      case StopBits::TWO:
        return spb::stop_bits::two;
        break;
      case StopBits::ONE:
      default:
        return spb::stop_bits::one;
    }
  }

private:
  uint32_t m_baud_rate;
  FlowControl m_flow_control;
  Parity m_parity;
  StopBits m_stop_bits;
};

class SerialPort
{
public:
  /// \brief Default constructor
  /// \param[in] ctx An IoContext object to handle threads
  /// \param[in] device_name The name of the serial device in the OS
  /// \param[in] serial_port_config Configuration options for the serial port
  SERIAL_DRIVER_PUBLIC
  SerialPort(
    const IoContext & ctx,
    const std::string & device_name,
    const SerialPortConfig serial_port_config);
  
  SERIAL_DRIVER_PUBLIC
  ~SerialPort();

  SERIAL_DRIVER_PUBLIC
  SerialPort(const SerialPort &) = delete;

  SERIAL_DRIVER_PUBLIC
  SerialPort & operator=(const SerialPort &) = delete;

  /// \brief Function to return the stored device name
  /// \returns Device name as a string
  SERIAL_DRIVER_PUBLIC
  std::string device_name() const;

  /// \brief Function to return the stored serial port configuration
  /// \returns SerialPortConfig object representing the stored serial port configuration
  SERIAL_DRIVER_PUBLIC
  SerialPortConfig serial_port_config() const;

  /// \brief Function to open the serial port as-configured
  SERIAL_DRIVER_PUBLIC
  void open();

  /// \brief Function to close the serial port as-configured
  SERIAL_DRIVER_PUBLIC
  void close();

  /// \brief Function to check whether the port is already open
  /// \returns Bool indicating whether the port is currently open
  SERIAL_DRIVER_PUBLIC
  bool is_open() const;

  /// \brief Blocking send operation
  /// \param[in] buff A buffer containing the data to send
  /// \returns The number of bytes sent
  SERIAL_DRIVER_PUBLIC
  size_t send(const std::vector<uint8_t> & buff);

  /// \brief Bocking receive operation
  /// \param[out] buff A buffer to be populated with the read data
  /// \returns The number of bytes read
  SERIAL_DRIVER_PUBLIC
  size_t receive(std::vector<uint8_t> & buff);

  /// \brief Non-blocking send operation
  /// \param[in] buff A buffer containing the data to send
  SERIAL_DRIVER_PUBLIC
  void async_send(const std::vector<uint8_t> & buff);

  /// \brief Non-blocking receive operation
  /// \param[in] func A function to be called when data are received
  SERIAL_DRIVER_PUBLIC
  void async_receive(Functor func);

private:
  void async_send_handler(
    const asio::error_code & error,
    size_t bytes_transferred);

  void async_receive_handler(
    const asio::error_code & error,
    size_t bytes_transferred);

  const IoContext & m_ctx;
  std::string m_device_name;
  asio::serial_port m_serial_port;
  SerialPortConfig m_port_config;
  Functor m_func;
  static constexpr size_t m_recv_buffer_size{2048};
  std::vector<uint8_t> m_recv_buffer;
};

}  // namespace serial_driver
}  // namespace drivers

#endif  // SERIAL_DRIVER__SERIAL_PORT_HPP_
