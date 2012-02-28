#include "StdAfx.h"
#include "X3D2.h"
#include "X3DNode.h"
#include "X3DScene.h"

#include "Quaternion.h"

#include <stdlib.h>	// rand

namespace System
{

/*
class XmlWriter : public IXmlWriter
{
public:

	virtual void BeginElement(StringIn name)
	{
	}

	virtual void EndElement()
	{
	}

	virtual void Attribute(StringIn name, StringIn value)
	{
	}
};
*/

namespace Graphics
{
	void gluDisk(Graphics::Graphics3D* pG, double innerRadius, double outerRadius, int slices, int loops);

/*
 * Convert degrees to radians:
 */
#define DEG_TO_RAD(A)   ((A)*(M_PI/180.0))


#define TXTR_COORD(x,y)    /*if (qobj->TextureFlag)*/ pG->glTexCoordf(x,y)

/*
 * Sin and Cos for degree angles:
 */
#define SIND( A )   sin( (A)*(M_PI/180.0) )
#define COSD( A)    cos( (A)*(M_PI/180.0) )

void X3DEXT gluSphere(Graphics::Graphics3D* pG, double radius, int slices, int stacks)
{
	ASSERT(0);
#if 0

   float rho, drho, theta, dtheta;
   float x, y, z;
   float s, t, ds, dt;
   int i, j, imin, imax;
   bool normals = true;
   float nsign;

 /*  if (qobj->Orientation==GLU_INSIDE)
	{
     nsign = -1.0;
   }
   else
	*/
	{
      nsign = 1.0;
   }
	
   drho = M_PI / (GLfloat) stacks;
   dtheta = 2.0 * M_PI / (GLfloat) slices;

	if (true)
	{
		/* draw +Z end as a triangle fan */
		pG->glBegin( GL_TRIANGLE_FAN );
		pG->glNormalf( 0.0, 0.0, 1.0 );
		TXTR_COORD(0.5,1.0);
		pG->glVertexf( 0.0, 0.0, nsign * radius );
		for (j=0;j<=slices;j++)
		{
			theta = (j==slices) ? 0.0 : j * dtheta;
			x = -sin(theta) * sin(drho);
			y = cos(theta) * sin(drho);
			z = nsign * cos(drho);
			if (normals)  pG->glNormalf( x*nsign, y*nsign, z*nsign );
			pG->glVertexf( x*radius, y*radius, z*radius );
		}
		pG->glEnd();
	}

	ds = 1.0 / slices;
	dt = 1.0 / stacks;
	t = 1.0;  /* because loop now runs from 0 */
/*
	if (qobj->TextureFlag) {
		imin = 0;
		imax = stacks;
	}
	else
*/	{
		imin = 1;
		imax = stacks-1;
	}

	/* draw intermediate stacks as quad strips */
	for (i=imin;i<imax;i++)
	{
		rho = i * drho;
		pG->glBegin( GL_QUAD_STRIP );
		s = 0.0;

		for (j=0;j<=slices;j++)
		{
			theta = (j==slices) ? 0.0 : j * dtheta;
			x = -sin(theta) * sin(rho);
			y = cos(theta) * sin(rho);
			z = nsign * cos(rho);
			if (normals)  pG->glNormalf( x*nsign, y*nsign, z*nsign );
			TXTR_COORD(s,t);
			pG->glVertexf( x*radius, y*radius, z*radius );

			x = -sin(theta) * sin(rho+drho);
			y = cos(theta) * sin(rho+drho);
			z = nsign * cos(rho+drho);
			if (normals)  pG->glNormalf( x*nsign, y*nsign, z*nsign );
			TXTR_COORD(s,t-dt);
			s += ds;
			pG->glVertexf( x*radius, y*radius, z*radius );
		}

		pG->glEnd();
		t -= dt;
	}

	if (true)
	{
		/* draw -Z end as a triangle fan */
		pG->glBegin( GL_TRIANGLE_FAN );
		pG->glNormalf( 0.0, 0.0, -1.0 );
		TXTR_COORD(0.5,0.0);
		pG->glVertexf( 0.0, 0.0, -radius*nsign );
		rho = M_PI - drho;
		s = 1.0;
		t = dt;
		for (j=slices;j>=0;j--)
		{
			theta = (j==slices) ? 0.0 : j * dtheta;
			x = -sin(theta) * sin(rho);
			y = cos(theta) * sin(rho);
			z = nsign * cos(rho);
			if (normals)  pG->glNormalf( x*nsign, y*nsign, z*nsign );
			TXTR_COORD(s,t);
			s -= ds;
			pG->glVertexf( x*radius, y*radius, z*radius );
		}
		pG->glEnd();
	}

	//BuildEdges();
#endif
}

/*
NodeType& X3DAppearanceNode::GetNodeType()
{
	static NodeType nodeType(NULL, typeid(X3DAppearanceNode), 
}
*/

void X3DEXT gluCylinder(Graphics::Graphics3D* pG, double baseRadius, double topRadius, double height, int slices, int stacks)
{
	ASSERT(0);
#if 0

   double da, r, dr, dz;
   float x, y, z, nz, nsign;
   int i, j;
/*
   if (qobj->Orientation==GLU_INSIDE)
	{
      nsign = -1.0;
   }
   else
*/	{
      nsign = 1.0;
   }

   da = 2.0*M_PI / slices;
   dr = (topRadius-baseRadius) / stacks;
   dz = height / stacks;
   nz = (baseRadius-topRadius) / height;  /* Z component of normal vectors */

	if (true)	// Filled
	{
		GLfloat ds = 1.0 / slices;
      GLfloat dt = 1.0 / stacks;
      GLfloat t = 0.0;
      z = 0.0;
      r = baseRadius;

      for (j=0;j<stacks;j++)
		{
         GLfloat s = 0.0;
         pG->glBegin( GL_QUAD_STRIP );
         for (i=0;i<=slices;i++)
			{
            GLfloat x, y;
            if (i == slices)
				{
               x = sin(0.0);
               y = cos(0.0);
            }
            else
				{
               x = sin(i * da);
               y = cos(i * da);
            }
            if (nsign==1.0)
				{
               pG->glNormalf( x*nsign, y*nsign, nz*nsign );
               TXTR_COORD(s, t);
               pG->glVertexf( x * r, y * r, z );
               pG->glNormalf( x*nsign, y*nsign, nz*nsign );
               TXTR_COORD(s, t + dt);
               pG->glVertexf( x * (r + dr), y * (r + dr), z + dz);
            }
            else
				{
               pG->glNormalf( x*nsign, y*nsign, nz*nsign );
               TXTR_COORD(s, t);
               pG->glVertexf( x * r, y * r, z );
               pG->glNormalf( x*nsign, y*nsign, nz*nsign );
               TXTR_COORD(s, t + dt);
               pG->glVertexf( x * (r + dr), y * (r + dr), z + dz);
            }
            s += ds;
         } /* for slices */
         pG->glEnd();
         r += dr;
         t += dt;
         z += dz;
      } /* for stacks */
   }

//	BuildEdges();
#endif
}

void gluDisk(Graphics::Graphics3D* pG, double innerRadius, double outerRadius, int slices, int loops)
{
ASSERT(0);
#if 0

   GLfloat da, dr;
#if 0
   GLdouble a, da;
   GLfloat r, dr;
   GLfloat x, y;
   GLfloat r1, r2, dtc;
   GLint s, l;
#endif

   /* Normal vectors */
   if (true)//qobj->Normals!=GLU_NONE)
	{
      if (true)//qobj->Orientation==GLU_OUTSIDE)
		{
	 pG->glNormalf( 0.0, 0.0, +1.0 );
      }
      else {
	 pG->glNormalf( 0.0, 0.0, -1.0 );
      }
   }

   da = 2.0*M_PI / slices;
   dr = (outerRadius-innerRadius) / (GLfloat) loops;

  // switch (qobj->DrawStyle)
	{
    //  case GLU_FILL:
      {
         /* texture of a gluDisk is a cut out of the texture unit square
          * x, y in [-outerRadius, +outerRadius]; s, t in [0, 1]
          * (linear mapping)
          */
         GLfloat dtc = 2.0f * outerRadius;
         GLfloat sa,ca;
         GLfloat r1 = innerRadius;
         GLint l;
         for (l=0; l<loops; l++) {
	    GLfloat r2 = r1 + dr;
/*
	    if (qobj->Orientation==GLU_OUTSIDE)
		 {
               GLint s;
	       glBegin( GL_QUAD_STRIP );
	       for (s=0;s<=slices;s++) {
                  GLfloat a;
		  if (s==slices) a = 0.0;
		  else  a = s * da;
		  sa = sin(a); ca = cos(a);
                  TXTR_COORD(0.5+sa*r2/dtc,0.5+ca*r2/dtc);
                  glVertex2f( r2*sa, r2*ca );
                  TXTR_COORD(0.5+sa*r1/dtc,0.5+ca*r1/dtc);
                  glVertex2f( r1*sa, r1*ca );
	       }
	       glEnd();
	    }
	    else
		*/
		 {
               GLint s;
	       pG->glBegin( GL_QUAD_STRIP );
	       for (s=slices;s>=0;s--) {
                  GLfloat a;
		  if (s==slices) a = 0.0;
		  else  a = s * da;
		  sa = sin(a); ca = cos(a);
                //  TXTR_COORD(0.5-sa*r2/dtc,0.5+ca*r2/dtc);
                  pG->glVertexf( r2*sa, r2*ca, 0 );
                //  TXTR_COORD(0.5-sa*r1/dtc,0.5+ca*r1/dtc);
                  pG->glVertexf( r1*sa, r1*ca, 0 );
	       }
			pG->glEnd();
	    }
	    r1 = r2;
	 }
     //    break;
      }
#if 0
      case GLU_LINE:
      {
         GLint l, s;
	 /* draw loops */
         for (l=0; l<=loops; l++) {
            GLfloat r = innerRadius + l * dr;
	    glBegin( GL_LINE_LOOP );
            for (s=0; s<slices; s++) {
               GLfloat a = s * da;
	       glVertex2f( r*sin(a), r*cos(a) );
            }
	    glEnd();
	 }
	 /* draw spokes */
         for (s=0; s<slices; s++) {
            GLfloat a = s * da;
	    GLfloat x = sin(a);
	    GLfloat y = cos(a);
	    lglBegin( GL_LINE_STRIP );
            for (l=0; l<=loops; l++) {
               GLfloat r = innerRadius + l * dr;
	       glVertex2f( r*x, r*y );
	    }
	    lglEnd();
	 }
	 break;
      }
      case GLU_POINT:
      {
         GLint s;
	 lglBegin( GL_POINTS );
         for (s=0; s<slices; s++) {
            GLfloat a = s * da;
	    GLfloat x = sin(a);
	    GLfloat y = cos(a);
            GLint l;
            for (l=0; l<=loops; l++) {
               GLfloat r = innerRadius * l * dr;
	       glVertex2f( r*x, r*y );
	    }
	 }
	 lglEnd();
	 break;
      }
      case GLU_SILHOUETTE:
      {
	 if (innerRadius!=0.0) {
            GLfloat a;
	    glBegin( GL_LINE_LOOP );
	    for (a=0.0; a<2.0*M_PI; a+=da) {
	       GLfloat x = innerRadius * sin(a);
	       GLfloat y = innerRadius * cos(a);
	       glVertex2f( x, y );
	    }
	    lglEnd();
	 }
         {
            GLfloat a;
            lglBegin( GL_LINE_LOOP );
            for (a=0; a<2.0*M_PI; a+=da) {
               GLfloat x = outerRadius * sin(a);
               GLfloat y = outerRadius * cos(a);
               glVertex2f( x, y );
            }
            lglEnd();
         }
	 break;
      }
      default:
         abort();
#endif
   }

//	BuildEdges();
#endif
}

}	// LDraw

namespace x3d
{

///////////////////////////////////////////////////////////////////////////////

//#define REMAINDER(t, d) ((t) - (d)*floor((t)/(d)))
inline double REMAINDER(double t, double d)
{
	return ((t) - (d)*floor((t)/(d)));
}

IMP_X3DFIELD0(X3DNode, TypedSFNode<X3DNode*>, metadata, inputOutput)

/*
X3DFieldDefinition* X3DNode::get_metadataFieldDef()
{
	static X3DFieldDefinition metadata(WSTR("metadata"), SAIFieldAccess_inputOutput, offsetof(X3DNode, m_metadata));
	return &metadata;
}
*/

NodeType* X3DNode::GetNodeType()
{
//	static X3DFieldDefinition metadata(WSTR("metadata"), SAIFieldAccess_inputOutput, offsetof(X3DNode, m_metadata));

	static X3DFieldDefinition* fields[] =
	{
		get_metadataFieldDef(),
	};

	static NodeType nodeType(nullptr, typeid(X3DNode), fields, _countof(fields), nullptr);
	return &nodeType;
}

/////////////////////////////////////////////////////////////////////
// All these tables are sorted by name

// Fields

// BIFS MPEG4
X3DFieldDefinition* BitmapFields[] =
{
	&X3DFieldDefinition("scale", FieldType_SFVec2f, SAIFieldAccess_inputOutput),
	/*
	SFVec2f [] scale -1,-1
	*/
};

X3DFieldDefinition* CircleFields[] =
{
	&X3DFieldDefinition("radius", FieldType_SFFloat, SAIFieldAccess_initializeOnly),
	/*
		SFFloat []       radius     1
	*/
};

X3DFieldDefinition* ConditionalFields[] =
{
	&X3DFieldDefinition("activate", FieldType_SFBool, SAIFieldAccess_inputOnly,-1),
	&X3DFieldDefinition("reverseActivate", FieldType_SFBool, SAIFieldAccess_inputOnly,-1),
	&X3DFieldDefinition("buffer", FieldType_SFString, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("isActive", FieldType_SFBool, SAIFieldAccess_outputOnly,-1),
	/*
	eventIn SFBool activate
	eventIn SFBool reverseActivate
	exposedField SFString buffer ""
	eventOut SFBool isActive
	*/
};

X3DFieldDefinition* Curve2DFields[] =	// MPEG-4
{
	&X3DFieldDefinition("fineness", FieldType_SFFloat, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("point", FieldType_SFNode, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("type", FieldType_MFInt32, SAIFieldAccess_inputOutput,-1),
	/*
	exposedField SFNode point NULL
	exposedField SFInt32 fineness 0
	exposedField MFInt32 type []
	*/
};

X3DFieldDefinition* FontStyleFields[] =
{
	&X3DFieldDefinition("family", FieldType_MFString, SAIFieldAccess_initializeOnly,-1),
	&X3DFieldDefinition("justify", FieldType_MFString, SAIFieldAccess_initializeOnly,-1),
	&X3DFieldDefinition("size", FieldType_SFFloat, SAIFieldAccess_initializeOnly,-1),
	&X3DFieldDefinition("style", FieldType_SFString, SAIFieldAccess_initializeOnly,-1),
	&X3DFieldDefinition("topToBottom", FieldType_SFBool, SAIFieldAccess_initializeOnly,-1),
	/*
	SFNode   [in,out] metadata    NULL    [X3DMetadataObject]
	MFString []       family      "SERIF"
	SFBool   []       horizontal  TRUE
	MFString []       justify     "BEGIN" ["BEGIN"|"END"|"FIRST"|"MIDDLE"|""]
	SFString []       language    ""
	SFBool   []       leftToRight TRUE
	SFFloat  []       size        1.0     (0,8)
	SFFloat  []       spacing     1.0     [0,8)
	SFString []       style       "PLAIN" ["PLAIN"|"BOLD"|"ITALIC"|"BOLDITALIC"|""]
	SFBool   []       topToBottom TRUE
	*/
};

X3DFieldDefinition* FormFields[] =
{
	&X3DFieldDefinition("children", FieldType_MFNode, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("size", FieldType_SFVec2f, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("groups", FieldType_MFInt32, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("constraints", FieldType_MFInt32, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("groupsIndex", FieldType_MFInt32, SAIFieldAccess_inputOutput,-1),
	/*
	eventIn MFNode addChildren
	eventIn MFNode removeChildren
	exposedField MFNode children []
	exposedField SFVec2f size -1, -1
	exposedField MFInt32 groups []
	exposedField MFInt32 constraints []
	exposedField MFInt32 groupsIndex []
	*/
};

X3DFieldDefinition* HAnimHumanoidFields[] =
{
	&X3DFieldDefinition("joints", FieldType_MFNode, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("info", FieldType_MFString, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("name", FieldType_SFString, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("rotation", FieldType_SFRotation, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("scale", FieldType_SFVec3f, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("scaleOrientation", FieldType_SFRotation, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("segments", FieldType_MFNode, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("skeleton", FieldType_MFNode, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("skin", FieldType_MFNode, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("translation", FieldType_SFVec3f, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("viewpoints", FieldType_MFNode, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("skinCoord", FieldType_SFNode, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("sites", FieldType_MFNode, SAIFieldAccess_inputOutput,-1),

	/*
	SFVec3f    [in,out] center           0 0 0    (-8,8)
	MFString   [in,out] info             []
	MFNode     [in,out] joints           []       [HAnimJoint]
	SFNode     [in,out] metadata         NULL     [X3DMetadataObject]
	SFString   [in,out] name             ""
	SFRotation [in,out] rotation         0 0 1 0  (-8,8)|[-1,1]
	SFVec3f    [in,out] scale            1 1 1    (0,8)
	SFRotation [in,out] scaleOrientation 0 0 1 0  (-8,8)|[-1,1]
	MFNode     [in,out] segments         []       [HAnimSegment]
	MFNode     [in,out] sites            []       [HAnimSite]
	MFNode     [in,out] skeleton         []       [HAnimJoint]
	MFNode     [in,out] skin             []       [X3DChildNode]
	SFNode     [in,out] skinCoord        NULL     [X3DCoordinateNode]
	SFNode     [in,out] skinNormal       NULL     [X3DNormalNode]
	SFVec3f    [in,out] translation      0 0 0    (-8,8)
	SFString   [in,out] version          ""
	MFNode     [in,out] viewpoints       []       [Viewpoint]
	SFVec3f    []       bboxCenter       0 0 0    (-8,8)
	SFVec3f    []       bboxSize         -1 -1 -1 [0,8) or -1 -1 -1
	*/
};

X3DFieldDefinition* HAnimJointFields[] =
{
	&X3DFieldDefinition("children", FieldType_MFNode, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("center", FieldType_SFVec3f, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("rotation", FieldType_SFRotation, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("scale", FieldType_SFVec3f, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("scaleOrientation", FieldType_SFRotation, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("translation", FieldType_SFVec3f, SAIFieldAccess_inputOutput,-1),
	/*
	MFNode     [in]     addChildren               [HAnimJoint,HAnimSegment,HAnimSite]
	MFNode     [in]     removeChildren            [HAnimJoint,HAnimSegment,HAnimSite]
	SFVec3f    [in,out] center           0 0 0    (-8,8)
	MFNode     [in,out] children         []       [HAnimJoint,HAnimSegment,HAnimSite]
	MFNode     [in,out] displacers       []       [HAnimDisplacer]
	SFRotation [in,out] limitOrientation 0 0 1 0  (-8,8)|[-1,1]
	MFFloat    [in,out] llimit           []       (-8,8)
	SFNode     [in,out] metadata         NULL     [X3DMetadataObject]
	SFString   [in,out] name             ""
	SFRotation [in,out] rotation         0 0 1 0  (-8,8)|[-1,1]
	SFVec3f    [in,out] scale            1 1 1    (0,8)
	SFRotation [in,out] scaleOrientation 0 0 1 0  (-8,8)|[-1,1]
	MFInt32    [in,out] skinCoordIndex   []
	MFFloat    [in,out] skinCoordWeight  []
	MFFloat    [in,out] stiffness        [0 0 0]  [0,1]
	SFVec3f    [in,out] translation      0 0 0    (-8,8)
	MFFloat    [in,out] ulimit           []       (-8,8)
	SFVec3f    []       bboxCenter       0 0 0    (-8,8)
	SFVec3f    []       bboxSize         -1 -1 -1 [0,8) or -1 -1 -1
	*/
};

X3DFieldDefinition* HAnimSegmentFields[] =
{
	&X3DFieldDefinition("children", FieldType_MFNode, SAIFieldAccess_inputOutput),
	/*
	MFNode   [in]     addChildren                          [X3DChildNode]
	MFNode   [in]     removeChildren                       [X3DChildNode]
	SFVec3f  [in,out] centerOfMass     0 0 0               (-8,8)
	MFNode   [in,out] children         []                  [X3DChildNode]
	SFNode   [in,out] coord            NULL                [X3DCoordinateNode]
	MFNode   [in,out] displacers       []                  [HAnimDisplacer]
	SFFloat  [in,out] mass             0                   (0,8)
	SFNode   [in,out] metadata         NULL                [X3DMetadataObject]
	MFFloat  [in,out] momentsOfInertia [0 0 0 0 0 0 0 0 0] [0,8)
	SFString [in,out] name             ""
	SFVec3f  []       bboxCenter       0 0 0               (-8,8)
	SFVec3f  []       bboxSize         -1 -1 -1            [0,8) or -1 -1 -1
	*/
};

X3DFieldDefinition* HAnimSiteFields[] =
{
	&X3DFieldDefinition("children", FieldType_MFNode, SAIFieldAccess_inputOutput),
	/*
	MFNode     [in]     addChildren               [X3DChildNode]
	MFNode     [in]     removeChildren            [X3DChildNode]
	SFVec3f    [in,out] center           0 0 0    (-8,8)
	MFNode     [in,out] children         []       [X3DChildNode]
	SFNode     [in,out] metadata         NULL     [X3DMetadataObject]
	SFString   [in,out] name             ""
	SFRotation [in,out] rotation         0 0 1 0  (-8,8)|[-1,1]
	SFVec3f    [in,out] scale            1 1 1    (0,8)
	SFRotation [in,out] scaleOrientation 0 0 1 0  (-8,8)|[-1,1]
	SFVec3f    [in,out] translation      0 0 0    (-8,8)|[-1,1]
	SFVec3f    []       bboxCenter       0 0 0    (-8,8)
	SFVec3f    []       bboxSize         -1 -1 -1 [0,8) or -1 -1 -1
	*/
};

X3DFieldDefinition* LinePropertiesBIFSFields[] =
{
	&X3DFieldDefinition("metadata", FieldType_SFNode, SAIFieldAccess_inputOutput,-1),

	&X3DFieldDefinition("lineColor", FieldType_SFColor, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("lineStyle", FieldType_SFInt32, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("width", FieldType_SFFloat, SAIFieldAccess_inputOutput,-1),
	/*
	exposedField SFColor lineColor 0, 0, 0
	exposedField SFInt32 lineStyle 0
	exposedField SFFloat width 1.0
	*/
};

// VRML97 2.0 version
X3DFieldDefinition* NurbsCurveFields[] =
{
	&X3DFieldDefinition("closed", FieldType_SFBool, SAIFieldAccess_initializeOnly,-1),
	&X3DFieldDefinition("controlPoint", FieldType_MFVec3f, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("knot", FieldType_MFFloat, SAIFieldAccess_initializeOnly,-1),
	&X3DFieldDefinition("order", FieldType_SFInt32, SAIFieldAccess_initializeOnly,-1),
	&X3DFieldDefinition("weight", FieldType_MFFloat, SAIFieldAccess_inputOutput,-1),
/*
// VRML97

	exposedField  MFVec3f  controlPoint  []    # (-,)
	exposedField  MFFloat  weight        []    # (0,)
	exposedField  SFInt32  tessellation  0     # (-,)
	field         MFFloat  knot          []    # (-,)
	field         SFInt32  order         3     # [2,)

// X3D
	SFNode   [in,out] controlPoint []    [X3DCoordinateNode]
	SFNode   [in,out] metadata     NULL  [X3DMetadataObject]
	SFInt32  [in,out] tessellation 0     (-8,8)
	MFDouble [in,out] weight       []    (0,8)
	SFBoolean[]       closed       FALSE 
	MFDouble []       knot         []    (-8,8)
	SFInt32  []       order        3     [2,8)
*/
};

// VRML97, X3D has renamed and slighty changed it to NurbsPatchSurface
X3DFieldDefinition* NurbsSurfaceFields[] =
{
	&X3DFieldDefinition("controlPoint", FieldType_MFVec3f, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("weight", FieldType_MFFloat, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("ccw", FieldType_SFBool, SAIFieldAccess_initializeOnly,-1),
	&X3DFieldDefinition("solid", FieldType_SFBool, SAIFieldAccess_initializeOnly,-1),
	&X3DFieldDefinition("uDimension", FieldType_SFInt32, SAIFieldAccess_initializeOnly,-1),
	&X3DFieldDefinition("vDimension", FieldType_SFInt32, SAIFieldAccess_initializeOnly,-1),
	&X3DFieldDefinition("uKnot", FieldType_MFFloat, SAIFieldAccess_initializeOnly,-1),
	&X3DFieldDefinition("vKnot", FieldType_MFFloat, SAIFieldAccess_initializeOnly,-1),
	&X3DFieldDefinition("uOrder", FieldType_SFInt32, SAIFieldAccess_initializeOnly,-1),
	&X3DFieldDefinition("vOrder", FieldType_SFInt32, SAIFieldAccess_initializeOnly,-1),

	/*
	exposedField  MFVec3f controlPoint    []     # (,)
	exposedField  SFNode  texCoord        []
	exposedField  SFInt32 uTessellation   0      # (-,)
	exposedField  SFInt32 vTessellation   0      # (-,)
	exposedField  MFFloat weight          []     # (0,)
	field         SFBool  ccw             TRUE
	field         SFBool  solid           TRUE
	field         SFInt32 uDimension      0      # [0,)
	field         MFFloat uKnot           []     # (-,)
	field         SFInt32 uOrder          3      # [2,) 
	field         SFInt32 vDimension      0      # [0,)
	field         MFFloat vKnot           []     # (-,)
	field         SFInt32 vOrder          3      # [2,)
  */
};

X3DFieldDefinition* ParticlesFields[] =
{
	&X3DFieldDefinition("creationRate", FieldType_SFFloat, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("creationRateVariation", FieldType_SFFloat, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("emitAlpha", FieldType_SFFloat, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("emitColor", FieldType_SFColor, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("emitColorVariation", FieldType_SFColor, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("emitterPosition", FieldType_SFVec3f, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("emitVelocity", FieldType_SFVec3f, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("emitVelocityVariation", FieldType_SFVec3f, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("enabled", FieldType_SFBool, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("fadeAlpha", FieldType_SFFloat, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("fadeColor", FieldType_SFColor, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("fadeRate", FieldType_SFFloat, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("force", FieldType_SFVec3f, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("influences", FieldType_MFNode, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("maxLifeTime", FieldType_SFTime, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("maxLifeTimeVariation", FieldType_SFFloat, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("maxParticles", FieldType_SFInt32, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("particleRadius", FieldType_SFFloat, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("particleRadiusVariation", FieldType_SFFloat, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("particleRadiusRate", FieldType_SFFloat, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("primitive", FieldType_SFNode, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("primitiveType", FieldType_SFInt32, SAIFieldAccess_inputOutput,-1),

/*
	SFFloat exposedField creationRate 500 
	SFFloat exposedField creationRateVariation 0 
	SFFloat exposedField emitAlpha 1.0 
	SFColor exposedField emitColor 1 1 1 
	SFColor exposedField emitColorVariation 0 0 0 
	SFVec3f exposedField emitterPosition 0 3 0 
	SFVec3f exposedField emitVelocity 0 0 0 
	SFVec3f exposedField emitVelocityVariation 1 1 1 
	SFBool exposedField enabled TRUE 
	SFFloat exposedField fadeAlpha 1.0 
	SFColor exposedField fadeColor 0.25 0.25 0.25 
	SFFloat exposedField fadeRate 0.25 
	SFVec3f exposedField force 0 -9.8 0 
	MFInfluenceNode exposedField influences [] 
	SFWorldNode exposedField init NULL 
	SFTime exposedField maxLifeTime 5 
	SFFloat exposedField maxLifeTimeVariation 0 
	SFInt32 exposedField maxParticles 500 
	SFFloat exposedField minRange 1 
	SFFloat exposedField maxRange 100 
	SFFloat exposedField particleRadius 0.1 
	SFFloat exposedField particleRadiusVariation 0 
	SFFloat exposedField particleRadiusRate 0 
	SFWorldNode exposedField primitive NULL 
	SFInt32 exposedField primitiveType 2 
	*/
};

X3DFieldDefinition* PlanarObstacleFields[] =
{
//	WSTR("distance"), SFVec3f, SAIFieldAccess_inputOutput,
	&X3DFieldDefinition("distance", FieldType_SFFloat, SAIFieldAccess_inputOutput,-1),	// ??
	&X3DFieldDefinition("normal", FieldType_SFVec3f, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("reflection", FieldType_SFFloat, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("absorption", FieldType_SFFloat, SAIFieldAccess_inputOutput,-1),
	/*
	SFVec3f exposedField distance 0 0 0 
	SFVec3f exposedField normal 0 1 0 
	SFFloat exposedField reflection 0 
	SFFloat exposedField absorption 0  
	*/
};

X3DFieldDefinition* ValuatorFields[] =
{
	&X3DFieldDefinition("factor1", FieldType_SFFloat, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("factor2", FieldType_SFFloat, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("factor3", FieldType_SFFloat, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("factor4", FieldType_SFFloat, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("inSFBool", FieldType_SFBool, SAIFieldAccess_inputOnly,-1),
	&X3DFieldDefinition("inMFColor", FieldType_SFColor, SAIFieldAccess_inputOnly,-1),
	&X3DFieldDefinition("inMFColor", FieldType_MFColor, SAIFieldAccess_inputOnly,-1),
	&X3DFieldDefinition("offset1", FieldType_SFFloat, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("offset2", FieldType_SFFloat, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("offset3", FieldType_SFFloat, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("offset4", FieldType_SFFloat, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("sum", FieldType_SFBool, SAIFieldAccess_inputOutput,-1),
/*
	eventIn SFBool inSFBool
	eventIn SFColor inSFColor
	eventIn MFColor inMFColor
	eventIn SFFloat inSFFloat
	eventIn MFFloat inMFFloat
	eventIn SFInt32 inSFInt32
	eventIn MFInt32 inMFInt32
	eventIn SFRotation inSFRotation
	eventIn MFRotation inMFRotation
	eventIn SFString inSFString
	eventIn MFString inMFString
	eventIn SFTime inSFTime
	eventIn SFVec2f inSFVec2f
	eventIn MFVec2f inMFVec2f
	eventIn SFVec3f inSFVec3f
	eventIn MFVec3f inMFVec3f
	eventOut SFBool outSFBool
	eventOut SFColor outSFColor
	eventOut MFColor outMFColor
	eventOut SFFloat outSFFloat
	eventOut MFFloat outMFFloat
	eventOut SFInt32 outSFInt32
	eventOut MFInt32 outMFInt32
	eventOut SFRotation outSFRotation
	eventOut MFRotation outMFRotation
	eventOut SFString outSFString
	eventOut MFString outMFString
	eventOut SFTime outSFTime
	eventOut SFVec2f outSFVec2f
	eventOut MFVec2f outMFVec2f
	eventOut SFVec3f outSFVec3f
	eventOut MFVec3f outMFVec3f
	exposedField SFFloat factor1 1.0
	exposedField SFFloat factor2 1.0
	exposedField SFFloat factor3 1.0
	exposedField SFFloat factor4 1.0
	exposedField SFFloat offset1 0.0
	exposedField SFFloat offset2 0.0
	exposedField SFFloat offset3 0.0
	exposedField SFFloat offset4 0.0
	exposedField SFBool sum FALSE
	*/
};

/*
///////////////////////////////////////////////////////////////////
// Node Types
CNodeType nodeTypes[] =
{
	WSTR("Anchor"), AnchorFields,
	WSTR("Appearance"), AppearanceFields,
	WSTR("AudioClip"), AudioClipFields,
	WSTR("AudioSource"), AudioSourceFields,	// MPEG4
	WSTR("Background"), BackgroundFields,
	WSTR("Background2D"), Background2DFields,	// MPEG4
	WSTR("Bitmap"), BitmapFields,	// MPEG4
	WSTR("Billboard"), BillboardFields,
	WSTR("Box"), BoxFields,
	WSTR("Circle"), CircleFields,	// MPEG4
//	TODO WSTR("Circle2D"), CircleFields,
	WSTR("Collision"), CollisionFields,
	WSTR("Color"), ColorFields,
	WSTR("ColorInterpolator"), ColorInterpolatorFields,
	WSTR("Conditional"), ConditionalFields,
	WSTR("Cone"), ConeFields,
	WSTR("Coordinate"), CoordinateFields,
	WSTR("Coordinate2D"), Coordinate2DFields,	// MPEG4
	WSTR("CoordinateInterpolator"), CoordinateInterpolatorFields,
	WSTR("CoordinateInterpolator2D"), CoordinateInterpolator2DFields,
	WSTR("Curve2D"), Curve2DFields,	// MPEG4
	WSTR("Cylinder"), CylinderFields,
	WSTR("DirectionalLight"), DirectionalLightFields,
	WSTR("ElevationGrid"), ElevationGridFields,
	WSTR("Extrusion"), ExtrusionFields,
	WSTR("Fog"), FogFields,
	WSTR("FontStyle"), FontStyleFields,
	WSTR("Form"), FormFields,
	WSTR("Group"), GroupFields,
	WSTR("HAnimHumanoid"), HAnimHumanoidFields,	// H-Anim
	WSTR("HAnimJoint"), HAnimJointFields,	// H-Anim
	WSTR("HAnimSegment"), HAnimSegmentFields,	// H-Anim
	WSTR("HAnimSite"), HAnimSiteFields,	// H-Anim
	WSTR("ImageTexture"), ImageTextureFields,
	WSTR("IndexedFaceSet"), IndexedFaceSetFields,
	WSTR("IndexedFaceSet2D"), IndexedFaceSet2DFields,		// MPEG4
	WSTR("IndexedLineSet"), IndexedLineSetFields,
	WSTR("IndexedLineSet2D"), IndexedLineSet2DFields,		// MPEG4
	WSTR("Inline"), InlineFields,
	WSTR("Layer3D"), Layer3DFields,	// MPEG4
	WSTR("LineProperties"), LinePropertiesFields,
	WSTR("LinePropertiesBIFS"), LinePropertiesBIFSFields,
	WSTR("LOD"), LODFields,
	WSTR("Material"), MaterialFields,
	WSTR("Material2D"), Material2DFields,	// MPEG4
	WSTR("MovieTexture"), MovieTextureFields,
	WSTR("MultiTexture"), MultiTextureFields,
	WSTR("MultiTextureCoordinate"), MultiTextureCoordinateFields,
	WSTR("NavigationInfo"), NavigationInfoFields,
	WSTR("Normal"), NormalFields,
	WSTR("NurbsCurve"), NurbsCurveFields,	// slightly different between VRML97 and X3D
	WSTR("NurbsSurface"), NurbsSurfaceFields,	// VRML97 backward compatible
	WSTR("OrderedGroup"), OrderedGroupFields,
	WSTR("OrientationInterpolator"), OrientationInterpolatorFields,
	WSTR("OrthoViewpoint"), OrthoViewpointFields,
	WSTR("Particles"), ParticlesFields,	// MPEG4
	WSTR("PixelTexture"), PixelTextureFields,
	WSTR("PlanarObstacle"), PlanarObstacleFields,	// MPEG4
	WSTR("PointLight"), PointLightFields,
	WSTR("PositionInterpolator"), PositionInterpolatorFields,
	WSTR("PositionInterpolator2D"), PositionInterpolator2DFields,	// MPEG4
	WSTR("ProximitySensor"), ProximitySensorFields,
	WSTR("QuantizationParameter"), QuantizationParameterFields,
	WSTR("Rectangle"), RectangleFields,	// MPEG4
	WSTR("Rectangle2D"), Rectangle2DFields,
	WSTR("ScalarInterpolator"), ScalarInterpolatorFields,
	WSTR("Script"), ScriptFields,
	WSTR("Shape"), ShapeFields,
	WSTR("Sound"), SoundFields,
	WSTR("Sound2D"), Sound2DFields,
	WSTR("Sphere"), SphereFields,
	WSTR("SpotLight"), SpotLightFields,
	WSTR("Switch"), SwitchFields,
	WSTR("Text"), TextFields,
	WSTR("TextureCoordinate"), TextureCoordinateFields,
	WSTR("TextureCoordinateGenerator"), TextureCoordinateGeneratorFields,
	WSTR("TextureTransform"), TextureTransformFields,
	WSTR("TimeSensor"), TimeSensorFields,
	WSTR("TouchSensor"), TouchSensorFields,
	WSTR("Transform"), TransformFields,
	WSTR("Transform2D"), Transform2DFields,	// MPEG4
	WSTR("TriangleSet"), TriangleSetFields,
	WSTR("TriangleStripSet"), TriangleStripSetFields,
	WSTR("Valuator"), ValuatorFields,
	WSTR("Viewpoint"), ViewpointFields,
	WSTR("WorldInfo"), WorldInfoFields,
	NULL
};
*/

String X3DFieldDefinition::getFieldTypeString()
{
	return x3d::ToString(getFieldType());
}

X3DEXT TextDocument* asvrml(X3DNode* node)
{
	TextDocument* td = new TextDocument;
	td->IncRef();
	AddView(node, td);
	td->m_Mimetype = "model/x3d+vrml";
	node->WriteVRML(*td);
	return td;
}

void xmlNodes(IXmlWriter* xmlwriter, MFNode* mfnode)
{
	uint nitems = mfnode->get_size();
	for (uint i = 0; i < nitems; ++i)
	{
		asxml(xmlwriter, mfnode->get1Value(i));
	}
}

X3DEXT void asxml(IXmlWriter* xmlwriter, X3DNode* x3dnode)
{
	xmlwriter->BeginElement(x3dnode->getNodeName());

	if (false)
	{
		xmlwriter->Attribute(L"USE", x3dnode->getDefName());
	}
	else
	{
		if (x3dnode->getDefName() != nullptr)
		{
			xmlwriter->Attribute(L"DEF", x3dnode->getDefName());
			SetUserData(dynamic_cast<Object*>(xmlwriter), x3dnode->getDefName(), x3dnode);
		}

		uint nfields = x3dnode->getFieldCount();

		for (uint i = 0; i < nfields; ++i)
		{
			X3DField* field = x3dnode->getField(i);

			if (field->getFieldType() != FieldType_SFNode &&
				field->getFieldType() != FieldType_MFNode)
			{
				if (field->getFieldName())
				{
				//	if (field->m_fieldDef)
				//	{
				//		if (field->SameValueAs(field->m_fieldDef->getDef))
					xmlwriter->Attribute(field->getFieldName(), field->getValueAsString());
				}
			}
		}

		for (uint i = 0; i < nfields; ++i)
		{
			X3DField* field = x3dnode->getField(i);

			if (field->getFieldType() == FieldType_SFNode)
			{
				X3DNode* value = static_cast<SFNode*>(field)->getValue();
				if (value)
				{
					asxml(xmlwriter, value);
				}
			}
			else if (field->getFieldType() == FieldType_MFNode)
			{
				MFNode* mfnode = static_cast<MFNode*>(field);
				xmlNodes(xmlwriter, mfnode);
			}
		}
	}

	xmlwriter->EndElement();
}

//////////////////////////////////////////////////////////////////////
// X3DNode

NodeType X3DNodeAVL::avlnodeType("header", typeid(X3DNodeAVL), nullptr, 0);

X3DNode::X3DNode(NodeType* nodeType) :
	m_metadata(new TypedSFNode<X3DNode*>(get_metadataFieldDef(), this))
//	m_metadata(new TypedSFNode<X3DMetadataObject*>(get_metadataFieldDef(), this))
{
	m_scene = nullptr;
	
	uint count = nodeType->m_fieldDefinitions->get_length();

	for (uint i = 0; i < count; ++i)
	{
		X3DFieldDefinition* def = nodeType->m_fieldDefinitions->item(i);

		X3DField** ppField = (X3DField**)((uint8*)this + def->m_offset);

		ASSERT(def->m_offset > 0);

		if (*ppField == NULL)
		{
			*ppField = X3DField::CreateFieldOfType(def->getFieldType(), this);	// TODO remove
		}

#if 0
		X3DField* pField = *ppField;

		pField->m_fieldAccess = def->getAccessType();
		pField->m_fieldName = def->getName();

		//m_fields.push_back(def->m_offset);
		m_fields.push_back(pField);
#endif

		/*
		if ((int)pField->m_fieldAccess & 1)	// input
		{
			X3DField* pField = new X3DField;
			pField->m_fieldType = m_p->fields[i].fieldType;
			pField->m_fieldAccess = m_p->fields[i].fieldAccess;
			pField->m_fieldName = m_p->fields[i].fieldName;

			// Create field value (?)
			pField->m_value = <CFieldValue>(CreateFieldOfType(pField->m_fieldType));
			ASSERT(pField->m_value);

			p->m_fields.Add(pField);

		}
		*/
	}

// Cache pointers to relevant fields
//	m_metadata = static_cast<SFNode*>(getField(WSTR("metadata")));
//	VERIFY(m_metadata);
}

X3DNode::~X3DNode()
{
	/*
	for (int i = 0; i < m_fields.GetSize(); i++)
	{
		;//	m_fields[i]->Release();
	}
	m_fields.RemoveAll();
	*/
}

NodeType* X3DNode::getType() const
{
	return static_cast<NodeType*>(GetType()->GetUserData(L"System::x3d::NodeType"));
}

#if 0
void X3DNode::setMetadata(X3DMetadataObject* metadata)
{
	if (metadata == NULL)
	{
		m_metadata->setValue((X3DNode*)NULL);
	}
	else
	{
		X3DNode* node = dynamic_cast<X3DNode*>(metadata);
		if (node == NULL)
			raise(Exception(L"metadata to X3DNode cast failed"));

		m_metadata->setValue(node);
	}
}
#endif

MFNode* X3DNode::GetFirstParentOfFieldName(StringIn fieldName)
{
	for (uint i = 0; i < m_parents.GetSize(); i++)
	{
		if (m_parents[i]->getFieldName() == fieldName)
		{
			return m_parents[i];
		}
	}

	return NULL;
}

X3DNode* X3DNode::GetFirstParentNodeOfFieldName(StringIn fieldName)
{
	for (uint i = 0; i < m_parents.GetSize(); i++)
	{
		if (m_parents[i]->getFieldName() == fieldName)
		{
			return m_parents[i]->getOwnerNode();
		}
	}

	return NULL;
}

void X3DNode::RemoveParent(MFNode* mfnode)
{
	for (uint i = 0; i < m_parents.GetSize(); i++)
	{
		if (m_parents[i] == mfnode)
		{
			m_parents.RemoveAt(i);
			return;
		}
	}
}

#if 0
template<class T> class string_buffer : public array<T>
{
public:
	CTOR string_buffer(const T* cstr) : array<T>(cstr, strlen(cstr))
	{
	}

	bool operator < (const string_buffer& other) const
	{
		return 0;
	}

	bool operator < (StringW* other) const
	{
		return 0;
	}
};

class StringLess
{
public:

	bool operator () (const StringW* x, const StringW* y) const
	{
		return *x < *y;
	}

	bool operator () (const StringW* x, const WCHAR* y) const
	{
		return x->Compare(y) < 0;
	}

	bool operator () (const WCHAR* x, const StringW* y) const
	{
		return y->Compare(x) > 0;
	}

	/*
	bool operator () (const StringW* x, const string_buffer<WCHAR>& y) const
	{
		return x->Compare(y.begin()) < 0;
	}

	bool operator () (const string_buffer<WCHAR>& x, const StringW* y) const
	{
		return y->Compare(x.begin()) > 0;
	}
	*/
};

X3DField* /*X3DNode::*/ getField(string_buffer<WCHAR> fieldName)
{
	map<StringW*, Object*, StringLess> test;

	StringW* key = NULL;

	test.find(L"Hello");

	return NULL;
}
#endif

void X3DNode::OnFieldChanged(X3DField* pField)
{
	get_FieldChanged()(this, pField);

	if (m_scene)
	{
		m_scene->Invalidate();
	}
}

X3DField* X3DNode::getField(uint index)
{
	NodeType* nodeType = getType();
	X3DFieldDefinition* def = nodeType->m_fieldDefinitions->item(index);

	X3DField* field = *(X3DField**)((uint8*)this + def->m_offset);

	return field;
}

uint X3DNode::getFieldCount()
{
	return getType()->m_fieldDefinitions->get_length();
}

X3DField* X3DNode::getField(StringIn fieldName)
{
	NodeType* nodeType = getType();

	uint count = nodeType->m_fieldDefinitions->get_length();

	for (uint i = 0; i < count; ++i)
	{
		X3DFieldDefinition* def = nodeType->m_fieldDefinitions->item(i);

		X3DField* field = *(X3DField**)((uint8*)this + def->m_offset);

		if (def->getName() == fieldName)
		{
			return field;
		}

		if ((int)def->m_fieldAccess & 1)	// input
		{
		//	syschar str[256];
		//	swprintf(str, WSTR("set_%s"), m_fields[i]->m_fieldName.c_str());
		//	WCHAR buf[256];
		//	swprintf_s(buf, L"set_%s", m_fields[i]->getFieldName());

		//	StringW* str = *WSTR("set_") + *m_fields[i]->m_fieldName;

			if (fieldName == L"set_" + def->getName())
			{
				return field;
			}
		}

		if ((int)def->m_fieldAccess & 2)	// output
		{
		//	WCHAR buf[256];
		//	swprintf_s(buf, L"%s_changed", m_fields[i]->getFieldName()->c_str());

		//	StringW* str = *m_fields[i]->m_fieldName + *WSTR("_changed");

			if (fieldName == def->getName() + L"_changed")
			{
				return field;
			}
		}
	}

	return NULL;
}

#if 0
void RouteDestination::Set()
{
	X3DNode* destNode = m_node;//pSourceField->m_outputRoutes[i]->m_destinationNode;
	if (destNode)
	{
		X3DField* pDestField = m_field;//destNode->getField(pSourceField->m_outputRoutes[i]->m_destinationField);

		if (pDestField)
		{
			destNode->Set(pSourceField, pDestField);
		}
	}
}
#endif

// virtual
void X3DNode::Change(X3DField* pSourceField)
{
	OnFieldChanged(pSourceField);	// Not absolutely sure about this

// Also send it along any routes
	for (int i = 0; i < pSourceField->m_outputRoutes.GetSize(); i++)
	{
		X3DField* pDestField = pSourceField->m_outputRoutes[i]->m_destination;
		X3DNode* pDestNode = pDestField->getOwnerNode();

		pDestNode->Set(pSourceField, pDestField);
	}
}

// virtual
void X3DNode::Set(X3DField* pSourceField, X3DField* pDestField)
{
	if (pSourceField->getFieldType() == pDestField->getFieldType())	// Fields must (almost?) always be of same type
	{
		pDestField->CopyFrom(pSourceField);

		OnFieldChanged(pDestField);

		//Change(pDestField);
	}
}

////////////////
//

X3DDrawContext::X3DDrawContext()
{
#if 0
	m_pGraphics3D = NULL;
#endif
//	m_pGraphics2D = NULL;
//	m_pBrush = NULL;

	m_nName = 0;
//	m_nLight = 0;
}


///////////////////////////////////////////////////////////////////////////
// X3DPrototypeInstance

NodeType* X3DPrototypeInstance::nodeType = NULL;

void X3DPrototypeInstance::ReplaceISFieldsWithInstanceFields(X3DNode* pFrom, X3DNode* pNode)
{
	ASSERT(0);
#if 0

	for (int i = 0; i < pNode->m_fields.GetSize(); i++)
	{
		X3DField* pFromField = pFrom->getField(i);
		X3DField* pField = pNode->getField(i);

		if (pFromField->m_is && pFromField->m_is.GetLength())
		{
			int i;
			for (i = 0; i < m_fields.GetSize(); i++)
			{
				if (getField(i)->getFieldName() == pFromField->m_is)
				{
					pField->CopyFrom(getField(i));
					break;
				}
			}
			ASSERT(i < m_fields.GetSize());
		}
		else
		{
			if (pField->getFieldType() == FieldType_SFNode)
			{
				if (static_cast<SFNode*>(pField)->getValue())
				{
					ReplaceISFieldsWithInstanceFields(static_cast<SFNode*>(pFromField)->getValue(), static_cast<SFNode*>(pField)->getValue());
				}
			}
			else if (pField->getFieldType() == FieldType_MFNode)
			{
				for (int i = 0; i < static_cast<MFNode*>(pField)->m_items.GetSize(); i++)
				{
					if (static_cast<MFNode*>(pField)->m_items[i])
					{
						ReplaceISFieldsWithInstanceFields(static_cast<MFNode*>(pFromField)->m_items[i], static_cast<MFNode*>(pField)->m_items[i]);
					}
				}
			}
		}
	}
#endif
}

////////////////////////////////////////////////////////////////
// CLSAIProtoDeclaration

X3DPrototypeInstance* SAIProtoDeclaration::createInstance()
{
	ASSERT(0);
	X3DPrototypeInstance* pInstance = new X3DPrototypeInstance;
#if 0

	pInstance->m_protoDecl = this;

	// Create readwrite fields on the instantiated node
	// (the fields, their types and default values are defined on the prototype declaration)
	{
		for (int i = 0; i < m_fields.GetSize(); i++)
		{
			X3DField* pField = CreateFieldOfType(m_fields[i]->getFieldType(), pInstance);

			//X3DField* pField = new X3DField;
			//pField->m_fieldType = m_fields[i]->m_fieldType;
			pField->m_fieldAccess = m_fields[i]->m_fieldAccess;
			pField->m_fieldName = m_fields[i]->m_fieldName;

			// initial value
			pField->CopyFrom(m_fields[i]);

			//pField->m_ownerNode = pInstance;
			pInstance->m_fields.Add(pField);
		}

		// clone first node
		{
			pInstance->m_node = m_nodes[0]->m_scene->CreateNodeOfType(m_nodes[0]->getType());

			// clone fields
			for (int i = 0; i < (pInstance->m_node)->m_fields.GetSize(); i++)
			{
				(pInstance->m_node)->m_fields[i]->CopyFrom(m_nodes[0]->m_fields[i]);
			}
		}
	}
#endif
	return pInstance;
}

////////////////////////////////////////////////////////////////
//

#if 0
class CLHAnimHumanoid : 
	public ILHAnimHumanoid,
	public X3DBoundedObject,

	//public X3DNode,
	public RenderImplImpl
{
public:
	CLHAnimHumanoid()
	{
	// Cache pointers to relevant fields
		m_skeleton = static_cast<MFNode*>(getField(WSTR("skeleton")));
	}

	MFNode* m_skeleton;

	virtual void Draw(X3DDrawContext* pDC)
	{
		int nLight = pDC->m_nLight;
		int nNames = pDC->m_namedNodes.GetSize();

		int i;

		for (i = 0; i < m_skeleton->m_items.GetSize(); i++)
		{
			X3DNode* node = m_skeleton->m_items[i];

			if (node)
			{
				RenderImplImpl* render = dynamic_cast<RenderImplImpl*>(node->GetNode());
				if (render)
				{
					render->PreDraw(pDC);
				}
			}
		}

		for (i = 0; i < m_skeleton->m_items.GetSize(); i++)
		{
			X3DNode* node = m_skeleton->m_items[i];

			if (node)
			{
				RenderImplImpl* render = dynamic_cast<RenderImplImpl*>(node->GetNode());
				if (render)
				{
					render->Draw(pDC);
				}
			}
		}

		for (i = pDC->m_namedNodes.GetSize(); i >= nNames; i--)
		{
#if USE_GL
			glPopName();
#endif
		}
		for (i = pDC->m_nLight; i >= nLight; i--)
		{
			pDC->m_pGraphics3D->glDisable(GL_LIGHT0+i);
		}
		pDC->m_nLight = nLight;
	}

	/*
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLHAnimHumanoid)
	COM_INTERFACE_ENTRY(ILHAnimHumanoid)

	COM_INTERFACE_ENTRY(ILX3DChildNode)
	COM_INTERFACE_ENTRY(ILX3DNode)

	COM_INTERFACE_ENTRY(ILX3DBoundedObject)
	//COM_INTERFACE_ENTRY(ILX3DBounded3DObject)	// ??
	COM_INTERFACE_ENTRY(ILX3DObject)

	COM_INTERFACE_ENTRY(ILSAINode)	// ???

	COM_INTERFACE_ENTRY(X3DNode)
	COM_INTERFACE_ENTRY(CLRenderImplImpl)
END_COM_MAP()
*/
};

class  CLHAnimJoint : 
	public ILHAnimJoint,

//	public X3DNode,
	public RenderImplImpl
{
public:
	CLHAnimJoint()
	{
	// Cache pointers to relevant fields
		m_C = static_cast<SFVec3f*>(getField(WSTR("center")));
		m_R = static_cast<SFRotation*>(getField(WSTR("rotation")));
		m_S = static_cast<SFVec3f*>(getField(WSTR("scale")));
		m_SR = static_cast<SFRotation*>(getField(WSTR("scaleOrientation")));
		m_T = static_cast<SFVec3f*>(getField(WSTR("translation")));
		m_children = static_cast<MFNode*>(getField(WSTR("children")));

	// Set defaults
		m_S->m_value[0] = m_S->m_value[1] = m_S->m_value[2] = 1.0;
	}

	SFVec3f* m_C;
	SFRotation* m_R;
	SFVec3f* m_S;
	SFRotation* m_SR;
	SFVec3f* m_T;
	MFNode* m_children;

	virtual void Draw(X3DDrawContext* pDC);

};

class  CLHAnimSegment :
	public ILHAnimSegment,

//	public X3DNode,
	public RenderImplImpl
{
public:
	CLHAnimSegment()
	{
	// Cache pointers to relevant fields
		m_children = static_cast<MFNode*>(getField(WSTR("children")));
	}

	MFNode* m_children;

	virtual void Draw(X3DDrawContext* pDC);

};

class  CLHAnimSite :
	public ILHAnimSite,

//	public X3DNode,
	public RenderImplImpl
{
public:
	CLHAnimSite()
	{
	}


	virtual void Draw(X3DDrawContext* pDC)
	{
	}

};
#endif

#if 0
	class CAudioFilter :
		public LMedia::BaseFilterImpl,
		public LMedia::IMediaSeeking
	{
	public:


	class CInputPin : 
		public LMedia::BasePinImpl,
		public LMedia::IMemInputPin
	{
	public:
		class CMemAllocator : 
			public LMedia::IMemAllocator
		{
		public:
			class CAudioSample : 
				public LMedia::CLMediaSampleImpl<LMedia::IMediaSample>
			{
			public:
				CAudioSample()
				{
				//	m_mediaType = NULL;
					m_pointer = NULL;
				}

				/*
				void FinalRelease()
				{
					if (m_pointer)
					{
						GlobalFree(m_pointer);
						m_pointer = NULL;
					}
				}
				*/

				uint8* m_pointer;
				DWORD m_dwBytes;
				ULONG m_ActualDataLength;

				CInputPin* m_pInput;
				//ILAudioMediaType* m_mediaType;
				/*
				DWORD dwbuffer1;
				LPBYTE buffer1;

				DWORD dwbuffer2;
				LPBYTE buffer2;
				*/

			public:
				ErrorCode LockBits(LMedia::LSampleData* pVal)
				{
					pVal->idata = m_pointer;

					/*
					ULONG nSamples;
					m_mediaType->GetSamples(&nSamples);

					ErrorCode hr = m_pInput->m_dsBuffer8->Lock(m_pInput->m_dwOffset, nSamples*m_pInput->m_wf.nBlockAlign, (void**)&buffer1, &dwbuffer1, (void**)&buffer2, &dwbuffer2, 0);
					ASSERT(SUCCEEDED(hr));

					*pVal = (LPBYTE)buffer1;
					*/

					return S_OK;
				}

				ErrorCode UnlockBits()
				{
					/*
					m_pInput->m_dsBuffer8->Unlock(buffer1, dwbuffer1, buffer2, dwbuffer2);
					*/
					return S_OK;
				}

#if 0
				STDMETHOD(GetMediaType)(LMediaType **ppmt)
				{
					ASSERT(0);
					return S_OK;
					//*pVal = m_mediaType;
					//(*pVal)->AddRef();
				}
#endif

				virtual ULONG GetActualDataLength()
				{
					return m_ActualDataLength;
				}
				virtual ErrorCode SetActualDataLength(ULONG length)
				{
					// TODO
					if (length > m_dwBytes)
					{
						ASSERT(0);
						return VFW_E_BUFFER_OVERFLOW;
					}

					m_ActualDataLength = length;

					return S_OK;
				}
			};

			CMemAllocator()
			{
				m_pInput = NULL;
			}

			CInputPin* m_pInput;

		public:
			ErrorCode GetBuffer(DWORD dwBytes, LMedia::IMediaSample* *pVal)
			{
				ASSERT(0);
#if 0
				CComObject<CAudioSample>* pSample;
				CComObject<CAudioSample>::CreateInstance(&pSample);
				pSample->AddRef();

				pSample->m_pInput = m_pInput;
				//pSample->m_mediaType = m_pInput->m_mediaType;

				pSample->m_pointer = (LPBYTE)GlobalAlloc(0, dwBytes);
				pSample->m_dwBytes = dwBytes;
				pSample->m_ActualDataLength = dwBytes;

				//m_

				*pVal = pSample;
#endif
				return S_OK;
			}

			ErrorCode ReleaseBuffer(LMedia::IMediaSample* pBuffer)
			{
				if (static_cast<CAudioSample*>(pBuffer)->m_pointer)
				{
#if WIN32
					GlobalFree(static_cast<CAudioSample*>(pBuffer)->m_pointer);
#endif
					static_cast<CAudioSample*>(pBuffer)->m_pointer = NULL;
				}
				return S_OK;
			}
		};

		CInputPin() : BasePinImpl(LMedia::LPINDIR_INPUT)
		{
			m_pFilter = NULL;
			m_dwOffset = 0;

			m_pLock.Init();
			ASSERT(0);
		}
#if 0
		int FinalConstruct()
		{
			ErrorCode hr;

			hr = CComObject<CMemAllocator>::CreateInstance(&m_pAllocator);
			if (FAILED(hr)) return hr;
			m_pAllocator->AddRef();
			m_pAllocator->m_pInput = this;

			return 0;
		}

		void FinalRelease()
		{
			if (m_pAllocator)
			{
				m_pAllocator->Release();
				m_pAllocator = NULL;
			}
		}
#endif
		CAudioFilter* m_pFilter;

		CriticalSection m_pLock;

		DWORD m_dwOffset;
		DWORD m_dwBufferBytes;

	//	CComPtr<IDirectSound8> m_ds8;
#if 0
		CComQIPtr<IDirectSoundBuffer8, &IID_IDirectSoundBuffer8> m_dsBuffer8;
		CComQIPtr<IDirectSound3DBuffer8, &IID_IDirectSound3DBuffer8> m_ds3DBuffer;
#endif
		CMemAllocator* m_pAllocator;

#if WIN32
		LPWAVEFORMATEX m_wf;
#endif
		HANDLE m_hEvent;

	public:
		LMedia::IBaseFilter* QueryFilter() const
		{
			return m_pFilter;
		}

		virtual ErrorCode CheckMediaType(const LMedia::MediaType& mt)
		{
			if (mt.majortype != LMEDIATYPE_Audio)
				return E_FAIL;

			if (mt.subtype != GUID_NULL)	// TODO
				return E_FAIL;

#if WIN32
			LPWAVEFORMATEX pwfx = (LPWAVEFORMATEX)mt.pbFormat;
			if (pwfx->wFormatTag != WAVE_FORMAT_PCM)
				return E_FAIL;
#else
			ASSERT(0);
#endif

			return S_OK;
		}

		ErrorCode CompleteConnect(LMedia::IPin* pConnector)
		{
			ErrorCode hr = BasePinImpl::CompleteConnect(pConnector);
			if (FAILED(hr)) return hr;

#if WIN32

			DSBUFFERDESC dsbdesc; 
		//	ErrorCode hr; 
			
			// Set up wave format structure. 
			//memset(&pcmwf, 0, sizeof(PCMWAVEFORMAT)); 
			//pcmwf = *(PCMWAVEFORMAT*)&m_wavfmt;
			/*
			m_wf.wFormatTag = WAVE_FORMAT_PCM; 
			m_wf.nChannels = 2;
			m_wf.nSamplesPerSec = 22050;
			m_wf.nBlockAlign = 2; 
			m_wf.nAvgBytesPerSec = m_wf.nSamplesPerSec * m_wf.nBlockAlign; 
			m_wf.wBitsPerSample = 8; 
			m_wf.cbSize = 0;
			*/
			//if (m_pmt.->format != FORMAT_WaveFormatEx)
						//	m_pmt = NULL;

			m_wf = (LPWAVEFORMATEX)m_mt.GetFormat();

			//	m_wf = (LPWAVEFORMATEX)m_pmt->cbFormat;
			//	if (m_wf->wFormatTag == WAVE_FORMAT_PCM)
			//	{
				//m_wf.nAvgBytesPerSec = m_wf.nSamplesPerSec * m_wf.nBlockAlign;

			ULONG nBufferSamples = m_wf->nSamplesPerSec * 2;	// We buffer two seconds
#if 0
			m_mediaType->GetSamples(&nsamples);
#endif

	// Set up DSBUFFERDESC structure. 

			memset(&dsbdesc, 0, sizeof(DSBUFFERDESC)); 
			dsbdesc.dwSize = sizeof(DSBUFFERDESC); 
			dsbdesc.dwFlags = DSBCAPS_GLOBALFOCUS |
				DSBCAPS_CTRL3D | DSBCAPS_CTRLPOSITIONNOTIFY | DSBCAPS_GETCURRENTPOSITION2/* | DSBCAPS_CTRLPAN |*/ /*DSBCAPS_CTRLVOLUME*/ | DSBCAPS_CTRLFREQUENCY; 

			m_dwBufferBytes = nBufferSamples*m_wf->nBlockAlign;	// Bytes used by one buffer
			dsbdesc.dwBufferBytes = m_dwBufferBytes*2;	// We double-buffer
			dsbdesc.lpwfxFormat = m_wf;

			// Create buffer. 
#if 0			
			CComPtr<IDirectSoundBuffer> dsBuffer;
			hr = m_pFilter->m_pMediaSource->m_pScene->m_ds8->CreateSoundBuffer(&dsbdesc, &dsBuffer, NULL); 
			if (FAILED(hr))
			{
				ASSERT(0);
				return hr;
			}

			m_dsBuffer8 = dsBuffer;
			m_ds3DBuffer = dsBuffer;
			if (m_dsBuffer8 == NULL)
			{
				ASSERT(0);
				return E_NOINTERFACE;
			}

			m_ds3DBuffer->SetPosition(0, 0, 0, DS3D_IMMEDIATE);

//			CreateStreamOnHGlobal(NULL, TRUE, &m_pFilter->m_stream);

			CComQIPtr<IDirectSoundNotify8, &IID_IDirectSoundNotify> notify8 = m_dsBuffer8;
			if (notify8 == NULL)
			{
				ASSERT(0);
				return E_NOINTERFACE;
			}
			m_hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
			if (m_hEvent == NULL)
			{
				ASSERT(0);
				return E_FAIL;
			}

			m_dwOffset = 0;

			DSBPOSITIONNOTIFY ps[2];
			ps[0].dwOffset = 0;
			ps[0].hEventNotify = m_hEvent;
			ps[1].dwOffset = m_dwBufferBytes;//nsamples*m_wf->nBlockAlign;//2*m_wf.nAvgBytesPerSec;
			ps[1].hEventNotify = m_hEvent;

			if (notify8->SetNotificationPositions(2, ps) != DS_OK)
			{
				ASSERT(0);
				return E_FAIL;
			}

			m_dsBuffer8->Play(0, 0, DSBPLAY_LOOPING);	// ??
#endif

#endif

			return S_OK;
		}

		LONGLONG m_lastTimeStart;
		LONGLONG m_lastTimeEnd;

	// IMemInputPin
		LMedia::IMemAllocator* GetAllocator()
		{
			return m_pAllocator;
		}
		bool Receive(LMedia::IMediaSample *sample)
		{
			m_pLock.Lock();


			ErrorCode hr;
#if WIN32

			LMedia::LSampleData sampledata;
			hr = sample->LockBits(&sampledata);
			if (SUCCEEDED(hr))
			{
				ULONG ActualDataLength = sample->GetActualDataLength();

				sample->GetTime(&m_lastTimeStart, &m_lastTimeEnd);

				DWORD nbytesSoFar = 0;
				while (nbytesSoFar < ActualDataLength)
				{
					DWORD nbytes;

				// Try to fill the rest of the buffer (either the first or second buffer)
					if (m_dwOffset < m_dwBufferBytes)	// first buffer
						nbytes = m_dwBufferBytes-m_dwOffset;
					else		// second buffer
						nbytes = m_dwBufferBytes*2-m_dwOffset;

				// Limit it to what is available/left in sample
					if (nbytes > ActualDataLength - nbytesSoFar)
					{
						nbytes = ActualDataLength - nbytesSoFar;
					}

					// Probably doesn't matter, but we check here that we're copying an integral number of samples
					ASSERT(((nbytes / m_wf->nBlockAlign)*m_wf->nBlockAlign) == nbytes);

//	#ifdef _DEBUG	// Remove this if you're single step debugging
	//#if 0	// Remove this if you're single step debugging
					DWORD dwCurrentPlayCursor;
					DWORD dwCurrentWriteCursor;
					ASSERT(0);
#if 0
					hr = m_dsBuffer8->GetCurrentPosition(&dwCurrentPlayCursor, &dwCurrentWriteCursor);
#endif
					ASSERT(SUCCEEDED(hr));

					DWORD dwbuffer1;
					LPBYTE buffer1;

					DWORD dwbuffer2;
					LPBYTE buffer2;

#if 0
					if (m_dwOffset < dwCurrentWriteCursor)
					{
						ASSERT(m_dwOffset < dwCurrentPlayCursor);
					}
					else
					{
						ASSERT(m_dwOffset >= dwCurrentWriteCursor);
					}
#endif
	//#endif

					ASSERT(0);
#if 0
					hr = m_dsBuffer8->Lock(m_dwOffset, nbytes, (void**)&buffer1, &dwbuffer1, (void**)&buffer2, &dwbuffer2, 0);
#endif
					if (SUCCEEDED(hr))
					{
						ASSERT(dwbuffer1 == nbytes);

						ASSERT(!IsBadWritePtr(buffer1, dwbuffer1));
						ASSERT(!IsBadReadPtr(sampledata.idata+nbytesSoFar, dwbuffer1));

						ASSERT(nbytesSoFar+dwbuffer1 <= ActualDataLength);

						CopyMemory(buffer1, sampledata.idata+nbytesSoFar, dwbuffer1);
						nbytesSoFar += dwbuffer1;

						ASSERT(buffer2 == NULL);
						/*
						if (buffer2)
						{
							CopyMemory(buffer2, pSample->m_pointer+nbytesSoFar, dwbuffer2);
							nbytesSoFar += dwbuffer2;
						}
						*/

						ASSERT(0);
#if 0
						m_dsBuffer8->Unlock(buffer1, dwbuffer1, buffer2, dwbuffer2);
#endif
					}
					else
						ASSERT(0);

					m_dwOffset += nbytes;

					ASSERT(m_dwOffset <= 2*m_dwBufferBytes);

					if (m_dwOffset == 2*m_dwBufferBytes)
						m_dwOffset = 0;	// Wrap around to first buffer

					if (m_dwOffset == 0 || m_dwOffset == m_dwBufferBytes)	// A buffer has been completely filled
					{
						DWORD status;
						ASSERT(0);
#if 0
						m_dsBuffer8->GetStatus(&status);
#endif
						if (!(status & DSBSTATUS_PLAYING))
						{
							// If it's not yet playing, wait til we've filled half the
							// buffer before starting to play
							if (m_dwOffset == m_dwBufferBytes)
							{
								ASSERT(0);
#if 0
								ErrorCode hr = m_dsBuffer8->Play(0, 0, DSBPLAY_LOOPING);
								ASSERT(SUCCEEDED(hr));
#endif
								WaitForSingleObject(m_hEvent, INFINITE);	// This should return immediately now
							}
						}
						else
						{
							WaitForSingleObject(m_hEvent, INFINITE);
						}
					}
				}

				sample->UnlockBits();
			}
#endif

			m_pLock.Unlock();

			return hr == S_OK;
			/*
			DWORD nbytesSoFar = 0;
			while (nbytesSoFar < pSample->m_ActualDataLength)
			{
				DWORD nbytes = m_dwBufferBytes;

				if (nbytes > pSample->m_ActualDataLength)
				{
					nbytes = pSample->m_ActualDataLength;
				}

				DWORD dwbuffer1;
				LPBYTE buffer1;

				DWORD dwbuffer2;
				LPBYTE buffer2;

				ErrorCode hr = m_dsBuffer8->Lock(m_dwOffset, nbytes, (void**)&buffer1, &dwbuffer1, (void**)&buffer2, &dwbuffer2, 0);
				if (SUCCEEDED(hr))
				{
					CopyMemory(buffer1, pSample->m_pointer+nbytesSoFar, dwbuffer1);
					nbytesSoFar += dwbuffer1;

					if (buffer2)
					{
						CopyMemory(buffer2, pSample->m_pointer+nbytesSoFar, dwbuffer2);
						nbytesSoFar += dwbuffer2;
					}

					m_dsBuffer8->Unlock(buffer1, dwbuffer1, buffer2, dwbuffer2);
				}

				DWORD status;
				m_dsBuffer8->GetStatus(&status);

				if (!(status & DSBSTATUS_PLAYING))
				{
					ErrorCode hr = m_dsBuffer8->Play(0, 0, DSBPLAY_LOOPING);
					ASSERT(SUCCEEDED(hr));
				}

				//if (dwBytesSoFar > m_dwBufferBytes)
				WaitForSingleObject(m_hEvent, INFINITE);

				m_dwOffset += nbytes;//pSample->m_dwBytes;

				while (m_dwOffset >= 2*m_dwBufferBytes)
					m_dwOffset -= 2*m_dwBufferBytes;
			}
			*/
		}
		ErrorCode EndOfStream();

		/*
		static DWORD WINAPI ThreadProc(LPVOID lpParameter)
		{
		}

		STDMETHOD(Run)(LONGLONG tStart)
		{
			DWORD m_threadId;
			HANDLE m_hThread = CreateThread(NULL, NULL, ThreadProc, (LPVOID)(COutputPin*)this, 0, &m_threadId);
			return S_OK;
		}
		*/
	};

		CAudioFilter()
		{
			m_pInput = NULL;
		//	m_pOutput = NULL;

//			m_pElement = NULL;
			ASSERT(0);
		}
#if 0
		int FinalConstruct()
		{
			ErrorCode hr;

			hr = BaseFilterImpl::FinalConstruct();
			if (FAILED(hr)) return hr;

			CComObject<CInputPin>::CreateInstance(&m_pInput);
			m_pInput->m_pFilter = this;
			AddPin(m_pInput);

			/*
			CComObject<COutputPin>::CreateInstance(&m_pOutput);
			m_pOutput->m_pFilter = this;
			AddPin(m_pOutput);
			*/

			return 0;
		}

		void FinalRelease()
		{
			BaseFilterImpl::FinalRelease();
		}
#endif
		CInputPin* m_pInput;
	//	CComObject<COutputPin>* m_pOutput;

		CLAudioClip* m_pMediaSource;

#if 0
		CLElementTimeImplImpl* m_pElement;
#endif

	// IMediaSeeking
		ErrorCode Seek(DWORD unit, LONGLONG t)
		{
			LMedia::IMediaSeeking* peerSeeking = dynamic_cast<LMedia::IMediaSeeking*>(m_pInput->m_connectedTo);
			if (peerSeeking == NULL)
				return E_NOINTERFACE;

			return peerSeeking->Seek(unit, t);
		}

		ErrorCode GetCurrentPosition(DWORD unit, LONGLONG *pVal)
		{
			/*
			CComQIPtr<IMediaSeeking> peerSeeking = m_pInputPin->m_connectedTo;
			if (peerSeeking == NULL)
				return E_NOINTERFACE;

			return peerSeeking->Seek(seconds);
			*/
			return S_OK;
		}

		ErrorCode GetDuration(DWORD unit, LONGLONG *pVal)
		{
			LMedia::IMediaSeeking* peerSeeking = dynamic_cast<LMedia::IMediaSeeking*>(m_pInput->m_connectedTo);
			if (peerSeeking == NULL)
				return E_NOINTERFACE;

			return peerSeeking->GetDuration(unit, pVal);
		}
	};

	ErrorCode CLAudioClip::LoadFile(const sysstring& wszFileName)
	{
//		USES_CONVERSION;

		m_filterGraph = new LMedia::FilterGraph;//.CoCreateInstance(CLSID_LFilterGraph);
		//if (SUCCEEDED(hr))
		{
			//m_filterGraph->AddFilter(m_pAudioFilter);

			m_pAudioFilter = new CAudioFilter;
			m_pAudioFilter->m_pMediaSource = this;
			m_filterGraph->AddFilter(m_pAudioFilter);

			try
			{
			m_filterGraph->LoadURL(wszFileName);
			}
			catch (int)
			{
			}

			//if (SUCCEEDED(hr))
			{
			//	m_filterGraph->Run();

			//	CComPtr<DispILStreams> streams;
			//	m_filterGraph->get_Streams(&streams);

#if 0
				if (TRUE)	// Video
				{
					CComPtr<ILMediaStream> stream;
					streams->Item(0, (DispILMediaStream**)&stream);
					if (stream)	// Connect video renderer
					{
						CComObject<CVideoFilter>::CreateInstance(&m_pVideoFilter);
						m_pVideoFilter->AddRef();
						m_pVideoFilter->m_pMediaSource = this;
						m_filterGraph->AddFilter(m_pVideoFilter);

						CComPtr<ILPin> pin;
						stream->GetPin(&pin);
						m_filterGraph->ConnectDirect(pin, m_pVideoFilter->m_pInput, NULL);
					}
				}
#endif

#if 0
				if (TRUE)	// Audio
				{
					CComPtr<DispILCollection> filters;
					m_filterGraph->get_Filters((IDispatch**)&filters);

					long nfilters;
					filters->get_Count(&nfilters);

					CComPtr<DispILFilter> filter;
					filters->Item(nfilters-1, (IUnknown**)&filter);
					CComPtr<ILBaseFilter> pfilter;
					filter->get_filter((IUnknown**)&pfilter);

					CComPtr<ILPin> outpin;
					pfilter->GetPin(2, &outpin);

				//
					CAudioFilter>::CreateInstance(&m_pAudioFilter);
					m_pAudioFilter->AddRef();
					m_pAudioFilter->m_pMediaSource = this;
					m_filterGraph->AddFilter(m_pAudioFilter);

					m_filterGraph->ConnectDirect(outpin, m_pAudioFilter->m_pInput, NULL);

				// Connect Audio renderer
					CComPtr<ILBaseFilter> audioRenderFilter;
					audioRenderFilter.CoCreateInstance(CLSID_LDSoundRender);

					CComPtr<ILPin> inpin;
					audioRenderFilter->GetPin(0, &inpin);

					m_filterGraph->AddFilter(audioRenderFilter);
					m_filterGraph->ConnectDirect(m_pAudioFilter->m_pOutput, inpin, NULL);
				}
#endif

			//	CComQIPtr<IMediaSeeking> seeking = m_filterGraph;
			//	seeking->GetDuration(&m_duration);
	#if 0
				CComQIPtr<ILVideo> video;
				m_movie->GetVideo(&video);
				if (video)
				{
					long width;
					long height;
					video->GetWidth(&width);
					video->GetHeight(&height);

					CComObject<CVideoSample>::CreateInstance(&m_pSample);
					m_pSample->AddRef();

					m_pSample->m_pBitmap = new Gdiplus::Bitmap(width, height, PixelFormat24bppRGB);

					video->SetSample(m_pSample);
				}
	#endif

	#if 0
				CComQIPtr<ILAudio> audio;
				m_movie->GetAudio(&audio);
				if (audio)
				{
					audio->GetSamples(&m_nSamples);

					if (m_nSamples > 0)
					{
						m_wavFormat = (LPWAVEFORMATEX)GlobalAlloc(0, sizeof(WAVEFORMATEX));
						audio->GetFormat(m_wavFormat);

						m_wavBuffer = (LPSTR)GlobalAlloc(0, (DWORD)(m_nSamples*m_wavFormat->nBlockAlign));
						if (m_wavBuffer)
						{
							LPSTR buffer = m_wavBuffer;

							int i = 0;
							ULONG chunksamples;
							while (audio->GetChunkSize(i, &chunksamples) == S_OK)
							{
								audio->ReadChunk(i, buffer, chunksamples);

								buffer += chunksamples*m_wavFormat->nBlockAlign;

								i++;
							}
						}
					}

	#if 0
					m_wavfmt.nAvgBytesPerSec = m_wavfmt.nSamplesPerSec * m_wavfmt.nBlockAlign;

					ULONG nSamples;
					audio->GetChunkSize(0, &nSamples);

					{
						//PCMWAVEFORMAT pcmwf; 
						DSBUFFERDESC dsbdesc; 
						ErrorCode hr; 
						
						// Set up wave format structure. 
						//memset(&pcmwf, 0, sizeof(PCMWAVEFORMAT)); 
						//pcmwf = *(PCMWAVEFORMAT*)&m_wavfmt;
						/*
						pcmwf.wf.wFormatTag = WAVE_FORMAT_PCM; 
						pcmwf.wf.nChannels = m_wavfmt.nChannels; 
						pcmwf.wf.nSamplesPerSec = 22050; 
						pcmwf.wf.nBlockAlign = 4; 
						pcmwf.wf.nAvgBytesPerSec = 
							pcmwf.wf.nSamplesPerSec * pcmwf.wf.nBlockAlign; 
						pcmwf.wBitsPerSample = 16; 
						*/
						
						// Set up DSBUFFERDESC structure. 
						
						memset(&dsbdesc, 0, sizeof(DSBUFFERDESC)); 
						dsbdesc.dwSize = sizeof(DSBUFFERDESC); 
						dsbdesc.dwFlags = 
							DSBCAPS_CTRL3D | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY; 
						
						dsbdesc.dwBufferBytes = nSamples * m_wavfmt.nBlockAlign;//3 * pcmwf.wf.nAvgBytesPerSec; 
						dsbdesc.lpwfxFormat = &m_wavfmt;//(LPWAVEFORMATEX)&pcmwf; 
						
						// Create buffer. 
						
						CComPtr<IDirectSoundBuffer> dsBuffer;
						hr = m_ds8->CreateSoundBuffer(&dsbdesc, &dsBuffer, NULL);
						m_dsBuffer8 = dsBuffer;
						m_ds3DBuffer = dsBuffer;
						if (SUCCEEDED(hr))
						{ 
							LPSTR pbuffer;
							DWORD dwbuffer;
							if (SUCCEEDED(m_dsBuffer8->Lock(0, nSamples * m_wavfmt.nBlockAlign, (void**)&pbuffer, &dwbuffer, NULL, NULL, 0)))
							{
								audio->ReadChunk(0, pbuffer, nSamples);

								m_dsBuffer8->Unlock(0, nSamples * m_wavfmt.nBlockAlign, NULL, 0);
							}

							// IDirectSoundBuffer interface is in *lplpDsb. 
							// Use QueryInterface to obtain IDirectSoundBuffer8.
							//return TRUE; 
						} 
						else 
						{ 
							ASSERT(0);
							/*
							// Failed. 
							*lplpDsb = NULL; 
							return FALSE; 
							*/
						} 

					}

				// We load the first chunk, even before starting playing, so there's no delay if and when we should play
	#endif
				}
	#endif
			}
		}

	//	return hr;
	return S_OK;
	}
#endif

NodeType Valuator::nodeType(WSTR("Valuator"), typeid(Valuator), NULL, 0);

NodeType Conditional::nodeType(WSTR("Conditional"), typeid(Conditional), NULL, 0);


#if 0
STDMETHODIMP CLAudioClip::CAudioFilter::CInputPin::Receive(ILMediaSample *samplein)
{
	EnterCriticalSection(&m_pLock);

#if 0
	MessageBeep(-1);

	CMemAllocator::CAudioSample* pSampleIn = static_cast<CMemAllocator::CAudioSample*>(samplein);

	CComPtr<ILAudioSample> sampleOut;
	m_pFilter->m_pOutput->m_allocator->GetBuffer(pSampleIn->m_dwBytes, (ILMediaSample**)&sampleOut);

	LPBYTE bufferOut;
	sampleOut->LockBits(&bufferOut);

	LPBYTE bufferIn = pSampleIn->m_pointer;

//	ULONG nSamples;
//	m_mediaType->GetSamples(&nSamples);

	WAVEFORMATEX wf;
	m_mediaType->GetFormat(&wf);

	DWORD nbytes = pSampleIn->m_dwBytes;//wf.nBlockAlign * nSamples;

	DWORD nSamplesIn = pSampleIn->m_dwBytes / wf.nBlockAlign;

	DWORD nSamplesOut = 0;	// TODO

#if 0
	if (TRUE)
	{

#if 0
		ULONG startSample = start_tsp * m_pMedia->m_wavFormat->nSamplesPerSec;
		ULONG nSamples = lent * m_pMedia->m_wavFormat->nSamplesPerSec;

		TRACE("startSample:%d, nSamples:%d\n", startSample, nSamples);
#endif

		double parent_speed = 1;
		double AD = m_pFilter->m_pElement->m_AD;// * m_pMedia->m_wavFormat->nSamplesPerSec;//m_dur;// ? AD=Active Duration?
		double speed = m_pFilter->m_pElement->m_speed->m_value->m_value;
		double acc = m_pFilter->m_pElement->m_accelerate->m_value->m_value;
		double dec = m_pFilter->m_pElement->m_decelerate->m_value->m_value;

		if (acc+dec > 1)	// Ignore both attributes
		{
			acc = 0;
			dec = 0;
		}

		double r = (1 / (1 - acc/2 - dec/2));// * m_pMedia->m_wavFormat->nSamplesPerSec;

		//Let dur be the value of the simple duration as defined by the Timing and Synchronization model.
		// This is the actual simple duration, and not simply the dur attribute.
		//This value does not account for the effect of any time manipulations.
		double dur = m_pFilter->m_pElement->m_dur;// * m_pMedia->m_wavFormat->nSamplesPerSec;

		// pThis->m_simpleDur has accounted for autoReverse
		double dur_ = m_pFilter->m_pElement->m_simpleDur;// * m_pMedia->m_wavFormat->nSamplesPerSec;

		double dacc = acc*dur;
		double ddec = dec*dur;

		DWORD startSample = m_nSample;

		for (ULONG n = 0; n < nSamplesOut; n++)
		{
			//DWORD insample = n+startSample;

			//if (speed == 0) speed = 0 ??

			double tau = (startSample + n) * (1.0/wf.nSamplesPerSec);//tps - m_pCurrentInterval->m_begin;

			double taf;

			if (speed > 0) // i.e. if the local speed is forwards 
				taf = tau * speed;
			else //  i.e. if the local speed is backwards 
				taf = AD - tau * fabs(speed);

			double tsu = REMAINDER(taf, dur_);

		// Account for autoReverse behavior.
			double tsu_;

			if (m_pFilter->m_pElement->m_autoReverse->m_value->m_value != VARIANT_TRUE)
			{
				tsu_ = tsu;
			}
			else
			{
				if (tsu < dur)
					tsu_ = tsu;
				else
					//tsu_ = /*dur - (tsu - dur) =*/ 2*dur - tsu;
					tsu_ = 2*dur - tsu;
			}

		// Calculate filtered time (tsf)

		// Account for acceleration/deceleration
			double tsf;

			if (tsu_ < dacc)
			{
				double rt = r * (tsu_ / dacc);

				tsf = tsu_ * rt / 2;
			}
			else if (tsu_ > (dur - ddec))
			{
				double rt = r * (dur - tsu_) / ddec;

				double tdec =  tsu_ - (dur - ddec);
				double pd =  tdec / ddec;

				tsf = r * (dur - dacc / 2 - ddec + tdec * (2 - pd) / 2);
			}
			else
			{
				tsf = r * (tsu_ - dacc / 2);
			}

			//ULONG tsf = tsf;

			DWORD nSampleIn = tsf*wf.nSamplesPerSec;

			//ASSERT(nSample >= 0 && nSample < m_pMedia->m_nSamples);

			for (int nb = 0; nb < wf.nBlockAlign; nb++)
			{
				bufferOut[n*wf.nBlockAlign+nb] = bufferIn[nSampleIn*wf.nBlockAlign+nb];
			}
		}
	}
#if 0
	else
	{
		CopyMemory(buffer, pSampleIn->m_pointer, nbytes);
	}
#endif
#endif

	CopyMemory(bufferOut, pSampleIn->m_pointer, nbytes);

	sampleOut->UnlockBits();

	<IMemInputPin> memInput = m_pFilter->m_pOutput->m_connectedTo;
	memInput->Receive(sampleOut);


#if 0
	double timeStart;
	double timeEnd;
	pSample->GetTime(&timeStart, &timeEnd);

#if 0
	HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

	m_pFilter->m_clock->AdviseTime(m_pFilter->m_tStart/*baseTime*/, timeStart/*streamTime*/, hEvent, NULL);

	WaitForSingleObject(hEvent, INFINITE);

	CloseHandle(hEvent);
#endif

	m_pSample = static_cast<CVideoSample*>(pSample);

//	m_pFilter->m_pMoviePlayer->m_cwnd.PostMessage(WM_USER+100, 0, 0);
#endif
#endif
	LeaveCriticalSection(&m_pLock);

	return S_OK;
}
#endif

NodeType LinePropertiesBIFS::s_nodeType(WSTR("LinePropertiesBIFS"), typeid(LinePropertiesBIFS), LinePropertiesBIFSFields, _countof(LinePropertiesBIFSFields));

LinePropertiesBIFS::LinePropertiesBIFS() : X3DAppearanceChildNode(&s_nodeType)
{
}

//	class MovieTexture;

#if 0
// TODO, group and anchor/inline/collision have same code

void CLHAnimSegment::Draw(X3DDrawContext* pDC)
{
	int nLight = pDC->m_nLight;
	int nNames = pDC->m_namedNodes.GetSize();

	int i;

	for (i = 0; i < m_children->m_items.GetSize(); i++)
	{
		X3DNode* node = m_children->m_items[i];

		if (node)
		{
			RenderImplImpl* render = dynamic_cast<RenderImplImpl*>(node->GetNode());
			if (render)
			{
				render->PreDraw(pDC);
			}
		}
	}

	for (i = 0; i < m_children->m_items.GetSize(); i++)
	{
		X3DNode* node = m_children->m_items[i];

		if (node)
		{
			RenderImplImpl* render = dynamic_cast<RenderImplImpl*>(node->GetNode());
			if (render)
			{
				render->Draw(pDC);
			}
		}
	}

	for (i = pDC->m_namedNodes.GetSize(); i >= nNames; i--)
	{
//		glPopName();
	}
	for (i = pDC->m_nLight; i >= nLight; i--)
	{
		pDC->m_pGraphics3D->glDisable(GL_LIGHT0+i);
	}
	pDC->m_nLight = nLight;
}
#endif


class Form : 
	public X3DGroupingNode, // X3DBoundedObject,

	public X3DBoundedImplImpl,
	public RenderImplImpl
{
public:
	CTOR Form() : X3DGroupingNode(s_nodeType)
	{
	}

	virtual NodeType* getType() const
	{
		return s_nodeType;
	}

//	MFNode* m_children;

	virtual void Draw(X3DDrawContext* pDC)
	{
	}

	virtual void CalculateBoundingBox()
	{
	}

	static NodeType* s_nodeType;
};

NodeType* Form::s_nodeType = NULL;

/*
To get a normal for a flat triangle, the equation is:

      a
     / \
    /   \
    b---c

normal = normalize( cross_product( (a-b), (c-b) ) )


*/

void lglNormal(Graphics::Graphics3D* p, const gm::vector3f& c, const gm::vector3f& b, const gm::vector3f& a)
{
	ASSERT(0);
#if 0
	LDraw::vector3f n = LDraw::cross(a-b, c-b);
	
	if (n[0] != 0 || n[1] != 0 || n[2] != 0)
		n.normalize();

	p->glNormalf(n[0], n[1], n[2]);
#endif
}

class Circle : 
	public X3DGeometryNode,

//	public X3DNode,
	public IGeometryRender
{
public:
	Circle() : X3DGeometryNode(nodeType)
	{
	// Cache pointers to relevant fields
		m_radius = static_cast<SFFloat*>(getField(WSTR("radius")));

	// Set defaults
		m_radius->m_value = 1.0f;
	}

	virtual NodeType* getType() const
	{
		return nodeType;
	}

	static NodeType* nodeType;

	SFFloat* m_radius;

	virtual void Draw(X3DDrawContext* pDC, X3DTextureNodeImplImpl* textureNode)
	{
#if 0
		glRectf(
			-m_size->m_value[0]/2, -m_size->m_value[1]/2,
			m_size->m_value[0]/2, m_size->m_value[1]/2);
#endif
	}

};



#define EPSILON 0.000001

int
intersect_triangle_barycentric(
   double orig[3], double dir[3],
   double vert0[3], double vert1[3], double vert2[3],
   double planeq[4], int i1, int i2,
   double *t, double *alpha, double *beta)
{
   double	dot, dot2;
   double	point[2];
   double	u0, v0, u1, v1, u2, v2;

   /* is ray parallel to plane? */
   dot = dir[0] * planeq[0] + dir[1] * planeq[1] + dir[2] * planeq[2];
   if (dot < EPSILON && dot > -EPSILON)		/* or use culling check */
      return 0;

   /* find distance to plane and intersection point */
   dot2 = orig[0] * planeq[0] +
      orig[1] * planeq[1] + orig[2] * planeq[2];
   *t = -(planeq[3] + dot2 ) / dot;
   point[0] = orig[i1] + dir[i1] * *t;
   point[1] = orig[i2] + dir[i2] * *t;

   /* begin barycentric intersection algorithm */
   u0 = point[0] - vert0[i1];
   v0 = point[1] - vert0[i2];
   u1 = vert1[i1] - vert0[i1];
   u2 = vert2[i1] - vert0[i1];
   v1 = vert1[i2] - vert0[i2];
   v2 = vert2[i2] - vert0[i2];

   /* calculate and compare barycentric coordinates */
   if (u1 == 0) {		/* uncommon case */
      *beta = u0 / u2;
      if (*beta < 0 || *beta > 1)
	       return 0;
      *alpha = (v0 - *beta * v2) / v1;
   }
   else {			/* common case, used for this analysis */
      *beta = (v0 * u1 - u0 * v1) / (v2 * u1 - u2 * v1);
      if (*beta < 0 || *beta > 1)
	       return 0;
      *alpha = (u0 - *beta * u2) / u1;
   }

   if (*alpha < 0 || (*alpha + *beta) > 1.0)
      return 0;

   return 1;
}

typedef struct {
   float x,y,z;
} XYZ;
//#define EPSILON  0.0000001
#define MODULUS(p) (sqrt(p.x*p.x + p.y*p.y + p.z*p.z))
#define TWOPI 6.283185307179586476925287
#define RTOD 57.2957795

double CalcAngleSum(XYZ q,XYZ *p,int n)
{
   int i;
   double m1,m2;
   double anglesum=0,costheta;
   XYZ p1,p2;

   for (i=0;i<n;i++) {

      p1.x = p[i].x - q.x;
      p1.y = p[i].y - q.y;
      p1.z = p[i].z - q.z;
      p2.x = p[(i+1)%n].x - q.x;
      p2.y = p[(i+1)%n].y - q.y;
      p2.z = p[(i+1)%n].z - q.z;

      m1 = MODULUS(p1);
      m2 = MODULUS(p2);
      if (m1*m2 <= EPSILON)
         return(TWOPI); /* We are on a node, consider this inside */
      else
         costheta = (p1.x*p2.x + p1.y*p2.y + p1.z*p2.z) / (m1*m2);

      anglesum += acos(costheta);
   }
   return(anglesum);
}
#define PLANE_FRONT		-1
#define PLANE_COINCIDE	0
#define PLANE_BACK		1

//int side = PLANE_FRONT;	// TODO, for each polygon ?

int ClassifyPoint( const gm::vector3f& plane_normal, double plane_distance, const gm::vector3f& destPt )
{
	double p = gm::dot(plane_normal, destPt ) + plane_distance;

	if( p > 0.5f )
		return PLANE_FRONT;
	else if( p < 0.5f )
		return PLANE_BACK;

	return PLANE_COINCIDE;
}


// Particles

class CParticle
{
public:
	CParticle()
	{
		m_timeOfLife = 0;
	}

	float m_timeOfLife;// the current time of life 
	float m_timeOfDeath;// the time of death 
	gm::vector3f m_position;// the current position
	gm::vector3f m_velocity;// the current velocity
	float m_radius;// the current radius
	//SFColor initialColor the initial color
	//SFColor color the current color
	//SFFloat alpha the alpha value

	float m_timeOfCreation;

	/*
SFFLoat timeOfLife the current time of life 
SFFLoat timeOfDeath the time of death 
SFVec3f position the current position
SFVec3f velocity the current velocity
SFFloat radius the current radius
SFColor initialColor the initial color
SFColor color the current color
SFFloat alpha the alpha value
*/
};

gm::vector3f rand3f()
{
	return gm::vector3f((float)rand()/(RAND_MAX/2)-1, (float)rand()/(RAND_MAX/2)-1, (float)rand()/(RAND_MAX/2)-1);
}

#if 0
class CLParticles :
	public ILParticles,

//	public X3DTimeDependentNode,

//	public X3DNode,
	public RenderImplImpl
{
public:
	CLParticles()
	{
		m_oldgt = 0;
		m_nTotalParticles = 0;

	// Cache pointers to relevant fields
		m_creationRate = static_cast<SFFloat*>(getField(WSTR("creationRate")));
		m_emitterPosition = static_cast<SFVec3f*>(getField(WSTR("emitterPosition")));
		m_maxLifeTime = static_cast<SFTime*>(getField(WSTR("maxLifeTime")));
		m_maxParticles = static_cast<SFInt32*>(getField(WSTR("maxParticles")));
		m_emitVelocity = static_cast<SFVec3f*>(getField(WSTR("emitVelocity")));
		m_emitVelocityVariation = static_cast<SFVec3f*>(getField(WSTR("emitVelocityVariation")));

	// Set defaults
		m_creationRate->m_value = 500;
		m_maxLifeTime->m_value = 5;
		m_maxParticles->m_value = 500;
		m_emitVelocityVariation->m_value[0] = m_emitVelocityVariation->m_value[1] = m_emitVelocityVariation->m_value[2] = 1;
	}

	SFFloat* m_creationRate;
	SFVec3f* m_emitterPosition;
	SFTime* m_maxLifeTime;
	SFInt32* m_maxParticles;
	SFVec3f* m_emitVelocity;
	SFVec3f* m_emitVelocityVariation;

/*
	SFFloat exposedField creationRate 500 
	SFFloat exposedField creationRateVariation 0 
	SFFloat exposedField emitAlpha 1.0 
	SFColor exposedField emitColor 1 1 1 
	SFColor exposedField emitColorVariation 0 0 0 
	SFVec3f exposedField emitterPosition 0 3 0 
	SFVec3f exposedField emitVelocity 0 0 0 
	SFVec3f exposedField emitVelocityVariation 1 1 1 
	SFBool exposedField enabled TRUE 
	SFFloat exposedField fadeAlpha 1.0 
	SFColor exposedField fadeColor 0.25 0.25 0.25 
	SFFloat exposedField fadeRate 0.25 
	SFVec3f exposedField force 0 -9.8 0 
	MFInfluenceNode exposedField influences [] 
	SFWorldNode exposedField init NULL 
	SFTime exposedField maxLifeTime 5 
	SFFloat exposedField maxLifeTimeVariation 0 
	SFInt32 exposedField maxParticles 500 
	SFFloat exposedField minRange 1 
	SFFloat exposedField maxRange 100 
	SFFloat exposedField particleRadius 0.1 
	SFFloat exposedField particleRadiusVariation 0 
	SFFloat exposedField particleRadiusRate 0 
	SFWorldNode exposedField primitive NULL 
	SFInt32 exposedField primitiveType 2 
*/

	vector<CParticle*> m_particles;

	virtual void Draw(X3DDrawContext* pDC)
	{
		pDC->m_pGraphics3D->glColorf(1,1,1);

		pDC->m_pGraphics3D->glBegin(GL_POINTS);

		for (int i = 0; i < m_particles.GetSize(); i++)
		{
			pDC->m_pGraphics3D->glVertex(m_particles[i]->m_position);
		}

		pDC->m_pGraphics3D->glEnd();
	}

	double m_oldgt;
	ULONG m_nTotalParticles;

	virtual void DoTime(double gt)
	{
		double framerate = gt-m_oldgt;

		if (framerate != 0)	// ??
		{
			for (int i = m_particles.GetSize()-1; i >= 0; i--)
			{
				m_particles[i]->m_timeOfLife = gt - m_particles[i]->m_timeOfCreation;

				if (m_particles[i]->m_timeOfLife > m_particles[i]->m_timeOfDeath)
				{
					// Destroy particle
					delete m_particles[i];
					m_particles.RemoveAt(i);
				}
				else
				{
					// Move particle
					m_particles[i]->m_position += m_particles[i]->m_velocity * framerate;
				}
			}
		}

		{
			ULONG nTotalParticles = m_creationRate->m_value * gt;

			int count = nTotalParticles - m_nTotalParticles;

			count += m_particles.GetSize();

			if (count > m_maxParticles->m_value)
				count = m_maxParticles->m_value;

			count -= m_particles.GetSize();

			for (int i = 0; i < count; i++)
			{
				CParticle* pParticle = new CParticle;

				pParticle->m_timeOfCreation = gt;

				pParticle->m_timeOfDeath = m_maxLifeTime->m_value;// + Rand ()*maxLifeTimeVariation;


				//pParticle->m_velocity = emitVelocity-> + Rand3()*emitVelocityVariation

				//RAND_MAX

				pParticle->m_position = m_emitterPosition->m_value;

				LDraw::vector3f randomVector = rand3f();
				LDraw::vector3f velocityVariation(m_emitVelocityVariation->m_value[0]*randomVector[0], m_emitVelocityVariation->m_value[1]*randomVector[1], m_emitVelocityVariation->m_value[2]*randomVector[2]);
				pParticle->m_velocity = m_emitVelocity->m_value + velocityVariation;

				m_particles.Add(pParticle);
			}

			m_nTotalParticles = nTotalParticles;
		}

		m_oldgt = gt;
	}

};

class  CLPlanarObstacle :
	public ILPlanarObstacle,

//	public X3DNode,
	public RenderImplImpl
{
public:
	CLPlanarObstacle()
	{
	}


};
#endif

#if 0
void CALLBACK vertexCallback(void* vertex)
{
	const GLdouble* pointer = (GLdouble*)vertex;
	glVertex3dv(pointer);
}

void CALLBACK beginCallback(unsigned int which)
{
	glBegin(which);
}

void CALLBACK endCallback()
{
	glEnd();
}

void CALLBACK errorCallback(unsigned int errorCode)
{
	const GLubyte* estring;
	estring = gluErrorString(errorCode);
}

void CALLBACK combineCallback(GLdouble coords[3], GLdouble *vertex_data[4], GLfloat weight[4], GLdouble **dataOut)
{
	GLdouble *vertex;

	vertex = (GLdouble*)malloc(6*sizeof(GLdouble));
	vertex[0] = coords[0];
	vertex[1] = coords[1];
	vertex[2] = coords[2];

	/*
	for (int i = 3; i < 6; i++)
	{
		vertex[i] = weight[0] * vertex_data[0][i] +
						weight[1] * vertex_data[1][i] +
						weight[2] * vertex_data[2][i] +
						weight[3] * vertex_data[3][i];
	}
	*/

	*dataOut = vertex;
}
#endif

// MPEG-4 2D bezier
class Curve2D :
	public X3DGeometryNode,

//	public X3DNode,
	public IGeometryRender
{
public:
	Curve2D() : X3DGeometryNode(nodeType)
	{
		m_list = 0;

	// Cache pointers to relevant fields
		m_point = static_cast<SFNode*>(getField(WSTR("point")));
		m_type = static_cast<MFInt32*>(getField(WSTR("type")));
		m_fineness = static_cast<SFFloat*>(getField(WSTR("fineness")));

	// Set defaults
		m_fineness->m_value = 0;	// ?? should it be 0.5?
	}

	virtual NodeType* getType() const
	{
		return nodeType;
	}

	static NodeType* nodeType;

	SFNode* m_point;
	MFInt32* m_type;
	SFFloat* m_fineness;

/*
	exposedField SFNode point NULL
	exposedField SFInt32 fineness 0
	exposedField MFInt32 type []
*/

	void draw_moveto(gm::vector2f& v0)
	{
		//glBegin(GL_LINES);

		m_vertexCount.Add(1);
		m_vertices.Add(gm::vector3f(v0[0], v0[1], 0));

#if 0
		glVertex2(v0);
		glVertex2(v1);
#endif

#if 0
		double* coords = new double[3];
		coords[0] = v0[0];
		coords[1] = v0[1];
		coords[2] = 0;
		gluTessVertex(tess, coords, coords);
#endif

		//glEnd();
	}

	vector<int> m_vertexCount;
	vector<gm::vector3f> m_vertices;

	void draw_lineto(const gm::vector2f& v1)
	{
		//glBegin(GL_LINES);

		m_vertexCount[m_vertexCount.GetSize()-1]++;
		m_vertices.Add(gm::vector3f(v1[0], v1[1], 0));

#if 0
		glVertex2(v0);
		glVertex2(v1);

		double* coords = new double[3];
		coords[0] = v1[0];
		coords[1] = v1[1];
		coords[2] = 0;
		gluTessVertex(tess, m_vertices[], coords);
#endif

		//glEnd();
	}

	void draw_line(const gm::vector2f& v0, const gm::vector2f& v1)
	{
		//glBegin(GL_LINES);

		m_vertexCount[m_vertexCount.GetSize()-1]++;
		m_vertices.Add(gm::vector3f(v0[0], v0[1], 0));

		m_vertexCount[m_vertexCount.GetSize()-1]++;
		m_vertices.Add(gm::vector3f(v1[0], v1[1], 0));

#if 0
		glVertex2(v0);
		glVertex2(v1);

		{
			double* coords = new double[3];
			coords[2] = 0;
			coords[0] = v0[0];
			coords[1] = v0[1];
			gluTessVertex(tess, coords, coords);
		}

		{
			double* coords = new double[3];
			coords[2] = 0;
			coords[0] = v1[0];
			coords[1] = v1[1];
			gluTessVertex(tess, coords, coords);
		}
#endif

		//glEnd();
	}

	void draw_curve(const gm::vector2f& v0, const gm::vector2f& v1, const gm::vector2f& v2, const gm::vector2f& v3)
	{
		double ax, ay, bx, by, cx, cy;

		cx = 3 * (v1[0] - v0[0]);
		cy = 3 * (v1[1] - v0[1]);
		bx = 3 * (v2[0] - v1[0]) - cx;
		by = 3 * (v2[1] - v1[1]) - cy;
		ax = v3[0] - v0[0] - cx - bx;
		ay = v3[1] - v0[1] - cy - by;

		double tinc = 1/20.0;

		for (double t = 0.0; t <= 1.0; t += tinc)
		{
			double x = ax * t*t*t + bx * t*t + cx * t + v0[0];
			double y = ay * t*t*t + by * t*t + cy * t + v0[1];

			m_vertexCount[m_vertexCount.GetSize()-1]++;
			m_vertices.Add(gm::vector3f(x, y, 0));

		//	gluTessVertex(tess, coords, coords);
		}

#if 0
		float points[4*3] =
		{
			v0[0], v0[1], 0,
			v1[0], v1[1], 0,
			v2[0], v2[1], 0,
			v3[0], v3[1], 0,
		};

		glMap1f(GL_MAP1_VERTEX_3, 0, 1, 3/*stride*/, 4/*order*/, points);
		ASSERT(glGetError() == GL_NO_ERROR);

		glEnable(GL_MAP1_VERTEX_3);
		ASSERT(glGetError() == GL_NO_ERROR);

		for (int i = 0; i < 40; i++)
		{
			glEvalCoord1f((float)i/40);
			ASSERT(glGetError() == GL_NO_ERROR);
		}
#endif

#if 0
		GLUnurbsObj* nurb = gluNewNurbsRenderer();
		if (nurb)
		{
			//gluNurbsProperty();

			gluBeginCurve(nurb);
			ASSERT(glGetError() == GL_NO_ERROR);

			float knot[8] = {0, 0, 0, 0, 1, 1, 1, 1 };

			float points[4*3] =
			{
				v0[0], v0[1], 0,
				v1[0], v1[1], 0,
				v2[0], v2[1], 0,
				v3[0], v3[1], 0,
			};

			gluNurbsCurve(nurb,
				8, knot,
				3, // stride
				points,//(float*)m_controlPoint->m_items.GetData(),
				4,//m_order->m_value,	// order
				GL_MAP1_VERTEX_3	// type
				);

			gluEndCurve(nurb);
			ASSERT(glGetError() == GL_NO_ERROR);

			gluDeleteNurbsRenderer(nurb);
			ASSERT(glGetError() == GL_NO_ERROR);
		}
#endif
	}

	unsigned int m_list;

	virtual void Draw(X3DDrawContext* pDC, X3DTextureNodeImplImpl* pTextureNode)
	{
		bool is_filled = true;	// TODO

		ASSERT(0);
#if 0

		if (m_vertices.GetSize() == 0)
		{
			<ILCoordinate2D> coordinate2D = m_point->m_value;
			if (coordinate2D)
			{
				CLCoordinate2D* pCoordinate2D = static_cast<CLCoordinate2D*>(coordinate2D.p);
				MFVec2f* point = pCoordinate2D->m_point;

				if (point->m_items.GetSize() > 0)
				{

						/*
						if (is_filled)
							glBegin(GL_POLYGON);
						else
							glBegin(GL_LINE_STRIP);
							*/
						if (m_type->m_items.GetSize() > 0)
						{
							gmVector2 cur = point->m_items[0];
							gmVector2 first = cur;
							gmVector2 curctl;

							int i = 1;
							int j = 0;

							draw_moveto(cur);

							while (i < point->m_items.GetSize())
							{
								int t = 0;

								if (m_type->m_items.GetSize() > j)
									t = m_type->m_items[j++];

								switch (t)
								{
								case 0: // move, use 1 point
									{
										//if (is_filled) draw_line(tess, cur, point->m_items[i]);
										cur = point->m_items[i];
										draw_moveto(cur);
										i++;
									}
									break;

								case 1: // line, use 1 point
									{
										draw_lineto(point->m_items[i]);
										cur = point->m_items[i];
										i++;
									}
									break;

								case 2: // bezier curve, use 3 points
									{
										draw_curve(cur, point->m_items[i], point->m_items[i+1], point->m_items[i+2]);
										cur = point->m_items[i+2];
										curctl = point->m_items[i+1];
										i += 3;
									}
									break;

								case 3: // tangent curve, use 2 points
									{
										gmVector2 tanctl;

										tanctl[0] = 2*cur[0] - curctl[0];
										tanctl[1] = 2*cur[1] - curctl[1];

										/*
										tanctl[0] = 2*cur[0] – curctl[0];
										tanctl[1] = 2*cur[1] – curctl[1];
										*/
										draw_curve(cur, tanctl, point->m_items[i], point->m_items[i+1]);
										cur = point->m_items[i+1];
										curctl = point->m_items[i];
										i += 2;
									}
									break;

								default:
									ASSERT(0);
								}
							}

							//if (is_filled) draw_line(tess, cur, first);
						}
						else
						{
						//	ASSERT(0);
						}

					//	glEnd();

				}
			}
		}

		if (m_list == 0)
		{
			m_list = glGenLists(1);

			if (m_list)
			{
				glNewList(m_list, GL_COMPILE);

				if (TRUE)
				{
					int n = 0;
					for (int i = 0; i < m_vertexCount.GetSize(); i++)
					{
						glBegin(GL_LINE_STRIP);

						int vertexCount = m_vertexCount[i];
						for (int j = 0; j < vertexCount; j++)
						{
							glVertex3(m_vertices[n+j]);
						}
						n += vertexCount;

						glEnd();
					}
				}
				else
				{
					GLUtesselator* tess = gluNewTess();
					if (tess)
					{
						gluTessCallback(tess, GLU_TESS_VERTEX, (void(CALLBACK*)())vertexCallback);
						gluTessCallback(tess, GLU_TESS_BEGIN, (void(CALLBACK*)())beginCallback);
						gluTessCallback(tess, GLU_TESS_END, (void(CALLBACK*)())endCallback);
						gluTessCallback(tess, GLU_TESS_ERROR, (void(CALLBACK*)())errorCallback);
						gluTessCallback(tess, GLU_TESS_COMBINE, (void(CALLBACK*)())combineCallback);

						gluTessBeginPolygon(tess, NULL);

						int n = 0;
						for (int i = 0; i < m_vertexCount.GetSize(); i++)
						{
							gluTessBeginContour(tess);

							int vertexCount = m_vertexCount[i];
							for (int j = 0; j < vertexCount; j++)
							{
								gluTessVertex(tess, m_vertices[n+j].getp(), m_vertices[n+j].getp());
							}
							n += vertexCount;

							gluTessEndContour(tess);
						}

						gluTessEndPolygon(tess);

						gluDeleteTess(tess);
					}
				}

				glEndList();
			}
			else
				ASSERT(0);
		}

		if (m_list)
		{
			glCallList(m_list);
		}


#if 0
		GLUnurbsObj* nurb = gluNewNurbsRenderer();
		if (nurb)
		{
			//gluNurbsProperty();

			gluBeginCurve(nurb);
			ASSERT(glGetError() == GL_NO_ERROR);

			gluNurbsCurve(nurb,
				m_knot->m_items.GetSize(), m_knot->m_items.GetData(),
				3, // stride
				(float*)m_controlPoint->m_items.GetData(),
				m_order->m_value,	// order
				GL_MAP1_VERTEX_3	// type
				);

			gluEndCurve(nurb);
			ASSERT(glGetError() == GL_NO_ERROR);

			gluDeleteNurbsRenderer(nurb);
			ASSERT(glGetError() == GL_NO_ERROR);
		}
#endif
#endif
	}

};

NodeType* Curve2D::nodeType = NULL;

// NURBS

class NurbsCurve :
	public X3DParametricGeometryNode,

//	public X3DNode,
	public IGeometryRender
{
public:
	NurbsCurve() : X3DParametricGeometryNode(nodeType)
	{
	// Cache pointers to relevant fields
		m_controlPoint = static_cast<MFVec3f*>(getField(WSTR("controlPoint")));
		m_knot = static_cast<MFFloat*>(getField(WSTR("knot")));
		m_order = static_cast<SFInt32*>(getField(WSTR("order")));

	// Set defaults
		m_order->m_value = 3;
	}

	virtual NodeType* getType() const
	{
		return nodeType;
	}

	static NodeType* nodeType;

	MFVec3f* m_controlPoint;
	MFFloat* m_knot;
	SFInt32* m_order;

/*
	SFNode   [in,out] controlPoint []    [X3DCoordinateNode]
	SFNode   [in,out] metadata     NULL  [X3DMetadataObject]
	SFInt32  [in,out] tessellation 0     (-8,8)
	MFDouble [in,out] weight       []    (0,8)
	SFBoolean[]       closed       FALSE 
	MFDouble []       knot         []    (-8,8)
	SFInt32  []       order        3     [2,8)
*/

	virtual void Draw(X3DDrawContext* pDC, X3DTextureNodeImplImpl* pTextureNode)
	{
		ASSERT(0);
#if 0
		GLUnurbsObj* nurb = gluNewNurbsRenderer();
		if (nurb)
		{
			//gluNurbsProperty();

			gluBeginCurve(nurb);
			ASSERT(glGetError() == GL_NO_ERROR);

			gluNurbsCurve(nurb,
				m_knot->m_items.GetSize(), m_knot->m_items.GetData(),
				3, // stride
				(float*)m_controlPoint->m_items.begin(),
				m_order->m_value,	// order
				GL_MAP1_VERTEX_3	// type
				);

			gluEndCurve(nurb);
			ASSERT(glGetError() == GL_NO_ERROR);

			gluDeleteNurbsRenderer(nurb);
			ASSERT(glGetError() == GL_NO_ERROR);
		}
#endif
	}

};

NodeType* NurbsCurve::nodeType = NULL;

// VRML97 backward compatible, X3D has renamed and slighty changed it to NurbsPatchSurface
class NurbsSurface :
	public X3DNurbsSurfaceGeometryNode,

//	public X3DNode,
	public IGeometryRender
{
public:
	NurbsSurface() : X3DNurbsSurfaceGeometryNode(s_nodeType)
	{
	// Cache pointers to relevant fields
		m_controlPoint = static_cast<MFVec3f*>(getField(WSTR("controlPoint")));
		m_weight = static_cast<MFFloat*>(getField(WSTR("weight")));
		m_uDimension = static_cast<SFInt32*>(getField(WSTR("uDimension")));
		m_vDimension = static_cast<SFInt32*>(getField(WSTR("vDimension")));
		m_uKnot = static_cast<MFFloat*>(getField(WSTR("uKnot")));
		m_vKnot = static_cast<MFFloat*>(getField(WSTR("vKnot")));
		m_uOrder = static_cast<SFInt32*>(getField(WSTR("uOrder")));
		m_vOrder = static_cast<SFInt32*>(getField(WSTR("vOrder")));

	// Set default values
		m_uDimension->m_value = 0;
		m_vDimension->m_value = 0;
		m_uOrder->m_value = 3;
		m_vOrder->m_value = 3;
	}

	virtual NodeType* getType() const
	{
		return s_nodeType;
	}

	static NodeType* s_nodeType;

	MFVec3f* m_controlPoint;
	MFFloat* m_weight;
	SFInt32* m_uDimension;
	SFInt32* m_vDimension;
	MFFloat* m_uKnot;
	MFFloat* m_vKnot;
	SFInt32* m_uOrder;
	SFInt32* m_vOrder;

/*
	exposedField  MFVec3f controlPoint    []     # (,)
	exposedField  SFNode  texCoord        []
	exposedField  SFInt32 uTessellation   0      # (-,)
	exposedField  SFInt32 vTessellation   0      # (-,)
	exposedField  MFFloat weight          []     # (0,)
	field         SFBool  ccw             TRUE
	field         SFBool  solid           TRUE
	field         SFInt32 uDimension      0      # [0,)
	field         MFFloat uKnot           []     # (-,)
	field         SFInt32 uOrder          3      # [2,) 
	field         SFInt32 vDimension      0      # [0,)
	field         MFFloat vKnot           []     # (-,)
	field         SFInt32 vOrder          3      # [2,)
 */

	virtual void Draw(X3DDrawContext* pDC, X3DTextureNodeImplImpl* pTextureNode)
	{
	//	pDC->m_pGraphics3D->Enable(GL_AUTO_NORMAL);
		//pDC->m_pGraphics3D->Enable(GL_NORMALIZE);

		ASSERT(0);
#if 0

		// TODO, bounds error checking
		GLUnurbsObj* nurb = gluNewNurbsRenderer();
		if (nurb)
		{
			gluNurbsProperty(nurb, GLU_DISPLAY_MODE, GLU_FILL);

			gluBeginSurface(nurb);
			ASSERT(glGetError() == GL_NO_ERROR);

			if (m_weight->m_items.GetSize() == 0)	// All treated as 1.0
			{
				gluNurbsSurface(nurb,
					m_uKnot->m_items.GetSize(), m_uKnot->m_items.GetData(),
					m_vKnot->m_items.GetSize(), m_vKnot->m_items.GetData(),
					3*(m_uKnot->m_items.GetSize()-m_uOrder->m_value),	// ustride
					3,	// vstride
					(float*)m_controlPoint->m_items.begin(),
					m_uOrder->m_value,
					m_vOrder->m_value,
					GL_MAP2_VERTEX_3
					);
				ASSERT(glGetError() == GL_NO_ERROR);
			}
			else
			{
				if (m_controlPoint->m_items.size() == m_weight->m_items.GetSize())
				{
					float *ctl = new float[m_controlPoint->m_items.size()*4];

					int ustride = (m_uKnot->m_items.GetSize()-m_uOrder->m_value);

					for (int i = 0; i < m_controlPoint->m_items.size(); i++)
					{
						ctl[i*4+0] = m_controlPoint->m_items[i][0];
						ctl[i*4+1] = m_controlPoint->m_items[i][1];
						ctl[i*4+2] = m_controlPoint->m_items[i][2];
						ctl[i*4+3] = m_weight->m_items[i];
					}

					gluNurbsSurface(nurb,
						m_uKnot->m_items.GetSize(), m_uKnot->m_items.GetData(),
						m_vKnot->m_items.GetSize(), m_vKnot->m_items.GetData(),
						4*ustride,	// ustride
						4,	// vstride
						ctl,//(float*)m_controlPoint->m_items.GetData(),
						m_uOrder->m_value,
						m_vOrder->m_value,
						GL_MAP2_VERTEX_4
						);
					ASSERT(glGetError() == GL_NO_ERROR);

					delete [] ctl;
				}
				else
				{
					ASSERT(0);
				}
			}

			gluEndSurface(nurb);
			ASSERT(glGetError() == GL_NO_ERROR);

			gluDeleteNurbsRenderer(nurb);
			ASSERT(glGetError() == GL_NO_ERROR);
		}
#endif
	}

};

String X3DNode::ToString()
{
	IO::StringWriter stream;
	WriteVRML(stream);
	return stream.str();
}

class Formatted
{
public:
};

IO::TextWriter& WriteToStream(IO::TextWriter& stream, Formatted& fmt)
{
	return stream;
}

IO::TextWriter& X3DNode::WriteVRML(IO::TextWriter& writer)
{
	if (m_name != nullptr)
	{
		writer << "DEF " << m_name << " ";
	}

	writer << getTypeName();
	writer << "\n";
	writer << '{';
//	++stream.m_streamObject->m_indent;
	writer << "\n";

	uint nfields = getFieldCount();

	for (uint i = 0; i < nfields; ++i)
	{
		X3DField* field = getField(i);

		writer << field->getFieldName();
		writer << ' ';
		field->WriteValueToStream(writer);
		writer << "\n";
	}

//	--stream.m_streamObject->m_indent;
	writer << '}';
	writer << "\n";

	return writer;
}

NodeType* NurbsSurface::s_nodeType = nullptr;

// Text

class FontStyle :
	public X3DFontStyleNode

//	public X3DNode
	//public CLRenderImplImpl
{
public:
	CTOR FontStyle() : X3DFontStyleNode(nodeType)
	{
	// Cache pointers to relevant fields
		m_family = static_cast<MFString*>(getField(WSTR("family")));
		m_size = static_cast<SFFloat*>(getField(WSTR("size")));

	// Set defaults
		m_size->m_value = 1.0f;
	}

	virtual NodeType* getType() const
	{
		return nodeType;
	}

	static NodeType* nodeType;

	MFString* m_family;
	SFFloat* m_size;

	/*
	SFNode   [in,out] metadata    NULL    [X3DMetadataObject]
	MFString []       family      "SERIF"
	SFBool   []       horizontal  TRUE
	MFString []       justify     "BEGIN" ["BEGIN"|"END"|"FIRST"|"MIDDLE"|""]
	SFString []       language    ""
	SFBool   []       leftToRight TRUE
	SFFloat  []       size        1.0     (0,8)
	SFFloat  []       spacing     1.0     [0,8)
	SFString []       style       "PLAIN" ["PLAIN"|"BOLD"|"ITALIC"|"BOLDITALIC"|""]
	SFBool   []       topToBottom TRUE
	*/

};

NodeType* FontStyle::nodeType = nullptr;

	///

#if 0
ErrorCode CAudioFilter::CInputPin::EndOfStream()
{
#if WIN32
	if (m_pFilter->m_pMediaSource->m_loop->m_value)	// Loop
	{
		m_pFilter->m_pFilterGraph->Stop();
		m_pFilter->m_pFilterGraph->Run();
	}
	else
	{
	// Wait until the last sample has ended
		HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

		m_pFilter->m_clock->AdviseTime(m_pFilter->m_tStart/*baseTime*/, m_lastTimeEnd/*streamTime*/, hEvent, NULL);
		WaitForSingleObject(hEvent, INFINITE);

		ASSERT(0);
#if 0
		ErrorCode hr = m_dsBuffer8->Stop();
		ASSERT(hr == DS_OK);
#endif
	}
#endif

	return S_OK;
}
#endif

////////

void X3DBoundedImplImpl::DrawBoundingBox(X3DDrawContext* pDC, BoundingBox bbox)
{
	Gui::Media3D::IndexedLines lines;

	if (true)
	{
		Vec3f positions[8] =
		{
			Vec3f(-1,-1,-1),
			Vec3f( 1,-1,-1),
			Vec3f( 1,-1, 1),
			Vec3f(-1,-1, 1),

			Vec3f(-1, 1,-1),
			Vec3f( 1, 1,-1),
			Vec3f( 1, 1, 1),
			Vec3f(-1, 1, 1),
		};

		uint indices[26] =
		{
			0, 1,
			1, 2,
			2, 3,
			3, 0,

			4, 5,
			5, 6,
			6, 7,
			7, 4,

			0, 4,
			1, 5,
			2, 6,
			3, 7,
		};

		Vec4f color(0.2f, 0.2f, 0.2f, 1.0f);
		lines.Create(pDC->m_renderContext, positions, _countof(positions), indices, _countof(indices), color);

		pDC->m_renderContext->PushModelView(pDC->m_renderContext->modelViewMatrix() *
			MatrixScale(bbox.m_size) *
			MatrixTranslation(bbox.m_center));

		lines.Draw(pDC->m_renderContext);

		pDC->m_renderContext->PopMatrix();
	}
	else
	{
		float diff = 0.3;
		Vec3f points[] =
		{
			Vec3f(-1,-1,-1), Vec3f(-1+diff,-1,-1),
			Vec3f(-1,-1,-1), Vec3f(-1-diff,-1,-1),
			Vec3f(-1,-1,-1), Vec3f(-1-diff,-1,-1),
			Vec3f(-1,-1,-1), Vec3f(-1-diff,-1,-1),
		};

		lines.Draw(pDC->m_renderContext);
	}

#if 0
	LDraw::vector3f csize;
	csize[0] = m_boxSize[0]/3;
	csize[1] = m_boxSize[1]/3;
	csize[2] = m_boxSize[2]/3;

	pDC->m_pGraphics3D->glPushAttrib(GL_ENABLE_BIT);

	pDC->m_pGraphics3D->glColor3f(1.0, 0, 0);	// red
	pDC->m_pGraphics3D->glDisable(GL_LIGHTING);

	pDC->m_pGraphics3D->glBegin(GL_LINES);

	// bottom

	// back-bottom-left
	{
		glVertex3f(m_boxCenter[0]-m_boxSize[0], m_boxCenter[1]-m_boxSize[1], m_boxCenter[2]-m_boxSize[2]);
		glVertex3f(m_boxCenter[0]-m_boxSize[0]+csize[0], m_boxCenter[1]-m_boxSize[1], m_boxCenter[2]-m_boxSize[2]);

		pDC->m_pGraphics3D->glVertex3f(m_boxCenter[0]-m_boxSize[0], m_boxCenter[1]-m_boxSize[1], m_boxCenter[2]-m_boxSize[2]);
		pDC->m_pGraphics3D->glVertex3f(m_boxCenter[0]-m_boxSize[0], m_boxCenter[1]-m_boxSize[1]+csize[1], m_boxCenter[2]-m_boxSize[2]);

		pDC->m_pGraphics3D->glVertex3f(m_boxCenter[0]-m_boxSize[0], m_boxCenter[1]-m_boxSize[1], m_boxCenter[2]-m_boxSize[2]);
		pDC->m_pGraphics3D->glVertex3f(m_boxCenter[0]-m_boxSize[0], m_boxCenter[1]-m_boxSize[1], m_boxCenter[2]-m_boxSize[2]+csize[2]);
	}

	// front-bottom-left
	{
		pDC->m_pGraphics3D->glVertex3f(m_boxCenter[0]-m_boxSize[0], m_boxCenter[1]-m_boxSize[1], m_boxCenter[2]+m_boxSize[2]);
		pDC->m_pGraphics3D->glVertex3f(m_boxCenter[0]-m_boxSize[0]+csize[0], m_boxCenter[1]-m_boxSize[1], m_boxCenter[2]+m_boxSize[2]);

		pDC->m_pGraphics3D->glVertex3f(m_boxCenter[0]-m_boxSize[0], m_boxCenter[1]-m_boxSize[1], m_boxCenter[2]+m_boxSize[2]);
		pDC->m_pGraphics3D->glVertex3f(m_boxCenter[0]-m_boxSize[0], m_boxCenter[1]-m_boxSize[1]+csize[1], m_boxCenter[2]+m_boxSize[2]);

		pDC->m_pGraphics3D->glVertex3f(m_boxCenter[0]-m_boxSize[0], m_boxCenter[1]-m_boxSize[1], m_boxCenter[2]+m_boxSize[2]);
		pDC->m_pGraphics3D->glVertex3f(m_boxCenter[0]-m_boxSize[0], m_boxCenter[1]-m_boxSize[1], m_boxCenter[2]+m_boxSize[2]-csize[2]);
	}

	// back-bottom-right
	{
		pDC->m_pGraphics3D->glVertex3f(m_boxCenter[0]+m_boxSize[0], m_boxCenter[1]-m_boxSize[1], m_boxCenter[2]-m_boxSize[2]);
		pDC->m_pGraphics3D->glVertex3f(m_boxCenter[0]+m_boxSize[0]-csize[0], m_boxCenter[1]-m_boxSize[1], m_boxCenter[2]-m_boxSize[2]);

		pDC->m_pGraphics3D->glVertex3f(m_boxCenter[0]+m_boxSize[0], m_boxCenter[1]-m_boxSize[1], m_boxCenter[2]-m_boxSize[2]);
		pDC->m_pGraphics3D->glVertex3f(m_boxCenter[0]+m_boxSize[0], m_boxCenter[1]-m_boxSize[1]+csize[1], m_boxCenter[2]-m_boxSize[2]);

		pDC->m_pGraphics3D->glVertex3f(m_boxCenter[0]+m_boxSize[0], m_boxCenter[1]-m_boxSize[1], m_boxCenter[2]-m_boxSize[2]);
		pDC->m_pGraphics3D->glVertex3f(m_boxCenter[0]+m_boxSize[0], m_boxCenter[1]-m_boxSize[1], m_boxCenter[2]-m_boxSize[2]+csize[2]);
	}

	// front-bottom-right
	{
		m_pGraphics3D->glVertex(m_boxCenter[0]+m_boxSize[0], m_boxCenter[1]-m_boxSize[1], m_boxCenter[2]+m_boxSize[2]);
		m_pGraphics3D->glVertex(m_boxCenter[0]+m_boxSize[0]-csize[0], m_boxCenter[1]-m_boxSize[1], m_boxCenter[2]+m_boxSize[2]);

		pDC->m_pGraphics3D->glVertex3f(m_boxCenter[0]+m_boxSize[0], m_boxCenter[1]-m_boxSize[1], m_boxCenter[2]+m_boxSize[2]);
		pDC->m_pGraphics3D->glVertex3f(m_boxCenter[0]+m_boxSize[0], m_boxCenter[1]-m_boxSize[1]+csize[1], m_boxCenter[2]+m_boxSize[2]);

		pDC->m_pGraphics3D->glVertex3f(m_boxCenter[0]+m_boxSize[0], m_boxCenter[1]-m_boxSize[1], m_boxCenter[2]+m_boxSize[2]);
		pDC->m_pGraphics3D->glVertex3f(m_boxCenter[0]+m_boxSize[0], m_boxCenter[1]-m_boxSize[1], m_boxCenter[2]+m_boxSize[2]-csize[2]);
	}

	// top

	// back-bottom-left
	{
		pDC->m_pGraphics3D->glVertex(m_boxCenter[0]-m_boxSize[0], m_boxCenter[1]+m_boxSize[1], m_boxCenter[2]-m_boxSize[2]);
		pDC->m_pGraphics3D->glVertex(m_boxCenter[0]-m_boxSize[0]+csize[0], m_boxCenter[1]+m_boxSize[1], m_boxCenter[2]-m_boxSize[2]);

		pDC->m_pGraphics3D->glVertex(m_boxCenter[0]-m_boxSize[0], m_boxCenter[1]+m_boxSize[1], m_boxCenter[2]-m_boxSize[2]);
		pDC->m_pGraphics3D->glVertex(m_boxCenter[0]-m_boxSize[0], m_boxCenter[1]+m_boxSize[1]-csize[1], m_boxCenter[2]-m_boxSize[2]);

		pDC->m_pGraphics3D->glVertex(m_boxCenter[0]-m_boxSize[0], m_boxCenter[1]+m_boxSize[1], m_boxCenter[2]-m_boxSize[2]);
		pDC->m_pGraphics3D->glVertex(m_boxCenter[0]-m_boxSize[0], m_boxCenter[1]+m_boxSize[1], m_boxCenter[2]-m_boxSize[2]+csize[2]);
	}

	// front-bottom-left
	{
		pDC->m_pGraphics3D->glVertex(m_boxCenter[0]-m_boxSize[0], m_boxCenter[1]+m_boxSize[1], m_boxCenter[2]+m_boxSize[2]);
		pDC->m_pGraphics3D->glVertex(m_boxCenter[0]-m_boxSize[0]+csize[0], m_boxCenter[1]+m_boxSize[1], m_boxCenter[2]+m_boxSize[2]);

		pDC->m_pGraphics3D->glVertex(m_boxCenter[0]-m_boxSize[0], m_boxCenter[1]+m_boxSize[1], m_boxCenter[2]+m_boxSize[2]);
		pDC->m_pGraphics3D->glVertex(m_boxCenter[0]-m_boxSize[0], m_boxCenter[1]+m_boxSize[1]-csize[1], m_boxCenter[2]+m_boxSize[2]);

		pDC->m_pGraphics3D->glVertex(m_boxCenter[0]-m_boxSize[0], m_boxCenter[1]+m_boxSize[1], m_boxCenter[2]+m_boxSize[2]);
		pDC->m_pGraphics3D->glVertex(m_boxCenter[0]-m_boxSize[0], m_boxCenter[1]+m_boxSize[1], m_boxCenter[2]+m_boxSize[2]-csize[2]);
	}

	// back-bottom-right
	{
		pDC->m_pGraphics3D->glVertex(m_boxCenter[0]+m_boxSize[0], m_boxCenter[1]+m_boxSize[1], m_boxCenter[2]-m_boxSize[2]);
		pDC->m_pGraphics3D->glVertex(m_boxCenter[0]+m_boxSize[0]-csize[0], m_boxCenter[1]+m_boxSize[1], m_boxCenter[2]-m_boxSize[2]);

		pDC->m_pGraphics3D->glVertex(m_boxCenter[0]+m_boxSize[0], m_boxCenter[1]+m_boxSize[1], m_boxCenter[2]-m_boxSize[2]);
		pDC->m_pGraphics3D->glVertex(m_boxCenter[0]+m_boxSize[0], m_boxCenter[1]+m_boxSize[1]-csize[1], m_boxCenter[2]-m_boxSize[2]);

		pDC->m_pGraphics3D->glVertex(m_boxCenter[0]+m_boxSize[0], m_boxCenter[1]+m_boxSize[1], m_boxCenter[2]-m_boxSize[2]);
		pDC->m_pGraphics3D->glVertex(m_boxCenter[0]+m_boxSize[0], m_boxCenter[1]+m_boxSize[1], m_boxCenter[2]-m_boxSize[2]+csize[2]);
	}

	// front-bottom-right
	{
		pDC->m_pGraphics3D->glVertex(m_boxCenter[0]+m_boxSize[0], m_boxCenter[1]+m_boxSize[1], m_boxCenter[2]+m_boxSize[2]);
		pDC->m_pGraphics3D->glVertex(m_boxCenter[0]+m_boxSize[0]-csize[0], m_boxCenter[1]+m_boxSize[1], m_boxCenter[2]+m_boxSize[2]);

		pDC->m_pGraphics3D->glVertex(m_boxCenter[0]+m_boxSize[0], m_boxCenter[1]+m_boxSize[1], m_boxCenter[2]+m_boxSize[2]);
		pDC->m_pGraphics3D->glVertex(m_boxCenter[0]+m_boxSize[0], m_boxCenter[1]+m_boxSize[1]-csize[1], m_boxCenter[2]+m_boxSize[2]);

		pDC->m_pGraphics3D->glVertex(m_boxCenter[0]+m_boxSize[0], m_boxCenter[1]+m_boxSize[1], m_boxCenter[2]+m_boxSize[2]);
		pDC->m_pGraphics3D->glVertex(m_boxCenter[0]+m_boxSize[0], m_boxCenter[1]+m_boxSize[1], m_boxCenter[2]+m_boxSize[2]-csize[2]);
	}

	pDC->m_pGraphics3D->glEnd();

	pDC->m_pGraphics3D->glPopAttrib();
#endif
}

#if 0
// virtual
void CLHAnimJoint::Draw(X3DDrawContext* pDC)
{
/*		gmMatrix4 P_ = gmMatrix4::translate(m_T[0], m_T[1], m_T[2]) *

						gmMatrix4::translate(m_C[0], m_C[1], m_C[2]) *

						gmMatrix4::rotate(gmDegrees(m_angle), m_R) *

						gmMatrix4::translate(m_SR[0], m_SR[1], m_SR[2]) *
						gmMatrix4::scale(m_S[0], m_S[1], m_S[2]) *
						gmMatrix4::translate(-m_SR[0], -m_SR[1], -m_SR[2]) *

						gmMatrix4::translate(-m_C[0], -m_C[1], -m_C[2]);// * P
*/
	/*
	gmMatrix4 P_ =
		gmMatrix4::translate(-m_C[0], -m_C[1], -m_C[2]) *
		gmMatrix4::translate(-m_SR[0], -m_SR[1], -m_SR[2]) *
		gmMatrix4::scale(m_S[0], m_S[1], m_S[2]) *
		gmMatrix4::translate(m_SR[0], m_SR[1], m_SR[2]) *
		gmMatrix4::rotate(gmDegrees(m_angle), m_R) *
		gmMatrix4::translate(m_C[0], m_C[1], m_C[2]) *
		gmMatrix4::translate(m_T[0], m_T[1], m_T[2])					;

	float m[4][4];
	P_.copyTo(m);
	*/

	pDC->m_pGraphics3D->glPushMatrix();

// P' = T * C * R * SR * S * -SR * -C * P

		pDC->m_pGraphics3D->glTranslate(m_T->m_value);
		pDC->m_pGraphics3D->glTranslate(m_C->m_value);
		pDC->m_pGraphics3D->glRotate(gmDegrees(m_R->m_value.m_angle), m_R->m_value.m_axis);
		pDC->m_pGraphics3D->glRotate(gmDegrees(m_SR->m_value.m_angle), m_SR->m_value.m_axis);
		pDC->m_pGraphics3D->glScale(m_S->m_value);
		pDC->m_pGraphics3D->glRotate(gmDegrees(m_SR->m_value.m_angle), -m_SR->m_value.m_axis);
		pDC->m_pGraphics3D->glTranslate(-m_C->m_value);

	// Draw axes
	if (false)
	{
		pDC->m_pGraphics3D->glPushAttrib(GL_ENABLE_BIT);

		float len = 4;

		pDC->m_pGraphics3D->glDisable(GL_LIGHTING);

		pDC->m_pGraphics3D->glBegin(GL_LINES);

		pDC->m_pGraphics3D->glColorf(1.0, 0, 0);	// red
		pDC->m_pGraphics3D->glVertexf(0, 0, 0);
		pDC->m_pGraphics3D->glVertexf(1*len, 0, 0);

		pDC->m_pGraphics3D->glColorf(0.0, 1.0, 0);	// blue
		pDC->m_pGraphics3D->glVertexf(0, 0, 0);
		pDC->m_pGraphics3D->glVertexf(0, 1*len, 0);

		pDC->m_pGraphics3D->glColorf(0, 0, 1.0);	// green
		pDC->m_pGraphics3D->glVertexf(0, 0, 0);
		pDC->m_pGraphics3D->glVertexf(0, 0, 1*len);

		pDC->m_pGraphics3D->glEnd();

		pDC->m_pGraphics3D->glPopAttrib();
	}

	int nLight = pDC->m_nLight;
	int nNames = pDC->m_namedNodes.GetSize();

	int i;

	for (i = 0; i < m_children->m_items.GetSize(); i++)
	{
		if (m_children->m_items[i])
		{
			RenderImplImpl* render = dynamic_cast<RenderImplImpl*>(m_children->m_items[i]->GetNode());
			if (render)
			{
				render->PreDraw(pDC);
			}
		}
	}

	for (i = 0; i < m_children->m_items.GetSize(); i++)
	{
		if (m_children->m_items[i])
		{
			RenderImplImpl* render = dynamic_cast<RenderImplImpl*>(m_children->m_items[i]->GetNode());
			if (render)
			{
				render->Draw(pDC);
			}
		}
	}

	for (i = pDC->m_namedNodes.GetSize(); i >= nNames; i--)
	{
		ASSERT(0);
#if 0
		glPopName();
#endif
	}
	for (i = pDC->m_nLight; i >= nLight; i--)
	{
		pDC->m_pGraphics3D->glDisable(GL_LIGHT0+i);
	}
	pDC->m_nLight = nLight;

	pDC->m_pGraphics3D->glPopMatrix();
}
#endif

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////

// static
X3DField* X3DField::CreateFieldOfType(FieldType fieldType, X3DNode* ownerNode)
{
	X3DField* pField = NULL;

	switch (fieldType)
	{
	// SF
	case FieldType_SFBool:
		{
			pField = new SFBool(ownerNode);
		}
		break;

	case FieldType_SFInt32:
		{
			pField = new SFInt32(NULL, ownerNode);
		}
		break;

	case FieldType_SFFloat:
		{
			pField = new SFFloat(ownerNode);
		}
		break;

	case FieldType_SFString:
		{
			pField = new SFString(ownerNode);
		}
		break;

	case FieldType_SFVec2f:
		{
			pField = new SFVec2f(ownerNode);
		}
		break;

	case FieldType_SFVec3f:
		{
			pField = new SFVec3f(ownerNode);
		}
		break;

	case FieldType_SFVec4f:
		{
			pField = new SFVec4f(ownerNode);
		}
		break;

	case FieldType_SFColor:
		{
			pField = new SFColor(ownerNode);
		}
		break;

	case FieldType_SFColorRGBA:
		{
			pField = new SFColorRGBA(ownerNode);
		}
		break;

	case FieldType_SFTime:
		{
			pField = new SFTime(ownerNode);
		}
		break;

	case FieldType_SFRotation:
		{
			pField = new SFRotation(ownerNode);
		}
		break;

	case FieldType_SFNode:
		{
			pField = new TypedSFNode<X3DNode*>(ownerNode);
		}
		break;

	case FieldType_SFImage:
		{
			pField = new SFImage(ownerNode);
		}
		break;

	// MF
	case FieldType_MFInt32:
		{
			pField = new MFInt32(ownerNode);
		}
		break;

	case FieldType_MFFloat:
		{
			pField = new MFFloat(ownerNode);
		}
		break;

	case FieldType_MFDouble:
		{
			pField = new MFDouble(ownerNode);
		}
		break;

	case FieldType_MFVec2f:
		{
			pField = new MFVec2f(ownerNode);
		}
		break;

	case FieldType_MFVec3f:
		{
			pField = new MFVec3f(ownerNode);
		}
		break;

	case FieldType_MFRotation:
		{
			pField = new MFRotation(ownerNode);
		}
		break;

	case FieldType_MFColor:
		{
			pField = new MFColor(ownerNode);
		}
		break;

	case FieldType_MFString:
		{
			pField = new MFString(ownerNode);
		}
		break;

	case FieldType_MFURL:
		{
			pField = new MFURL(ownerNode);
		}
		break;

	case FieldType_MFNode:
		{
			pField = new MFNode(ownerNode);
		}
		break;
		
	default:
		ASSERT(0);
		return NULL;
	}

	return pField;
}

}	// x3d
}
