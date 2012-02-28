#include <stdafx.h>
#include "GUI2.h"
#include <math.h>
//#include "MTypes.h"
//#include "CArray.h"
//#include "SVec3DF.h"

#include "CTriangulator.h"

namespace System
{
///
///     Default constructor
///
CTriangulator::CTriangulator()
{
    //m_points = new CVec3DArray();
}

///
///     Default destructor
///
CTriangulator::~CTriangulator()
{
//    delete m_points;
}

///
///     Adds a point to the contour
///
TVoid CTriangulator::add(const SVec3D& p)
{
    m_points.push_back(p);
}

///
///     Triangulates the contour
///
TVoid CTriangulator::triangulate(CUIntArray& indices)
{
    _process(indices);
}

///
///     Processes the triangulation
///
TVoid CTriangulator::_process(CUIntArray& indices)
{
    const TInt n = m_points.size();
    if (n < 3)
        return;
    TInt *V = new TInt[n];
    if (0.0f < _area())
    {
        for (TInt v = 0; v < n; v++)
            V[v] = v;
    }
    else
    {
        for (TInt v = 0; v < n; v++)
            V[v] = (n - 1) - v;
    }
    TInt nv = n;
    TInt count = 2 * nv;
    for (TInt m = 0, v = nv - 1; nv > 2;)
    {
        if (0 >= (count--))
            return;

        TInt u = v;
        if (nv <= u)
            u = 0;
        v = u + 1;
        if (nv <= v)
            v = 0;
        TInt w = v + 1;
        if (nv <= w)
            w = 0;

        if (_snip(u, v, w, nv, V))
        {
            TInt a, b, c, s, t;
            a = V[u];
            b = V[v];
            c = V[w];
            indices.push_back(a);
            indices.push_back(b);
            indices.push_back(c);
            m++;
            for (s = v, t = v + 1; t < nv; s++, t++)
                V[s] = V[t];
            nv--;
            count = 2 * nv;
        }
    }

    delete V;
}

///
///     Returns the area of the contour
///
TFloat CTriangulator::_area()
{
    TInt n = m_points.size();
    TFloat A = 0.0f;
    for (TInt p = n - 1, q = 0; q < n; p = q++)
    {
        SVec3D pval = m_points[p];
        SVec3D qval = m_points[q];
        A += pval.x * qval.y - qval.x * pval.y;
    }
    return(A * 0.5f);
}
TBool CTriangulator::_snip(TInt u, TInt v, TInt w, TInt n, TInt *V)
{
    TInt p;
    SVec3D A = m_points[V[u]];
    SVec3D B = m_points[V[v]];
    SVec3D C = m_points[V[w]];
    if (FLT_EPSILON > (((B.x - A.x) * (C.y - A.y)) - ((B.y - A.y) * (C.x - A.x))) )
        return false;
    for (p = 0; p < n; p++)
    {
        if ((p == u) || (p == v) || (p == w))
            continue;
        SVec3D P = m_points[V[p]];
        if (_insideTriangle(A, B, C, P))
            return false;
    }
    return true;
}

///
///     Tests if a point is inside the given triangle
///
TBool CTriangulator::_insideTriangle(const SVec3D& A, const SVec3D& B, const SVec3D& C,
    const SVec3D& P)
{
    TFloat ax, ay, bx, by, cx, cy, apx, apy, bpx, bpy, cpx, cpy;
    TFloat cCROSSap, bCROSScp, aCROSSbp;

    ax = C.x - B.x;  ay = C.y - B.y;
    bx = A.x - C.x;  by = A.y - C.y;
    cx = B.x - A.x;  cy = B.y - A.y;
    apx = P.x - A.x;  apy = P.y - A.y;
    bpx = P.x - B.x;  bpy = P.y - B.y;
    cpx = P.x - C.x;  cpy = P.y - C.y;

    aCROSSbp = ax * bpy - ay * bpx;
    cCROSSap = cx * apy - cy * apx;
    bCROSScp = bx * cpy - by * cpx;

    return ((aCROSSbp >= 0.0f) && (bCROSScp >= 0.0f) && (cCROSSap >= 0.0f));
}

}
