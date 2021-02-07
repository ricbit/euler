PROB=p418
g++ -std=c++14  -I/home/ricbit/src/scipoptsuite-7.0.2/build/ -I/home/ricbit/src/scipoptsuite-7.0.2/scip/src/ -I/home/ricbit/work/easyscip/easyscip/ $PROB.cc -o $PROB  -L/home/ricbit/src/scipoptsuite-7.0.2/build/lib/ -lscip  -m64 -O3 -mtune=native -fomit-frame-pointer -lsoplex -lm -O3 -Wall -lgmp -lz -lreadline -lzimpl -g
