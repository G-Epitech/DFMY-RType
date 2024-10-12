uniform sampler2D texture;

void main()
{
    vec4 color = texture2D(texture, gl_TexCoord[0].xy);

    float newRed = (color.r * 0.625) + (color.g * 0.375);
    float newGreen = (color.r * 0.7) + (color.g * 0.3);
    float newBlue = color.b;

    gl_FragColor = vec4(newRed, newGreen, newBlue, color.a);
}
