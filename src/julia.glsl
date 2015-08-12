uniform vec2 c;
uniform vec2 o;
uniform vec2 scale;
uniform int iter;

void main() {
    vec2 z;
	z.x = scale.x * (gl_TexCoord[0].x - o.x);
    z.y = scale.y * (gl_TexCoord[0].y - o.y);

    int i;
    float r = 0.5 + sqrt(0.25 + sqrt(c.x * c.x + c.y * c.y));
    for(i=0; i<iter; i++) {
        float x = z.x * z.x - z.y * z.y + c.x;
        float y = z.x * z.y + z.x * z.y + c.y;

        if((x * x + y * y) > r * r) break;
        z.x = x;
        z.y = y;
    }

    float a = float(i) / float(iter);
    gl_FragColor = vec4(0.2 + 0.8 * (0.5 - 0.5 * cos(9.42 * a)),  0.6 + 0.4 * (0.5 - 0.5 * cos(9.42 * a)),
    1.0 - 0.2 * (a - a * a), 1.0);
}
