uniform vec2 c;
uniform int iter;

void main() {
	vec2 z;
	z.x = 3.0 * (gl_TexCoord[0].x - 0.5);
	z.y = 3.0 * (gl_TexCoord[0].y - 0.5);

	int i;
	for(i=0; i<iter; i++) {
		float x = (z.x * z.x - z.y * z.y) + c.x;
		float y = (z.y * z.x + z.x * z.y) + c.y;

		if((x * x + y * y) > 4.0) break;
		z.x = x;
		z.y = y;
	}

    float a = float(i) / float(iter);
	gl_FragColor = vec4(a, a, a, 1.0);
}
