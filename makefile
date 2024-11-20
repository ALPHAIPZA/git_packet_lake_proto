# 컴파일러 설정
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pthread

# 라이브러리 링크 설정
LDFLAGS = -lpcap

# 타겟 이름
TARGET = packet_capture

# 소스 파일과 오브젝트 파일
SRC_FILES = main.cpp PacketCapture.cpp
OBJ_FILES = $(SRC_FILES:.cpp=.o)

# Doxygen 설정 파일
DOXYFILE = Doxyfile

# 기본 빌드 타겟
all: $(TARGET)

# 실행 파일 생성
$(TARGET): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# 개별 소스 파일 컴파일
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Doxygen 문서 생성
doc:
	@if [ -f $(DOXYFILE) ]; then \
		doxygen $(DOXYFILE); \
		echo "Doxygen 문서 생성 완료."; \
	else \
		echo "Doxygen 설정 파일(Doxyfile)을 찾을 수 없습니다."; \
	fi

# clean 타겟: 빌드 파일 삭제
clean:
	rm -f $(OBJ_FILES) $(TARGET)
	rm -rf html latex

# 디버그 빌드 타겟
debug: CXXFLAGS += -g
debug: clean $(TARGET)
