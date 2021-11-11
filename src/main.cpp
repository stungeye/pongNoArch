#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main() {
	ofSetupOpenGL(800, 500, OF_WINDOW); // <-------- setup the GL context
	ofRunApp(new ofApp());
}
