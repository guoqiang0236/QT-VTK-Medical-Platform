#ifndef RAWREADER_H
#define RAWREADER_H

#include <string>
#include <vector>
#include <complex>
#include <fstream>
#include <cstdint>

// 数据头结构定义
struct BMFMDataHeader {
    char data_tag[10];
    uint16_t ping_number;
    uint32_t curr_sys_time;
    uint16_t curr_time_ms;
    uint8_t probe_id;
    uint8_t bf_mode;
    int8_t Incident_Angle;
    uint8_t Spatial_Compounding_Flag;
    uint8_t Focus_number;
    uint8_t Focus_idx;
    uint8_t Parallel_bmfm_start_line;
    uint8_t Parallel_bmfm_lines;
    uint8_t pitch;
    uint16_t Rconvex;
    uint16_t cspeed;
    uint16_t Num_Pts_Per_Line;
    uint16_t corr_shift_real;
    uint16_t corr_shift_imag;
    uint32_t Recv_Freq;
    uint16_t Xmit_Volt;
    uint8_t X_Geolocation;
    uint8_t ExtViewAngle;
    uint16_t Xmit_Cycle;
    uint16_t Downsampling_interval;
    uint8_t Xmit_Polarity;
    uint8_t Doppler12LineBmfmNumber;
    uint16_t sample_max_cnt;
    uint8_t Xmit_F_number;
    uint8_t BModeImageOffset;
    uint8_t System_Capacity;
    uint8_t Scan_interval_lines;
    uint16_t Xmit_Focus_Distance;
    uint16_t Uniform_Xmit_Focus_Distance;
    uint32_t Header_Addr_step;
    uint16_t Packet_size;
    uint8_t flagHBCompound;
    uint8_t flagHModeType;
    uint16_t Receive_period;
    uint16_t Recv_Count_Max;
    uint16_t Recv_Gain_adj_pts;
    uint8_t Recv_F_number;
    uint8_t BMode12LineArrange;
    uint8_t UniformFocus_flag;
    uint16_t mline_num_in_Bframe;
    uint16_t BROI_num_pts_per_line;
    uint16_t Recv_Gain_Interval;
    uint16_t Recv_Gain_Start;
    uint16_t Gain_Shift_bit;
    uint16_t Sub_block_trig_num;
    uint16_t mtrig_num_ROI;
    uint16_t mline_num_in_trig;
    int32_t Filter_Coeff[10];
    uint16_t Num_Recv_Line_Per_Frame;
    uint8_t left_extra_trig_num;
    uint8_t right_extra_trig_num;
    uint8_t B_XMIT_PAT;
    uint8_t speckleSizeChoice;
    uint8_t Doppler_Moving_window_size;
    uint8_t Doppler_batch_num;
    uint16_t Doppler_start_line_number;
    uint16_t Doppler_start_sample_number;
    uint32_t Data_len; // 数据长度
    uint16_t num_trig_per_mtrig; // 触发次数
    uint16_t Spc_Num_pts_per_line;
    uint16_t Num_Trig_Per_Frame; // 添加此字段以修复错误  
    uint16_t Spc_start_pt; // 添加此字段以修复错误  
};

// RawReader 类定义
class RawReader {
public:
    RawReader();
    ~RawReader();

    bool open(const std::string& filename);
    void close();
    bool readFrame(BMFMDataHeader& header, std::vector<std::complex<float>>& data);
    bool readAllFrames(std::vector<BMFMDataHeader>& headers, std::vector<std::vector<std::complex<float>>>& allData);
 
    bool readHeader(BMFMDataHeader& header);
	void setnz_(size_t nz) { nz_ = nz; } 
	void setnx_(size_t nx) { nx_ = nx; }
	size_t getnz_() const { return nz_; }
	size_t getnx_() const { return nx_; }
	float getGlobalMax() const { return m_globalMax; }
	const float getThetaStart() const { return theta_start; }
	const float getThetaEnd() const { return theta_end; }
	const float getRMax() const { return r_max; }
private:
    std::ifstream file_;
    const std::vector<int> pick_lines_ = { 0,1,2,3,4,5,6,7,8,9,10,11 }; // 默认全选12通道
    size_t nz_ = 528;  
    size_t nx_ = 66;  
    float  m_globalMax = 0.0f;
    const float theta_start = -M_PI / 4;
    const float theta_end = M_PI / 4;
    const float r_max = 1.0;
    bool skipBytes(size_t count);
    bool readBMode(BMFMDataHeader& header, std::vector<std::complex<float>>& data);
    bool readHMMode(BMFMDataHeader& header, std::vector<std::complex<float>>& data);
    bool readSMode(BMFMDataHeader& header, std::vector<std::complex<float>>& data);
    bool readHMode(BMFMDataHeader& header, std::vector<std::complex<float>>& data);
};

#endif // RAWREADER_H
