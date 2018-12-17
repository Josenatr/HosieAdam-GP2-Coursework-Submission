#version 420 core


attribute vec3 position;
attribute vec2 texCoord;
attribute vec3 normal;

varying vec2 texCoord0;
varying vec3 normal0;
varying vec4 position0;

uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4(position*5.0f, 1.0);
	position0 = gl_Position;
	texCoord0 = texCoord;
	normal0 = (transform * vec4(normal,0.0)).xyz;

}