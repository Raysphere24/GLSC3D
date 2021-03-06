#include<stdio.h>

#include "glsc3d_3.h"

#define INTV              (1)
#define WINDOW_SIZE_X     (1024)
#define WINDOW_SIZE_Y     (512)

#define LEN         (4.0)

#define SIZE        (30)
#define Imax        (2 * SIZE)
#define Jmax        (2 * SIZE)

int main(void)
{
	g_init("Sample_g_bird_view.c", WINDOW_SIZE_X, WINDOW_SIZE_Y);

	g_def_scale_3D(0,
		-LEN / 2.0, LEN / 2.0, -LEN / 2.0, LEN / 2.0, -LEN / 2.0 * 2.0, LEN / 2.0 * 2.0,
		-LEN / 2.0, LEN / 2.0, -LEN / 2.0, LEN / 2.0, -LEN / 2.0, LEN / 2.0,
		0, 0, WINDOW_SIZE_X / 2, WINDOW_SIZE_Y);
	g_def_scale_3D(1,
		-LEN / 2.0, LEN / 2.0, -LEN / 2.0, LEN / 2.0, -LEN / 2.0 * 2.0, LEN / 2.0 * 2.0,
		-LEN / 2.0, LEN / 2.0, -LEN / 2.0, LEN / 2.0, -LEN / 2.0, LEN / 2.0,
		WINDOW_SIZE_X / 2, 0, WINDOW_SIZE_X / 2, WINDOW_SIZE_Y);

	double dt = 0.04;
	int i,j;
	double xx,yy,dx=LEN/Imax,dy=LEN/Jmax;

	double array[Imax*Jmax];
	double array2[Imax][Jmax];

	for(int i_time = 0; ; i_time = (i_time + 1) % (int)(2*M_PI/dt))
	{
		double t = dt*i_time;

		for (j = 0; j < Jmax; j++) {
			yy = dy * (j + 0.5) - LEN / 2.0;
			for (i = 0; i < Imax; i++) {
				xx = dx * (i + 0.5) - LEN / 2.0;
				array[i * Jmax + j] = sin(2 * xx - t) * cos(3 * yy - t);
			}
		}
		for (i = 0; i < Imax; i++)
		{
			xx = dx * (i + 0.5) - LEN/2.0;
			for (j = 0; j < Jmax; j++)
			{
				yy = dy * (j + 0.5) - LEN/2.0;
				array2[i][j] = sin(2*xx - t) * cos(3*yy - t);
			}
		}
		g_cls();

		g_line_width(4.0);
		g_sel_scale(0);

		g_line_width(2.0);
		g_bird_view_3D(-LEN/2.0, LEN/2.0, -LEN/2.0, LEN/2.0, Imax, Jmax, array2, G_TRUE, G_FALSE);

		g_line_width(4.0);
		g_sel_scale(1);
		g_bird_view_f_3D(-LEN/2.0, LEN/2.0, -LEN/2.0, LEN/2.0, Imax, Jmax, array, G_FALSE, G_TRUE);

		g_finish();
	}
	return 0;
}