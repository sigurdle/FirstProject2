namespace System
{
namespace Web
{

const unsigned short MEDIA_ERR_ABORTED = 1;
const unsigned short MEDIA_ERR_NETWORK = 2;
const unsigned short MEDIA_ERR_DECODE = 3;

class HTMLEXT MediaError : public Object
{
public:
	unsigned short get_code();

	unsigned short m_code;
};

// ready state
const unsigned short DATA_UNAVAILABLE = 0;
const unsigned short CAN_SHOW_CURRENT_FRAME = 1;
const unsigned short CAN_PLAY = 2;
const unsigned short CAN_PLAY_THROUGH = 3;

class HTMLEXT HTMLMediaElement :
	public HTMLElement,
	public ElementCSSInlineStyleImpl<HTMLMediaElement>
{
public:

	CTOR HTMLMediaElement(NamedNodeMap* attributes);

// error state
	MediaError* get_error();

// network state

	String get_src();
	void set_src(StringIn src);
	String get_currentSrc();

	unsigned long get_totalBytes();
	void load();

	unsigned short get_readyState();
	bool get_seeking();

// playback state
	float get_currentTime();
	void set_currentTime(float currentTime);

	float get_duration();

	bool get_paused();

	float get_defaultPlaybackRate();
	void set_defaultPlaybackRate(float defaultPlaybackRate);

	float get_playbackRate();
	void set_playbackRate(float playbackRate);

	bool get_ended();

	bool get_autoplay();
	void set_autoplay(bool autoplay);

	void play();
	void pause();

// looping
	float get_start();
	void set_start(float start);

	float get_end();
	void set_end(float end);

	float get_loopStart();
	void set_loopStart(float loopStart);

//	attribute float loopEnd;
//	attribute unsigned long playCount;
//	attribute unsigned long currentLoop;

	/*
// error state
readonly attribute MediaError error;

// network state
attribute DOMString src;
readonly attribute DOMString currentSrc;
const unsigned short EMPTY = 0;
const unsigned short LOADING = 1;
const unsigned short LOADED_METADATA = 2;
const unsigned short LOADED_FIRST_FRAME = 3;
const unsigned short LOADED = 4;
readonly attribute unsigned short networkState;
readonly attribute float bufferingRate;
readonly attribute boolean bufferingThrottled;
readonly attribute TimeRanges buffered;
readonly attribute ByteRanges bufferedBytes;
readonly attribute unsigned long totalBytes;
void load();

// ready state
const unsigned short DATA_UNAVAILABLE = 0;
const unsigned short CAN_SHOW_CURRENT_FRAME = 1;
const unsigned short CAN_PLAY = 2;
const unsigned short CAN_PLAY_THROUGH = 3;
readonly attribute unsigned short readyState;
readonly attribute boolean seeking;

// playback state
attribute float currentTime;
readonly attribute float duration;
readonly attribute boolean paused;
attribute float defaultPlaybackRate;
attribute float playbackRate;
readonly attribute TimeRanges played;
readonly attribute TimeRanges seekable;
readonly attribute boolean ended;
attribute boolean autoplay;
void play();
void pause();

// looping
attribute float start;
attribute float end;
attribute float loopStart;
attribute float loopEnd;
attribute unsigned long playCount;
attribute unsigned long currentLoop;

// cue ranges
void addCueRange(in DOMString className, in DOMString id, in float start, in float end, in boolean pauseOnExit, in CueRangeCallback enterCallback, in CueRangeCallback exitCallback);
void removeCueRanges(in DOMString className);

// controls
attribute boolean controls;
attribute float volume;
attribute boolean muted;
*/

protected:

	MediaError* m_error;
};

}	// Web
}	// System
