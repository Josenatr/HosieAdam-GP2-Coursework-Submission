#version 420 core


varying vec2 texCoord0;
varying vec3 normal0;
varying vec4 position0;

uniform sampler2D diffuse;

void main()
{
	gl_FragColor = texture2D(diffuse, texCoord0) * clamp(dot(-vec3(position0), normal0), 0.0,1.0);
}