CC = gcc

demo:
	$(CC) src/main.c -o demo.exe `sdl2-config --cflags --libs`
