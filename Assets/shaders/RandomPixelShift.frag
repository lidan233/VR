float rand(vec2 co) {
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void mainImage( out vec4 fragColor, in vec2 fragCoord ) {
    
    float shift_size = (10. + (40. * iMouse.x / iResolution.x));
    
    vec2 co1 = vec2(1. * iTime + fragCoord.x,  5. * iTime + fragCoord.y);
    vec2 co2 = vec2(2. * iTime + fragCoord.x,  7. * iTime + fragCoord.y);
    vec2 co3 = vec2(3. * iTime + fragCoord.x, 11. * iTime + fragCoord.y);
    
    float offset_x     = (rand(co1) - 0.5) * shift_size;
    float offset_y     = (rand(co2) - 0.5) * shift_size;
    float shift_amount =  rand(co3);
    
    vec2 offset = vec2(offset_x, offset_y) * shift_amount;
    
    fragColor = texture(iChannel0, (fragCoord.xy + offset) / iResolution.xy);
    
}