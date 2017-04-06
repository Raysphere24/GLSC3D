#include<stdio.h>

#include "glsc3d.h"

#define WINDOW_SIZE_X     (1000)
#define WINDOW_SIZE_Y     (500)

int main()
{
	g_init("GRAPH", WINDOW_SIZE_X, WINDOW_SIZE_Y);

	g_def_scale_3D(0,
				   -2, 2, -2, 2, -2, 2,
				   0, 0, WINDOW_SIZE_X/2, WINDOW_SIZE_Y,
				   -0.1, 1.0, 0.1,
				   10);
	g_def_scale_3D(1,
				   -2, 2, -2, 2, -2, 2,
				   WINDOW_SIZE_X/2, 0, WINDOW_SIZE_X/2, WINDOW_SIZE_Y,
				   -0.1, 1.0, 0.1,
				   10);

	for (int i_time = 0;; i_time++)
	{
		g_cls();
		g_sel_scale_3D(0);
		g_line_color(1, 0, 0, 1);
		g_prism_3D(0, 0, 0, 1, -1, 1, 2, 4, M_PI / 4, 10, G_YES, G_NO);

		g_sel_scale_3D(1);
		g_area_color_3D(1, 0, 0, 1);
		g_prism_3D_core(0, 0, 0, 1, -1, 1, 2, 4, M_PI / 4, 10, 1, G_NO, G_YES);

		g_finish();
	}
	return 0;
}