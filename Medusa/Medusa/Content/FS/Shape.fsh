#ifndef GL_ES 
#define lowp
#define mediump
#define highp
#endif

varying lowp vec4 vColor;

void main (void)
{
	gl_FragColor =vColor;
}