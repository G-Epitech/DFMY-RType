uniform sampler2D texture;

void main()
{
    vec4 color = texture2D(texture, gl_TexCoord[0].xy);

    float newRed = color.r;
    float newGreen = (color.g * 0.95) + (color.b * 0.05);
    float newBlue = (color.g * 0.433) + (color.b * 0.567);

    gl_FragColor = vec4(newRed, newGreen, newBlue, color.a);
}
