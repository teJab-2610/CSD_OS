CXX = g++
CXXFLAGS = -Wall -std=c++17

SRC1 = ../../src/drivers/keyboard.cpp ../../src/kernel/memory.cpp 
SRC2 = ./mem_vis.cpp
OUT1 = test
CXXFLAGS += -w
OUT2 = vis

clean:
	del memory.txt memory_out.txt memory.png

$(OUT1): $(SRC1)
	$(CXX) $(CXXFLAGS) $(SRC1) -o $(OUT1)

$(OUT2): $(SRC2)
	$(CXX) $(CXXFLAGS) $(SRC2) -o $(OUT2)

all: $(OUT1) $(OUT2)