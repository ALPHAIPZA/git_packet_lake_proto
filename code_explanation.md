# Code Explanation

## 1. Overview

이 프로젝트는 `.pcap` 파일을 입력으로 받아, 파일 이름에서 추출한 날짜/시간(`YYYY_MM_DD_HH_MM`)을 디렉토리 이름으로 사용하여 응용 계층 프로토콜별로 데이터를 분류하는 프로그램

### 주요 컴포넌트
- **`main.cpp`**: 프로그램의 진입점. 입력 `.pcap` 파일 경로를 받아 출력 디렉토리를 생성한 후, `ProtocolSorter`를 호출하여 프로토콜 분류를 수행
- **`ProtocolSorter`**: 입력받은 `.pcap` 파일 데이터를 응용 계층 프로토콜별로 분류하고, 각각의 `.pcap` 파일로 저장

---

## 2. How It Works

### 1. 입력 및 출력 처리
- **입력**: 사용자로부터 `.pcap` 파일 경로를 명령줄 인수로 전달
- **출력 디렉토리**: 입력 파일 이름(`YYYY_MM_DD_HH_MM.pcap`)에서 날짜/시간 정보를 추출해 동일한 이름의 디렉토리를 생성

### 2. 프로토콜 분류
- 입력 `.pcap` 데이터를 HTTP, FTP, DNS, SMTP, IMAP, SSH, TLS 등으로 분류하고 각 프로토콜별 `.pcap` 파일로 저장

---

## 3. Main Components

### `main.cpp`
1. **역할**:
   - `.pcap` 파일 경로를 명령줄 인수로 입력
   - 파일명에서 날짜/시간 정보를 추출하여 출력 디렉토리를 생성
   - `ProtocolSorter`를 호출하여 프로토콜 분류를 수행

2. **구조**:
   - 명령줄 인수 검증 및 오류 처리
   - 출력 디렉토리를 생성하는 유틸리티 함수(`createOutputDirectory`) 포함

### `ProtocolSorter`
1. **역할**:
   - `.pcap` 파일과 출력 디렉토리를 입력받아 패킷 데이터를 HTTP, FTP, DNS 등 응용 계층 프로토콜별로 분류
   - 분류된 데이터를 각각의 `.pcap` 파일로 저장

2. **구조**:
   - 프로토콜별로 분류 로직 구현
   - 결과 파일은 출력 디렉토리 내부에 저장

---

## 4. Example Execution

### 실행 명령어
```bash
./bin/protocol_sorter 2024_11_25_15_30.pcap
```

## 5. Future Improvements
### Class 예정
Analyzer 인터페이스
Suricata class
Yara class
Logger Class : Packet에 Rule을 적용한 후의 탐지율 확인
