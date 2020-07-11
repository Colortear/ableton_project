#ifndef WARP_MARKER_H
# define WARP_MARKER_H

class WarpMarker {
public:
    WarpMarker(float beat, float timestamp);
    WarpMarker(WarpMarker&& wm);
    WarpMarker(const WarpMarker& copy) = delete;
    WarpMarker& operator=(const WarpMarker& lvalue) = delete;

    float   getTempo() const;
    float   beat() const;
    float   time() const;
private:
    const float _beat;
    const float _timestamp;
};

#endif // WARP_MARKER_H
