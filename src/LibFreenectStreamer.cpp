#include "LibFreenectStreamer.hpp"

namespace oi { namespace core { namespace rgbd {
    
    LibFreenectStreamer::LibFreenectStreamer(StreamerConfig cfg, oi::core::network::UDPBase * c) : RGBDStreamer(cfg, c) {
    }
    
    bool LibFreenectStreamer::OpenDevice() {
        int ret = freenect_init(&fn_ctx, NULL);
        if (ret < 0) return false;
        
        freenect_set_log_level(fn_ctx, FREENECT_LOG_FATAL);
        freenect_select_subdevices(fn_ctx, FREENECT_DEVICE_CAMERA);
        int num_devices = ret = freenect_num_devices(fn_ctx);
        if (ret < 0 || num_devices == 0) {
            printf("No device found!\n");
            freenect_shutdown(fn_ctx);
            return false;
        }
        
        return true;
    }
    
    int LibFreenectStreamer::SendFrame() {
        uint32_t ts;
        short *depth = 0;
        char *rgb = 0;
        int ret = 0;
        
        ret = freenect_sync_get_video((void**)&rgb, &ts, 0, FREENECT_VIDEO_RGB);
        if (ret < 0) {
            std::cout << "Error freenect_sync_get_video" << std::endl;
            return 0;
        }

        ret = freenect_sync_get_depth((void**)&depth, &ts, 0, FREENECT_DEPTH_REGISTERED);
        if (ret < 0) {
            std::cout << "Error freenect_sync_get_depth" << std::endl;
            return 0;
        }
        
        std::chrono::milliseconds timestamp = NOW();
        int result = _SendRGBDFrame(++sequence, (unsigned char *) rgb, (unsigned short *) depth, timestamp);
        return result; // res
    }
    
    bool LibFreenectStreamer::CloseDevice() {
        /*
        freenect_stop_depth(fn_dev);
        freenect_stop_video(fn_dev);
        freenect_close_device(fn_dev);
         */

        freenect_shutdown(fn_ctx);
        return true;
    }
    
    bool LibFreenectStreamer::HandleData(oi::core::network::DataContainer * dc) {
        return false;
    }
    
    int LibFreenectStreamer::frame_width() {
        return 640;
    }
    
    int LibFreenectStreamer::frame_height() {
        return 480;
    }
    
    int LibFreenectStreamer::send_depth_stride() {
        return 2;
    }
    
    int LibFreenectStreamer::raw_depth_stride() {
        return 4;
    }
    
    int LibFreenectStreamer::raw_color_stride() {
        return 4;
    }
    
    float LibFreenectStreamer::device_cx() {
        //if (this->dev == 0) return 0.0f;
        return 339.5f;//i_d.cx;
    }
    
    float LibFreenectStreamer::device_cy() {
        //if (this->dev == 0) return 0.0f;
        return 242.7f;//i_d.cy;
    }
    
    float LibFreenectStreamer::device_fx() {
        //if (this->dev == 0) return 0.0f;
        return 594.21f;//i_d.fx;
    }
    
    float LibFreenectStreamer::device_fy() {
        //if (this->dev == 0) return 0.0f;
        return 591.04f;//i_d.fy;
    }
    
    float LibFreenectStreamer::device_depth_scale() {
        //if (this->dev == 0) return 0.0f;
        return 0.001f; // TODO: is this correct for kinect?!
    }
    
    std::string LibFreenectStreamer::device_guid() {
        //if (this->dev == 0) return "";
        return serial;
    }
    
    TJPF LibFreenectStreamer::color_pixel_format() {
        return TJPF_RGB;
    }
    
    bool LibFreenectStreamer::supports_audio() {
        return false;
    }
    
    bool LibFreenectStreamer::supports_body() {
        return false;
    }
    
    bool LibFreenectStreamer::supports_bidx() {
        return false;
    }
    
    bool LibFreenectStreamer::supports_hd() {
        return false;
    }
    
} } }
