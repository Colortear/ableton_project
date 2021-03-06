Operations:
marker <beat time> <sample time>:
    When a marker is place into the map container the span between the two may overlap
    one or more other markers. I have decided that the natural solution to overlap is to
    remove the existing markers that have been interrupted by the new marker given that
    the new marker is within the reasonable limits of our data primitives and non-negative.
    The reason is that I cannot think of a reasonable way of handling intersecting relationships
    between the lines. using the formula provided below it would result in negative values.

end_tempo <value>:
    Simply store the value in the corresponding container.

s2b <sample time>:
    In order to find the interpolation a point on the sample line, find the markers that delimit
    the area that the point is contained. The the lower and upper bound of the area signify
    the markers closest to the provided sample time are used to get the distance between the two.
    In order to find the corresponding value we must expand or contract the values to the relative
    scale of the opposing line using these upper and lower bounds which are connected by the markers
    provided by the input.
    The corresponding side can be found by dividing the difference between the given value and it's
    lower bound (previous marker) by the distance between it's lower and upper bound. This is
    multiplied by the difference between the related points (upper and lower bounds)on the other
    line provided by the marker and this value. Finally, the lower bounds on the other line is added 
    to the new fraction produced by applying the ratio found on the originating line. In other words:
    Where s = sample time (input), Us = sample upper bound, Ls = sample lower bound,
    Ub = beat upper bound, Lb = beat lower bound

                                        s - Ls
                    b = Lb + ((Ub - Lb) ------- )
                                        Us - Ls

b2s <beat time>:
    Or for time
                                        b - Lb 
                    s = Ls + ((Us - LS) ------- )
                                        Ub - Lb

There are two special cases regarding the number of markers currently in the map. If the map is
empty there is no special characteristic of the values and the rate between the two is constant,
or 1/1. In the instance that there is only one marker, the marker is not contingent upon a
correlative marker since in either direction is ∞ or 0, and since ∞/∞ and 0/0 is undefined
a query under this state must be treated specially. If end_tempo is not provided, any query past
the last marker would be undefined. per the document there will always be an end_tempo and a
single marker. Therefore if the map is populated with only a single marker then all values will
be processed at the rate of end_tempo. The relationships past the final can be calculated for
given a sample value where tempo is beats per one second (sample unit):

                    b = ((s - Ls) * tempo) + Lb
                  
and to find the converse:

                              b - Lb
                    s = Ls + --------
                              tempo

to calculate the relationship between the first marker and 0 in instance that there are multiple
markers, that first segment is treated as an extension of the segment demarcated by the first
and second markers (or with the above solution using tempo).
