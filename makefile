FILE=src/main.cpp

build:
	g++-10 $(FILE) -O3 -pedantic -lfmt

debug:
	g++-10 $(FILE) -g -gstabs -O3 -pedantic -lfmt
