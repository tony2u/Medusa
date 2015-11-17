#ifndef GL_ES 
#define lowp
#define mediump
#define highp
#endif

uniform highp vec3 uLightDiffuse;	// Color and ID passed in from vertex.
void main()
{
	// Simply assigns the color and ID number of the object it renders.
	gl_FragColor = vec4(uLightDiffuse,1.0);
}

