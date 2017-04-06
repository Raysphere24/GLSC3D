#include<stdio.h>
#include "glsc3d.h"

#define WINDOW_SIZE_X     (1000)
#define WINDOW_SIZE_Y     (500)

int main()
{
    g_init("GRAPH", WINDOW_SIZE_X, WINDOW_SIZE_Y);
    g_def_scale_2D(0,-2, 2, -2, 2,0, 0,WINDOW_SIZE_X/2, WINDOW_SIZE_Y);
    g_def_scale_3D(1,-1,1,-1,1,-1,1,WINDOW_SIZE_X/2, 0,WINDOW_SIZE_X/2, WINDOW_SIZE_Y,1, 1, 1,1);
    
    int i_time;
    for(i_time = 0;;i_time++)
    {
        int i;
        double x[10],y[10],z[10];
        for (i = 0; i < 10; i++)
        {
            x[i] = sin(2*M_PI*i/10);
            y[i] = cos(2*M_PI*i/10);
            z[i] = sin(2*M_PI*i/10)*cos(2*M_PI*i/10);
        }
        
        g_cls();
        
        g_sel_scale_2D(0);
        g_line_color(1, 0, 0, 1);
        g_polyline_2D(x,y,10);
        
        g_sel_scale_3D(1);
        g_line_color(1,0,0,1);
        g_polyline_3D(x,y,z,10);
        
        g_finish();
    }
    return 0;
}