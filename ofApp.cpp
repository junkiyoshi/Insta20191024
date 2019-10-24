#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(1.5);
	ofEnableDepthTest();

	this->mesh.setMode(OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {
	
	ofSeedRandom(39);

	this->mesh.clear();

	for (auto i = 0; i < 350; i++) {

		auto location = glm::vec3(
			ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.0003), 0, 1, -300, 300),
			ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.0003), 0, 1, -300, 300),
			ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.0003), 0, 1, -300, 300));

		this->mesh.addVertex(location);
		this->mesh.addColor(ofColor(255, 0));
	}

	for (int i = 0; i < this->mesh.getVertices().size(); i++) {

		auto location = this->mesh.getVertex(i);
		vector<int> near_index_list;
		for (int k = 0; k < this->mesh.getVertices().size(); k++) {

			if (i == k) { continue; }

			auto other = this->mesh.getVertex(k);
			auto distance = glm::distance(location, other);
			if (distance < 50) {

				this->mesh.addIndex(i);
				this->mesh.addIndex(k);

				auto distance_alpha = 255;
				if (distance > 35) {

					distance_alpha = ofMap(distance, 35, 50, 255, 0);
				}

				auto i_alpha = this->mesh.getColor(i).a;
				this->mesh.setColor(i, ofColor(39, distance_alpha > i_alpha ? distance_alpha : i_alpha));

				auto k_alpha = this->mesh.getColor(k).a;
				this->mesh.setColor(k, ofColor(39, distance_alpha > k_alpha ? distance_alpha : k_alpha));
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	
	for (int i = 0; i < this->mesh.getVertices().size(); i++) {

		ofSetColor(this->mesh.getColor(i));
		ofDrawSphere(this->mesh.getVertex(i), 3);
	}
	this->mesh.draw();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}