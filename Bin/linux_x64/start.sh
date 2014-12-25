#bin/sh

ulimit -n 1024000
ulimit -u 10240
ulimit -c unlimited
ulimit -d unlimited
ulimit -m unlimited
ulimit -s unlimited
ulimit -t unlimited
ulimit -v unlimited

LD_LIBRARY_PATH=./
export LD_LIBRARY_PATH
./DemoServer
