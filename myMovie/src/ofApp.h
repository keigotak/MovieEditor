#pragma once

//#define DEVELOPPER_INFO
//#define REC_IPAD
#define REC_IPHONE

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
    
    typedef struct {
        int r;
        int g;
        int b;
        int y;
        int a;
    }Color_Data;
    
    
        ofVideoPlayer 		vidPlayer;
    
        ofxCvColorImage			colorImg;
    
        bool                bStartLog;
        bool                bPlaying;
    bool                bEvaluating;
    
        unsigned long long  start_time;
        unsigned long long  end_time;
    unsigned long long  exe_start_time;
    unsigned long long  count_time;
    unsigned long long  pause_start_time;
    unsigned long long paused_time;
    unsigned long long disp_start_time;
    unsigned long long disp_end_time;
    
        int                 pos_timeLog;
    
    Color_Data              ref_ave_roi;
    Color_Data              ave_roi;
    Color_Data              diff_ave_roi;
    Color_Data              bef_ave_roi;
    Color_Data              tave_roi;
    vector<Color_Data>      v_tave;
    int                     tave_num;
    vector<Color_Data>      v_disp;
    vector<Color_Data>      v_disp_tave;
    
    vector<ofTexture>       v_Img;
    int                     v_Img_num;
    int                     v_disp_Img_max;
    bool                    bImg;
    vector<int>             v_Img_time;
    
    vector<ofImage>         v_Img_chara;
    int                     ary_img_chara[90] = {
        5,2,3,1,4,3,5,2,1,4,
        3,6,3,2,5,6,6,6,1,4,
        3,2,3,6,5,1,4,3,6,6,
        6,6,2,2,2,6,5,3,6,6,
        1,6,6,6,4,2,6,3,6,6,
        6,5,1,3,4,6,2,5,1,3,
        6,6,6,6,4,3,6,6,5,3,
        0,0,0,0,0,0,0,0,0,0};
    
    int                     threshold_r_l;
    int                     threshold_r_m;
    int                     threshold_r_h;
    int                     threshold_g_l;
    int                     threshold_g_h;
    int                     threshold_b_l;
    int                     threshold_b_h;

    ofRectangle             rect_sphere;
    ofRectangle             rect_dialog;
    
    ofTrueTypeFont          font_log;
    ofTrueTypeFont          font_time;

    ofImage                 img1;
    ofImage                 img2;
    
    int                     flash_time;
    
    vector<int>             v_log_x;
    int                     log_x_speed;
    
    double                  rate_height;
    double                  rate_width;
    
    vector<ofImage>     v_crop_img1;
    vector<ofImage>     v_crop_img2;
    
private:
    void getAveragePixels(ofPixels &pixels, Color_Data* out_proc);
    void getTimeAveragedData(Color_Data* out_proc);
    
    int                     grabed_img_num;

    
};
