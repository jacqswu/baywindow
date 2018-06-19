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
    const string        VIDEO_FILES[1] = {
        "Pexels_Koi",
//        "Pexels_Jellyfish",
//        "Pexels_Clouds",
//        "Fish-Tank",
//        "Candolim-Beach",
//        "Ground-Zero",
//        "Skate",
//        "Flowers",
//        "Summer Breeze",
//        "Milky Way Glowing At Night",
//        "Tulips_are_Here",
//        "Red",
//        "Oculus",
    };
    int                 VIDEO_ARRAY_SIZE;
    int                 currentBitmapIdx;
    int                 posX, posY;
    int                 vidW, vidH;
    float               scale;
    
    // mosaic
    float               res;
    bool                resToggle;
    ofImage             screenImage;
    
    // dev tools
    void drawDevStats();
    bool                DEV_DRAW_STATS;
    const int           DEV_LINE_X = 15;
    const int           DEV_LINE_Y = 15;
    
    // printout
    void printImage();
    ofImage             imgPrint;
    const string        PRINT_FOLDER_NAME = "prints/";
    const string        PRINT_EXT = ".png";
    
    // shuffle vids
    void nextWord();
    bool                bw;
    bool                pause;
    
    // keys
    bool                isDevKey(int key);
    bool                isToggleKey(int key);
    bool                isPauseKey(int key);
    bool                isCenterKey(int key);
    bool                isPrintKey(int key);
    bool                isNextKey(int key);
    bool                isResetKey(int key);
    bool                isBlackWhiteKey(int key);
    bool                isZeroKey(int key);
    
    // unused
    ofFbo fbo;
    float fboTime;
    //    ofxSyphonServer mainOutputSyphonServer;
};



