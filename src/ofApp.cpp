#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowShape(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT);
	ofSetFrameRate(Constants::DESIRED_FRAMERATE);

	m_origImg.load(Constants::IMG_PATH);
	m_edittedImg = m_origImg; //cloning the image object, rether than pointing to

	sliderGroup1.setName("Modifty Sliders");
	sliderGroup1.add(floatSlider.set("Re-Size", 0.0f, 0.0f, 255.0f));
	sliderGroup1.add(intSlider.set("Resolution", 3, 3,64));

	sliderGroup2.setName("Colour Sliders");
	sliderGroup2.add(brightnessSlider.set("Brightness", 0.0f, -255.0f, 255.0f));
	sliderGroup2.add(contrastSlider.set("Contrast", 0.0f, -255.0f, 255.0f));
	sliderGroup2.add(greyScaleSlider.set("GreyScale", 0.0f, -255.0f, 255.0f));
	sliderGroup2.add(saturationSlider.set("Saturation", 0.0f, -255.0f, 255.0f));
	sliderGroup2.add(RSlider.set("R ", 0.0f, -255.0f, 255.0f));
	sliderGroup2.add(GSlider.set("G ", 0.0f, -255.0f, 255.0f));
	sliderGroup2.add(BSlider.set("B ", 0.0f, -255.0f, 255.0f));

	sliderGroup3.setName("ScreenShot - Space bar");
	
	//slider grouping
	mainGroup.add(sliderGroup1);
	mainGroup.add(sliderGroup2);
	mainGroup.add(sliderGroup3);
	m_gui.setup(mainGroup);
	
	//buttons
	
	m_gui.add(m_displaySharpen.setup("display sharpen"));
	m_gui.add(m_displayBoxBlur.setup("display box blur"));

	brightnessSlider.addListener(this, &ofApp::applyBrightness);
	contrastSlider.addListener(this, &ofApp::applyContrast);
	greyScaleSlider.addListener(this, &ofApp::applygreyScale);
	saturationSlider.addListener(this, &ofApp::applySaturation);
	RSlider.addListener(this, &ofApp::applyR);
	GSlider.addListener(this, &ofApp::applyG);
	BSlider.addListener(this, &ofApp::applyB);

	m_displaySharpen.addListener(this, &ofApp::enableSharpenFilter);
	m_displayBoxBlur.addListener(this, &ofApp::enableBoxBlurFilter);

}

//--------------------------------------------------------------
void ofApp::update(){
	ofSetCircleResolution(intSlider);
		
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(255, 255, 255);
	 m_edittedImg.draw(0,0, floatSlider);
	m_origImg.draw(m_origImg.getWidth(), 0, m_edittedImg.getWidth() / 4.0f, m_edittedImg.getHeight() / 4.0f);

	colorPick = m_edittedImg.getColor(mouseX, mouseY);
	ofSetColor(colorPick.r, colorPick.g, colorPick.b);
	ofDrawCircle(m_origImg.getWidth() + 200, 0, m_edittedImg.getWidth() / 8.0f - 200, m_edittedImg.getHeight() / 8.0f);
	
	m_gui.draw();// draw this last
}

//-------------------------------------------------------------
void ofApp::exit() {
	//cleanup
	brightnessSlider.removeListener(this, &ofApp::applyBrightness);
	contrastSlider.removeListener(this, &ofApp::applyContrast);
	greyScaleSlider.removeListener(this, &ofApp::applygreyScale);
	saturationSlider.removeListener(this, &ofApp::applySaturation);
	RSlider.removeListener(this, &ofApp::applyR);
	GSlider.removeListener(this, &ofApp::applyG);
	BSlider.removeListener(this, &ofApp::applyB);
}

void ofApp::applyBrightness(float &intensity) {
	ofColor tempCol;
	ofColor newCol;

	for (int x = 0; x < m_origImg.getWidth(); x++) {
		for (int y = 0; y < m_origImg.getHeight(); y++) {
			tempCol = m_origImg.getColor(x, y);

			newCol.set( MAX(MIN(tempCol.r + intensity, 250.0f), 0.0f),
						MAX(MIN(tempCol.g + intensity, 250.0f), 0.0f),
						MAX(MIN(tempCol.b + intensity, 250.0f), 0.0f));
			m_edittedImg.setColor(x, y, newCol);
			}
		}
	m_edittedImg.update();
}

void ofApp::applyContrast(float &intensity) {
	ofColor tempCol;
	ofColor newCol;

	float constrastFactor = (259.0f * (intensity + 255.0f)) / (255.0f + (259.0f + intensity));

	for (int x = 0; x < m_origImg.getWidth(); x++) {
		for (int y = 0; y < m_origImg.getHeight(); y++) {
			tempCol = m_origImg.getColor(x, y);

			newCol.set(MAX(MIN(constrastFactor * (tempCol.r - 128.0f) + 128.0f, 255.0f), 0.0f),
				MAX(MIN(constrastFactor * (tempCol.b - 128.0f) + 128.0f, 255.0f), 0.0f),
				MAX(MIN(constrastFactor * (tempCol.g - 128.0f) + 128.0f, 255.0f), 0.0f));

			m_edittedImg.setColor(x, y, newCol);
		}
	}
	m_edittedImg.update();
}

void ofApp::applygreyScale(float &intensity) {
	ofColor tempCol;
	ofColor newCol;

	for (int x = 0; x < m_origImg.getWidth(); x++) {
		for (int y = 0; y < m_origImg.getHeight(); y++) {
			tempCol = m_origImg.getColor(x, y);

			newCol.set(tempCol.r + intensity);
			
			m_edittedImg.setColor(x, y, newCol);
		}
	}
	m_edittedImg.update();
}

void ofApp::applySaturation(float& intensity) {
	float HueCol;
	float SaturationCol;
	float BrightnessCol;

	ofColor tempCol;

	for (int y = 0; y < m_origImg.getHeight(); y++) {
		for (int x = 0; x < m_origImg.getWidth(); x++) {
			tempCol = m_origImg.getColor(x, y);

			BrightnessCol = tempCol.getBrightness();
			HueCol = tempCol.getHue();
			SaturationCol = intensity;

			ofColor newCol(tempCol.r, tempCol.g, tempCol.b);
			if (intensity != 0) {
				newCol.setHsb(HueCol, SaturationCol, BrightnessCol);
			}
			m_edittedImg.setColor(x, y, newCol);
		}
	}
	m_edittedImg.update();
}

void ofApp::applyR(float& intensity) {
	ofColor tempCol;
	ofColor newCol;

	for (int x = 0; x < m_origImg.getWidth(); x++) {
		for (int y = 0; y < m_origImg.getHeight(); y++) {
			tempCol = m_origImg.getColor(x, y);

			newCol.set(MAX(MIN(tempCol.r + intensity, 250.0f), 0.0f),
				MAX(MIN(tempCol.g*0, 250.0f), 0.0f),
				MAX(MIN(tempCol.b*0 , 250.0f), 0.0f));
			m_edittedImg.setColor(x, y, newCol);
		}
	}
	m_edittedImg.update();
}

void ofApp::applyG(float& intensity) {
	ofColor tempCol;
	ofColor newCol;

	for (int x = 0; x < m_origImg.getWidth(); x++) {
		for (int y = 0; y < m_origImg.getHeight(); y++) {
			tempCol = m_origImg.getColor(x, y);

			newCol.set(MAX(MIN(tempCol.r*0, 250.0f), 0.0f),
				MAX(MIN(tempCol.g + intensity, 250.0f), 0.0f),
				MAX(MIN(tempCol.b *0, 250.0f), 0.0f));
			m_edittedImg.setColor(x, y, newCol);
		}
	}
	m_edittedImg.update();
}
void ofApp::applyB(float& intensity) {
	ofColor tempCol;
	ofColor newCol;

	for (int x = 0; x < m_origImg.getWidth(); x++) {
		for (int y = 0; y < m_origImg.getHeight(); y++) {
			tempCol = m_origImg.getColor(x, y);

			newCol.set(MAX(MIN(tempCol.r * 0, 250.0f), 0.0f),
				MAX(MIN(tempCol.g * 0, 250.0f), 0.0f),
				MAX(MIN(tempCol.b + intensity, 250.0f), 0.0f));
			m_edittedImg.setColor(x, y, newCol);
		}
	}
	m_edittedImg.update();
}

void ofApp::enableSharpenFilter() {
	applyConvolution3x3(Constants::CONVOLUTION_MAT_TYPE::SHARPEN);
};

void ofApp::enableBoxBlurFilter() {
	applyConvolution3x3(Constants::CONVOLUTION_MAT_TYPE::BOX_BLUR);
};

void ofApp::applyConvolution3x3(Constants::CONVOLUTION_MAT_TYPE matType) {
	ofColor tempCol;
	ofColor newCol;
	ofVec3f sum;
	int neighbourX = 0;
	int neighbourY = 0;
	int startIndex = (int)matType * 9;
	int imgWidth = m_origImg.getWidth();
	int imgHeight = m_origImg.getHeight();

	//std::cout << startIndex << std::endl;

	for (int y = 0; y < imgHeight; y++) {
		for (int x = 0; x < imgWidth; x++) {
			//newCol.set(0, 0, 0);
			sum.set(0.0f, 0.0f, 0.0f);

			//go through kernel 3x3 = 9 length
			for (int k = startIndex; k < startIndex + 9; k++) {

				//std::cout << k << std::endl;

				//check if we are trying to access an image coordinate out of bounds. Extend edges if so.
				//note that we need k here to start at 0 so we use modulo (%) to get the integer remainder of k / 9
				neighbourX = x + Constants::CONVOLUTION_KERNAL_CONVERT_X[k % 9];
				if (neighbourX < 0) {
					neighbourX = 0;
				}
				else if (neighbourX > imgWidth - 1) {
					neighbourX = imgWidth - 1;
				}

				neighbourY = y + Constants::CONVOLUTION_KERNAL_CONVERT_Y[k % 9];
				if (neighbourY < 0) {
					neighbourY = 0;
				}
				else if (neighbourY > imgHeight - 1) {
					neighbourY = imgHeight - 1;
				}

				//find out which 2D coordinate of image this k belongs to
				tempCol = m_origImg.getColor(neighbourX, neighbourY);

				//sum up kernel factors
				sum.x += tempCol.r * Constants::CONVOLUTION_MATS_3X3[k];
				sum.y += tempCol.g * Constants::CONVOLUTION_MATS_3X3[k];
				sum.z += tempCol.b * Constants::CONVOLUTION_MATS_3X3[k];
			}

			//std::cout << newCol << std::endl;

			//make sure values are in bounds
			newCol.set(MAX(MIN(sum.x, 255.0f), 0.0f),
				MAX(MIN(sum.y, 255.0f), 0.0f),
				MAX(MIN(sum.z, 255.0f), 0.0f));

			m_edittedImg.setColor(x, y, newCol);
		}
	}

	m_edittedImg.update();
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	// take screen shot
	if (key == ' ') {
		imgScreenShot.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		string filename = "screenshot_" + ofToString(count, 3, '0') + ".png";
		imgScreenShot.save(filename);
		count++;
	}
}


//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	colorPick = m_edittedImg.getColor(mouseX, mouseY);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){


}
