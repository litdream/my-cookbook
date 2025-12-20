#gcc main.c -I/usr/include/SDL3 $(pkg-config --cflags --libs sdl3)

gcc main.c -I/usr/include/SDL2 $(pkg-config --cflags --libs sdl2)

