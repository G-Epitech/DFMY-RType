uniform sampler2D texture;

void main()
{
    vec4 color = texture2D(texture, gl_TexCoord[0].xy);

    float newRed = (color.r * 0.567) + (color.g * 0.433);
    float newGreen = (color.r * 0.558) + (color.g * 0.442);
    float newBlue = color.b;

    gl_FragColor = vec4(newRed, newGreen, newBlue, color.a);
}
