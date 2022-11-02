# PROJECT 1.1
## Install cmake
`
sudo apt install cmake
`
## Install ninja (optional)
`
sudo apt install ninja-build
`
## Build and run with make 
```
git clone git@github.com:TVKain/Project-1.git
cd Project-1
mkdir build
cd build
cmake ..
make 
./main
```
## Build and run with ninja
```
git clone git@github.com:TVKain/Project-1.git
cd Project-1
mkdir build
cd build
cmake .. -G Ninja
ninja
./main
```

