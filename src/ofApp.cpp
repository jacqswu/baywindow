#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(BKGD_COLOR);
    ofSetColor(BKGD_COLOR);
    VIDEO_ARRAY_SIZE = sizeof(VIDEO_FILES)/sizeof(VIDEO_FILES[0]);
    
    loadVideos();
    DEV_DRAW_STATS = false;
    currentBitmapIdx = 0;
    posX = 0;
    posY = 0;
    scale = 1.0;
    resToggle = false;
    bw = false;
    pause = false;
    
    //    mainOutputSyphonServer.setName("Screen Output");
}

//--------------------------------------------------------------
void ofApp::loadVideos() {
    videos.resize(VIDEO_ARRAY_SIZE);
    for ( int i=0; i<VIDEO_ARRAY_SIZE; i++ ) {
        //with extension
        videos[i].load(VIDEO_FOLDER+VIDEO_FILES[i]+VIDEO_EXT);
//        videos[i].load(VIDEO_FOLDER+VIDEO_FILES[i]);
        
        videos[i].setVolume(0);
        videos[i].setPixelFormat(OF_PIXELS_RGBA);
        videos[i].play();
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    
    ofSetColor(0xFFFFFF);
    videos[currentBitmapIdx].setPaused(pause);
    videos[currentBitmapIdx].update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    if(resToggle){
        res = 5.0;
    } else{
        res = 25.0;
    }
    
    vidW = int(videos[currentBitmapIdx].getWidth());
    vidH = int(videos[currentBitmapIdx].getHeight());
    
    // resize videos from 1280x720 to screen height
    videos[currentBitmapIdx].draw(posX, posY, ofGetHeight()*scale*vidW/vidH, ofGetHeight()*scale);
    
    // now, take a "screenshot" of the frame
    screenImage.grabScreen(0,0,ofGetWidth(),ofGetHeight());
    
    // resize the screenshot
    screenImage.resize(res*5,res*5);
    screenImage.update();
    
    //  draw pixelated image at fullscreen
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
            if(bw){
                color1.setSaturation(0);
            }
            //                        color1.invert();
            
            //Force threshold
//             if((color1.r+color1.g+color1.b) < 382){
//             color1 = 0;
//             }
//             else{
//             color1 = 255;
//             }

            //            color1.a = alpha;
            ofSetColor(color1);
            ofDrawTriangle(x * width, y * height, x * width + width, y * height, x * width + width/2, y * height + height/2);
            
            
            // RIGHT TRIANGLE ----------------------------------------------
            
            ofColor color2 = screenImage.getColor(x*5+3,y*5+2);
            if(bw){
                color2.setSaturation(0);
            }
            //                        color2.invert();
            
            //Force threshold
//             if((color2.r+color2.g+color2.b) < 382){
//             color2 = 0;
//             }
//             else{
//             color2 = 255;
//             }

            //            color2.a = alpha;
            ofSetColor(color2);
            ofDrawTriangle(x * width + width, y * height, x * width + width, y * height + height, x * width + width/2, y * height + height/2);
            
            // BOTTOM TRIANGLE ----------------------------------------------
            
            ofColor color3 = screenImage.getColor(x*5+3,y*5+4);
            if(bw){
                color3.setSaturation(0);
            }
            //                        color3.invert();
            
            //Force threshold
//             if((color3.r+color3.g+color3.b) < 382){
//             color3 = 0;
//             }
//             else{
//             color3 = 255;
//             }

            //            color3.a = alpha;
            ofSetColor(color3);
            ofDrawTriangle(x * width + width/2, y * height + height/2, x * width + width, y * height + height, x * width, y * height + height);
            
            // LEFT TRIANGLE ----------------------------------------------
            
            ofColor color4 = screenImage.getColor(x*5,y*5+2);
            if(bw){
                color4.setSaturation(0);
            }
            //                        color4.invert();
            
            //Force threshold
//             if((color4.r+color4.g+color4.b) < 382){
//             color4 = 0;
//             }
//             else{
//             color4 =255;
//             }

            //            color4.a = alpha;
            ofSetColor(color4);
            ofDrawTriangle(x * width, y * height, x * width + width/2, y * height + height/2, x * width, y * height + height);
        }
    }
    //    mainOutputSyphonServer.publishScreen();
    
    if(DEV_DRAW_STATS){
        drawDevStats();
    }
}

//--------------------------------------------------------------
void ofApp::drawDevStats() {
    ofSetHexColor(0x000000);
//    // print FPS
//    ofDrawBitmapString("FPS: " + ofToString(ofGetFrameRate()), DEV_LINE_X, 20+DEV_LINE_Y*1);

    ofDrawBitmapString("SPACEBAR: Play/Pause", DEV_LINE_X, DEV_LINE_Y*2);
    ofDrawBitmapString("UP/DOWN: Resolution", DEV_LINE_X, DEV_LINE_Y*3);
    ofDrawBitmapString("LEFT/RIGHT: Position", DEV_LINE_X, DEV_LINE_Y*4);
    ofDrawBitmapString("=/-: Scale", DEV_LINE_X, DEV_LINE_Y*5);
    ofDrawBitmapString("C: Center", DEV_LINE_X, DEV_LINE_Y*6);
    ofDrawBitmapString("Z: Zero", DEV_LINE_X, DEV_LINE_Y*7);
    ofDrawBitmapString("N: Next", DEV_LINE_X, DEV_LINE_Y*8);
    ofDrawBitmapString("B: Black/white", DEV_LINE_X, DEV_LINE_Y*9);
    ofDrawBitmapString("P: Print", DEV_LINE_X, DEV_LINE_Y*10);
    ofDrawBitmapString("R: Reset", DEV_LINE_X, DEV_LINE_Y*11);
    ofDrawBitmapString("X: Close Stats", DEV_LINE_X, DEV_LINE_Y*12);
    
    ofDrawBitmapString("Position: ("+ofToString(posX)+","+ofToString(posY)+")", DEV_LINE_X, DEV_LINE_Y*14);
    ofDrawBitmapString("Scale: "+ofToString(scale), DEV_LINE_X, DEV_LINE_Y*15);
    
//    // avg, max, min fps since start
//    ofDrawBitmapString("FPS over " + ofToString(int(ofGetElapsedTimef()))
//                       + "s: avg=" + ofToString(fps_sum/(ofGetFrameNum()-FPS_IGNORE_INITIAL_FRAMES))
//                       + " max=" + ofToString(fps_max) + " min=" + ofToString(fps_min)
//                       ,20,20+15);
//    // num of simultaneously open video files
//    ofDrawBitmapString("# files: " + ofToString(Config::PUBLIC_NUM_PEOPLE),20,20+15*2);
//    // num of video frames per display frame
//    ofDrawBitmapString("# vixels: " + ofToString(pplpic.vixelMap.size()),20,20+15*3);
//    // vixel size
//    ofDrawBitmapString("vixel: " + ofToString(Config::Config::VIXEL_SIZE) + " x " + ofToString(Config::Config::VIXEL_SIZE),20,20+15*4);
//    // display resolution
//    ofDrawBitmapString("scrn: " + ofToString(ofGetWidth()) + " x " + ofToString(ofGetHeight()),20,20+15*5);
//    // save to disk queue
//    ofDrawBitmapString("disk q: " + ofToString(diskRecorder.q.size()),20,20+15*6);
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
    
    // 'X': draw/hide stats
    if(isDevKey(key)){
        DEV_DRAW_STATS = !DEV_DRAW_STATS;
    }
    
    // SPACEBAR: pause
    if(isPauseKey(key)){
        pause = !pause;
    }
    
    // UP DOWN LEFT RIGHT ARROWS: video position
    else if(key == OF_KEY_DOWN){
        posY += 10;
    }
    else if(key == OF_KEY_UP){
        posY -= 10;
    }
    
    else if(key == OF_KEY_LEFT){
        posX -= 10;
    }
    else if(key == OF_KEY_RIGHT){
        posX += 10;
    }
    
    // 'T': change resolution
    else if(isToggleKey(key)){
        resToggle = !resToggle;
    }
    
    // + -: video scale
    else if(key == '='){
        scale += 0.1;
    }
    else if(key == '-'){
        scale -= 0.1;
    }
    
    // 'C': center video
    else if(isCenterKey(key)) {
        posX = int((ofGetWidth() - ofGetHeight()*vidW/vidH)/2);
    }
    
    // 'Z': zero video
    else if(isZeroKey(key)) {
        posX = 0;
    }
    
    // 'B': black and white
    else if(isBlackWhiteKey(key)) {
        bw = !bw;
    }
    
    // 'N': next word bitmap
    else if(isNextKey(key)) {
        nextWord();
    }
    
    // 'P': print
    else if (isPrintKey(key)) {
        printImage();
    }
    
    // 'R': reset
    else if (isResetKey(key)) {
        posX = 0;
        posY = 0;
        res = 25.0;
        scale = 1.0;
    }
}

bool ofApp::isDevKey(int key) {
    return key == 'x';
}

bool ofApp::isToggleKey(int key) {
    return key == 't';
}

bool ofApp::isPauseKey(int key) {
    return key == ' ';
}

bool ofApp::isNextKey(int key) {
    return key == 'n';
}

bool ofApp::isCenterKey(int key) {
    return key == 'c';
}

bool ofApp::isZeroKey(int key) {
    return key == 'z';
}

bool ofApp::isBlackWhiteKey(int key) {
    return key == 'b';
}

bool ofApp::isPrintKey(int key) {
    return key == 'p';
}

bool ofApp::isResetKey(int key) {
    return key == 'r';
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


