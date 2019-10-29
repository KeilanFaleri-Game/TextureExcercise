#version 120

attribute vec2 a_Position;
attribute vec4 a_Color;
attribute vec2 a_UV;

uniform float u_XOffset;

varying vec4 v_Color;
varying vec2 v_UV;

void main()
{
    vec2 pos = a_Position;
    pos.x += u_XOffset;

    gl_Position = vec4( pos, 0, 1 );

    v_Color = a_Color;

	v_UV = a_UV;
}
