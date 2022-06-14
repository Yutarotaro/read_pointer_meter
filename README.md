# read_pointer_meter
C++ project for Pointer Meter Reading

## Enviroment
linux, MacOS or docker 

## Dependency
OpenCV 3.4.10
prebuild docker image → https://hub.docker.com/r/boredfunuke/opencv

# Usage

```bash
git clone git@github.com:Yutarotaro/read_pointer_meter.git
cd read_pointer_meter
git submodule update --init --recursive
cd src
mkdir build && cd build
cmake ..
make -j4
./main
```

## If run on Docker

```bash
docker build -t pointer_meter .
docker run -it --net host -e DISPLAY=host.docker.internal:0 -v /path/to/src:/read_pointer_meter pointer_meter
``` 
