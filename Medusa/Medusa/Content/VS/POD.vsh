#ifndef GL_ES 
#define lowp
#define mediump
#define highp
#endif

attribute highp vec3	aVertex;
attribute mediump vec2	aTexCoord;
attribute mediump vec3	aNormal;
uniform mediump mat4	uWorldViewProjectMatrix;
uniform mediump vec3	uModelLightDirection;
varying mediump vec2	vTexCoord;
varying mediump float	vDot;
void main(void)
{
	gl_Position = uWorldViewProjectMatrix * vec4(aVertex,1.0);
	vTexCoord = aTexCoord;
	vDot=dot(aNormal,-uModelLightDirection);
}