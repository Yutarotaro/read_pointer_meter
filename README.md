# read_pointer_meter
C++ project for Pointer Meter Reading

## Enviroment
linux, MacOS or docker 

## Dependency
OpenCV 3.4.10

# Usage

```bash
git clone git@github.com:Yutarotaro/read_pointer_meter.git
cd read_pointer_meter/src
mkdir build && cd build
cmake ..
make -j4
./main
```

## If run on Docker

```bash
docker build -t pointer_meter .
docker run -it --net host -e DISPLAY=host.docker.internal:0 -v /fullpath/to/read_pointer_meter:/read_pointer_meter pointer_meter
``` 
