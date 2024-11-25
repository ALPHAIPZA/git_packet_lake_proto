#include "ProtocolSorter.h"
#include <vector>
#include <string>
#include <sys/stat.h>   // mkdir() 함수
#include <sys/types.h>  // mode_t
#include <cstdlib>      // std::system
#include <iostream>
#include <stdexcept>

void ProtocolSorter::sortPcapByProtocol(const std::string& inputPcap, const std::string& outputDir) {
    // 디렉토리 생성 (POSIX mkdir 사용)
    if (mkdir(outputDir.c_str(), 0777) && errno != EEXIST) {
        throw std::runtime_error("출력 디렉토리를 생성할 수 없습니다: " + outputDir);
    }

    // 분류할 프로토콜 리스트
    std::vector<std::string> protocols = {"http", "ftp", "dns", "smtp", "imap", "ssh", "tls"};

    for (const auto& protocol : protocols) {
        // TShark 명령 생성
        std::string outputPcap = outputDir + "/" + protocol + ".pcap";
        std::string command = "tshark -r " + inputPcap + " -Y \"" + protocol + "\" -w " + outputPcap;

        // 명령 실행
        int retCode = std::system(command.c_str());
        if (retCode != 0) {
            std::cerr << "TShark 명령 실행 실패: " << command << std::endl;
            throw std::runtime_error("TShark 명령 실행 중 오류 발생");
        }
    }

    std::cout << "응용 계층 프로토콜별 분류가 완료되었습니다: " << outputDir << std::endl;
}
