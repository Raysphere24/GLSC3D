#include<stdlib.h>
#include<stdio.h>
#include "glsc3d.h"

#define INTV              (1)
#define WINDOW_SIZE_X     (700)
#define WINDOW_SIZE_Y     (700)

int main()
{
    g_init("GRAPH", WINDOW_SIZE_X, WINDOW_SIZE_Y);
    
    g_def_scale_3D(0,-2,2,-2,2,-2,2,0,0,WINDOW_SIZE_X,WINDOW_SIZE_Y,1,1,1,1);
    
    int i_time;
    for(i_time=0;;i_time++)
    {
        g_init_light_core(0,cos(0.01*i_time),sin(0.01*i_time),sin(0.01*i_time)*cos(0.01*i_time),1);
        g_cls();
        
        g_sel_scale_3D(0);
        g_area_color_3D(1,0,0,1);
        g_box_3D(0,0,0,1,1,1, G_YES,G_NO);
        
        g_finish();
        g_sleep(0.05);
    }
    return 0;
}
