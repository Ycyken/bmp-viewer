.PHONY: all clean

TARGET = bmp_viewer

all : $(TARGET)

clean:
	rm -f src/*.o $(TARGET) $(TARGET)_riscv $(TARGET)_arm

$(TARGET).o:
	gcc -c -Wextra -pedantic src/$(TARGET).c -o src/$(TARGET).o

$(TARGET): bmp_viewer.o
	gcc -Wextra -pedantic src/$(TARGET).o -o $(TARGET)

riscv:
	riscv64-linux-gnu-gcc -Wextra -pedantic -static src/$(TARGET).c -o $(TARGET)_riscv

arm: 
	arm-linux-gnueabi-gcc -Wextra -pedantic -static src/$(TARGET).c -o $(TARGET)_arm
