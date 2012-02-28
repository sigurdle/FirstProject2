#include "stdafx.h"
#include <math.h>
#include "glu.h"

/*
 * This matmul was contributed by Thomas Malik 
 *
 * Perform a 4x4 matrix multiplication  (product = a x b).
 * Input:  a, b - matrices to multiply
 * Output:  product - product of a and b
 * WARNING: (product != b) assumed
 * NOTE:    (product == a) allowed    
 *
 * KW: 4*16 = 64 muls
 */
#define A(row,col)  a[(col<<2)+row]
#define B(row,col)  b[(col<<2)+row]
#define P(row,col)  product[(col<<2)+row]

static void matmul4( GLdouble *product, const GLdouble *a, const GLdouble *b )
{
   GLint i;
   for (i = 0; i < 4; i++) {
      GLfloat ai0=A(i,0),  ai1=A(i,1),  ai2=A(i,2),  ai3=A(i,3);
      P(i,0) = ai0 * B(0,0) + ai1 * B(1,0) + ai2 * B(2,0) + ai3 * B(3,0);
      P(i,1) = ai0 * B(0,1) + ai1 * B(1,1) + ai2 * B(2,1) + ai3 * B(3,1);
      P(i,2) = ai0 * B(0,2) + ai1 * B(1,2) + ai2 * B(2,2) + ai3 * B(3,2);
      P(i,3) = ai0 * B(0,3) + ai1 * B(1,3) + ai2 * B(2,3) + ai3 * B(3,3);
   }
}

void gl_Frustum2(GLdouble mat[16],
                 GLdouble left, GLdouble right,
	 	 GLdouble bottom, GLdouble top,
		 GLdouble nearval, GLdouble farval )
{
   GLdouble x, y, a, b, c, d;
   GLdouble m[16];
//   GLmatrix *mat = 0;

//   GET_ACTIVE_MATRIX( ctx,  mat, ctx->NewState, "glFrustrum" );

   if ((nearval<=0.0 || farval<=0.0) || (nearval == farval) || (left == right) || (top == bottom)) {
     // gl_error( ctx,  GL_INVALID_VALUE, "glFrustum(near or far)" );
      return;
   }

   x = (2.0*nearval) / (right-left);
   y = (2.0*nearval) / (top-bottom);
   a = (right+left) / (right-left);
   b = (top+bottom) / (top-bottom);
   c = -(farval+nearval) / ( farval-nearval);
   d = -(2.0*farval*nearval) / (farval-nearval);  /* error? */

#define M(row,col)  m[col*4+row]
   M(0,0) = x;     M(0,1) = 0.0F;  M(0,2) = a;      M(0,3) = 0.0F;
   M(1,0) = 0.0F;  M(1,1) = y;     M(1,2) = b;      M(1,3) = 0.0F;
   M(2,0) = 0.0F;  M(2,1) = 0.0F;  M(2,2) = c;      M(2,3) = d;
   M(3,0) = 0.0F;  M(3,1) = 0.0F;  M(3,2) = -1.0F;  M(3,3) = 0.0F;
#undef M


//   gl_mat_mul_floats( mat, m, MAT_FLAG_PERSPECTIVE );
	matmul4(mat, mat, m);      


#if 0
   if (ctx->Transform.MatrixMode == GL_PROJECTION)
   {
      /* Need to keep a stack of near/far values in case the user push/pops
       * the projection matrix stack so that we can call Driver.NearFar()
       * after a pop.
       */
      ctx->NearFarStack[ctx->ProjectionStackDepth][0] = nearval;
      ctx->NearFarStack[ctx->ProjectionStackDepth][1] = farval;
      
      if (ctx->Driver.NearFar) {
	 (*ctx->Driver.NearFar)( ctx, nearval, farval );
      }
   }
#endif
}

/*
 * Transform a point (column vector) by a 4x4 matrix.  I.e.  out = m * in
 * Input:  m - the 4x4 matrix
 *         in - the 4x1 vector
 * Output:  out - the resulting 4x1 vector.
 */
static void transform_point( GLdouble out[4], const GLdouble m[16],
			     const GLdouble in[4] )
{
#define M(row,col)  m[col*4+row]
   out[0] = M(0,0) * in[0] + M(0,1) * in[1] + M(0,2) * in[2] + M(0,3) * in[3];
   out[1] = M(1,0) * in[0] + M(1,1) * in[1] + M(1,2) * in[2] + M(1,3) * in[3];
   out[2] = M(2,0) * in[0] + M(2,1) * in[1] + M(2,2) * in[2] + M(2,3) * in[3];
   out[3] = M(3,0) * in[0] + M(3,1) * in[1] + M(3,2) * in[2] + M(3,3) * in[3];
#undef M
}

void gluPerspective2(double m[16], GLdouble fovy, GLdouble aspect,
                              GLdouble zNear, GLdouble zFar )
{
   GLdouble xmin, xmax, ymin, ymax;

   ymax = zNear * tan( fovy * M_PI / 360.0 );
   ymin = -ymax;

   xmin = ymin * aspect;
   xmax = ymax * aspect;

   gl_Frustum2(m, xmin, xmax, ymin, ymax, zNear, zFar );
}

/* projection du point (objx,objy,obz) sur l'ecran (winx,winy,winz) */
int gluProject2(GLdouble objx,GLdouble objy,GLdouble objz,
					 const GLdouble model[16],const GLdouble proj[16],
					 const GLint viewport[4],
					 GLdouble *winx,GLdouble *winy,GLdouble *winz)
{
	/* matrice de transformation */
	GLdouble in[4],out[4];
	
	/* initilise la matrice et le vecteur a transformer */
	in[0]=objx; in[1]=objy; in[2]=objz; in[3]=1.0;
	transform_point(out,model,in);
	transform_point(in,proj,out);
	
	/* d'ou le resultat normalise entre -1 et 1*/
	if (in[3]==0.0)
		return GL_FALSE;
	
	in[0]/=in[3]; in[1]/=in[3]; in[2]/=in[3];
	
	/* en coordonnees ecran */
	*winx = viewport[0]+(1+in[0])*viewport[2]/2;
	*winy = viewport[1]+(1+in[1])*viewport[3]/2;
	*winy = viewport[3] - *winy;
		
		/* entre 0 et 1 suivant z */
		*winz = (1+in[2])/2;
	return GL_TRUE;
}

/* projection du point (objx,objy,obz) sur l'ecran (winx,winy,winz) */
int gluProject2(GLdouble objx,GLdouble objy,GLdouble objz,
					 const GLdouble model[16],const GLdouble proj[16],
					 const GLdouble viewport[4],
					 GLdouble *winx,GLdouble *winy,GLdouble *winz)
{
	/* matrice de transformation */
	GLdouble in[4],out[4];
	
	/* initilise la matrice et le vecteur a transformer */
	in[0]=objx; in[1]=objy; in[2]=objz; in[3]=1.0;
	transform_point(out,model,in);
	transform_point(in,proj,out);
	
	/* d'ou le resultat normalise entre -1 et 1*/
	if (in[3]==0.0)
		return GL_FALSE;
	
	in[0]/=in[3]; in[1]/=in[3]; in[2]/=in[3];
	
	/* en coordonnees ecran */
	*winx = viewport[0]+(1+in[0])*viewport[2]/2;
	*winy = viewport[1]+(1+in[1])*viewport[3]/2;
	*winy = viewport[3] - *winy;
		
		/* entre 0 et 1 suivant z */
		*winz = (1+in[2])/2;

		ASSERT(*winz >= 0 && *winz < 1);

	return GL_TRUE;
}
