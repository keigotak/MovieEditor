#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0,0,0);
    ofSetVerticalSync(true);

    vidPlayer.load("sin9.mp4");
    vidPlayer.setLoopState(OF_LOOP_NONE);
    vidPlayer.play();
    
    colorImg.allocate(1920, 1080);
    
    bStartLog = false;
    bPlaying = true;
    vidPlayer.setPaused(bPlaying);
    bEvaluating = false;
    bImg = false;
    
    disp_start_time = 8110;
    disp_end_time = 380700;
    flash_time = 3000;
    start_time = disp_start_time - 50;
    end_time = disp_end_time + 50;
    
    ref_ave_roi = *new Color_Data;
    ref_ave_roi = {0};
    ave_roi = *new Color_Data;
    ave_roi = {0};
    diff_ave_roi = *new Color_Data;
    diff_ave_roi = {0};
    tave_roi = *new Color_Data;
    tave_roi = {0};
    tave_num = 10;
    v_disp_Img_max = 15;
    v_Img_num = 0;
    
    rate_width = 0.704;
    rate_height = 1.0;
    log_x_speed = -35;
    
#ifdef REC_IPAD
    threshold_r_l = 0;
    threshold_r_m = 145;
    threshold_r_h = 150;
    threshold_g_l = 0;
    threshold_g_h = 190;
    threshold_b_l = 110;
    threshold_b_h = 120;
#endif  //REC_IPAD
#ifdef REC_IPHONE
    threshold_r_l = 130;
    threshold_r_m = 142;
    threshold_r_h = 150;
    threshold_g_l = 120;
    threshold_g_h = 140;
    threshold_b_l = 105;
    threshold_b_h = 115;
#endif  //REC_IPHONE
    
#ifdef REC_IPAD
    rect_sphere.set(452 * 1920 / ofGetWidth(),
                    15 * 1080 / ofGetHeight(),
                    21 * 1920 / ofGetWidth(),
                    21 * 1080 / ofGetHeight());
    int offset_x = 10;
    rect_dialog.set((355 + offset_x) * 1920 / ofGetWidth(),
                    30 * 1080 / ofGetHeight(),
                    310 * 1920 / ofGetWidth(),
                    35 * 1080 / ofGetHeight());
#endif  //REC_IPAD
#ifdef REC_IPHONE
    rect_sphere.set(463 * 1920 / ofGetWidth(),
                    12 * 1080 / ofGetHeight(),
                    15 * 1920 / ofGetWidth(),
                    18 * 1080 / ofGetHeight());
    rect_dialog.set(395 * 1920 / ofGetWidth(),
                    30 * 1080 / ofGetHeight(),
                    270 * 1920 / ofGetWidth(),
                    23 * 1080 / ofGetHeight());
#endif  //REC_IPHONE
    font_log.loadFont("HelveticaNeue.dfont", 21);
    font_time.loadFont("HelveticaNeue.dfont", 50);
    
    exe_start_time = ofGetElapsedTimeMillis();
    count_time = 0;
    paused_time = 0;
    pause_start_time = ofGetElapsedTimeMillis();
    
    grabed_img_num = 0;
    
    v_Img_chara.resize(6);
    v_Img_chara[0].loadImage("echo.png");
    v_Img_chara[1].loadImage("cloud.png");
    v_Img_chara[2].loadImage("van.png");
    v_Img_chara[3].loadImage("ramza.png");
    v_Img_chara[4].loadImage("seris.png");
    v_Img_chara[5].loadImage("sefiros.png");
    
    img1.loadImage("sin9_2.png");
    v_crop_img1.resize(5);
#ifdef REC_IPAD
    int start_img1_x = 5;
    int start_img1_y = 25;
    int crop_size_img1_x = img1.getWidth() - 65;
    int crop_size_img1_y = 50;
    int step_img1_y = 38;
#endif  //REC_IPAD
#ifdef REC_IPHONE
    int start_img1_x = 5;
    int start_img1_y = 17;
    int crop_size_img1_x = img1.getWidth() - 60;
    int crop_size_img1_y = 50;
    int step_img1_y = 25;
#endif  //REC_IPHONE
    v_crop_img1[0].cropFrom(img1,
                            start_img1_x, start_img1_y,
                            crop_size_img1_x, crop_size_img1_y);
    v_crop_img1[1].cropFrom(img1,
                            start_img1_x, start_img1_y + (crop_size_img1_y + step_img1_y),
                            crop_size_img1_x, crop_size_img1_y);
    v_crop_img1[2].cropFrom(img1,
                            start_img1_x, start_img1_y + (crop_size_img1_y + step_img1_y) * 2,
                            crop_size_img1_x, crop_size_img1_y);
    v_crop_img1[3].cropFrom(img1,
                            start_img1_x, start_img1_y + (crop_size_img1_y + step_img1_y) * 3,
                            crop_size_img1_x, crop_size_img1_y);
    v_crop_img1[4].cropFrom(img1,
                            start_img1_x, start_img1_y + (crop_size_img1_y + step_img1_y) * 4,
                            crop_size_img1_x, crop_size_img1_y);
    for (int i=0; i< v_crop_img1.size(); i++) {
#ifdef REC_IPAD
        v_crop_img1[i].resize(ofGetWidth() * 0.37, ofGetHeight() * 0.1);
#endif  //REC_IPAD
#ifdef REC_IPHONE
        v_crop_img1[i].resize(ofGetWidth() * 0.4, ofGetHeight() * 0.1);
#endif  //REC_IPHONE
    }
    
    
    img2.loadImage("sin9_1.png");
    v_crop_img2.resize(5);
#ifdef REC_IPAD
    int start_img2_x = 2;
    int start_img2_y = 10;
    int crop_size_img2_x = img2.getWidth() - 10;
    int crop_size_img2_y = 60;
    int step_img2_y = 27;
#endif  //REC_IPAD
#ifdef REC_IPHONE
    int start_img2_x = 4;
    int start_img2_y = 10;
    int crop_size_img2_x = img2.getWidth() - 10;
    int crop_size_img2_y = 60;
    int step_img2_y = 11;
#endif  //REC_IPHONE
    v_crop_img2[0].cropFrom(img2,
                            start_img2_x, start_img2_y,
                            crop_size_img2_x, crop_size_img2_y);
    v_crop_img2[1].cropFrom(img2,
                            start_img2_x, start_img2_y + (crop_size_img2_y + step_img2_y),
                            crop_size_img2_x, crop_size_img2_y);
    v_crop_img2[2].cropFrom(img2,
                            start_img2_x, start_img2_y + (crop_size_img2_y + step_img2_y) * 2,
                            crop_size_img2_x, crop_size_img2_y);
    v_crop_img2[3].cropFrom(img2,
                            start_img2_x, start_img2_y + (crop_size_img2_y + step_img2_y) * 3,
                            crop_size_img2_x, crop_size_img2_y);
    v_crop_img2[4].cropFrom(img2,
                            start_img2_x, start_img2_y + (crop_size_img2_y + step_img2_y) * 4,
                            crop_size_img2_x, crop_size_img2_y);
    for (int i=0; i< v_crop_img2.size(); i++) {
#ifdef REC_IPAD
        v_crop_img2[i].resize(ofGetWidth() * 0.37, ofGetHeight() * 0.1);
#endif  //REC_IPAD
#ifdef REC_IPHONE
        v_crop_img2[i].resize(ofGetWidth() * 0.4, ofGetHeight() * 0.1);
#endif  //REC_IPHONE
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    bool bNewFrame = false;
    
    if(!bPlaying) {
        count_time = ofGetElapsedTimeMillis() - exe_start_time - paused_time;
    }
    
    vidPlayer.update();
    bNewFrame = vidPlayer.isFrameNew();
    
    if(bNewFrame && !bPlaying) {
        ofPixels &pixels = vidPlayer.getPixels();
        if(pixels.isAllocated()) {
            
            colorImg.setFromPixels(pixels);
            colorImg.setROI(rect_sphere);
            ofPixels &tmp_cImg1 = colorImg.getRoiPixels();
            colorImg.resetROI();

            Color_Data o_proc = *new Color_Data;
            o_proc = {0};
            getAveragePixels(tmp_cImg1, &o_proc);
            v_tave.push_back(o_proc);
            while(v_tave.size() > tave_num) {
                v_tave.erase(v_tave.begin());
            }
            Color_Data o_proc2 = *new Color_Data;
            o_proc2 = {0};
            getTimeAveragedData(&o_proc2);
            tave_roi.r = o_proc2.r;
            tave_roi.g = o_proc2.g;
            tave_roi.b = o_proc2.b;
            tave_roi.y = o_proc2.y;

            if(count_time <= start_time || count_time - disp_start_time >= end_time) {
                bEvaluating = false;
                ref_ave_roi = o_proc;
            } else {
                bEvaluating = true;
                ave_roi = o_proc;
                
                v_disp.push_back(ave_roi);
                while( v_disp.size() > 300){
                    v_disp.erase(v_disp.begin());
                }
                
                v_disp_tave.push_back(tave_roi);
                while( v_disp_tave.size() > 300){
                    v_disp_tave.erase(v_disp_tave.begin());
                }
                
                // check if pixel value is in the range
                if(tave_roi.r >= threshold_r_l && tave_roi.r <= threshold_r_h) {
                    if(!bImg) {
                        if (tave_roi.r < threshold_r_m) {
                            if(tave_roi.g >= threshold_g_l && tave_roi.g <= threshold_g_h) {
                                if(tave_roi.b >= threshold_b_l && tave_roi.b <= threshold_b_h) {
                                    colorImg.setROI(rect_dialog);
                                    ofPixels &tmp_cImg = colorImg.getRoiPixels();
                                    colorImg.resetROI();
                                
                                    ofTexture tmp_texture;
                                    tmp_texture.loadData(tmp_cImg);
                                    v_Img.push_back(tmp_texture);
                                    v_Img_time.push_back(count_time - disp_start_time);
                                    v_log_x.push_back(ofGetWidth());
                                    
                                    ofLogNotice() << "time/rgb=" << ofToString(count_time - disp_start_time) << "/" << ofToString(ave_roi.r) + "," +ofToString(ave_roi.g) + "," +ofToString(ave_roi.b);
                                    
                                    while(v_Img.size() > v_disp_Img_max) {
                                        v_Img.erase(v_Img.begin());
                                        v_Img_time.erase(v_Img_time.begin());
                                        v_log_x.erase(v_log_x.begin());
                                    }
                                    bImg = true;
                                    v_Img_num++;
                                }
                            }
                        }
                    }
                } else {
                    bImg = false;
                }
            }
        }
        
        for(int i=0; i<v_log_x.size(); i++) {
            if(v_log_x[i] <= ofGetWidth() * rate_width) {
                v_log_x[i] = ofGetWidth() * rate_width;
            } else {
                v_log_x[i] += log_x_speed;
            }
        }
    }
}

void ofApp::getAveragePixels(ofPixels &pixels, Color_Data* out_proc){
    int w = pixels.getWidth();
    int h = pixels.getHeight();
    int numPixels = w * h;
    
    unsigned char *loadedPixels = pixels.getPixels();
    int numChannels = pixels.getNumChannels();
    
    double r_totalPixelVal = 0.0;
    double g_totalPixelVal = 0.0;
    double b_totalPixelVal = 0.0;
    double y_totalPixelVal = 0.0;
    double gs_totalPixelVal = 0.0;
    
    double r_averagePixelVal = 0.0;
    double g_averagePixelVal = 0.0;
    double b_averagePixelVal = 0.0;
    double y_averagePixelVal = 0.0;
    double gs_averagePixelVal = 0.0;
    
    if(numChannels >= 3) {
        for (int i=0; i<numPixels; i++) {
            int pix = i * numChannels;
            r_totalPixelVal += loadedPixels[pix]; // red pixels
            g_totalPixelVal += loadedPixels[pix+1]; // green pixels
            b_totalPixelVal += loadedPixels[pix+2]; // blue pixels
            y_totalPixelVal += 0.3 * loadedPixels[pix] + 0.6 * loadedPixels[pix+1] + 0.1 * loadedPixels[pix+2];
        }
    } else {
        for (int i=0; i<numPixels; i++) {
            gs_totalPixelVal += loadedPixels[i]; // grayscale
        }
    };
    
    r_averagePixelVal = (r_totalPixelVal / numPixels);
    g_averagePixelVal = (g_totalPixelVal / numPixels);
    b_averagePixelVal = (b_totalPixelVal / numPixels);
    y_averagePixelVal = (y_totalPixelVal / numPixels);
    
    gs_averagePixelVal = (gs_totalPixelVal / numPixels);
    
    out_proc->r = r_averagePixelVal;
    out_proc->g = g_averagePixelVal;
    out_proc->b = b_averagePixelVal;
    out_proc->y = y_averagePixelVal;
    out_proc->a = gs_averagePixelVal;
    
}

void ofApp::getTimeAveragedData(Color_Data* out_proc){
    for (int i = 0; i < v_tave.size(); i++) {
        out_proc->r += v_tave[i].r;
        out_proc->g += v_tave[i].g;
        out_proc->b += v_tave[i].b;
        out_proc->y += v_tave[i].y;
    }
    
    out_proc->r = (int)(out_proc->r / v_tave.size() + 0.5);
    out_proc->g = (int)(out_proc->g / v_tave.size() + 0.5);
    out_proc->b = (int)(out_proc->b / v_tave.size() + 0.5);
    out_proc->y = (int)(out_proc->y / v_tave.size() + 0.5);
}


//--------------------------------------------------------------
void ofApp::draw(){
    ofFill();
    
	ofSetHexColor(0xFFFFFF);
    // video play
    vidPlayer.draw(0, 0, ofGetWidth(), ofGetHeight());

    // logs
    int i = 0;
    int y_offset = ofGetHeight() * 0.104;
    for( int i = 0; i< v_Img.size(); i++ ){
        v_Img[i].draw(v_log_x[i],
                      y_offset + (ofGetHeight() * rate_height - y_offset) / v_disp_Img_max * (v_Img.size() - i - 1),
                      ofGetWidth() * (1 - rate_width) - ofGetWidth() * 0.002,
                      ((ofGetHeight() * rate_height - y_offset) - v_disp_Img_max * 2) / v_disp_Img_max);
    }

    if (v_Img_num < v_disp_Img_max) {
        for (int i = 0; i < v_Img_num; i++) {
            ofSetHexColor(0xFFFFFF);
            font_log.drawString(ofToString(i + 1),
                                ofGetWidth() * 0.71,
                                y_offset + (ofGetHeight() * rate_height - y_offset) / v_disp_Img_max * ((v_Img.size() - i - 1) + 0.75));
            ofSetHexColor(0x86B81B);
            font_log.drawString(ofToString((int)(v_Img_time[i] / 1000)) +
                                "." +
                                ofToString((int)((v_Img_time[i] / 100) % 10)) +
                                "s",
                                ofGetWidth() * 0.93,
                                y_offset + (ofGetHeight() * rate_height - y_offset) / v_disp_Img_max * ((v_Img.size() - i - 1) + 0.75));
            ofSetHexColor(0xFFFFFF);
            if (ary_img_chara[i] > 0 && ary_img_chara[i] < 7) {
                v_Img_chara[ary_img_chara[i] - 1].draw(v_log_x[i] + ofGetWidth() * 0.03,
                                                   y_offset + (ofGetHeight() * rate_height - y_offset) / v_disp_Img_max * (v_Img.size() - i - 1),
                                                   43,
                                                   43);
            }
        }
    } else {
        int j = 0;
        int k = v_Img_num;
        for (int i = v_Img_num - v_disp_Img_max; i < v_Img_num; i++) {
            ofSetHexColor(0xFFFFFF);
            font_log.drawString(ofToString(i + 1),
                                ofGetWidth() * 0.71,
                                y_offset + (ofGetHeight() * rate_height - y_offset) / v_disp_Img_max * ((v_Img.size() - j - 1) + 0.75));
            ofSetHexColor(0x86B81B);
            font_log.drawString(ofToString((int)(v_Img_time[j] / 1000)) +
                                "." +
                                ofToString((int)((v_Img_time[j] / 100) % 10)) +
                                "s",
                                ofGetWidth() * 0.93,
                                y_offset + (ofGetHeight() * rate_height - y_offset) / v_disp_Img_max * ((v_Img.size() - j - 1) + 0.75));
            ofSetHexColor(0xFFFFFF);
            if (ary_img_chara[k - 1] > 0 && ary_img_chara[k - 1] < 7) {
                v_Img_chara[ary_img_chara[k - 1] - 1].draw(v_log_x[v_Img.size() - j - 1] + ofGetWidth() * 0.03,
                                                       y_offset + (ofGetHeight() * rate_height - y_offset) / v_disp_Img_max * (j),
                                                       43,
                                                       43);

            }
            j++;
            k--;
        }
    }
    
    //images
    ofSetHexColor(0xFFFFFF);
//    int crop_img_offset_y = ofGetHeight() * 0.24;
    int crop_img_offset_y = ofGetHeight() * 0.0;
#ifndef DEVELOPPER_INFO
    for(int i=0; i < v_crop_img2.size(); i++) {
        v_crop_img2[i].draw(ofGetWidth() * 0.005, crop_img_offset_y + ofGetHeight() * 0.2 * i);
    }
    for(int i=0; i < v_crop_img1.size(); i++) {
        v_crop_img1[i].draw(ofGetWidth() * 0.005, crop_img_offset_y + ofGetHeight() * 0.1 + ofGetHeight() * 0.2 * i);
    }
#endif

    //time
    int disp_time = count_time - disp_start_time;
    if (disp_time <= 0) {
        disp_time = 0;
        ofSetHexColor(0x86B81B);
    } else if (disp_time >= disp_end_time) {
        disp_time = disp_end_time;
        if((count_time - disp_start_time) % flash_time < flash_time / 2) {
            ofSetHexColor(0x0097DB);
        } else {
            ofSetHexColor(0xFFFFFF);
        }
    } else {
        ofSetHexColor(0xD7004A);
    }
    ofRect(ofGetWidth() - ofGetWidth() / 400 - ofGetWidth() * 0.295,
           ofGetHeight()  * 0,
           ofGetWidth() * 0.295,
           ofGetHeight() * 0.1);
    
    if(disp_time >= disp_end_time) {
        if((count_time - disp_start_time) % flash_time < flash_time / 2) {
            ofSetHexColor(0xFFFFFF);
        } else {
            ofSetHexColor(0x0097DB);
        }
    } else {
        ofSetHexColor(0xFFFFFF);
    }

    int margine = 100;
    ofRect(ofGetWidth() - ofGetWidth() / 400 - ofGetWidth() * 0.295 + ofGetWidth() / margine,
           ofGetHeight() * 0 + ofGetWidth() / margine,
           ofGetWidth() * 0.295 - ofGetWidth() / margine * 2,
           ofGetHeight() * 0.1 - ofGetWidth() / margine * 2);

    if (disp_time <= 0) {
        ofSetHexColor(0x86B81B);
    } else if (disp_time >= disp_end_time) {
        if((count_time - disp_start_time) % flash_time < flash_time / 2) {
            ofSetHexColor(0x007FAB);
        } else {
            ofSetHexColor(0xFFFFFF);
        }
    } else {
        ofSetHexColor(0xD7004A);
    }
    int time_pos_x = ofGetWidth() - ofGetWidth() * 0.19;
    int time_pos_x_step = 0;
    if((double)disp_time / 1000 < 10) {
        time_pos_x_step = 0;
    } else if((double)disp_time / 1000 >= 10 && (double)disp_time / 1000 < 100) {
        time_pos_x_step = ofGetWidth() * 0.016;
    } else if((double)disp_time / 1000 >= 100 && (double)disp_time / 1000 < 1000) {
        time_pos_x_step = ofGetWidth() * 0.032;
    }
    font_time.drawString(ofToString((int)(disp_time / 1000)) +
                         "." +
                         ofToString((int)((disp_time / 100) % 10)) +
                         "s",
                         time_pos_x - time_pos_x_step,
                         ofGetHeight() * 0.083);
    
#ifdef DEVELOPPER_INFO
	ofSetHexColor(0xFFFFFF);
    //draw time info
    ofDrawBitmapString("count_time=" + ofToString(count_time), 0, 20);
    ofDrawBitmapString("count - start=" + ofToString(count_time - disp_start_time), 0, 40);
    ofDrawBitmapString("exe_start_time=" + ofToString(exe_start_time), 0, 60);
    ofDrawBitmapString("paused_time=" + ofToString(paused_time), 0, 80);
    ofDrawBitmapString("pause_start_time=" + ofToString(pause_start_time), 0, 100);
    ofDrawBitmapString("bPlaying=" + ofToString(bPlaying), 0, 120);
    ofDrawBitmapString("start_time=" + ofToString(start_time), 0, 140);
    ofDrawBitmapString("end_time=" + ofToString(end_time), 0, 160);
    ofDrawBitmapString("bEvaluating=" + ofToString(bEvaluating), 0, 180);
    ofDrawBitmapString("Image number=" + ofToString(v_Img_num), 0, 200);
    
    // draw mouse info
    ofDrawBitmapString("x,y = " +
                       ofToString(mouseX) + "," +
                       ofToString(mouseY),
                       0,
                       ofGetHeight() - 100);
    
    // draw crop video
    colorImg.setROI(rect_dialog);
    colorImg.drawROI(0,
                     ofGetHeight() - 30,
                     280,
                     30);
    colorImg.resetROI();
    
    colorImg.setROI(rect_sphere);
    colorImg.drawROI(0,
                     ofGetHeight() - 80,
                     40,
                     40);
    colorImg.resetROI();
    
    // draw crop video info
    ofDrawBitmapString("REF   R,G,B,Y=" +
                       ofToString(ref_ave_roi.r) + "," +
                       ofToString(ref_ave_roi.g) + "," +
                       ofToString(ref_ave_roi.b) + "," +
                       ofToString(ref_ave_roi.y),
                       0,
                       ofGetHeight() - 120);
    ofDrawBitmapString("      R,G,B,Y=" +
                       ofToString(ave_roi.r) + "," +
                       ofToString(ave_roi.g) + "," +
                       ofToString(ave_roi.b) + "," +
                       ofToString(ave_roi.y),
                       0,
                       ofGetHeight() - 140);
    ofDrawBitmapString("T_AVE R,G,B,Y=" +
                       ofToString(tave_roi.r) + "," +
                       ofToString(tave_roi.g) + "," +
                       ofToString(tave_roi.b) + "," +
                       ofToString(tave_roi.y),
                       0,
                       ofGetHeight() - 160);
    if (bEvaluating) {
        ofNoFill();
        
        ofSetColor(ofColor::tomato);
        ofLine(0, threshold_r_l / 2 + 100, v_disp.size(), threshold_r_l / 2 + 100);
        ofLine(0, threshold_r_m / 2 + 100, v_disp.size(), threshold_r_m / 2 + 100);
        ofLine(0, threshold_r_h / 2 + 100, v_disp.size(), threshold_r_h / 2 + 100);
        ofSetColor(ofColor::red);
        ofBeginShape();
        for( int i = 0; i< v_disp_tave.size(); i++ ){
            ofVertex(i, v_disp_tave[i].r / 2 + 100);
        }
        ofEndShape();
        
        ofSetColor(ofColor::springGreen);
        ofLine(0, threshold_g_l + 200, v_disp.size(), threshold_g_l + 200);
        ofLine(0, threshold_g_h / 2 + 200, v_disp.size(), threshold_g_h / 2 + 200);
        ofSetColor(ofColor::green);
        ofBeginShape();
        for( int i = 0; i< v_disp_tave.size(); i++ ){
            ofVertex(i, v_disp_tave[i].g / 2 + 200);
        }
        ofEndShape();

        ofSetColor(ofColor::steelBlue);
        ofLine(0, threshold_b_l + 300, v_disp.size(), threshold_b_l + 300);
        ofLine(0, threshold_b_h / 2 + 300, v_disp.size(), threshold_b_h / 2 + 300);
        ofSetColor(ofColor::blue);
        ofBeginShape();
        for( int i = 0; i< v_disp_tave.size(); i++ ){
            ofVertex(i, v_disp_tave[i].b / 2 + 300);
        }
        
        ofEndShape();
        ofSetColor(ofColor::yellow);
        ofBeginShape();
        for( int i = 0; i< v_disp_tave.size(); i++ ){
            ofVertex(i, v_disp_tave[i].y / 2 + 400);
        }
        ofEndShape();
    }
    
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
        case 't':
            ofLogNotice() << ofToString(count_time);
            break;
        case 'p':
            ofImage saveImage;
            saveImage.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
            saveImage.saveImage("./save/screen" + ofToString(grabed_img_num) + ".png", OF_IMAGE_QUALITY_BEST);
            grabed_img_num++;
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


