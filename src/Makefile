GCC=g++ -O3 -g -Wall -Werror -Wextra -pedantic -std=c++17
#LD_FLAGS= -lpthread
LD_FLAGS=

all: lss

rebuild: clean all

lss: lss.cpp lss.h
	$(GCC) $< -o $@ $(LD_FLAGS)

#	$(GCC) $< *.o -o $@ $(LD_FLAGS)

#	$(GCC) $< -o $@ $(LD_FLAGS)

clean:
	rm -rf *.o laa vgcore*
