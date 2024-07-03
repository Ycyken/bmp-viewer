.PHONY: all clean

TARGET = bmp_viewer

all : $(TARGET)

clean:
	rm *.o $(TARGET)

bmp_viewer.o: bmp_viewer.c
	gcc -c bmp_viewer.c

$(TARGET): bmp_viewer.o
	gcc bmp_viewer.o -o $(TARGET)