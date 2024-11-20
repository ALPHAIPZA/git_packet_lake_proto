#include "PacketCapture.h"
#include <iostream>
#include <csignal>
#include <atomic>

std::atomic<bool> isRunning(true);

/**
 * @brief SIGINT (Ctrl+C) 신호를 처리하여 프로그램을 종료합니다.
 * @param signal 수신된 신호 (예: SIGINT).
 */
void signalHandler(int signal) {
    if (signal == SIGINT) {
        isRunning.store(false);
    }
}

int main() {
    std::string interfaceName;
    std::cout << "네트워크 인터페이스 이름을 입력하세요 (예: eth0): ";
    std::cin >> interfaceName;

    PacketCapture packetCapture(interfaceName);

    try {
        // SIGINT 신호 처리기 설정
        std::signal(SIGINT, signalHandler);

        // 패킷 캡처 시작
        packetCapture.startCapture();

        // 사용자 입력 대기
        while (isRunning.load()) {
            char input;
            std::cout << "'q'를 입력하여 캡처를 중지하세요: ";
            std::cin >> input;

            if (input == 'q' || !isRunning.load()) {
                break;
            }
        }

        packetCapture.stopCapture();
    } catch (const std::exception& ex) {
        std::cerr << "오류 발생: " << ex.what() << "\n";
    }

    return 0;
}
