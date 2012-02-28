#ifndef __SWFPLAYER_H_
#define __SWFPLAYER_H_

#ifndef SWFExt
#define SWFExt	DECLSPEC_DLLIMPORT
#endif

//#include "Movie.h"

namespace System
{
namespace SWF
{

class Decoder;

class Wind;

class SWFExt Player : public UI::FrameworkElement, public System::ActionScripting::MembersMap
{
public:

	CTOR Player();
	~Player();

	Decoder* m_decoder;

	PlacedCharacter* m_OverButton;

//	std::vector<std::string> m_stack;

	Wind* m_pWind;

	Movie* GetMovie() const;
	void SetMovie(Movie* movie);

	void Play();

	PlacedCharacter* m_placedMovie;

	PlacedCharacter* HitTest(Timeline* timeline, LDraw::PointD point, LDraw::Matrix3f* transform);

protected:

	friend class Wind;

	void OnAdvance();
	void OnAdvanceChildren(Timeline* timeline);
	void OnAdvance(Timeline* timeline, PlacedCharacter* placed);

	void RenderShape(ShapeCharacter* shape, UI::Graphics* pGraphics);
	void RenderText(TextCharacter* bitmapCharacter, const ColorTransform& colorTransform, UI::Graphics* pGraphics);
//	void RenderBitmap(BitmapCharacter shape, LDraw::Graphics* pGraphics);
	void RenderShape(const ShapeData* shape, LDraw::Brush* brush, UI::Graphics* pGraphics);

	void Render(Timeline* timeline, const ColorTransform& colorTransform, UI::Graphics* pGraphics);

	virtual LDraw::SizeD OnMeasure(LDraw::SizeD availSize);
	virtual void OnRender(UI::Graphics* pGraphics);
//	virtual void handleEvent(System::Event* evt);

	virtual void OnMouseMove(UI::MouseEventArgs* args);
	virtual void OnButtonDown(UI::MouseButtonEventArgs* args);
	virtual void OnButtonUp(UI::MouseButtonEventArgs* args);

	void ExecuteScripts(PlacedCharacter* placed, ButtonCharacter* pButton, uint16 condMask);

	Movie* m_movie;
};

}	// LSWF
}

#endif // __SWFPLAYER_H_
