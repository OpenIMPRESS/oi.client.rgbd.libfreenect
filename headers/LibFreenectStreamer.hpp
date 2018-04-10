#pragma once
#include <asio.hpp>
#include <turbojpeg.h>
#include <cstdlib>
#include <signal.h>

#include "UDPConnector.hpp"
#include "RGBDStreamer.hpp"

#include "libfreenect.h"
#include <libfreenect_sync.h>

namespace oi { namespace core { namespace rgbd {
    
    class LibFreenectStreamer : public RGBDStreamer {
    public:
        LibFreenectStreamer(StreamerConfig cfg, oi::core::network::UDPBase * c);
        bool OpenDevice();
        bool CloseDevice();
        bool HandleData(oi::core::network::DataContainer * dc) ;
        int SendFrame();
    protected:
        int frame_width();
        int frame_height();
        int send_depth_stride();
        int raw_depth_stride();
        int raw_color_stride();
        
        float device_cx();
        float device_cy();
        float device_fx();
        float device_fy();
        float device_depth_scale();
        
        std::string serial;
        std::string device_guid();
        TJPF color_pixel_format();
        
        bool supports_audio();
        bool supports_body();
        bool supports_bidx();
        bool supports_hd();
        
        freenect_context* fn_ctx;
        unsigned long sequence = 0;
    };
    
} } }
