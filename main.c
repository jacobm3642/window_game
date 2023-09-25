// -- Written in C -- //
#include "shapes.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>

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

int parce_line(char input[], Polygon *ploys[], int polyCount) {
    int buffer[255] = {0};
    int numbuff[8] = {0};
    int j = 0, k = 0;
    for (int i = 0; i < 255; i++){
        if (input[i] >= '0' && input[i] <= '9') {
            numbuff[j] = (input[i] - '0');
            j++;
        } else if (input[i] == ',') {
            int sum = 0;
            for (int l = 0; l < j; l++) {
                sum += (numbuff[l] * pow(10, (j-l-1)));
            }
            buffer[k] = sum;
            k++;
            j = 0;
        } else if (input[i] = '\0') {
			break;
		}
    }
	for (i = 0, i < k, i++) {
		// Polygon *temp = (Polygon *)make_polygon();
	}
    return 0; // Add a return statement if needed
}

void DrawAScene(char path[], Polygon *ploys[]){
    FILE *file;
    char c_char;
    int polyCount = 0;

    file = fopen(path, "r");

    if (file == NULL) {
        fprintf(stderr, "Could not open file for reading.\n");
        return; // Return early in case of an error
    }

    do {
        char linebuffer[255];
        int i = 0;

        do {
            c_char = fgetc(file);
            if (c_char != '\n' && c_char != EOF)
                linebuffer[i++] = c_char;
        } while (c_char != '\n' && c_char != EOF);

        linebuffer[i] = '\0'; // Add null-terminator to make it a valid C string

        if (polyCount < 40) {
            parse_line(linebuffer, ploys, polyCount);
            polyCount += 1;
        }
    } while (c_char != EOF);

    fclose(file);
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

	Polygon *scene[] = (Polygon*)malloc(sizeof(polygon) * 40);

	while(1){
    	while (XPending(dpy) > 0) {
    	    XNextEvent(dpy, &xev);

    	    if (xev.type == Expose) {
    	        XGetWindowAttributes(dpy, win, &gwa);
    	        glViewport(0, 0, gwa.width, gwa.height);
    	        DrawAQuad(test);
    	        glXSwapBuffers(dpy, win);
    	    } else if (xev.type == KeyPress) {
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
    	                test->top_left.y += 10.0/1000.0;
    	                test->top_right.y += 10.0/1000.0;
    	                test->lower_left.y += 10.0/1000.0;
    	                test->lower_right.y += 10.0/1000.0;
    	                break;
    	        }
    	    }
    	}
		usleep(5000);
		XClearWindow(dpy, win); 
    	DrawAScene("./assets/scene0.dat", scene);
    	glXSwapBuffers(dpy, win);
	}
} /* this is the } which closes int main(int argc, char *argv[]) { */
