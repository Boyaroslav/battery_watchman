install:
	gcc -o battnotif `pkg-config --cflags --libs gio-2.0` main.c  