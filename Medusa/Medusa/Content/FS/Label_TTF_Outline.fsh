#ifndef GL_ES 
#define lowp
#define mediump
#define highp
#else
precision lowp float; 
#endif


uniform sampler2D uTextureSampler;
uniform highp vec4 uOutlineColor;

varying  mediump vec2	vTexCoord;
varying lowp vec4 vColor;

void main (void)
{
	lowp vec4 texColor=texture2D(uTextureSampler,vTexCoord);	//r:outline
	gl_FragColor =vColor*uOutlineColor*texColor.r;
}