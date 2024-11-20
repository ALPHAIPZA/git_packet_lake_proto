#ifndef PACKET_CAPTURE_H
#define PACKET_CAPTURE_H

#include <pcap.h>
#include <string>
#include <atomic>

/**
 * @class PacketCapture
 * @brief 패킷 캡처를 처리하고, 캡처된 패킷을 파일에 저장하는 클래스.
 */
class PacketCapture {
public:
    /**
     * @brief PacketCapture 객체를 생성합니다.
     * @param interfaceName 패킷을 캡처할 네트워크 인터페이스 이름.
     */
    explicit PacketCapture(const std::string& interfaceName);

    /**
     * @brief 소멸자. 패킷 캡처를 중지하고 리소스를 해제합니다.
     */
    ~PacketCapture();

    /**
     * @brief 패킷 캡처를 시작합니다.
     */
    void startCapture();

    /**
     * @brief 패킷 캡처를 중지합니다.
     */
    void stopCapture();

private:
    std::string interfaceName; ///< 네트워크 인터페이스 이름.
    pcap_t* handle; ///< pcap 세션 핸들.
    pcap_dumper_t* dumper; ///< 패킷 데이터를 파일에 저장하는 핸들.
    std::atomic<bool> isCapturing; ///< 패킷 캡처 진행 여부.

    /**
     * @brief 패킷을 캡처하는 메인 루프입니다.
     */
    void captureLoop();

    /**
     * @brief 캡처된 패킷을 저장할 파일 이름을 생성합니다.
     * @return 타임스탬프 기반의 파일 이름 문자열.
     */
    std::string generateFileName() const;

    /**
     * @brief 출력 디렉토리가 존재하는지 확인하고, 없으면 생성합니다.
     * @param path 디렉토리 경로.
     */
    void ensureOutputDirectoryExists(const std::string& path) const;
};

#endif
