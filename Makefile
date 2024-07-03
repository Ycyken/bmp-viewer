.PHONY: all clean

TARGET = bmp_viewer

all : $(TARGET)

clean:
	rm src/*.o $(TARGET)

bmp_viewer.o:
	gcc -c src/bmp_viewer.c -o src/bmp_viewer.o

$(TARGET): bmp_viewer.o
	gcc src/bmp_viewer.o -o $(TARGET)