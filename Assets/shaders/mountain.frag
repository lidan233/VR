// --- events ----------------------------------------------------------
#define mouseUp      ( iMouse.z < 0. )                  // mouse up even:   mouse button released (well, not just that frame)
#define mouseDown    ( iMouse.z > 0. && iMouse.w > 0. ) // mouse down even: mouse button just clicked
#define mouseClicked ( iMouse.w < 0. )                  // mouse clicked:   mouse button currently clicked


// --- constant ---------------------------------------------------------
#define PI 3.141592653589793238
#define TWOPI 6.283185307179586
#define SC (250.0)
#define MOD2 vec2(3.07965, 7.4235)
#define MOD3 vec3(.1031,.11369,.13787)
#define C(x) clamp(x, 0., 1.)
#define S(a, b, x) smoothstep(a, b, x)
#define F(x, f) (floor(x * f) / f)
#define B(x,y,z,w) S(x-z, x+z, w)*S(y+z, y-z, w)
#define lava_time iTime*0.1
#define TEMPERATURE 2200.0

//firework-----------------
#define NUM_EXPLOSIONS 8.
#define NUM_PARTICLES 70.


vec2 lava_rot2D(vec2 p, float angle) {
    angle = radians(angle);
    float s = sin(angle);
    float c = cos(angle);

    return p * mat2(c,s,-s,c);
}


float lava_hash12(vec2 p) {
    p  = fract(p / MOD2);
    p += dot(p.xy, p.yx+19.19);
    return fract(p.x * p.y);
}
float hash( float n )
{
    return fract(sin(n)*43758.5453123);
}


const vec2 add = vec2(1.0, 0.0);

float lava_noise( in vec2 x ) {
    vec2 p = floor(x);
    vec2 f = fract(x);
    f = f*f*(3.0-2.0*f);
    float res = mix(mix( lava_hash12(p),          lava_hash12(p + add.xy),f.x),
    mix( lava_hash12(p + add.yx), lava_hash12(p + add.xx),f.x),f.y);
    return res;
}

mat2 makem2(in float theta){float c = cos(theta);float s = sin(theta);return mat2(c,-s,s,c);}
float noiseLava( in vec2 x )
{
    vec2 p = floor(x);
    vec2 f = fract(x);

    f = f*f*(3.0-2.0*f);

    float n = p.x + p.y*57.0;

    float res = mix(mix( hash(n+  0.0), hash(n+  1.0),f.x),
    mix( hash(n+ 57.0), hash(n+ 58.0),f.x),f.y);

    return res*255;
}


float sampleFreq = 0.2 ;
vec2 gradn(vec2 p) {
    float ep = .09;
    float gradx = noiseLava(sampleFreq*vec2(p.x+ep,p.y))-noiseLava(sampleFreq*vec2(p.x-ep,p.y));
    float grady = noiseLava(sampleFreq*vec2(p.x,p.y+ep))-noiseLava(sampleFreq*vec2(p.x,p.y-ep));
    return vec2(gradx,grady);
}


vec3 blackbody(float t)
{
    t *= TEMPERATURE;

    float u = ( 0.860117757 + 1.54118254e-4 * t + 1.28641212e-7 * t*t )
    / ( 1.0 + 8.42420235e-4 * t + 7.08145163e-7 * t*t );

    float v = ( 0.317398726 + 4.22806245e-5 * t + 4.20481691e-8 * t*t )
    / ( 1.0 - 2.89741816e-5 * t + 1.61456053e-7 * t*t );

    float x = 3.0*u / (2.0*u - 8.0*v + 4.0);
    float y = 2.0*v / (2.0*u - 8.0*v + 4.0);
    float z = 1.0 - x - y;

    float Y = 1.0;
    float X = Y / y * x;
    float Z = Y / y * z;

    mat3 XYZtoRGB = mat3(3.2404542, -1.5371385, -0.4985314,
    -0.9692660,  1.8760108,  0.0415560,
    0.0556434, -0.2040259,  1.0572252);

    return max(vec3(0.0), (vec3(X,Y,Z) * XYZtoRGB) * pow(t * 0.0004, 4.0));
}


float flowFBM(in vec2 p)
{
    float z=2.;
    float rz = 0.;
    vec2 bp = p;
    for (float i= 1.;i < 9.;i++ ){
        //primary flow speed
        p += lava_time*.006;
        //secondary flow speed (speed of the perceived flow)
        bp += lava_time*0.00009;
        //displacement field (try changing time multiplier)
        vec2 gr = gradn(i*p*1.4+lava_time*0.1);
        //rotation of the displacement field
        gr*=makem2(lava_time*2.-(0.05*p.x+0.03*p.y)*40.);
        //displace the system
        p += gr*.5;
        //add noise octave
        rz+= (sin(lava_noise(p)*7.)*0.5+0.5)/z;
        //blend factor (blending displaced system with base system)
        //you could call this advection factor (.5 being low, .95 being high)
        p = mix(bp,p,.77);
        //intensity scaling
        z *= 1.4;
        //octave scaling
        p *= 3.1;
        bp *= 1.5;
    }
    return rz;
}



vec3 fhash31(float p) {
    vec3 p3 = fract(vec3(p) * MOD3);
    p3 += dot(p3, p3.yzx + 19.19);
    return fract(vec3((p3.x + p3.y)*p3.z, (p3.x+p3.z)*p3.y, (p3.y+p3.z)*p3.x));
}
float fhash12(vec2 p){
    vec3 p3  = fract(vec3(p.xyx) * MOD3);
    p3 += dot(p3, p3.yzx + 19.19);
    return fract((p3.x + p3.y) * p3.z);
}

float fcirc(vec2 uv, vec2 pos, float size) {
    uv -= pos;
    size *= size;
    return S(size*1.1, size, dot(uv, uv));
}

float flight(vec2 uv, vec2 pos, float size) {
    uv -= pos;
    size *= size;
    return size/dot(uv, uv);
}

vec3 fexplosion(vec2 uv, vec2 p, float seed, float t) {

    vec3 col = vec3(0.);

    vec3 en = fhash31(seed);
    vec3 baseCol = en;
    for(float i=0.; i<NUM_PARTICLES; i++) {
        vec3 n = fhash31(i)-.5;

        vec2 startP = p-vec2(0., t*t*.1);
        vec2 endP = startP+normalize(n.xy)*n.z;
        float pt = 1.-pow(t-1., 2.);
        vec2 pos = mix(p, endP, pt);
        float size = mix(.01, .005, S(0., .1, pt));
size *= S(1., .1, pt);
float sparkle = (sin((pt+n.z)*100.)*.5+.5);
sparkle = pow(sparkle, pow(en.x, 3.)*50.)*mix(0.01, .01, en.y*n.y);
size += sparkle*B(en.x, en.y, en.z, t);
col += baseCol*flight(uv, pos, size);
}

return col;
}

vec3 Rainbow(vec3 c) {
    float t=iTime;
    float avg = (c.r+c.g+c.b)/3.;
    c = avg + (c-avg)*sin(vec3(0., .333, .666)+t);
    c += sin(vec3(.4, .3, .3)*t + vec3(1.1244,3.43215,6.435))*vec3(.4, .1, .5);
    return c;
}

vec3 firework(vec2 fragCoord)
{

    vec2 uv = fragCoord.xy / iResolution.xy;
    uv.x -= .5;
    uv.x *= iResolution.x/iResolution.y;
    float n = fhash12(uv+10.);
    float t = iTime*.5;
    vec3 c = vec3(0.);

    for(float i=0.; i<NUM_EXPLOSIONS; i++) {
        float et = t+i*1234.45235;
        float id = floor(et);
        et -= id;
        vec2 p = fhash31(id).xy;
        p.x -= .5;
        p.x *= 1.6;
        c += fexplosion(uv, p, id, et);
    }
    c = Rainbow(c);
    return c ;
}


uniform vec3 eyes[2] ;
uniform vec3 target[2] ;
uniform vec3 direction ;
uniform vec2 max_min_distance ;
const vec3 lig = normalize( vec3(-0.3,0.4,0.7) );


struct Ray{
    vec3 origin ;
    vec3 direction ;
} ;

float hash31(vec3 p3)
{
    p3  = fract(p3 * MOD3);
    p3 += dot(p3, p3.yzx + 19.19);
    return -1.0 + 2.0 * fract((p3.x + p3.y) * p3.z);
}
vec3 hash33(vec3 p3)
{
    p3 = fract(p3 * MOD3);
    p3 += dot(p3, p3.yxz+19.19);
    return -1.0 + 2.0 * fract(vec3((p3.x + p3.y)*p3.z, (p3.x+p3.z)*p3.y, (p3.y+p3.z)*p3.x));
}

//float hash21(vec2 p3)
//{
//    p3  = fract(p3 * MOD3);
//    p3 += dot(p3, p3.yx + 19.19);
//    return -1.0 + 2.0 * fract((p3.x + p3.y) * sin(p3.x + p3.y));
//}


vec4 noised4( in vec3 x )
{
    vec3 p = floor(x);
    vec3 w = fract(x);

    // quintic interpolation
    vec3 u = w*w*w*(w*(w*6.0-15.0)+10.0);
    vec3 du = 30.0*w*w*(w*(w-2.0)+1.0);

    // cubic interpolation
    // vec3 u = w*w*(3.0-2.0*w);
    // vec3 du = 6.0*w*(1.0-w);

    float a = hash31(p+vec3(0.0,0.0,0.0));
    float b = hash31(p+vec3(1.0,0.0,0.0));
    float c = hash31(p+vec3(0.0,1.0,0.0));
    float d = hash31(p+vec3(1.0,1.0,0.0));
    float e = hash31(p+vec3(0.0,0.0,1.0));
    float f = hash31(p+vec3(1.0,0.0,1.0));
    float g = hash31(p+vec3(0.0,1.0,1.0));
    float h = hash31(p+vec3(1.0,1.0,1.0));


    float k0 =   a;
    float k1 =   b - a;
    float k2 =   c - a;
    float k3 =   e - a;
    float k4 =   a - b - c + d;
    float k5 =   a - c - e + g;
    float k6 =   a - b - e + f;
    float k7 = - a + b + c - d + e - f - g + h;

    return vec4( k0 + k1*u.x + k2*u.y + k3*u.z + k4*u.x*u.y + k5*u.y*u.z + k6*u.z*u.x + k7*u.x*u.y*u.z,
    du * vec3( k1 + k4*u.y + k6*u.z + k7*u.y*u.z,
    k2 + k5*u.z + k4*u.x + k7*u.z*u.x,
    k3 + k6*u.x + k5*u.y + k7*u.x*u.y ) );
}

vec3 noised( in vec2 x )
{
    vec2 p = floor(x);
    vec2 f = fract(x);
    vec2 ff = f*f;
    vec2 f2 = f*2.0;
    vec2 u = ff*(3.0-f2);

    float n = p.x + p.y*57.0;

    float a = hash(n+  0.0);
    float b = hash(n+  1.0);
    float c = hash(n+ 57.0);
    float d = hash(n+ 58.0);
    return vec3(a+(b-a)*u.x+(c-a)*u.y+(a-b-c+d)*u.x*u.y,
    30.0*ff*((ff-f2)+1.0)*(vec2(b-a,c-a)+(a-b-c+d)*u.yx));
}



float noise3( in vec3 x )
{
    vec3 p1 = floor(x);
    vec3 ff = fract(x);

    vec3 w = ff*ff*ff*(ff*(ff*6.0-15.0)+10.0);;

    vec3 a = hash33(p1+vec3(0.0,0.0,0.0));
    vec3 b = hash33(p1+vec3(1.0,0.0,0.0));
    vec3 c = hash33(p1+vec3(0.0,1.0,0.0));
    vec3 d = hash33(p1+vec3(1.0,1.0,0.0));
    vec3 e = hash33(p1+vec3(0.0,0.0,1.0));
    vec3 f = hash33(p1+vec3(1.0,0.0,1.0));
    vec3 g = hash33(p1+vec3(0.0,1.0,1.0));
    vec3 h = hash33(p1+vec3(1.0,1.0,1.0));

    return 	mix(
    mix(
    mix(dot(ff - vec3(0, 0, 0),a),
    dot(ff - vec3(1, 0, 0),b),
    w.x),
    mix(dot(ff - vec3(0, 1, 0),c),
    dot(ff - vec3(1, 1, 0),d),
    w.x),
    w.z),
    mix(
    mix(dot(ff - vec3(0, 1, 0), e),
    dot(ff - vec3(1, 1, 0), f),
    w.x),
    mix(dot(ff - vec3(0, 1, 1), g),
    dot(ff - vec3(1, 1, 1), h),
    w.x),
    w.z),
    w.y);

}

float noise( in vec2 x )
{
    vec2 p = floor(x);
    vec2 f = fract(x);

    f = f*f*(3.0-2.0*f);

    float n = p.x + p.y*57.0;

    float res = mix(mix( hash(n+  0.0), hash(n+  1.0),f.x),
    mix( hash(n+ 57.0), hash(n+ 58.0),f.x),f.y);

    return res;
}


mat3 m = mat3( 0.00,  0.80,  0.60,
-0.80,  0.36, -0.48,
-0.60, -0.48,  0.64 );

mat2 m2 = mat2(1.6,-1.2,1.2,1.6);


float fbm( vec2 p )
{
    float f = 0.0;
    f += 0.5000*noise( p ); p = m2*p*2.02;
    f += 0.2500*noise( p ); p = m2*p*2.03;
    f += 0.1250*noise( p ); p = m2*p*2.01;
    f += 0.0625*noise( p );
    return f/0.9375;
}


//-----------------------------------------------------------------------------
float SmokeParticle(vec2 loc, vec2 pos, float size, float rnd, float time)
{
    loc = loc-pos;
    float d = dot(loc, loc)/size;
    // Outside the circle? No influence...
    if (d > 1.0) return 0.0;

    // Rotate the particles...
    float r= time*rnd*1.85;
    float si = sin(r);
    float co = cos(r);
    // Grab the rotated noise decreasing resolution due to Y position.
    // Also used 'rnd' as an additional noise changer.
    d = noise(hash(rnd*828.0)*83.1+mat2(co, si, -si, co)*loc.xy*2./(pos.y*.16)) * pow((1.-d), 3.)*.7;
    return d;
}


//const mat2 m = mat2(0.8,-0.6,0.6,0.8);

float terrain( in vec2 x )
{
    vec2  p = x*0.003;
    float a = 0.0;
    float b = 1.0;
    vec2  d = vec2(0.0);
    for(int i=0;i<14; i++)
    {
        vec3 n = noised(p);
        d += n.yz;
        a += b*n.x/(1.0+dot(d,d));
        b *= 0.5;
        p=m2*p;
    }

    return 140.0*a;
}


// smooth your triangles
float map( in vec3 p )
{
    float h = terrain(p.xz);

    float ss = 0.03;
    float hh = h*ss;
    float fh = fract(hh);
    float ih = floor(hh);
    fh = mix( sqrt(fh), fh, smoothstep(50.0,140.0,h) );
    h = (ih+fh)/ss;

    return p.y - h;
}




int jintersect(in vec3 rO, in vec3 rD, out float resT )
{
    float h = 0.0;
    float t = 0.1;
    for( int j=0; j<150; j++ )
    {
        //if( t>2000.0 ) break;

        vec3 p = rO + t*rD;
        if( p.y>300.0 ) return 0;
        h = map( p );

        if( p.y < 70.0 && h < 10.0 ) return 2 ;
        if( h<0.1)
        {
            resT = t;
            return 1;
        }
        t += max(0.1,0.5*h);
    }

    if( h<5.0 )
    {
        resT = t;
        return 1;
    }
    return 0;
}

// just calculate the direct light
float softshadow(in vec3 rO, in vec3 rD )
{
    float res = 1.0;
    float t = 0.1;
    for( int j=0; j<80; j++ )
    {
        vec3 p = rO + t*rD;
        float h = map( p );
        if( h<0.1 )
        {
            return 0.0;
        }
        res = min( res, 16.0*h/t );
        t += h;
    }
    return clamp( res, 0.0, 1.0 );
}


vec3 calcNormal( in vec3 pos, float t )
{
    vec3  eps = vec3(0.001*t,0.0,0.0);
    vec3 nor;
    float center = map(pos);
    nor.x = center - map(pos-eps.xyy);
    nor.y = 0.001*t;
    nor.z = center - map(pos-eps.yyx);
    return normalize(nor);
}


vec3 CamPath( float time )
{
    vec2 p = 650.0*vec2( cos(1.4+0.37*time), cos(3.2+0.31*time) );
    return vec3( p.x, 0.0, p.y );
}




mat3 setCamera( in vec3 ro, in vec3 ta, in float cr )
{
    vec3 cw = normalize(ta-ro);
    vec3 cp = vec3(sin(cr), cos(cr),0.0);
    vec3 cu = normalize( cross(cw,cp) );
    vec3 cv = normalize( cross(cu,cw) );
    return mat3( cu, cv, cw );
}

vec4 mapClouds( in vec3 pos )
{
    vec2 q = pos.xz *0.5 + vec2(0.0,-iTime);

    float d = clamp( fbm(q)-0.55, 0.0, 1.0 );
    d *= smoothstep( 0.5, 0.55, terrain(pos.xz)+0.01 );

    vec4 res = vec4( d );
    res.xyz  = 0.25*mix( vec3(1.0,0.8,0.7), 0.2*vec3(0.4,0.4,0.4), d );
    res.xyz *= 0.5 + 0.5*smoothstep(-2.0, 1.0, pos.y);
    return res;
}

vec4 raymarchClouds( in vec3 ro, in vec3 rd, in vec3 bcol, in vec2 px )
{
    vec4 sum = vec4( 0.0 );
    float sun = pow( clamp( dot(rd,lig), 0.0, 1.0 ), 6.0 );
    float t = hash(px.x)*25.6;
    for( int i=0; i<60; i++ )
    {
        vec4 col = mapClouds( ro + t*rd );
        col.xyz += vec3(1.0,0.7,0.4)*0.4*sun*(1.0-col.w);
        col.xyz = mix( col.xyz, bcol, 1.0-exp(-0.00006*t*t*t) );
        col.a *= 2.0;
        col.rgb *= col.a;
        sum = sum + col*(1.0 - sum.a);

        t += max(0.1,0.05*t);
        if( t>300 || sum.w>0.95 ) break;
    }
    sum.xyz /= (0.001+sum.w);
    return clamp( sum, 0.0, 1.0 );
}



void mainImage(out vec4 fragColor, in vec2 fragCoord)
{
    vec2 xy = -1.0 + 2.0 * fragCoord.xy / iResolution.xy ;
    vec2 s = xy*vec2(1.75, 1.0) ;
    vec2 tuv = (fragCoord-.5*iResolution.xy)/iResolution.y;

    bool isCyan = 0.5 < mod(fragCoord.x, 2.0 ) ;
    if(.5<mod(fragCoord.y,2.0))isCyan = !isCyan;
    if(isCyan) s.x = s.x - 0.3 ;
    float time = 0.1 * iTime ;


    vec3 light1 = vec3(0.53, 0.292, 0.796);
    vec3 light2 = vec3( -0.707, 0.000, -0.707 );

    vec3 campos = CamPath(time) ;
    vec3 campos_next = CamPath(time+ 3.0 ) ;

    campos.y = terrain( campos.xz ) + 15.0  ;
    if(campos.y<=70) campos.y = 75 ;
    campos_next.y = campos.y * 0.5 ;

    float roll = 0.1 * cos(0.1*time) ;
    vec3 front = normalize(campos_next - campos) ;
    vec3 up = vec3(sin(roll), cos(roll), 0.0) ;
    vec3 right = normalize(cross(front,up)) ;
    up = normalize(cross(right,front)) ;
    vec3 rd = normalize( s.x*right + s.y*up + 1.6*front ) ;

    if( isCyan ) campos += 2.0 * right ;

    float sundot = clamp(dot(rd, light1),0.0,1.0) ;
    vec3 col ;
    float t ;
    vec3 diffuse ;
    vec3 fcol = vec3(0) ;

    int isIntersectWithTerrain = jintersect(campos, rd, t) ;
    if(isIntersectWithTerrain==0)
    {
        col = vec3(0.3,0.5,0.85) - rd.y*rd.y*0.5;
        col = mix( col, 0.85*vec3(0.7,0.75,0.85), pow( 1.0-max(rd.y,0.0), 4.0 ) );
        // sun
        col += 0.25*vec3(1.0,0.7,0.4)*pow( sundot,5.0 );
        col += 0.25*vec3(1.0,0.8,0.6)*pow( sundot,64.0 );
        col += 0.2*vec3(1.0,0.8,0.6)*pow( sundot,512.0 );
        // clouds
        vec2 sc = campos.xz + rd.xz*(SC*1000.0-campos.y)/rd.y;
        col = mix( col, vec3(1.0,0.95,1.0), 0.5*smoothstep(0.5,0.8,fbm(0.0005*sc/SC)) );
        // horizon
        col = mix( col, 0.68*vec3(0.4,0.65,1.0), pow( 1.0-max(rd.y,0.0), 16.0 ) );
        t = -1.0;

        // firework
        col = 0.2*  firework(fragCoord) +(1.-.2)*col  ;

        //        col = 0.3* fcol+(1.-.3)*col;
        //        col = fcol ;
    }else if(isIntersectWithTerrain==1){
        vec3 pos = campos + t*rd ;
        vec3 nor = calcNormal(pos, t) ;

        float dif1 = clamp(dot(light1, nor), 0.0, 1.0 ) ;
        float dif2 = clamp( 0.2 + 0.8*dot(light2, nor),0.0,1.0 ) ;
        float sh = 1.0;
        if( dif1>0.001 ) // if it isn't already facing away from the light, determine if it is shadowed
        sh = softshadow(pos+light1*20.0,light1);

        vec3 dif1v = vec3(dif1) ;
        dif1v *= vec3( sh, sh*sh*0.5+0.5*sh, sh*sh );

        // the snow covers up most of the nice detail in the dirt
        #if 1
        col = vec3(0.1,0.05,0.02);
        #else
        float r = noise( 7.0*pos.xz );
        col = (r*0.25+0.75)*0.9*mix( vec3(0.10,0.05,0.03), vec3(0.13,0.10,0.08), clamp(terrain( vec2(pos.x,pos.y*48.0))/200.0,0.0,1.0) );
        col = mix( col, 0.17*vec3(0.5,.23,0.04)*(0.50+0.50*r),smoothstep(0.70,0.9,nor.y) );
        col = mix( col, 0.10*vec3(0.2,.30,0.00)*(0.25+0.75*r),smoothstep(0.95,1.0,nor.y) );
        col *= 0.75;
        #endif

        // snow
        //        #if 1
        //        float h = smoothstep(55.0,80.0,pos.y + 25.0*fbm(0.01*pos.xz) );
        //        float e = smoothstep(1.0-0.5*h,1.0-0.1*h,nor.y);
        //        float o = 0.3 + 0.7*smoothstep(0.0,0.1,nor.x+h*h);
        //        float s = h*e*o;
        //        s = smoothstep( 0.1, 0.9, s );
        //        col = mix( col, 0.4*vec3(0.6,0.65,0.7), s );
        //        #endif


        //        vec3  col = vec3(0.36,0.43,0.54) - rd.y*0.5;
        //        float sun = clamp( dot(rd,lig), 0.0, 1.0 );
        //        col += vec3(1.0,0.8,0.4)*0.24*pow( sun, 6.0 );
        //        vec3 bcol = col;
        //        //smoke
        //        vec4 res = raymarchClouds( campos, rd, bcol, fragCoord );
        //        col = mix( col, res.xyz, res.w ) ;

        // sum the shadowing and direct light
        vec3 brdf  = 2.0*vec3(0.17,0.19,0.20)*clamp(nor.y,0.0,1.0); //flat surfaces are enhanced
        brdf += 6.0*vec3(1.00,0.95,0.80)*dif1v; // shadow
        brdf += 2.0*vec3(0.20,0.20,0.20)*dif2; //second light source

        col *= brdf;
        //add distance fog
        float fo = 1.0-exp(-pow(0.0015*t,1.5));
        vec3 fco = vec3(0.7) + 0.6*vec3(0.8,0.7,0.5)*pow( sundot, 4.0 );
        col = mix( col, fco, fo );
    }else if(isIntersectWithTerrain==2){
        vec3 pos = campos + t*rd ;
        vec3 lavCol = blackbody(flowFBM(pos.xz*0.05)) ;
        col = lavCol ;
    }

    col = sqrt(col); // brightens the image (colors are < 1.0, so sqrt would be a larger number)

    // darkens the edges of the image
    //    vec2 uv = xy*0.5+0.5;
    //    col *= 0.7 + 0.3*pow(16.0*uv.x*uv.y*(1.0-uv.x)*(1.0-uv.y),0.1);

    vec2 pos= (fragCoord.xy/iResolution.y - vec2(.8,.5))*2.;
    float gaz = 1.5*fbm(vec2(5.*(pos.x-PI),2.*pos.y-6.*time));
    col = 0.4* vec3(.2,.3,0.1)*gaz+(1.-.4)*col;


    if(isCyan)
    fragColor=vec4(col,1.0);
    //    else

    //        fragColor=vec4(sqrt(col.r),0.0,0.0,1.0);
}