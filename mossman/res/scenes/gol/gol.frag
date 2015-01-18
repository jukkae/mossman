uniform vec2 c;
uniform float iterations;
uniform float translateX;
uniform float translateY;
uniform float shrink;
uniform sampler2D tex;

void main() {
	
    vec2 z;
    z.x = (gl_TexCoord[0].x - translateX) * shrink;
    z.y = (gl_TexCoord[0].y - translateY) * shrink;
    vec2 z1 = vec2(0.0, 0.0);
    vec2 z2 = vec2(0.0, 0.0);
    vec2 z3 = vec2(0.0, 0.0);

    int i;
    int iter = int(iterations);
    for(i=0; i < iter; i++) {
    	z1 = vec2(z.x  * z.x  - z.y  * z.y,  2.0 * z.x  * z.y);
    	z1 = vec2(z1.x * z.x  - z1.y * z.y,  z1.y * z.x + z1.x * z.y) + c;
    	
    	z2 = vec2(z1.x * z1.x - z1.y * z1.y, 2.0 * z1.x * z1.y);
    	z2 = vec2(z2.x * z1.x - z2.y * z1.y, z2.y * z1.x + z2.x * z1.y) + c;
    	
    	z3 = vec2(z2.x * z2.x - z2.y * z2.y, 2.0 * z2.x * z2.y);
    	z3 = vec2(z3.x * z2.x  - z3.y * z2.y,  z3.y * z2.x + z3.x * z2.y) + c;
    	
    	z  = vec2(z3.x * z3.x - z3.y * z3.y, 2.0 * z3.x * z3.y);
    	z  = vec2(z.x * z3.x  - z.y * z3.y,  z.y * z3.x + z.x * z3.y) + c;
    	
        if( length(z) > 4.0) break;
    }
    i = i * 4 + 4;
    if( length(z1) > 4.0 )
    	i--;
	if( length(z2) > 4.0 )
		i--;
	if( length(z3) > 4.0 )
		i--;
    
    gl_FragColor = vec4(0.0, 1.0, 0.0, float(i)/(4.0*iterations));
    //float max = 4.0 * iterations;
    //gl_FragColor = texture2D(tex, vec2(float(i) / max, 0));
}