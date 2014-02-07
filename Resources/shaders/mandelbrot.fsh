#ifdef GL_ES
    precision highp float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
uniform sampler2D CC_Texture0;

uniform float u_scaleFactor;
uniform float u_maxIters;
uniform vec2 u_center;
uniform vec2 u_ratio;

void main()
{
    vec2 c = (v_texCoord.xy - 0.5) * u_ratio * u_scaleFactor - u_center;
    vec2 z = c;
    
    float iter = 0.0;
    do {
        iter += 1.0;
        z = vec2((z.x * z.x - z.y * z.y),
                 (2.0 * z.x * z.y)) + c;
        if ((dot(z, z) > 4.0) || iter > u_maxIters) {
            break;
        }  
    } while (true);
    
    
    vec4 output_color;
    if (iter <= u_maxIters) {
        float nic = (iter - (log(log(length(z))) / log(2.0))) / u_maxIters;
        float sin_nic = sin(nic);                
        output_color = vec4((0.3 * sin_nic), 
                            (1.0 * sin_nic),
                            (4.0 * sin_nic),
                            1.0);
    } else {
        output_color = vec4(0.0, 0.0, 0.0, 1.0);
    }
    
    
    gl_FragColor = v_fragmentColor * texture2D(CC_Texture0, v_texCoord) * output_color;
}