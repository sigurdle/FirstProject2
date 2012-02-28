#include "PSVGFEPointLightElement.h"
#include "SVGFEPointLightElement.h"
#include "SVGFEDistantLightElement.h"
#include "SVGFESpotLightElement.h"

namespace System
{
namespace Web
{

//virtual
CEffect* NAME::Filter(LDraw::GraphicsO* pO, CEffect* inPinImage[], PSVGFilterElement* pFilterElement, const LDraw::RectF& uRect, double scaleX, double scaleY)
{
	LDraw::Bitmap* inImage = inPinImage[0]->m_outImage;

#if 0

#ifdef DIFFUSE

	SVGFEDiffuseLightingElement* psvgElement = static_cast<SVGFEDiffuseLightingElement*>(m_pNode);

	double kd = psvgElement->m_diffuseConstant->m_animated->m_animVal->m_value->m_value;

#else

	SVGFESpecularLightingElement* psvgElement = static_cast<SVGFESpecularLightingElement*>(m_pNode);

	double ks = psvgElement->m_specularConstant->m_animated->m_animVal->m_value->m_value;
	double specularExponent = psvgElement->m_specularExponent->m_animated->m_animVal->m_value->m_value;

#endif

	double surfaceScale = psvgElement->m_surfaceScale->m_animated->m_animVal->m_value->m_value;

	long lighttype;	// 0=distance,1=point,2=spot

	SVGFEPointLightElement::PSVGFEPointLightElement* pfePoint = (SVGFEPointLightElement::PSVGFEPointLightElement*)GetElementByTagNameNS(WSTR("http://www.w3.org/2000/svg"), WSTR("fePointLight"), false);
	PSVGElement* pfeDistant = (PSVGElement*)GetElementByTagNameNS(WSTR("http://www.w3.org/2000/svg"), WSTR("feDistantLight"), false);
	PSVGElement* pfeSpot = (PSVGElement*)GetElementByTagNameNS(WSTR("http://www.w3.org/2000/svg"), WSTR("feSpotLight"), false);
	if (pfeDistant)
	{
		lighttype = 0;
	}
	else if (pfePoint)
	{
		lighttype = 1;
	}
	else if (pfeSpot)
	{
		lighttype = 2;
	}
	else
		return NULL;

	if (true)
	{
		LDraw::BitmapData srcdata;
		if (inImage->LockBits(
			&LDraw::RectI(0, 0, inImage->GetWidth(), inImage->GetHeight()),
			LDraw::ImageLockModeRead/*,
			PixelFormat32bppPARGB*/, &srcdata) != 0)
		{
			ASSERT(0);
			return NULL;
		}

		LDraw::BitmapData dstdata;
		if (outImage->LockBits(
			&LDraw::RectI(0, 0, outImage->GetWidth(), outImage->GetHeight()),
			LDraw::ImageLockModeWrite/*,
			PixelFormat32bppPARGB*/, &dstdata) != 0)
		{
			inImage->UnlockBits(&srcdata);

			ASSERT(0);
			return NULL;
		}

		double lightColor[3];
		lightColor[0] = MAX(0, MIN(255, m_computedLightingColor.m_rgbColor[0]))/255.0;
		lightColor[1] = MAX(0, MIN(255, m_computedLightingColor.m_rgbColor[1]))/255.0;
		lightColor[2] = MAX(0, MIN(255, m_computedLightingColor.m_rgbColor[2]))/255.0;

		LDraw::vector3d S;	// Spot light

		LDraw::vector3d lightLocation;
		if (lighttype == 1)	// Point
		{
			SVGFEPointLightElement* psvgfePoint = static_cast<SVGFEPointLightElement*>(pfePoint->m_pNode);

			lightLocation[0] = psvgfePoint->m_x->m_animated->m_animVal->m_value->m_value;
			lightLocation[1] = psvgfePoint->m_y->m_animated->m_animVal->m_value->m_value;
			lightLocation[2] = psvgfePoint->m_z->m_animated->m_animVal->m_value->m_value;
		}
		else if (lighttype == 2)	// Spot
		{
			SVGFESpotLightElement* psvgfeSpot = static_cast<SVGFESpotLightElement*>(pfeSpot->m_pNode);

			lightLocation[0] = psvgfeSpot->m_x->m_animated->m_animVal->m_value->m_value;
			lightLocation[1] = psvgfeSpot->m_y->m_animated->m_animVal->m_value->m_value;
			lightLocation[2] = psvgfeSpot->m_z->m_animated->m_animVal->m_value->m_value;

			LDraw::vector3d pointsAt;

			pointsAt[0] = psvgfeSpot->m_pointsAtX->m_animated->m_animVal->m_value->m_value;
			pointsAt[1] = psvgfeSpot->m_pointsAtY->m_animated->m_animVal->m_value->m_value;
			pointsAt[2] = psvgfeSpot->m_pointsAtZ->m_animated->m_animVal->m_value->m_value;

			S = lightLocation - pointsAt;

		//	if (!gmIsZero(S.length()))
			if (S[0] != 0 || S[1] != 0 || S[2] != 0)
				S.normalize();
		}

		LDraw::vector3d L;

		if (lighttype == 0)	// Distant
		{
			SVGFEDistantLightElement* psvgfeDistant = static_cast<SVGFEDistantLightElement*>(pfeDistant->m_pNode);

			double azimuth = psvgfeDistant->m_azimuth->m_animated->m_animVal->m_value->m_value;
			double elevation = psvgfeDistant->m_elevation->m_animated->m_animVal->m_value->m_value;

		// For Infinite light sources it is constant:

			double cos_elevation = cos(gmRadians(elevation));

			double Lx = cos(gmRadians(azimuth))*cos_elevation;
			double Ly = sin(gmRadians(azimuth))*cos_elevation;
			double Lz = sin(gmRadians(elevation));

			L = LDraw::vector3d(Lx, Ly, Lz);//.normalize();
		}

		double Lr, Lg, Lb;

		if (lighttype == 0 || lighttype == 1)
		{
			Lr = lightColor[0];
			Lg = lightColor[1];
			Lb = lightColor[2];
		}
		//else ; Spotlight

	// Surface normal is calculated using the Sobel gradient 3x3 filter:

	#define I(x,y) (((LDraw::PixelRGBAP_32*)((uint8*)srcdata.Scan0 + srcdata.Stride*(y) + (x)*4))->a/255.0)

	#define Nx(x,y) (-surfaceScale * 1/4* \
							(( I(x+1,y-1) + 2*I(x+1,y) + I(x+1,y+1)) \
							- I(x-1,y-1) - 2*I(x-1,y) - I(x-1,y+1)))

	#define Ny(x,y) (-surfaceScale * 1/4* \
							(( I(x-1,y+1) + 2*I(x,y+1) + I(x+1,y+1)) \
							 - I(x-1,y-1) - 2*I(x,y-1) - I(x+1,y-1)))

	#define Nz(x,y) 1.0

	//	constant eye vector E = (0,0,1) (for point light)
		LDraw::vector3d	E(0,0,1);

		int width = inImage->GetWidth();
		int height = inImage->GetHeight();

		for (int y = 1; y < height-1; y++)
		{
			LDraw::PixelRGBAP_32* in = (LDraw::PixelRGBAP_32*)((uint8*)srcdata.Scan0 + srcdata.Stride*y);
			LDraw::PixelRGBAP_32* out = (LDraw::PixelRGBAP_32*)((uint8*)dstdata.Scan0 + dstdata.Stride*y);

			ASSERT(in->r <= in->a);
			ASSERT(in->g <= in->a);
			ASSERT(in->b <= in->a);

			for (int x = 1; x < width-1; x++)
			{
			// Calculate L, the unit vector from the image sample to the light

			// For Point and spot lights it is a function of position:
				if (lighttype == 1 || lighttype == 2)
				{
					double Lx = lightLocation[0] - x;// + bounds.X;
					double Ly = lightLocation[1] - y;
					double Lz = lightLocation[2] - (surfaceScale * (in->a/255.0));	//Z(x,y);

					L = LDraw::vector3d(Lx, Ly, Lz).normalize();

				//	Lr,Lg,Lb, the light color vector, is a function of position
				// in the spot light case only:
					if (lighttype == 2)	// Spotlight
					{
						double dotLS = LDraw::dot(L, S);
						ASSERT(dotLS > 0);	// TODO, check if the code below works in this case (should be black)

						double specularExponent = static_cast<SVGFESpotLightElement*>(pfeSpot->m_pNode)->m_specularExponent->m_animated->m_animVal->m_value->m_value;
						Lr = lightColor[0]*pow(-dotLS, specularExponent);
						Lg = lightColor[1]*pow(-dotLS, specularExponent);
						Lb = lightColor[2]*pow(-dotLS, specularExponent);
						/*
						// where S is the unit vector pointing from the light to the point (pointsAtX, pointsAtY, pointsAtZ) in the x-y plane:

						Sx = pointsAtX - Lightx
						Sy = pointsAtY - Lighty
						Sz = pointsAtZ - Lightz
						*/

					//	S = (Sx, Sy, Sz) / Norm(Sx, Sy, Sz) 
						
						/*
						Lr = Lightr*pow((-L.S),specularExponent)
						Lg = Lightg*pow((-L.S),specularExponent)
						Lb = Lightb*pow((-L.S),specularExponent) 

						where S is the unit vector pointing from the light to the point (pointsAtX, pointsAtY, pointsAtZ) in the x-y plane:

						Sx = pointsAtX - Lightx
						Sy = pointsAtY - Lighty
						Sz = pointsAtZ - Lightz

						S = (Sx, Sy, Sz) / Norm(Sx, Sy, Sz) 
						*/

					//	If L.S is positive, no light is present. (Lr = Lg = Lb = 0)
					}
				}
			//	else ; for distant light it is constant and calculated outside the loop

			//	gmVector3 L = gmVector3(Lx, Ly, Lz).normalize();

				LDraw::vector3d N = LDraw::vector3d(Nx(x,y), Ny(x,y), Nz(x,y)).normalize();

				// The resulting RGBA image is computed as follows:

#ifdef DIFFUSE
				double dotNL = LDraw::dot(N, L);

				if (dotNL > 0)
				{
					double Dr = kd * dotNL * Lr;
					double Dg = kd * dotNL * Lg;
					double Db = kd * dotNL * Lb;

					out->r = (uint8)(Dr * 255);
					out->g = (uint8)(Dg * 255);
					out->b = (uint8)(Db * 255);
				}
				else
				{
					out->r = 0;
					out->g = 0;
					out->b = 0;
				}
				out->a = 255;

#else
			//	The definition of H reflects our assumption of the constant eye vector E = (0,0,1):
			// H = (L + E) / Norm(L+E)
				LDraw::vector3d H = (L + E).normalize();
			//	where L is the light unit vector

				double dotNH = LDraw::dot(N, H);
				double powNH = ks * pow(dotNH, specularExponent);

				double Sr = powNH * Lr;
				double Sg = powNH * Lg;
				double Sb = powNH * Lb;
				double Sa = MAX(Sr, MAX(Sg, Sb));

				out->r = (uint8)(Sr * 255);
				out->g = (uint8)(Sg * 255);
				out->b = (uint8)(Sb * 255);
			//	out->alpha = min(in->alpha, (BYTE)(Sa * 255));
				out->a = (uint8)(Sa * 255);
#endif

				/*
				ASSERT(out->red <= out->alpha);
				ASSERT(out->green <= out->alpha);
				ASSERT(out->blue <= out->alpha);
				*/

			// Un - premultiply destination
				/*
				if (out->alpha > 0)
				{
					out->red = ((int)out->red * 255) / out->alpha;
					out->green = ((int)out->green * 255) / out->alpha;
					out->blue = ((int)out->blue * 255) / out->alpha;
				}
				*/

				in++;
				out++;
			}
		}

		inImage->UnlockBits(&srcdata);
		outImage->UnlockBits(&dstdata);
	}
#endif
	return 0;
}

}	// LSVG
}
