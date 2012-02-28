// PrefsLanguageDlg.cpp : Implementation of CPrefsLanguageDlg
#include "stdafx.h"
#include "LHTML.h"
#include "LHTML2.h"
#include "PrefsLanguageDlg.h"

struct ISO639Language
{
	TCHAR* code;
	TCHAR* name;
	WORD langID;
};

ISO639Language languageCodes[] =
{
	_T("aa"), _T("Afar"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("ab"), _T("Abkhazian"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("af"), _T("Afrikaans"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("am"), _T("Amharic"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("ar"), _T("Arabic"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("as"), _T("Assamese"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("ay"), _T("Aymara"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("az"), _T("Azerbaijani"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("ba"), _T("Bashkir"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("be"), _T("Byelorussian"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("bg"), _T("Bulgarian"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("bh"), _T("Bihari"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("bi"), _T("Bislama"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("bn"), _T("Bengali; Bangla"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("bo"), _T("Tibetan"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("br"), _T("Breton"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("ca"), _T("Catalan"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("co"), _T("Corsican"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("cs"), _T("Czech"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("cy"), _T("Welsh"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("da"), _T("Danish"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("de"), _T("German"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("dz"), _T("Bhutani"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("el"), _T("Greek"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("en"), _T("English"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("eo"), _T("Esperanto"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("es"), _T("Spanish"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("et"), _T("Estonian"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("eu"), _T("Basque"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("fa"), _T("Farsi; Persian"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("fi"), _T("Finnish"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("fj"), _T("Fiji"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("fo"), _T("Faroese"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("fr"), _T("French"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("fy"), _T("Frisian"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("ga"), _T("Irish; Gaelic"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("gd"), _T("Scots; Gaelic"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("gl"), _T("Galician"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("gn"), _T("Guarani"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("gu"), _T("Gujarati"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("ha"), _T("Hausa"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("he"), _T("Hebrew"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("hi"), _T("Hindi"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("hr"), _T("Croatian"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("hu"), _T("Hungarian"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("hy"), _T("Armenian"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("ia"), _T("Interlingua"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("ie"), _T("Interlingue"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("ik"), _T("Inupiak"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("in"), _T("Indonesian"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("is"), _T("Icelandic"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("it"), _T("Italian"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("ja"), _T("Japanese"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("ji"), _T("Yiddish"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("jv"), _T("Javanese"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("ka"), _T("Georgian"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("kk"), _T("Kazakh"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("kl"), _T("Greenlandic"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("km"), _T("Cambodian"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("kn"), _T("Kannada"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("ko"), _T("Korean"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("ks"), _T("Kashmiri"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("ku"), _T("Kurdish"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("ky"), _T("Kirghiz"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("la"), _T("Latin"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("ln"), _T("Lingala"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("lo"), _T("Laothian"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("lt"), _T("Lithuanian"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("lv"), _T("Latvian; Lettish"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("mg"), _T("Malagasy"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("mi"), _T("Maori"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("mk"), _T("Macedonian"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("ml"), _T("Malayalam"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("mn"), _T("Mongolian"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("mo"), _T("Moldavian"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("mr"), _T("Marathi"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("ms"), _T("Malay"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("mt"), _T("Maltese"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("my"), _T("Burmese"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("na"), _T("Nauru"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("ne"), _T("Nepali"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("nl"), _T("Dutch"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("no"), _T("Norwegian"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("oc"), _T("Occitan"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("om"), _T("Afan (Oromo)"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("or"), _T("Oriya"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("pa"), _T("Punjabi"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("pl"), _T("Polish"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("ps"), _T("Pashto; Pushto"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("pt"), _T("Portuguese"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("qu"), _T("Quechua"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("rm"), _T("Rhaeto-romance"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("rn"), _T("Kurundi"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("ro"), _T("Romanian"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("ru"), _T("Russian"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("rw"), _T("Kinyarwanda"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("sa"), _T("Sanskrit"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("sd"), _T("Sindhi"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("sg"), _T("Sangho"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("sh"), _T("Serbo-Croatian"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("si"), _T("Singhalese"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("sk"), _T("Slovak"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("sl"), _T("Slovenian"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("sm"), _T("Samoan"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("sn"), _T("Shona"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("so"), _T("Somali"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("sq"), _T("Albanian"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("sr"), _T("Serbian"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("ss"), _T("Siswati"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("st"), _T("Sesotho"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("su"), _T("Sundanese"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("sv"), _T("Swedish"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("sw"), _T("Swahili"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("ta"), _T("Tamil"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("te"), _T("Telugu"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("tg"), _T("Tajik"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("th"), _T("Thai"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("ti"), _T("Tigrinya"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("tk"), _T("Turkmen"), MAKELANGID(LANG_NEUTRAL, 0),
	_T("tl"), _T("Ta"), MAKELANGID(LANG_NEUTRAL, 0),
};

#define NUMLANGUAGES (sizeof(languageCodes)/sizeof(ISO639Language))
int g_numLanguages = NUMLANGUAGES;

/////////////////////////////////////////////////////////////////////////////
// CPrefsLanguageDlg

LRESULT CPrefsLanguageDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CComboBox langList = GetDlgItem(IDC_LANGUAGE_LIST);

	for (int i = 0; i < g_numLanguages; i++)
	{
		int index = langList.AddString(languageCodes[i].name);
		langList.SetItemData(index, i);
	}

	// Set currently selected language
	{
		for (int i = 0; i < g_numLanguages; i++)
		{
			ASSERT(0);
#if 0
			if (wcscmp(languageCodes[i].code, m_pPrefs->m_systemLanguage.c_str()) == 0)
				break;
#endif
		}

		if (i < g_numLanguages)
		{
			langList.SelectString(-1, languageCodes[i].name);
		}
	}

	CheckRadioButton(IDC_SYSTEM_SUBTITLES, IDC_SYSTEM_SUBTITLES+1, IDC_SYSTEM_SUBTITLES+m_pPrefs->m_systemOverdubOrSubtitle);

	CheckDlgButton(IDC_SYSTEM_CAPTIONS, m_pPrefs->m_systemCaptions);
	CheckDlgButton(IDC_SYSTEM_AUDIODESC, m_pPrefs->m_systemAudioDesc);

	return 1;  // Let the system set the focus
}

BOOL CPrefsLanguageDlg::OnApply()
{
	ASSERT(0);
#if 0
	CComboBox langList = GetDlgItem(IDC_LANGUAGE_LIST);

	if (langList.GetCurSel() >= 0)
	{
		m_pPrefs->m_systemLanguage = languageCodes[langList.GetItemData(langList.GetCurSel())].code;
	}

	if (IsDlgButtonChecked(IDC_SYSTEM_SUBTITLES))
		m_pPrefs->m_systemOverdubOrSubtitle = 0;
	else
		m_pPrefs->m_systemOverdubOrSubtitle = 1;

	m_pPrefs->m_systemCaptions = IsDlgButtonChecked(IDC_SYSTEM_CAPTIONS);
	m_pPrefs->m_systemAudioDesc = IsDlgButtonChecked(IDC_SYSTEM_AUDIODESC);
#endif
	return TRUE;
}
