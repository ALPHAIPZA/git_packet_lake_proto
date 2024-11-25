#include "ProtocolSorter.h"
#include <iostream>
#include <string>
#include <cstring>      // strerror()
#include <stdexcept>
#include <sys/stat.h>   // mkdir() for POSIX
#include <sys/types.h>  // mode_t

/**
 * @brief 입력 파일 이름에서 날짜/시간 정보를 추출해 출력 디렉토리를 생성
 * @param inputFile 입력 파일 경로
 * @return 생성된 출력 디렉토리 경로
 */
std::string createOutputDirectory(const std::string& inputFile) {
    // 파일 이름에서 날짜/시간 추출 (예: YYYY_MM_DD_HH_MM.pcap)
    auto lastSlashPos = inputFile.find_last_of('/');
    std::string fileName = (lastSlashPos != std::string::npos) ? inputFile.substr(lastSlashPos + 1) : inputFile;

    // 확장자 제거
    auto dotPos = fileName.find_last_of('.');
    std::string baseName = (dotPos != std::string::npos) ? fileName.substr(0, dotPos) : fileName;

    // YYYY_MM_DD_HH_MM 형식 확인
    if (baseName.empty() || baseName.find('_') == std::string::npos) {
        throw std::invalid_argument("파일 이름에서 날짜/시간 정보를 찾을 수 없습니다: " + fileName);
    }

    // 출력 디렉토리 생성
    if (mkdir(baseName.c_str(), 0777) && errno != EEXIST) {
        throw std::runtime_error("출력 디렉토리를 생성할 수 없습니다: " + baseName + " (" + strerror(errno) + ")");
    }

    return baseName;
}

int main(int argc, char* argv[]) {
    try {
        // 명령줄 인수 확인
        if (argc != 2) {
            std::cerr << "사용법: " << argv[0] << " <input_pcap>" << std::endl;
            return 1;
        }

        // 입력 파일 경로 설정
        const std::string inputPcap = argv[1];

        // 출력 디렉토리 이름 생성
        const std::string outputDir = createOutputDirectory(inputPcap);

        // ProtocolSorter 인스턴스 생성 및 실행
        ProtocolSorter sorter;
        sorter.sortPcapByProtocol(inputPcap, outputDir);

        std::cout << "프로토콜별 패킷이 성공적으로 분류되었습니다." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "오류: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
