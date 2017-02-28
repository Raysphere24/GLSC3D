#include "glsc3d_private_ext.h"

#ifdef G_ENABLE_OPENGL_DEBUG

#define DEF_CASE(value) case value: printf(#value); break

void APIENTRY g_debug_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *user)
{
	printf("\nSource : ");
	switch (source) {
		DEF_CASE(GL_DEBUG_SOURCE_API);
		DEF_CASE(GL_DEBUG_SOURCE_WINDOW_SYSTEM);
		DEF_CASE(GL_DEBUG_SOURCE_SHADER_COMPILER);
		DEF_CASE(GL_DEBUG_SOURCE_APPLICATION);
		DEF_CASE(GL_DEBUG_SOURCE_OTHER);
	}

	printf(", Type : ");
	switch (type) {
		DEF_CASE(GL_DEBUG_TYPE_ERROR);
		DEF_CASE(GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR);
		DEF_CASE(GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR);
		DEF_CASE(GL_DEBUG_TYPE_PORTABILITY);
		DEF_CASE(GL_DEBUG_TYPE_PERFORMANCE);
		DEF_CASE(GL_DEBUG_TYPE_OTHER);
	}

	printf(", Severity : ");
	switch (severity) {
		DEF_CASE(GL_DEBUG_SEVERITY_HIGH);
		DEF_CASE(GL_DEBUG_SEVERITY_MEDIUM);
		DEF_CASE(GL_DEBUG_SEVERITY_LOW);
		DEF_CASE(GL_DEBUG_SEVERITY_NOTIFICATION);
	}

	printf("\n%s\n", message);
}

#endif