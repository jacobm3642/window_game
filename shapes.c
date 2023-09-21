#include "shapes.h"
#include <stdlib.h>

Square make_square(int top_left[2], int top_right[2], int lower_left[2], int lower_right[2], int color[3]){
    Square temp;
    temp.top_left.x = top_left[0];
    temp.top_left.y = top_left[1];
    temp.top_right.x = top_right[0];
    temp.top_right.y = top_right[1];  
    temp.lower_left.x = lower_left[0];
    temp.lower_left.y = lower_left[1];
    temp.lower_right.x = lower_right[0];
    temp.lower_right.y = lower_right[1];
    temp.color.r = color[0];
    temp.color.g = color[1];
    temp.color.b = color[2];
    temp.norm = 0;
    return temp;
}

void convert_Vec2(Vec2 *vec) {
        vec->x = vec->x/1000;
        vec->y = vec->y/1000;
}

void convert_Color(Color *color) {
    color->r = color->r/255;
    color->g = color->g/255;
    color->b = color->b/255;
}

void convert_square_values(Square *square) {
    convert_Vec2(&(square->top_left));
    convert_Vec2(&(square->top_right));
    convert_Vec2(&(square->lower_left));
    convert_Vec2(&(square->lower_right));
    convert_Color(&(square->color));
    square->norm = 1;
}

Polygon make_polygon(Vec2 *points[], int size, int color[3]) {
    Polygon *temp; 
    *temp = (Polygon*)malloc(sizeof(Polygon) + sizeof(Vec2)*size);
    
    if (temp != NULL) {
        // fuck off
    }

    temp->size = size;
    temp->color.r = color[0];
    temp->color.g = color[1];
    temp->color.b = color[2];
    temp->norm = 0;
    
    for (int i = 0; i < size; i++){
        temp->Vertex[i] = points[i];
    }
    
    return *temp;
}

void convert_polygon_values(Polygon *polygon) {
    convert_Color(&(polygon->color));
    for (int i = 0; i < polygon->size; i++ ) {
        convert_Vec2(&(polygon->Vertex[i]));
    }
    polygon->norm = 1;
}
