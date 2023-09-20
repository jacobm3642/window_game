current_dir=$(pwd)

# sudo ldconfig $current_dir

gcc -shared -o libshapes.so shapes.c 
gcc -o main main.c -lX11 -lGL -lGLU -L$current_dir -lshapes

./main
