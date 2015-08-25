#version 120

uniform vec2 c;
uniform vec2 origin;
uniform vec2 scale;
uniform int  iterations;

vec2 complex_product(vec2 a, vec2 b) {
    return vec2(a.x * b.x - a.y * b.y,
                a.x * b.y + a.y * b.x);
}

void main() {
    vec2 z = scale * (gl_TexCoord[0].xy - origin);

    float eps = 0.005 * scale.x;
    float dist = length(z - c) / eps;

    if (dist < 1.0) {
        gl_FragColor = vec4(1.0 - 0.5 * dist, 0.2, 0.2, 1.0);
        return;
    }

    vec2 w = z;
    float radius = 0.5 + sqrt(0.25 + length(z));

    int i;
    for (i = 0; i < iterations; ++i) {
	// w = complex_product(w, w) + z;
	float x = w.x * w.x - w.y * w.y + z.x;
	float y = 2.0 * w.x * w.y + z.y;
	w.x = x; w.y = y;
        if (length(w) > radius) break;
    }

    float p = float(i) / float(iterations);
    float r = 0.2 + 0.8 * (0.5 - 0.5 * cos(9.42 * p));
    float g = 0.6 + 0.4 * (0.5 - 0.5 * cos(9.42 * p));
    float b = 1.0 - 0.2 * (p - p * p);
    gl_FragColor = vec4(r, g, b, 1.0);
}
