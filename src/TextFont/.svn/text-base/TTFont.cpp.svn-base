#include "StdAfx.h"
#include "TextFont.h"

/*
namespace std
{
#include "stdio.h"
#include "stdarg.h"
}
*/

//using namespace std;
//using namespace System;
//using namespace System::IO;

//FILE* fplog;

void flog(const char* str, ...)
{
#if 0//_WINDOWS
	va_list va;
	va_start(va, str);

	if (fplog)
	{
		//fprintffplog, str
		vfprintf(fplog, str, va);
		fflush(fplog);
	}
#endif
}

namespace System
{
namespace LType
{

	//using namespace LDraw;

//#define LOG	ATLTRACE
#define LOG	1? (void)0: flog
//#define LOG	flog

//void AddPath(ScanLine* scanlines, const CRect& bounds, const uint8* types, const PointF* xpts, int ntypes, uint8 bClip);
//void CalculatePathBounds(const uint8* types, const PointF* xpts, int count, double mx[4]);

gm::vector2d rotatePoint(double x, double y, double angle)
{
	double CosVal = cos(angle);
	double SinVal = sin(angle);

	gm::vector2d v = gm::vector2d(x*CosVal - y*SinVal, y*CosVal + x*SinVal);
	if (fabs(v[0]) < 0.000001) v[0] = 0;
	if (fabs(v[1]) < 0.000001) v[1] = 0;
	return v;
}

gm::vector2d rotatePoint(const gm::vector2d& v, double angle)
{
	return rotatePoint(v[0], v[1], angle);
}

gm::PointI projectVec(const gm::PointI& b, const gm::PointI& a)
{
	gm::vector2d B(b.X/64.0, b.Y/64.0);
	gm::vector2d A(a.X/64.0, a.Y/64.0);

	gm::vector2d r((dot(A, B) / dot(A,A)) * A);

	return gm::PointI(r[0]*64, r[1]*64);
}

double angleBetween(const gm::vector2d& _v1, const gm::vector2d& _v2)
{
	gm::vector2d v1 = _v1;
	v1.normalize();

	gm::vector2d v2 = _v2;
	v2.normalize();

	return acos(dot(v1, v2));
}

double GetPositionOfPointAlongVector(const gm::PointF& pt, const gm::PointF& vec)
{
	LDraw::PointF perpendicular = LDraw::PointF(vec.Y, -vec.X);
	vector2f v;
	gm::intersection(pt, pt+perpendicular, LDraw::PointF(0,0), vec, v);
	return v.length();
}

int GetPositionOfPointAlongVector(gm::PointI& pt, gm::PointI& vec)
{
//	return project(pt, vector).X;
	return GetPositionOfPointAlongVector(LDraw::PointF(pt.X/64.0, pt.Y/64.0), LDraw::PointF(vec.X/64.0, vec.Y/64.0)) * 64;
}

#pragma pack(push,1)

struct OTFHeader
{
	ULONG/*Fixed*/ sfntVersion;// 0x00010000 for version 1.0. 
	uint16  numTables;// Number of tables.  
	uint16  searchRange;// (Maximum power of 2 <= numTables) x 16. 
	uint16  entrySelector;// Log2(maximum power of 2 <= numTables). 
	uint16  rangeShift;// NumTables x 16-searchRange. 
};

struct OTFCmapSubTable
{
	uint16 platformID;// Platform identifier 
	uint16 platformSpecificID;// Platform-specific encoding identifier 
	uint32 offset;// Offset of the mapping table 
};

#pragma pack(pop)

OTFTable* TTFontFile::FindTable(uint32 tag) const
{
	tytablemap::const_iterator it = m_tablemap.find(tag);
	if (it != m_tablemap.end())
	{
		return (*it).second;
	}
	else
		return NULL;
}

State::State()
{
	bAutoFlip = true;

	controlValueCutIn = (17*64)/16;//17/16 pixels (F26Dot6)
	minDistance = 64;	// Default	1 pixel
	singleWidthCutIn = 0;

	rp0 = 0;
	rp1 = 0;
	rp2 = 0;

	zp0 = 1;
	zp1 = 1;
	zp2 = 1;

	// x-axis
	freedom.X = 1 * 16384;
	freedom.Y = 0;

	// x-axis
	project.X = 1 * 16384;
	project.Y = 0;

	dualproject.X = 1 * 16384;
	dualproject.Y = 0;

	deltaBase = 9;
	deltaShift = 3;

	roundThreshold = 32;
	roundPhase = 0;
	roundPeriod = 64;
}

int State::round(int n)
{
	int n2;
	
	if (n < 0)
		n2 = -n;
	else
		n2 = n;

	n2 -= roundPhase;
	n2 += (roundThreshold);
	n2 &= ~(roundPeriod-1);
	n2 += roundPhase;

	if (n < 0)
		n2 = -n2;

	return n2;
}

int f2i(double n)
{
	if (n >= 0)
		return (int)(n+0.5);
	else
		return -(int)((-n) + 0.5);
}

#if 0
State defaultGlyphState;
#endif

VM::VM(TTFontFile* pFile, TTFont* pFont)
{
	ASSERT(pFile != NULL);

	m_pFile = pFile;
	m_pFont = pFont;
	m_loop = 1;

	m_iflevel = 0;

	if (pFont)
	{
		gpointsCount[0] = pFile->m_maxp.maxTwilightPoints;
		orgpoints[0] = pFont->m_twilightPoints;
	}
	else
	{
		orgpoints[0] = NULL;
	}
	newpoints[0] = orgpoints[0];
	gpointsCount[1] = 0;

	bpoints[0] = new uint8[m_pFile->m_maxp.maxPoints];
	memset(bpoints[0], 0, m_pFile->m_maxp.maxPoints);
	bpoints[1] = NULL;

	{
#if 0
		flags = new uint8[m_pFile->m_maxp.maxPoints];
		memcpy(flags, glyph2->data.flags, m_pFile->m_maxp.maxPoints);
#endif

		bpoints[1] = new uint8[m_pFile->m_maxp.maxPoints];
		memset(bpoints[1], 0, m_pFile->m_maxp.maxPoints);

	//	orgpoints[1] = new LDraw::PointI[m_fontFile->m_maxp.maxPoints];
	//	memcpy(orgpoints[1], glyph2->data.points, sizeof(LDraw::PointI)*m_fontFile->m_maxp.maxPoints);
	}

	if (m_pFont)
	{
		m_cvt = new FWord[m_pFile->m_cvtSize];
		memcpy(m_cvt, m_pFont->m_cvt, m_pFile->m_cvtSize*sizeof(FWord));
	}
	else
	{
		m_cvt = NULL;
	}

	m_pStorage = new int32[m_pFile->m_maxp.maxStorage];
	if (m_pFont)
	{
		memcpy(m_pStorage, m_pFont->m_pStorage, m_pFile->m_maxp.maxStorage*sizeof(int32));
	}
}

LDraw::PointI& VM::orgpoint(int zone, int p)
{
	ASSERT(zone == 0 || zone == 1);
	ASSERT(p >= 0 && p < gpointsCount[zone]);

	return orgpoints[zone][p];
}

LDraw::PointI& VM::newpoint(int zone, int p)
{
	ASSERT(zone == 0 || zone == 1);
	ASSERT(p >= 0 && p < gpointsCount[zone]);

	return newpoints[zone][p];
}

const LDraw::PointI& VM::get_orgpoint(int zone, int p) const
{
	ASSERT(zone == 0 || zone == 1);
	ASSERT(p >= 0 && p < gpointsCount[zone]);

	return orgpoints[zone][p];
}

const LDraw::PointI& VM::get_newpoint(int zone, int p) const
{
	ASSERT(zone == 0 || zone == 1);
	ASSERT(p >= 0 && p < gpointsCount[zone]);

	return newpoints[zone][p];
}

int32 VM::ReadStorage(uint32 loc)
{
	if (loc < 0 || loc >= m_pFile->m_maxp.maxStorage)
	{
		ASSERT(0);
		THROW(-1);
	}

	return m_pStorage[loc];
}

void VM::WriteStorage(uint32 loc, int32 val)
{
	if (loc < 0 || loc >= m_pFile->m_maxp.maxStorage)
	{
		ASSERT(0);
		THROW(-1);
	}

	m_pStorage[loc] = val;
}

void VM::push(StkElt value)
{
	/*
	if (value == 57)
	{
		LOG("\n");
	}
	*/
	//m_stack.push(value);
	m_stack.Add(value);
}

StkElt VM::pop()
{
	int size = m_stack.GetSize();
	if (size <= 0)
	{
		ASSERT(0);
		THROW(-1);
	}
	StkElt elt = m_stack[m_stack.GetSize()-1];//*(m_stack.end()-1);
//	ASSERT(elt == m_stack[size-1]);
	m_stack.RemoveAt(m_stack.GetSize()-1);
	return elt;
}

void VM::SetPoint(int zone, int npoint, LDraw::PointI point)
{
	if (m_state.freedom.X) bpoints[zone][npoint] |= 1;
	if (m_state.freedom.Y) bpoints[zone][npoint] |= 2;

	newpoints[zone][npoint] = point;
}

/*
class tt_instr
{
public:
	union
	{
	};
};*/

//typedef void (*tyttfunc)(VM* vm);
//extern tyttfunc ttfuncs[];

//int level = 0;

void printlevel()
{
//	ASSERT(level >= 0);

	/*
	for (int i = 0; i < level; i++)
	{
		LOG("  ");
	}
	*/
}

void skip_next(VM* vm)
{
	uint8 code = *vm->pc++;
	switch (code)
	{
	case 0x40:	// npushb
		{
			uint8 n = *vm->pc++;
			vm->pc += n;
		}
		break;

	case 0x41:	// npushw
		{
			uint8 n = *vm->pc++;
			vm->pc += n*2;
		}
		break;

		// pushb[abc]
	case 0xB0:
	case 0xB1:
	case 0xB2:
	case 0xB3:
	case 0xB4:
	case 0xB5:
	case 0xB6:
	case 0xB7:
		{
			uint8 n = code - 0xB0;
			n += 1;
			vm->pc += n;
		}
		break;

		// pushw[abc]
	case 0xB8:
	case 0xB9:
	case 0xBA:
	case 0xBB:
	case 0xBC:
	case 0xBD:
	case 0xBE:
	case 0xBF:
		{
			uint8 n = code - 0xB8;
			n += 1;
			vm->pc += n*2;
		}
		break;

	case 0x89:	// IDEF
		{
			while (1)
			{
				uint8 instr_code = *vm->pc;
				if (instr_code == 0x2D)	// endf
					break;
				skip_next(vm);
			}
			ASSERT(*vm->pc == 0x2D);
			vm->pc++;
		}
		break;

	case 0x2D:	// endf
		{
			ASSERT(0);
		}
		break;

	case 0x1B:	// else
		{
			ASSERT(0);
		}
		break;
	
	case 0x59:	// eif
		{
			ASSERT(0);
		}
		break;

	case 0x58:	// if
		{
			printlevel();
			LOG("if");
		//	level++;
			while (1)
			{
				uint8 instr_code = *vm->pc;
				if (instr_code == 0x59)	// eif
					break;

				if (instr_code == 0x1B)	// else
				{
					vm->pc++;
					while (1)
					{
						uint8 instr_code = *vm->pc;
						if (instr_code == 0x59)	// eif
							break;

						skip_next(vm);
					}

					ASSERT(*vm->pc == 0x59);	// eif
					break;
				}
				skip_next(vm);
			}

			ASSERT(*vm->pc == 0x59);	// eif
			vm->pc++;

//			level--;
			printlevel();
			LOG("eif");
		}
		break;
	}
}

void VM::tt_notimpl()
{
	LOG("unkown: %d - %x", (uint8)*pc, (uint8)*pc);
	pc++;
}

// GPV[] Get Projection Vector
void VM::tt_gpv()
{
	VM* vm = this;

	LOG("gpv");
	vm->pc++;

	LOG(" %d,%d", vm->m_state.project.X, vm->m_state.project.Y);

	// 2.14
	vm->push(vm->m_state.project.X);
	vm->push(vm->m_state.project.Y);
}

// SFVTPV[] Set Freedom Vector To Projection Vector
void VM::tt_sfvtpv()
{
	VM* vm = this;
	vm->pc++;
	vm->m_state.freedom = vm->m_state.project;
	LOG("sfvtpv");
}

// SDPVTL[a] Set Dual Projection Vector To Line
void VM::tt_sdpvtl()
{
	VM* vm = this;
	int a = *vm->pc - 0x86;
	vm->pc++;

	uint32 pi2 = vm->pop();//: point number (uint32)  
	uint32 pi1 = vm->pop();//point number (uint32) 

	vector2d o_p1(vm->orgpoints[vm->m_state.zp1][pi1].X, vm->orgpoints[vm->m_state.zp1][pi1].Y);
	vector2d o_p2(vm->orgpoints[vm->m_state.zp2][pi2].X, vm->orgpoints[vm->m_state.zp2][pi2].Y);
	vector2d n_p1(vm->newpoints[vm->m_state.zp1][pi1].X, vm->newpoints[vm->m_state.zp1][pi1].Y);
	vector2d n_p2(vm->newpoints[vm->m_state.zp2][pi2].X, vm->newpoints[vm->m_state.zp2][pi2].Y);

	vector2d project = n_p2 - n_p1;
	vector2d dualproject = o_p2 - o_p1;

	if (a)	// perpendicular
	{
		project = vector2d(project[1], -project[0]);
		dualproject = vector2d(dualproject[1], -dualproject[0]);
	}
	project.normalize();
	dualproject.normalize();

	// TODO, round to nearest integer
	vm->m_state.project.X = f2i(project[0] * 16384);
	vm->m_state.project.Y = f2i(project[1] * 16384);
	vm->m_state.dualproject.X = f2i(dualproject[0] * 16384);
	vm->m_state.dualproject.Y = f2i(dualproject[1] * 16384);

	LOG("Set Dual Projection Vector To Line [%s] (%.2f,%.2f), (%.2f,%.2f)", a? "perpendicular": "parallel", dualproject[0], dualproject[1], project[0], project[1]);
}

// ALIGNRP[] ALIGN to Reference PointI
void VM::tt_alignrp()
{
	VM* vm = this;
	vm->pc++;

	LOG("ALIGNRP");

	if (vm->m_state.zp1 == 1)
	{
//		LOG("Zone1\n");
	}

	if (vm->m_state.zp0 == 1)
	{
	//	LOG("Zone1\n");
	}

	vector2d project(vm->m_state.project.X, vm->m_state.project.Y);
	double angle;// = angleBetween(gmVector2(1, 0), project);
	angle = LDraw::GetLineAngleRadians(0, 0, project[0], project[1]);

	vector2d freedom(vm->m_state.freedom.X, vm->m_state.freedom.Y);
	freedom.normalize();
	freedom = rotatePoint(freedom, -angle);
	ASSERT(fabs(freedom.length() - 1) < 0.00001);

	vector2d rp0 = rotatePoint(vm->newpoints[vm->m_state.zp0][vm->m_state.rp0].X, vm->newpoints[vm->m_state.zp0][vm->m_state.rp0].Y, -angle);

	LOG(" %d", vm->m_state.rp0);

	for (int i = 0; i < vm->m_loop; i++)
	{
		uint32 pi = vm->pop(); //point to be shifted (uint32)  

		if (pi < 0 || pi >= vm->gpointsCount[vm->m_state.zp1])
		{
			ASSERT(0);
			THROW(-1);
		}

		vector2d p = rotatePoint(vm->newpoints[vm->m_state.zp1][pi].X, vm->newpoints[vm->m_state.zp1][pi].Y, -angle);

		double dx = rp0[0] - p[0];
		double dy = freedom[1]/freedom[0] * dx;
		vector2d newpt(p[0] + dx, p[1] + dy);

		newpt = rotatePoint(newpt, angle);

		//if (vm->m_state.project.X == 1)
		{
			/*
			if (vm->m_state.project.X) vm->bpoints[vm->m_state.zp1][pi] |= 1;
			if (vm->m_state.project.Y) vm->bpoints[vm->m_state.zp1][pi] |= 2;

			vm->newpoints[vm->m_state.zp1][pi].X = newpt[0]+0.5;
			vm->newpoints[vm->m_state.zp1][pi].Y = newpt[1]+0.5;
			*/
			SetPoint(m_state.zp1, pi, LDraw::PointI(newpt[0]+0.5, newpt[1]+0.5));

			LOG(" p=%d (%.2f,%.2f)", pi, newpt[0]/64, newpt[1]/64);
		}

		//	vm->orgpoints[vm->m_state.zp0][p].X += freedom[0] * d;
	//	vm->orgpoints[vm->m_state.zp0][p].Y += freedom[1] * d;
	//	LOG("%d, ", p);
	}
	vm->m_loop = 1;
}

// JMPR[] JuMP Relative
void VM::tt_jmpr()
{
	VM* vm = this;
	LOG("jmpr");
	int32 offset = vm->pop();
	vm->pc += offset;
}

// JROF[] Jump Relative On False
void VM::tt_jrof()
{
	VM* vm = this;
	LOG("jrof");
	int e = vm->pop();
	int32 offset = vm->pop();
	if (!e)
	{
		vm->pc += offset;
	}
	else
	{
		vm->pc++;
	}
}

// SDB[] Set Delta Base in the graphics state
void VM::tt_sdb()
{
	VM* vm = this;
	vm->pc++;

	uint32 n = vm->pop();//: value for the delta base (uint32) 

	vm->m_state.deltaBase = n;

	LOG("sdb %d", n);
}

// WCVTP[] Write Control Value Table in Pixel units
void VM::tt_wcvtp()
{
	VM* vm = this;
	vm->pc++;
	LOG("Write Control Value Table in Pixel units");

	F26Dot6 val = vm->pop();	// value in pixels (F26Dot6) 
	uint32 loc = vm->pop();	// control value table location (uint32) 

	if (loc < 0 || loc >= vm->m_pFile->m_cvtSize)
	{
		ASSERT(0);
		THROW(-1);
	}

	LOG(" %d=%d", loc, val);

	vm->m_cvt[loc] = val;//(int)(val * (int)(vm->m_pFont->m_emSize*64) / vm->m_pFont->m_unitsPerEm);
//	vm->m_pFont->m_cvtUnit[loc] = 1;
}

//MPPEM[] Measure Pixels Per EM
void VM::tt_mppem()
{
	VM* vm = this;
	vm->pc++;

	Euint16 ppem = (int)vm->m_pFont->m_emSize;//*64;

	vm->push(ppem);
	LOG("mppem %d", ppem);
}

void VM::tt_npushb()
{
	VM* vm = this;
	LOG("npushb");
	vm->pc++;

	uint8 n = *vm->pc++;
	while (n > 0)
	{
		uint8 value = *vm->pc++;

		LOG(" %d", value);

		vm->push(value);
		n--;
	}
}

void VM::tt_npushw()
{
	VM* vm = this;
	LOG("npushw");
	vm->pc++;

	uint8 n = *vm->pc++;
	while (n > 0)
	{
		int16 value = (int)vm->pc[0]<<8 | vm->pc[1];

		LOG(" %d", value);

		vm->pc += 2;
		vm->push(value);
		n--;
	}
}

void VM::tt_pushb()
{
	VM* vm = this;
	LOG("pushb");
	uint8 n = *vm->pc - 0xB0;
	vm->pc++;
	n += 1;
	while (n > 0)
	{
		LOG(" %d", *vm->pc);

		vm->push((uint8)*vm->pc++);
		n--;
	}
}

void VM::tt_pushw()
{
	VM* vm = this;
	LOG("pushw");
	uint8 n = *vm->pc - 0xB8;
	vm->pc++;
	n += 1;
	while (n > 0)
	{
		int16 value = (int)vm->pc[0]<<8 | vm->pc[1];

		LOG(" %d", value);

		vm->pc += 2;
		vm->push(value);
		n--;
	}
}

// POP[] POP top stack element
void VM::tt_pop()
{
	VM* vm = this;
	LOG("pop");
	vm->pc++;
	vm->pop();
}

// SPVTL[a] Set Projection Vector To Line
void VM::tt_spvtl()
{
	VM* vm = this;
	uint a = *vm->pc - 0x6;
	vm->pc++;

	uint32 pi2 = vm->pop();
	uint32 pi1 = vm->pop();

	LOG("Set Projection Vector To Line %s p1=%d p2=%d", a?"[perpendicular]": "", pi1, pi2);

	if (pi1 < 0 || pi1 >= vm->gpointsCount[vm->m_state.zp1])
	{
		ASSERT(0);
		THROW(-1);
	}

	if (pi2 < 0 || pi2 >= vm->gpointsCount[vm->m_state.zp2])
	{
		ASSERT(0);
		THROW(-1);
	}

	vector2d p1 = vector2d(vm->newpoints[vm->m_state.zp1][pi1].X, vm->newpoints[vm->m_state.zp1][pi1].Y);
	vector2d p2 = vector2d(vm->newpoints[vm->m_state.zp2][pi2].X, vm->newpoints[vm->m_state.zp2][pi2].Y);

	vector2d project = p2 - p1;

	if (a)
	{
		project = vector2d(project[1], -project[0]);
	}
	project.normalize();

	vm->m_state.project.X = project[0] * 16384;
	vm->m_state.project.Y = project[1] * 16384;

	vm->m_state.dualproject = vm->m_state.project;

	LOG(" (%.4f,%.4f)", project[0], project[1]);
}

// SFVTL[a] Set Freedom Vector To Line
void VM::tt_sfvtl()
{
	VM* vm = this;
	uint a = *vm->pc - 0x8;
	vm->pc++;

	uint32 pi2 = vm->pop();
	uint32 pi1 = vm->pop();

	if (pi1 < 0 || pi1 >= vm->gpointsCount[vm->m_state.zp1])
	{
		ASSERT(0);
		THROW(-1);
	}

	if (pi2 < 0 || pi2 >= vm->gpointsCount[vm->m_state.zp2])
	{
		ASSERT(0);
		THROW(-1);
	}

	LOG("Set Freedom Vector To Line %s p1=%d p2=%d", a?"[perpendicular]": "", pi1, pi2);

	vector2d p1 = vector2d(vm->newpoints[vm->m_state.zp1][pi1].X, vm->newpoints[vm->m_state.zp1][pi1].Y);
	vector2d p2 = vector2d(vm->newpoints[vm->m_state.zp2][pi2].X, vm->newpoints[vm->m_state.zp2][pi2].Y);

	vector2d freedom = p2 - p1;

	if (a)
	{
		freedom = vector2d(freedom[1], -freedom[0]);
	}
	freedom.normalize();

	vm->m_state.freedom.X = freedom[0] * 16384;
	vm->m_state.freedom.Y = freedom[1] * 16384;

	LOG(" (%.4f,%.4f)", freedom[0], freedom[1]);
}

// SFVTCA[a] Set Freedom Vector to Coordinate Axis
void VM::tt_sfvtca()
{
	VM* vm = this;
	uint8 a = *vm->pc - 0x4;
	vm->pc++;

	LOG("Set Freedom Vector to Coordinate Axis ");

	if (a == 0)	// y-axis
	{
		LOG("y-axis");

		vm->m_state.freedom.X = 0;
		vm->m_state.freedom.Y = 1 * 16384;
	}
	else	// x-axis
	{
		LOG("x-axis");

		vm->m_state.freedom.X = 1 * 16384;
		vm->m_state.freedom.Y = 0;
	}
}

// SVTCA[a] Set freedom and projection Vectors To Coordinate Axis
void VM::tt_svtca()
{
	VM* vm = this;
	uint8 a = *vm->pc - 0x0;
	vm->pc++;

	LOG("svtca ");

	if (a == 0)	// y-axis
	{
		LOG("y-axis");

		vm->m_state.freedom.X = 0;
		vm->m_state.freedom.Y = 1 * 16384;

		vm->m_state.project.X = 0;
		vm->m_state.project.Y = 1 * 16384;

		vm->m_state.dualproject.X = 0;
		vm->m_state.dualproject.Y = 1 * 16384;
	}
	else	// x-axis
	{
		LOG("x-axis");

		vm->m_state.freedom.X = 1 * 16384;
		vm->m_state.freedom.Y = 0;

		vm->m_state.project.X = 1 * 16384;
		vm->m_state.project.Y = 0;

		vm->m_state.dualproject.X = 1 * 16384;
		vm->m_state.dualproject.Y = 0;
	}
}

// SPVFS[] Set Projection Vector From Stack
void VM::tt_spvfs()
{
	VM* vm = this;
	vm->pc++;

	LOG("Set Projection Vector From Stack");

	vm->m_state.project.Y = vm->pop();
	vm->m_state.project.X = vm->pop();
//	ASSERT((vm->m_state.project.X*2 + vm->m_state.project.Y*2) == 0x4000);

	vm->m_state.dualproject = vm->m_state.project;
}

// Set Projection Vector To Coordinate Axis
void VM::tt_spvtca()
{
	VM* vm = this;
	uint8 a = *vm->pc - 0x02;
	vm->pc++;
	LOG("spvtca");

	if (a == 0)	// y-axis
	{
		vm->m_state.project.X = 0;
		vm->m_state.project.Y = 1 * 16384;

		vm->m_state.dualproject.X = 0;
		vm->m_state.dualproject.Y = 1 * 16384;
	}
	else	// x-axis
	{
		vm->m_state.project.X = 1 * 16384;
		vm->m_state.project.Y = 0;

		vm->m_state.dualproject.X = 1 * 16384;
		vm->m_state.dualproject.Y = 0;
	}
}

// SCANCTRL[] SCAN conversion ConTRoL
void VM::tt_scanctrl()
{
	VM* vm = this;
	vm->pc++;
	long n = vm->pop();

	// TODO
	LOG("scanctrl");
}

void VM::callfun(TTFun* f)
{
	/*
	uint8* pc = vm->pc;
	vm->pc = f->m_data;

	while (vm->pc - f->m_data < f->m_size)
	{
		uint8 instr_code = *vm->pc;
		printlevel();
		ttfuncs[instr_code](vm);
		LOG("\n");
	}
	level--;
	printlevel();
	LOG("}");
	vm->pc = pc;
	*/

	VM::Caller* ctx = new Caller;
	ctx->pCaller = m_ctx;
	ctx->return_pc = pc;
	ctx->instructionsData = f->m_data;
	ctx->instructionsLength = f->m_size;
	pc = ctx->instructionsData;
	m_ctx = ctx;
}

void VM::tt_call()
{
	VM* vm = this;
	vm->pc++;

	uint32 f = vm->pop();
	LOG("call %d\n", f);
//	level++;

	tyfunmap::iterator funti = vm->m_pFile->m_functions.find(f);
	if (funti != vm->m_pFile->m_functions.end())
	{
		callfun((*funti).second);
	}
	else
	{
		LOG("Calling undefined function %d\n", f);

		ASSERT(0);
		THROW(-1);
	}
}

// LOOPCALL[] LOOP and CALL function
void VM::tt_loopcall()
{
	VM* vm = this;
	vm->pc++;

	uint32 f = vm->pop();
	uint16 count = vm->pop();

	tyfunmap::iterator funti = vm->m_pFile->m_functions.find(f);
	if (funti != vm->m_pFile->m_functions.end())
	{
		for (int i = 0; i < count; i++)
		{
			LOG("call %d\n", f);
		//	level++;
			callfun((*funti).second);
		}
	}
	else
	{
		LOG("Calling undefined function %d\n", f);
		ASSERT(0);
		THROW(-1);
	}
}

void VM::tt_fdef()
{
	VM* vm = this;
	vm->pc++;

	if (vm->m_pFile->m_functions.size() >= vm->m_pFile->m_maxp.maxFunctionDefs)
	{
		LOG("number of fdefs exceed number specified in maxp table");
		ASSERT(0);
		THROW(-1);
	}

	uint32 f = vm->pop();

	LOG("fdef %d", f);

	TTFun* pFun = new TTFun;
	pFun->m_data = vm->pc;

	vm->m_pFile->m_functions.insert(tyfunmap::value_type(f, pFun));

	while (1)
	{
		uint8 instr_code = *vm->pc;
		if (instr_code == 0x2D)	// endf
			break;
		
		skip_next(vm);
	}
	pFun->m_size = vm->pc - pFun->m_data;

	ASSERT(*vm->pc == 0x2D);
	vm->pc++;
}

void VM::tt_endf()
{
	VM* vm = this;
	LOG("endf");
	vm->pc++;
}

// GTEQ[] Greater Than or EQual
void VM::tt_gteq()
{
	VM* vm = this;
	LOG("gteq");
	vm->pc++;

	int32 e2 = vm->pop();
	int32 e1 = vm->pop();

	LOG(" %d >= %d", e1, e2);

	if (e1 >= e2)
		vm->push(1);
	else
		vm->push(0);
}

// LTEQ[] Less Than or EQual
void VM::tt_lteq()
{
	VM* vm = this;
	vm->pc++;

	int32 e2 = vm->pop();
	int32 e1 = vm->pop();

	LOG("lteq %d <= %d = %d", e1, e2, e1 <= e2);

	if (e1 <= e2)
		vm->push(1);
	else
		vm->push(0);
}

// EQ[] EQual
void VM::tt_eq()
{
	VM* vm = this;
	LOG("eq");
	vm->pc++;

	int32 e2 = vm->pop();
	int32 e1 = vm->pop();

	LOG(" %d == %d", e1, e2);

	vm->push(e1 == e2);
}

// NEQ[] NEQual
void VM::tt_neq()
{
	VM* vm = this;
	LOG("neq");
	vm->pc++;

	int32 e2 = vm->pop();
	int32 e1 = vm->pop();

	LOG(" %d != %d", e1, e2);

	vm->push(e1 != e2);
}

// LT[] Less Than
void VM::tt_lt()
{
	VM* vm = this;
	LOG("lt");
	vm->pc++;

	int32 e2 = vm->pop();
	int32 e1 = vm->pop();

	if (e1 < e2)
		vm->push(1);
	else
		vm->push(0);
}

// GT[] Greater Than
void VM::tt_gt()
{
	VM* vm = this;
	LOG("gt");
	vm->pc++;

	int32 e2 = vm->pop();
	int32 e1 = vm->pop();

	LOG(" %d > %d", e1, e2);

	if (e1 > e2)
		vm->push(1);
	else
		vm->push(0);
}

// AND[] logical AND
void VM::tt_and()
{
	VM* vm = this;
	LOG("and");
	vm->pc++;

	StkElt e2 = vm->pop();
	StkElt e1 = vm->pop();

	LOG(" %d && %d", e1, e2);

	vm->push(e1 && e2);
}

// OR[] logical OR
void VM::tt_or()
{
	VM* vm = this;
	LOG("or");
	vm->pc++;

	StkElt e2 = vm->pop();
	StkElt e1 = vm->pop();

	LOG(" %d || %d", e1, e2);

	vm->push(e1 || e2);
}

// DIV[] DIVide
void VM::tt_div()
{
	VM* vm = this;
	LOG("div");
	vm->pc++;

	int32 e2 = vm->pop();
	int32 e1 = vm->pop();

	LOG(" %d / %d", e1, e2);

	if (e2 == 0)
	{
		ASSERT(0);
		THROW(-1);
	}
	else
	{
		LOG("= %d", (e1*64)/e2);

		vm->push(((LONGLONG)e1*64) / e2);
	}
}

// MUL[] MULtiply
void VM::tt_mul()
{
	VM* vm = this;
	vm->pc++;

	int32 e2 = vm->pop();
	int32 e1 = vm->pop();

	vm->push((LONGLONG)e1*e2 / 64);

	LOG("mul %d*%d=%d", e1, e2, (int)((LONGLONG)e1*e2 / 64));
}

// ADD[] ADD
void VM::tt_add()
{
	VM* vm = this;
	vm->pc++;

	int32 e2 = vm->pop();
	int32 e1 = vm->pop();

	vm->push(e1 + e2);

	LOG("add %d+%d=%d", e1, e2, e1+e2);
}

// SUB[] SUBtract
void VM::tt_sub()
{
	VM* vm = this;
	LOG("sub");
	vm->pc++;

	int32 e2 = vm->pop();
	int32 e1 = vm->pop();

	LOG(" %d-%d=%d", e1, e2, e1-e2);

	vm->push(e1 - e2);
}

// MAX[] MAXimum of top two stack elements
void VM::tt_max()
{
	VM* vm = this;
	LOG("max");
	vm->pc++;

	int32 e2 = vm->pop();
	int32 e1 = vm->pop();

	LOG(" %d,%d", e1, e2);

	vm->push(MAX(e1, e2));
}

// MIN[] MINimum of top two stack elements
void VM::tt_min()
{
	VM* vm = this;
	LOG("min");
	vm->pc++;

	int32 e2 = vm->pop();
	int32 e1 = vm->pop();

	LOG(" %d,%d", e1, e2);

	vm->push(MIN(e1, e2));
}

// SWAP[] SWAP the top two elements on the stack
void VM::tt_swap()
{
	VM* vm = this;
	LOG("swap");
	vm->pc++;

	StkElt e2 = vm->pop();
	StkElt e1 = vm->pop();

	vm->push(e2);
	vm->push(e1);
}

// WS[] Write Store
void VM::tt_ws()
{
	VM* vm = this;
	vm->pc++;

	uint32 val = vm->pop();
	uint32 loc = vm->pop();

	vm->WriteStorage(loc, val);

	LOG("ws %d=%d", loc, val);
}

// RS[] Read Store
void VM::tt_rs()
{
	VM* vm = this;
	vm->pc++;

	int32 loc = vm->pop();
	int val = vm->ReadStorage(loc);

	LOG("rs loc=%d val=%d", loc, val);

	vm->push(val);
}

// ABS[] ABSolute value
void VM::tt_abs()
{
	VM* vm = this;
	vm->pc++;

	int32 val = vm->pop();
	vm->push(val < 0? -val: val);
	LOG("abs");
}

// FLIPRGON[] FLIP RanGe ON
void VM::tt_fliprgon()
{
	VM* vm = this;
	vm->pc++;

	LOG("Flip Range On");
	uint32 high = vm->pop();
	uint32 low = vm->pop();

	if (low < 0)
	{
		ASSERT(0);
		THROW(-1);
	}
	if (high >= vm->m_pFile->m_maxp.maxPoints)
	{
		ASSERT(0);
		THROW(-1);
	}

	for (int i = low; i <= high; i++)
	{
		vm->flags[i] |= 1;
	}
}

// RTG[] Round To Grid
void VM::tt_rtg()
{
	VM* vm = this;
	vm->pc++;

	LOG("rtg");

	vm->m_state.roundPhase = 0;
	vm->m_state.roundPeriod = 64;
	vm->m_state.roundThreshold = 32;
//Pops  -  
//Pushes  -
}

// RTHG[] Round To Half Grid
void VM::tt_rthg()
{
	VM* vm = this;
	vm->pc++;

	vm->m_state.roundPhase = 32;
	vm->m_state.roundPeriod = 64;
	vm->m_state.roundThreshold = 32;

	LOG("rthg");
}

// RUTG[] Round Up To Grid
void VM::tt_rutg()
{
	VM* vm = this;
	vm->pc++;

	vm->m_state.roundPhase = 0;
	vm->m_state.roundPeriod = 64;
	vm->m_state.roundThreshold = 63;

	LOG("rutg");
}

// RDTG[] Round Down To Grid
void VM::tt_rdtg()
{
	VM* vm = this;
	vm->pc++;

	vm->m_state.roundPhase = 0;
	vm->m_state.roundPeriod = 64;
	vm->m_state.roundThreshold = 0;

	LOG("rdtg");
}

// RTDG[] Round To Double Grid
void VM::tt_rtdg()
{
	VM* vm = this;
	vm->pc++;

	vm->m_state.roundPhase = 0;
	vm->m_state.roundPeriod = 32;
	vm->m_state.roundThreshold = 16;

	LOG("rtdg");

//Pops  -  
//Pushes  -
}

// MDRP[abcde] Move Direct Relative PointI
void VM::tt_mdrp()
{
	VM* vm = this;
	int a = (*vm->pc) & 16;
	int b = ((*vm->pc)>>3) & 1;
	int c = ((*vm->pc)>>2) & 1;
	int de = (*vm->pc) & 3;

	vm->pc++;

	uint32 pi = vm->pop();

	if (pi < 0 || pi >= vm->gpointsCount[vm->m_state.zp1])
	{
		ASSERT(0);
		THROW(-1);
	}

	vector2d project(vm->m_state.project.X, vm->m_state.project.Y);

//	double angle = angleBetween(gmVector2(1, 0), project);
	double angle = LDraw::GetLineAngleRadians(0, 0, project[0], project[1]);

	double len = project.length();

	/*
	{
		gmVector2 p1(208, 40);
		gmVector2 p2(30, 87);

		int dist = rotatePoint(p2 - p1, 1.12)[0];
		
		gmVector2 p1_ = rotatePoint(p1, 1.12);
		gmVector2 p2_ = rotatePoint(p2, 1.12);
		int dist2 = p2_[0] - p1_[0];
	}
	*/

	vector2d project2(vm->m_state.dualproject.X, vm->m_state.dualproject.Y);
	double angle2 = LDraw::GetLineAngleRadians(0, 0, project2[0], project2[1]);
//	double angle2 = angleBetween(gmVector2(1, 0), project2);

	double len2 = project2.length();

	vector2d freedom(vm->m_state.freedom.X, vm->m_state.freedom.Y);

	freedom.normalize();
	freedom = rotatePoint(freedom, -angle);
	ASSERT(fabs(freedom.length() - 1) < 0.00001);
	ASSERT(freedom[0] != 0);

	int org_dist2 = rotatePoint(vm->orgpoints[vm->m_state.zp1][pi].X - vm->orgpoints[vm->m_state.zp0][vm->m_state.rp0].X, vm->orgpoints[vm->m_state.zp1][pi].Y - vm->orgpoints[vm->m_state.zp0][vm->m_state.rp0].Y, -angle2)[0];

//	int dist = rotatePoint(vm->orgpoints[vm->m_state.zp1][pi].X - vm->orgpoints[vm->m_state.zp0][vm->m_state.rp0].X, vm->orgpoints[vm->m_state.zp1][pi].Y - vm->orgpoints[vm->m_state.zp0][vm->m_state.rp0].Y, -angle2)[0];

	int distance;

	if (c)
	{
		distance = vm->m_state.round(org_dist2);
	}
	else
	{
		distance = org_dist2;
	}

#if 0
	/*
	gmVector2 rp0_org = rotatePoint(vm->orgpoints[vm->m_state.zp0][vm->m_state.rp0].X, vm->orgpoints[vm->m_state.zp0][vm->m_state.rp0].Y, -angle2);
	gmVector2 p_org = rotatePoint(vm->orgpoints[vm->m_state.zp1][pi].X, vm->orgpoints[vm->m_state.zp1][pi].Y, -angle2);

	gmVector2 rp0 = rotatePoint(vm->newpoints[vm->m_state.zp0][vm->m_state.rp0].X, vm->newpoints[vm->m_state.zp0][vm->m_state.rp0].Y, -angle);
	gmVector2 p = rotatePoint(vm->newpoints[vm->m_state.zp1][pi].X, vm->newpoints[vm->m_state.zp1][pi].Y, -angle);

	double distance = (p_org[0] - rp0_org[0]);
	if (c)
	{
		distance = vm->m_state.round(distance);
	}
//	int newx = (p_org[0] + (rp0[0] - rp0_org[0]));
//	int newx = (p_org[0] - rp0_org[0] + rp0[0]);
	int newx = rp0[0] + distance;//(p_org[0] + distance);
	if (c)
	{
		newx = vm->m_state.round(newx);
	}
	*/

	double dy = freedom[1]/freedom[0] * (newx - p[0]);

	gmVector2 newp(newx, p[1] + dy);

	newp = rotatePoint(newp, angle);
#endif

	int org_dist = rotatePoint(vm->newpoints[vm->m_state.zp1][pi].X - vm->newpoints[vm->m_state.zp0][vm->m_state.rp0].X, vm->newpoints[vm->m_state.zp1][pi].Y - vm->newpoints[vm->m_state.zp0][vm->m_state.rp0].Y, -angle)[0];
	vector2d p = rotatePoint(vm->newpoints[vm->m_state.zp1][pi].X, vm->newpoints[vm->m_state.zp1][pi].Y, -angle);

	int newx = (p[0]) + (distance - org_dist);

	/*
	if (c)
	{
		newx = vm->m_state.round(newx);
	}
	*/

	double dy = freedom[1]/freedom[0] * (newx - p[0]);

	vector2d newp(newx, (p[1]) + dy);
	newp = rotatePoint(newp, angle);

	if (vm->m_state.freedom.X) vm->bpoints[vm->m_state.zp1][pi] |= 1;
	if (vm->m_state.freedom.Y) vm->bpoints[vm->m_state.zp1][pi] |= 2;
	vm->newpoints[vm->m_state.zp1][pi].X = newp[0]+0.5;
	vm->newpoints[vm->m_state.zp1][pi].Y = newp[1]+0.5;

	LOG("mdrp rp0=%d p=%d (%.3f,%.3f)", vm->m_state.rp0, pi, vm->newpoints[vm->m_state.zp1][pi].X / 64.0, vm->newpoints[vm->m_state.zp1][pi].Y / 64.0);

	vm->m_state.rp1 = vm->m_state.rp0;
	vm->m_state.rp2 = pi;
	if (a)
	{
		vm->m_state.rp0 = pi;
	}
}

// MSIRP[a] Move Stack Indirect Relative PointI
void VM::tt_msirp()
{
	VM* vm = this;
	uint8 a = *vm->pc - 0x3A;
	vm->pc++;

	F26Dot6 distance = vm->pop();
	uint32 pi = vm->pop();

	vector2d project(vm->m_state.project.X, vm->m_state.project.Y);
	double angle;// = angleBetween(gmVector2(1, 0), project);
	angle = LDraw::GetLineAngleRadians(0, 0, project[0], project[1]);

	vector2d freedom(vm->m_state.freedom.X, vm->m_state.freedom.Y);
	freedom.normalize();
	freedom = rotatePoint(freedom, -angle);
	ASSERT(freedom.length() == 1);

	if (vm->m_state.rp0 >= vm->gpointsCount[vm->m_state.zp0])
	{
		ASSERT(0);
		THROW(-1);
	}

	if (pi < 0 || pi >= vm->gpointsCount[vm->m_state.zp1])
	{
		ASSERT(0);
		THROW(-1);
	}

	vector2d rp0_org = rotatePoint(vm->orgpoints[vm->m_state.zp0][vm->m_state.rp0].X, vm->orgpoints[vm->m_state.zp0][vm->m_state.rp0].Y, -angle);
	vector2d rp0 = rotatePoint(vm->newpoints[vm->m_state.zp0][vm->m_state.rp0].X, vm->newpoints[vm->m_state.zp0][vm->m_state.rp0].Y, -angle);
	vector2d p_org = rotatePoint(vm->orgpoints[vm->m_state.zp1][pi].X, vm->orgpoints[vm->m_state.zp1][pi].Y, -angle);
	vector2d p = rotatePoint(vm->newpoints[vm->m_state.zp1][pi].X, vm->newpoints[vm->m_state.zp1][pi].Y, -angle);

	int org_dist = p_org[0] - rp0_org[0];//vm->orgpoints[vm->m_state.zp0][pi].X - vm->orgpoints[vm->m_state.zp0][vm->m_state.rp0].X;
	int cur_dist = p[0] - rp0[0];//vm->orgpoints[vm->m_state.zp0][pi].X - vm->orgpoints[vm->m_state.zp0][vm->m_state.rp0].X;

/* auto-flip test */

//#if 0
	//if (pi == 2)
	{
		if (vm->m_state.bAutoFlip)// CUR.GS.auto_flip )
		{
			if ( (org_dist ^ distance) < 0 )
			//if (p[0] < rp0[0])
				distance = -distance;
		}
	}
//#endif

	ASSERT(freedom[0] != 0);

	//double dx = cv - rp0[0];
	int newx = (rp0[0]+distance)/* - p[0]*/;

	int dy = freedom[1]/freedom[0] * (newx - p[0]);

	vector2d newp(newx/*p[0] + dx*/, p[1] + dy);

	newp = rotatePoint(newp, angle);

	if (vm->m_state.freedom.X) vm->bpoints[vm->m_state.zp1][pi] |= 1;
	if (vm->m_state.freedom.Y) vm->bpoints[vm->m_state.zp1][pi] |= 2;
	vm->newpoints[vm->m_state.zp1][pi].X = newp[0]+0.5;
	vm->newpoints[vm->m_state.zp1][pi].Y = newp[1]+0.5;

	if (pi == 3)
	{
		LOG("");
	}

	LOG("msirp dist=%d rp0=%d p=%d X=%d Y=%d - ", distance, vm->m_state.rp0, pi, vm->newpoints[vm->m_state.zp1][pi].X, vm->newpoints[vm->m_state.zp1][pi].Y);

	if (a)
	{
		vm->m_state.rp0 = pi;
	}
}

// MIRP[abcde] Move Indirect Relative PointI
void VM::tt_mirp()
{
	VM* vm = this;
	int a = (*vm->pc) & 16;
	int b = ((*vm->pc)>>3) & 1;
	int c = ((*vm->pc)>>2) & 1;
	int de = (*vm->pc) & 3;

	vm->pc++;
	// TODO

	int n = vm->pop();//: CVT entry number (F26Dot6)
	uint32 pi = vm->pop();//: point number (uint32) 

	if (vm->m_state.project.X == 0)
	{
	//	return;//LOG("");
	}

	if (n < 0 || n >= vm->m_pFile->m_cvtSize)
	{
		ASSERT(0);
		THROW(-1);
	}
	
	F26Dot6 cv = vm->m_cvt[n];
// Moves point p along the freedom vector so that the distance from p to the current position of rp0 is equal to the distance stated in the referenced CVT entry

// single width test
	if (abs(cv) < vm->m_state.singleWidthCutIn)
	{
      if (cv >= 0)
			cv =  vm->m_state.singleWidthCutIn;
      else
			cv = -vm->m_state.singleWidthCutIn;
	}

	/*
	if (vm->m_state.zp1 == 0 )
	{
		vm->orgpoints[pi].X = CUR.zp0.org[CUR.GS.rp0].x +
			TT_MulFix14( cvt_dist, CUR.GS.freeVector.x );
		
		CUR.zp1.org[point].y = CUR.zp0.org[CUR.GS.rp0].y +
			TT_MulFix14( cvt_dist, CUR.GS.freeVector.y );
		
		CUR.zp1.cur[point] = CUR.zp1.org[point];
	}
	*/

	vector2d project(vm->m_state.project.X, vm->m_state.project.Y);
//	double angle = angleBetween(gmVector2(1, 0), project);
//	angle = LDraw::GetLineAngle(0, 0, project[0], project[1]);

	vector2d project2(vm->m_state.project.X, vm->m_state.project.Y);
	//double angle = angleBetween(gmVector2(1, 0), project);
	double angle2 = LDraw::GetLineAngleRadians(0, 0, project2[0], project2[1]);
//	ASSERT(angle2 == angle);

	vector2d freedom(vm->m_state.freedom.X, vm->m_state.freedom.Y);
	freedom.normalize();
	freedom = rotatePoint(freedom, -angle2);
	ASSERT(fabs(freedom.length() - 1) < 0.00001);

	if (vm->m_state.rp0 >= vm->gpointsCount[vm->m_state.zp0])
	{
		ASSERT(0);
		THROW(-1);
	}

	if (pi < 0 || pi >= vm->gpointsCount[vm->m_state.zp1])
	{
		ASSERT(0);
		THROW(-1);
	}

	// TODO, do this in dualproject
	vector2d rp0_org = rotatePoint(vm->orgpoints[vm->m_state.zp0][vm->m_state.rp0].X, vm->orgpoints[vm->m_state.zp0][vm->m_state.rp0].Y, -angle2);
	vector2d rp0 = rotatePoint(vm->newpoints[vm->m_state.zp0][vm->m_state.rp0].X, vm->newpoints[vm->m_state.zp0][vm->m_state.rp0].Y, -angle2);

	// Do this in project
	vector2d p_org = rotatePoint(vm->orgpoints[vm->m_state.zp1][pi].X, vm->orgpoints[vm->m_state.zp1][pi].Y, -angle2);
	vector2d p = rotatePoint(vm->newpoints[vm->m_state.zp1][pi].X, vm->newpoints[vm->m_state.zp1][pi].Y, -angle2);

//	int org_dist = p_org[0] - rp0_org[0];//vm->orgpoints[vm->m_state.zp0][pi].X - vm->orgpoints[vm->m_state.zp0][vm->m_state.rp0].X;
//	int cur_dist = p[0] - rp0[0];//vm->orgpoints[vm->m_state.zp0][pi].X - vm->orgpoints[vm->m_state.zp0][vm->m_state.rp0].X;

	int org_dist;
	int cur_dist;

	{
		vector2d rp0_org = vector2d(vm->orgpoints[vm->m_state.zp0][vm->m_state.rp0].X, vm->orgpoints[vm->m_state.zp0][vm->m_state.rp0].Y);
		vector2d p_org = vector2d(vm->orgpoints[vm->m_state.zp1][pi].X, vm->orgpoints[vm->m_state.zp1][pi].Y);
		vector2d rp0 = vector2d(vm->newpoints[vm->m_state.zp0][vm->m_state.rp0].X, vm->newpoints[vm->m_state.zp0][vm->m_state.rp0].Y);
		vector2d p = vector2d(vm->newpoints[vm->m_state.zp1][pi].X, vm->newpoints[vm->m_state.zp1][pi].Y);

	// Do this in project
		org_dist = rotatePoint(p_org - rp0_org, -angle2)[0];
		cur_dist = rotatePoint(p - rp0, -angle2)[0];
	}

/* auto-flip test */

//#if 0
	//if (pi == 2)
	{
		if (vm->m_state.bAutoFlip)// CUR.GS.auto_flip )
		{
			if ( (org_dist ^ cv) < 0 )	// If the signs are different
			//if (p[0] < rp0[0])
				cv = -cv;
		}
	}
//#endif

//	if (freedom[0] == 0)
//		freedom[0] = 0.00001;
#if 1
	ASSERT(freedom[0] != 0);
#endif

	if (c)
	{
	//	cv = (cv+63) & ~63;
	}

	int distance = vm->m_state.round(cv);

	/*
	if (false)
	{
	if (c)
	{
		distance = vm->m_state.round(distance);
	}
	}
	*/

	if (b)	// use min distance
	{
		if (org_dist >= 0)
		{
			if (distance < vm->m_state.minDistance)
			{
				distance = vm->m_state.minDistance;
			}
		}
		else
		{
			if (distance > -vm->m_state.minDistance)
			{
				distance = -vm->m_state.minDistance;
			}
		}
	}

	/*
	if (c)
	{
		cv = (cv+32) & ~63;
	}
	*/

	//double dx = cv - rp0[0];
//	int newx = p[0] + (distance - cur_dist);//(rp0[0]+ (distance/* - cur_dist*/))/* - p[0]*/;
	int newx = rp0[0] + distance;

//	int newx2 = rp0_org[0] + distance;
	if (c)
	{
//		if ( abs( cv - org_dist ) >= vm->m_state.controlValueCutIn)
  //        cv = org_dist;
#if 0
		newx = vm->m_state.round(newx);
#endif
	}
	/*
	if (c)
	{
		if (newx < 0)
			newx = -(((-newx)+32) & ~63);
		else
			newx = (newx+32) & ~63;
	}
	*/

	double dy = freedom[1]/freedom[0] * (newx - p[0]);

//	int dy2 = freedom[1]/freedom[0] * (newx2 - p[0]);

	vector2d newp(newx, p[1] + dy);
//	gmVector2 newp2(newx2, p[1] + dy2);

	newp = rotatePoint(newp, angle2);
//	newp2 = rotatePoint(newp2, angle2);

//	vm->bpoints[vm->m_state.zp1][pi] |= 3;
	if (vm->m_state.freedom.X) vm->bpoints[vm->m_state.zp1][pi] |= 1;
	if (vm->m_state.freedom.Y) vm->bpoints[vm->m_state.zp1][pi] |= 2;
	vm->newpoints[vm->m_state.zp1][pi].X = newp[0]+0.5;
	vm->newpoints[vm->m_state.zp1][pi].Y = newp[1]+0.5;

	/*** UNDOCUMENTED: when moving a twilight zone point, its original position is changed as well. ***/
	if (vm->m_state.zp1 == 0)
	{
		MessageBeep(-1);
	//	proc.movePointToXY (zp1, p, proc.getPointX (zp0, rp0), proc.getPointY (zp0, rp0));
	//	proc.moveOriginalPointToXY (zp1, p, proc.getPointX (zp0, rp0), proc.getPointY (zp0, rp0));
	//	proc.moveOriginalPoint (zp1, p, rp0Pos + newDist);
	}

	LOG("mirp cv=%d(%d) rp0=%d p=%d (%.2f,%.2f)", cv, n, vm->m_state.rp0, pi, newp[0]/64, newp[1]/64);

	/*
	if (vm->m_state.zp1 == 1)
	{
		LOG("Zone1");
	}
	*/

#if 0
	gmVector2 pt = gmVector2(vm->orgpoints[vm->m_state.zp1][p].X / 64.0, vm->orgpoints[vm->m_state.zp1][p].Y / 64.0);

	gmVector2 project = gmVector2(vm->m_state.project.X, vm->m_state.project.Y);
	gmVector2 freedom = gmVector2(vm->m_state.freedom.X, vm->m_state.freedom.Y);

	gmVector2 tri1;
	intersection(gmVector2(0, 0), gmVector2(vm->m_state.project.X, vm->m_state.project.Y),
		pt, pt + freedom, tri1);

	project.normalize();

	gmVector2 tri2 = -tri1 + project * cv;

	gmVector2 perpendicular = gmVector2(project[1], -project[0]);

	gmVector2 newpt;
	intersection(tri2, tri2+perpendicular, pt, pt+freedom, newpt);

#if 0
	vm->orgpoints[vm->m_state.zp1][p].X = newpt[0] * 64;
	vm->orgpoints[vm->m_state.zp1][p].Y = newpt[1] * 64;
#endif

//	double angle = angleBetween(gmVector2(vm->m_state.project.X, vm->m_state.project.Y), gmVector2(vm->m_state.freedom.X, vm->m_state.freedom.Y));
#endif

	vm->m_state.rp1 = vm->m_state.rp0;
	vm->m_state.rp2 = pi;
	if (a)// has the value TRUE
		vm->m_state.rp0 = pi;

	if (a)
		LOG("Set rp0,");
	else
		LOG("Don't set rp0,");

	if (b)
		LOG("Keep distance,");
	else
		LOG("Don't keep distance,");

	if (c)
		LOG("Round distance,");
	else
		LOG("Don't round distance,");

#if 0

	gmVector2 rp1 = gmVector2(vm->orgpoints[vm->m_state.zp0][vm->m_state.rp1].X / 64.0, vm->orgpoints[vm->m_state.zp0][vm->m_state.rp1].Y / 64.0);

	gmVector2 freedom(vm->m_state.freedom.X, vm->m_state.freedom.Y);



	vm->orgpoints[vm->m_state.zp1][p].X = pt.X * 64;
	vm->orgpoints[vm->m_state.zp1][p].Y = pt.Y * 64;
#endif
}

// IF[] IF test
void VM::tt_if()
{
	VM* vm = this;
	vm->pc++;
	printlevel();
	LOG("if ");

	StkElt e = vm->pop();
	if (e)
	{
		vm->m_iflevel++;
		LOG("(%d)\n", e);
		/*
		while (1)
		{
			uint8 instr_code = *vm->pc;
			if (instr_code == 0x59)	// eif
				break;

			if (instr_code == 0x1B)	// else
			{
				level--;
				printlevel();
				LOG("else\n");
				level++;
				vm->pc++;

				while (1)
				{
					uint8 instr_code = *vm->pc;
					if (instr_code == 0x59)	// eif
						break;

					skip_next(vm);
				}

				ASSERT(*vm->pc == 0x59);	// eif
				break;
			}

			printlevel();
			ttfuncs[instr_code](vm);
			LOG("\n");
		}
		ASSERT(*vm->pc == 0x59);	// eif
		vm->pc++;

		level--;
		printlevel();
		LOG("eif");
		*/
	}
	else
	{
		vm->m_iflevel++;
		LOG("(false)\n");

		while (1)
		{
			uint8 instr_code = *vm->pc;

			if (instr_code == 0x1B)	// else
				break;

			if (instr_code == 0x59)	// eif
			{
				break;
			}

			skip_next(vm);
		}

		if (*vm->pc == 0x1B)	// else
		{
//			level--;
			printlevel();
			LOG("else\n");
//			level++;
			vm->pc++;

			return;
			/*
			while (1)
			{
				uint8 instr_code = *vm->pc;

				if (instr_code == 0x59)	// eif
					break;

				printlevel();
				ttfuncs[instr_code](vm);
				LOG("\n");
			}
			*/
		}

		vm->m_iflevel--;
		ASSERT(*vm->pc == 0x59);	// eif
		vm->pc++;

//		level--;
		printlevel();
		LOG("eif");
	}
}

// RCVT[] Read Control Value Table entry
void VM::tt_rcvt()
{
	VM* vm = this;
	vm->pc++;
	LOG("Read Control Value Table Entry");

	uint32 loc = vm->pop();//: CVT entry number (uint32)

	if (loc >= 0 && loc < vm->m_pFile->m_cvtSize)
	{
		F26Dot6 value = vm->m_cvt[loc];

		LOG(" %d = %d", loc, value);

		vm->push(value);//Pushes  value: CVT value (F26Dot6)
	}
	else
	{
		ASSERT(0);
		THROW(-1);
	}
}

// MD[a] Measure Distance
void VM::tt_md()
{
	uint8 a = *pc - 0x49;
	pc++;

	uint32 p1 = pop();
	uint32 p2 = pop();

	vector2d project(m_state.project.X, m_state.project.Y);
	double angle = LDraw::GetLineAngleRadians(0, 0, project[0], project[1]);

	int32 distance;

	if (a)	// original
	{
		distance = rotatePoint(orgpoints[m_state.zp1][p2].X - orgpoints[m_state.zp0][p1].X, orgpoints[m_state.zp1][p2].Y - orgpoints[m_state.zp0][p1].Y, -angle)[0];
	}
	else
	{
		distance = rotatePoint(newpoints[m_state.zp1][p2].X - newpoints[m_state.zp0][p1].X, newpoints[m_state.zp1][p2].Y - newpoints[m_state.zp0][p1].Y, -angle)[0];
	}

	push(distance);

	LOG("Measure Distance %.2f", distance / 64.0);
}

// GC[a] Get Coordinate projected onto the projection vector
void VM::tt_gc()
{
	VM* vm = this;
	uint8 a = *vm->pc - 0x46;
	vm->pc++;

	uint32 p = vm->pop();//: point number (uint32)  

	vector2d project(vm->m_state.dualproject.X, vm->m_state.dualproject.Y);
	//double angle = angleBetween(project, gmVector2(1, 0));
	double angle = LDraw::GetLineAngleRadians(0, 0, project[0], project[1]);

	if (p >= vm->gpointsCount[vm->m_state.zp2])
		THROW(-1);

	vector2d pt;
	
	if (a)
		pt = rotatePoint(vm->orgpoints[vm->m_state.zp2][p].X, vm->orgpoints[vm->m_state.zp2][p].Y, -angle);
	else
		pt = rotatePoint(vm->newpoints[vm->m_state.zp2][p].X, vm->newpoints[vm->m_state.zp2][p].Y, -angle);

	int d = (int)(pt[0]+0.5);// * 64 * vm->m_pFont->m_emSize / vm->m_pFont->m_unitsPerEm);

//	d = (d+32) & ~63;

	vm->push(d);

//	F26Dot6 c = GetPositionOfPointAlongVector(vm->orgpoints[vm->m_state.zp2][p], vm->m_state.project);
//	vm->push(c);//Pushes  c: coordinate location (F26Dot6)  

	LOG("gc p=%d d=%d", p, d);
}

// DUP[] DUPlicate top stack element
void VM::tt_dup()
{
	VM* vm = this;
	LOG("dup %d", vm->m_stack[vm->m_stack.GetSize()-1]);
	vm->pc++;
	vm->push(vm->m_stack[vm->m_stack.GetSize()-1]);
}

// CINDEX[] Copy the INDEXed element to the top of the stack
void VM::tt_cindex()
{
	VM* vm = this;
	LOG("cindex");

	vm->pc++;
	int k = vm->pop();
	ASSERT(k > 0);

	LOG(" %d=%d", k, vm->m_stack[vm->m_stack.GetSize()-k]);

	vm->push(vm->m_stack[vm->m_stack.GetSize()-k]/**(vm->m_stack.end()-k)*/);
}

// MINDEX[] Move the INDEXed element to the top of the stack
void VM::tt_mindex()
{
	VM* vm = this;
	vm->pc++;
	LOG("mindex");

	int k = vm->pop();
	ASSERT(k > 0);
	if (!(k > 0)) THROW(-1);

//	int size = vm->m_stack.GetSize();

	StkElt elt = vm->m_stack[vm->m_stack.GetSize()-k];
	vm->m_stack.RemoveAt(vm->m_stack.GetSize()-k);//vm->m_stack.end()-k);
	vm->push(elt);
}

// ROLL[] ROLL the top three stack elements
void VM::tt_roll()
{
	VM* vm = this;
	LOG("roll");
	vm->pc++;

	StkElt e1 = vm->pop();
	StkElt e2 = vm->pop();
	StkElt e3 = vm->pop();
	vm->push(e2);
	vm->push(e1);
	vm->push(e3);
}

// SMD[] Set Minimum Distance
void VM::tt_smd()
{
	VM* vm = this;
	vm->pc++;
	vm->m_state.minDistance = vm->pop();

	LOG("Set Minimum Distance %d", vm->m_state.minDistance);
}

// SCFS[] Sets Coordinate From the Stack using projection vector and freedom vector
void VM::tt_scfs()
{
	VM* vm = this;
	vm->pc++;
	LOG("scfs");

	F26Dot6 c = vm->pop();//: coordinate value (F26Dot6)  
	uint32 pn = vm->pop();//: point number (uint32)  

	vector2d project(vm->m_state.project.X, vm->m_state.project.Y);
	double angle;
	angle = LDraw::GetLineAngleRadians(0, 0, project[0], project[1]);

	vector2d freedom(vm->m_state.freedom.X, vm->m_state.freedom.Y);
	freedom.normalize();
	freedom = rotatePoint(freedom, -angle);

	vector2d p = rotatePoint(vm->newpoints[vm->m_state.zp2][pn].X, vm->newpoints[vm->m_state.zp2][pn].Y, -angle);

	int newx = c;
	int dy = freedom[1]/freedom[0] * (newx - p[0]);

	vector2d newp = rotatePoint(vector2d(newx, p[1] + dy), angle);

	if (vm->m_state.freedom.X) vm->bpoints[vm->m_state.zp2][pn] |= 1;
	if (vm->m_state.freedom.Y) vm->bpoints[vm->m_state.zp2][pn] |= 2;
	vm->newpoints[vm->m_state.zp2][pn].X = newp[0]+0.5;
	vm->newpoints[vm->m_state.zp2][pn].Y = newp[1]+0.5;
}

// ISECT[] moves point p to the InterSECTion of two lines
void VM::tt_isect()
{
	VM* vm = this;
	vm->pc++;
	LOG("isect");

	uint32 a0 = vm->pop();//: start point of line A (uint32)  
	uint32 a1 = vm->pop();//: end point of line A (uint32)  
	uint32 b0 = vm->pop();//: start point of line B (uint32)  
	uint32 b1 = vm->pop();//: end point of line B (uint32)  
	uint32 p = vm->pop();//: point to move (uint32) 
}

// WCVTF[] Write Control Value Table in Funits
void VM::tt_wcvtf()
{
	VM* vm = this;
	vm->pc++;
	LOG("Write Control Value Table in Funits");

	//n: number in FUnits (uint32) l: control value table location (uint32) 
	int32 val = vm->pop();
	uint loc = vm->pop();

	if (loc == 23)
		LOG("");

	if (loc >= 0 && loc < vm->m_pFile->m_cvtSize)
	{
		vm->m_cvt[loc] = val;
		//vm->m_pFont->m_cvtUnit[loc] = 0;
	}
	else
	{
		ASSERT(0);
		THROW(-1);
	}
}

// SRP0[] Set Reference PointI 0
void VM::tt_srp0()
{
	VM* vm = this;
	vm->pc++;
	LOG("srp0");

	vm->m_state.rp0 = vm->pop();//: point number (uint32) 
	/*
	if (vm->m_state.rp0 < 0)
	{
		ASSERT(0);
		THROW(-1);
	}
	*/
}

// SRP1[] Set Reference PointI 1
void VM::tt_srp1()
{
	VM* vm = this;
	vm->pc++;
	LOG("srp1");

	vm->m_state.rp1 = vm->pop();//: point number (uint32) 
	if (vm->m_state.rp1 < 0) THROW(-1);
}

// SRP2[] Set Reference PointI 2
void VM::tt_srp2()
{
	VM* vm = this;
	vm->pc++;
	LOG("srp2");

	vm->m_state.rp2 = vm->pop();//: point number (uint32) 
	if (vm->m_state.rp2 < 0) THROW(-1);
}

// SZP0[] Set Zone Pointer 0
void VM::tt_szp0()
{
	VM* vm = this;
	vm->pc++;
	LOG("szp0");

	vm->m_state.zp0 = vm->pop();//: zone number (uint32) 
	if (vm->m_state.zp0 < 0 || vm->m_state.zp0 > 1)
		THROW(-1);
}

// SZP1[] Set Zone Pointer 1
void VM::tt_szp1()
{
	VM* vm = this;
	vm->pc++;
	LOG("szp1");

	vm->m_state.zp1 = vm->pop();//: zone number (uint32) 
	if (vm->m_state.zp1 < 0 || vm->m_state.zp1 > 1)
		THROW(-1);
}

// SZP2[] Set Zone Pointer 2
void VM::tt_szp2()
{
	VM* vm = this;
	vm->pc++;
	LOG("szp2");

	vm->m_state.zp2 = vm->pop();//: zone number (uint32) 
	if (vm->m_state.zp2 < 0 || vm->m_state.zp2 > 1)
		THROW(-1);
}

// SZPS[] Set Zone PointerS
void VM::tt_szps()
{
	VM* vm = this;
	vm->pc++;
	LOG("Set Zone PointerS");

	uint32 n = vm->pop();//: zone number (uint32) 
	if (n < 0 || n > 1)
		THROW(-1);

	vm->m_state.zp0 = n;
	vm->m_state.zp1 = n;
	vm->m_state.zp2 = n;
}

void VM::tt_else()
{
	VM* vm = this;
	LOG("else without matching if");
	ASSERT(0);
	THROW(-1);
}

void VM::tt_eif()
{
	VM* vm = this;
	vm->pc++;
	if (vm->m_iflevel > 0)
	{
		vm->m_iflevel--;
	}
	else
	{
		LOG("eif without matching if");
		ASSERT(0);
		THROW(-1);
	}
}

// SFVFS[] Set Freedom Vector From Stack
void VM::tt_sfvfs()
{
	VM* vm = this;
	vm->pc++;
	LOG("sfvfs");

	vm->m_state.freedom.Y = vm->pop();//: y component of freedom vector (F2Dot14)  
	vm->m_state.freedom.X = vm->pop();//: x component of freedom vector (F2Dot14)  
}

// NEG[] NEGate
void VM::tt_neg()
{
	VM* vm = this;
	vm->pc++;
	int32 val = vm->pop();
	vm->push(-val);
	LOG("neg %d=%d", val, -val);
}

// NOT[] logical NOT
void VM::tt_not()
{
	VM* vm = this;
	vm->pc++;
	int32 val = vm->pop();
	vm->push(!val);
	LOG("not");
}

// SCANTYPE[] SCANTYPE
void VM::tt_scantype()
{
	VM* vm = this;
	vm->pc++;
	LOG("scantype");

	int n = vm->pop();//: stack element 

/*
	if n=0 rules 1 and 2 are invoked (dropout control scan conversion including stubs)
	if n=1 rules 1 and 3 are invoked (dropout control scan conversion excluding stubs)
	if n=2 rule 1 is invoked (fast scan conversion)

*/
}

// MIAP[a] Move Indirect Absolute PointI
void VM::tt_miap()
{
	VM* vm = this;
	int a = *vm->pc - 0x3E;
	vm->pc++;

	int n = vm->pop();	// CVT entry number (F26Dot6)  
	uint32 pi = vm->pop();	// point number (uint32)  

	if (vm->orgpoints[vm->m_state.zp0] == NULL)
	{
		// zone zp0 points not available from font program
		THROW(-2);
	}

	if (a == 0)
	{
// don't round the distance and don't look at the control value cut-in  
//		ASSERT(0);
	}
	else
	{
// round the distance and look at the control value cut-in  
//		if (vm->m_pFont->m_cvt[n]
	}

	F26Dot6 c = vm->m_cvt[n];

	vector2d project(vm->m_state.project.X, vm->m_state.project.Y);
	double angle = angleBetween(vector2d(1, 0), project);
	angle = LDraw::GetLineAngleRadians(0, 0, project[0], project[1]);

	vector2d freedom(vm->m_state.freedom.X, vm->m_state.freedom.Y);
	freedom.normalize();
	freedom = rotatePoint(freedom, -angle);
	ASSERT(fabs(freedom.length()-1) < 0.0001);

	if (pi < 0 || pi >= vm->gpointsCount[vm->m_state.zp0]) THROW(-1);

	vector2d p = rotatePoint(vm->newpoints[vm->m_state.zp0][pi].X, vm->newpoints[vm->m_state.zp0][pi].Y, -angle);

	ASSERT(freedom[0] != 0);

	int newx = c;// - p[0];
	if (a)
	{
		newx = vm->m_state.round(newx);
		//newx = (newx+32) & ~63;
	//	c = (c+32) & ~63;
	}

	/*
	int distance_diff = newx - p[0];
	if (abs(distance_diff) >= vm->m_state.controlValueCutIn)
	{
		newx = p[0];
	}
	*/

	double dy = freedom[1]/freedom[0] * (newx - p[0]);

	vector2d newp(newx, p[1] + dy);

	newp = rotatePoint(newp, angle);

	if (vm->bpoints[vm->m_state.zp0])
	{
		if (vm->bpoints[vm->m_state.zp0][pi] == 0)
		{
		//	vm->orgpoints[vm->m_state.zp0][pi].X = newp[0] + 0.5;
		//	vm->orgpoints[vm->m_state.zp0][pi].Y = newp[1] + 0.5;
		}

		if (vm->m_state.freedom.X) vm->bpoints[vm->m_state.zp0][pi] |= 1;
		if (vm->m_state.freedom.Y) vm->bpoints[vm->m_state.zp0][pi] |= 2;
	}
	vm->newpoints[vm->m_state.zp0][pi].X = newp[0] + 0.5;
	vm->newpoints[vm->m_state.zp0][pi].Y = newp[1] + 0.5;

	LOG("miap %d(%d), p=%d (%.2f,%.2f)", c, n, pi, newp[0]/64, newp[1]/64);//vm->orgpoints[vm->m_state.zp0][p].X/64, vm->orgpoints[vm->m_state.zp0][p].Y/64);

#if 0
	gmVector2 pnt = gmVector2(vm->orgpoints[vm->m_state.zp0][p].X / 64.0, vm->orgpoints[vm->m_state.zp0][p].Y / 64.0);
	gmVector2 freedom = gmVector2(vm->m_state.freedom.X, vm->m_state.freedom.Y);
	gmVector2 project = gmVector2(vm->m_state.project.X, vm->m_state.project.Y);
	project.normalize();

	gmVector2 perpendicular = gmVector2(project[1], -project[0]);

	double c = vm->m_cvt[n]/64.0;

	gmVector2 v;
	intersection(
		pnt, pnt+freedom,
		project * c, project * c + perpendicular, v);

	/*
	vm->orgpoints[vm->m_state.zp0][p].X = v[0] * 64;
	vm->orgpoints[vm->m_state.zp0][p].Y = v[1] * 64;
	*/

//	vm->opoints[vm->m_state.zp0][p].X = v[0] * 64;
//	vm->opoints[vm->m_state.zp0][p].Y = v[1] * 64;
#endif

	vm->m_state.rp0 = vm->m_state.rp1 = pi;
}

//MDAP[a] Move Direct Absolute PointI
void VM::tt_mdap()
{
	VM* vm = this;
	int a = *vm->pc - 0x2E;
	vm->pc++;

	uint32 pi = vm->pop();	// point number (uint32)  

	if (pi < 0 || pi >= vm->gpointsCount[vm->m_state.zp0])
		THROW(-1);

	LOG("mdap p=%d", pi);

	if (a)
	{
		vector2d project(vm->m_state.project.X, vm->m_state.project.Y);
		double angle = angleBetween(vector2d(1, 0), project);
		angle = LDraw::GetLineAngleRadians(0, 0, project[0], project[1]);

		vector2d freedom(vm->m_state.freedom.X, vm->m_state.freedom.Y);
		freedom.normalize();
		freedom = rotatePoint(freedom, -angle);
		ASSERT(fabs(freedom.length() - 1) < 0.00001);

		vector2d p = rotatePoint(vm->newpoints[vm->m_state.zp0][pi].X, vm->newpoints[vm->m_state.zp0][pi].Y, -angle);
		int newx = p[0];
		newx = vm->m_state.round(newx);
		/*
		if (x < 0)
		{
			x = -(((-x)+32) & ~63);
		}
		else
		{
			x = (x+32) & ~63;
		}
		*/

		double dy = freedom[1]/freedom[0] * (newx - p[0]);
		vector2d newpt(newx, p[1] + dy);

		newpt = rotatePoint(newpt, angle);

		vm->newpoints[vm->m_state.zp0][pi].X = newpt[0]+0.5;
		vm->newpoints[vm->m_state.zp0][pi].Y = newpt[1]+0.5;

		LOG("(%.2f,%.2f)", newpt[0] / 64.0, newpt[1] / 64.0);
	}

	if (vm->m_state.freedom.X) vm->bpoints[vm->m_state.zp0][pi] |= 1;
	if (vm->m_state.freedom.Y) vm->bpoints[vm->m_state.zp0][pi] |= 2;

	vm->m_state.rp0 = vm->m_state.rp1 = pi;
}

//bool bGlyphProgram = false;

// IP[] Interpolate PointI
void VM::tt_ip()
{
	VM* vm = this;
	vm->pc++;
	LOG("ip rp1=%d rp2=%d", vm->m_state.rp1, vm->m_state.rp2);
//	fflush(fplog);

	/*
	if (bGlyphProgram)
	{
		ATLTRACE("");
	}
	*/

	for (int i = 0; i < vm->m_loop; i++)
	{
		uint32 p = vm->pop();

		if (p < 0 || p >= vm->gpointsCount[vm->m_state.zp2])
			THROW(-1);

	//	PointI pt1 = vm->orgpoints[1][vm->m_state.rp1];
	//	PointI pt2 = vm->orgpoints[1][vm->m_state.rp2];

		vector2d project(vm->m_state.dualproject.X, vm->m_state.dualproject.Y);
		vector2d freedom(vm->m_state.freedom.X, vm->m_state.freedom.Y);
		freedom.normalize();

		//double angle = angleBetween(project, gmVector2(1, 0));
		double angle = LDraw::GetLineAngleRadians(0, 0, project[0], project[1]);

		freedom = rotatePoint(freedom, -angle);
		ASSERT(fabs(freedom.length() - 1) < 0.00001);

		LOG(" p=%d", p);
//		fflush(fplog);

		vector2d _pt1 = rotatePoint(vm->orgpoints[vm->m_state.zp0][vm->m_state.rp1].X, vm->orgpoints[vm->m_state.zp0][vm->m_state.rp1].Y, -angle);
		vector2d _pt2 = rotatePoint(vm->orgpoints[vm->m_state.zp1][vm->m_state.rp2].X, vm->orgpoints[vm->m_state.zp1][vm->m_state.rp2].Y, -angle);
		vector2d _pt = rotatePoint(vm->orgpoints[vm->m_state.zp2][p].X, vm->orgpoints[vm->m_state.zp2][p].Y, -angle);

		vector2d n_pt1 = rotatePoint(vm->newpoints[vm->m_state.zp0][vm->m_state.rp1].X, vm->newpoints[vm->m_state.zp0][vm->m_state.rp1].Y, -angle);
		vector2d n_pt2 = rotatePoint(vm->newpoints[vm->m_state.zp1][vm->m_state.rp2].X, vm->newpoints[vm->m_state.zp1][vm->m_state.rp2].Y, -angle);
		vector2d n_pt = rotatePoint(vm->newpoints[vm->m_state.zp2][p].X, vm->newpoints[vm->m_state.zp2][p].Y, -angle);

		double t = (_pt[0] - _pt1[0]) / (_pt2[0] - _pt1[0]);
		double newx = n_pt1[0] + (n_pt2[0] - n_pt1[0]) * t;

		double dy = freedom[1]/freedom[0] * (newx - n_pt[0]);

		n_pt = rotatePoint(newx, n_pt[1] + dy, angle);

		if (vm->m_state.zp2 == 1)
		{
		//	LOG("Zone1");
		}
		vm->newpoints[vm->m_state.zp2][p].X = n_pt[0] + 0.5;
		vm->newpoints[vm->m_state.zp2][p].Y = n_pt[1] + 0.5;

		if (vm->m_state.freedom.X) vm->bpoints[vm->m_state.zp2][p] |= 1;
		if (vm->m_state.freedom.Y) vm->bpoints[vm->m_state.zp2][p] |= 2;

		LOG("(%.2f,%.2f)", (vm->newpoints[vm->m_state.zp2][p].X/64.0), (vm->newpoints[vm->m_state.zp2][p].Y/64.0));
//		fflush(fplog);

//		gmVector2 normal1 = gmVector2(vm->m_state.project.Y, -vm->m_state.project.X);

		/*
		double d1 = normal1 - vm->orgpoints[vm->m_state.zp0][p];

		int d1 = pt.X - pt1.X;
		int d2 = pt.X - pt2.X;

		int d3 = pt.X - pt3.X;
		int d4 = pt.X - pt3.X;
		*/
	}
	vm->m_loop = 1;
}

// IUP[a] Interpolate Untouched Points through the outline
void VM::tt_iup()
{
	VM* vm = this;
	int a = *vm->pc - 0x30;
	vm->pc++;

	if (vm->m_state.zp2 != 1)
		THROW(-1);

	if (a == 0)	// 0: interpolate in the y-direction  
	{
		LOG("iup y-direction");

		// Traverse all the contours
		int cstart = 0;
		for (int c = 0; c < glyphDesc->numberOfContours; c++)
		{
			// Find first touched point in contour
			int fi;
			for (fi = cstart; fi <= endPtsOfContours[c]; fi++)
			{
				if (vm->bpoints[vm->m_state.zp2][fi] & 2)
				{
					break;
				}
			}

			if (fi <= endPtsOfContours[c])
			{
				int first = fi;
				// Traverse the rest of the contour
				do
				{
					// find next touched point
					int second = first;

					do
					{
						second++;
						if (second > endPtsOfContours[c])
						{
							second = fi;	// Wrap around
							break;
						}
					}
					while (!(vm->bpoints[m_state.zp2][second] & 2));

					int lowest;
					int highest;

					if (orgpoints[m_state.zp2][first].Y <= orgpoints[m_state.zp2][second].Y)
					{
						lowest = first;
						highest = second;
					}
					else
					{
						lowest = second;
						highest = first;
					}

					int lowestShift = newpoints[m_state.zp2][lowest].Y - orgpoints[m_state.zp2][lowest].Y;
					int highestShift = newpoints[m_state.zp2][highest].Y - orgpoints[m_state.zp2][highest].Y;

					// move the points in between
					int j;
					if (first == endPtsOfContours[c])
						j = cstart;	// Wrap around to beginning of contour
					else
						j = first+1;
					while (j != second)
					{
						int newx;
						int orgx = orgpoints[vm->m_state.zp2][j].Y;
						if (orgx <= orgpoints[vm->m_state.zp2][lowest].Y)
						{
							newx = orgx + lowestShift;
						}
						else if (orgx >= orgpoints[vm->m_state.zp2][highest].Y)
						{
							newx = orgx + highestShift;
						}
						else
						{
							double t = (double)(orgx - orgpoints[m_state.zp2][lowest].Y) / (orgpoints[m_state.zp2][highest].Y - orgpoints[vm->m_state.zp2][lowest].Y);
							newx = newpoints[m_state.zp2][lowest].Y + (newpoints[m_state.zp2][highest].Y - newpoints[m_state.zp2][lowest].Y) * t + 0.5;
						}

						ASSERT(!(bpoints[vm->m_state.zp2][j] & 2));
						newpoints[vm->m_state.zp2][j].Y = newx;
						bpoints[vm->m_state.zp2][j] |= 2;

						if (j == endPtsOfContours[c])
							j = cstart;	// Wrap around to beginning of contour
						else
							j++;
					}

					// For the next pair of touched points, the first point is the previous pairs second point
					first = second;
				}
				while (first != fi);
			}

			cstart = endPtsOfContours[c]+1;	// start point index of next contour
		}

	}
	else //1: interpolate in the x-direction  
	{
		LOG("iup x-direction");

		// Traverse all the contours
		int cstart = 0;
		for (int c = 0; c < glyphDesc->numberOfContours; c++)
		{
			// Find first touched point in contour
			int fi;
			for (fi = cstart; fi <= endPtsOfContours[c]; fi++)
			{
				if (vm->bpoints[vm->m_state.zp2][fi] & 1)
				{
					break;
				}
			}

			if (fi <= endPtsOfContours[c])
			{
				int first = fi;
				// Traverse the rest of the contour
				do
				{
					// find next touched point
					int second = first;
					
					do
					{
						second++;
						if (second > endPtsOfContours[c])
						{
							second = fi;	// Wrap around
							break;
						}
					}
					while (!(vm->bpoints[m_state.zp2][second] & 1));

					int lowest;
					int highest;

					if (orgpoints[m_state.zp2][first].X <= orgpoints[m_state.zp2][second].X)
					{
						lowest = first;
						highest = second;
					}
					else
					{
						lowest = second;
						highest = first;
					}

					int lowestShift = newpoints[m_state.zp2][lowest].X - orgpoints[m_state.zp2][lowest].X;
					int highestShift = newpoints[m_state.zp2][highest].X - orgpoints[m_state.zp2][highest].X;

					// move the points in between
					//for (int j = first+1; j < second; j++)
					int j;
					if (first == endPtsOfContours[c])
						j = cstart;	// Wrap around to beginning of contour
					else
						j = first+1;
					while (j != second)
					{
						int newx;
						int orgx = orgpoints[vm->m_state.zp2][j].X;
						if (orgx <= orgpoints[vm->m_state.zp2][lowest].X)
						{
							newx = orgx + lowestShift;
						}
						else if (orgx >= orgpoints[vm->m_state.zp2][highest].X)
						{
							newx = orgx + highestShift;
						}
						else
						{
							double t = (double)(orgx - orgpoints[m_state.zp2][lowest].X) / (orgpoints[m_state.zp2][highest].X - orgpoints[vm->m_state.zp2][lowest].X);
							newx = newpoints[m_state.zp2][lowest].X + (newpoints[m_state.zp2][highest].X - newpoints[m_state.zp2][lowest].X) * t + 0.5;
						}

						newpoints[vm->m_state.zp2][j].X = newx;
						bpoints[vm->m_state.zp2][j] |= 1;

						if (j == endPtsOfContours[c])
							j = cstart;	// Wrap around to beginning of contour
						else
							j++;
					}

					// For the next pair of touched points, the first point is the previous pairs second point
					first = second;
				}
				while (first != fi);
			}

			cstart = endPtsOfContours[c]+1;	// start point index of next contour
		}

	}
}

// SCVTCI[] Set Control Value Table Cut-In
void VM::tt_scvtci()
{
	VM* vm = this;
	vm->pc++;
	LOG("scvtci");

	vm->m_state.controlValueCutIn = vm->pop();	// value for cut-in (F26Dot6) 
}

// GETINFO[] GET INFOrmation
void VM::tt_getinfo()
{
	VM* vm = this;
	vm->pc++;
	LOG("getinfo");

	uint32 result = 0;

	uint32 selector = vm->pop();
	if (selector & 1)	// version
	{
		/*
System  Engine Version  
Macintosh System 6.0  1  
Macintosh System 7.0  2  
Windows 3.1  3  
KanjiTalk 6.1  4  
*/
		result = 3;
	}

	if (selector & 2)	// rotated?
	{
		// TODO
		// set bit 8 if rotated
	}

	if (selector & 4)	// stretched?
	{
		// TODO
		// set bit 9 if stretched
	}

	vm->push(result);
}

// ROFF[] Round OFF
void VM::tt_roff()
{
	VM* vm = this;
	vm->pc++;
	LOG("roff");

	vm->m_state.roundPhase = 0;
	vm->m_state.roundThreshold = 0;
	vm->m_state.roundPeriod = 1;
}

// SROUND[] Super ROUND
void VM::tt_sround()
{
	VM* vm = this;
	vm->pc++;
	LOG("sround");
	uint8 n = vm->pop();
	
	int Threshold = n&15;
	int Phase = (n>>4)&3;
	int Period = (n>>6)&3;

	if (Period == 0)
		vm->m_state.roundPeriod = 32;
	else if (Period == 1)
		vm->m_state.roundPeriod = 64;
	else if (Period == 2)
		vm->m_state.roundPeriod = 128;
	else
		THROW(-1);

	if (Phase == 0)
		vm->m_state.roundPhase = 0;
	else if (Phase == 1)
		vm->m_state.roundPhase = vm->m_state.roundPeriod/4;
	else if (Phase == 2)
		vm->m_state.roundPhase = vm->m_state.roundPeriod/2;
	else
		vm->m_state.roundPhase = vm->m_state.roundPeriod*3/4;

	switch (Threshold)
	{
	case 0:  vm->m_state.roundThreshold = vm->m_state.roundPeriod-1; break;
	case 1:  vm->m_state.roundThreshold = vm->m_state.roundPeriod * -3/8; break;  
	case 2:  vm->m_state.roundThreshold = vm->m_state.roundPeriod * -2/8; break;
	case 3:  vm->m_state.roundThreshold = vm->m_state.roundPeriod * -1/8; break;
	case 4:  vm->m_state.roundThreshold = vm->m_state.roundPeriod * 0/8; break;
	case 5:  vm->m_state.roundThreshold = vm->m_state.roundPeriod * 1/8; break;
	case 6:  vm->m_state.roundThreshold = vm->m_state.roundPeriod * 2/8; break;
	case 7:  vm->m_state.roundThreshold = vm->m_state.roundPeriod * 3/8; break;
	case 8:  vm->m_state.roundThreshold = vm->m_state.roundPeriod * 4/8; break;
	case 9:  vm->m_state.roundThreshold = vm->m_state.roundPeriod * 5/8; break;
	case 10: vm->m_state.roundThreshold = vm->m_state.roundPeriod * 6/8; break;
	case 11: vm->m_state.roundThreshold = vm->m_state.roundPeriod * 7/8; break;
	case 12: vm->m_state.roundThreshold = vm->m_state.roundPeriod * 8/8; break;
	case 13: vm->m_state.roundThreshold = vm->m_state.roundPeriod * 9/8; break;
	case 14: vm->m_state.roundThreshold = vm->m_state.roundPeriod * 10/8; break;
	case 15: vm->m_state.roundThreshold = vm->m_state.roundPeriod * 11/8; break;
	}
}

// ROUND[ab] ROUND value
void VM::tt_round()
{
	VM* vm = this;
	vm->pc++;

	F26Dot6 n1 = vm->pop();//: device space distance (F26Dot6)  

	F26Dot6 n2;
	if (1)	//grid
	{
		n2 = vm->m_state.round(n1);
	//	n2 = (n1+32) & ~63;
	}

	vm->push(n2);

	LOG("round %d=%d", n1, n2);
}

// INSTCTRL[ ] INSTRuction execution ConTRoL
void VM::tt_instctrl()
{
	VM* vm = this;
	vm->pc++;
	LOG("instctrl");
	int32 s = vm->pop();	// selector (int32)
	int32 v = vm->pop();	// value for instruction control (int32)
}

// SLOOP[] Set LOOP variable
void VM::tt_sloop()
{
	VM* vm = this;
	LOG("sloop");
	vm->pc++;
	vm->m_loop = vm->pop();
	if (vm->m_loop < 1)
		THROW(-1);
}

// FLIPOFF[] set the auto FLIP Boolean to OFF
void VM::tt_flipoff()
{
	VM* vm = this;
	vm->pc++;
	vm->m_state.bAutoFlip = false;
	LOG("flipoff");
}

// FLIPON[] set the auto FLIP Boolean to ON
void VM::tt_flipon()
{
	VM* vm = this;
	vm->pc++;
	vm->m_state.bAutoFlip = true;
	LOG("flipon");
}

void deltap(VM* vm, double angle, vector2d& freedom, int pi, int magnitude)
{
	int move;

	if (magnitude >= 8)
		move = magnitude-7;
	else
		move = magnitude-8;

	if (pi < 0 || pi >= vm->gpointsCount[vm->m_state.zp0])
		THROW(-1);

	vector2d p = rotatePoint(vm->newpoint(vm->m_state.zp0,pi).X, vm->newpoint(vm->m_state.zp0,pi).Y, -angle);

	int dx = (move*64) / (1<<vm->m_state.deltaShift);
	double dy = freedom[1]/freedom[0] * dx;
	vector2d newpt(p[0] + dx, p[1] + dy);

	newpt = rotatePoint(newpt, angle);

//	vm->bpoints[vm->m_state.zp0][pi] = true;
	if (vm->m_state.freedom.X) vm->bpoints[vm->m_state.zp0][pi] |= 1;
	if (vm->m_state.freedom.Y) vm->bpoints[vm->m_state.zp0][pi] |= 2;

	vm->newpoint(vm->m_state.zp0,pi).X = newpt[0]+0.5;
	vm->newpoint(vm->m_state.zp0,pi).Y = newpt[1]+0.5;

	LOG(" p=%d (%.2f,%.2f)", pi, newpt[0]/64, newpt[1]/64);
}

// DELTAP1[] DELTA exception P1
void VM::tt_deltap1()
{
	VM* vm = this;
	if (vm->m_state.zp0 == 1)
	{
	//	LOG("Zone1\n");
	}
	vm->pc++;
	uint32 n = vm->pop();

	LOG("deltap1");

	vector2d project(vm->m_state.project.X, vm->m_state.project.Y);
	double angle = angleBetween(vector2d(1, 0), project);
	angle = LDraw::GetLineAngleRadians(0, 0, project[0], project[1]);

	vector2d freedom(vm->m_state.freedom.X, vm->m_state.freedom.Y);
	freedom.normalize();
	freedom = rotatePoint(freedom, -angle);
	ASSERT(fabs(freedom.length() - 1) < 0.0001);

	for (uint32 i = 0; i < n; i++)
	{
		uint32 pi = vm->pop();
		uint8 arg = vm->pop();
		if (pi >= vm->gpointsCount[vm->m_state.zp0])
			THROW(-1);

		ASSERT(pi < vm->gpointsCount[vm->m_state.zp0]);

		int rel = arg>>4;
		int magnitude = arg&0xF;
		LOG(" p=%d at ppem=(%d+%d)(%d)", pi, vm->m_state.deltaBase, rel, vm->m_state.deltaBase+rel);
		if (vm->m_pFont->m_emSize == vm->m_state.deltaBase+rel)
		{
			deltap(this, angle, freedom, pi, magnitude);
		}
	}
}

// DELTAP2[] DELTA exception P2
void VM::tt_deltap2()
{
	VM* vm = this;

	vm->pc++;
	uint32 n = vm->pop();

	vector2d project(vm->m_state.project.X, vm->m_state.project.Y);
	double angle = angleBetween(vector2d(1, 0), project);
	angle = LDraw::GetLineAngleRadians(0, 0, project[0], project[1]);

	vector2d freedom(vm->m_state.freedom.X, vm->m_state.freedom.Y);
	freedom.normalize();
	freedom = rotatePoint(freedom, -angle);
	ASSERT(fabs(freedom.length() - 1) < 0.0001);

	for (uint32 i = 0; i < n; i++)
	{
		uint32 pi = vm->pop();
		uint8 arg = vm->pop();

		if (pi < 0 || pi >= vm->gpointsCount[vm->m_state.zp0])
			THROW(-1);

		int rel = arg>>4;
		int magnitude = arg&0xF;

		if (vm->m_pFont->m_emSize == vm->m_state.deltaBase+16+rel)
		{
			deltap(this, angle, freedom, pi, magnitude);
		}
	}
	LOG("deltap2");
}

// DELTAP3[] DELTA exception P3
void VM::tt_deltap3()
{
	VM* vm = this;

	vm->pc++;
	uint32 n = vm->pop();

	vector2d project(vm->m_state.project.X, vm->m_state.project.Y);
	double angle = angleBetween(vector2d(1, 0), project);
	angle = LDraw::GetLineAngleRadians(0, 0, project[0], project[1]);

	vector2d freedom(vm->m_state.freedom.X, vm->m_state.freedom.Y);
	freedom.normalize();
	freedom = rotatePoint(freedom, -angle);
	ASSERT(fabs(freedom.length() - 1) < 0.0001);

	for (uint32 i = 0; i < n; i++)
	{
		uint32 pi = vm->pop();
		uint8 arg = vm->pop();

		if (pi < 0 || pi >= vm->gpointsCount[vm->m_state.zp0])
			THROW(-1);

		int rel = arg>>4;
		int magnitude = arg&0xF;

		if (vm->m_pFont->m_emSize == vm->m_state.deltaBase+32+rel)
		{
			deltap(this, angle, freedom, pi, magnitude);
		}
	}
	LOG("deltap3");
}

// DELTAC1[] DELTA exception C1
void VM::tt_deltac1()
{
	VM* vm = this;
	LOG("deltac1");

	vm->pc++;
	uint32 n = vm->pop();
	for (uint32 i = 0; i < n; i++)
	{
		int c = vm->pop();
		uint8 arg = vm->pop();

		if (!(c >= 0 && c < vm->m_pFile->m_cvtSize))
			THROW(-1);

		int rel = arg>>4;
		int magnitude = arg&0xF;

		LOG(" c=%d at ppem=%d", c, vm->m_state.deltaBase+rel);

		if (vm->m_pFont->m_emSize == vm->m_state.deltaBase+rel/* && vm->m_pFont->m_emSize <= vm->m_state.deltaBase+15*/)
		{
			LOG(" c=%d", c);
			int move;

			if (magnitude >= 8)
				move = magnitude-7;
			else
				move = magnitude-8;

			int dx = (move * 64) / (1<<vm->m_state.deltaShift);

			vm->m_cvt[c] += dx;
		}
	}
}

// DELTAC2[] DELTA exception C2
void VM::tt_deltac2()
{
	VM* vm = this;
	LOG("deltac2");

	vm->pc++;
	uint32 n = vm->pop();
	for (uint32 i = 0; i < n; i++)
	{
		int c = vm->pop();
		uint8 arg = vm->pop();

		if (!(c >= 0 && c < vm->m_pFile->m_cvtSize))
			THROW(-1);

		int rel = arg>>4;
		int magnitude = arg&0xF;

		LOG(" c=%d at ppem=%d", c, vm->m_state.deltaBase+16+rel);

		if (vm->m_pFont->m_emSize == vm->m_state.deltaBase+16+rel)
		{
			int move;

			if (magnitude >= 8)
				move = magnitude-7;
			else
				move = magnitude-8;

			int dx = (move * 64) / (1<<vm->m_state.deltaShift);

			vm->m_cvt[c] += dx;
		}
	}
}

// DELTAC3[] DELTA exception C3
void VM::tt_deltac3()
{
	VM* vm = this;
	LOG("deltac3");

	vm->pc++;
	uint32 n = vm->pop();
	for (uint32 i = 0; i < n; i++)
	{
		int c = vm->pop();
		uint8 arg = vm->pop();

		int rel = arg>>4;
		int magnitude = arg&0xF;

		LOG(" c=%d at ppem=%d", c, vm->m_state.deltaBase+32+rel);

		if (vm->m_pFont->m_emSize == vm->m_state.deltaBase+32+rel/* && vm->m_pFont->m_emSize <= vm->m_state.deltaBase+15*/)
		{
			//ASSERT(0);
		}
	}
}

// SHP[a] SHift PointI using reference point
void VM::tt_shp()
{
	pc++;

	// TODO

	for (int i = 0; i < m_loop; i++)
	{
		uint32 pi = pop(); //point to be shifted (uint32)
	}
	m_loop = 1;
}

// SHC[a] SHift Contour using reference point
void VM::tt_shc()
{
	pc++;

	uint32 c = pop();//: contour to be shifted (uint32) 

	// TODO
}

// SHPIX[] SHift point by a PIXel amount
void VM::tt_shpix()
{
	VM* vm = this;
	vm->pc++;

	vector2d freedom(vm->m_state.freedom.X, vm->m_state.freedom.Y);
	freedom.normalize();

	F26Dot6 d = vm->pop();//magnitude of the shift (F26Dot6)  
	LOG("shpix ");
	for (int i = 0; i < vm->m_loop; i++)
	{
		if (vm->m_state.zp0 == 1)
		{
		//	LOG("zone1");
		}
		uint32 pi = vm->pop(); //point to be shifted (uint32)

		ASSERT(pi < vm->gpointsCount[vm->m_state.zp0]);

		if (vm->m_state.freedom.X) vm->bpoints[vm->m_state.zp0][pi] |= 1;
		if (vm->m_state.freedom.Y) vm->bpoints[vm->m_state.zp0][pi] |= 2;

		vm->newpoints[vm->m_state.zp0][pi].X += freedom[0] * d;
		vm->newpoints[vm->m_state.zp0][pi].Y += freedom[1] * d;

		LOG(" p=%d (%.2f,%.2f)", pi, vm->newpoints[vm->m_state.zp0][pi].X/64.0, vm->newpoints[vm->m_state.zp0][pi].Y/64.0);
	}
	vm->m_loop = 1;
}

VM::tyttfunc VM::ttfuncs[256] =
{
	&VM::tt_svtca,	// SVTCA[a] Set freedom and projection Vectors To Coordinate Axis
	&VM::tt_svtca,
	&VM::tt_spvtca,	// SPVTCA[a] Set Projection Vector To Coordinate Axis
	&VM::tt_spvtca,
	&VM::tt_sfvtca,	// SFVTCA[a] Set Freedom Vector to Coordinate Axis
	&VM::tt_sfvtca,
	&VM::tt_spvtl,	// SPVTL[a] Set Projection Vector To Line
	&VM::tt_spvtl,
	&VM::tt_sfvtl,	// SFVTL[a] Set Freedom Vector To Line
	&VM::tt_sfvtl,
	&VM::tt_spvfs,	// SPVFS[] Set Projection Vector From Stack
	&VM::tt_sfvfs,	// SFVFS[] Set Freedom Vector From Stack
	&VM::tt_gpv,	// GPV[] Get Projection Vector
	&VM::tt_notimpl,
	&VM::tt_sfvtpv,	// SFVTPV[] Set Freedom Vector To Projection Vector
	&VM::tt_isect,	// ISECT[] moves point p to the InterSECTion of two lines
	&VM::tt_srp0,	// SRP0[] Set Reference PointI 0
	&VM::tt_srp1,	// SRP1[] Set Reference PointI 1
	&VM::tt_srp2,	// SRP2[] Set Reference PointI 2
	&VM::tt_szp0,	// SZP0[] Set Zone Pointer 0
	&VM::tt_szp1, // 20 // SZP1[] Set Zone Pointer 1
	&VM::tt_szp2,	// SZP2[] Set Zone Pointer 2
	&VM::tt_szps,	// SZPS[] Set Zone PointerS
	&VM::tt_sloop,	// SLOOP[] Set LOOP variable
	&VM::tt_rtg,	// RTG[] Round To Grid
	&VM::tt_rthg,	// RTHG[] Round To Half Grid
	&VM::tt_smd,	// SMD[] Set Minimum Distance
	&VM::tt_else,
	&VM::tt_jmpr,	// JMPR[] JuMP Relative
	&VM::tt_scvtci,	// SCVTCI[] Set Control Value Table Cut-In
	&VM::tt_notimpl, // 30
	&VM::tt_notimpl,
	&VM::tt_dup,	// DUP[] DUPlicate top stack element
	&VM::tt_pop,	// POP[] POP top stack element
	&VM::tt_notimpl,
	&VM::tt_swap,	// SWAP[] SWAP the top two elements on the stack
	&VM::tt_notimpl,
	&VM::tt_cindex,	// CINDEX[] Copy the INDEXed element to the top of the stack
	&VM::tt_mindex,		// MINDEX[] Move the INDEXed element to the top of the stack
	&VM::tt_notimpl,
	&VM::tt_notimpl, // 40
	&VM::tt_notimpl,
	&VM::tt_loopcall,	// LOOPCALL[] LOOP and CALL function
	&VM::tt_call,
	&VM::tt_fdef,
	&VM::tt_endf,
	&VM::tt_mdap,		// MDAP[a] Move Direct Absolute PointI
	&VM::tt_mdap,		// MDAP[a] Move Direct Absolute PointI
	&VM::tt_iup,		// IUP[a] Interpolate Untouched Points through the outline
	&VM::tt_iup,
	&VM::tt_shp,		// SHP[a] SHift PointI using reference point
	&VM::tt_shp,
	&VM::tt_shc,		// SHC[a] SHift Contour using reference point
	&VM::tt_shc,
	&VM::tt_notimpl,
	&VM::tt_notimpl,
	&VM::tt_shpix,	// SHPIX[] SHift point by a PIXel amount
	&VM::tt_ip,		// IP[] Interpolate PointI
	&VM::tt_msirp,	// MSIRP[a] Move Stack Indirect Relative PointI
	&VM::tt_notimpl,
	&VM::tt_alignrp, // 60	// ALIGNRP[] ALIGN to Reference PointI
	&VM::tt_rtdg,		// RTDG[] Round To Double Grid
	&VM::tt_miap,		// MIAP[a] Move Indirect Absolute PointI
	&VM::tt_miap,		// MIAP[a] Move Indirect Absolute PointI
	&VM::tt_npushb,	// 64
	&VM::tt_npushw,
	&VM::tt_ws,		// WS[] Write Store
	&VM::tt_rs,		// RS[] Read Store
	&VM::tt_wcvtp,	// // WCVTP[] Write Control Value Table in Pixel units
	&VM::tt_rcvt,		// RCVT[] Read Control Value Table entry
	&VM::tt_gc,		// 70 // GC[a] Get Coordinate projected onto the projection vector
	&VM::tt_gc,
	&VM::tt_scfs,	// SCFS[] Sets Coordinate From the Stack using projection vector and freedom vector
	&VM::tt_md,	// MD[a] Measure Distance
	&VM::tt_md,
	&VM::tt_mppem,	// MPPEM[] Measure Pixels Per EM
	&VM::tt_notimpl,
	&VM::tt_flipon,	// FLIPON[] set the auto FLIP Boolean to ON
	&VM::tt_flipoff,	// FLIPOFF[] set the auto FLIP Boolean to OFF
	&VM::tt_notimpl,
	&VM::tt_lt,	// LT[] Less Than
	&VM::tt_lteq,	// LTEQ[] Less Than or EQual
	&VM::tt_gt,	// GT[] Greater Than
	&VM::tt_gteq, // GTEQ[] Greater Than or EQual
	&VM::tt_eq,	// EQ[] EQual
	&VM::tt_neq,	// NEQ[] Not EQual
	&VM::tt_notimpl,
	&VM::tt_notimpl,
	&VM::tt_if,	// IF[] IF test
	&VM::tt_eif,
	&VM::tt_and,	// AND[] logical AND
	&VM::tt_or,	// OR[] logical OR
	&VM::tt_not,	// // NOT[] logical NOT
	&VM::tt_deltap1,	// DELTAP1[] DELTA exception P1
	&VM::tt_sdb,	// // SDB[] Set Delta Base in the graphics state
	&VM::tt_notimpl,
	&VM::tt_add,	// ADD[] ADD
	&VM::tt_sub,	// SUB[] SUBtract
	&VM::tt_div,	// DIV[] DIVide
	&VM::tt_mul,	// MUL[] MULtiply
	&VM::tt_abs, // 100 ABS[] ABSolute value
	&VM::tt_neg,	// NEG[] NEGate
	&VM::tt_notimpl,
	&VM::tt_notimpl,
	&VM::tt_round,	// ROUND[ab] ROUND value
	&VM::tt_round,
	&VM::tt_round,
	&VM::tt_round,
	&VM::tt_notimpl,
	&VM::tt_notimpl,
	&VM::tt_notimpl, // 110
	&VM::tt_notimpl,
	&VM::tt_wcvtf,	// WCVTF[] Write Control Value Table in Funits
	&VM::tt_deltap2,	// DELTAP2[] DELTA exception P2
	&VM::tt_deltap3,	// DELTAP3[] DELTA exception P3
	&VM::tt_deltac1,	// DELTAC1[] DELTA exception C1
	&VM::tt_deltac2,	// DELTAC2[] DELTA exception C2
	&VM::tt_deltac3,	// DELTAC3[] DELTA exception C3
	&VM::tt_sround,	// SROUND[] Super ROUND
	&VM::tt_notimpl,
	&VM::tt_notimpl, // 120
	&VM::tt_jrof,	// JROF[] Jump Relative On False
	&VM::tt_roff,	// ROFF[] Round OFF
	&VM::tt_notimpl,
	&VM::tt_rutg,	// RUTG[] Round Up To Grid
	&VM::tt_rdtg,	// RDTG[] Round Down To Grid
	&VM::tt_notimpl,
	&VM::tt_notimpl,
	&VM::tt_notimpl,
	&VM::tt_fliprgon,	// FLIPRGON[] FLIP RanGe ON
	&VM::tt_notimpl, // 130
	&VM::tt_notimpl,
	&VM::tt_notimpl,
	&VM::tt_scanctrl,
	&VM::tt_sdpvtl,	// SDPVTL[a] Set Dual Projection Vector To Line
	&VM::tt_sdpvtl,
	&VM::tt_getinfo,	// GETINFO[] GET INFOrmation	
	&VM::tt_notimpl,
	&VM::tt_roll,	// ROLL[] ROLL the top three stack elements
	&VM::tt_max,	// MAX[] MAXimum of top two stack elements
	&VM::tt_min, // MIN[] MINimum of top two stack elements
	&VM::tt_scantype,	// SCANTYPE[] SCANTYPE
	&VM::tt_instctrl,	// INSTCTRL[ ] INSTRuction execution ConTRoL
	&VM::tt_notimpl,
	&VM::tt_notimpl,
	&VM::tt_notimpl,
	&VM::tt_notimpl,
	&VM::tt_notimpl,
	&VM::tt_notimpl,
	&VM::tt_notimpl,
	&VM::tt_notimpl, // 150
	&VM::tt_notimpl,
	&VM::tt_notimpl,
	&VM::tt_notimpl,
	&VM::tt_notimpl,
	&VM::tt_notimpl,
	&VM::tt_notimpl,
	&VM::tt_notimpl,
	&VM::tt_notimpl,
	&VM::tt_notimpl,
	&VM::tt_notimpl, // 160
	&VM::tt_notimpl,
	&VM::tt_notimpl,
	&VM::tt_notimpl,
	&VM::tt_notimpl,
	&VM::tt_notimpl,
	&VM::tt_notimpl,
	&VM::tt_notimpl,
	&VM::tt_notimpl,
	&VM::tt_notimpl,
	&VM::tt_notimpl, // 170
	&VM::tt_notimpl,
	&VM::tt_notimpl,
	&VM::tt_notimpl,
	&VM::tt_notimpl,
	&VM::tt_notimpl,
	&VM::tt_pushb,
	&VM::tt_pushb,
	&VM::tt_pushb,
	&VM::tt_pushb,
	&VM::tt_pushb, // 180
	&VM::tt_pushb,
	&VM::tt_pushb,
	&VM::tt_pushb,
	&VM::tt_pushw, // 184
	&VM::tt_pushw,
	&VM::tt_pushw,
	&VM::tt_pushw,
	&VM::tt_pushw,
	&VM::tt_pushw,
	&VM::tt_pushw,	// 190
	&VM::tt_pushw,
	&VM::tt_mdrp,	// MDRP[abcde] Move Direct Relative PointI
	&VM::tt_mdrp,
	&VM::tt_mdrp,
	&VM::tt_mdrp,
	&VM::tt_mdrp,
	&VM::tt_mdrp,
	&VM::tt_mdrp,
	&VM::tt_mdrp,
	&VM::tt_mdrp,	// 200
	&VM::tt_mdrp,
	&VM::tt_mdrp,
	&VM::tt_mdrp,
	&VM::tt_mdrp,
	&VM::tt_mdrp,
	&VM::tt_mdrp,
	&VM::tt_mdrp,
	&VM::tt_mdrp,
	&VM::tt_mdrp,
	&VM::tt_mdrp,	// 210
	&VM::tt_mdrp,
	&VM::tt_mdrp,
	&VM::tt_mdrp,
	&VM::tt_mdrp,
	&VM::tt_mdrp,
	&VM::tt_mdrp,
	&VM::tt_mdrp,
	&VM::tt_mdrp,
	&VM::tt_mdrp,
	&VM::tt_mdrp,	// 220
	&VM::tt_mdrp,
	&VM::tt_mdrp,
	&VM::tt_mdrp,
	&VM::tt_mirp,	// MIRP[abcde] Move Indirect Relative PointI
	&VM::tt_mirp,
	&VM::tt_mirp,
	&VM::tt_mirp,
	&VM::tt_mirp,
	&VM::tt_mirp,
	&VM::tt_mirp,	// 230
	&VM::tt_mirp,
	&VM::tt_mirp,
	&VM::tt_mirp,
	&VM::tt_mirp,
	&VM::tt_mirp,
	&VM::tt_mirp,
	&VM::tt_mirp,
	&VM::tt_mirp,
	&VM::tt_mirp,
	&VM::tt_mirp,	// 240
	&VM::tt_mirp,
	&VM::tt_mirp,
	&VM::tt_mirp,
	&VM::tt_mirp,
	&VM::tt_mirp,
	&VM::tt_mirp,
	&VM::tt_mirp,
	&VM::tt_mirp,
	&VM::tt_mirp,
	&VM::tt_mirp,
	&VM::tt_mirp,
	&VM::tt_mirp,
	&VM::tt_mirp,
	&VM::tt_mirp,
	&VM::tt_mirp,
};

bool VM::next()
{
	if (m_ctx == NULL)
	{
		return false;
	}

	if (pc - m_ctx->instructionsData >= m_ctx->instructionsLength)
	{
		pc = m_ctx->return_pc;
		Caller* ctx = m_ctx;
		m_ctx = ctx->pCaller;
		delete ctx;
//		level--;
		return true;
		/*
		if (m_ctx == NULL)
			return false;
			*/
	}

	uint8 instr_code = *pc;

	if (instr_code == 0x1B)	// else
	{
//		level--;
		printlevel();
		LOG("else\n");
//		level++;
		pc++;

		while (1)
		{
			uint8 instr_code = *pc;
			if (instr_code == 0x59)	// eif
				break;

			skip_next(this);
		}

		ASSERT(*pc == 0x59);	// eif
		return true;//break;
	}

	if (instr_code == 0x59)	// eif
	{
	}

	printlevel();
	(this->*ttfuncs[instr_code])();
	LOG("\n");

	return true;
}

/////////////////////////////////////////////////////////////////
// GlyphData

GlyphData::GlyphData()
{
	flags = NULL;
	points = NULL;
	endPtsOfContours = NULL;
}

GlyphData::~GlyphData()
{
	delete [] flags;
	delete [] points;
	delete [] endPtsOfContours;
}

/////////////////////////////////////////////////////////////////
// FontFile

TTFontFile::TTFontFile()
{
//	m_bOpened = false;
	//m_filename = filename;

	m_familyName = null;

	m_prepData = NULL;
	m_prepLength = 0;
	m_cvtSize = 0;
	m_glyfTabData = NULL;
	m_glyphOffsets = NULL;
}

TTFontFile::~TTFontFile()
{
	if (m_glyfTabData)
	{
		delete [] m_glyfTabData;
	}
}

bool TTFontFile::ReadHeader(IO::Stream* m_fp)
{
	ASSERT(m_tablemap.size() == 0);

	OTFHeader header;
	if (m_fp->Read(&header, sizeof header) != sizeof header)
		return false;

	header.sfntVersion = BigEndian32(header.sfntVersion);

	if (header.sfntVersion != 0x00010000)
		return false;

	//printf("rh_1\n");

	header.numTables = BigEndian16(header.numTables);// Number of tables.  
//	USHORT  searchRange;// (Maximum power of 2 <= numTables) x 16. 
//	USHORT  entrySelector;// Log2(maximum power of 2 <= numTables). 
//	USHORT  rangeShift;// NumTables x 16-searchRange. 

	//printf("rh_2\n");

	OTFTable* table = new OTFTable[header.numTables];

	//printf("rh_3\n");

	for (int i = 0; i < header.numTables; i++)
	{
		m_fp->Read(&table[i], sizeof(OTFTable));

		//	LOG("%4.4s\n", &table[i].tag);

		table[i].tag = BigEndian32(table[i].tag);
		table[i].offset = BigEndian32(table[i].offset);
		table[i].length = BigEndian32(table[i].length);

		m_tablemap.insert(tytablemap::value_type(table[i].tag, &table[i]));
	}

	return true;
}

void TTFontFile::Init(IO::Stream* m_fp)
{
			//printf("_1\n");

	if (!ReadHeader(m_fp))
		THROW(-1);

			//printf("_2\n");

	OTFTable* pTable;

	OTF_HEAD head;
	pTable = FindTable('head');
	if (pTable)
	{
		m_fp->Seek(pTable->offset, System::IO::STREAM_SEEK_SET);

		m_fp->Read(&head, sizeof(head));
		uint32 version = BigEndian32(head.version);
		m_unitsPerEm = BigEndian16(head.unitsPerEm);
		m_macStyle = BigEndian16(head.macStyle);
	//	head.indexToLocFormat = BigEndian16(head.indexToLocFormat);
	//	head.glyphDataFormat = BigEndian16(head.glyphDataFormat);
	//	ASSERT(head.glyphDataFormat == 0);

		uint32 magicNumber = BigEndian32(head.magicNumber);
		if (magicNumber != 0x5F0F3CF5)
			THROW(-1);

		if (version != 0x00010000)
			THROW(-1);
	}
	else
		THROW(-1);

	//printf("_3\n");

	pTable = FindTable('name');
	if (pTable)
	{
		m_fp->Seek(pTable->offset, System::IO::STREAM_SEEK_SET);

		OTF_NAME name;
		m_fp->Read(&name, sizeof(name));
		ASSERT(name.format == 0);
		name.count = BigEndian16(name.count);
		name.stringOffset = BigEndian16(name.stringOffset);

		int i;

		OTFNameRecord* nameRecord = new OTFNameRecord[name.count];
		for (i = 0; i < name.count; i++)
		{
			m_fp->Read(&nameRecord[i], sizeof(OTFNameRecord));
			nameRecord[i].platformID = BigEndian16(nameRecord[i].platformID);
			nameRecord[i].platformSpecificID = BigEndian16(nameRecord[i].platformSpecificID);
			nameRecord[i].nameID = BigEndian16(nameRecord[i].nameID);
			nameRecord[i].offset = BigEndian16(nameRecord[i].offset);
			nameRecord[i].length = BigEndian16(nameRecord[i].length);
		}

		char* stringData = new char[pTable->length - name.stringOffset];
		m_fp->Read(stringData, pTable->length - name.stringOffset);

	//printf("_4\n");

		for (i = 0; i < name.count; i++)
		{
			WCHAR* str;

			if (nameRecord[i].platformID == 0)	// unicode
			{
				int clen = nameRecord[i].length / 2;
				str = new WCHAR[clen+1];
				int c;
				for (c = 0; c < clen; c++)
				{
					str[c] = BigEndian16(((short*)(stringData + nameRecord[i].offset))[c]);
				}
				str[c] = 0;
			}
			else
			{
				int clen = nameRecord[i].length;
				str = new WCHAR[clen+1];
				int c;
				for (c = 0; c < clen; c++)
				{
					str[c] = ((char*)(stringData + nameRecord[i].offset))[c];
				}
				str[c] = 0;
			}

			if (nameRecord[i].nameID == 1)	// Just record the name with id 1 ?
			{
				if (m_familyName == null)//->Length() == 0)
				{
						//printf("_j3\n");

					m_familyName = string_copy(str);

						//printf("_j4\n");
				}
			}

			delete str;
		}

	//printf("_5\n");
	}
	else
		THROW(-1);
}

/*
FontFamily::~FontFamily()
{
	if (m_prepData)
	{
		delete m_prepData;
		m_prepData = NULL;
	}

	if (m_glyfTabData)
	{
		delete m_glyfTabData;
		m_glyfTabData = NULL;
	}

	if (m_cvt)
	{
		delete m_cvt;
		m_cvt = NULL;
	}
}
*/

void TTFontFile::Init2(IO::Stream* m_fp)
{
	TRY
	{
		ReadHeader(m_fp);

	//	return;	// TODO remove

		OTFTable* pTable;

		OTF_HEAD head;
		pTable = FindTable('head');
		if (pTable)
		{
			m_fp->Seek(pTable->offset, System::IO::STREAM_SEEK_SET);

			m_fp->Read(&head, sizeof(head));
			m_unitsPerEm = BigEndian16(head.unitsPerEm);
			m_macStyle = BigEndian16(head.macStyle);
			head.indexToLocFormat = BigEndian16(head.indexToLocFormat);
			head.glyphDataFormat = BigEndian16(head.glyphDataFormat);

			ASSERT(head.glyphDataFormat == 0);
		}
		else
		{
			ASSERT(0);
			THROW(-1);
		}

		pTable = FindTable('maxp');
		if (pTable)
		{
			m_fp->Seek(pTable->offset, System::IO::STREAM_SEEK_SET);
			m_fp->Read(&m_maxp, sizeof(OTFMaxProfileHeader));
			m_maxp.numGlyphs = BigEndian16(m_maxp.numGlyphs);
			m_maxp.maxStorage = BigEndian16(m_maxp.maxStorage);
			m_maxp.maxFunctionDefs = BigEndian16(m_maxp.maxFunctionDefs);
			m_maxp.maxPoints = BigEndian16(m_maxp.maxPoints);
			m_maxp.maxContours = BigEndian16(m_maxp.maxContours);
			m_maxp.maxTwilightPoints = BigEndian16(m_maxp.maxTwilightPoints);
		}
		else
		{
			ASSERT(0);
			THROW(-1);
		}

		pTable = FindTable('cvt ');
		if (pTable)
		{
			ASSERT((pTable->length & (sizeof(FWord)-1)) == 0);
			m_cvtSize = pTable->length / sizeof(FWord);
			m_cvt = new FWord[m_cvtSize];

			m_fp->Seek(pTable->offset, System::IO::STREAM_SEEK_SET);
			m_fp->Read(m_cvt, m_cvtSize*2);

			for (int i = 0; i < m_cvtSize; i++)
			{
				m_cvt[i] = BigEndian16(m_cvt[i]);
			}
			LOG("cvt[23]=%d\n", m_cvt[23]);
		}
		else
		{
			m_cvtSize = NULL;
			m_cvt = NULL;
		/*
			THROW(-1);
		*/
		}

		pTable = FindTable('hhea');	// Horizontal overall
		if (pTable)
		{
			m_fp->Seek(pTable->offset, System::IO::STREAM_SEEK_SET);
			m_fp->Read(&hhea, sizeof(hhea));
			hhea.numOfLongHorMetrics = BigEndian16(hhea.numOfLongHorMetrics);
			if (!(hhea.numOfLongHorMetrics > 0))
			{
				ASSERT("hhea.numOfLongHorMetrics must be greater than 0\n");
				ASSERT(0);
				THROW(-1);
			}
			hhea.ascent = BigEndian16(hhea.ascent);
			hhea.descent = BigEndian16(hhea.descent);
		}
		else
		{
			ASSERT(0);
			THROW(-1);
		}

		pTable = FindTable('hmtx');	// Horizontal per-glyph
		if (pTable)
		{
			m_fp->Seek(pTable->offset, System::IO::STREAM_SEEK_SET);
			uint8* data = new uint8[pTable->length];
			m_fp->Read(data, pTable->length);

			m_horMetrics = new OTF_HORMETRIC[m_maxp.numGlyphs];

			uint8* p = data;

			uint16 advanceWidth = 0;
			int i;
			for (i = 0; i < hhea.numOfLongHorMetrics; i++)
			{
				OTF_HORMETRIC* hm = (OTF_HORMETRIC*)p;
				m_horMetrics[i].advanceWidth = advanceWidth = BigEndian16(hm->advanceWidth);
				m_horMetrics[i].leftSideBearing = BigEndian16(hm->leftSideBearing);
				p += sizeof(OTF_HORMETRIC);
			}

			for (; i < m_maxp.numGlyphs; i++)
			{
				m_horMetrics[i].advanceWidth = advanceWidth;
				m_horMetrics[i].leftSideBearing = BigEndian16(*(FWord*)p); p += 2;
			}
			
			delete data;
		}
		else
		{
			ASSERT(0);
			THROW(-1);
		}

		pTable = FindTable('loca');
		if (pTable)
		{
			m_fp->Seek(pTable->offset, System::IO::STREAM_SEEK_SET);
			if (head.indexToLocFormat == 0)	// short offsets
			{
				int numGlyphs = pTable->length / 2;

				if (numGlyphs != m_maxp.numGlyphs+1)
				{
					ASSERT(0);
					THROW(-1);
				}

				m_glyphOffsets = new uint32[numGlyphs];

				uint16* offsets = new uint16[numGlyphs];

				m_fp->Read(offsets, 2*numGlyphs);
				for (int i = 0; i < numGlyphs; i++)
				{
					m_glyphOffsets[i] = BigEndian16(offsets[i]) * 2;
				}

				delete [] offsets;
			}
			else if (head.indexToLocFormat == 1)	// long offsets
			{
				int numGlyphs = pTable->length / 4;

				if (numGlyphs != m_maxp.numGlyphs+1)
				{
					ASSERT(0);
					THROW(-1);
				}

				m_glyphOffsets = new uint32[numGlyphs];

				m_fp->Read(m_glyphOffsets, 4*numGlyphs);
				for (int i = 0; i < numGlyphs; i++)
				{
					m_glyphOffsets[i] = BigEndian32(m_glyphOffsets[i]);
				}
			}
		}
		else
			THROW(-1);

		pTable = FindTable('glyf');
		if (pTable)
		{
			m_fp->Seek(pTable->offset, System::IO::STREAM_SEEK_SET);
			uint8* data = new uint8[pTable->length];
			if (m_fp->Read(data, pTable->length) != pTable->length)
				THROW(-1);

			m_glyfTabData = data;

			/*
			Glyph2* glyph = new Glyph2;

			glyph->Desc = *(OTFGlyphDesc*)data;

			glyph->Desc.numberOfContours = BigEndian16(glyph->Desc.numberOfContours);
			glyph->Desc.xMax = BigEndian16(glyph->Desc.xMax);
			glyph->Desc.yMax = BigEndian16(glyph->Desc.yMax);
			glyph->Desc.xMin = BigEndian16(glyph->Desc.xMin);
			glyph->Desc.yMin = BigEndian16(glyph->Desc.yMin);
			*/
		}
		else
			THROW(-1);

		pTable = FindTable('cmap');
		if (pTable)
		{
			m_fp->Seek(pTable->offset, System::IO::STREAM_SEEK_SET);
			uint8* data = new uint8[pTable->length];
			m_fp->Read(data, pTable->length);

			uint8* p = data;

			uint16 version = BigEndian16(*(uint16*)p); p += 2;
			uint16 numberSubtables = BigEndian16(*(uint16*)p); p += 2;

			ASSERT(version == 0);

			OTFCmapSubTable* subtables = (OTFCmapSubTable*)p;

			{
				for (int i = 0; i < numberSubtables; i++)
				{
					OTFCmapSubTable* subtable = (OTFCmapSubTable*)p;
					subtable->platformID = BigEndian16(subtable->platformID);
					subtable->platformSpecificID = BigEndian16(subtable->platformSpecificID);
					subtable->offset = BigEndian32(subtable->offset);

					p += sizeof(OTFCmapSubTable);
				}
			}

			/*
			OTFCmapSubTable* subtable = &subtables[0];
			int i;
			for (i = 0; i < numberSubtables; i++)
			{
				if (subtables[i].platformID == 0)	// Unicode
				{
					subtable = &subtables[i];
					break;
				}
			}
			*/

			for (int i = 0; i < numberSubtables; i++)
			{
				if (subtables[i].platformID == 3/* || subtables[i].platformID == 0*/)	// Windows
				{
					OTFCmapSubTable* subtable = &subtables[i];

					p = data + subtable->offset;

					uint16 format = BigEndian16(*(uint16*)p); p += 2;

				//	printf("format: %d\n", format);

					if (format == 0)
					{
						uint16 length = BigEndian16(*(uint16*)p); p += 2;
						uint16 language = BigEndian16(*(uint16*)p); p += 2;

						for (int c = 0; c < 256; c++)
						{
							uint8 glyph = *p++;
							m_cmap.insert(tycmap::value_type(c, glyph));
						}
					}
					else if (format == 2)
					{
						ASSERT(0);
					}
					else if (format == 4)
					{
						uint16 length = BigEndian16(*(uint16*)p); p += 2;
						uint16 language = BigEndian16(*(uint16*)p); p += 2;

					//	printf("HERESRE\n");

						uint16 segCountX2 = BigEndian16(*(uint16*)p); p += 2;
						uint16 segCount = segCountX2/2;
						uint16 searchRange = BigEndian16(*(uint16*)p); p += 2;
						uint16 entrySelector = BigEndian16(*(uint16*)p); p += 2;
						uint16 rangeShift = BigEndian16(*(uint16*)p); p += 2;

						int i;

						uint16* endCode = (uint16*)p;//new uint16[segCount];
						for (i = 0; i < segCount; i++)
						{
							endCode[i] = BigEndian16(*(uint16*)p); p += 2;
						}
						uint16 reservedPad = *(uint16*)p; p += 2;
						ASSERT(reservedPad == 0);

						uint16* startCode = (uint16*)p;//new uint16[segCount];
						for (i = 0; i < segCount; i++)
						{
							startCode[i] = BigEndian16(*(uint16*)p); p += 2;
						}

						uint16* idDelta = (uint16*)p;//new uint16[segCount];
						for (i = 0; i < segCount; i++)
						{
							idDelta[i] = BigEndian16(*(uint16*)p); p += 2;
						}

						uint16* idRangeOffset = (uint16*)p;//new uint16[segCount];
						for (i = 0; i < segCount; i++)
						{
							idRangeOffset[i] = BigEndian16(*(uint16*)p); p += 2;
						}

						uint16* glyphIndexArray = (uint16*)p;
						//for (

						for (i = 0; i < segCount; i++)
						{
							//ASSERT(idRangeOffset[i] == 0);

							if (idRangeOffset[i] != 0)
							{
								for (int code = startCode[i]; code <= endCode[i]; code++)
								{
								//	uint16* glyphIndexAddress = idRangeOffset[i] + /*2 **/ (code - startCode[i]) + &idRangeOffset[i];

									uint16* glyphIndexAddress = &idRangeOffset[i] + idRangeOffset[i] / 2 + (code - startCode[i]);
									ASSERT(glyphIndexAddress >= glyphIndexArray);

									uint16 glyph = BigEndian16(*glyphIndexAddress);
									ASSERT(glyph < m_maxp.numGlyphs);
									m_cmap.insert(tycmap::value_type(code, glyph));
								}
							}
							else
							{
								for (int code = startCode[i]; code <= endCode[i]; code++)
								{
								//	uint16 glyphIndex = idRangeOffset[code]/2 + (c - startCode[code]) + idRangeOffset[code];
									uint16 glyph = idDelta[i] + code;
									m_cmap.insert(tycmap::value_type(code, glyph));
								}
							}
						}
					}
					else if (format == 12)
					{
						p += 2;
						uint32 length = BigEndian32(*(uint16*)p); p += 4;
						uint32 language = BigEndian32(*(uint16*)p); p += 4;

						uint32 nGroups = BigEndian32(*(uint32*)p); p += 4;

						for (uint32 n = 0; n < nGroups; n++)
						{
							uint32 startCharCode = BigEndian32(*(uint32*)p); p += 4;
							uint32 endCharCode = BigEndian32(*(uint32*)p); p += 4;
							uint32 startGlyphCode = BigEndian32(*(uint32*)p); p += 4;

							if (startCharCode >= 0x1000)
							{
								MessageBeep(-1);
							}

							for (uint32 code = startCharCode; code <= endCharCode; code++)
							{
								uint32 glyph = startGlyphCode + code - startCharCode;
								pair<tycmap::iterator, bool> p = m_cmap.insert(tycmap::value_type(code, glyph));
							}
						}
					}
					else
						ASSERT(0);
				}
			}
		}
		else
			THROW(-1);

		pTable = FindTable('bsln');
		if (pTable)
		{
			m_fp->Seek(pTable->offset, System::IO::STREAM_SEEK_SET);

			OTFBaseline baseline;
			m_fp->Read(&baseline, sizeof(OTFBaseline));
			baseline.version = BigEndian32(baseline.version);
			baseline.format = BigEndian16(baseline.format);
			baseline.defaultBaseline = BigEndian16(baseline.defaultBaseline);
		}

		pTable = FindTable('fpgm');
		if (pTable)
		{
			m_fp->Seek(pTable->offset, System::IO::STREAM_SEEK_SET);
			m_fontPrgData = new uint8[pTable->length];
			m_fontPrgLength = pTable->length;

			m_fp->Read(m_fontPrgData, pTable->length);
		}
		else
		{
			m_fontPrgData = NULL;
			m_fontPrgLength = 0;
		}

		pTable = FindTable('prep');
		if (pTable)
		{
			m_fp->Seek(pTable->offset, System::IO::STREAM_SEEK_SET);
			m_prepData = new uint8[pTable->length];
			m_prepLength = pTable->length;

			m_fp->Read(m_prepData, pTable->length);
		}
		else
		{
			m_prepData = NULL;
			m_prepLength = 0;
		}

		if (true)	// TODO, do this
		{
			// Do this once for the font
			if (m_fontPrgData)
			{
				VM vm(this, NULL);
				vm.pc = m_fontPrgData;

				while (vm.pc - m_fontPrgData < m_fontPrgLength)
				{
					uint8 instr_code = *vm.pc;
					printlevel();
					(vm.*VM::ttfuncs[instr_code])();
					LOG("\n");
				}
				ASSERT(vm.m_stack.GetSize() == 0);
			}
		}
	}
	CATCH(int)
	{
		printf("Error");
	}
}

/*
bool FontFile::OpenFile()
{
	ASSERT(m_fp == NULL);
	m_fp = fopen(m_filename.c_str(), "rb");
	ASSERT(m_fp);
}

void FontFile::CloseFile()
{
	ASSERT(m_fp);
	fclose(m_fp);
	m_fp = NULL;
}
*/

uint32 TTFontFile::CharToGlyph(uint32 c) const
{
	ASSERT(this);

	/*
	if (c >= 0x10000)
	{
		MessageBeep(-1);
	}
	*/

	uint32 glyphIndex;

	tycmap::const_iterator ci = m_cmap.find(c);
	if (ci != m_cmap.end())
	{
		glyphIndex = (*ci).second;
	}
	else
	{
		glyphIndex = 0;
	}

	return glyphIndex;
}

Glyph2* TTFontFile::GetGlyph(uint32 glyphIndex)
{
	ASSERT(this);

	tyglyphmap::iterator it = m_glyphs.find(glyphIndex);
	if (it != m_glyphs.end())
	{
		return (*it).second;
	}
	else
	{
		Glyph2* pGlyph = ParseGlyph(glyphIndex);
		if (pGlyph)
		{
			m_glyphs.insert(tyglyphmap::value_type(glyphIndex, pGlyph));
		}
		return pGlyph;
	}
}

Glyph2* TTFontFile::ParseGlyph(uint32 glyphIndex)
{
	ASSERT(this);

	if (m_glyfTabData == NULL)
		return NULL;

	int len = m_glyphOffsets[glyphIndex+1] - m_glyphOffsets[glyphIndex];
	if (len == 0)
		return NULL;

	TRY
	{
		uint8* data = m_glyfTabData + m_glyphOffsets[glyphIndex];
		uint8* end = data+len;
		uint8* p = data;

		Glyph2* glyph = new Glyph2;

		glyph->Desc = *(OTFGlyphDesc*)p; p += sizeof(OTFGlyphDesc);

		glyph->Desc.numberOfContours = BigEndian16(glyph->Desc.numberOfContours);
		glyph->Desc.xMax = BigEndian16(glyph->Desc.xMax);
		glyph->Desc.yMax = BigEndian16(glyph->Desc.yMax);
		glyph->Desc.xMin = BigEndian16(glyph->Desc.xMin);
		glyph->Desc.yMin = BigEndian16(glyph->Desc.yMin);

		if (glyph->Desc.numberOfContours > 0)	// single
		{
			glyph->data.endPtsOfContours = new uint16[glyph->Desc.numberOfContours];

			{
				for (int c = 0; c < glyph->Desc.numberOfContours; c++)
				{
					if (p > end-2) THROW(-1);
					glyph->data.endPtsOfContours[c] = BigEndian16(*(uint16*)p);
					if (glyph->data.endPtsOfContours[c] >= m_maxp.maxPoints)
						THROW(-1);
					p += 2;
				}
			}

			if (p > end-2) THROW(-1);
			glyph->instructionsLength = BigEndian16(*(uint16*)p); p += 2;

			if (p > end-glyph->instructionsLength) THROW(-1);
			glyph->instructionsData = new uint8[glyph->instructionsLength];
			memcpy(glyph->instructionsData, p, glyph->instructionsLength);
			p += glyph->instructionsLength;

			glyph->data.flags = new uint8[m_maxp.maxPoints];

			int c;

			int n = 0;
			for (c = 0; c < glyph->Desc.numberOfContours; c++)
			{
				while (n <= glyph->data.endPtsOfContours[c])
				{
					if (p > end-1) THROW(-1);
					uint8 flag = *p++;

					glyph->data.flags[n++] = flag;

					if (flag & 0x8)
					{
						// I'm not sure if this can cross a contour boundary or not ?
						if (p > end-1) THROW(-1);
						uint8 count = *p++;
						for (int i = 0; i < count; i++)
						{
							glyph->data.flags[n++] = flag;
						}
					}
				}
			}

			/*
			{
				for (int i = 0; i <= glyph->data.endPtsOfContours[0]; i++)
				{
					ATLTRACE("%d:%d\n", i, glyph->data.flags[i]);
				}
			}
			*/


			int npoints = n;
			glyph->data.points = new LDraw::PointI[m_maxp.maxPoints];

			int x = 0;
			n = 0;
			for (c = 0; c < glyph->Desc.numberOfContours; c++)
			{
				for (; n <= glyph->data.endPtsOfContours[c]; n++)
				{
					if (glyph->data.flags[n] & 2)	// 8bit
					{
						if (p > end-1) THROW(-1);
						int d = *(uint8*)p; p += 1;

						if ((glyph->data.flags[n] & 16) == 0)	// sign bit
						{
							d = -d;
						}

						x += d;
					}
					else	// 16bit
					{
						if (glyph->data.flags[n] & 16)
						{
							x = x;
						}
						else
						{
							if (p > end-2) THROW(-1);
							x += (int16)BigEndian16(*(int16*)p); p += 2;
						}
					}
					glyph->data.points[n].X = x;
				}
			}

			int y = 0;
			n = 0;
			for (c = 0; c < glyph->Desc.numberOfContours; c++)
			{
				for (; n <= glyph->data.endPtsOfContours[c]; n++)
				{
					if (glyph->data.flags[n] & 4)	// 8bit
					{
						if (p > end-1) THROW(-1);
						int d = *(uint8*)p; p += 1;

						if ((glyph->data.flags[n] & 32) == 0)	// sign bit
						{
							d = -d;
						}

						y += d;
					}
					else	// 16bit
					{
						if (glyph->data.flags[n] & 32)
						{
							y = y;
						}
						else
						{
							if (p > end-2) THROW(-1);
							y += (int16)BigEndian16(*(int16*)p); p += 2;
						}
					}
					glyph->data.points[n].Y = y;
				}
			}

			// Create 2 additional points
			{
				glyph->data.points[npoints].X = 0;//m_horMetrics[glyphIndex].leftSideBearing;// * 64 * m_emSize / m_unitsPerEm + 0.5;
				glyph->data.points[npoints].Y = 0;

				glyph->data.points[npoints+1].X = /*m_horMetrics[glyphIndex].leftSideBearing +*/ m_horMetrics[glyphIndex].advanceWidth;// * 64 * m_emSize / m_unitsPerEm + 0.5;
				glyph->data.points[npoints+1].Y = 0;
			}

			glyph->npoints = npoints+2;

			if ((p-data)&1) p++;	// pad to even number of bytes
		//	ASSERT( p - data == m_glyphOffsets[glyphIndex+1] - m_glyphOffsets[glyphIndex]);
	/*
			if (fplog)
			{
				fclose(fplog);
				fplog = NULL;
			}
	*/

			return glyph;
		}
		else	// multiple countours
		{
			// TODO
			glyph->instructionsData = NULL;
			glyph->instructionsLength = 0;

			glyph->data.points = new LDraw::PointI[m_maxp.maxPoints];
			glyph->npoints = 2;

			glyph->data.flags = new uint8[m_maxp.maxPoints];

			return glyph;
		}
	}
	CATCH(int)
	{
		TRACE("Error in parsing glyph\n");
	}

	return NULL;
}

/////////////////////////////////////////////////////////////////
// Glyph

Glyph::Glyph()
{
	pPath = NULL;
}

Glyph::~Glyph()
{
	delete pPath;
}

/////////////////////////////////////////////////////////////////
// Font

TTFont::TTFont(TTFontFile* fontFile, REAL emSize)
{
	if (fontFile == NULL)
		THROW(-1);

	m_fontFile = fontFile;

//	m_glyphshapes = new Glyph*[m_fontFile->m_maxp.numGlyphs];
//	memset(m_glyphshapes, 0, m_fontFile->m_maxp.numGlyphs*sizeof(Glyph*));

	m_twilightPoints = new LDraw::PointI[m_fontFile->m_maxp.maxTwilightPoints];
	m_twilightPoints2 = new LDraw::PointI[m_fontFile->m_maxp.maxTwilightPoints];

	m_pStorage = new int32[m_fontFile->m_maxp.maxStorage];

	m_emSize = emSize;

	m_cvt = new FWord[m_fontFile->m_cvtSize];
	memcpy(m_cvt, m_fontFile->m_cvt, m_fontFile->m_cvtSize*sizeof(FWord));

		// Do this once first and each time size or matrix changes
//#if 0
	{
		for (int i = 0; i < m_fontFile->m_cvtSize; i++)
		{
			if (m_cvt[i] >= 0)
				m_cvt[i] = (int)(m_cvt[i] * 64 * m_emSize / m_fontFile->m_unitsPerEm + 0.5);
			else
				m_cvt[i] = -(int)(-m_cvt[i] * 64 * m_emSize / m_fontFile->m_unitsPerEm + 0.5);

		//	m_cvtUnit[i] = 1;
		}
	}

	if (true)
	{
	if (m_fontFile->m_prepData)
	{
		VM vm(m_fontFile, this);

		vm.m_ctx = new VM::Caller;
		vm.m_ctx->instructionsData = m_fontFile->m_prepData;
		vm.m_ctx->instructionsLength = m_fontFile->m_prepLength;
		vm.m_ctx->return_pc = NULL;

		vm.pc = m_fontFile->m_prepData;

		LOG("Prep Instructions\n");

		TRY
		{
			while (vm.next())
				;

		/*
		while (vm.pc - m_prepData < m_prepLength)
		{
			uint8 instr_code = *vm.pc;
			printlevel();
			ttfuncs[instr_code](&vm);
			LOG("\n");
		}
		*/
			ASSERT(vm.m_stack.GetSize() == 0);
		}
		CATCH(int)
		{
		}

		memcpy(m_cvt, vm.m_cvt, m_fontFile->m_cvtSize*sizeof(FWord));
		memcpy(m_pStorage, vm.m_pStorage, m_fontFile->m_maxp.maxStorage*sizeof(int32));

#if 0
		defaultGlyphState = vm.m_state;
#endif
	}
//#endif
	}

	{
		LOG("CVT:\n");
		for (int i = 0; i < m_fontFile->m_cvtSize; i++)
		{
			LOG("%d:\t%.2f\t\t%8d\t\t%d\n", i, m_cvt[i] / 64.0, m_cvt[i], (int)(64 * m_emSize));
		}
		LOG("\n");
	//	fclose(fplog);
	}
}

TTFont::~TTFont()
{
	if (m_cvt)
	{
		delete m_cvt;
		m_cvt = NULL;
	}
}

void TTFont::ScalePoints(const Glyph2* glyph2, const LDraw::PointI* orgpoints, LDraw::PointI* newpoints) const
{
	//LDraw::PointI* orgpoints = glyph2->data.points;

	for (int i = 0; i < glyph2->npoints; i++)
	{
		if (orgpoints[i].X >= 0)
			newpoints[i].X = orgpoints[i].X * 64 * m_emSize / m_fontFile->m_unitsPerEm + 0.5;
		else
			newpoints[i].X = -(int)(-orgpoints[i].X * 64 * m_emSize / m_fontFile->m_unitsPerEm + 0.5);

		if (orgpoints[i].Y >= 0)
			newpoints[i].Y = orgpoints[i].Y * 64 * m_emSize / m_fontFile->m_unitsPerEm + 0.5;
		else
			newpoints[i].Y = -(int)(-orgpoints[i].Y * 64 * m_emSize / m_fontFile->m_unitsPerEm + 0.5);
	}
}

VM* TTFont::SetupGlyphVM(const Glyph2* glyph2)
{
	VM* vm = new VM(m_fontFile, this);

	vm->glyphDesc = &glyph2->Desc;
	vm->endPtsOfContours = glyph2->data.endPtsOfContours;

	vm->flags = new uint8[m_fontFile->m_maxp.maxPoints];
	memcpy(vm->flags, glyph2->data.flags, m_fontFile->m_maxp.maxPoints);

#if 0
	vm->bpoints[1] = new uint8[m_fontFile->m_maxp.maxPoints];
	memset(vm->bpoints[1], 0, m_fontFile->m_maxp.maxPoints);
#endif

//	vm->orgpoints[1] = glyph2->data.points;
	vm->orgpoints[1] = new LDraw::PointI[m_fontFile->m_maxp.maxPoints];
	//memcpy(vm->orgpoints[1], glyph2->data.points, sizeof(LDraw::PointI)*m_fontFile->m_maxp.maxPoints);

	// Scale
	{
		LDraw::PointI* orgpoints = glyph2->data.points;

		//if (orgpoints)
			ScalePoints(glyph2, orgpoints, vm->orgpoints[1]);
		/*
		for (int i = 0; i < glyph2->npoints; i++)
		{
			if (orgpoints[i].X >= 0)
				vm->orgpoints[1][i].X = orgpoints[i].X * 64 * m_emSize / m_fontFile->m_unitsPerEm + 0.5;
			else
				vm->orgpoints[1][i].X = -(int)(-orgpoints[i].X * 64 * m_emSize / m_fontFile->m_unitsPerEm + 0.5);

			if (orgpoints[i].Y >= 0)
				vm->orgpoints[1][i].Y = orgpoints[i].Y * 64 * m_emSize / m_fontFile->m_unitsPerEm + 0.5;
			else
				vm->orgpoints[1][i].Y = -(int)(-orgpoints[i].Y * 64 * m_emSize / m_fontFile->m_unitsPerEm + 0.5);
		}
		*/
	}

	// Initialize the new points to the same values as the old points
	vm->newpoints[1] = new LDraw::PointI[m_fontFile->m_maxp.maxPoints];
	memcpy(vm->newpoints[1], vm->orgpoints[1], sizeof(LDraw::PointI)*m_fontFile->m_maxp.maxPoints);

	{	// round that additional point ?
		State state;
		vm->newpoints[1][glyph2->npoints-1].X = state.round(vm->newpoints[1][glyph2->npoints-1].X);
	}

	vm->gpointsCount[1] = m_fontFile->m_maxp.maxPoints;//npoints;
//	vm.m_state = defaultGlyphState;
	vm->m_state.zp0 = 1;
	vm->m_state.zp1 = 1;
	vm->m_state.zp2 = 1;

	vm->m_ctx = new VM::Caller;
	vm->m_ctx->instructionsData = glyph2->instructionsData;
	vm->m_ctx->instructionsLength = glyph2->instructionsLength;
	vm->m_ctx->return_pc = NULL;

	vm->pc = glyph2->instructionsData;

	return vm;
}

Glyph* TTFont::NormalizeGlyph(const Glyph2* pGlyph2, const uint8* flags, const LDraw::PointI* points, const uint16* endPtsOfContours, int numberOfContours)
{
	LDraw::GraphicsPathF* path = new LDraw::GraphicsPathF(LDraw::FillModeWinding);

	if (numberOfContours < 0)
		return NULL;

	LType::GlyphData ndata;
	ndata.flags = new uint8[GetFile()->m_maxp.maxPoints*2];
	ndata.points = new LDraw::PointI[GetFile()->m_maxp.maxPoints*2];
	ndata.endPtsOfContours = new uint16[/*vm->glyphDesc->*/numberOfContours];
	if (ndata.endPtsOfContours == NULL)
		return NULL;

	int npoints2;
	{
		int n2 = 0;
		int n = 0;
		for (int c = 0; c < /*vm->glyphDesc->*/numberOfContours; c++)
		{
			for (; n <= /*vm->*/endPtsOfContours[c]; n++)
			{
			//	endPtsOfContours[i] = n2;

				if (/*vm->*/flags[n] & 1)	// oncurve
				{
					ndata.flags[n2] = 1;
					ndata.points[n2] = points[n];//vm->get_newpoint(1, n);
					n2++;
				}
				else
				{
					ndata.flags[n2] = 0;
					ndata.points[n2] = points[n];//vm->get_newpoint(1, n);
					n2++;

					if (n+1 <= /*vm->*/endPtsOfContours[c])
					{
						if (!(/*vm->*/flags[n+1] & 1))	// consecutive offpoint
						{
							ndata.points[n2].X = points[n].X + (points[n+1].X - points[n].X) / 2;
							ndata.points[n2].Y = points[n].Y + (points[n+1].Y - points[n].Y) / 2;
							ndata.flags[n2] = 1;
							n2++;
						}
					}
				}
				ndata.endPtsOfContours[c] = n2-1;
			}
		}
		npoints2 = n2;
	}

//	LOG("%d\n", ndata.endPtsOfContours[0]);

	// Convert a GlyphData to a GraphicsPathF, GlyphData must be normalized (i.e, no consecutive off-curve points)
	{
		int n = 0;
		for (int c = 0; c < /*vm->glyphDesc->*/numberOfContours; c++)
		{
#if 0
			path->StartFigure();
#endif
			int startx = ndata.points[n].X;
			int starty = ndata.points[n].Y;

			int x = startx;
			int y = starty;

			path->AddMove(LDraw::PointF(x, y));

			n++;

			for (; n <= ndata.endPtsOfContours[c]; )
			{
				if (ndata.flags[n] & 1)	// on curve
				{
					path->AddLine(LDraw::PointF(ndata.points[n].X, ndata.points[n].Y));
				//	path->AddLine(x, y, points[n].X, points[n].Y);

					x = ndata.points[n].X;
					y = ndata.points[n].Y;
					n++;
				}
				else
				{
					LDraw::PointD quad[3];
					quad[0] = LDraw::PointD(x, y);
					quad[1] = LDraw::PointD(ndata.points[n].X, ndata.points[n].Y);

					if (n < ndata.endPtsOfContours[c])
					{
						quad[2] = LDraw::PointD(ndata.points[n+1].X, ndata.points[n+1].Y);
						ASSERT(ndata.flags[n+1] & 1);	// It must be normalized
						n += 2;
					}
					else
					{
						quad[2] = LDraw::PointD(startx, starty);

					//	char str[256];
					//	sprintf("%d,%d", startx, starty);

						n += 1;
					}


#if 0
					LDraw::PointD cubic[4];
					LDraw::MakeBezierFromQBSpline(cubic, quad);

				//	path->AddBezier((float)cubic[0].X, (float)cubic[0].Y, (float)cubic[1].X, (float)cubic[1].Y, (float)cubic[2].X, (float)cubic[2].Y, (float)cubic[3].X, (float)cubic[3].Y);
					path->AddBezier(LDraw::PointF(cubic[1].X, (float)cubic[1].Y), LDraw::PointF(cubic[2].X, (float)cubic[2].Y), LDraw::PointF(cubic[3].X, (float)cubic[3].Y));

					x = cubic[3].X;
					y = cubic[3].Y;
#else
					path->AddBezier2(quad[1].X, quad[1].Y, quad[2].X, quad[2].Y);
					x = quad[2].X;
					y = quad[2].Y;
#endif
				}
			}
			path->CloseFigure();
		}
	}

	TTFontFile* pFile = GetFile();
	REAL size = GetSize();

	Glyph* pGlyph = new Glyph;
	pGlyph->minX = pGlyph2->Desc.xMin * size / pFile->m_unitsPerEm;
	pGlyph->minY = pGlyph2->Desc.yMin * size / pFile->m_unitsPerEm;
	pGlyph->maxX = pGlyph2->Desc.xMax * size / pFile->m_unitsPerEm;
	pGlyph->maxY = pGlyph2->Desc.yMax * size / pFile->m_unitsPerEm;

	pGlyph->pPath = path;

	return pGlyph;
}

}	// LType
}	// System
