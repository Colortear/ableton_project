#ifndef WARPMARKER_H
# define WARPMARKER_H

class WarpMarker {
public:
    WarpMarker(double beat, double timestamp);
    WarpMarker(WarpMarker&& wm);
    WarpMarker(const WarpMarker& copy) = delete;
    WarpMarker& operator=(const WarpMarker& lvalue) = delete;

    double   beat() const;
    double   time() const;
private:
    const double _beat;
    const double _timestamp;
};

#endif // WARPMARKER_H
