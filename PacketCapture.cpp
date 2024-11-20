#include "PacketCapture.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <cstring>
#include <stdexcept>
#include <thread>

PacketCapture::PacketCapture(const std::string& interfaceName)
    : interfaceName(interfaceName), handle(nullptr), dumper(nullptr), isCapturing(false) {}

PacketCapture::~PacketCapture() {
    stopCapture();
}

void PacketCapture::startCapture() {
    char errorBuffer[PCAP_ERRBUF_SIZE];
    handle = pcap_open_live(interfaceName.c_str(), BUFSIZ, 1, 1000, errorBuffer);

    if (!handle) {
        throw std::runtime_error("네트워크 인터페이스를 열 수 없습니다: " + std::string(errorBuffer));
    }

    ensureOutputDirectoryExists("./Origin_Captured_packets"); // 출력 디렉토리 확인 및 생성
    std::string fileName = generateFileName();
    dumper = pcap_dump_open(handle, fileName.c_str());
    if (!dumper) {
        pcap_close(handle);
        throw std::runtime_error("파일을 열 수 없습니다: " + std::string(pcap_geterr(handle)));
    }

    isCapturing.store(true);
    std::cout << "인터페이스 " << interfaceName << "에서 캡처 시작\n";
    std::cout << "캡처 중지하려면 'q'를 입력하거나 Ctrl+C를 누르세요. 파일: " << fileName << "\n";

    // 별도 스레드에서 캡처 실행
    std::thread captureThread(&PacketCapture::captureLoop, this);
    captureThread.detach();
}

void PacketCapture::stopCapture() {
    if (isCapturing.load()) {
        isCapturing.store(false);
        pcap_breakloop(handle);

        if (dumper) {
            pcap_dump_close(dumper);
        }
        if (handle) {
            pcap_close(handle);
        }

        std::cout << "캡처 중지됨.\n";
    }
}

void PacketCapture::captureLoop() {
    struct pcap_pkthdr* header;
    const u_char* data;

    while (isCapturing.load()) {
        int result = pcap_next_ex(handle, &header, &data);
        if (result == 1) { // 패킷 성공적으로 읽음
            pcap_dump((u_char*)dumper, header, data);
        } else if (result == -1) { // 오류 발생
            std::cerr << "패킷 캡처 오류: " << pcap_geterr(handle) << "\n";
            isCapturing.store(false);
        }
    }
}

std::string PacketCapture::generateFileName() const {
    std::time_t now = std::time(nullptr);
    std::tm* timeInfo = std::localtime(&now);

    std::ostringstream oss;
    oss << "./Origin_Captured_packets/"
        << std::put_time(timeInfo, "%Y_%m_%d_%H_%M") << ".pcap";

    return oss.str();
}

void PacketCapture::ensureOutputDirectoryExists(const std::string& path) const {
    struct stat info;

    if (stat(path.c_str(), &info) != 0) { // 디렉토리가 존재하지 않으면 생성
        if (mkdir(path.c_str(), 0755) != 0) {
            std::cerr << "디렉토리를 생성하는 중 오류 발생: " << strerror(errno) << "\n";
            throw std::runtime_error("디렉토리 생성 실패: " + path);
        } else {
            std::cout << "디렉토리 생성됨: " << path << "\n";
        }
    } else if (!(info.st_mode & S_IFDIR)) { // 경로가 디렉토리가 아닌 경우
        throw std::runtime_error("경로가 디렉토리가 아닙니다: " + path);
    }
}