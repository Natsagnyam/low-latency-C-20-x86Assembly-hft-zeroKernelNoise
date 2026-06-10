# Compiler settings
CXX = g++
CXXFLAGS = -std=c++20 -O3 -march=native -Wall -Wextra \
           -fno-exceptions -fno-rtti -fno-plt \
           -Iinclude

# Assembler settings
AS = nasm
ASFLAGS = -f elf64

# Targets
TARGET = hft_engine
SRCS = src/main.cpp src/producer.cpp
OBJS = src/main.o src/producer.o src/hot_path.o

# The default target
all: $(TARGET)

# Link everything together
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) -lpthread

# Compile C++ source (Generic rule for .cpp files)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Assemble the hot path
src/hot_path.o: src/hot_path.asm
	$(AS) $(ASFLAGS) src/hot_path.asm -o src/hot_path.o

clean:
	rm -f $(OBJS) $(TARGET)