#ifndef TRACKMANAGER_H
#define TRACKMANAGER_H

#include "TrackData.h"
#include "CarState.h"

class TrackManager {
private:
    TrackData currentTrack;
    
public:
    void loadTrack(const std::string& trackName);
    void update(const CarState& carState);
    const TrackData& getTrackData() const;
    
private:
    void createDefaultTrack();
};

#endif
