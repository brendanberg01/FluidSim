//
// Created by Brendan Berg on 15.12.18.
//

#ifndef FLUIDSIM_BOUNDARY_HPP
#define FLUIDSIM_BOUNDARY_HPP

#include <algorithm>
#include <limits>

#include <Utility/Point.hpp>


template <typename T>
struct Boundary
{
    static constexpr T minVal = std::numeric_limits<T>::lowest();
    static constexpr T maxVal = std::numeric_limits<T>::max();

    Point<T> min{maxVal, maxVal, maxVal};
    Point<T> max{minVal, minVal, minVal};

    void EnlargeToPoint (const Point<T>& point)
    {
        min.x = std::min(min.x, point.x);
        max.x = std::max(max.x, point.x);

        min.y = std::min(min.y, point.y);
        max.y = std::max(max.y, point.y);

        min.z = std::min(min.z, point.z);
        max.z = std::max(max.z, point.z);
    }

    Point<T> GetSize () const
    {
        Point<T> result {max.x - min.x, max.y - min.y, max.z - min.z};
        return result;
    }

    Point<T> GetCenterCoordinate () const
    {
        Point<double> result {(max.x + min.x) / 2.0,
                              (max.y + min.y) / 2.0,
                              (max.z + min.z) / 2.0};
        return result;
    }

    bool ContainsPoint (const Point<T>& point) const
    {
        return min.x < point.x && point.x < max.x
            && min.y < point.y && point.y < max.y;
    }

    bool operator== (const Boundary<T>& rhs) const
    {
        return (min == rhs.min) && (max == rhs.max);
    }

    bool operator!= (const Boundary<T>& rhs) const
    {
        return !(*this == rhs);
    }

    static Boundary<T> Combine (const Boundary<T>& lhs, const Boundary<T>& rhs)
    {
        Boundary<T> result;

        result.min.x = std::min(lhs.min.x, rhs.min.x);
        result.max.x = std::max(lhs.max.x, rhs.max.x);

        result.min.y = std::min(lhs.min.y, rhs.min.y);
        result.max.y = std::max(lhs.max.y, rhs.max.y);

        result.min.z = std::min(lhs.min.z, rhs.min.z);
        result.max.z = std::max(lhs.max.z, rhs.max.z);

        return result;
    }


};


#endif //FLUIDSIM_BOUNDARY_HPP
