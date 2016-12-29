#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0,0,0);
    ofSetVerticalSync(true);
    
    vidPlayer.load("7_gacha.mp4");
    vidPlayer.setLoopState(OF_LOOP_NONE);
    vidPlayer.play();
        
    bPlaying = true;
    vidPlayer.setPaused(bPlaying);
    
    font.loadFont("Arial.ttf", 23);
    
    exe_start_time = ofGetElapsedTimeMillis();
    count_time = 0;
    paused_time = 0;
    pause_start_time = ofGetElapsedTimeMillis();
    
    keys.clear();
    numbers.clear();
    tags.clear();
    timing.clear();
    rets.clear();
    
    keys.push_back("Kira_Nizi");
    keys.push_back("Nizi");
    keys.push_back("Gold");
    keys.push_back("Silver");
    
    for(int i = 0; i < keys.size(); i++) {
        numbers[keys[i]] = 0;
        tags[keys[i]] = keys[i];
    }
    
    timing.push_back(0);
    timing.push_back(28000);
    timing.push_back(50000);
    timing.push_back(86000);
    timing.push_back(117000);
    timing.push_back(151000);
    
    bCounted = false;
    section = 0;
    for (int i = 0; i < sizeof(total_ret) / sizeof(int); i++) {
        total_ret[i] = 0;
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    bool bNewFrame = false;
    
    if(!bPlaying) {
        count_time = ofGetElapsedTimeMillis() - exe_start_time - paused_time;
    }
    
    vidPlayer.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofFill();
    
    ofSetHexColor(0xFFFFFF);
    // video play
    vidPlayer.draw(0, 0, ofGetWidth(), ofGetHeight());
    
    //Numbers
    font.drawString("<Today's Counts>",
                    ofGetWidth() * 0.0,
                    ofGetHeight() * 0.1);
    font.drawString("<Total Counts>",
                    ofGetWidth() * 0.69,
                    ofGetHeight() * 0.1);
    int ret[6][4] = {
        {0, 0, 0, 0},
        {0, 0, 1, 0},
        {1, 0, 3, 7},
        {0, 0, 5, 6},
        {0, 1, 5, 5},
        {2, 1, 2, 6}};
    
    if(count_time >= timing[section] && count_time < timing[section + 1]) {
        if(!bCounted) {
            for(int i=0; i<4; i++) {
                total_ret[i] += ret[section][i];
                total_counts[i] += ret[section][i];
            }
        }
        section++;
        bCounted = true;
    } else {
        bCounted = false;
    }
    
    //today's number
    int total_num = 0;
    for(int i = 0; i < 4; i++) {
        total_num += total_ret[i];
    }
    ofSetColor(ofColor::white);
    font.drawString(ofToString(total_num) + " : Totals",
                    ofGetWidth() * 0.05,
                    ofGetHeight() * 0.15 + 30 * (keys.size()));

    
    //total number
    int total_counts_num = 0;
    for(int i = 0; i < 4; i++) {
        total_counts_num += total_counts[i];
    }
    ofSetColor(ofColor::white);
    font.drawString(ofToString(total_counts_num) + " : Totals",
                    ofGetWidth() * 0.73,
                    ofGetHeight() * 0.15 + 30 * (keys.size()));
    
    // Rate
    ofSetColor(ofColor::white);
    font.drawString("<Today's Rate>",
                    ofGetWidth() * 0.0,
                    ofGetHeight() * 0.59);
    for(int i = 0; i < keys.size(); i++) {
        numbers[keys[i]] = total_ret[i];
        if(keys[i] == "Silver") {
            ofSetColor(ofColor::silver);
        } else if(keys[i] == "Gold") {
            ofSetColor(ofColor::gold);
        } else if(keys[i] == "Nizi") {
            ofSetColor(ofColor::royalBlue);
        } else if(keys[i] == "Kira_Nizi") {
            ofSetHexColor(0xFF69B4);
        }
        font.drawString(ofToString(numbers[keys[i]]) + " : " + tags[keys[i]],
                        ofGetWidth() * 0.05,
                        ofGetHeight() * 0.15 + 30 * i);
        if(total_num > 0) {
            ofRect(ofGetWidth() * 0.03,
                   ofGetHeight() * (0.6 + 0.05 * i),
                   ofGetWidth() * 0.2 * total_ret[i] / total_num,
                   ofGetHeight() * 0.04);
            double earn_rate = (double)numbers[keys[i]] / total_num;
            font.drawString(ofToString(earn_rate * 100, 1) + "%", ofGetWidth() * 0.2 * total_ret[i] / total_num + 50, ofGetHeight() * (0.635 + 0.05 * i));
        } else if(total_num == 0) {
            ofRect(ofGetWidth() * 0.03,
                   ofGetHeight() * (0.6 + 0.05 * i),
                   0,
                   ofGetHeight() * 0.04);
            double earn_rate = 0.0;
            font.drawString(ofToString(earn_rate * 100, 1) + "%", 50, ofGetHeight() * (0.635 + 0.05 * i));
        }
    }
    
    //total rate
    ofSetColor(ofColor::white);
    font.drawString("<Total Rate>",
                    ofGetWidth() * 0.69,
                    ofGetHeight() * 0.59);
    for(int i = 0; i < keys.size(); i++) {
        total_numbers[keys[i]] = total_counts[i];
        if(keys[i] == "Silver") {
            ofSetColor(ofColor::silver);
        } else if(keys[i] == "Gold") {
            ofSetColor(ofColor::gold);
        } else if(keys[i] == "Nizi") {
            ofSetColor(ofColor::royalBlue);
        } else if(keys[i] == "Kira_Nizi") {
            ofSetHexColor(0xFF69B4);
        }
        font.drawString(ofToString(total_numbers[keys[i]]) + " : " + tags[keys[i]],
                        ofGetWidth() * 0.73,
                        ofGetHeight() * 0.15 + 30 * i);
        if(total_counts_num > 0) {
            ofRect(ofGetWidth() * 0.76,
                   ofGetHeight() * (0.6 + 0.05 * i),
                   ofGetWidth() * 0.2 * total_numbers[keys[i]] / total_counts_num,
                   ofGetHeight() * 0.04);
            double earn_rate = (double)total_numbers[keys[i]] / total_counts_num;
            font.drawString(ofToString(earn_rate * 100, 1) + "%", ofGetWidth() * 0.74 + ofGetWidth() * 0.2 * total_numbers[keys[i]] / total_counts_num + 50, ofGetHeight() * (0.635 + 0.05 * i));
        } else if(total_counts_num == 0) {
            ofRect(ofGetWidth() * 0.76,
                   ofGetHeight() * (0.6 + 0.05 * i),
                   0,
                   ofGetHeight() * 0.04);
            double earn_rate = 0.0;
            font.drawString(ofToString(earn_rate * 100, 1) + "%", ofGetWidth() * 0.7, ofGetHeight() * (0.635 + 0.05 * i));
        }
    }
    
#ifdef DEVELOPPER_INFO
    
    //draw time info
    ofDrawBitmapString(ofToString(count_time), ofGetWidth() * 0.8, 20);
    
#endif // DEVELOPPER_INFO
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key){
        case ' ':
            bPlaying = !bPlaying;
            vidPlayer.setPaused(bPlaying);
            if(bPlaying) {
                pause_start_time = ofGetElapsedTimeMillis();
            } else {
                paused_time += ofGetElapsedTimeMillis() - pause_start_time;
                count_time = ofGetElapsedTimeMillis() - exe_start_time - paused_time;
            }
            break;
        case 'p':
            ofLogNotice() << "time:" << ofToString(count_time);
            break;
    }
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


