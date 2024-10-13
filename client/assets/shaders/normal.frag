#version 130

uniform sampler2D texture;
uniform bool hasTexture;
uniform vec4 objectColor;

void main()
{
    vec4 texColor = objectColor;

    if (hasTexture)
    {
        texColor = texture2D(texture, gl_TexCoord[0].xy) * objectColor;
    }

    gl_FragColor = texColor;
}
