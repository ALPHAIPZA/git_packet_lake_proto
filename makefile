# 컴파일러 설정
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pthread

# 라이브러리 설정
LDFLAGS = -lpcap

# 실행 파일 이름
CAPTURE_TARGET = packet_capture
ANALYZE_TARGET = analyze_packets

# 소스 파일 및 오브젝트 파일
CAPTURE_SRC = main.cpp PacketCapture.cpp
CAPTURE_OBJ = $(CAPTURE_SRC:.cpp=.o)

ANALYZE_SRC = analyze_packets.cpp
ANALYZE_OBJ = $(ANALYZE_SRC:.cpp=.o)

# 기본 타겟
all: $(CAPTURE_TARGET) $(ANALYZE_TARGET)

# 패킷 캡처 실행 파일 빌드
$(CAPTURE_TARGET): $(CAPTURE_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# 프로토콜 분석 실행 파일 빌드
$(ANALYZE_TARGET): $(ANALYZE_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# 개별 소스 파일 컴파일
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# clean: 빌드 파일 삭제
clean:
	rm -f $(CAPTURE_OBJ) $(ANALYZE_OBJ) $(CAPTURE_TARGET) $(ANALYZE_TARGET)

# 디버그 타겟: 디버깅 플래그 활성화
debug: CXXFLAGS += -g
debug: clean all
