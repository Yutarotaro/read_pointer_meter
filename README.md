# read_pointer_meter

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

なんか今$git submoduleがあんま動かなかったので、とりあえずしなくても大丈夫

## If run on Docker

```bash
docker build -t read_pointer_meter .
docker run -it --net host -e DISPLAY=host.docker.internal:0 -v /path/to/src:/read_pointer_meter 
```
