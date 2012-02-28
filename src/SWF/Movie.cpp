#include "stdafx.h"
#include "swf.h"
#include "Movie.h"
#include "_Movie.h"

#include "swfdecoder.h"

namespace System
{
namespace SWF
{

	/*
FillStyle::FillStyle(const FillStyle& other)
{
	m_p = other.m_p;
	if (m_p)
		m_p->AddRef();
}
*/

FillStyle::FillStyle(RGBAColor color)
{
	m_Type = 0;
	m_color = color;
}

FillStyle::FillStyle(uint8 Type, RGBAColor color)
{
	m_Type = Type;
	m_color = color;
}

FillStyle::FillStyle(uint8 Type, BitmapCharacter* bitmap)
{
	m_Type = Type;
	m_bitmap = bitmap;
}

/*
FillStyle::~FillStyle()
{
	if (m_p)
		m_p->Release();
}

FillStyle& FillStyle::operator = (const FillStyle& other)
{
	_FillStyle* old = m_p;
	m_p = other.m_p;
	if (m_p) m_p->AddRef();
	if (old) old->Release();

	return *this;
}
*/

uint8 FillStyle::GetFillType() const
{
	return m_Type;
}

RGBAColor FillStyle::GetColor() const
{
	return m_color;
}

BitmapCharacter* FillStyle::GetBitmapCharacter() const
{
	return m_bitmap;
}

/////////////////////////////////////////////////////////////
// PlacedCharacter

System::Variant PlacedCharacter::GetMember(StringIn name)
{
			if (name == "_currentframe")			return get__currentframe();
	else	if (name == "gotoAndPlay")			return (System::Object*)new gotoAndPlay(this);
	else													return MembersMap::GetMember(name);
}

void PlacedCharacter::gotoAndPlay::dispatch(System::ActionScripting::VM* vm, System::ActionScripting::StackFrame* pStackFrame, int numargs)
{
	ASSERT(numargs == 1);
	String label = vm->pop();

	PlacedCharacter* placed = m_placed;
	Timeline* timeline;
	while ((timeline = dynamic_cast<Timeline*>(placed->m_character)) == NULL)
	{
		placed = dynamic_cast<Sprite*>(placed->m_parent)->m_placed;
	}

	int nframe = timeline->m_labels[label]-1;

	//m_placed->

	TRACE("%s %d\n", label->c_str(), nframe);

	placed->m_gotoFrame = nframe;
//	timeline->m_frames[nframe]->m_stream->Seek(timeline->m_frames[nframe]->m_streamPos);
//	timeline->m_frames[nframe]->DoActions(placed);

	delete pStackFrame;

	// push result on stack
	vm->push(System::ActionScripting::StkElt(0L));
}

/////////////////////////////////////////////////////////////
// Timeline

Timeline::Timeline()
{
	m_FrameCount = 0;
	m_DecodedFrameCount = 0;

	m_depth = new PlacedCharacter*[65536];
	for (int i = 0; i < 65536; i++)
	{
		m_depth[i] = NULL;
	}
}

void Timeline::gotoAndPlay(StringIn label)
{
//	int nframe = ((_Timeline*)(_Sprite*)Sprite(m_character).m_p)->m_labels[label]-1;
	int nframe = m_labels[label]-1;

	if (nframe >= 0)
	{
	}
	else
	{
		TRACE("gotoAndPlay(%s) : unspecified label\n", label->c_str());
	}
}

/////////////////////////////////////////////////////////////
// Sprite

System::Variant Sprite::GetMember(System::StringA* name)
{
		  if (*name == "_framesloaded")			return get__framesloaded();
	else													return MembersMap::GetMember(name);
}

/*
Sprite::Sprite()
{
	m_p = NULL;
}

Sprite::Sprite(const Sprite& other)
{
	m_p = other.m_p;
	if (m_p) m_p->AddRef();
}

Sprite::Sprite(_Sprite* p)
{
	m_p = p;
	if (m_p) m_p->AddRef();
}

Sprite::Sprite(const Object& other)
{
	m_p = dynamic_cast<_Sprite*>(other.m_p);
	if (m_p) m_p->AddRef();
}
*/

/*
int Sprite::GetFrameCount() const 
{
	return ((_Sprite*)m_p)->GetFrameCount();
}

void Sprite::SetFrameCount(int FrameCount)
{
	->SetFrameCount(FrameCount);
}
*/

/////////////////////////////////////////////////////////////
// Movie

/*
Movie::Movie(const Movie& other)
{
	m_p = other.m_p;
	if (m_p) m_p->AddRef();
}

Movie::~Movie()
{
	if (m_p)
		m_p->Release();
}

Movie& Movie::New()
{
	ASSERT(m_p == NULL);
	m_p = new _Movie;
	m_p->AddRef();

	return *this;
}
*/

Movie::Movie()
{
			m_FrameSize.Xmin = 0;
			m_FrameSize.Ymin = 0;
			m_FrameSize.Xmax = 0;
			m_FrameSize.Ymax = 0;

			m_bBackground = false;

			m_lastDefinitionID = 0;

			m_FrameRate = 0;

	m_character = new Character*[65536];
	std::memset(m_character, 0, 65536*sizeof(Character*));
}

bool Movie::HasBackgroundColor() const
{
	return m_bBackground;
}

RGBColor Movie::GetBackgroundColor() const
{
	return m_BackgroundColor;
}

Rect Movie::GetFrameSize() const
{
	return m_FrameSize;
}

void Movie::SetFrameSize(long Width, long Height)
{
	m_FrameSize.Xmax = Width;
	m_FrameSize.Ymax = Height;
}

void Movie::SetFrameRate(uint16 FrameRate)
{
	m_FrameRate = FrameRate;
}

uint16 Movie::GetFrameRate() const
{
	return m_FrameRate;
}

void Movie::SetBackgroundColor(RGBColor color)
{
	m_bBackground = true;
	m_BackgroundColor = color;
}

int Movie::GetFrameCount() const
{
	return m_FrameCount;
}

void Movie::SetFrameCount(int FrameCount)
{
	ASSERT(FrameCount >= 0 && FrameCount < 65536);
	m_FrameCount = FrameCount;
}

/*
Movie& Movie::operator = (const Movie& other)
{
	_Movie* old = m_p;
	m_p = other.m_p;
	if (m_p) m_p->AddRef();
	if (old) old->Release();

	return *this;
}
*/

void Movie::DefineShape(uint8 level, Character* character)
{
	ASSERT(m_character);
	ASSERT(m_character[character->GetCharacterID()] == NULL);
	m_character[character->GetCharacterID()] = character;
}

void Movie::DefineBitsLossless(uint8 level, Character* character)
{
	ASSERT(m_character);
	ASSERT(m_character[character->GetCharacterID()] == NULL);
	m_character[character->GetCharacterID()] = character;
}

Character* Movie::GetCharacter(int index) const
{
	ASSERT(index >= 0 && index < 65536);
	return m_character[index];
}

//

System::StringA* TagStream::ReadString()
{
	System::BufferImp<char> buffer;
	System::StringBuilderA value(&buffer);
	char c;
	while ((c = getbyte()) != 0)
	{
		value << c;
	}

	return buffer.DetachToString();
}


}	// SWF
}
