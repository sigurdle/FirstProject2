class CPDFEExtGState;

typedef struct _t_FixedMatrix
{
	double a;
	double b;
	double c;
	double d;
	double h;
	double v;
}
ASFixedMatrix, *ASFixedMatrixP;

typedef struct _t_PDEFontAttrs
{
	CUString/*ASAtom*/ name;
	CUString/*ASAtom*/ type;
	CUString/*ASAtom*/ charSet;
	CUString/*ASAtom*/ encoding;
	ASUns32 flags;
//	ASFixedRect fontBBox;
	ASInt16 missingWidth;
	ASInt16 stemV;
	ASInt16 stemH;
	ASInt16 capHeight;
	ASInt16 xHeight;
	ASInt16 ascent;
	ASInt16 descent;
	ASInt16 leading;
	ASInt16 maxWidth;
	ASInt16 avgWidth;
	ASInt16 italicAngle;
	/* New in Acrobat 4.0 */
//	ASAtom cidFontType;
	ASInt16 wMode;
	//ASAtom psName;
	//ASAtom lang;
	//ASAtom registry;
	//ASAtom ordering;
	ASInt32 supplement;
	/* New in Acrobat 5.0 */
	ASInt32 cantEmbed;
//	ASAtom deltaEncoding;
	/* New in Acrobat 5.0.5 */
	ASInt32 protection;
}
PDEFontAttrs, *PDEFontAttrsP;

typedef enum
{
	kPDFETextRun = 0x0001,
	kPDFETextChar = 0x0002,
	kPDFETextPageSpace = 0x0004,
	kPDFETextGetBounds = 0x0008
}
PDFETextFlags;

typedef struct _t_PDEColorValue
{
	double color[7];
//	PDEObject colorObj2;
//	PDEObject colorObj;
}
PDEColorValue, *PDEColorValueP;

typedef struct _t_PDEColorSpec
{
//	PDEColorSpace space;
	PDEColorValue value;
}
PDEColorSpec, *PDEColorSpecP;

typedef struct _t_PDEGraphicState
{
	ASUns32 wasSetFlags;
	PDEColorSpec fillColorSpec;
	PDEColorSpec strokeColorSpec;
//	PDEDash dash;
	double lineWidth;
	double miterLimit;
	ASFixed flatness;
	ASInt32 lineCap;
	ASInt32 lineJoin;
//	ASAtom renderIntent;
	CPDFEExtGState* extGState;
}
PDEGraphicState, *PDEGraphicStateP;

typedef struct _t_PDETextState
{
	ASUns32 wasSetFlags;
	ASFixed charSpacing;
	ASFixed wordSpacing;
	ASInt32 renderMode;
	ASFixed fontSize; /*new in PDFLib 5.0. Default=1 */
	ASFixed hscale;/*new in PDFLib 5.0. Default=100 (==100%)*/
	ASFixed textRise; /*new in PDFLib 5.0*/
}
PDETextState, *PDETextStateP;

typedef enum
{
	kPDFEMoveTo,
	kPDFELineTo,
	kPDFECurveTo,
	kPDFECurveToV,
	kPDFECurveToY,
	kPDFERect,
	kPDFEClosePath,
	kPDFEPathLastType
}
PDEPathElementType;

typedef enum
{
	kPDFEInvisible = 0x00,
	kPDFEStroke = 0x01,
	kPDFEFill = 0x02,
	kPDFEEoFill = 0x04
}
PDFEPathOpFlags;

class CPDFEExtGState
{
public:
	CPDFCosDict* m_cos;
	int m_nIndex;

	void Create(CPDFCosDict* cosObj)
	{
		m_cos = cosObj;
		m_nIndex = 0;
	}

	double GetOpacityFill()
	{
		CPDFCosReal* pValue = (CPDFCosReal*)m_cos->FindObjectByName("ca");
		if (pValue)
			return pValue->m_value;
		else
			return 1.0;
	}

	double GetOpacityStroke()
	{
		CPDFCosReal* pValue = (CPDFCosReal*)m_cos->FindObjectByName("CA");
		if (pValue)
			return pValue->m_value;
		else
			return 1.0;
	}

	void SetOpacityFill(double opacity)
	{
		CPDFCosReal* pValue = (CPDFCosReal*)m_cos->FindObjectByName("ca");
		if (pValue == NULL)
		{
			pValue = m_cos->m_pCosDoc->CosNewReal(false, opacity);
			m_cos->CosDictPut("ca", pValue);
		}
		else
			pValue->m_value = opacity;
	}

	void SetOpacityStroke(double opacity)
	{
		CPDFCosReal* pValue = (CPDFCosReal*)m_cos->FindObjectByName("CA");
		if (pValue == NULL)
		{
			pValue = m_cos->m_pCosDoc->CosNewReal(false, opacity);
			m_cos->CosDictPut("CA", pValue);
		}
		else
			pValue->m_value = opacity;
	}
};

class CPDFEElement
{
public:
	CPDFPage* m_pPage;

	PDEGraphicState m_gstate;
	ASFixedMatrix	m_matrix;

	CPDFEElement()
	{
		m_pPage = NULL;

		m_matrix.a = 1;	m_matrix.b = 0;
		m_matrix.c = 0;	m_matrix.d = 1;
		m_matrix.h = 0;	m_matrix.v = 0; 

		m_gstate.lineWidth = 1;	// ??
		m_gstate.miterLimit = 4;	// ??
		m_gstate.lineCap = 0;
		m_gstate.lineJoin = 0;
		m_gstate.extGState = NULL;
	}

	virtual ~CPDFEElement()
	{
	}

	void SetGState(PDEGraphicState* stateP)
	{
		m_gstate = *stateP;
	}

	void SetMatrix(ASFixedMatrix* matrixP)
	{
		m_matrix = *matrixP;
	}

	virtual long GetType() = 0;

	virtual void WriteToStream(FILE* fp) = 0;
};

class CPDFEFont
{
public:
	int m_nIndex;
	CPDFCosDict* m_cos;
//	CUString m_name;
	PDEFontAttrs m_attrs;

	CPDFEFont()
	{
		m_nIndex = 0;
		m_cos = NULL;
	}

	STDMETHODIMP Create(PDEFontAttrsP attrsP)
	{
		m_attrs = *attrsP;
		return S_OK;
	}
};

class CPDFETextRun
{
public:
	CUString m_text;

	CPDFEFont* m_pFont;
	PDETextState m_textState;
	ASFixedMatrix m_textMatrix;

	CPDFETextRun()
	{
		m_pFont = NULL;
	}
};

class CPDFEText : public CPDFEElement
{
public:
	CArray<CPDFETextRun*,CPDFETextRun*> m_textRuns;

public:
	virtual long GetType()
	{
		return 1;
	}

	void Add(long flags, long index, char* text, long textLen, CPDFEFont* font, PDEGraphicStateP gstateP, PDETextStateP tstateP, ASFixedMatrixP textMatrixP, ASFixedMatrixP strokeMatrixP)
	{
		CPDFETextRun* pRun = new CPDFETextRun;
		if (pRun)
		{
			pRun->m_text = text;
			pRun->m_textState = *tstateP;
			pRun->m_pFont = font;
			pRun->m_textMatrix = *textMatrixP;

			m_textRuns.Add(pRun);
		}
	}

	long GetNumRuns()
	{
		return m_textRuns.GetSize();
	}

	long RunGetNumChars(long runIndex)
	{
		return m_textRuns[runIndex]->m_text.GetLength();
	}

	CPDFEFont* GetFont(long flags, long index)
	{
		long runIndex;

		if (flags & kPDFETextRun)
			runIndex = index;
		else
			runIndex = GetRunForChar(index);

		return m_textRuns[runIndex]->m_pFont;
	}

	long GetRunForChar(long charIndex)
	{
		for (int i = 0; i < m_textRuns.GetSize(); i++)
		{
			if (charIndex - m_textRuns[i]->m_text.GetLength() < 0)
				break;

			charIndex -= m_textRuns[i]->m_text.GetLength();
		}

		return i;
	}

	virtual void WriteToStream(FILE* fp)
	{
		fprintf(fp, "BT\r\n");	// Begin text object

		for (int i = 0; i < m_textRuns.GetSize(); i++)
		{
			CPDFETextRun* pRun = m_textRuns[i];

			fprintf(fp, "/F%d %g Tf\r\n", pRun->m_pFont->m_nIndex, pRun->m_textState.fontSize/65536.0);
		//	fprintf(fp, "%g %g Td\r\n", pRun->m_textMatrix.h/65536.0, pRun->m_textMatrix.v/65536.0);
			fprintf(fp, "%g %g %g %g %g %g Tm\r\n",
				pRun->m_textMatrix.a, pRun->m_textMatrix.b,
				pRun->m_textMatrix.c, pRun->m_textMatrix.d,
				pRun->m_textMatrix.h, pRun->m_textMatrix.v
				);
			fprintf(fp, "(%s) Tj\r\n", pRun->m_text);
		}

		fprintf(fp, "ET\r\n");	// End text object
	}
};

class CPDFEPath : public CPDFEElement
{
public:
	long* m_data;
	long m_dataSize;
	long m_opFlags;

	CPDFEPath()
	{
		m_data = NULL;
		m_dataSize = 0L;
		m_opFlags = 0;
	}

	virtual ~CPDFEPath()
	{
		if (m_data)
		{
			free(m_data);
			m_data = NULL;
			m_dataSize = 0L;
		}
	}

	virtual long GetType()
	{
		return 2;
	}

	void SetPaintOp(long opFlags)
	{
		m_opFlags = opFlags;
	}

	void SetData(long* data, long dataSize)
	{
		ATLASSERT((dataSize % 4) == 0);
		if (m_data)
		{
			m_data = NULL;
			m_dataSize = 0;
		}

		m_data = (long*)malloc(dataSize);
		if (m_data)
		{
			memcpy(m_data, data, dataSize);
			m_dataSize = dataSize;
		}
	}

	virtual void WriteToStream(FILE* fp)
	{
		fprintf(fp, "q\r\n"); // Save graphics state

		if (m_gstate.extGState)
		{
			fprintf(fp, "/GS%d gs\r\n", m_gstate.extGState->m_nIndex);
		}

		fprintf(fp, "%g w\r\n", m_gstate.lineWidth);
		fprintf(fp, "%g M\r\n", m_gstate.miterLimit);
		//fprintf(fp, "%d j\r\n", m_gstate.lineCap);
		//fprintf(fp, "%d J\r\n", m_gstate.lineJoin);

		fprintf(fp, "%.4g %.4g %.4g %.4g %.4g %.4g cm\r\n", m_matrix.a, m_matrix.b, m_matrix.c, m_matrix.d, m_matrix.h, m_matrix.v);

		fprintf(fp, "%g %g %g RG\r\n", m_gstate.strokeColorSpec.value.color[0], m_gstate.strokeColorSpec.value.color[1], m_gstate.strokeColorSpec.value.color[2]);
		fprintf(fp, "%g %g %g rg\r\n", m_gstate.fillColorSpec.value.color[0], m_gstate.fillColorSpec.value.color[1], m_gstate.fillColorSpec.value.color[2]);

		long count = m_dataSize/4;
		long n = 0;

		while (n < count)
		{
			int op = m_data[n++];

			if (op == kPDFEMoveTo)	// move
			{
				fprintf(fp, "%g %g m", (double)m_data[n+0]/65536.0, (double)m_data[n+1]/65536.0);
				n += 2;
			}
			else if (op == kPDFELineTo)	// line
			{
				fprintf(fp, "%g %g l", (double)m_data[n+0]/65536.0, (double)m_data[n+1]/65536.0);
				n += 2;
			}
			else if (op == kPDFECurveTo)	// cubic bezier
			{
				fprintf(fp, "%g %g %g %g %g %g c",
					(double)m_data[n+0]/65536.0, (double)m_data[n+1]/65536.0,
					(double)m_data[n+2]/65536.0, (double)m_data[n+3]/65536.0,
					(double)m_data[n+4]/65536.0, (double)m_data[n+5]/65536.0
					);

				n += 6;
			}
			else if (op == kPDFEClosePath)	// close
			{
				fprintf(fp, "h");
			}
			else
				ATLASSERT(0);

			fprintf(fp, "\r\n");
		}

		if (m_opFlags & (kPDFEStroke | kPDFEFill))
			fprintf(fp, "B");
		else if (m_opFlags & kPDFEFill)
			fprintf(fp, "f");
		else if (m_opFlags & kPDFEStroke)
			fprintf(fp, "S");

		/*
		if (m_opFlags & kPDFEFill)
			fprintf(fp, "f\r\n");
		else if (m_opFlags & kPDFEEoFill)
			fprintf(fp, "f*\r\n");
			*/

		fprintf(fp, "\r\n");
		fprintf(fp, "Q\r\n");// Restore graphics state
	}
};

class CPDFEImage : public CPDFEElement
{
public:
	CPDFCosStream* m_cos;

	int m_nIndex;

	CPDFEImage()
	{
		m_cos = NULL;
		m_nIndex = 0;
	}

	virtual long GetType()
	{
		return 3;
	}

	STDMETHODIMP CreateFromCosObject(CPDFCosStream* pCosStream, ASFixedMatrix*	matrixP)
	{
		m_cos = pCosStream;
		m_matrix = *matrixP;

		return S_OK;
	}

	virtual void WriteToStream(FILE* fp)
	{
		fprintf(fp, "q\r\n"); // Save graphics state

		fprintf(fp, "%g %g %g %g %g %g cm\r\n", m_matrix.a, m_matrix.b, m_matrix.c, m_matrix.d, m_matrix.h, m_matrix.v);

		fprintf(fp, "/Im%d Do\r\n", m_nIndex);	// Paint image

		fprintf(fp, "Q\r\n");// Restore graphics state
	}
};

class CPDFEContent
{
protected:
	CArray<CPDFEElement*,CPDFEElement*> m_elements;

public:
	CPDFPage* m_pPage;

public:
	CPDFEContent()
	{
		m_pPage = NULL;
	}

	~CPDFEContent()
	{
		for (int i = 0; i < m_elements.GetSize(); i++)
		{
			delete m_elements[i];
		}
		m_elements.RemoveAll();
	}

	long GetNumElems()
	{
		return m_elements.GetSize();
	}

	CPDFEElement* GetElem(long index)
	{
		if (index >= 0 && index < m_elements.GetSize())
		{
			return m_elements[index];
		}
		else
			return NULL;
	}

	void AddElem(long addAfterIndex, CPDFEElement* pdeElement)
	{
		pdeElement->m_pPage = m_pPage;
		m_elements.InsertAt(addAfterIndex+1, pdeElement);
	}

//	CArray<CPDFEFont*,CPDFEFont*> m_fonts;
//	CArray<CPDFCosObject*,CPDFCosObject*> m_xobjects;

	/*
	int FindFont(CPDFEFont* pFont)
	{
		for (int i = 0; i < m_fonts.GetSize(); i++)
		{
			if (m_fonts[i] == pFont)
				return i+1;
		}

		return 0;
	}
	*/

	int CPDFEContent::FindDictObject(CPDFCosDict* pXObjectDict, CPDFCosObject* pObject)
	{
		for (int i = 0; i < pXObjectDict->m_entries.GetSize(); i++)
		{
			if (pXObjectDict->m_entries[i]->m_value == pObject)
			{
				return i+1;
			}
		}

		return 0;
	}

	void UpdateFontNames(CPDFEElement* element);

	void UpdateFontNames()
	{
//		m_fonts.RemoveAll();

		for (int i = 0; i < m_elements.GetSize(); i++)
		{
			UpdateFontNames(m_elements[i]);
		}
	}

	void WriteToStream(FILE* fp)
	{
		for (int i = 0; i < m_elements.GetSize(); i++)
		{
			m_elements[i]->WriteToStream(fp);
		}
	}
};
