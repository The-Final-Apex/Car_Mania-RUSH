#include "TrackManager.h"

void TrackManager::loadTrack(const std::string& trackName) {
    if (trackName == "default_track") {
        createDefaultTrack();
    }
}

void TrackManager::createDefaultTrack() {
    // Create a nice and simple oval track :3
    currentTrack.addSegment(Vector2D(-50, -25), Vector2D(50, -25));
    currentTrack.addSegment(Vector2D(50, -25), Vector2D(50, 25));
    currentTrack.addSegment(Vector2D(50, 25), Vector2D(-50, 25));
    currentTrack.addSegment(Vector2D(-50, 25), Vector2D(-50, -25));
}

void TrackManager::update(const CarState& carState) {
    // Update track logic (checkpoints, lap counting, sum other stuff.)
}

const TrackData& TrackManager::getTrackData() const {
    return currentTrack;
}
