all:
	gcc -o hello hello.c
	./hello
	objdump -D hello -M intel > hello.asm
	readelf -a hello >hello.elfinfo
