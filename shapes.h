typedef struct Vec2 {
    float x;
    float y;
} Vec2;

typedef struct Color {
    float r;
    float g;
    float b;
} Color;

typedef struct Square {
    // all values will be converted from int range to float
    // Vec2 will be stored in a range of -1000 to 1000
    // and converted at draw to -1 to 1
    // color will be in range 0 to 255 
    // and also converted at draw to 0 to 1
    Vec2 top_left; 
    Vec2 top_right;
    Vec2 lower_left;
    Vec2 lower_right;
    Color color;
    int norm;
} Square;
