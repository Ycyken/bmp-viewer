# BMP Viewer
Application that prints the header of a bmp file in human readable format. Application only supports BMP versions 3, 4, 5.

## Getting started

### Requirements
- Make
- GCC
  
For RISC-V and ARM cross-compilation:
- gcc-arm-linux-gnueabi
- gcc-riscv64-linux-gnu

### Start
From the root directory of the repository:
```
make
```
Then you can pass a bmp image to app:
```
./bmp_viewer path/to/your_file
```
Cross compilation:
```
make riscv
./bmp_viewer_riscv path/to/your_file
```
or
```
make arm
./bmp_viewer_arm path/to/your_file
```
Clean the repository
```
make clean
```
