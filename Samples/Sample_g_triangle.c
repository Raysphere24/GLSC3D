#include<stdio.h>

#include "glsc3d_3.h"

#define WINDOW_SIZE_X     (1000)
#define WINDOW_SIZE_Y     (500)

int main()
{
	g_init("Sample_g_triangle.c", WINDOW_SIZE_X, WINDOW_SIZE_Y);

	g_def_scale_2D(0, -2, 2, -2, 2, 0, 0, WINDOW_SIZE_X / 2, WINDOW_SIZE_Y);
	g_def_scale_3D(1, -2, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 2, WINDOW_SIZE_X / 2, 0, WINDOW_SIZE_X / 2, WINDOW_SIZE_Y);

	for (int i_time = 0;; i_time++)
	{
		g_cls();

		g_sel_scale(0);
		g_triangle_2D(-0.5, -1.5, -1.5, 1.5, -1.5, -1.5, G_YES, G_NO);
		g_area_color(1, 0, 0, 1);
		g_triangle_2D(1, -1.5, 0, -1.5, 1, 1.5, G_NO, G_YES);

		g_sel_scale(1);
		g_triangle_3D(0, -2.5, 0, 2, 0.5, 2, 0, 2.5, 2, G_YES, G_NO);
		g_triangle_3D_core(2, -0.5, 0, -2.5, 0, 0, 2, -0.5, 2, 0, G_NO, G_YES);

		g_finish();
	}
	return 0;
}
