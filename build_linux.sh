rm blobSDLlinux
rm *.o

# Download and make ant tweak bar. Optionally install it, otherwise set its path here.
# You will need its libAntTweakBar.so.1 in your path to run.
ANTTWEAKBAR_PATH=/path/to/anttweakbar

echo "ANT $ANTTWEAKBAR_PATH/include/"
g++ -c Shapes.c main.cpp `pkg-config sdl --cflags` -I$ANTTWEAKBAR_PATH/include/
g++ -s main.o Shapes.o -o blobSDLlinux `pkg-config sdl glu --libs` -L$ANTTWEAKBAR_PATH/lib/ -lAntTweakBar
