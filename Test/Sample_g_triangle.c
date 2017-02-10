#include<stdlib.h>
#include<stdio.h>

#include "glsc3d.h"


#define WINDOW_SIZE_X     (1000)
#define WINDOW_SIZE_Y     (500)

int main()
{
    g_init("GRAPH", WINDOW_SIZE_X, WINDOW_SIZE_Y);
	
	g_scr_color(1, 1, 1);
//	g_init_light(0, 0, 0, -1);
	
    g_def_scale_3D(0,-2, 2, -2, 2, -2, 2,WINDOW_SIZE_X/2, 0,WINDOW_SIZE_X/2, WINDOW_SIZE_Y,1, 1, 1,1);
    
    g_def_scale_2D(1,-2, 2, -2, 2,0, 0,WINDOW_SIZE_X/2, WINDOW_SIZE_Y);
    
    int i_time;
    for(i_time = 0;;i_time++)
    {
        g_cls();
        
        g_sel_scale_2D(1);
		
        g_line_color(1, 0, 0, 1);
        g_triangle_2D(-0.5,-1.5,-1.5,1.5,-1.5,-1.5,G_WIRE);
		
        g_area_color_2D(1, 0, 0,1);
        g_triangle_2D(1,-1.5,0,-1.5,1,1.5,G_FILL);
		
		g_area_color_2D(0, 1, 0, 1);
		g_triangle_2D(1, 1, 0, 0, 0, 1, G_FILL);
        
        g_sel_scale_3D(0);
		
        g_line_color(1, 0, 0, 1);
        g_triangle_3D(0,-2.5,0,0,0.5,2,0,2.5,2,G_WIRE);
		
        g_area_color_3D(1, 0, 0, 1);
        g_triangle_3D(2,-0.5,0,-2.5,0,0,2,-0.5,2,G_FILL);
        
        g_finish();
    }
    return 0;
}