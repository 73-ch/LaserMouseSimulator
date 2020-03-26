#ifndef Mouse_hpp
#define Mouse_hpp

#include <stdio.h>
#include "ofMain.h"

const float radius = 10.;

class Mouse {
    glm::vec2 position;
    float r;
    glm::vec2 direction;
    unsigned int reverse = 0;
    unsigned int life_count = 0;
    enum State {
        ROTATE,
        MOVE
    };
    float add_rotation = 0;
    int rotation_count = 0;
    
    State state = MOVE;
    
public:
    
    bool color_frag; // t: red, f: green
    
    Mouse() {
        position = glm::vec2(ofRandom(radius, ofGetWidth() - radius), ofRandom(radius, ofGetHeight() - radius));
        
        // dir
        r = ofRandom(PI * 2.);
        direction = glm::vec2(cos(r), sin(r));
        
        // color
        color_frag = ofRandom(1) > 0.5;
        
        state = MOVE;
    }
    
    void attacked() {
        if (state == ROTATE) return;

    
        state = ROTATE;
        add_rotation = PI + ofRandom(-0.2, 0.2);
        rotation_count = 0;
    }
    
    void laser() {
        
    }
    
    float collision(vector<Mouse> &mouses) {
        float d = 0;
        
        float minimum = ofGetWidth() - abs(position.x*2.0 - ofGetWidth());
        float min_y = ofGetHeight() - abs(position.y*2.0 - ofGetHeight());
        
        if (min_y < minimum) minimum = min_y;
    
        
        for (auto &m : mouses) {
            if (m.position == position) continue; // 自分自身
            
            d = glm::length(position - m.position) - radius;
            
            if (d < minimum) minimum = d;
        }

        return minimum;
    }
    
    void update(vector<Mouse> &mouses, const float step = 1.0) {
    
        life_count++;
        if (state == MOVE) {
            position = position + direction * step * 0.1 * ((reverse > 0 ) ? -1 : 1);
        
            position.x = ofClamp(position.x, 0, ofGetWidth());
            position.y = ofClamp(position.y, 0, ofGetHeight());
            
            if (ofRandom(10) > 9.98) {
                state = ROTATE;
                add_rotation = ofRandom(-0.2, 0.2);
                rotation_count = 0;
            }
            
            
            
        } else if (state == ROTATE) {
            
            rotation_count = rotation_count + 1;
            r += add_rotation / 180;
            direction = glm::vec2(cos(r), sin(r));
            
            for (auto &m : mouses) {
                if (m.position == position) continue; // 自分自身
//                ofLogNotice() << glm::abs(glm::dot(glm::normalize(m.position - position), direction));
                
                if (glm::abs(glm::dot(glm::normalize(m.position - position), direction)) < 0.002 && glm::length(m.position - position) < 150) {
                    m.attacked();
                }
            }
            
            
            if (rotation_count > 180) {
                
                state = MOVE;
                add_rotation = 0;
                rotation_count = 0;
            }
        }
    
        
        
        float dist = collision(mouses);
        
        if (dist < radius && reverse == 0) {
//            ofLogNotice() << dist;
            reverse = 1;
        }
        
        if (reverse > 0) {
            reverse++;
        }
        
        if (reverse > 180) {
            r += ofRandom(-0.3, 0.3);
            direction = glm::vec2(cos(r), sin(r));
            reverse = 0;
        }
        
    }
    
    void draw() {
        if (color_frag) {
            ofSetColor(255, 0,0);
        } else {
            ofSetColor(0,255,0);
        }
    
        ofDrawCircle(position, radius);
        ofSetColor(200);
        ofDrawLine(position, position + direction * radius);
        
        string text = state == MOVE ? "m" : "r" + ofToString(rotation_count);
        
        
        ofSetColor(0,0,
        255);
        ofDrawBitmapString(text, position);
        
        if (reverse > 1) {
            ofDrawBitmapString("&"+ofToString(reverse), position + glm::vec2(0, 10));
        }
    }
    
};



#endif /* Mouse_hpp */
