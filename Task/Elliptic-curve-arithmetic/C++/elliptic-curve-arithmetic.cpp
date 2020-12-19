#include <cmath>
#include <iostream>

using namespace std;

// define a type for the points on the elliptic curve that behaves
// like a built in type.  
class EllipticPoint
{
    double m_x, m_y;
    static constexpr double MagicZeroMarker = -99.0;
    static constexpr double B = 7; // the 'b' in y^2 = x^3 + a * x + b
                                  //  'a' is 0
public:
    friend std::ostream& operator<<(std::ostream&, const EllipticPoint&);

    // Create a point that is initialized to Zero
    constexpr EllipticPoint() noexcept : m_x(MagicZeroMarker - 1), m_y(0) {}

    // Create a point based on the yCoordiante.  For a curve with a = 0 and b = 7
    // there is only one x for each y
    explicit EllipticPoint(double yCoordinate) noexcept
    {
        m_y = yCoordinate;
        m_x = cbrt(m_y * m_y - B);
    }

    // Check if the point is 0
    bool IsZero() const noexcept
    {
        // x and y are undefined at the Zero point.  Internally
        // represent Zero with a large negative x.  Such points
        // cannot be on the curve itself.
        bool isBool = m_x <= MagicZeroMarker;
        return isBool;
    }

    // make a negaive version of the point  ( p = -q)
    EllipticPoint operator-() const noexcept
    {
        EllipticPoint negPt;
        negPt.m_x = m_x;
        negPt.m_y = -m_y;
        
        return negPt;
    }

    // add a point to this one  ( p+=q )
    EllipticPoint& operator+=(const EllipticPoint& rhs) noexcept
    {
        if(IsZero())
        {
            *this = rhs;
        }
        else if (rhs.IsZero())
        {
            // since rhs is zero this point does not need to be
            // modified
        }
        else
        {
            double L = (rhs.m_y - m_y) / (rhs.m_x - m_x);
            if(!isfinite(L))
            {
                if(signbit(m_y) != signbit(rhs.m_y))
                {
                    // in this case rhs == -lhs, the result should be 0
                    *this = EllipticPoint();
                    return *this;
                }

                // in this case rhs == lhs.  based on the property
                // of the curve, lhs + rhs + the new value must = 0.
                // the line going through all three points is tangent to
                // curve at rhs (and lhs).  wikipedia has a nice diagram.
                // the math used to calculate L is different.
                L = (3 * m_x * m_x) / (2 * m_y);
            }
            
            double newX = L * L - m_x - rhs.m_x;
            double newY = L * (m_x - newX) - m_y;
            
            if (abs(newY) > 1e20)
            {
                // snap this point to zero
                *this = EllipticPoint();
            }
            else
            {            
                m_x = newX;
                m_y = newY;
            }            
        }

        return *this;
    }

    // multiple the point by an integer ( p *= 3)
    EllipticPoint& operator*=(int rhs) noexcept
    {
        EllipticPoint r;
        EllipticPoint p = *this;

        for (int i = 1; i <= rhs; i <<= 1) 
        {
            if (i & rhs) r += p;
            p += p;
        }

        *this = r;
        return *this;
    }
};

// add points  (p + q)
inline EllipticPoint operator+(EllipticPoint lhs, const EllipticPoint& rhs) noexcept
{
    lhs += rhs;
    return lhs;
}

// multiply by an integer  (p * 3)
inline EllipticPoint operator*(EllipticPoint lhs, const int rhs) noexcept
{
    lhs *= rhs;
    return lhs;
}

// print the point
ostream& operator<<(ostream& os, const EllipticPoint& pt)
{
    if(pt.IsZero()) cout << "(Zero)\n";
    else cout << "(" << pt.m_x << ", " << pt.m_y << ")\n";
    return os;
}

int main(void) {
    const EllipticPoint a(1), b(2);
    cout << "a = " << a;
    cout << "b = " << b;
    const EllipticPoint c = a + b;
    cout << "c = a + b = " << c;
    cout << "a + b + c = " << a + b + c;
    const EllipticPoint d = -c;
    cout << "d = -c = " << d;
    cout << "c + d = " << c + d;
    cout << "a + (b + d) = " << a + (b + d);
    cout << "a * 12345 = " << a * 12345 << "\n";

    const EllipticPoint zero;
    EllipticPoint g;
    cout << "g = zero = " << g;
    cout << "g+=a = " << (g+=a);
    cout << "g+=zero = " << (g+=zero);
    cout << "g+=b = " << (g+=b);
    cout << "g*=2 = " << (g*=2) << "\n";

    EllipticPoint special(0);  // the point where it crosses the x-axis
    cout << "special = " << special; // this has the minimum possible value for x
    cout << "special*=2 = " << (special*=2); // doubling it gives zero. at this point
                                            //  the tangent to the curve is vertical
    
    return 0;
}
