// --- events ----------------------------------------------------------
#define mouseUp      ( iMouse.z < 0. )                  // mouse up even:   mouse button released (well, not just that frame)
#define mouseDown    ( iMouse.z > 0. && iMouse.w > 0. ) // mouse down even: mouse button just clicked
#define mouseClicked ( iMouse.w < 0. )                  // mouse clicked:   mouse button currently clicked

// --- constant ---------------------------------------------------------
#define SC (250.0)
#define MOD3 vec3(.1031,.11369,.13787)

uniform vec3 eyes[2] ;
uniform vec3 direction ;
uniform vec2 max_min_distance ;



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
float hash( float n )
{
    return fract(sin(n)*43758.5453123);
}


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




bool jintersect(in vec3 rO, in vec3 rD, out float resT )
{
    float h = 0.0;
    float t = 0.1;
    for( int j=0; j<150; j++ )
    {
        //if( t>2000.0 ) break;

        vec3 p = rO + t*rD;
        if( p.y>300.0 ) return false;
        h = map( p );

        if( h<0.1)
        {
            resT = t;
            return true;
        }
        t += max(0.1,0.5*h);

    }

    if( h<5.0 )
    {
        resT = t;
        return true;
    }
    return false;
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



void mainImage(out vec4 fragColor, in vec2 fragCoord)
{
    vec2 xy = -1.0 + 2.0 * fragCoord.xy / iResolution.xy ;
    vec2 s = xy*vec2(1.75, 1.0) ;
    bool isCyan = 0.5 < mod(fragCoord.x, 2.0 ) ;
    if(.5<mod(fragCoord.y,2.0))isCyan = !isCyan;
    if(isCyan) s.x = s.x - 0.3 ;
    float time = 0.1 * iTime ;


    vec3 light1 = vec3(0.53, 0.292, 0.796);
    vec3 light2 = vec3( -0.707, 0.000, -0.707 );

    vec3 campos = CamPath(time) ;
    vec3 campos_next = CamPath(time+ 3.0 ) ;

    campos.y = terrain( campos.xz ) + 15.0 ;
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

    if(!jintersect(campos, rd, t))
    {
        col = 0.9 * vec3(0.97,0.99,1.0) ;
        col += 0.2 * vec3(0.8, 0.7, 0.5) * pow(sundot, 4.0) ;
    }else {
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


        // sum the shadowing and direct light
        vec3 brdf  = 2.0*vec3(0.17,0.19,0.20)*clamp(nor.y,0.0,1.0); //flat surfaces are enhanced
        brdf += 6.0*vec3(1.00,0.95,0.80)*dif1v; // shadow
        brdf += 2.0*vec3(0.20,0.20,0.20)*dif2; //second light source

        col *= brdf;

        //add distance fog
        float fo = 1.0-exp(-pow(0.0015*t,1.5));
        vec3 fco = vec3(0.7) + 0.6*vec3(0.8,0.7,0.5)*pow( sundot, 4.0 );
        col = mix( col, fco, fo );
    }

    col = sqrt(col); // brightens the image (colors are < 1.0, so sqrt would be a larger number)

    // darkens the edges of the image
    vec2 uv = xy*0.5+0.5;
    col *= 0.7 + 0.3*pow(16.0*uv.x*uv.y*(1.0-uv.x)*(1.0-uv.y),0.1);
    if(isCyan)
        fragColor=vec4(col,1.0);
//    else
//        fragColor=vec4(sqrt(col.r),0.0,0.0,1.0);
}