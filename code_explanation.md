# Packet Capture and Protocol Analysis

이 프로젝트는 Linux 환경에서 패킷을 캡처하고, 저장된 `.pcap` 파일을 분석하여 패킷의 프로토콜(TCP, UDP, ICMP 등)을 분류하는 C++ 프로그램입니다. 프로그램은 `packet_capture`와 `analyze_packets` 두 가지 주요 기능으로 구성됩니다.

---

## **구성 파일**

### **1. `PacketCapture.h`**
- `PacketCapture` 클래스 정의.
- 네트워크 인터페이스에서 패킷을 캡처하고, 데이터를 `.pcap` 파일로 저장하는 기능 제공.
- 주요 메서드:
  - `startCapture()`: 패킷 캡처 시작.
  - `stopCapture()`: 패킷 캡처 중지.
  - `ensureOutputDirectoryExists(const std::string&)`: 캡처된 데이터를 저장할 디렉토리 확인 및 생성.

### **2. `PacketCapture.cpp`**
- `PacketCapture` 클래스 구현.
- POSIX API(`stat`, `mkdir`)를 사용하여 디렉토리 생성.
- `pcap` 라이브러리를 통해 패킷 데이터를 캡처하여 `.pcap` 파일로 저장.
- **비동기 작업**: `std::thread`를 사용하여 캡처 작업 수행.

### **3. `main.cpp`**
- `PacketCapture` 클래스를 기반으로 프로그램의 전체 흐름을 제어.
- 사용자 입력을 받아 패킷 캡처를 시작하고, 캡처된 데이터를 지정된 디렉토리에 저장.
- 실행 중 사용자 입력(`q` 또는 Ctrl+C)을 통해 캡처 종료.

### **4. `analyze_packets.cpp`**
- `.pcap` 파일을 읽고, 각 패킷의 프로토콜을 분석하여 결과 출력.
- 분석된 프로토콜의 이름과 검출 횟수를 출력.
- `std::unordered_map`를 사용하여 프로토콜별 카운트를 관리.
- 중복된 프로토콜은 출력하지 않으며, 카운트만 갱신.

---

## **프로그램 실행 방법**

### **1. `packet_capture` 프로그램 실행**
1. 네트워크 인터페이스를 확인:
   ```bash
   ip link show
