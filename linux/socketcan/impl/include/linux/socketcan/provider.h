#ifndef LINUX_SOCKETCAN_H_
#define LINUX_SOCKETCAN_H_

// core
#include "core/message.h"
#include "core/providers/base.h"

// libsockcanpp
#include <CanDriver.hpp>
#include <CanId.hpp>

// stdlib
#include <stdint.h> // int32_t
#include <string>   // std::string

using sockcanpp::CanDriver;
using sockcanpp::CanId;

namespace base = can::providers::base;

// can::providers::linux throws error...
namespace can::providers::os::socketcan
{

    // sockcanpp::CanDriver::CanDriver(const std::string &canInterface, int32_t canProtocol, int32_t filterMask, sockcanpp::CanId defaultSenderId = 0)
    struct Options : can::providers::base::Options
    {
        std::string canInterface;
        int32_t canProtocol;
        std::optional<CanId> defaultSenderId;
        std::optional<int32_t> filterMask;
    };

    class CANBus : base::CANBus
    {
    private:
        CanDriver *driver;
        Options *op;

    public:
        CANBus(std::optional<base::bitrate_enum_t> b, base::Options *o);
        virtual ~CANBus(); // desructor

        can::frame_read_res readMessage();
    };
}

#endif /* LINUX_SOCKETCAN_H_ */