#version 100
#ifndef GL_ES 
#define lowp
#define mediump
#define highp
#endif



precision mediump float;

uniform sampler2D uTextureSampler;
uniform highp vec4 uTextColor;

varying  mediump vec2	vTexCoord;
varying lowp vec4 vColor;

void main (void)
{
	lowp vec4 texColor=texture2D(uTextureSampler,vTexCoord);	//a:text
	gl_FragColor=vColor*uTextColor*texColor.a;
}