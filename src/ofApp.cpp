#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(BKGD_COLOR);
    ofSetColor(255);
    VIDEO_ARRAY_SIZE = sizeof(VIDEO_FILES)/sizeof(VIDEO_FILES[0]);
    
    loadVideos();
    currentBitmapIdx = 0;
    posX = 0;
    res = 25.0;
    pause = false;
    
    //    mainOutputSyphonServer.setName("Screen Output");
}

//--------------------------------------------------------------
void ofApp::loadVideos() {
    videos.resize(VIDEO_ARRAY_SIZE);
    for ( int i=0; i<VIDEO_ARRAY_SIZE; i++ ) {
        //        videos[i].load(VIDEO_FOLDER+VIDEO_FILES[i]+VIDEO_EXT);
        videos[i].load(VIDEO_FOLDER+VIDEO_FILES[i]);
        videos[i].setVolume(0);
        videos[i].setPixelFormat(OF_PIXELS_RGBA);
        videos[i].play();
        //        wordBitmaps[i].setImageType(OF_IMAGE_GRAYSCALE);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    
    ofSetColor(255);
    videos[currentBitmapIdx].setPaused(pause);
    videos[currentBitmapIdx].update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    vidW = int(videos[currentBitmapIdx].getWidth());
    vidH = int(videos[currentBitmapIdx].getHeight());
    
    // resize videos from 1280x720 to screen height
    videos[currentBitmapIdx].draw(posX, 0, ofGetHeight()*vidW/vidH, ofGetHeight());
    
    // now, take a "screenshot" of the frame
    screenImage.grabScreen(0,0,ofGetWidth(),ofGetHeight());
    
    // resize the screenshot
    screenImage.resize(res*5,res*5);
    screenImage.update();
    
    //  draw pixelated imag at fullscreen
    screenImage.draw(0,0, ofGetWidth(), ofGetHeight());
    
    
    
    // sample colors from the screenshot, and draw as a grid overlay:
    
    // overlay opacity based on mouse x
    //    float alpha = ofMap(ofGetMouseX(), 0, ofGetWidth(), 0, 255, true);
    //    float alpha = 255;
    //    ofSetColor(0, alpha);
    //    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());    // draw black rect to clear screen
    
    int nCols = res;
    int nRows = res;
    
    // grid square size for drawing:
    float width = ofGetWidth() / (float)nCols;
    float height = ofGetHeight() / (float)nRows;
    
    
    //MATH FOR MOSAIC
    
    for (int y=0; y<nRows; y++) {
        for (int x=0; x<nCols; x++) {
            
            // sample the color of the screenshot at this grid pos
            
            // TOP TRIANGLE ----------------------------------------------
            
            ofColor color1 = screenImage.getColor(x*5+2,y*5);
            //            color1.setSaturation(0);
            //                        color1.invert();
            
            //Force threshold
            /*
             if((color1.r+color1.g+color1.b) < 382){
             color1 = 0;
             }
             else{
             color1 = 255;
             }
             */
            
            //            color1.a = alpha;
            ofSetColor(color1);
            ofDrawTriangle(x * width, y * height, x * width + width, y * height, x * width + width/2, y * height + height/2);
            
            
            // RIGHT TRIANGLE ----------------------------------------------
            
            ofColor color2 = screenImage.getColor(x*5+3,y*5+2);
            //            color2.setSaturation(0);
            //                        color2.invert();
            
            //Force threshold
            /*
             if((color2.r+color2.g+color2.b) < 382){
             color2 = 0;
             }
             else{
             color2 = 255;
             }
             */
            
            //            color2.a = alpha;
            ofSetColor(color2);
            ofDrawTriangle(x * width + width, y * height, x * width + width, y * height + height, x * width + width/2, y * height + height/2);
            
            // BOTTOM TRIANGLE ----------------------------------------------
            
            ofColor color3 = screenImage.getColor(x*5+3,y*5+4);
            //            color3.setSaturation(0);
            //                        color3.invert();
            
            //Force threshold
            /*
             if((color3.r+color3.g+color3.b) < 382){
             color3 = 0;
             }
             else{
             color3 = 255;
             }
             */
            
            //            color3.a = alpha;
            ofSetColor(color3);
            ofDrawTriangle(x * width + width/2, y * height + height/2, x * width + width, y * height + height, x * width, y * height + height);
            
            // LEFT TRIANGLE ----------------------------------------------
            
            ofColor color4 = screenImage.getColor(x*5,y*5+2);
            //            color4.setSaturation(0);
            //                        color4.invert();
            
            //Force threshold
            /*
             if((color4.r+color4.g+color4.b) < 382){
             color4 = 0;
             }
             else{
             color4 =255;
             }
             */
            //            color4.a = alpha;
            ofSetColor(color4);
            ofDrawTriangle(x * width, y * height, x * width + width/2, y * height + height/2, x * width, y * height + height);
        }
    }
    //    mainOutputSyphonServer.publishScreen();
}

//--------------------------------------------------------------
void ofApp::printImage() {
    imgPrint.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
    string fileName = ofToDataPath(PRINT_FOLDER_NAME+VIDEO_FILES[currentBitmapIdx]+"_"+ofGetTimestampString("%F %H.%M.%S")+PRINT_EXT);
    imgPrint.save(fileName,OF_IMAGE_QUALITY_HIGH);
    ofLog() << "Saved printout " << fileName;
}

//--------------------------------------------------------------
void ofApp::nextWord(){
    if(currentBitmapIdx == VIDEO_ARRAY_SIZE - 1){
        currentBitmapIdx = 0;
    } else {
        currentBitmapIdx++;
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    // SPACEBAR: pause
    if(key == ' '){
        pause = !pause;
    }
    
    // UP DOWN ARROWS: change resolution
    else if(key == OF_KEY_DOWN){
        res -= 5;
    }
    else if(key == OF_KEY_UP){
        res += 5;
    }
    
    // LEFT RIGHT ARROWS: video position
    else if(key == OF_KEY_LEFT){
        posX -= 10;
    }
    else if(key == OF_KEY_RIGHT){
        posX += 10;
    }
    
    // 'C': center video
    else if(isCenterKey(key)) {
        posX = int((ofGetHeight()*vidW/vidH)/2)*-1;
    }
    
    // 'N': next word bitmap
    else if(isNextKey(key)) {
        nextWord();
    }
    
    // 'P': print
    else if (isPrintKey(key)) {
        printImage();
    }
}

bool ofApp::isNextKey(int key) {
    return key == 'n';
}

bool ofApp::isCenterKey(int key) {
    return key == 'c';
}

bool ofApp::isPrintKey(int key) {
    return key == 'p';
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


