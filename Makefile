CC=g++

all: src/main.cpp
	$(CC) -o src/bomb-partty -lncurses src/main.cpp

install: src/main.cpp src/bomb-partty
	mkdir /usr/local/bin/bomb-partty-bin/
	cp dictionary.txt /usr/local/bin/bomb-partty-bin/
	cp set.txt /usr/local/bin/bomb-partty-bin/
	cp src/bomb-partty /usr/local/bin/

uninstall:
	rm -rf -r /usr/local/bin/bomb-partty-bin/
	rm /usr/local/bin/bomb-partty

reinstall: src/main.cpp src/bomb-partty
	rm -rf -r /usr/local/bin/bomb-partty-bin/
	rm /usr/local/bin/bomb-partty
	mkdir /usr/local/bin/bomb-partty-bin/
	cp dictionary.txt /usr/local/bin/bomb-partty-bin/
	cp set.txt /usr/local/bin/bomb-partty-bin/
	cp src/bomb-partty /usr/local/bin/
