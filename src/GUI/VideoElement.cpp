#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

	/*
template<class ownerclass, T (*::get)() class T> class property_
{
public:

	operator T& ()
	{
		return m_value;
	}

	operator const T& () const
	{
		return m_value;
	}

	T& operator = (const T& other)
	{
		m_value = other;
	}

	T m_value;
};

#define _property(classname, propname)
*/

DependencyClass* VideoElement::get_Class()
{
	static DependencyClass depclass(typeid(thisClass), baseClass::get_Class());

	static DependencyProperty* properties[] =
	{
		get_UrlProperty(),
		get_DurationTimeProperty(),
		get_CurrentTimeProperty(),
		get_IsPlayingProperty(),
		get_IsStoppedProperty(),
		get_IsPausedProperty(),
	};

	return &depclass;
}

DependencyClass* VideoElement::pClass(get_Class());

IMP_DEPENDENCY_PROPERTY(String, VideoElement, Url, nullptr)
IMP_DEPENDENCY_PROPERTY(double, VideoElement, CurrentTime, 0.0)
IMP_DEPENDENCY_PROPERTY(double, VideoElement, DurationTime, 0.0)
IMP_DEPENDENCY_PROPERTY(bool, VideoElement, IsPlaying, false)
IMP_DEPENDENCY_PROPERTY(bool, VideoElement, IsStopped, false)
IMP_DEPENDENCY_PROPERTY(bool, VideoElement, IsPaused, false)

IMP_DEPENDENCY_PROPERTY(float, VideoElement, Volume, 0.0f)
IMP_DEPENDENCY_PROPERTY(float, VideoElement, Balance, 0.0f)

VideoElement::VideoElement() : UIElement(get_Class())
{
}

void VideoElement::OnComputedPropertyValueChanged(PropertyValue* pPropertyVal, bool handled)
{
	if (pPropertyVal->m_dp == get_UrlProperty())
	{
		if (m_pVideo != NULL)
		{
			ASSERT(0);
			// TODO, stop previous
		}

		String url = get_Url();

		m_pVideo = new DShow::VideoPlayer(this);
		m_pVideo->Load(url);

		handled = true;
	}

	baseClass::OnComputedPropertyValueChanged(pPropertyVal, handled);
}

HRESULT VideoElement::Init(IDirect3DDevice9* d3ddev, uint width, uint height, ID3D10Texture2D* texture)
{
	ASSERT(m_pBitmap == NULL);

	m_pBitmap = new Graphics::Bitmap(width, height, 0, Graphics::PixelFormat_t::RGBAP_32, NULL);
	m_pBitmap->m_d3d10_texture = texture;
	m_pBitmap->m_d3d10_texture->AddRef();

	return S_OK;
}

HRESULT VideoElement::DrawScene(IDirect3DDevice9* d3ddev, IDirect3DTexture9* texture)
{
	IRootVisual* root = GetRoot();
	if (root)
	{
		root->InvalidateRender();
	}

	return S_OK;
}

/*
void VideoElement::SetSrcRect(float fTU, float fTV)
{
}
*/

void VideoElement::Play()
{
	if (m_pVideo == NULL) raise(Exception("No video"));
	m_pVideo->Play();
}

void VideoElement::Pause()
{
	if (m_pVideo == NULL) raise(Exception("No video"));
	m_pVideo->Pause();
}

void VideoElement::Stop()
{
	if (m_pVideo == NULL) raise(Exception("No video"));
	m_pVideo->Stop();
}

void VideoElement::Render(ManagedRenderContext renderContext)
{
	Graphics::Bitmap* bitmap = get_Bitmap();
	if (bitmap)
	{
		if (true)
		{
			gm::RectF dstRect(0.0f, 0.0f, float(bitmap->GetWidth()), float(bitmap->GetHeight()));
			renderContext.DrawBitmap(bitmap, dstRect, get_Opacity());
		}
		else
		{
			Graphics::RenderTarget* rt = renderContext.m_p->GetRT();

			ImmediateRenderContext* imm = static_cast<ImmediateRenderContext*>(renderContext.m_p);
			rt->m_modelView = imm->m_transform;
			rt->m_modelViewProjection = rt->m_projection * rt->m_modelView;

			gm::RectF dstRect(80.0f, 20.0f, float(bitmap->GetWidth()), float(bitmap->GetHeight()));
			//*get_DestRect()

			Graphics::Direct10::s.Render(renderContext.m_p->GetRT(), bitmap, dstRect);
		}
	}
}

Graphics::Bitmap* VideoElement::GetBitmap(Graphics::RenderTarget* rt, int scaledWidth, int scaledHeight, float scaleX, float scaleY)
{
	Graphics::Bitmap* bitmap = get_Bitmap();
	if (bitmap)
	{
		return bitmap;
	}

	return NULL;
}

}	// Gui
}	// System
