GCC=g++ -O3 -g -Wall -Werror -Wextra -pedantic -std=c++17
#LD_FLAGS= -lpthread
LD_FLAGS=

all: lss

rebuild: clean all

lss: src/lss.cpp src/lss.h
	$(GCC) $< -o $@ $(LD_FLAGS)

#	$(GCC) $< *.o -o $@ $(LD_FLAGS)

#	$(GCC) $< -o $@ $(LD_FLAGS)

clean:
	rm -rf src/*.o lss src/vgcore*
