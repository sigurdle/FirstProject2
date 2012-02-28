#ifndef TTDebuggerFrame_h
#define TTDebuggerFrame_h

namespace System
{

class GlyphPreview;
class TTInstructionsControl;
class TTDebuggerFrame;
class FontInstructions;

typedef void (FontInstructions::*tyttfunc)();

class TTInstruction : public System::Object
{
public:

	CTOR TTInstruction()
	{
		m_name = NULL;
	//	m_args = NULL;
	}

	System::StringA* m_name;
//	System::StringA* args;
	int m_level;
	uint16 m_offset;
};

/*
class TTBreakpoint
{
public:
	TTBreakpoint(uint8 oldbyte)
	{
		m_oldbyte = oldbyte;
	}
	uint8 m_oldbyte;
};
*/

// TODO, oldword ?
typedef map<uint8*, uint8/*oldbyte*/> ttbreakpointaddrmap_t;

class TTBreakpoints : public System::Object
{
public:
	ttbreakpointaddrmap_t m_breakpoints;
};

class GlyphPreview : public UI::FrameworkElement
{
public:
	CTOR GlyphPreview(TTDebuggerFrame* pFrame);

	TTDebuggerFrame* m_pFrame;

protected:

	virtual void OnRender(UI::Graphics* pGraphics);
	virtual void OnMouseMove(UI::MouseEventArgs* args);
};

class TTInstructionsControl : public UI::Control//FrameworkElement
{
public:
	CTOR TTInstructionsControl();

	void Update();

	LDraw::Font* GetFont()
	{
		return UI::Control::GetFont(this);
	}

	TTBreakpoints* m_frame;
	FontInstructions* m_instructions;
	UI::ScrollViewer* m_pScroller;

protected:

	virtual void OnRender(UI::Graphics* pGraphics);
	virtual LDraw::SizeD MeasureOverride(LDraw::SizeD availSize);
};

typedef map<uint16, bool> ttbreakpointmap_t;

class FontInstructions : public System::Object
{
public:

	CTOR FontInstructions(uint8* start, uint16 length)
	{
		m_iflevel = 0;
		m_start = start;
		m_length = length;
		pc = m_start;
	}

	int m_iflevel;

	uint16 m_length;
	uint8* m_start;
	uint8* pc;
	/*
	struct Caller
	{
		Caller()
		{
			pCaller = NULL;
		}
		Caller* pCaller;
		uint8* instructions;
		uint32 instructionLength;
		uint8* return_pc;
	};
	*/

//	void callfun(TTFun* f);

	void next();

	static tyttfunc ttfuncs[256];

	void TTInstr(System::StringA* name)
	{
		TTInstruction* tti = new TTInstruction;
		tti->m_name = name;
		tti->m_level = m_iflevel;
		tti->m_offset = pc - m_start;

		m_instructions.Add(tti);
	}

	vector<TTInstruction*> m_instructions;
	ttbreakpointmap_t m_breakpoints;

protected:

	void tt_notimpl();
	void tt_gpv();
	void tt_sfvtpv();
	void tt_sdpvtl();
	void tt_alignrp();
	void tt_jmpr();
	void tt_jrof();
	void tt_sdb();
	void tt_wcvtp();
	void tt_mppem();
	void tt_npushb();
	void tt_npushw();
	void tt_pushb();
	void tt_pushw();
	void tt_pop();
	void tt_spvtl();
	void tt_sfvtl();
	void tt_sfvtca();
	void tt_svtca();
	void tt_spvfs();
	void tt_spvtca();
	void tt_scanctrl();
	void tt_call();
	void tt_loopcall();
	void tt_fdef();
	void tt_endf();
	void tt_gteq();
	void tt_lteq();
	void tt_eq();
	void tt_lt();
	void tt_gt();
	void tt_and();
	void tt_or();
	void tt_div();
	void tt_mul();
	void tt_add();
	void tt_sub();
	void tt_max();
	void tt_min();
	void tt_swap();
	void tt_ws();
	void tt_rs();
	void tt_abs();
	void tt_fliprgon();
	void tt_rtg();
	void tt_rthg();
	void tt_rdtg();
	void tt_rtdg();
	void tt_mdrp();
	void tt_msirp();
	void tt_mirp();
	void tt_if();
	void tt_rcvt();
	void tt_md();
	void tt_gc();
	void tt_dup();
	void tt_cindex();
	void tt_mindex();
	void tt_roll();
	void tt_smd();
	void tt_scfs();
	void tt_isect();
	void tt_wcvtf();
	void tt_srp0();
	void tt_srp1();
	void tt_srp2();
	void tt_szp0();
	void tt_szp1();
	void tt_szp2();
	void tt_szps();
	void tt_else();
	void tt_eif();
	void tt_sfvfs();
	void tt_neg();
	void tt_not();
	void tt_scantype();
	void tt_miap();
	void tt_mdap();
	void tt_ip();
	void tt_iup();
	void tt_scvtci();
	void tt_getinfo();
	void tt_roff();
	void tt_sround();
	void tt_round();
	void tt_instctrl();
	void tt_sloop();
	void tt_flipoff();
	void tt_flipon();
	void tt_deltap1();
	void tt_deltap2();
	void tt_deltap3();
	void tt_deltac1();
	void tt_deltac2();
	void tt_deltac3();
	void tt_shp();
	void tt_shc();
	void tt_shpix();
};

class TTDebuggerFrame : public UI::CLXUIWindow
{
public:
	CTOR TTDebuggerFrame();

	UI::DockPanel* get_InfoWin() const
	{
		return m_infoWin;
	}

public:

	TTBreakpoints* m_breakpoints;
	unsigned int m_nSteps;

protected:

//	virtual void handleEvent(System::Event* evt);

	void OnDebugGo();
	void OnDebugGoBack();
	void OnDebugStepInto();
	void OnDebugStepBack();

	void Update();

private:

	UI::ChildWindowContainer* pCanvas;
	TTInstructionsControl* m_glyphProgramWin;
	TTInstructionsControl* m_fontProgramWin;
	GlyphPreview* m_glyphPreviewWin;
	UI::TreeControl* m_stackWin;
	UI::TreeControl* m_cvtWin;
	UI::DockPanel* m_infoWin;
};

}

#endif // TTDebuggerFrame_h
