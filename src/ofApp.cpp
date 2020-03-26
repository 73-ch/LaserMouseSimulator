#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){


    for (int i = 0; i < 60; i++) {
        Mouse mouse;
        mouses.push_back(mouse);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    for (auto &m : mouses) {
        m.update(mouses, 0.5);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    for (auto &m : mouses) {
        m.draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
