
namespace System
{

class StringEntry;

class Cell : public System::Object
{
public:

	CTOR Cell()
	{
		m_reentrant = 0;
		m_pSheet = NULL;
		m_bValidValue = false;
		m_pStringContent = NULL;
	}

	Sheet* m_pSheet;
	uint32 m_col;
	uint32 m_row;

	double GetValue()
	{
		if (m_reentrant)
			THROW(-1);

		if (!m_bValidValue)
		{
			m_reentrant++;
			Evaluate();
			m_reentrant--;
		}

		return m_value;
	}

	void SetFormula(Excel::FormulaTokens* formula);
	void Evaluate();

	Excel::FormulaTokens* m_formula;

	double m_value;
	System::StringA* m_stringValue;
	bool m_bValidValue;
	uint8 m_reentrant;

	float m_maxascent;
	float m_maxdescent;
	float m_maxsize;

	StringEntry* m_pStringContent;

	int m_xfIndex;

	vector<CellRef> m_dependencies;
};

}
