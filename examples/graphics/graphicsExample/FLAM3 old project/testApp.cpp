#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
	counter = 0;
	ofBackground(255,255,255);
	nsamples = 25000;
	// nsamples = mnsamples;
	seed = 0;
	gi = 0;
	gj = 0;
	transp = 60;
	ofSetWindowTitle("LIV3 FLAM3");
	samples= (double *) malloc(sizeof(double)*nsamples*8);
	parity = 0;
	ofBackground(0,0,0);
	framecount = 0;
	mpx = mpy = 0.0;
	mmpx = mmpy = 0.0;
	fullscreen = 0;
	momode = 0;
	speed = 1.1;
	ofSetFrameRate(30);
	cpv = (flam3_genome *) malloc(sizeof(flam3_genome)*2);
	{
		FILE *in;
		char *inf = "/Users/spot/live.flam3";
		
		in = fopen(inf, "rb");
		
		cps = flam3_parse_from_file(in, inf, flam3_defaults_on, &ncps);
		// 
		
		for (int i = 0; i < ncps; i++) {
			cps[i].time = (double) i;
		}
		if (NULL == cps) {
			// exit(1);
		}
	}
	flam3_copy(&cp, &cps[gi]);
	/*
	ofSoundStreamSetup(0,2,this, 44100, 256, 4);	
	left = new float[256];
	right = new float[256];
	 */
	
}


//--------------------------------------------------------------
void testApp::update(){

	counter = counter + speed;
}

//--------------------------------------------------------------
void testApp::draw(){

	
	ofEnableAlphaBlending();		
	// ofEnableSmoothing();
    
	int cohere = 1;
	double t0, t1, t2;
	if (!cohere) {
	  t0 = gi + cos(.3*counter)/2+0.5+(mpx-0.5)/2;
	  t1 = gj + cos(.81*counter)/2+0.5;
	  t2 = cos(counter*1.13)/2+0.5+(mpy-0.5)/2;
	  flam3_interpolate(cps, ncps, t0, &cpv[0]);
	  // flam3_print(out, &cp, NULL, 0);
	  // fflush(out);
	  if (1) {
		flam3_copy(&cpv[1], &cps[gj]);
	  } else {
		flam3_interpolate(cps, ncps, t1, &cpv[1]);
	  }
	  cpv[0].time = 0.0;
	  cpv[1].time = 1.0;
	  flam3_interpolate(cpv, 2, t2, &cp);
	} else {
	  flam3_rotate(&cp, 1+speed*audio1*10);
	}
	
	randctx rc;
	unsigned short xform_distrib[CHOOSE_XFORM_GRAIN];
	
	/* Set up the isaac rng */
	for (int lp = 0; lp < RANDSIZ; lp++)
		rc.randrsl[lp] = seed;
	
	irandinit(&rc,1);
	
	prepare_xform_fn_ptrs(&cp,&rc);
	flam3_create_xform_distrib(&cp, xform_distrib);
	
	framecount++;
	
	double *s = samples + (parity?(4*nsamples):0);
	
	s[0] = flam3_random_isaac_11(&rc);
	s[1] = flam3_random_isaac_11(&rc);
	s[2] = flam3_random_isaac_01(&rc);
	s[3] = flam3_random_isaac_01(&rc);
	
	switch (gi) {
		case 0:
			cp.xform[4].var[5] = mpx;
			cp.xform[3].var[8] = mpy;
			
		case 1:
			cp.xform[5].var[1] = mpx;
			cp.xform[12].c[2][0] = mpy;
			break;
			
		case 2:
			cp.xform[8].var[1] = mpx;
			cp.xform[8].juliaN_power = mpy + 0.5;
			break;
		case 3:
			cp.xform[0].c[0][0] = -mpx+0.5;
			cp.xform[0].c[1][1] = -mpy+0.5;
			break;
		case 4:
			cp.xform[2].color[0] = 0.2;
			cp.xform[2].c[0][0] = mpy;
			cp.xform[3].var[1] = -mpx;
			cp.xform[2].c[1][0] = 1/(mpx+0.1);
			break;
		case 5:
			cp.xform[0].var[VAR_DISC] = mpx;
			cp.xform[1].c[2][0] = 2*(mpx-0.5);
			cp.xform[1].c[2][1] = 2*(mpy-0.5);
			break;
		case 6:
			cp.xform[0].rectangles_x = mpx;
			cp.xform[0].rectangles_y = mpy;
			cp.xform[0].c[0][0] = mpx + 0.5;
			cp.xform[0].c[1][1] = mpy - 1.5;
			cp.xform[10].c[0][0] = mpx/2 - 1.0;
			cp.xform[10].c[1][1] = mpy/2 - 1.0;
			break;
		case 7:
			cp.xform[3].c[2][0] = mpx;
			cp.xform[3].c[2][1] = mpy;
			cp.xform[3].c[0][0] = mpx - 1.5;
			cp.xform[3].c[1][1] = mpy;
			cp.xform[3].var[0] = mpx;
			cp.xform[3].var[1] = mpy;
			break;
		case 8:
			cp.xform[0].c[2][0] = mpx - 0.5;
			cp.xform[0].c[2][1] = mpy - 0.5;
			cp.xform[1].c[0][0] = mpx - 0.5;
			cp.xform[1].c[1][1] = mpy - 0.5;
			cp.xform[2].c[2][0] = mpx - 0.5;
			cp.xform[2].c[2][1] = mpy - 0.5;
			cp.xform[4].juliaN_dist = 1 - mpx;
			cp.xform[5].juliaN_dist = 1 - mpy;
			break;
		case 9:
			cp.xform[0].var[VAR_WAVES] = mpx*2 + 0.2;
			cp.xform[1].var[VAR_DISC] = mpy*2 + 0.1;
			break;
		case 10:
			cp.xform[1].juliaScope_power = 1/(mpx + 0.1);
			cp.xform[1].juliaN_power = 1/(mpy + 0.1);
			break;
		case 1000:
			cp.xform[gj%cp.num_xforms].var[momode%flam3_nvariations] = mpx;
			cp.xform[momode%cp.num_xforms].var[gj%flam3_nvariations] = mpy;
			break;
	}			
			
	
	flam3_iterate(&cp, nsamples, 20, s, xform_distrib, &rc);		
	
	double *s0, *s1;
	
	if (parity) {
		s0 = samples;
		s1 = samples + nsamples * 4;
	} else {
		s0 = samples + nsamples * 4;
		s1 = samples;
	}
	
	ofFill();
	for (int i = 0; i < nsamples-1; i++) {		
		int c = (int)(s0[4*i+2] * CMAP_SIZE);
		if (c < 0) c = 0;
		else if (c > (CMAP_SIZE-1)) c = CMAP_SIZE-1;		
				
		ofSetColor(255*cp.palette[c][0],255*cp.palette[c][1],255*cp.palette[c][2],transp);
		float w = 1.0 + c/32.0;
		w = (w - 1) * 3;
				
		double a0 = s0[4*i] - cp.center[0];
		double a1 = s0[4*i+1] - cp.center[1];
		double a2 = s1[4*i] - cp.center[0];
		double a3 = s1[4*i+1] - cp.center[1];
		double mw = 100 * c;
		a0 *= cp.pixels_per_unit;
		a1 *= cp.pixels_per_unit;
		a2 *= cp.pixels_per_unit;
		a3 *= cp.pixels_per_unit;
		a0 += 640;
		a1 += 400;
		a2 += 640;
		a3 += 400;
		if (cohere) {
			// w = (w-1)*3;
			ofCircle(a0,a1,w);
			ofCircle(a2,a3,w);
			if ((a0-a2)*(a0-a2) + (a1-a3)*(a1-a3) < 10000) {
				ofSetLineWidth(w);
				 ofLine(a0, a1, a2, a3);
			}
			
		} else if (1) {
			w = (w-1)*10;
			ofCircle(a0,a1,w);
			ofCircle(a2,a3,w);
		} else {
			w = (w-1)*8;
			ofRect(a0-w/2,a1-w/2,w,w);
			ofRect(a2-w/2,a3-w/2,w,w);
		}
	}
	parity = !parity;
	
	ofSetLineWidth(1);
	ofSetColor(255,255,255,255);
	float *sp = ofSoundGetSpectrum(64);
	float max = 0.0;
	int maxBand = 0;
	for (int i = 10; i < 64; i++) {
		if (sp[i] > max) {
			max = sp[i];
			maxBand = i;
		}
	}
	if (0)
	for (int i = 10; i < 64; i++) {
		int w=5;
		ofRect(i*w,0,w,100*sp[i]/max);
	}
	if (1) {
		mpx = mmpx + maxBand/64.0;
		mpy = mmpy + sp[30]/max;
	} else {
		mpx = mmpx;
		mpy = mmpy;
	}
	/*
	ofNoFill();
	ofSetLineWidth(1);
	 // Curve from 2nd to 3rd point.
	ofCurve(10, 10,
			100, 10,
			100, 100,
			10, 100);
	 */
	
	
	 
}

//--------------------------------------------------------------
/*
void testApp::audioReceived(float * input, int bufferSize, int nChannels){	
	// samples are "interleaved"
	float max = 0;
	for (int i = 0; i < bufferSize; i++){
		left[i] = input[i*2];
		right[i] = input[i*2+1];
		if (left[i] > max)
			max = left[i];
	}
	audio1 = max;
}
*/


//--------------------------------------------------------------
void testApp::keyPressed  (int key){
	if (key == 's') {
		gi = (gi+1) % ncps;
		flam3_copy(&cp, &cps[gi]);
	} else if (key == 'd') {
		gj = (gj+1) % ncps;
	} else if (key == 'a') {
		momode++;
	} else if (key == 'f') {
		ofToggleFullscreen();
		ofHideCursor();
		fullscreen = !fullscreen;
	} else if (key == OF_KEY_LEFT) {
		speed *= 0.80;
	} else if (key == OF_KEY_RIGHT) {
		speed *= 1.2;
	} else if (key == '1') {
		mySound.loadSound("/Users/Shared/spot/Music/iTunes/iTunes Media/Music/Shpongle/The Remixes/08 once upon the sea of blissful awareness (esionjim rmx).mp3", true);
		mySound.play();
	} else if (key == '2') {
		mySound.loadSound("/Users/Shared/spot/Music/iTunes/iTunes Media/Music/Sheryl Crow/C'mon, C'mon/01 Steve McQueen.mp3", true);
		mySound.play();
	} else if (key == '3') {
		mySound.loadSound("/Users/Shared/spot/Music/iTunes/iTunes Media/Music/Bach/Sonatas & Partitas CD1 [Lydia Mordkovitch]/01 Sonata No. 1 in Sol minor, BWV 1001 - I. Adagio.mp3", true);
		mySound.play();
	} else if (key == '9') {
		mySound.setPosition(mySound.getPosition()-0.02);
	} else if (key == '0') {
		mySound.setPosition(mySound.getPosition()+0.02);
	}

}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	mmpx = x / 1000.0;
	mmpy = y / 800.0;
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}


//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}
