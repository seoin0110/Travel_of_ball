#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    ofSetupOpenGL(1024,768,OF_WINDOW);            // <-------- setup the GL context
    srand((unsigned int)time(NULL)); //랜덤함수를 위한 설정
    ofRunApp(new ofApp());
}
