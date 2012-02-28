
#ifdef __cplusplus
extern "C" {
#endif

namespace System
{
namespace MSWindows
{

#define MM_WOM_OPEN         0x3BB           /* waveform output */
#define MM_WOM_CLOSE        0x3BC
#define MM_WOM_DONE         0x3BD

/* wave callback messages */
#define WOM_OPEN        MM_WOM_OPEN
#define WOM_CLOSE       MM_WOM_CLOSE
#define WOM_DONE        MM_WOM_DONE
#define WIM_OPEN        MM_WIM_OPEN
#define WIM_CLOSE       MM_WIM_CLOSE
#define WIM_DATA        MM_WIM_DATA

/* device ID for wave device mapper */
#define WAVE_MAPPER     ((UINT)-1)

/* flags for dwFlags parameter in waveOutOpen() and waveInOpen() */
#define  WAVE_FORMAT_QUERY         0x0001
#define  WAVE_ALLOWSYNC            0x0002
#if(WINVER >= 0x0400)
#define  WAVE_MAPPED               0x0004
#define  WAVE_FORMAT_DIRECT        0x0008
#define  WAVE_FORMAT_DIRECT_QUERY  (WAVE_FORMAT_QUERY | WAVE_FORMAT_DIRECT)
#endif /* WINVER >= 0x0400 */

typedef struct wavehdr_tag { 
    LPSTR  lpData; 
    DWORD  dwBufferLength; 
    DWORD  dwBytesRecorded; 
    DWORD  dwUser; 
    DWORD  dwFlags; 
    DWORD  dwLoops; 
    struct wavehdr_tag * lpNext; 
    DWORD  reserved; 
} WAVEHDR; 

typedef WAVEHDR* LPWAVEHDR;

typedef struct HWAVEOUT__ * HWAVEOUT;
//struct tWAVEFORMATEX;

typedef HWAVEOUT FAR *LPHWAVEOUT;
typedef const WAVEFORMATEX FAR *LPCWAVEFORMATEX;

typedef uint* LPUINT;

/* MMTIME data structure */
typedef struct mmtime_tag
{
	UINT            wType;      /* indicates the contents of the union */
	union
	{
		DWORD       ms;         /* milliseconds */
		DWORD       sample;     /* samples */
		DWORD       cb;         /* byte count */
		DWORD       ticks;      /* ticks in MIDI stream */
		
		/* SMPTE */
		struct
		{
			uint8    hour;       /* hours */
			uint8    min;        /* minutes */
			uint8    sec;        /* seconds */
			uint8    frame;      /* frames  */
			uint8    fps;        /* frames per second */
			uint8    dummy;      /* pad */
#ifdef _WIN32
			uint8    pad[2];
#endif
		} smpte;
		
		/* MIDI */
		struct
		{
			DWORD songptrpos;   /* song pointer position */
		} midi;
	} u;
} MMTIME, *PMMTIME, NEAR *NPMMTIME, FAR *LPMMTIME;

/* types for wType field in MMTIME struct */
#define TIME_MS         0x0001  /* time in milliseconds */
#define TIME_SAMPLES    0x0002  /* number of wave samples */
#define TIME_BYTES      0x0004  /* current byte offset */
#define TIME_SMPTE      0x0008  /* SMPTE time */
#define TIME_MIDI       0x0010  /* MIDI time */
#define TIME_TICKS      0x0020  /* Ticks within MIDI stream */

/* flags used with waveOutOpen(), waveInOpen(), midiInOpen(), and */
/* midiOutOpen() to specify the type of the dwCallback parameter. */

#define CALLBACK_TYPEMASK   0x00070000l    /* callback type mask */
#define CALLBACK_NULL       0x00000000l    /* no callback */
#define CALLBACK_WINDOW     0x00010000l    /* dwCallback is a HWND */
#define CALLBACK_TASK       0x00020000l    /* dwCallback is a HTASK */
#define CALLBACK_FUNCTION   0x00030000l    /* dwCallback is a FARPROC */
#ifdef _WIN32
#define CALLBACK_THREAD     (CALLBACK_TASK)/* thread ID replaces 16 bit task */
#define CALLBACK_EVENT      0x00050000l    /* dwCallback is an EVENT Handle */
#endif

#define MAXERRORLENGTH   256    /* max error text length (including NULL) */

WINMMAPI MMRESULT WINAPI waveOutOpen( OUT LPHWAVEOUT phwo, IN UINT uDeviceID,
    IN LPCWAVEFORMATEX pwfx, IN DWORD_PTR dwCallback, IN DWORD_PTR dwInstance, IN DWORD fdwOpen);

WINMMAPI MMRESULT WINAPI waveOutClose( IN OUT HWAVEOUT hwo);
WINMMAPI MMRESULT WINAPI waveOutPrepareHeader( IN HWAVEOUT hwo, IN OUT LPWAVEHDR pwh, IN UINT cbwh);
WINMMAPI MMRESULT WINAPI waveOutUnprepareHeader( IN HWAVEOUT hwo, IN OUT LPWAVEHDR pwh, IN UINT cbwh);
WINMMAPI MMRESULT WINAPI waveOutWrite( IN HWAVEOUT hwo, IN OUT LPWAVEHDR pwh, IN UINT cbwh);
WINMMAPI MMRESULT WINAPI waveOutPause( IN HWAVEOUT hwo);
WINMMAPI MMRESULT WINAPI waveOutRestart( IN HWAVEOUT hwo);
WINMMAPI MMRESULT WINAPI waveOutReset( IN HWAVEOUT hwo);
WINMMAPI MMRESULT WINAPI waveOutBreakLoop( IN HWAVEOUT hwo);
WINMMAPI MMRESULT WINAPI waveOutGetPosition( IN HWAVEOUT hwo, IN OUT LPMMTIME pmmt, IN UINT cbmmt);
WINMMAPI MMRESULT WINAPI waveOutGetPitch( IN HWAVEOUT hwo, OUT LPDWORD pdwPitch);
WINMMAPI MMRESULT WINAPI waveOutSetPitch( IN HWAVEOUT hwo, IN DWORD dwPitch);
WINMMAPI MMRESULT WINAPI waveOutGetPlaybackRate( IN HWAVEOUT hwo, OUT LPDWORD pdwRate);
WINMMAPI MMRESULT WINAPI waveOutSetPlaybackRate( IN HWAVEOUT hwo, IN DWORD dwRate);
WINMMAPI MMRESULT WINAPI waveOutGetID( IN HWAVEOUT hwo, OUT LPUINT puDeviceID);
WINMMAPI MMRESULT WINAPI waveOutGetErrorTextA( IN MMRESULT mmrError, OUT LPSTR pszText, IN UINT cchText);

}	// MSWindows
}	// System

#ifdef __cplusplus
}
#endif
