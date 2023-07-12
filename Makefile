CC = g++
Header_Files = src/include/Xeebo.h src/include/Game_Object.h src/include/Event.h
Source_Files = src/main.cpp src/Xeebo.cpp src/Game_Object.cpp
Object_Files = object_files/Xeebo.o object_files/Game_Object.o
Main_Executable = main.exe
Debug = -ggdb -g3 -O0

$(Object_Files): $(Source_Files) $(Header_Files)
	$(CC) -c src/Xeebo.cpp -o object_files/Xeebo.o
	$(CC) -c src/Game_Object.cpp -o object_files/Game_Object.o

$(Main_Executable): $(Object_Files)
	$(CC) src/main.cpp $(Object_Files) -o $(Main_Executable) `sdl2-config --cflags --libs`

debug: $(Source_Files) $(Header_Files)
	$(CC) -c src/Xeebo.cpp $(Debug) -o object_files/Xeebo.o
	$(CC) -c src/Game_Object.cpp $(Debug) -o object_files/Game_Object.o
	$(CC) src/main.cpp $(Object_Files) $(Debug) -o debug_$(Main_Executable) `sdl2-config --cflags --libs` -mconsole
