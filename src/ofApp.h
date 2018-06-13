#pragma once

#include "ofMain.h"
#include "ofxSyphon.h"

class ofApp : public ofBaseApp{
    
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
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    // general
    const int           BKGD_COLOR = 0xFFFFFF;
    
    // video
    void loadVideos();
    ofVideoPlayer vid;
    vector<ofVideoPlayer>    videos;
    const string        VIDEO_FOLDER = "videos/";
    const string        VIDEO_EXT = ".mp4";
    const string        VIDEO_FILES[5] = {
        "clouds.mp4",
        "flower01.mp4",
        "flower02.mp4",
        "flower03.mp4",
        "flower04.mp4"
    };
    int                 VIDEO_ARRAY_SIZE;
    int                 currentBitmapIdx;
    int                 posX;
    int                 vidW, vidH;
    bool                isCenterKey(int key);
    
    // mosaic
    float               res;
    ofImage             screenImage;
    
    // printout
    void printImage();
    ofImage             imgPrint;
    bool                isPrintKey(int key);
    const string        PRINT_FOLDER_NAME = "prints/";
    const string        PRINT_EXT = ".png";
    
    // shuffle vids
    void nextWord();
    bool                isNextKey(int key);
    
    bool                pause;
    
    // unused
    ofFbo fbo;
    float fboTime;
    //    ofxSyphonServer mainOutputSyphonServer;
};



