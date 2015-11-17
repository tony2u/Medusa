#ifndef GL_ES 
#define lowp
#define mediump
#define highp
#endif

attribute highp vec3	aVertex;
attribute lowp vec4	aColor;
attribute mediump vec2	aTexCoord;
uniform highp mat4	uWorldViewProjectMatrix;
varying mediump vec2	vTexCoord;
varying lowp vec4 vColor;
void main(void)
{
	gl_Position = uWorldViewProjectMatrix * vec4(aVertex, 1.0);
	vTexCoord = aTexCoord;
	vColor=aColor;
}