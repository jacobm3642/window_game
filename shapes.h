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
    char norm;
} Square;

typedef struct Polygon {
    int size;
    Color color;
    char norm;
    Vec2 *Vertex[];
} Polygon;

Polygon make_polygon(Vec2 *points[], int size, int color[3]);

Square make_square(int top_left[2], int top_right[2], int lower_left[2], int lower_right[2], int color[3]);

void convert_Vec2(Vec2 *vec);

void convert_Color(Color *color);

void convert_square_values(Square *square);
