#ifndef PROTOCOLSORTER_H
#define PROTOCOLSORTER_H

#include <string>
#include <stdexcept>
#include <filesystem>
#include <cstdlib>
#include <iostream>

/**
 * @class ProtocolSorter
 * @brief TShark를 사용하여 .pcap 파일을 응용 계층 프로토콜별로 분류하는 클래스
 *
 * TShark 명령줄 도구를 호출하여 .pcap 파일에서 HTTP, FTP 등 응용 계층 프로토콜별로
 * 패킷을 필터링하고 각각의 .pcap 파일로 저장합니다.
 */
class ProtocolSorter {
public:
    /**
     * @brief .pcap 파일을 TShark를 사용해 응용 계층 프로토콜별로 분류합니다.
     * @param inputPcap 입력 .pcap 파일 경로
     * @param outputDir 프로토콜별로 분류된 파일을 저장할 출력 디렉토리 경로
     * @exception std::runtime_error TShark 명령 실행 실패 시 예외 발생
     */
    void sortPcapByProtocol(const std::string& inputPcap, const std::string& outputDir);
};

#endif // PROTOCOLSORTER_H
