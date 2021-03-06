#include "glsc3d_3.h"
#include <stdlib.h>

#define WIRE G_NO
#define FILL G_YES

int main(void) {
	const int Size = 240;
	const int CountX = 5, CountY = 2;

	g_enable_highdpi();
	g_set_antialiasing(2);
	g_init("GLSC3D", Size * CountX, Size * CountY);

	g_init_light(0, 1, -1, 1);
	g_init_light_core(1, 0, 1, 2, 0.5f);
//	g_init_light_core(2, 1, 1, 1, 0.25f);

	//g_scr_color(1, 1, 1);
	//g_scr_color(0.5, 0.5, 0.5);

	g_area_color(0.5, 0.75, 0.5, 1);
	//g_line_color(0, 0, 0, 1);

	//g_line_width(2);
	//g_line_type(1);

	double a = 4 * sqrt(2);

	int id = 0;
	for (int j = 0; j < CountY; j++)
	for (int i = 0; i < CountX; i++) {
//		g_def_scale_3D_core_legacy(id++, -1, 1, -1, 1, -1, 1, Size * i, Size * j, Size, Size, 0, 1, 1, 8, 0, 0, 1);
		g_def_scale_3D(id, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, Size * i, Size * j, Size, Size);
		g_vision(id++, 0, a, a, 0, 0, 1, 1);
	}

	for (double t = 0;; t += 1./128) {
		double c = cos(t), s = sin(t);

		g_cls();

		g_sel_scale(0);
		g_boundary();
		g_pyramid_3D_core (0, 0,-1, 0, 0, 1, 1, 2, t, 6, 0, WIRE, FILL);

		g_sel_scale(1);
		g_cone_3D_core    (0, 0,-1, 0, 0, 1, 1, 2, 100, 0, WIRE, FILL);

		g_sel_scale(2);
		g_prism_3D_core   (0, 0, 0, 0, 0, 1, 1, 2, t, 6, 0, WIRE, FILL);

		g_sel_scale(3);
		g_boundary();
		g_cylinder_3D_core(0, 0, 0, 0, 0, 1, 1, 2, t,24, 0, WIRE, FILL);

		g_sel_scale(4);
		g_ellipse_3D_core(0, 0, 0, 1.5, 1, 0.75, c, s, 0, 16, 0, WIRE, FILL);

		g_sel_scale(5);
		g_box_center_3D_core(0, 0, 0, 3, 2, 1.5, 0, WIRE, FILL);

		g_sel_scale(6);
		g_sphere_3D_core(0, 0, 0, 1, 16, 0, WIRE, FILL);

		g_sel_scale(7);
		g_rectangle_3D_core(0, 0, 0, c, s, 0, 3, 2, 0, 0, WIRE, FILL);

		g_sel_scale(8);
		g_text_size(24);
		g_arrow_3D_core(0, 0, 0, c, s, 0, 1, 0.25, 100, 0, WIRE, FILL);
		g_arrow_3D_core(0, 0, 0,-s, c, 0, 1, 0.25, 100, 0, WIRE, FILL);
		g_arrow_3D_core(0, 0, 0, 0, 0, 1, 1, 0.25, 100, 0, WIRE, FILL);
		g_text_3D_virtual( 1.1*c, 1.1*s, 0, "x");
		g_text_3D_virtual(-1.1*s, 1.1*c, 0, "y");
		g_text_3D_virtual(0, 0, 1, "z");

		g_sel_scale(9);
		g_fan_3D_core(0, 0, 0, c, s, 0, 1, 2.0, 0, 16, 0, WIRE, FILL);

		/*
		g_sel_scale(10);
		{
			int Imax = 1 << 16;
			for(int i = 0;i < Imax;i ++)
			{
				double x = 0;
				double y = 0;
				double z = 0;
				double dx = 2.0 * (rand() / (RAND_MAX + 1.0) - 0.5);
				double dy = 2.0 * (rand() / (RAND_MAX + 1.0) - 0.5);
				double dz = 2.0 * (rand() / (RAND_MAX + 1.0) - 0.5);

				double arrow_size = 1;
				double head_size = 0.5;
				g_arrow_3D(x,y,z,dx,dy,dz,arrow_size,head_size,0,FILL);
			}

		}
		 */
		g_finish();
}
return 0;
}
