#ifndef GL_ES 
#define lowp
#define mediump
#define highp
#else
precision lowp float; 
#endif


uniform sampler2D uTextureSampler;
uniform highp vec4 uTextColor;
uniform highp vec4 uOutlineColor;

varying  mediump vec2	vTexCoord;
varying lowp vec4 vColor;

void main (void)
{
	lowp vec4 texColor=texture2D(uTextureSampler,vTexCoord);	//a:text r:outline
	float textAlpha = texColor.a; 
    float outlineAlpha = texColor.r; 

	vec4 outlineColor=uOutlineColor*outlineAlpha;
	vec4 textColor=uTextColor*textAlpha;

	vec4 resultColor=textColor*textColor.a+outlineColor*outlineColor.a*(1.0-textColor.a);
	resultColor.a=textColor.a+outlineColor.a*(1.0-textColor.a);
	resultColor.rgb/=resultColor.a;
		
	gl_FragColor =vColor*resultColor;
}