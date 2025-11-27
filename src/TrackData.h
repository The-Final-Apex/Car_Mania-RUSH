#ifndef TRACKDATA_H
#define TRACKDATA_H

#include <vector>
#include "PhysicsEngine.h"

struct TrackSegment {
    Vector2D start;
    Vector2D end;
    bool isRoad;
};

class TrackData {
private:
    std::vector<TrackSegment> segments;
    std::vector<Vector2D> checkpoints;
    
public:
    void addSegment(const Vector2D& start, const Vector2D& end, bool isRoad = true);
    const std::vector<TrackSegment>& getSegments() const;
    const std::vector<Vector2D>& getCheckpoints() const;
};

#endif
