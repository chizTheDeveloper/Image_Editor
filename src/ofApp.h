#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "constant.h"

class ofApp : public ofBaseApp{

	public:

		ofImage m_origImg;
		ofImage m_edittedImg;

		//Gui stuff	
		ofxPanel m_gui;

		void setup();
		void update();
		void draw();
		void exit();

		ofParameterGroup mainGroup;
		ofParameterGroup sliderGroup1;
		ofParameterGroup sliderGroup2;
		ofParameterGroup sliderGroup3;

		ofParameter<int> intSlider;
		ofParameter<float> floatSlider;
		ofParameter<float> brightnessSlider;
		ofParameter<float> contrastSlider;
		ofParameter<float> greyScaleSlider;
		ofParameter<float> saturationSlider;
		ofParameter<float> RSlider;
		ofParameter<float> GSlider;
		ofParameter<float> BSlider;

		ofxButton m_displayBoxBlur;
		ofxButton m_displaySharpen;
		
		
		ofColor colorPick = ofColor(255, 255, 255);

		ofImage imgScreenShot;
		int count;
		bool snapped;

		void applyBrightness(float &intensity);
		void applyContrast(float &intensity);
		void applygreyScale(float &intensity);
		void applySaturation(float & intensity);
		void applyR(float& intensity);
		void applyG(float& intensity);
		void applyB(float& intensity);
		void enableSharpenFilter();
		void enableBoxBlurFilter();
		void applyConvolution3x3(Constants::CONVOLUTION_MAT_TYPE matType);

		void keyPressed(int key);	
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);


	


		

	
};
