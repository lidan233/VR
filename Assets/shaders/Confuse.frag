const float MK = 1337000.;
const float ULTRA = 31.4;

vec2 confuse (float time) {
    return vec2 (cos (sin (time) * ULTRA * time)) * MK;
}

float dream (float of) {
    vec2 trip = confuse (iTime);
    
    return length (of * trip);
}

void mainImage (out vec4 fragColor, in vec2 fragCoord) {
	vec2 uv = fragCoord.xy / iResolution.xy;
    vec2 center = iResolution.xy / 2.;
    
    if (length (fragCoord - center) < 50.) {
		fragColor = vec4(
            cos (dream (3.1415 * sin (iTime))),
            sin (iTime),
            cos (iTime),
            1.
        );
    }
    else {
        fragColor = vec4 (1., 0.3 * cos (sin (iTime) * ULTRA * iTime) + 0.3, 0.5, 1.);
    }
}
