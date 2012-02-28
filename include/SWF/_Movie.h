
#pragma once

namespace SWF
{

#if 0
	class _FillStyle : public System::_Object
	{
	public:
		_FillStyle()// : m_refcount(0)
		{
		}

		int m_index;

		//ULONG m_refcount;

		uint8 m_Type;

		RGBAColor m_color;
		BitmapCharacter m_bitmap;
	};

	class _Sprite : public _Timeline, public Character::_Character,
		public ::ActionScript::MembersMap
	{
	public:

		PlacedCharacter* m_placed;	// ?? sprite can only be placed once ?

		virtual Variant GetMember(System::StringA name)
		{
				  if (name == "_framesloaded")			return get__framesloaded();
			else													return MembersMap::GetMember(name);
		}
	};

	class _Movie : public System::_Object, public _Timeline,
		public ::ActionScript::MembersMap
	{
	public:
		_Movie()
		{
			m_FrameSize.Xmin = 0;
			m_FrameSize.Ymin = 0;
			m_FrameSize.Xmax = 0;
			m_FrameSize.Ymax = 0;

			m_bBackground = false;

			m_lastDefinitionID = 0;

			m_FrameRate = 0;

			m_character = new Character[65536];
			/*
			for (int i = 0; i < 65536; i++)
			{
				m_character[i] = NULL;
			}
			*/
		}

		virtual Variant GetMember(System::StringA name)
		{
				  if (name == "_framesloaded")			return get__framesloaded();
			else													return MembersMap::GetMember(name);
		}

		bool m_bBackground;
		RGBColor m_BackgroundColor;
		Rect m_FrameSize;
		uint16 m_FrameRate;

		typedef map<uint16, Character*> tydefmap;

		tydefmap m_definitions;

		uint16 m_lastDefinitionID;

		Character* m_character;
	};

#endif
}