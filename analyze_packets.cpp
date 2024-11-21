/**
 * @file analyze_packets.cpp
 * @brief pcap 파일에서 캡처된 패킷의 프로토콜을 분석하는 프로그램.
 *
 * 이 프로그램은 pcap 파일을 읽어서 각 패킷의 프로토콜(TCP, UDP, ICMP 등)을 분석하고 출력하며,
 * 중복된 프로토콜은 출력되지 않고 검출 횟수만 카운트됩니다.
 */

#include <pcap.h>
#include <iostream>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netinet/ip_icmp.h>
#include <unordered_map>
#include <string>

// 프로토콜별 카운트를 저장하는 전역 맵
std::unordered_map<std::string, int> protocolCount;

/**
 * @brief 패킷 데이터를 기반으로 프로토콜을 분석하여 카운트를 증가시킵니다.
 * 
 * @param packet pcap 파일에서 읽은 패킷 데이터.
 */
void analyzeProtocol(const u_char* packet) {
    const struct ip* ipHeader = reinterpret_cast<const struct ip*>(packet);

    std::string protocolName;
    switch (ipHeader->ip_p) {
        case IPPROTO_TCP:
            protocolName = "TCP";
            break;
        case IPPROTO_UDP:
            protocolName = "UDP";
            break;
        case IPPROTO_ICMP:
            protocolName = "ICMP";
            break;
        default:
            protocolName = "OTHER";
            break;
    }

    // 프로토콜 카운트를 증가
    protocolCount[protocolName]++;
}

/**
 * @brief 현재까지 카운트된 프로토콜 정보를 출력합니다.
 */
void printProtocolCounts() {
    std::cout << "\nProtocol Counts:\n";
    for (const auto& [protocol, count] : protocolCount) {
        std::cout << protocol << " : " << count << "\n";
    }
}

/**
 * @brief 메인 함수로, pcap 파일을 열고 패킷을 순차적으로 읽어 프로토콜을 분석합니다.
 * 
 * @param argc 명령줄 인수의 개수.
 * @param argv 명령줄 인수 배열. argv[1]은 분석할 pcap 파일 경로입니다.
 * @return 프로그램 실행 결과. 성공 시 0, 실패 시 1을 반환합니다.
 */
int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <pcap_file>\n";
        return 1;
    }

    char errorBuffer[PCAP_ERRBUF_SIZE];
    pcap_t* pcap = pcap_open_offline(argv[1], errorBuffer); /**< pcap 파일을 오프라인 모드로 엽니다. */
    if (!pcap) {
        std::cerr << "Error opening file: " << errorBuffer << "\n";
        return 1;
    }

    struct pcap_pkthdr* header; /**< 패킷 헤더 정보. */
    const u_char* packet; /**< 패킷 데이터. */
    while (pcap_next_ex(pcap, &header, &packet) > 0) {
        analyzeProtocol(packet); /**< 패킷의 프로토콜을 분석하고 카운트를 증가합니다. */
    }

    pcap_close(pcap); /**< pcap 파일을 닫습니다. */

    printProtocolCounts(); /**< 분석된 프로토콜 카운트를 출력합니다. */
    return 0;
}
