CXX=g++
CC=gcc
CXXFLAGS=-std=c++98 -Werror -Wpedantic -Wall -Wextra
CFLAGS=-std=c99 -Werror -Wpedantic -Wall -Wextra -g

all: tri_tiling

tri_tiling: tri_tiling.cpp
	${CXX} tri_tiling.cpp -o tri_tiling ${CXXFLAGS}

tothemax: tothemax.c
	${CC} tothemax.c -o tothemax ${CFLAGS}

test_tri_tiling:
	echo -e '0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26\n27\n28\n29\n30\n-1' | ./tri_tiling

test_tothemax: tothemax
	./tothemax < tothemaxtestinput.txt
