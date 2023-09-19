# sudo ldconfig [path to pwd]

current_dir=$(pwd)

gcc -shared -o libshapes.so shapes.c 
gcc -o main main.c -lX11 -lGL -lGLU -L$current_dir -lshapes

./main
