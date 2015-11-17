#ifndef GL_ES 
#define lowp
#define mediump
#define highp
#endif

attribute highp vec3	aVertex;
uniform  highp mat4	uWorldViewProjectMatrix;
void main(void)
{
	gl_Position = uWorldViewProjectMatrix * vec4(aVertex, 1.0);
}