#ifndef GL_ES 
#define lowp
#define mediump
#define highp
#endif

uniform sampler2D uTextureSampler;
varying  mediump vec2	vTexCoord;
varying lowp vec4 vColor;
void main (void)
{
	lowp vec4 texColor=texture2D(uTextureSampler,vTexCoord);
	gl_FragColor =texColor*vColor;
}