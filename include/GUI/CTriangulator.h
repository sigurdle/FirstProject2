#ifndef __CTRIANGULATOR
#define __CTRIANGULATOR

namespace System
{

#define TVoid void
typedef bool TBool;
typedef int TInt;
typedef unsigned int TUInt;
typedef float TFloat;

typedef gm::vector3f SVec3D;
typedef vector<gm::vector3f> CVec3DArray;
typedef vector<int> CUIntArray;

class GUIEXT CTriangulator
{
protected:
    CVec3DArray             m_points;              // points on contour

    ///
    ///     Tests if a point is inside the given triangle
    ///
    TBool _insideTriangle(const SVec3D& A, const SVec3D& B, const SVec3D& C,
        const SVec3D& P);

    ///
    ///     Returns the area of the contour
    ///
    TFloat _area();
    TBool _snip(TInt u, TInt v, TInt w, TInt n, TInt *V);       

    ///
    ///     Processes the triangulation
    ///
    TVoid _process(CUIntArray& indices);

public:
    ///
    ///     Default constructor
    ///
    CTriangulator();

    ///
    ///     Default destructor
    ///
    ~CTriangulator();

    ///
    ///     Adds a point to the contour
    ///
    TVoid add(const SVec3D& p);

    ///
    ///     Triangulates the contour
    ///
    TVoid triangulate(vector<int>& indices);

    ///
    ///     Returns the given point in the triangulator array
    ///
    inline SVec3D get(const TUInt id) { return m_points[id]; }
};

}

#endif
