#pragma once

//#define DEVELOPPER_INFO

#include "ofMain.h"

#include "ofxOpenCv.h"

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
    
    ofVideoPlayer 		vidPlayer;
    
    bool                bPlaying;
    
    unsigned long long  exe_start_time;
    unsigned long long  count_time;
    unsigned long long  pause_start_time;
    unsigned long long  paused_time;
    
    ofTrueTypeFont          font;
    
    vector<string>          keys;
    map<string, int>        numbers;
    map<string, int>        total_numbers;
    map<string, string>     tags;
    vector<int>             timing;
    
    bool                    bCounted;
    int                     section;
    int                     total_ret[4];
    int                     total_counts[4] = {57, 17, 130, 313};
    vector< vector<int> >   rets;

};
