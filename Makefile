.PHONY: clean native riscv arm

TARGET = bmp_viewer

.DEFAULT_GOAL = native

native:
	gcc -Wextra -pedantic src/$(TARGET).c -o $(TARGET)

clean:
	rm -f src/*.o $(TARGET) $(TARGET)_riscv $(TARGET)_arm

riscv:
	riscv64-linux-gnu-gcc -Wextra -pedantic -static src/$(TARGET).c -o $(TARGET)_riscv

arm: 
	arm-linux-gnueabi-gcc -Wextra -pedantic -static src/$(TARGET).c -o $(TARGET)_arm
