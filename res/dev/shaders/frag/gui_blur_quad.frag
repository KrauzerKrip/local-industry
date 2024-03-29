#version 400 core

in vec2 TexCoords;
out vec4 color;
uniform vec4 quadColor;

uniform sampler2D screenTexture;
uniform vec2 screenTextureSize; // in pixels

uniform float sigma;
uniform vec2 direction;


float CalcGauss(float x, float sigma)
{
    if (sigma <= 0.0)
        return 0.0;
    return exp(-(x*x) / (2.0 * sigma) ) / (2.0 * 3.14157 * sigma);
}

void main()
{
    vec4 texCol   = texture2D(screenTexture, TexCoords);
    vec4 gaussCol = vec4(texCol.rgb, 1.0);
    vec2 step     = direction / screenTextureSize;
    for ( int i = 1; i <= 32; ++ i )
    {
        float weight = CalcGauss( float(i) / 32.0, sigma * 0.5 );
        if ( weight < 1.0/255.0 )
            break;
        texCol    = texture2D( screenTexture, TexCoords + step * float(i) );
        gaussCol += vec4( texCol.rgb * weight, weight );
        texCol    = texture2D( screenTexture, TexCoords - step * float(i) );
        gaussCol += vec4( texCol.rgb * weight, weight );
    }
    gaussCol.rgb = clamp(gaussCol.rgb / gaussCol.w, 0.0, 1.0);
    color = vec4(mix(gaussCol.rgb, quadColor.rgb, 0.5), 1.0);
}