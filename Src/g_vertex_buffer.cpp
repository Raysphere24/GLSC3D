#include "glsc3d_3_private.h"

static const size_t VERTEX_BUFFER_SIZE = 3 << 14;

static const G_VECTOR g_vector_zero(0, 0, 0);

enum struct G_PRIMITIVE_MODE { POINT, LINE, TRIANGLE };
G_PRIMITIVE_MODE g_primitive_mode;

#ifdef G_USE_CORE_PROFILE

#define BUFFER_OFFSET_COLOR  ((void *)(sizeof(float) * 4))
#define BUFFER_OFFSET_NORMAL ((void *)(sizeof(float) * 8))

class G_VERTEX_BUFFER
{
	G_VERTEX *data = nullptr;
	int count = 0;
	GLuint vertex_array_id = 0, vertex_buffer_id = 0;
	GLuint shader_program = 0;
	G_PRIMITIVE_MODE primitive_mode;

public:
	G_VERTEX_BUFFER(G_PRIMITIVE_MODE primitive_mode) : primitive_mode(primitive_mode) {}

	void init()
	{
		data = (G_VERTEX *)malloc(VERTEX_BUFFER_SIZE * sizeof(G_VERTEX));

		if (data == nullptr) {
			fprintf(stderr, "failed to allocate memory\a\n");
			fprintf(stderr, "GLSC3D will abort\n");
			g_quit();
		}

		glGenVertexArrays(1, &vertex_array_id);
		glBindVertexArray(vertex_array_id);

		glGenBuffers(1, &vertex_buffer_id);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
		glBufferData(GL_ARRAY_BUFFER, VERTEX_BUFFER_SIZE * sizeof(G_VERTEX), NULL, GL_STREAM_DRAW);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
	}

	void set_shader_program(GLuint program) { shader_program = program; }

	void append(const G_VERTEX &vertex)
	{
		if (data == nullptr) init();

		data[count] = vertex;
		count++;

		if (count == VERTEX_BUFFER_SIZE)
			flush();
	}

	void flush()
	{
		if (count == 0) return;

		g_use_program(shader_program);

		if (primitive_mode == G_PRIMITIVE_MODE::LINE) {
			glUniform1i(g_line_stipple_location, g_current_line_stipple);
		}

		glBindVertexArray(vertex_array_id);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
		glBufferSubData(GL_ARRAY_BUFFER, 0, count * sizeof(G_VERTEX), data);

		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(G_VERTEX), 0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(G_VERTEX), BUFFER_OFFSET_COLOR);
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(G_VERTEX), BUFFER_OFFSET_NORMAL);

		GLenum opengl_primitive_modes[] = { GL_POINTS, GL_LINES, GL_TRIANGLES };

		glDrawArrays(opengl_primitive_modes[(int)primitive_mode], 0, count);

		count = 0;
	}
};

G_VERTEX_BUFFER g_vertex_buffer_points(G_PRIMITIVE_MODE::POINT);
G_VERTEX_BUFFER g_vertex_buffer_lines(G_PRIMITIVE_MODE::LINE);
G_VERTEX_BUFFER g_vertex_buffer_triangles(G_PRIMITIVE_MODE::TRIANGLE);

#endif

#ifndef G_USE_CORE_PROFILE
bool g_inside_glbegin;
#endif

void g_vertex_buffer_init()
{
	//g_vertex_buffer_points.init();
	//g_vertex_buffer_lines.init();
	//g_vertex_buffer_triangles.init();
}

// for 3D triangle
void g_vertex_buffer_append(const G_VERTEX &vertex)
{
#ifdef G_USE_CORE_PROFILE
	//assert(g_primitive_mode == G_PRIMITIVE_MODE::TRIANGLE);
	g_vertex_buffer_triangles.append(vertex);
#else
	glColor4fv((float *)&vertex.color);
	glNormal3fv((float *)&vertex.normal);
	glVertex3fv((float *)&vertex.position);
#endif
}

// for points, lines and 2D triangle
void g_emit_vertex(G_VECTOR position)
{
#ifdef G_USE_CORE_PROFILE
	G_VERTEX vertex;
	vertex.position = position;
	//vertex.normal = g_vector_zero;
	//vertex.pad = 0;

	switch (g_primitive_mode) {
	case G_PRIMITIVE_MODE::POINT:
		vertex.size = g_current_marker_size;
		vertex.color = g_current_marker_color;
		g_vertex_buffer_points.append(vertex);
		break;
	case G_PRIMITIVE_MODE::LINE:
		vertex.size = g_current_line_size;
		vertex.color = g_current_line_color;
		g_vertex_buffer_lines.append(vertex);
		break;
	case G_PRIMITIVE_MODE::TRIANGLE:
		vertex.size = 1;
		vertex.color = g_current_area_color;
		g_vertex_buffer_triangles.append(vertex);
		break;
	}
#else
	switch (g_primitive_mode) {
	case G_PRIMITIVE_MODE::POINT:
		glColor4fv((float *)&g_current_marker_color);
		glVertex4f(position.x, position.y, position.z, g_current_marker_size);
		break;
	case G_PRIMITIVE_MODE::LINE:
		glColor4fv((float *)&g_current_line_color);
		glVertex3fv((float *)&position);
		break;
	case G_PRIMITIVE_MODE::TRIANGLE:
		glColor4fv((float *)&g_current_area_color);
		glVertex3fv((float *)&position);
		break;
	}
#endif
}

void g_emit_line(G_VECTOR p, G_VECTOR q)
{
	g_emit_vertex(p);
	g_emit_vertex(q);
}

void g_emit_triangle(G_VECTOR p, G_VECTOR q, G_VECTOR r)
{
	g_emit_vertex(p);
	g_emit_vertex(q);
	g_emit_vertex(r);
}

#ifdef G_USE_CORE_PROFILE

void g_vertex_buffer_points_flush(void)
{
	g_vertex_buffer_points.flush();
}

void g_vertex_buffer_lines_flush(void)
{
	g_vertex_buffer_lines.flush();
}

void g_vertex_buffer_triangles_flush(void)
{
	g_vertex_buffer_triangles.flush();
}

#endif

void g_vertex_buffer_flush()
{
#ifdef G_USE_CORE_PROFILE
	g_vertex_buffer_points_flush();
	g_vertex_buffer_lines_flush();
	g_vertex_buffer_triangles_flush();
#else
	if (g_inside_glbegin) {
		glEnd();
		g_inside_glbegin = false;
	}
#endif
}

void g_prepare_points()
{
	//g_current_vertex_buffer_ptr = &g_vertex_buffer_points;
	//g_current_color_ptr = &g_current_marker_color;
	//g_current_size_ptr = &g_current_marker_size;

#ifdef G_USE_CORE_PROFILE
	g_vertex_buffer_points.set_shader_program(g_marker_programs[g_current_marker_size_type][g_current_marker_type]);
#else
	g_use_program(g_marker_programs[g_current_marker_size_type][g_current_marker_type]);
	GLint pixel_scale_location = g_marker_pixel_scale_location[g_current_marker_size_type][g_current_marker_type];
	if (pixel_scale_location >= 0)
		glUniform1f(pixel_scale_location, g_current_pixel_scale);
	GLint screen_scale_location = g_marker_screen_scale_location[g_current_marker_size_type][g_current_marker_type];
	if (screen_scale_location >= 0)
		glUniform1f(screen_scale_location, g_screen_scale_factor);
#endif
}

void g_prepare_lines()
{
	//g_current_vertex_buffer_ptr = &g_vertex_buffer_lines;
	//g_current_color_ptr = &g_current_line_color;

#ifdef G_USE_CORE_PROFILE
	//g_current_size_ptr = &g_current_line_size;
	//g_use_program(g_line_program);
	g_primitive_mode = G_PRIMITIVE_MODE::LINE;
	g_vertex_buffer_lines.set_shader_program(g_line_program);
#else
	g_use_program(0);
	glDisable(GL_LIGHTING);
#endif
}

void g_prepare_triangles()
{
	//g_current_vertex_buffer_ptr = &g_vertex_buffer_triangles;
	//g_current_color_ptr = &g_current_area_color;
	//g_current_size_ptr = &g_current_dummy_size;

	if (glsc3D_inner_scale[g_current_scale_id].is_3D) {
#ifdef G_USE_CORE_PROFILE
		//g_use_program(g_lighting_program);
		g_vertex_buffer_triangles.set_shader_program(g_lighting_program);
#else
		if (!g_inside_glbegin) {
			g_use_program(0);
			glEnable(GL_LIGHTING);
		}
#endif
	} else {
#ifdef G_USE_CORE_PROFILE
		//g_use_program(g_constant_program);
		g_vertex_buffer_triangles.set_shader_program(g_constant_program);
#else
		if (!g_inside_glbegin) {
			g_use_program(0);
			glDisable(GL_LIGHTING);
		}
#endif
	}
}

void g_set_primitive_mode(G_PRIMITIVE_MODE mode)
{
#ifdef G_USE_CORE_PROFILE
	switch (mode) {
	case G_PRIMITIVE_MODE::POINT:
		g_prepare_points();
		break;
	case G_PRIMITIVE_MODE::LINE:
		g_prepare_lines();
		break;
	case G_PRIMITIVE_MODE::TRIANGLE:
		g_prepare_triangles();
		break;
	}
#else
	if (g_primitive_mode != mode || !g_inside_glbegin) {
		g_vertex_buffer_flush();
		switch (mode) {
		case G_PRIMITIVE_MODE::POINT:
			g_prepare_points();
			glBegin(GL_POINTS);
			break;
		case G_PRIMITIVE_MODE::LINE:
			g_prepare_lines();
			glBegin(GL_LINES);
			break;
		case G_PRIMITIVE_MODE::TRIANGLE:
			g_prepare_triangles();
			glBegin(GL_TRIANGLES);
			break;
		}
		g_inside_glbegin = true;
	}
#endif
	g_primitive_mode = mode;
}

void g_begin_points()
{
	g_set_primitive_mode(G_PRIMITIVE_MODE::POINT);
}

void g_begin_lines()
{
	g_set_primitive_mode(G_PRIMITIVE_MODE::LINE);
}

void g_begin_triangles()
{
	g_set_primitive_mode(G_PRIMITIVE_MODE::TRIANGLE);
}
