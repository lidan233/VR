vec4 sphere( vec3 spherepos, float r, vec3 raypos )
{
 //   float disp = texture( iChannel1, raypos.xy * 0.05 ).r;
   // ec4 clip =vec4( -1.0,-1.0,0,0);
    
   // return max( distance( spherepos, raypos ) - r, dot(raypos, normalize(clip.xyz)) - clip.w);
    return vec4( distance( spherepos, raypos ) - r,1.0,0,0.5); 
}


vec4 box( vec3 position, vec3 lengths, vec3 raypos )
{
    vec3 p = raypos - position;
    
    float d0 = max( p.x - lengths.x, -p.x - lengths.x );
    float d1 = max( p.y - lengths.y, -p.y - lengths.y );
    float d2 = max( p.z - lengths.z, -p.z - lengths.z );
    return vec4( max( d0, max(d1,d2 )), 1.0,0, 0.8);
}

vec4 cylinder( vec3 position, vec2 dim, vec3 raypos )
{
    vec3 p = raypos - position;
    return vec4( max( length( p.xz ) - dim.x,
                 max( p.y - dim.y, -p.y - dim.y)), 1.0,0,0.1);
}

vec4 stage( vec3 raypos, float w, float r )
{

 //   float scale = max( 0.0, 1.0 -  length( raypos.xz) / 40.0 );
    
  //  float d = cos( iTime * 10.0 - distance( vec2( 0,0) , raypos.xz) * 0.5 ) * 2.0 + 
    //    	  cos( iTime * 10.0 - distance( vec2( 10.0,5.0) , raypos.xz) * 1.0 )  * 0.8 + 
    //     	  cos( iTime * 10.0 - distance( vec2( -10.0,-5.0) , raypos.xz) * 2.0 ) * 0.8;
    
    float disp = texture( iChannel0, raypos.xz * 0.01 ).r;
//    
    float dome = r - length( raypos );
    return vec4( min( raypos.y - w - disp * 4.0, dome),0,0,0);
}



vec4 getlight( vec3 eye, vec3 normal, vec3 position, vec3 lightpos, vec4 lightcolour  )
{
    float d = distance( lightpos, position );
    vec3 n = normalize( lightpos - position  );
    
    vec4 spec = pow( max( dot( normalize( n - eye ), normal ), 0.0 ), 16.0 ) * vec4(1.0,1.0,1.0,1.0);
   
    
    return max( dot( normal, n ), 0.0 ) * lightcolour + spec * 0.25;   
    
}

vec4 matmin( vec4 o0, vec4 o1 )
{
    if ( o0.x < o1.x )
    { 
        return o0;
    }
    
    return o1;
}


vec4 smin( vec4 a, vec4 b, float k )
{
    float res = exp( -k*a.x ) + exp( -k*b.x );
    float blend = -log( res )/k;
    float aw = exp( -k*a.x ) / res;
    float bw = exp(-k*b.x) / res;
    
  	//vec3 material = a.x/(a.x+b.x) * a.yzw + b.x/(a.x+b.x) * b.yzw;
    //return vec4( blend, material ); */
    vec4 colour = aw * a + bw * b;
    colour.x = blend;
    return colour;
}

vec4 softmin( vec4 a, vec4 b, float d )
{
    if (abs( a.x-b.x ) > d )
    {
        return matmin( a, b );
    }
   	else
    {
        float lerp = abs( a.x - b.x ) / d;
        return matmin(a,b) * lerp +  (a+b)/2.0 * ( 1.0 - lerp );
        
    }
}



vec4 sdf( vec3 raypos )
{
 //   float e = abs( cos( iTime ) ) * 10.0;
    return smin( cylinder( vec3( 20.0, 10.0, 0.0), vec2( 5.0, 20.0), raypos ),
                smin( box( vec3( -20, 0.0, 20), vec3( 10.0,10.0,10.0), raypos ),
                    smin( sphere( vec3( 0, 0.0, -20 ), 10.0, raypos ),
                	 stage( raypos, -10.0, 100.0 ), 1.0
                   ),1.0
               ),0.25
    );
    
    //return  stage( raypos, -10.0, 200.0 );
}

vec3 grad( vec3 raypos, float delta )
{
    float dx =  sdf( raypos + vec3( delta, 0,0 ) ).x - sdf( raypos - vec3( delta,0,0 ) ).x;
    float dy =  sdf( raypos + vec3( 0, delta,0 ) ).x - sdf( raypos - vec3( 0,delta,0 ) ).x;
    float dz =  sdf( raypos + vec3( 0,0, delta ) ).x - sdf( raypos - vec3( 0,0,delta ) ).x;
    return vec3( dx,dy,dz );
}


vec4 contact( vec3 position, vec3 normal, float scale )
{
    float s = sdf( position + normal * scale ).x;
    return  (s/scale) * vec4( 1.0,1.0,1.0,1.0);
    
}

vec4 shadowlight( vec3 eye, vec3 normal, vec3 origin,  vec3 lightpos, vec4 colour, float ep )
{
   vec3 ray = normalize( lightpos - origin);
    
    vec4 amb = contact( origin, normal, 4.0 ) * 0.25 ;
    vec3 p = origin + ray * 2.0;
    for ( int i = 0; i < 512; i++ )
    {
        vec4 sd = sdf(p);
        float ld = distance( p, lightpos );
        float step = min( sd.x, ld );
        if ( sd.x  <  ep )
        {
           return amb;
        }
        else if ( ld < ep )
        {
           return getlight( eye, normal, origin, lightpos, colour ) + amb;
        }
        
        p += ray * step;
    } 
    
    
    return getlight( eye, normal, origin, lightpos, colour ) + amb;
}

vec4 getDiffuse( float d )
{
   // return vec4( 1.0-d,1.0-d,1.0-d,1.0);
   return (1.0-d) * vec4( 1.0,0.7,0.7,1.0) + d * vec4( 0.9,0.9,1.0,1.0) *d;
}

vec4 reflectRay( vec3 eye, 
                 vec3 normal, 
                 vec3 origin,
                 vec4 colour,
                 vec3 lightpos, 
                 float ep )
{
   vec3 ray = reflect( eye, normal );
    
    vec3 p = origin + ray * 2.0;
    for ( int i = 0; i < 512; i++ )
    {
        vec4 sd = sdf(p);
        float step =sd.x;
        if ( step  <  ep )
        {
           vec3 normal = normalize( grad( p, 0.1 ) );
           return getlight( p, normal, p, lightpos, colour ) * getDiffuse( sd.y );
        }
        
        p += ray * step;
    } 
    return vec4(0,0,0,1.0);
   
}



vec4 march( vec3 ray, vec3 origin, float ep )
{
    vec3 p = origin;
    vec3 eye = normalize( ray );
    for ( int i = 0; i < 512; i++ )
    {
        vec4 step = sdf(p);
        if ( step.x  <  ep )
        {
            vec4 ref = vec4(0,0,0,0);
            vec3 normal = normalize( grad( p, 0.1 ) );
            vec4 lightcol = vec4(1.0,1.0,1.0,1.0) * 0.8;
            if ( step.w > 0.0 )
            {
            	ref = reflectRay( eye, normal, p, lightcol,  vec3( -10,20,-10 ), 0.1 ); 
            }
            
 //           vec4 cube =  texture( iChannel0, reflect( eye, normal ) ); //reflect( eye, normal ) );
 //           return //shadowlight( eye, normal, p,  vec3( 100,100,100 ), vec4(0.5,0.5,0,1.0 ), ep) + 
   return    shadowlight( eye, normal, p,  vec3( -10,50,-10 ), lightcol, ep) 
            * getDiffuse( step.y ) + ref * step.w;
           // return cube *  contact( p, normal, 4. );
        }
        
        p += ray * step.x;
    }
    
    return vec4(0.0,0,0,1);
}

vec3 rotatevecY( vec3 vec, float angle )
{
    vec3 m0 = vec3( -cos( angle ), 0, sin( angle ));
    vec3 m1 = vec3( 0            , 1.0,   0      );
    vec3 m2 = vec3( sin( angle ), 0, cos( angle ) );
    
    return vec3(  dot( m0, vec ), dot( m1, vec ), dot( m2, vec )) ;
} 


void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
	vec2 uv = fragCoord.xy / iResolution.xy;
    
    float aspect = iResolution.y / iResolution.x;
    
    vec3 origin = vec3(0.0, 2, -50.0 + iMouse.y / iResolution.y * 100.0);
    vec3 ray = vec3( uv.x - 0.5, (uv.y - 0.5) * aspect, 0.5 );
    

    
    ray = rotatevecY( ray, iMouse.x / iResolution.x * 8.0 );
    origin = rotatevecY( origin,  iMouse.x / iResolution.x * 8.0  );

    
	fragColor = march( ray, origin, 0.25);
}
