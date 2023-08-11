#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 150, true, true, true);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->mesh.clear();

	ofFbo fbo;
	fbo.allocate(ofGetWidth(), ofGetHeight());
	fbo.begin();
	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);
	ofClear(0);
	ofSetColor(0);

	font.drawString("Every", font.stringWidth("Every") * -0.5, font.stringHeight("Every") * -0.75);
	font.drawString("Day", font.stringWidth("Day") * -0.5, font.stringHeight("Day") * 0.25);
	font.drawString("Coding", font.stringWidth("Coding") * -0.5, font.stringHeight("Coding") * 1.25);

	fbo.end();

	ofPixels pixels;
	fbo.readToPixels(pixels);

	float span = 0.1;
	for (float x = 0; x < fbo.getWidth(); x += span) {

		for (float y = 0; y < fbo.getHeight(); y += span) {

			auto noise_value = ofMap(ofNoise(x * 0.02, y * 0.02 + ofGetFrameNum() * 0.04, ofGetFrameNum() * 0.02), 0, 1, 0, 10);
			if ((int)noise_value % 2 == 0) {

				continue;
			}

			ofColor color = pixels.getColor((int)x, (int)y);
			if (color == ofColor(0, 0)) {

				continue;
			}

			this->mesh.addVertex(glm::vec3(x, y, 0));
			this->mesh.addVertex(glm::vec3(x + span, y, 0));
			this->mesh.addVertex(glm::vec3(x + span, y + span, 0));
			this->mesh.addVertex(glm::vec3(x, y + span, 0));

			this->mesh.addIndex(this->mesh.getNumVertices() - 1); this->mesh.addIndex(this->mesh.getNumVertices() - 4); this->mesh.addIndex(this->mesh.getNumVertices() - 3);
			this->mesh.addIndex(this->mesh.getNumVertices() - 1); this->mesh.addIndex(this->mesh.getNumVertices() - 2); this->mesh.addIndex(this->mesh.getNumVertices() - 3);

			for (int i = 0; i < 4; i++) {

				this->mesh.addColor(ofColor(0));
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->mesh.draw();

	ostringstream os;
	os << setw(4) << setfill('0') << ofGetFrameNum();
	ofImage image;
	image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
	image.saveImage("image/img_" + os.str() + ".jpg");
	if (ofGetFrameNum() >= 20 * 25) {

		std::exit(1);
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}