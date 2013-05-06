rm blobSDLosx
rm *.o
g++ -c Shapes.c `pkg-config sdl --cflags`
g++ -c main.cpp `pkg-config sdl --cflags`
g++ main.o Shapes.o -o blobSDLosx `pkg-config sdl --libs` -framework opengl -lanttweakbar

# portability.. pkgconfig vs framework vs straight up library includes? look at quakespasm/ioquake3/yquake2 again.
