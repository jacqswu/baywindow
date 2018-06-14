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
    const string        VIDEO_FILES[9] = {
        "goldengate01",
        "goldengate02",
        "clouds",
        "flower01",
        "flower02",
        "flower03",
        "flower04",
        "jellyfish01",
        "jellyfish02",
//        "jellyfish03",
//        "jellyfish04",
//        "jellyfish05",
//        "jellyfish06",
//        "jellyfish07",
//        "jellyfish08",
//        "jellyfish09",
//        "sutro01",
//        "pattern01",
//        "pattern06",
//        "pattern02",
//        "pattern03",
//        "pattern04",
//        "pattern05",
//        "lavalamp",
//        "coral01",
//        "waves01",
//        "plant01",
//        "plant02",
//        "plant03",
//        "sunset01",
//        "milkyway01",
//        "milkyway02",
//        "ocean01",
//        "ocean02"
    };
    int                 VIDEO_ARRAY_SIZE;
    int                 currentBitmapIdx;
    int                 posX;
    int                 vidW, vidH;
    float               scale;
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
    bool                bw;
    
    bool                pause;
    
    // unused
    ofFbo fbo;
    float fboTime;
    //    ofxSyphonServer mainOutputSyphonServer;
};



