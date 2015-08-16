uniform vec2 c;
uniform vec2 o;
uniform vec2 scale;
uniform int iter;

void main() {
    vec2 z;
	z.x = scale.x * (gl_TexCoord[0].x - o.x);
    z.y = scale.y * (gl_TexCoord[0].y - o.y);

    float eps = 0.005 * scale.x;
    float dist = sqrt(pow(z.x - c.x, 2) + pow(z.y - c.y, 2)) / eps;
    if (dist < 1.0) {
        gl_FragColor = vec4(1.0 - 0.5 * dist, 0.2, 0.2, 1.0);
        return;
    }

    vec2 w = z;
    int i;
    float r = 0.5 + sqrt(0.25 + sqrt(z.x * z.x + z.y * z.y));
    for(i=0; i<iter; i++) {
        float x = w.x * w.x - w.y * w.y + z.x;
        float y = w.x * w.y + w.x * w.y + z.y;

        if((x * x + y * y) > r * r) break;
        w.x = x;
        w.y = y;
    }

    float a = float(i) / float(iter);
    gl_FragColor = vec4(0.2 + 0.8 * (0.5 - 0.5 * cos(9.42 * a)),  0.6 + 0.4 * (0.5 - 0.5 * cos(9.42 * a)),
    1.0 - 0.2 * (a - a * a), 1.0);
}
