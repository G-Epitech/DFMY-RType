#version 130

uniform sampler2D texture;
uniform vec4 addColor;

void main()
{
    vec4 texColor = texture2D(texture, gl_TexCoord[0].xy);

    gl_FragColor = texColor * addColor;
}
