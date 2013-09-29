#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"


extern "C" {
#include "flam3.h"
}


class testApp : public ofBaseApp{
	
	public:
		
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
	
	// void audioReceived 	(float * input, int bufferSize, int nChannels); 

		
		float 	counter;
	int framecount;
	int fullscreen;
		int nsamples;
		double *samples;
		int parity;
		int seed;
	int momode;
		FILE *out;
		int ncps;
	int transp;
	    flam3_genome *cps;
	    flam3_genome *cpv;
	    flam3_genome cp;
	    int gi, gj;
	float mpx, mpy;
	float mmpx, mmpy;
	float speed;
	float audio1;
	
	
	float * left;
	float * right;
	
	ofSoundPlayer mySound;

	
};

#endif
	
