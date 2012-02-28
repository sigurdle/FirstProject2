#ifndef Web_PText_h
#define Web_PText_h

namespace System
{
namespace Web
{

interface ITextNodeExt
{
	virtual void CalculateDimensions(CHTMCalcContext* pC) abstract;
	virtual void OnTextContentChanged() abstract;
	virtual bool GetCursorPosition(int cursorPos, gm::PointD* pos, double* pHeight, gm::matrix3d* pMat3) abstract;
};

class WEBEXT PCharacterData :public PNode
{
public:
	CTOR PCharacterData(CharacterData* pCharData);

	virtual void OnTextContentChanged() abstract;
// Moved to CPNode 
//	virtual BOOL GetCursorPosition(int cursorPos, PointD* pos, double* pHeight, gmMatrix3* pMat3) = 0;
};

class WEBEXT PText : public PCharacterData
{
public:
	CTOR PText(Text* pText);
	~PText();

	void BuildWords();
	void RemoveWords();
	CHTMPCharacterBox* GetWordAtCursorPos(int cursorPos, int& wordCursorPos);
	void DistributeInline(CHTMFlowInlineContext* pInlineC);
	virtual bool GetCursorPosition(int cursorPos, gm::PointD* pos, double* pHeight, gm::matrix3f* pMat3);
	virtual void OnTextContentChanged();

	virtual void RemoveChildren()
	{
		RemoveWords();
	}

// CSS Box Model
//	virtual void CalculateDimensions(CHTMCalcContext* pC);
	virtual void CalculateBoundsAndChildren();

	virtual void DistributeInline(CHTMFlowContext* pParentC, PElementBase* nearestPositioned, PElementBase* stackingContext, double oparentwidth);
	virtual bool HasDistributableChildren()
	{
		return true;
	}

public:

	typedef PCharacterData baseClass;

	double m_ascentPixel;
	ITextNodeExt* m_ext;
	vector<CHTMPCharacterBox*> m_wordList;
	PNode* m_realNode;
	String m_data;
	int m_realOffset;
	bool m_bComputedWords;
};

}	// Web
}	// System

#endif // Web_PText_h
