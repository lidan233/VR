// Constants
#define PI 3.1415
#define MOD2 vec2(3.07965, 7.4235)

// Raymarching
float minPrimStepSize = 0.4 ;
const int primNumSamples = 150 ;

// Colours
const vec3 obsidianCol = vec3(30./255., 31./255., 30./255.) ;
const vec3 sunCol = vec3(1.0,1.0,1.0) ;
const vec3 skyCol = vec3(206./255., 146./255., 14./255.) ;
const float ambientCol = 0.3 ;

// Sun
const float lightElev = 20. * 3.14/180. ;
const float lightAzi = 100. * 3.14/180. ;
const vec3 lightDir = vec3(cos(lightAzi)*cos(lightElev),sin(lightElev),sin(lightAzi)*cos(lightElev));

// Terrain
const int octavesTerrain =  12 ;
const float sharpness = 0.35 ;
const float offset = 0.85 ;

// Lava

vec2 rot2D(vec2 p, float angle) {
    angle = radians(angle);
    float s = sin(angle);
    float c = cos(angle);
    
    return p * mat2(c,s,-s,c);  
}

float rand(vec2 c){
    return fract(sin(dot(c.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

float hash12(vec2 p) {
	p  = fract(p / MOD2);
    p += dot(p.xy, p.yx+19.19);
    return fract(p.x * p.y);
}

const vec2 add = vec2(1.0, 0.0);

float noise( in vec2 x ) {
    vec2 p = floor(x);
    vec2 f = fract(x);
    f = f*f*(3.0-2.0*f);
    float res = mix(mix( hash12(p),          hash12(p + add.xy),f.x),
                    mix( hash12(p + add.yx), hash12(p + add.xx),f.x),f.y);
    return res;
}

float noiseEmber(vec2 p) {
    return hash12(p);
}

float smoothNoiseEmber(vec2 p) {
    vec2 p0 = floor(p + vec2(0.0, 0.0));
    vec2 p1 = floor(p + vec2(1.0, 0.0));
    vec2 p2 = floor(p + vec2(0.0, 1.0));
    vec2 p3 = floor(p + vec2(1.0, 1.0));
    vec2 pf = fract(p);
    return mix( mix(noise(p0), noise(p1), pf.x),mix(noise(p2), noiseEmber(p3), pf.x), pf.y);
}

const int octavesEmber = 5 ;

float fbmEmber(in vec2 p) {
    float f=0.0;
    for(int i=0; i < octavesEmber; ++i)
        f+=smoothNoiseEmber(2.0*p*exp2(float(i)))/exp2(float(i+1));
    return f;
}

float sampleField(vec3 position) {
  float noiseVal = 0.0 ;
  float amplitude = 1.0 ;
  float scaling = 75. ;
  float freq = 0.009 ;
  float lac = 2.0 ;
  for (int i = 0 ; i < octavesTerrain ; ++i) {
    noiseVal += amplitude * noise(freq*position.xz) ;
    amplitude /= lac ;
    freq *= lac ;
  }
    
  // Islandise terrain //
  noiseVal -= offset ;
  noiseVal = clamp(noiseVal,0.,1.5) ;
  noiseVal = pow(sharpness, noiseVal) ;
  noiseVal = 1.0 - (noiseVal) ;
  return noiseVal * scaling ;
}

#define time iTime*0.1
float hash( float n )
{
    return fract(sin(n)*43758.5453123);
}
float hash21(in vec2 n){ return fract(sin(dot(n, vec2(12.9898, 4.1414))) * 43758.5453); }
mat2 makem2(in float theta){float c = cos(theta);float s = sin(theta);return mat2(c,-s,s,c);}
float noiseLava( in vec2 x )
{
    vec2 p = floor(x);
    vec2 f = fract(x);

    f = f*f*(3.0-2.0*f);

    float n = p.x + p.y*57.0;

    float res = mix(mix( hash(n+  0.0), hash(n+  1.0),f.x),
    mix( hash(n+ 57.0), hash(n+ 58.0),f.x),f.y);

    return res*255.0;
}


float sampleFreq = 0.2 ;
vec2 gradn(vec2 p) {
	float ep = .09;
	float gradx = noiseLava(sampleFreq*vec2(p.x+ep,p.y))-noiseLava(sampleFreq*vec2(p.x-ep,p.y));
	float grady = noiseLava(sampleFreq*vec2(p.x,p.y+ep))-noiseLava(sampleFreq*vec2(p.x,p.y-ep));
	return vec2(gradx,grady);
}


// ...... Taken from https://www.shadertoy.com/view/MdBSRW
#define TEMPERATURE 2200.0

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


// ..... Taken from https://www.shadertoy.com/view/lslXRS
float flowFBM(in vec2 p)
{
	float z=2.;
	float rz = 0.;
	vec2 bp = p;
	for (float i= 1.;i < 9.;i++ ){
		//primary flow speed
		p += time*.006;
		//secondary flow speed (speed of the perceived flow)
		bp += time*0.00009;
		//displacement field (try changing time multiplier)
		vec2 gr = gradn(i*p*1.4+time*0.1);
		//rotation of the displacement field
		gr*=makem2(time*2.-(0.05*p.x+0.03*p.y)*40.);
		//displace the system
		p += gr*.5;
		//add noise octave
		rz+= (sin(noise(p)*7.)*0.5+0.5)/z;
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


vec3 getFieldNormal(in vec3 cameraPos, in vec3 direction, float dist) {
  float p = min(.3, .0005+.00005 * dist*dist);
  vec3 position = cameraPos + direction * dist ;
  vec3 nor = vec3(0.0,sampleField(position), 0.0);
  vec3 v2 = nor-vec3(p,sampleField(position+vec3(p,0.0,0.0)), 0.0);
  vec3 v3 = nor-vec3(0.0,sampleField(position+vec3(0.0,0.0,-p)), -p);
  nor = cross(v2, v3);
  return normalize(nor);   
}

vec3 calcSkyCol(in vec3 direction)
{
	float sunAmount = max( dot(direction, lightDir), 0.0 );
	float v = pow(1.0-max(direction.y,0.0),5.)*.5;
	vec3  sky = vec3(v*sunCol.x*0.4+skyCol.x, v*sunCol.y*0.4+skyCol.y, v*sunCol.z*0.4+skyCol.z);
	sky = sky + sunCol * pow(sunAmount, 6.5)*.32;
	sky = sky+ sunCol * min(pow(sunAmount, 1600.), .3)*.65;
	return sky;
}

float fineRayMarchBinarySearch(vec3 startPos, vec3 direction, in vec2 rayDists, out float height) {
    float halfwayT;
	for (int n = 0; n < 4; n++)
	{
		halfwayT = (rayDists.x + rayDists.y) * .5;
		vec3 p = startPos + halfwayT*direction;
		if ((height = sampleField(p)) - p.y > 0.5) {
			rayDists.x = halfwayT;
		} else {
			rayDists.y = halfwayT;
		}
	}
	return rayDists.x;
}

bool coarseRayMarch(vec3 startPos, vec3 direction, out float rayDist, out float height) {
    vec3 position = startPos ;
    bool intersected = false ;
    rayDist = 0.0 ;
    float oldRayDist = rayDist ;
    
    for (int i = 0 ; i < primNumSamples ; ++i) {
        if (position.y > 66.) {
            break ;
        }
		if ((height = sampleField(position)) - position.y > 0.5) {            
            intersected = true ;
            break ;
        } else {
            oldRayDist = rayDist ;
            float delta = max(minPrimStepSize,height*0.001) + (rayDist*0.025);
		    rayDist += delta;
            position = (rayDist)*direction + startPos ;
        }
    }
    
    if (intersected) {
       rayDist = fineRayMarchBinarySearch(startPos,direction,vec2(rayDist,oldRayDist),height) ;   
    }
    
    return intersected ;
}

// Calculate sun light...
vec3 calcColour(in vec3 pos, in vec3 normal, in vec3 eyeDir, float dis, float height)
{
  	float h = dot(lightDir,normal);
	float c = max(h, 0.0)+ambientCol;
    vec2 samplePosition = (eyeDir * dis + pos).xz  ;
    vec3 lavCol = blackbody(flowFBM(samplePosition*0.005)) ;
    float specular = 0.0 ;
    vec3 col ;
    if (height > 0.0) {
        specular = 0.6 ;
        col = obsidianCol ;
        col = col * (sunCol + lavCol * 6.0/(height)) * c ;
        if (h  > 0.0) {
          vec3 R = reflect(lightDir, normal);
	  	  float specAmount = pow( max(dot(R, normalize(eyeDir)), 0.0), 3.0)*specular;
		  col = mix(col, sunCol , specAmount);
        }
    } else {
        col = lavCol ;
    }
    
    return col ;
}

vec3 calcFog( in vec3  rgb, in float dis, in vec3 dir) {
	float fogAmount = exp(-dis* 0.002);
	return mix(calcSkyCol(dir), rgb, fogAmount);
}
    

void mainImage( out vec4 fragColor, in vec2 fragCoord)
{    
    vec2 uv = (fragCoord.xy - iResolution.xy * .5) / iResolution.y;
    vec2  m = 2.*((iMouse.xy / iResolution.xy) - 0.5);
    
    if (iMouse.xy == vec2(0)) {
       m.y = 0.0 ;   
    }
    
    vec3 dir = vec3(uv, 1.);
    dir.yz = rot2D(dir.yz,  90. * m.y);
    dir.xz = rot2D(dir.xz, 180. * m.x + 180.);
    dir = normalize(dir) ;

    float offset = iTime ;
    vec3 cameraPos = vec3(0.0,0.0,3.0*offset) ;
    float heightOffset = sampleField(cameraPos) ;
    cameraPos.y = 20.0 + heightOffset ;
    float rayInterDist = -1.0 ;
    float height = 0.0 ;
	bool hasIntersected = coarseRayMarch(cameraPos,dir,rayInterDist,height) ;
    vec3 col = vec3(0.0) ;
    if (hasIntersected) {
      vec3 normal = getFieldNormal(cameraPos,dir,rayInterDist) ;
      col = calcColour(cameraPos + dir*rayInterDist, normal, dir, rayInterDist, height) ;
    } else {
      col = calcSkyCol(dir) ;     
    }
    col =  calcFog(col,rayInterDist,dir) ;
    
    // Taken from 
    vec3 embers=vec3(1.0,0.35,0.04)*smoothstep(0.77+sin(time*5.0)*0.01+sin(time)*0.01,1.0,fbmEmber(uv*10.0+vec2(cos(uv.y*0.8+time*1.0)*10.0,time*40.0)));
    embers+=vec3(1.0,0.35,0.04)*smoothstep(0.77+sin(time*82.0)*0.01+sin(time*1.2)*0.01,1.0,fbmEmber(vec2(100.0)+uv*8.0+vec2(time*1.0+cos(uv.y*0.3+time*1.0)*10.0,time*30.0)));

	fragColor = vec4(col + 8.*embers,1) ;
}