uniform sampler2D texture;

void main()
{
    vec4 color = texture2D(texture, gl_TexCoord[0].xy);

    gl_FragColor = vec4(color.r, color.g, color.b, color.a);
}
