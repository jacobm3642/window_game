// -- Written in C -- //
#include "shapes.h"
#include<stdio.h>
#include<stdlib.h>
#include<X11/X.h>
#include<X11/Xlib.h>
#include<GL/gl.h>
#include<GL/glx.h>
#include<GL/glu.h>

Display                 *dpy;
Window                  root;
GLint                   att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
XVisualInfo             *vi;
Colormap                cmap;
XSetWindowAttributes    swa;
Window                  win;
GLXContext              glc;
XWindowAttributes       gwa;
XEvent                  xev;

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

void DrawAQuad(Square *square) {
 	glClearColor(1.0, 1.0, 1.0, 1.0);
 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    if (square->norm == 0){
        convert_square_values(square);
        printf("%f\n", square->lower_left.x);
    }


 	glMatrixMode(GL_PROJECTION);
 	glLoadIdentity();
 	glOrtho(-1., 1., -1., 1., 1., 20.);

 	glMatrixMode(GL_MODELVIEW);
 	glLoadIdentity();
 	gluLookAt(0., 0., 10., 0., 0., 0., 0., 1., 0.);
    
    

 	glBegin(GL_QUADS);
 	 	glColor3f(square->color.r, square->color.g, square->color.b);
        glVertex3f(square->top_left.x, square->top_left.y, 0.);
 	 	glVertex3f( square->top_right.x, square->top_right.y, 0.);
 	 	glVertex3f( square->lower_right.x,  square->lower_right.y, 0.);
 	 	glVertex3f(square->lower_left.x, square->lower_left.y, 0.);
 	glEnd();
} 
	
int main(int argc, char *argv[]) {


 	// this creates a connection to a display server
 	dpy = XOpenDisplay(NULL);
	
 	// this checks if the server has made a connection
 	if(dpy == NULL) {
 		printf("\n\tcannot connect to X server\n\n");
 	       exit(0);
 	}
	
 	// this gets a root window for the display pass into it
 	root = DefaultRootWindow(dpy);

 	// seems to create the visual that i want 
 	vi = glXChooseVisual(dpy, 0, att);

 	// checks if the visual worked and if it did makes a hex output
 	if(vi == NULL) {
		printf("\n\tno appropriate visual found\n\n");
 	       exit(0);
 	} 
 	else {
		printf("\n\tvisual %p selected\n", (void *)vi->visualid); /* %p creates hexadecimal output like in glxinfo */
 	}

	// creates a colormap but doesint allocte any colors
 	cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);

 	swa.colormap = cmap;
 	swa.event_mask = ExposureMask | KeyPressMask;
	
 	win = XCreateWindow(dpy, root, 0, 0, 600, 600, 0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa);

 	XMapWindow(dpy, win);
 	XStoreName(dpy, win, "COOL THING");
 
 	glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
 	glXMakeCurrent(dpy, win, glc);
 
	glEnable(GL_DEPTH_TEST); 

    // this should be done by a func
    int t_l[2] = {-500, -500};
    int t_r[2] = {500, -500};
    int b_l[2] = {-500, 500};
    int b_r[2] = {500, 500};
    int color[3] = {250, 0, 0};
 
    Square *test = malloc(sizeof(Square));    
    *test = make_square(t_l, t_r, b_l, b_r, color);
    // end of part that needs to be cleaned

	while(1) {
 		XNextEvent(dpy, &xev);
        if(xev.type == Expose) {
        	XGetWindowAttributes(dpy, win, &gwa);
            glViewport(0, 0, gwa.width, gwa.height);
        	DrawAQuad(test);
            glXSwapBuffers(dpy, win);
        } else if(xev.type == KeyPress) {
			KeySym key = XLookupKeysym(&xev.xkey, 0);
	
        	switch (key) {
                case XK_Escape:
                    free(test);
                    glXMakeCurrent(dpy, None, NULL);
        	        glXDestroyContext(dpy, glc);
        	        XDestroyWindow(dpy, win);
        	        XCloseDisplay(dpy);
        	        exit(0);
                    break;
                case XK_Up:
                    printf("you pressed up\n");
                    break;
        	}
        }
    } /* this closes while(1) { */
} /* this is the } which closes int main(int argc, char *argv[]) { */
