#version 120

uniform vec2  c;
uniform vec2  origin;
uniform vec2  scale;
uniform float radius;
uniform int   iterations;

void main() {
    vec2 z = scale * (gl_TexCoord[0].xy - origin);

    int i;
    for (i = 0; i < iterations; ++i) {
        float x = z.x * z.x - z.y * z.y + c.x;
        float y = z.x * z.y + z.x * z.y + c.y;

        z.x = x; z.y = y;
        if (length(z) > radius) break;

    }

    float p = float(i) / float(iterations);
    float r = 0.2 + 0.8 * (0.5 - 0.5 * cos(9.42 * p));
    float g = 0.6 + 0.4 * (0.5 - 0.5 * cos(9.42 * p));
    float b = 1.0 - 0.2 * (p - p * p);
    gl_FragColor = vec4(r, g, b, 1.0);
}
