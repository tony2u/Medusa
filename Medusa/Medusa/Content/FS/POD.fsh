#ifndef GL_ES 
#define lowp
#define mediump
#define highp
#endif

uniform sampler2D uTextureSampler;
varying mediump vec2	vTexCoord;
varying lowp float		vDot;
void main (void)
{
	gl_FragColor=texture2D(uTextureSampler,vTexCoord)*vDot;
}