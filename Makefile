.PHONY: all clean

TARGET = bmp_viewer

all : $(TARGET)

clean:
	rm -f src/*.o $(TARGET) $(TARGET)_riscv

$(TARGET).o:
	gcc -c src/$(TARGET).c -o src/$(TARGET).o

$(TARGET): bmp_viewer.o
	gcc src/$(TARGET).o -o $(TARGET)

riscv:
	riscv64-linux-gnu-gcc -static src/$(TARGET).c -o $(TARGET)_riscv