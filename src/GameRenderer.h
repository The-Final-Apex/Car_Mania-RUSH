#ifndef GAMERENDERER_H
#define GAMERENDERER_H

#include "CarState.h"
#include "TrackData.h"
#include <iostream>

class GameRenderer {
public:
    void initialize();
    void beginFrame();
    void renderTrack(const TrackData& track);
    void renderCar(const CarState& car);
    void renderHUD(const CarState& car);
    void endFrame();
    void cleanup();
    
private:
    void clearScreen();
    void drawPoint(int x, int y, char ch);
};

#endif
