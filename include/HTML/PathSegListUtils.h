#ifndef __PathSegListUtils_h__
#define __PathSegListUtils_h__

namespace System
{
namespace Web
{
class SVGPathSegList;

HTMLEXT void GetPathSegListBBox(SVGPathSegList* seglist, gm::RectD* bbox);
HTMLEXT void GetPathSegListBBox(SVGPathSegList* seglist, gm::Matrix3f matrix, gm::RectD* bbox);
HTMLEXT void GetPathSegListBBox(SVGPathSegList* seglist, gm::Matrix3d matrix, gm::RectD* bbox);
//HTMLEXT void DrawPathSegList(SVGPathSegList* seglist, LDraw::GraphicsPathF* path, SVGMatrix* matrix);

}
}

#endif // __PathSegListUtils_h__
