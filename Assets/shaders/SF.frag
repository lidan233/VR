/*

            Fiery Spikeball
            ---------------

            Making some modifications to Duke's \"Cloudy Spikeball\" port to produce a fiery version.

            I trimmed the original shader down a bit, changed the weighting slightly, made a couple of
            sacrifices to the spike shape to tighten up the distance equation, etc.


            Cloudy Spikeball - Duke
            https://www.shadertoy.com/view/MljXDw

            // port from http://glslsandbox.com/e#1802.0, with some modifications.
            //--------------
            // Posted by las
            // http://www.pouet.net/topic.php?which=7920&page=29&x=14&y=9
            // By the way, the demo is really good. Definitely worth watching.


        */




        mat2 rM; // Rotation matrix.


        // IQ's noise
        float pn( in vec3 p )
        {
            vec3 ip = floor(p);
            p = fract(p);
            p *= p*(3.0-2.0*p);
            vec2 uv = (ip.xy+vec2(37.0,17.0)*ip.z) + p.xy;
            uv = texture2D( iChannel0, (uv+ 0.5)/256.0, -100.0 ).yx;
            return mix( uv.x, uv.y, p.z );
        }

        // FBM
        float fpn(vec3 p) {
            return pn(p*.06125)*.57 + pn(p*.125)*.28 + pn(p*.25)*.15;
        }

        // Spikeball. Using 16 hardcoded points, reflected to give 32 spikes in all.
        float spikeball(vec3 p) {

            // Ball
            float d = length(p)-1.6;

            // Spikes
            p = normalize(p);
            vec4 b = max(max(max(
                abs(vec4(dot(p,vec3(0.526,0.000,0.851)), dot(p,vec3(-0.526,0.000,0.851)),dot(p, vec3(0.851,0.526,0.000)), dot(p,vec3(-0.851,0.526,0.000)))),
                abs(vec4(dot(p,vec3(0.357,0.934,0.000)), dot(p,vec3(-0.357,0.934,0.000)), dot(p, vec3(0.000,0.851,0.526)), dot(p,vec3(0.000,-0.851,0.526))))),
                             abs(vec4(dot(p,vec3(0.000,0.357,0.934)), dot(p,vec3(0.000,-0.357,0.934)), dot(p, vec3(0.934,0.000,0.357)), dot(p,vec3(-0.934,0.000,0.357))))),
                         abs(vec4(dot(p,vec3(0.577,0.577,0.577)), dot(p,vec3(-0.577,0.577,0.577)), dot(p, vec3(0.577,-0.577,0.577)), dot(p,vec3(0.577,0.577,-0.577)))));
            b.xy = max(b.xy, b.zw);
            b.x = pow(max(b.x, b.y), 64.);


            return d - exp2(b.x*(sin(iGlobalTime)*0.25+0.75));
        }


        // Distance function.
        float map(vec3 p) {


            //float c = cos(iGlobalTime), s = sin(iGlobalTime);
            //p.xy=c*p.xy+s*vec2(p.y, -p.x); // Rotate p.xy
            //p.xz=c*p.xz+s*vec2(p.z, -p.x); // Rotate p.xz

            // Performs the same as above. \"rM\" is produced just once, before the raymarching loop.
            // I think it'd be faster, but GPUs are strange, so who knows.
            // Duke tells me that \"r *= rM\" can break in some older browsers. Hence, the longhand.
            p.xy = p.xy*rM;
            p.xz = p.xz*rM;

            return spikeball(p) +  fpn(p*50.+iGlobalTime*15.) * 0.8;
        }

        // See \"Combustible Voronoi\"
        // https://www.shadertoy.com/view/4tlSzl
        vec3 firePalette(float i){

            float T = 1400. + 1300.*i; // Temperature range (in Kelvin).
            vec3 L = vec3(7.4, 5.6, 4.4); // Red, green, blue wavelengths (in hundreds of nanometers).
            L = pow(L,vec3(5.0)) * (exp(1.43876719683e5/(T*L))-1.0);
            return 1.0-exp(-5e8/L); // Exposure level. Set to \"50.\" For \"70,\" change the \"5\" to a \"7,\" etc.
        }


        void mainImage( out vec4 fragColor, in vec2 fragCoord )
        {
           // p: position on the ray
           // rd: direction of the ray
           //
           // Trimmed \"rd\" down. Plus, moved \"ro\" back 6 units to get rid of the \"p.z += 6\" line
           // in the distance equation. Also, reversed the Z-coordinates, because it's a personal preference.
           vec3 rd = normalize(vec3((fragCoord.xy-0.5*iResolution.xy)/iResolution.y, 1.));
           vec3 ro = vec3(0., 0., -8.);

           // ld, td: local, total density
           // w: weighting factor
           float ld=0., td=0., w;

           // t: length of the ray
           // d: distance function
           float d=1., t=0.;

           // Distance threshold.
           const float h = .1;

           // total color
           vec3 tc = vec3(0.);


           // Setting up the matrix outside of the loop, which might save a few cycles.
           float cs = cos(iGlobalTime), si = sin(iGlobalTime);
           rM = mat2(cs, si, -si, cs);
            //p.xy=c*p.xy+s*vec2(p.y, -p.x); // Rotate p.xy
            //p.xz=c*p.xz+s*vec2(p.z, -p.x); // Rotate p.xz

           // Tidied the raymarcher up a bit. Plus, got rid some redundancies... I think.

           // rm loop
           for (int i=0; i<64; i++) {

              // Loop break conditions. Seems to work, but let me know if I've
              // overlooked something. The middle break isn't really used here, but
              // it can help in certain situations.
              if(td>(1.-1./200.) || d<0.001*t || t>12.)break;

              // evaluate distance function
              // Took away the \"0.5\" factor, and put it below.
              d = map(ro+t*rd);

              // check whether we are close enough (step)
              // compute local density and weighting factor
              //const float h = .1;
              ld = (h - d) * step(d, h);
              w = (1. - td) * ld;

              // accumulate color and density
              tc += w*w + 1./50.;  // Different weight distribution.
              td += w + 1./200.;


              // enforce minimum stepsize
              d = max(d, 0.04); // Increased the minimum, just a little.

              // step forward
              t += d*0.5;

           }

           // Fire palette.
           tc = firePalette(tc.x);


           fragColor = vec4(tc, 1.0); //vec4(tc.x+td*2., ld*3., 0, tc.x);
        }
