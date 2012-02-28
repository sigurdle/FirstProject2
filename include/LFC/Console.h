namespace System
{

enum ConsoleColor
{
	ConsoleColor_Black = 0,
	ConsoleColor_DarkGray = 8,

	ConsoleColor_DarkBlue = 1,
	ConsoleColor_Blue = 1 | 8,

	ConsoleColor_DarkGreen = 2,
	ConsoleColor_Green = 2 | 8,

	ConsoleColor_DarkCyan = 3,
	ConsoleColor_Cyan = 3 | 8,

	ConsoleColor_DarkRed = 4,
	ConsoleColor_Red = 4 | 8,

	ConsoleColor_DarkMagenta = 5,
	ConsoleColor_Magenta = 5 | 8,

	ConsoleColor_DarkYellow = 6,
	ConsoleColor_Yellow = 6 | 8,

	ConsoleColor_Gray = 7,
	ConsoleColor_White = 7 | 8
};

class LFCEXT ConsoleBuffer : public Object
{
public:

	CTOR ConsoleBuffer();
	CTOR ConsoleBuffer(HANDLE hFile);
	~ConsoleBuffer();

	void IncRef()
	{
	}

	void DecRef()
	{
	}

	void Clear();

	ConsoleColor get_BackgroundColor();
	void set_BackgroundColor(ConsoleColor color);
	ConsoleColor get_ForegroundColor();
	void set_ForegroundColor(ConsoleColor color);

	int get_CursorLeft();
	int get_CursorTop();
	void set_CursorPosition(int x, int y);

	void SetWindowSize(int width, int height);

	HANDLE get_Handle()
	{
		return m_hFile;
	}

protected:

	HANDLE m_hFile;
};

class LFCEXT Console
{
public:

	static void Clear();
	static void SetWindowPosition(int x, int y);
	static void SetWindowSize(int width, int height);

	static String get_OriginalTitle();
	static String get_Title();
	static void set_Title(StringIn title);
	static bool get_CursorVisible();
	static void set_CursorVisible(bool visible);
	static int get_LargestWindowWidth();
	static int get_LargestWindowHeight();

	static ConsoleColor get_BackgroundColor();
	static void set_BackgroundColor(ConsoleColor color);
	static ConsoleColor get_ForegroundColor();
	static void set_ForegroundColor(ConsoleColor color);

	static bool get_TreatControlCAsInput();
	static void set_TreatControlCAsInput(bool val);

	static bool get_FullScreen();
	static void set_FullScreen(bool fullScreen);

	static ConsoleBuffer* get_ActiveBuffer();
	static void set_ActiveBuffer(ConsoleBuffer* buffer);

	static void Beep();
	static void Beep(unsigned int freq, unsigned int duration);

//	static Window* get_Window();

	static bool Open();
	static bool Close();

	static void Write(int number);
	static void Write(float number);
	static void Write(double number);
	static void Write(StringIn str);
	static void WriteLn(StringIn str);

//	static _Ptr<IO::StreamWriter> get_Out();
// static _Ptr<IO::StreamReader> get_In();
//	static _Ptr<IO::StreamWriter> get_Err();

	static _Ptr<IO::TextReader> get_In()
	{
		return In;
	}

	static _Ptr<IO::StreamWriter> get_Out();
	static void set_Out(IO::StreamWriter* stream);

	static _Ptr<IO::StreamWriter> get_Err()
	{
		return Err;
	}

	static Event0& get_TitleChanged()
	{
		return s_titleChanged;
	}

	static Event0& get_ForegroundColorChanged()
	{
		return s_foregroundColorChanged;
	}

	static Event0& get_BackgroundColorChanged()
	{
		return s_backgroundColorChanged;
	}

	static IO::FileStream* _In;
	static IO::FileStream* _Out;
	static IO::FileStream* _Err;

	static _Ptr<IO::StreamReader> In;
	static _Ptr<IO::StreamWriter> Out;
	static _Ptr<IO::StreamWriter> Err;

	static _Ptr<ConsoleBuffer> s_activeBuffer;
	static bool s_open;

private:

	CTOR Console();

	static String s_originalTitle;

	static Event0 s_titleChanged;
	static Event0 s_foregroundColorChanged;
	static Event0 s_backgroundColorChanged;
};

}	// System
