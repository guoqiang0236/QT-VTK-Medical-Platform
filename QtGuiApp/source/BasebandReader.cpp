#include "BasebandReader.h"
#include <iostream>
#include <vector>
#include <complex>
#include <cstring>
#include <limits>

RawReader::RawReader() {}

RawReader::~RawReader() {
    close();
}

bool RawReader::open(const std::string& filename) {
    file_.open(filename, std::ios::binary | std::ios::in);
    if (!file_.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return false;
    }
    static char buffer[65536]; // 64 KB 缓冲区
    file_.rdbuf()->pubsetbuf(buffer, sizeof(buffer));
    return true;
}

void RawReader::close() {
    if (file_.is_open()) {
        file_.close();
    }
}


bool RawReader::readFrame(BMFMDataHeader& header, std::vector<std::complex<float>>& data) {
    if (!file_.is_open()) {
        return false;
    }

    // 读取帧长度
    uint32_t frame_len = 0;
    if (!file_.read(reinterpret_cast<char*>(&frame_len), sizeof(frame_len))) {
        return false; // 文件结束或读取失败
    }

    // 检查帧长度是否合理
    if (frame_len < 192 + 40) {
        std::cerr << "Invalid frame length: " << frame_len << std::endl;
        return false;
    }

    // 计算数据部分长度
    const size_t data_section_len = frame_len - 192 - 40;
    const size_t complex_data_len = data_section_len / 2;
    header.Data_len = static_cast<int>(data_section_len);

    // 读取头部信息
    if (!readHeader(header)) {
        return false;
    }

    // 根据模式读取数据
    bool success = false;
    switch (header.bf_mode) {
    case 30: // BM-mode
        success = readBMode(header, data);
        break;
    case 31: // HM-mode
        success = readHMMode(header, data);
        break;
    case 6:  // S-mode
        success = readSMode(header, data);
        break;
    case 19: // H-mode
        success = readHMode(header, data);
        break;
    default:
        // 跳过未知模式数据
        if (!skipBytes(frame_len - 192)) {
            return false;
        }
        success = false;
    }

    // 跳过尾部 40 字节
    if (success) {
        if (!skipBytes(40)) {
            return false;
        }
    }

    return success;
}



bool RawReader::readHeader(BMFMDataHeader& header) {
    file_.read(header.data_tag, sizeof(header.data_tag));
    file_.read(reinterpret_cast<char*>(&header.ping_number), sizeof(header.ping_number));
    file_.read(reinterpret_cast<char*>(&header.curr_sys_time), sizeof(header.curr_sys_time));
    file_.read(reinterpret_cast<char*>(&header.curr_time_ms), sizeof(header.curr_time_ms));
    file_.read(reinterpret_cast<char*>(&header.probe_id), sizeof(header.probe_id));
    file_.read(reinterpret_cast<char*>(&header.bf_mode), sizeof(header.bf_mode));
    file_.read(reinterpret_cast<char*>(&header.Incident_Angle), sizeof(header.Incident_Angle));
    file_.read(reinterpret_cast<char*>(&header.Spatial_Compounding_Flag), sizeof(header.Spatial_Compounding_Flag));

    uint8_t byte_data;
    file_.read(reinterpret_cast<char*>(&byte_data), sizeof(byte_data));
    header.Focus_number = byte_data & 0x0F;
    header.Focus_idx = (byte_data >> 4) & 0x0F;

    file_.read(reinterpret_cast<char*>(&header.Parallel_bmfm_start_line), sizeof(header.Parallel_bmfm_start_line));
    file_.read(reinterpret_cast<char*>(&header.Parallel_bmfm_lines), sizeof(header.Parallel_bmfm_lines));
    file_.read(reinterpret_cast<char*>(&header.pitch), sizeof(header.pitch));
    file_.read(reinterpret_cast<char*>(&header.Rconvex), sizeof(header.Rconvex));
    file_.read(reinterpret_cast<char*>(&header.cspeed), sizeof(header.cspeed));
    file_.read(reinterpret_cast<char*>(&header.Num_Pts_Per_Line), sizeof(header.Num_Pts_Per_Line));
    file_.read(reinterpret_cast<char*>(&header.corr_shift_real), sizeof(header.corr_shift_real));
    header.Spc_Num_pts_per_line = header.corr_shift_real;
    file_.read(reinterpret_cast<char*>(&header.Num_Trig_Per_Frame), sizeof(header.Num_Trig_Per_Frame));
    file_.read(reinterpret_cast<char*>(&header.corr_shift_imag), sizeof(header.corr_shift_imag));
    header.Spc_start_pt = header.corr_shift_imag;
    file_.read(reinterpret_cast<char*>(&header.Recv_Freq), sizeof(header.Recv_Freq));
    file_.read(reinterpret_cast<char*>(&header.Xmit_Volt), sizeof(header.Xmit_Volt));
    file_.read(reinterpret_cast<char*>(&header.X_Geolocation), sizeof(header.X_Geolocation));
    file_.read(reinterpret_cast<char*>(&header.ExtViewAngle), sizeof(header.ExtViewAngle));
    file_.read(reinterpret_cast<char*>(&header.Xmit_Cycle), sizeof(header.Xmit_Cycle));
    file_.read(reinterpret_cast<char*>(&header.Downsampling_interval), sizeof(header.Downsampling_interval));
    file_.read(reinterpret_cast<char*>(&header.Xmit_Polarity), sizeof(header.Xmit_Polarity));
    file_.read(reinterpret_cast<char*>(&header.Doppler12LineBmfmNumber), sizeof(header.Doppler12LineBmfmNumber));
    file_.read(reinterpret_cast<char*>(&header.sample_max_cnt), sizeof(header.sample_max_cnt));
    file_.read(reinterpret_cast<char*>(&header.Xmit_F_number), sizeof(header.Xmit_F_number));
    file_.read(reinterpret_cast<char*>(&header.BModeImageOffset), sizeof(header.BModeImageOffset));
    file_.read(reinterpret_cast<char*>(&header.System_Capacity), sizeof(header.System_Capacity));
    file_.read(reinterpret_cast<char*>(&header.Scan_interval_lines), sizeof(header.Scan_interval_lines));
    file_.read(reinterpret_cast<char*>(&header.Xmit_Focus_Distance), sizeof(header.Xmit_Focus_Distance));
    file_.read(reinterpret_cast<char*>(&header.Uniform_Xmit_Focus_Distance), sizeof(header.Uniform_Xmit_Focus_Distance));
    file_.read(reinterpret_cast<char*>(&header.Header_Addr_step), sizeof(header.Header_Addr_step));
    file_.read(reinterpret_cast<char*>(&header.Packet_size), sizeof(header.Packet_size));
    file_.read(reinterpret_cast<char*>(&header.flagHBCompound), sizeof(header.flagHBCompound));
    header.num_trig_per_mtrig = header.flagHBCompound;
    file_.read(reinterpret_cast<char*>(&header.flagHModeType), sizeof(header.flagHModeType));
    file_.read(reinterpret_cast<char*>(&header.Receive_period), sizeof(header.Receive_period));
    file_.read(reinterpret_cast<char*>(&header.Recv_Count_Max), sizeof(header.Recv_Count_Max));
    file_.read(reinterpret_cast<char*>(&header.Recv_Gain_adj_pts), sizeof(header.Recv_Gain_adj_pts));
    file_.read(reinterpret_cast<char*>(&header.Recv_F_number), sizeof(header.Recv_F_number));

    file_.read(reinterpret_cast<char*>(&byte_data), sizeof(byte_data));
    header.BMode12LineArrange = byte_data & 0x0F;
    header.UniformFocus_flag = (byte_data >> 4) & 0x0F;

    file_.read(reinterpret_cast<char*>(&header.mline_num_in_Bframe), sizeof(header.mline_num_in_Bframe));
    file_.read(reinterpret_cast<char*>(&header.BROI_num_pts_per_line), sizeof(header.BROI_num_pts_per_line));
    file_.read(reinterpret_cast<char*>(&header.Recv_Gain_Interval), sizeof(header.Recv_Gain_Interval));
    file_.read(reinterpret_cast<char*>(&header.Recv_Gain_Start), sizeof(header.Recv_Gain_Start));
    file_.read(reinterpret_cast<char*>(&header.Gain_Shift_bit), sizeof(header.Gain_Shift_bit));
    file_.read(reinterpret_cast<char*>(&header.Sub_block_trig_num), sizeof(header.Sub_block_trig_num));
    file_.read(reinterpret_cast<char*>(&header.mtrig_num_ROI), sizeof(header.mtrig_num_ROI));
    file_.read(reinterpret_cast<char*>(&header.mline_num_in_trig), sizeof(header.mline_num_in_trig));

    for (int i = 0; i < 10; ++i) {
        file_.read(reinterpret_cast<char*>(&header.Filter_Coeff[i]), sizeof(header.Filter_Coeff[i]));
    }

    file_.read(reinterpret_cast<char*>(&header.Num_Recv_Line_Per_Frame), sizeof(header.Num_Recv_Line_Per_Frame));
    file_.read(reinterpret_cast<char*>(&header.left_extra_trig_num), sizeof(header.left_extra_trig_num));
    file_.read(reinterpret_cast<char*>(&header.right_extra_trig_num), sizeof(header.right_extra_trig_num));
    file_.read(reinterpret_cast<char*>(&header.B_XMIT_PAT), sizeof(header.B_XMIT_PAT));
    file_.read(reinterpret_cast<char*>(&header.speckleSizeChoice), sizeof(header.speckleSizeChoice));
    file_.read(reinterpret_cast<char*>(&header.Doppler_Moving_window_size), sizeof(header.Doppler_Moving_window_size));
    file_.read(reinterpret_cast<char*>(&header.Doppler_batch_num), sizeof(header.Doppler_batch_num));
    file_.read(reinterpret_cast<char*>(&header.Doppler_start_line_number), sizeof(header.Doppler_start_line_number));
    file_.read(reinterpret_cast<char*>(&header.Doppler_start_sample_number), sizeof(header.Doppler_start_sample_number));

    // 跳过 46 字节
    skipBytes(46);

    return true;
}

bool RawReader::skipBytes(size_t count) {
    if (file_.eof()) return false;
    file_.seekg(count, std::ios::cur);
    return !file_.fail();
}

bool RawReader::readBMode(BMFMDataHeader& header, std::vector<std::complex<float>>& data) {
    const uint16_t num_trig_per_mtrig = header.num_trig_per_mtrig;
    const uint16_t trig_num = header.Num_Trig_Per_Frame;
    const uint16_t num_pts_perline = header.Num_Pts_Per_Line;
    const uint16_t packet_size = header.Packet_size;
    const int trig_factor = static_cast<int>(2 * (1 + 1.0 / num_trig_per_mtrig));

    const size_t data_size = num_pts_perline * trig_num * 12 * packet_size * trig_factor;
    std::vector<int16_t> raw_data(data_size);

    file_.read(reinterpret_cast<char*>(raw_data.data()), data_size * sizeof(int16_t));
    if (file_.gcount() != data_size * sizeof(int16_t)) {
        return false;
    }

    // Reshape and convert to complex
    data.resize(12 * num_pts_perline * trig_num * trig_factor / 2);

    for (size_t i = 0; i < data.size(); ++i) {
        data[i] = std::complex<float>(
            static_cast<float>(raw_data[2 * i]),
            static_cast<float>(raw_data[2 * i + 1])
        );
    }

    return true;
}

bool RawReader::readHMMode(BMFMDataHeader& header, std::vector<std::complex<float>>& data) {
    const uint16_t num_trig_per_mtrig = header.num_trig_per_mtrig;
    const uint16_t trig_num = header.Num_Trig_Per_Frame;
    const uint16_t num_pts_perline = header.Num_Pts_Per_Line;
    const uint16_t packet_size = header.Packet_size;
    const int trig_factor = static_cast<int>(2 * (1 + 1.0 / num_trig_per_mtrig));

    const size_t data_size = num_pts_perline * trig_num * 12 * packet_size * trig_factor;
    std::vector<int16_t> raw_data(data_size);

    file_.read(reinterpret_cast<char*>(raw_data.data()), data_size * sizeof(int16_t));
    if (file_.gcount() != data_size * sizeof(int16_t)) {
        return false;
    }

    // Simplified processing
    data.resize(12 * num_pts_perline * trig_num * trig_factor * packet_size / 2);
    for (size_t i = 0; i < data.size(); ++i) {
        data[i] = std::complex<float>(
            static_cast<float>(raw_data[2 * i]),
            static_cast<float>(raw_data[2 * i + 1])
        );
    }

    return true;
}

bool RawReader::readSMode(BMFMDataHeader& header, std::vector<std::complex<float>>& data) {
    const uint16_t num_pts_perline = header.Num_Pts_Per_Line;
    const uint16_t packet_size = header.Packet_size;
    const size_t trig_len = num_pts_perline * 12 * 2 + 4;
    const size_t nn = trig_len * packet_size;

    std::vector<int16_t> raw_data(nn);
    file_.read(reinterpret_cast<char*>(raw_data.data()), nn * sizeof(int16_t));
    if (file_.gcount() != nn * sizeof(int16_t)) {
        return false;
    }

    // Simplified processing
    data.resize(12 * num_pts_perline * packet_size);
    for (size_t i = 0; i < data.size(); ++i) {
        data[i] = std::complex<float>(
            static_cast<float>(raw_data[2 * i]),
            static_cast<float>(raw_data[2 * i + 1])
        );
    }

    return true;
}

bool RawReader::readAllFrames(std::vector<BMFMDataHeader>& headers,
    std::vector<std::vector<std::complex<float>>>& allData) {
    if (!file_.is_open()) {
        std::cerr << "File is not open." << std::endl;
        return false;
    }

    size_t frame_count = 0;
    std::vector<std::vector<std::complex<float>>> iq; // 存储最终的帧数据
    std::vector<std::complex<float>> temp(nx_ * nz_ * 2, { 0, 0 }); // 临时存储当前帧的数据

    while (true) {
        BMFMDataHeader header;
        std::vector<std::complex<float>> frame_data;

        if (!readFrame(header, frame_data)) {
            if (file_.eof()) break; // 文件结束
            continue; // 跳过错误帧
        }

        if (header.bf_mode == 19) { // H-mode处理
            const uint8_t start_line = header.Parallel_bmfm_start_line;
            const uint8_t interval_line = header.Scan_interval_lines;

            // 初始化临时存储
            if (start_line == 1) {
                temp.assign(nx_ * nz_ * 2, { 0, 0 }); // 重置 temp 为全零
            }
            // 合并多通道数据并填充到正确位置
            //std::cout <<"frame_data.size = :" << frame_data.size() << std::endl;
            int xishu = 0;
            for (size_t x = start_line - 1; x < nx_; x += interval_line) {
                
                for (size_t z = 0; z < nz_ * 2; ++z) {
                    std::complex<float> sum = { 0, 0 }; // 初始化合并结果
                    //std::cout << "z = " << z << ", Channels: ";
                   
                    for (int ch : pick_lines_) {
                        size_t index = z * 12+ch+xishu* nz_ * 2*12; // 计算 frame_data 中的索引
                        //std::cout << "index = " << index << std::endl;
                        
                        if (index < frame_data.size()) {
                            sum += frame_data[index]; // 合并多通道数据
                        }
                    }
                    //std::cout << " -> Sum: " << sum << std::endl;
                    temp[x * nz_ * 2 + z] = sum; // 直接填充到 temp
                    
                }
                xishu++;
            }

            // 当完成一帧采集时
            if (start_line == interval_line) {
              

                iq.push_back(temp); // 将当前帧数据添加到最终结果中
            }

            // 完成一帧采集
            if (!frame_data.empty()) {
                headers.push_back(header);
                frame_count++;
            }
        }
    }

    // 将最终的帧数据存储到 allData 中
    allData = iq;

    return !allData.empty();
}
bool RawReader::readHMode(BMFMDataHeader& header, std::vector<std::complex<float>>& data) {
    const uint16_t num_pts_perline = header.Num_Pts_Per_Line;
    const uint16_t trig_num = header.Num_Trig_Per_Frame;
    const uint16_t num_channels = 12;

    // 原始数据尺寸应为4倍通道数（上下各两个通道）
    const size_t raw_data_size = num_pts_perline * trig_num * num_channels * 4;
    std::vector<int16_t> raw_data(raw_data_size);
    file_.read(reinterpret_cast<char*>(raw_data.data()), raw_data_size * sizeof(int16_t));

    // 重新组织数据维度（对齐Python的reshape逻辑）
    data.resize(num_pts_perline * trig_num * num_channels * 2); // 上下通道合并后尺寸

    for (size_t t = 0; t < trig_num; ++t) {
        for (size_t p = 0; p < num_pts_perline; ++p) {
            for (size_t c = 0; c < num_channels; ++c) {
                // 关键修正点：按触发次数*4划分通道块
                const size_t base_idx = t * 4 * num_pts_perline * num_channels + p * num_channels + c;

                // 上通道（0和2）
                size_t up_idx = (t * 2) * num_pts_perline * num_channels + p * num_channels + c;
                data[up_idx] = std::complex<float>(
                    raw_data[base_idx],
                    raw_data[base_idx + 2 * num_pts_perline * num_channels]
                );

                // 下通道（1和3）
                size_t down_idx = (t * 2 + 1) * num_pts_perline * num_channels + p * num_channels + c;
                data[down_idx] = std::complex<float>(
                    raw_data[base_idx + num_pts_perline * num_channels],
                    raw_data[base_idx + 3 * num_pts_perline * num_channels]
                );
            }
        }
    }
    /*std::cout << "C++ HMode Data (Points 5000 to 5100):" << std::endl;
    for (size_t i = 278684; i < 278784 && i < data.size(); ++i) {
        std::cout << "[" << i << "] = " << data[i].real() << " + " << data[i].imag() << "j" << std::endl;
    }*/
    return true;
}

