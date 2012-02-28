#include "stdafx.h"
#include "LXMLEditor2.h"

#include "InspectorDlg.h"

//#include "XMLAttributesDlg.h"
#include "ControlsWindow.h"
//#include "XMLKeyFrameValuesDlg.h"

#include "XMLControlsHandler.h"

#if 0

struct ISO639Language
{
	WORD code;
	WCHAR* name;
	WORD langID;
};

ISO639Language languageCodes[] =
{
	'aa', L"Afar", MAKELANGID(LANG_NEUTRAL, 0),
	'ab', L"Abkhazian", MAKELANGID(LANG_NEUTRAL, 0),
	'af', L"Afrikaans", MAKELANGID(LANG_NEUTRAL, 0),
	'am', L"Amharic", MAKELANGID(LANG_NEUTRAL, 0),
	'ar', L"Arabic", MAKELANGID(LANG_NEUTRAL, 0),
	'as', L"Assamese", MAKELANGID(LANG_NEUTRAL, 0),
	'ay', L"Aymara", MAKELANGID(LANG_NEUTRAL, 0),
	'az', L"Azerbaijani", MAKELANGID(LANG_NEUTRAL, 0),
	'ba', L"Bashkir", MAKELANGID(LANG_NEUTRAL, 0),
	'be', L"Byelorussian", MAKELANGID(LANG_NEUTRAL, 0),
	'bg', L"Bulgarian", MAKELANGID(LANG_NEUTRAL, 0),
	'bh', L"Bihari", MAKELANGID(LANG_NEUTRAL, 0),
	'bi', L"Bislama", MAKELANGID(LANG_NEUTRAL, 0),
	'bn', L"Bengali; Bangla", MAKELANGID(LANG_NEUTRAL, 0),
	'bo', L"Tibetan", MAKELANGID(LANG_NEUTRAL, 0),
	'br', L"Breton", MAKELANGID(LANG_NEUTRAL, 0),
	'ca', L"Catalan", MAKELANGID(LANG_NEUTRAL, 0),
	'co', L"Corsican", MAKELANGID(LANG_NEUTRAL, 0),
	'cs', L"Czech", MAKELANGID(LANG_NEUTRAL, 0),
	'cy', L"Welsh", MAKELANGID(LANG_NEUTRAL, 0),
	'da', L"Danish", MAKELANGID(LANG_NEUTRAL, 0),
	'de', L"German", MAKELANGID(LANG_NEUTRAL, 0),
	'dz', L"Bhutani", MAKELANGID(LANG_NEUTRAL, 0),
	'el', L"Greek", MAKELANGID(LANG_NEUTRAL, 0),
	'en', L"English", MAKELANGID(LANG_NEUTRAL, 0),
	'eo', L"Esperanto", MAKELANGID(LANG_NEUTRAL, 0),
	'es', L"Spanish", MAKELANGID(LANG_NEUTRAL, 0),
	'et', L"Estonian", MAKELANGID(LANG_NEUTRAL, 0),
	'eu', L"Basque", MAKELANGID(LANG_NEUTRAL, 0),
	'fa', L"Farsi; Persian", MAKELANGID(LANG_NEUTRAL, 0),
	'fi', L"Finnish", MAKELANGID(LANG_NEUTRAL, 0),
	'fj', L"Fiji", MAKELANGID(LANG_NEUTRAL, 0),
	'fo', L"Faroese", MAKELANGID(LANG_NEUTRAL, 0),
	'fr', L"French", MAKELANGID(LANG_NEUTRAL, 0),
	'fy', L"Frisian", MAKELANGID(LANG_NEUTRAL, 0),
	'ga', L"Irish; Gaelic", MAKELANGID(LANG_NEUTRAL, 0),
	'gd', L"Scots; Gaelic", MAKELANGID(LANG_NEUTRAL, 0),
	'gl', L"Galician", MAKELANGID(LANG_NEUTRAL, 0),
	'gn', L"Guarani", MAKELANGID(LANG_NEUTRAL, 0),
	'gu', L"Gujarati", MAKELANGID(LANG_NEUTRAL, 0),
	'ha', L"Hausa", MAKELANGID(LANG_NEUTRAL, 0),
	'he', L"Hebrew", MAKELANGID(LANG_NEUTRAL, 0),
	'hi', L"Hindi", MAKELANGID(LANG_NEUTRAL, 0),
	'hr', L"Croatian", MAKELANGID(LANG_NEUTRAL, 0),
	'hu', L"Hungarian", MAKELANGID(LANG_NEUTRAL, 0),
	'hy', L"Armenian", MAKELANGID(LANG_NEUTRAL, 0),
	'ia', L"Interlingua", MAKELANGID(LANG_NEUTRAL, 0),
	'ie', L"Interlingue", MAKELANGID(LANG_NEUTRAL, 0),
	'ik', L"Inupiak", MAKELANGID(LANG_NEUTRAL, 0),
	'in', L"Indonesian", MAKELANGID(LANG_NEUTRAL, 0),
	'is', L"Icelandic", MAKELANGID(LANG_NEUTRAL, 0),
	'it', L"Italian", MAKELANGID(LANG_NEUTRAL, 0),
	'ja', L"Japanese", MAKELANGID(LANG_NEUTRAL, 0),
	'ji', L"Yiddish", MAKELANGID(LANG_NEUTRAL, 0),
	'jv', L"Javanese", MAKELANGID(LANG_NEUTRAL, 0),
	'ka', L"Georgian", MAKELANGID(LANG_NEUTRAL, 0),
	'kk', L"Kazakh", MAKELANGID(LANG_NEUTRAL, 0),
	'kl', L"Greenlandic", MAKELANGID(LANG_NEUTRAL, 0),
	'km', L"Cambodian", MAKELANGID(LANG_NEUTRAL, 0),
	'kn', L"Kannada", MAKELANGID(LANG_NEUTRAL, 0),
	'ko', L"Korean", MAKELANGID(LANG_NEUTRAL, 0),
	'ks', L"Kashmiri", MAKELANGID(LANG_NEUTRAL, 0),
	'ku', L"Kurdish", MAKELANGID(LANG_NEUTRAL, 0),
	'ky', L"Kirghiz", MAKELANGID(LANG_NEUTRAL, 0),
	'la', L"Latin", MAKELANGID(LANG_NEUTRAL, 0),
	'ln', L"Lingala", MAKELANGID(LANG_NEUTRAL, 0),
	'lo', L"Laothian", MAKELANGID(LANG_NEUTRAL, 0),
	'lt', L"Lithuanian", MAKELANGID(LANG_NEUTRAL, 0),
	'lv', L"Latvian; Lettish", MAKELANGID(LANG_NEUTRAL, 0),
	'mg', L"Malagasy", MAKELANGID(LANG_NEUTRAL, 0),
	'mi', L"Maori", MAKELANGID(LANG_NEUTRAL, 0),
	'mk', L"Macedonian", MAKELANGID(LANG_NEUTRAL, 0),
	'ml', L"Malayalam", MAKELANGID(LANG_NEUTRAL, 0),
	'mn', L"Mongolian", MAKELANGID(LANG_NEUTRAL, 0),
	'mo', L"Moldavian", MAKELANGID(LANG_NEUTRAL, 0),
	'mr', L"Marathi", MAKELANGID(LANG_NEUTRAL, 0),
	'ms', L"Malay", MAKELANGID(LANG_NEUTRAL, 0),
	'mt', L"Maltese", MAKELANGID(LANG_NEUTRAL, 0),
	'my', L"Burmese", MAKELANGID(LANG_NEUTRAL, 0),
	'na', L"Nauru", MAKELANGID(LANG_NEUTRAL, 0),
	'ne', L"Nepali", MAKELANGID(LANG_NEUTRAL, 0),
	'nl', L"Dutch", MAKELANGID(LANG_NEUTRAL, 0),
	'no', L"Norwegian", MAKELANGID(LANG_NEUTRAL, 0),
	'oc', L"Occitan", MAKELANGID(LANG_NEUTRAL, 0),
	'om', L"Afan (Oromo)", MAKELANGID(LANG_NEUTRAL, 0),
	'or', L"Oriya", MAKELANGID(LANG_NEUTRAL, 0),
	'pa', L"Punjabi", MAKELANGID(LANG_NEUTRAL, 0),
	'pl', L"Polish", MAKELANGID(LANG_NEUTRAL, 0),
	'ps', L"Pashto; Pushto", MAKELANGID(LANG_NEUTRAL, 0),
	'pt', L"Portuguese", MAKELANGID(LANG_NEUTRAL, 0),
	'qu', L"Quechua", MAKELANGID(LANG_NEUTRAL, 0),
	'rm', L"Rhaeto-romance", MAKELANGID(LANG_NEUTRAL, 0),
	'rn', L"Kurundi", MAKELANGID(LANG_NEUTRAL, 0),
	'ro', L"Romanian", MAKELANGID(LANG_NEUTRAL, 0),
	'ru', L"Russian", MAKELANGID(LANG_NEUTRAL, 0),
	'rw', L"Kinyarwanda", MAKELANGID(LANG_NEUTRAL, 0),
	'sa', L"Sanskrit", MAKELANGID(LANG_NEUTRAL, 0),
	'sd', L"Sindhi", MAKELANGID(LANG_NEUTRAL, 0),
	'sg', L"Sangho", MAKELANGID(LANG_NEUTRAL, 0),
	'sh', L"Serbo-Croatian", MAKELANGID(LANG_NEUTRAL, 0),
	'si', L"Singhalese", MAKELANGID(LANG_NEUTRAL, 0),
	'sk', L"Slovak", MAKELANGID(LANG_NEUTRAL, 0),
	'sl', L"Slovenian", MAKELANGID(LANG_NEUTRAL, 0),
	'sm', L"Samoan", MAKELANGID(LANG_NEUTRAL, 0),
	'sn', L"Shona", MAKELANGID(LANG_NEUTRAL, 0),
	'so', L"Somali", MAKELANGID(LANG_NEUTRAL, 0),
	'sq', L"Albanian", MAKELANGID(LANG_NEUTRAL, 0),
	'sr', L"Serbian", MAKELANGID(LANG_NEUTRAL, 0),
	'ss', L"Siswati", MAKELANGID(LANG_NEUTRAL, 0),
	'st', L"Sesotho", MAKELANGID(LANG_NEUTRAL, 0),
	'su', L"Sundanese", MAKELANGID(LANG_NEUTRAL, 0),
	'sv', L"Swedish", MAKELANGID(LANG_NEUTRAL, 0),
	'sw', L"Swahili", MAKELANGID(LANG_NEUTRAL, 0),
	'ta', L"Tamil", MAKELANGID(LANG_NEUTRAL, 0),
	'te', L"Telugu", MAKELANGID(LANG_NEUTRAL, 0),
	'tg', L"Tajik", MAKELANGID(LANG_NEUTRAL, 0),
	'th', L"Thai", MAKELANGID(LANG_NEUTRAL, 0),
	'ti', L"Tigrinya", MAKELANGID(LANG_NEUTRAL, 0),
	'tk', L"Turkmen", MAKELANGID(LANG_NEUTRAL, 0),
	'tl', L"Ta", MAKELANGID(LANG_NEUTRAL, 0),
};

#if 0
{
L"AFGHANISTAN                                     AF      AFG     004
L"ALBANIA                                         AL      ALB     008
L"ALGERIA                                         DZ      DZA     012
L"AMERICAN SAMOA                                  AS      ASM     016
L"ANDORRA                                         AD      AND     020
L"ANGOLA                                          AO      AGO     024
L"ANGUILLA                                        AI      AIA     660
L"ANTARCTICA                                      AQ      ATA     010
L"ANTIGUA AND BARBUDA                             AG      ATG     028
L"ARGENTINA                                       AR      ARG     032
L"ARMENIA                                         AM      ARM     051  
L"ARUBA                                           AW      ABW     533
L"AUSTRALIA                                       AU      AUS     036
L"AUSTRIA                                         AT      AUT     040
L"AZERBAIJAN                                      AZ      AZE     031  
L"BAHAMAS                                         BS      BHS     044
L"BAHRAIN                                         BH      BHR     048
L"BANGLADESH                                      BD      BGD     050
L"BARBADOS                                        BB      BRB     052
L"BELARUS                                         BY      BLR     112  
L"BELGIUM                                         BE      BEL     056
L"BELIZE                                          BZ      BLZ     084
L"BENIN                                           BJ      BEN     204
L"BERMUDA                                         BM      BMU     060
L"BHUTAN                                          BT      BTN     064
L"BOLIVIA                                         BO      BOL     068
L"BOSNIA AND HERZEGOWINA                          BA      BIH     070
L"BOTSWANA                                        BW      BWA     072
L"BOUVET ISLAND                                   BV      BVT     074
L"BRAZIL                                          BR      BRA     076
L"BRITISH INDIAN OCEAN TERRITORY                  IO      IOT     086
L"BRUNEI DARUSSALAM                               BN      BRN     096
L"BULGARIA                                        BG      BGR     100
L"BURKINA FASO                                    BF      BFA     854
L"BURUNDI                                         BI      BDI     108
L"CAMBODIA                                        KH      KHM     116
L"CAMEROON                                        CM      CMR     120
L"CANADA                                          CA      CAN     124
L"CAPE VERDE                                      CV      CPV     132
L"CAYMAN ISLANDS                                  KY      CYM     136
L"CENTRAL AFRICAN REPUBLIC                        CF      CAF     140
L"CHAD                                            TD      TCD     148
L"CHILE                                           CL      CHL     152
L"CHINA                                           CN      CHN     156
L"CHRISTMAS ISLAND                                CX      CXR     162
L"COCOS (KEELING) ISLANDS                         CC      CCK     166
L"COLOMBIA                                        CO      COL     170
L"COMOROS                                         KM      COM     174
L"CONGO, Democratic Republic of (was Zaire)       CD      COD     180
L"CONGO, People's Republic of                     CG      COG     178
L"COOK ISLANDS                                    CK      COK     184
L"COSTA RICA                                      CR      CRI     188
L"COTE D'IVOIRE                                   CI      CIV     384
L"CROATIA (local name: Hrvatska)                  HR      HRV     191      
L"CUBA                                            CU      CUB     192
L"CYPRUS                                          CY      CYP     196
L"CZECH REPUBLIC                                  CZ      CZE     203  
L"DENMARK                                         DK      DNK     208
L"DJIBOUTI                                        DJ      DJI     262
L"DOMINICA                                        DM      DMA     212
L"DOMINICAN REPUBLIC                              DO      DOM     214
L"EAST TIMOR                                      TL      TLS     626
L"ECUADOR                                         EC      ECU     218
L"EGYPT                                           EG      EGY     818
L"EL SALVADOR                                     SV      SLV     222
L"EQUATORIAL GUINEA                               GQ      GNQ     226
L"ERITREA                                         ER      ERI     232
L"ESTONIA                                         EE      EST     233  
L"ETHIOPIA                                        ET      ETH     231
L"FALKLAND ISLANDS (MALVINAS)                     FK      FLK     238
L"FAROE ISLANDS                                   FO      FRO     234
L"FIJI                                            FJ      FJI     242
L"FINLAND                                         FI      FIN     246
L"FRANCE                                          FR      FRA     250
L"FRANCE, METROPOLITAN                            FX      FXX     249  
L"FRENCH GUIANA                                   GF      GUF     254
L"FRENCH POLYNESIA                                PF      PYF     258
L"FRENCH SOUTHERN TERRITORIES                     TF      ATF     260
L"GABON                                           GA      GAB     266
L"GAMBIA                                          GM      GMB     270
L"GEORGIA                                         GE      GEO     268  
L"GERMANY                                         DE      DEU     276
L"GHANA                                           GH      GHA     288
L"GIBRALTAR                                       GI      GIB     292
L"GREECE                                          GR      GRC     300
L"GREENLAND                                       GL      GRL     304
L"GRENADA                                         GD      GRD     308
L"GUADELOUPE                                      GP      GLP     312
L"GUAM                                            GU      GUM     316
L"GUATEMALA                                       GT      GTM     320
L"GUINEA                                          GN      GIN     324
L"GUINEA-BISSAU                                   GW      GNB     624
L"GUYANA                                          GY      GUY     328
L"HAITI                                           HT      HTI     332
L"HEARD AND MC DONALD ISLANDS                     HM      HMD     334
L"HONDURAS                                        HN      HND     340
L"HONG KONG                                       HK      HKG     344
L"HUNGARY                                         HU      HUN     348
L"ICELAND                                         IS      ISL     352
L"INDIA                                           IN      IND     356
L"INDONESIA                                       ID      IDN     360
L"IRAN (ISLAMIC REPUBLIC OF)                      IR      IRN     364
L"IRAQ                                            IQ      IRQ     368
L"IRELAND                                         IE      IRL     372
L"ISRAEL                                          IL      ISR     376
L"ITALY                                           IT      ITA     380
L"JAMAICA                                         JM      JAM     388
L"JAPAN                                           JP      JPN     392
L"JORDAN                                          JO      JOR     400
L"KAZAKHSTAN                                      KZ      KAZ     398  
L"KENYA                                           KE      KEN     404
L"KIRIBATI                                        KI      KIR     296
L"KOREA, DEMOCRATIC PEOPLE'S REPUBLIC OF          KP      PRK     408
L"KOREA, REPUBLIC OF                              KR      KOR     410
L"KUWAIT                                          KW      KWT     414
L"KYRGYZSTAN                                      KG      KGZ     417  
L"LAO PEOPLE'S DEMOCRATIC REPUBLIC                LA      LAO     418
L"LATVIA                                          LV      LVA     428  
L"LEBANON                                         LB      LBN     422
L"LESOTHO                                         LS      LSO     426
L"LIBERIA                                         LR      LBR     430
L"LIBYAN ARAB JAMAHIRIYA                          LY      LBY     434
L"LIECHTENSTEIN                                   LI      LIE     438
L"LITHUANIA                                       LT      LTU     440  
L"LUXEMBOURG                                      LU      LUX     442
L"MACAU                                           MO      MAC     446
L"MACEDONIA, THE FORMER YUGOSLAV REPUBLIC OF      MK      MKD     807 
L"MADAGASCAR                                      MG      MDG     450
L"MALAWI                                          MW      MWI     454
L"MALAYSIA                                        MY      MYS     458
L"MALDIVES                                        MV      MDV     462
L"MALI                                            ML      MLI     466
L"MALTA                                           MT      MLT     470
L"MARSHALL ISLANDS                                MH      MHL     584
L"MARTINIQUE                                      MQ      MTQ     474
L"MAURITANIA                                      MR      MRT     478
L"MAURITIUS                                       MU      MUS     480
L"MAYOTTE                                         YT      MYT     175  
L"MEXICO                                          MX      MEX     484
L"MICRONESIA, FEDERATED STATES OF                 FM      FSM     583
L"MOLDOVA, REPUBLIC OF                            MD      MDA     498  
L"MONACO                                          MC      MCO     492
L"MONGOLIA                                        MN      MNG     496
L"MONTSERRAT                                      MS      MSR     500
L"MOROCCO                                         MA      MAR     504
L"MOZAMBIQUE                                      MZ      MOZ     508
L"MYANMAR                                         MM      MMR     104
L"NAMIBIA                                         NA      NAM     516
L"NAURU                                           NR      NRU     520
L"NEPAL                                           NP      NPL     524
L"NETHERLANDS                                     NL      NLD     528
L"NETHERLANDS ANTILLES                            AN      ANT     530
L"NEW CALEDONIA                                   NC      NCL     540
L"NEW ZEALAND                                     NZ      NZL     554
L"NICARAGUA                                       NI      NIC     558
L"NIGER                                           NE      NER     562
L"NIGERIA                                         NG      NGA     566
L"NIUE                                            NU      NIU     570
L"NORFOLK ISLAND                                  NF      NFK     574
L"NORTHERN MARIANA ISLANDS                        MP      MNP     580
L"NORWAY                                          NO      NOR     578
L"OMAN                                            OM      OMN     512
L"PAKISTAN                                        PK      PAK     586
L"PALAU                                           PW      PLW     585
L"PALESTINIAN TERRITORY, Occupied                 PS      PSE     275
L"PANAMA                                          PA      PAN     591
L"PAPUA NEW GUINEA                                PG      PNG     598
L"PARAGUAY                                        PY      PRY     600
L"PERU                                            PE      PER     604
L"PHILIPPINES                                     PH      PHL     608
L"PITCAIRN                                        PN      PCN     612
L"POLAND                                          PL      POL     616
L"PORTUGAL                                        PT      PRT     620
L"PUERTO RICO                                     PR      PRI     630
L"QATAR                                           QA      QAT     634
L"REUNION                                         RE      REU     638
L"ROMANIA                                         RO      ROU     642
L"RUSSIAN FEDERATION                              RU      RUS     643
L"RWANDA                                          RW      RWA     646
L"SAINT KITTS AND NEVIS                           KN      KNA     659
L"SAINT LUCIA                                     LC      LCA     662
L"SAINT VINCENT AND THE GRENADINES                VC      VCT     670
L"SAMOA                                           WS      WSM     882
L"SAN MARINO                                      SM      SMR     674
L"SAO TOME AND PRINCIPE                           ST      STP     678
L"SAUDI ARABIA                                    SA      SAU     682
L"SENEGAL                                         SN      SEN     686
L"SEYCHELLES                                      SC      SYC     690
L"SIERRA LEONE                                    SL      SLE     694
L"SINGAPORE                                       SG      SGP     702
L"SLOVAKIA (Slovak Republic)                      SK      SVK     703  
L"SLOVENIA                                        SI      SVN     705  
L"SOLOMON ISLANDS                                 SB      SLB     090
L"SOMALIA                                         SO      SOM     706
L"SOUTH AFRICA                                    ZA      ZAF     710
L"SOUTH GEORGIA AND THE SOUTH SANDWICH ISLANDS    GS      SGS     239
L"SPAIN                                           ES      ESP     724
L"SRI LANKA                                       LK      LKA     144
L"ST. HELENA                                      SH      SHN     654
L"ST. PIERRE AND MIQUELON                         PM      SPM     666
L"SUDAN                                           SD      SDN     736
L"SURINAME                                        SR      SUR     740
L"SVALBARD AND JAN MAYEN ISLANDS                  SJ      SJM     744
L"SWAZILAND                                       SZ      SWZ     748
L"SWEDEN                                          SE      SWE     752
L"SWITZERLAND                                     CH      CHE     756
L"SYRIAN ARAB REPUBLIC                            SY      SYR     760
L"TAIWAN                                          TW      TWN     158
L"TAJIKISTAN                                      TJ      TJK     762  
L"TANZANIA, UNITED REPUBLIC OF                    TZ      TZA     834
L"THAILAND                                        TH      THA     764
L"TOGO                                            TG      TGO     768
L"TOKELAU                                         TK      TKL     772
L"TONGA                                           TO      TON     776
L"TRINIDAD AND TOBAGO                             TT      TTO     780
L"TUNISIA                                         TN      TUN     788
L"TURKEY                                          TR      TUR     792
L"TURKMENISTAN                                    TM      TKM     795  
L"TURKS AND CAICOS ISLANDS                        TC      TCA     796
L"TUVALU                                          TV      TUV     798
L"UGANDA                                          UG      UGA     800
L"UKRAINE                                         UA      UKR     804
L"UNITED ARAB EMIRATES                            AE      ARE     784
L"UNITED KINGDOM                                  GB      GBR     826
L"UNITED STATES                                   US      USA     840
L"UNITED STATES MINOR OUTLYING ISLANDS            UM      UMI     581
L"URUGUAY                                         UY      URY     858
L"UZBEKISTAN                                      UZ      UZB     860  
L"VANUATU                                         VU      VUT     548
L"VATICAN CITY STATE (HOLY SEE)                   VA      VAT     336
L"VENEZUELA                                       VE      VEN     862
L"VIET NAM                                        VN      VNM     704
L"VIRGIN ISLANDS (BRITISH)                        VG      VGB     092
L"L"VIRGIN ISLANDS (U.S.)                           VI      VIR     850
L"WALLIS AND FUTUNA ISLANDS                       WF      WLF     876
L"WESTERN SAHARA                                  EH      ESH     732
L"YEMEN                                           YE      YEM     887
L"YUGOSLAVIA                                      YU      YUG     891
L"ZAMBIA                                          ZM      ZMB     894
L"ZIMBABWE                                        ZW      ZWE     716
};
#endif

WCHAR* PreserverAspectRatioAlignStrings[] =
{
	L"none",
	L"xMinYMin",
	L"xMidYMin",
	L"xMaxYMin",
	L"xMinYMid",
	L"xMidYMid",
	L"xMaxYMid",
	L"xMinYMax",
	L"xMidYMax",
	L"xMaxYMax",
};

WCHAR* MeetOrSliceStrings[] =
{
	L"meet",
	L"slice",
};

/////////////////////////////////////////////////////////////////////////////////
// (X)HTML

class CHTMLHTMLHandler : public CXMLControlsHandler
{
public:
	CHTMLHTMLHandler()
	{
	}

	virtual void Setup()
	{
		m_controlWindow->AddData(new CXMLStringData(L"head/title", L""));

	// Controls
		m_controlWindow->AddControl(new CXMLControlString("title"));
		m_controlWindow->GetControl("title")->ConnectData(m_controlWindow->GetData(L"head/title"));
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
	}
};

class CHTMLFrameSetHandler : public CXMLControlsHandler
{
public:
	CHTMLFrameSetHandler()
	{
	}

	virtual void Setup()
	{
		m_controlWindow->AddData(new CXMLStringData(L"@framespacing", L""));
		m_controlWindow->AddData(new CXMLStringData(L"@bordercolor", L""));

	// Controls
		m_controlWindow->AddControl(new CXMLControlString("framespacing"));
		m_controlWindow->GetControl("framespacing")->ConnectData(m_controlWindow->GetData(L"@framespacing"));

		m_controlWindow->AddControl(new CXMLControlColor("bordercolor"));
		m_controlWindow->GetControl("bordercolor")->ConnectData(m_controlWindow->GetData(L"@bordercolor"));
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
	}
};

class CHTMLFrameHandler : public CXMLControlsHandler
{
public:
	CHTMLFrameHandler()
	{
	}

	virtual void Setup()
	{
		m_controlWindow->AddData(new CXMLStringData(L"@name", L""));
		m_controlWindow->AddData(new CXMLStringData(L"@src", L""));
		m_controlWindow->AddData(new CXMLStringData(L"@scrolling", L"auto"));

	// Controls
		m_controlWindow->AddControl(new CXMLControlString("name"));
		m_controlWindow->GetControl("name")->ConnectData(m_controlWindow->GetData(L"@name"));

		m_controlWindow->AddControl(new CXMLControlString("src"));
		m_controlWindow->GetControl("src")->ConnectData(m_controlWindow->GetData(L"@src"));

		m_controlWindow->AddControl(new CXMLControlPopup("scrolling", L"auto|no|yes"));
		m_controlWindow->GetControl("scrolling")->ConnectData(m_controlWindow->GetData(L"@scrolling"));
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
	}
};

class CHTMLAHandler : public CXMLControlsHandler
{
public:
	CHTMLAHandler()
	{
	}

	virtual void Setup()
	{
		m_controlWindow->AddData(new CXMLStringData(L"@href", L""));
		m_controlWindow->AddData(new CXMLStringData(L"@target", L""));
		m_controlWindow->AddData(new CXMLStringData(L"@navindex", L""));

	// Controls
		m_controlWindow->AddControl(new CXMLControlString("href"));
		m_controlWindow->GetControl("href")->ConnectData(m_controlWindow->GetData(L"@href"));

		m_controlWindow->AddControl(new CXMLControlString("target"));
		m_controlWindow->GetControl("target")->ConnectData(m_controlWindow->GetData(L"@target"));

		m_controlWindow->AddControl(new CXMLControlNumber("navindex"));
		m_controlWindow->GetControl("navindex")->ConnectData(m_controlWindow->GetData(L"@navindex"));
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
	}
};

/////////////////////////////////////////////////////////////////////////////////
// NITF

class CNITFPersonHandler : public CXMLControlsHandler
{
public:
	CNITFPersonHandler()
	{
	}

	virtual void Setup()
	{
		m_controlWindow->AddData(new CXMLStringData(L"@gender", L""));

	// Controls
		m_controlWindow->AddControl(new CXMLControlPopup("gender", L"|male|female"));
		m_controlWindow->GetControl("gender")->ConnectData(m_controlWindow->GetData(L"@gender"));
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
	}
};

////////////////////////////////////////////////////////////////////////////
// SMIL

class CSMILRootLayoutHandler :
	public CXMLControlsHandler
{
public:
	CSMILRootLayoutHandler()
	{
	}

	virtual void Setup()
	{
	// Data
		m_controlWindow->AddData(new CXMLStringData(L"@width", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@height", L"0"));

	// Controls
		m_controlWindow->AddControl(new CControlLength("width"));
		m_controlWindow->GetControl("width")->ConnectData(m_controlWindow->GetData(L"@width"));

		m_controlWindow->AddControl(new CControlLength("height"));
		m_controlWindow->GetControl("height")->ConnectData(m_controlWindow->GetData(L"@height"));
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
	}
};

class CSMILRegionHandler :
	public CXMLControlsHandler
{
public:
	CSMILRegionHandler()
	{
	}

	virtual void Setup()
	{
	// Data
		m_controlWindow->AddData(new CXMLStringData(L"@left", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@top", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@width", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@height", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@fit", L"hidden"));
		m_controlWindow->AddData(new CXMLStringData(L"@showBackground", L"always"));

	// Controls
		m_controlWindow->AddControl(new CControlLength("left"));
		m_controlWindow->GetControl("left")->ConnectData(m_controlWindow->GetData(L"@left"));

		m_controlWindow->AddControl(new CControlLength("top"));
		m_controlWindow->GetControl("top")->ConnectData(m_controlWindow->GetData(L"@top"));

		m_controlWindow->AddControl(new CControlLength("width"));
		m_controlWindow->GetControl("width")->ConnectData(m_controlWindow->GetData(L"@width"));

		m_controlWindow->AddControl(new CControlLength("height"));
		m_controlWindow->GetControl("height")->ConnectData(m_controlWindow->GetData(L"@height"));

		m_controlWindow->AddControl(new CXMLControlPopup("fit", L"fill|hidden|meet|scroll|slice"));
		m_controlWindow->GetControl("fit")->ConnectData(m_controlWindow->GetData(L"@fit"));

		m_controlWindow->AddControl(new CXMLControlPopup("showBackground", L"always|whenActive"));
		m_controlWindow->GetControl("showBackground")->ConnectData(m_controlWindow->GetData(L"@showBackground"));
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
	}
};

class CSMILMediaHandler :
	public CXMLControlsHandler
{
public:
	CSMILMediaHandler()
	{
	}

	virtual void Setup()
	{
	// Data
		m_controlWindow->AddData(new CXMLStringData(L"@left", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@top", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@width", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@height", L"0"));

	// Controls
		m_controlWindow->AddControl(new CControlLength("left"));
		m_controlWindow->GetControl("left")->ConnectData(m_controlWindow->GetData(L"@left"));

		m_controlWindow->AddControl(new CControlLength("top"));
		m_controlWindow->GetControl("top")->ConnectData(m_controlWindow->GetData(L"@top"));

		m_controlWindow->AddControl(new CControlLength("width"));
		m_controlWindow->GetControl("width")->ConnectData(m_controlWindow->GetData(L"@width"));

		m_controlWindow->AddControl(new CControlLength("height"));
		m_controlWindow->GetControl("height")->ConnectData(m_controlWindow->GetData(L"@height"));

	// Data
		m_controlWindow->AddData(new CXMLStringData(L"@src", L""));
		m_controlWindow->AddData(new CXMLStringData(L"@erase", L"0"));

	// Controls
		m_controlWindow->AddControl(new CXMLControlString("src"));
		m_controlWindow->GetControl("src")->ConnectData(m_controlWindow->GetData(L"@src"));

		m_controlWindow->AddControl(new CXMLControlPopup("erase", L"whenDone|never"));
		m_controlWindow->GetControl("erase")->ConnectData(m_controlWindow->GetData(L"@erase"));
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
	}
};

#include "..\Utils\parsenumber.h"

#include "Transition.h"
class CTransitions g_Transitions;

#include "TransitionSettingsDlg.h"

class CSMILTransitionHandler :
	public CXMLControlsHandler
{
public:
	CSMILTransitionHandler()
	{
		m_pMapping = NULL;
	}

	CSMILTransition* m_pMapping;

	virtual void Setup()
	{
	// Data
		m_controlWindow->AddData(new CXMLStringData(L"@dur", L"1"));

		CComBSTR str;
		for (int i = 0; i < g_Transitions.m_items.GetSize(); i++)
		{
			if (i > 0) str += L"|";
			str += g_Transitions.m_items[i]->m_name;
		}

		//
		m_controlWindow->AddControl(new CXMLControlPopup("transitionType", str));

		{
			CComBSTR type;
			/*m_controlWindow->*/GetPathNodeValue(L"@type", &type);
		//	CComBSTR type;
		//	element->getAttribute(L"type", &type);

			CComBSTR subtype;
			/*m_controlWindow->*/GetPathNodeValue(L"@subtype", &subtype);
		//	CComBSTR subtype;
		//	element->getAttribute(L"subtype", &subtype);

			m_pMapping = g_Transitions.FindMapping(type, subtype);
			if (m_pMapping)
			{
				m_controlWindow->GetControl("transitionType")->SetProperty(NULL, _bstr_t(m_pMapping->m_pTransition->m_name/*_bstr_t(PreserverAspectRatioAlignStrings[align-1]*/));
				//::SendMessage(GetDlgItem(IDC_SMILTRANSITION_TYPE), CB_SELECTSTRING, -1, (LPARAM)(TCHAR*)m_pMapping->m_pTransition->m_name);
			}
			else
			{
				m_controlWindow->GetControl("transitionType")->SetProperty(NULL, L"");
				//::SendMessage(GetDlgItem(IDC_SMILTRANSITION_TYPE), CB_SETCURSEL, -1, 0);
			}
		}

		m_controlWindow->AddControl(new CXMLControlButton("Settings"));

		m_controlWindow->AddControl(new CXMLControlString("dur"));
		m_controlWindow->GetControl("dur")->ConnectData(m_controlWindow->GetData(L"@dur"));
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
		if (pControl->GetName() == "transitionType")
		{
			_bstr_t transitionType = m_controlWindow->GetControl("transitionType")->GetProperty(NULL);

			CTransition* pTransition = NULL;
			for (int i = 0; i < g_Transitions.m_items.GetSize(); i++)
			{
				if (!wcscmp(g_Transitions.m_items[i]->m_name, transitionType))
				{
					pTransition = g_Transitions.m_items[i];
					break;
				}
			}

			if (pTransition)
			{
				ASSERT(pTransition);

				CSMILTransition* pMapping = pTransition->m_mapping[0];

				/*m_controlWindow->*/SetPathNodeValue(L"@type", pMapping->m_type);
				/*m_controlWindow->*/SetPathNodeValue(L"@subtype", pMapping->m_subtype);

				m_pMapping = pMapping;
			//	ASSERT(pMapping == m_pMapping);

				/*
				int index = ::SendMessage(GetDlgItem(IDC_SMILTRANSITION_TYPE), CB_GETCURSEL, 0, 0);
				if (index >= 0)
				{
					CTransition* pTransition = (CTransition*)::SendMessage(GetDlgItem(IDC_SMILTRANSITION_TYPE), CB_GETITEMDATA, index, 0);

					CSMILTransition* pMapping = pTransition->m_mapping[0];

					m_controlWindow->SetPathNodeValue(L"@type", pMapping->m_type);
					m_controlWindow->SetPathNodeValue(L"@subtype", pMapping->m_subtype);

					ASSERT(pMapping == m_pMapping);
				}
				*/
			}
		}
		else if (pControl->GetName() == "Settings")
		{
			if (m_pMapping)
			{
				CTransitionSettingsDlg dlg(m_pMapping);
				//dlg.m_pMapping = m_pMapping;

				double startProgress;
				CComBSTR bstr_startProgress;
				/*m_controlWindow->*/GetPathNodeValue(L"@startProgress", &bstr_startProgress);
				if (bstr_startProgress.Length())
					startProgress = getfnumber(bstr_startProgress);
				else
					startProgress = 0;

				double endProgress;
				CComBSTR bstr_endProgress;
				/*m_controlWindow->*/GetPathNodeValue(L"@endProgress", &bstr_endProgress);
				if (bstr_endProgress.Length())
					endProgress = getfnumber(bstr_endProgress);
				else
					endProgress = 1;

				long horzRepeat;
				CComBSTR bstr_horzRepeat;
				/*m_controlWindow->*/GetPathNodeValue(L"@horzRepeat", &bstr_horzRepeat);
				if (bstr_horzRepeat.Length())
					horzRepeat = str2int(bstr_horzRepeat);
				else
					horzRepeat = 1;

				long vertRepeat;
				CComBSTR bstr_vertRepeat;
				/*m_controlWindow->*/GetPathNodeValue(L"@vertRepeat", &bstr_vertRepeat);
				if (bstr_vertRepeat.Length())
					vertRepeat = str2int(bstr_vertRepeat);
				else
					vertRepeat = 1;

				int reverse;
				CComBSTR bstr_direction;
				/*m_controlWindow->*/GetPathNodeValue(L"@direction", &bstr_direction);
				if (bstr_direction.Length() && !wcscmp(bstr_direction, L"reverse"))
					reverse = 1;
				else
					reverse = 0;

				dlg.m_startProgress = startProgress;
				dlg.m_endProgress = endProgress;
				dlg.m_horzRepeat = horzRepeat;
				dlg.m_vertRepeat = vertRepeat;
				dlg.m_reverse = reverse;

				if (dlg.DoModal() == IDOK)
				{
					if (m_pMapping != dlg.m_pMapping)
					{
						if (wcscmp(dlg.m_pMapping->m_type, m_pMapping->m_type))
						{
							/*m_controlWindow->*/SetPathNodeValue(L"@type", dlg.m_pMapping->m_type);
							//element->setAttribute(L"type", dlg.m_pMapping->m_type);
						}

						if (wcscmp(dlg.m_pMapping->m_subtype, m_pMapping->m_subtype))
						{
							/*m_controlWindow->*/SetPathNodeValue(L"@subtype", dlg.m_pMapping->m_subtype);
							//element->setAttribute(L"subtype", dlg.m_pMapping->m_subtype);
						}

						m_pMapping = dlg.m_pMapping;
					}

					if (dlg.m_startProgress != startProgress)
					{
						WCHAR str[64];
						swprintf(str, L"%g", dlg.m_startProgress);
						/*m_controlWindow->*/SetPathNodeValue(L"@startProgress", str);
					}

					if (dlg.m_endProgress != endProgress)
					{
						WCHAR str[64];
						swprintf(str, L"%g", dlg.m_endProgress);
						/*m_controlWindow->*/SetPathNodeValue(L"@endProgress", str);
					}

					if (dlg.m_horzRepeat != horzRepeat)
					{
						WCHAR str[64];
						swprintf(str, L"%d", dlg.m_horzRepeat);
						/*m_controlWindow->*/SetPathNodeValue(L"@horzRepeat", str);
					}

					if (dlg.m_vertRepeat != vertRepeat)
					{
						WCHAR str[64];
						swprintf(str, L"%d", dlg.m_vertRepeat);
						/*m_controlWindow->*/SetPathNodeValue(L"@vertRepeat", str);
					}

					if ((dlg.m_reverse==0) != (reverse==0))
					{
						if (dlg.m_reverse)
							/*m_controlWindow->*/SetPathNodeValue(L"@direction", L"reverse");
						else// TODO RemovePathNodeValue
							/*m_controlWindow->*/SetPathNodeValue(L"@direction", L"forward");
					}
				}
			}
		}
	}
};

////////////////////////////////////////////////////////////////////////////
// SVG

void AddPreserveAspectRatioControls(CXMLControlsHandler* handler)
{
// preserveAspectRatio
	{
	// TODO	m_controlWindow->AddControl(new CXMLControlCheckbox("defer"));
		handler->m_controlWindow->AddControl(new CXMLControlPopup("align", L"none|xMinYMin|xMidYMin|xMaxYMin|xMinYMid|xMidYMid|xMaxYMid|xMinYMax|xMidYMax|xMaxYMax"));
		handler->m_controlWindow->AddControl(new CXMLControlPopup("meetOrSlice", L"meet|slice|"));

		CComBSTR value;
		handler->/*m_controlWindow->*/GetPathNodeValue(L"@preserveAspectRatio", &value);

		int align = 0;
		int meetOrSlice = 0;

		if (value.Length())
		{
			WCHAR* p = value;

			while (iswspace(*p)) p++;

		// TODO "defer"

			int i;

			for (i = 0; i < sizeof(PreserverAspectRatioAlignStrings)/sizeof(WCHAR*); i++)
			{
				if (!wcsncmp(PreserverAspectRatioAlignStrings[i], p, wcslen(PreserverAspectRatioAlignStrings[i])))
				{
					align = (LSVGPreserveAspectRatioAlignType)(i+1);
					p += wcslen(PreserverAspectRatioAlignStrings[i]);
					break;
				}
			}

			while (iswspace(*p)) p++;

			for (i = 0; i < sizeof(MeetOrSliceStrings)/sizeof(WCHAR*); i++)
			{
				if (!wcsncmp(MeetOrSliceStrings[i], p, wcslen(MeetOrSliceStrings[i])))
				{
					meetOrSlice = (LSVGMeetOrSliceType)(i+1);
					p += wcslen(MeetOrSliceStrings[i]);
					break;
				}
			}
		}

		if (align > 0)
			handler->m_controlWindow->GetControl("align")->SetProperty(NULL, _bstr_t(PreserverAspectRatioAlignStrings[align-1]));

		if (meetOrSlice > 0)
			handler->m_controlWindow->GetControl("meetOrSlice")->SetProperty(NULL, _bstr_t(MeetOrSliceStrings[meetOrSlice-1]));
	}
}

BOOL HandlePreserveAspectRatioControls(CXMLControlsHandler* handler, CControl* pControl)
{
	if ((pControl->GetName() == "align") ||
		(pControl->GetName() == "meetOrSlice"))
	{
		_bstr_t align = handler->m_controlWindow->GetControl("align")->GetProperty(NULL);
		_bstr_t meetOrSlice = handler->m_controlWindow->GetControl("meetOrSlice")->GetProperty(NULL);

		_bstr_t value = align + L" " + meetOrSlice;

		handler->/*m_controlWindow->*/SetPathNodeValue(L"@preserveAspectRatio", value);

		return TRUE;
	}

	return FALSE;
}

#if 0
class CSVGTests
{
public:
	void Setup(IControlsWindow* controlWindow)
	{
	// Data
		controlWindow->AddData(new CXMLStringData(L"@requiredFeatures", L""));
		controlWindow->AddData(new CXMLStringData(L"@requiredExtensions", L""));
		controlWindow->AddData(new CXMLStringData(L"@systemLanguage", L""));

	// Controls
		controlWindow->AddControl(new CXMLControlString("requiredFeatures"));
		controlWindow->GetControl("requiredFeatures")->ConnectData(controlWindow->GetData(L"@requiredFeatures"));

		controlWindow->AddControl(new CXMLControlString("requiredExtensions"));
		controlWindow->GetControl("requiredExtensions")->ConnectData(controlWindow->GetData(L"@requiredExtensions"));

		controlWindow->AddControl(new CXMLControlString("systemLanguage"));
		controlWindow->GetControl("systemLanguage")->ConnectData(controlWindow->GetData(L"@systemLanguage"));
	}
};
#endif

class CExternalResourcesRequired
{
public:
	void Setup(IControlsWindow* controlWindow)
	{
	// Data
		controlWindow->AddData(new CXMLStringData(L"@externalResourcesRequired", L"false"));

	// Controls
		controlWindow->AddControl(new CXMLControlCheckbox("externalResourcesRequired"));
		controlWindow->GetControl("externalResourcesRequired")->ConnectData(controlWindow->GetData(L"@externalResourcesRequired"));
	}
};

class CSVGSVGHandler :
	public CXMLControlsHandler,
	public CExternalResourcesRequired
{
public:
	CSVGSVGHandler()
	{
	}

	virtual void Setup()
	{
	// Data
		m_controlWindow->AddData(new CXMLStringData(L"@x", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@y", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@width", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@height", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@viewBox", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@preserveAspectRatio", L"xMidYMid meet"));

	// Controls
		m_controlWindow->AddControl(new CControlLength("x"));
		m_controlWindow->GetControl("x")->ConnectData(m_controlWindow->GetData(L"@x"));

		m_controlWindow->AddControl(new CControlLength("y"));
		m_controlWindow->GetControl("y")->ConnectData(m_controlWindow->GetData(L"@y"));

		m_controlWindow->AddControl(new CControlLength("width"));
		m_controlWindow->GetControl("width")->ConnectData(m_controlWindow->GetData(L"@width"));

		m_controlWindow->AddControl(new CControlLength("height"));
		m_controlWindow->GetControl("height")->ConnectData(m_controlWindow->GetData(L"@height"));

		m_controlWindow->AddControl(new CXMLControlString("viewBox"));
		m_controlWindow->GetControl("viewBox")->ConnectData(m_controlWindow->GetData(L"@viewBox"));

		AddPreserveAspectRatioControls(this);
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
		if (HandlePreserveAspectRatioControls(this, pControl))
			return;

		/*
		if ((pControl->GetName() == "align") ||
			(pControl->GetName() == "meetOrSlice"))
		{
			_bstr_t align = m_controlWindow->GetControl("align")->GetProperty(NULL);
			_bstr_t meetOrSlice = m_controlWindow->GetControl("meetOrSlice")->GetProperty(NULL);

			_bstr_t value = align + L" " + meetOrSlice;

			m_controlWindow->SetPathNodeValue(L"@preserveAspectRatio", value);
		}
		*/
	}
};

class CSVGEllipseHandler :
	public CXMLControlsHandler,
	public CExternalResourcesRequired
{
public:
	CSVGEllipseHandler()
	{
	}

	virtual void Setup()
	{
		m_controlWindow->AddData(new CXMLStringData(L"@cx", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@cy", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@rx", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@ry", L"0"));

		m_controlWindow->AddControl(new CControlLength("cx"));
		m_controlWindow->GetControl("cx")->ConnectData(m_controlWindow->GetData(L"@cx"));

		m_controlWindow->AddControl(new CControlLength("cy"));
		m_controlWindow->GetControl("cy")->ConnectData(m_controlWindow->GetData(L"@cy"));

		m_controlWindow->AddControl(new CControlLength("rx"));
		m_controlWindow->GetControl("rx")->ConnectData(m_controlWindow->GetData(L"@rx"));

		m_controlWindow->AddControl(new CControlLength("ry"));
		m_controlWindow->GetControl("ry")->ConnectData(m_controlWindow->GetData(L"@ry"));

	// title/descr
		m_controlWindow->AddData(new CXMLStringData(L"title", NULL));
		m_controlWindow->AddData(new CXMLStringData(L"descr", NULL));

		m_controlWindow->AddControl(new CXMLControlString("title"));
		m_controlWindow->GetControl("title")->ConnectData(m_controlWindow->GetData(L"title"));

		m_controlWindow->AddControl(new CXMLControlString("descr"));
		m_controlWindow->GetControl("descr")->ConnectData(m_controlWindow->GetData(L"descr"));

		CExternalResourcesRequired::Setup(m_controlWindow);
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
	}
};

class CSVGCircleHandler :
	public CXMLControlsHandler,
	public CExternalResourcesRequired
{
public:
	CSVGCircleHandler()
	{
	}

	virtual void Setup()
	{
	// Data
		m_controlWindow->AddData(new CXMLStringData(L"@cx", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@cy", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@r", L"0"));

	// Controls
		m_controlWindow->AddControl(new CControlLength("cx"));
		m_controlWindow->GetControl("cx")->ConnectData(m_controlWindow->GetData(L"@cx"));

		m_controlWindow->AddControl(new CControlLength("cy"));
		m_controlWindow->GetControl("cy")->ConnectData(m_controlWindow->GetData(L"@cy"));

		m_controlWindow->AddControl(new CControlLength("r"));
		m_controlWindow->GetControl("r")->ConnectData(m_controlWindow->GetData(L"@r"));

		CExternalResourcesRequired::Setup(m_controlWindow);
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
	}
};

class CSVGRectHandler :
	public CXMLControlsHandler,
	public CExternalResourcesRequired
{
public:
	CSVGRectHandler()
	{
	}

	virtual void Setup()
	{
	// Data
		m_controlWindow->AddData(new CXMLStringData(L"@x", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@y", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@width", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@height", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@rx", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@ry", L"0"));

	// Controls
		m_controlWindow->AddControl(new CControlLength("x"));
		m_controlWindow->GetControl("x")->ConnectData(m_controlWindow->GetData(L"@x"));

		m_controlWindow->AddControl(new CControlLength("y"));
		m_controlWindow->GetControl("y")->ConnectData(m_controlWindow->GetData(L"@y"));

		m_controlWindow->AddControl(new CControlLength("width"));
		m_controlWindow->GetControl("width")->ConnectData(m_controlWindow->GetData(L"@width"));

		m_controlWindow->AddControl(new CControlLength("height"));
		m_controlWindow->GetControl("height")->ConnectData(m_controlWindow->GetData(L"@height"));

		m_controlWindow->AddControl(new CControlLength("rx"));
		m_controlWindow->GetControl("rx")->ConnectData(m_controlWindow->GetData(L"@rx"));

		m_controlWindow->AddControl(new CControlLength("ry"));
		m_controlWindow->GetControl("ry")->ConnectData(m_controlWindow->GetData(L"@ry"));

		CExternalResourcesRequired::Setup(m_controlWindow);
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
	}
};

class CSVGLineHandler :
	public CXMLControlsHandler,
	public CExternalResourcesRequired
{
public:
	CSVGLineHandler()
	{
	}

	virtual void Setup()
	{
	// Data
		m_controlWindow->AddData(new CXMLStringData(L"@x1", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@y1", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@x2", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@y2", L"0"));

	// Controls
		m_controlWindow->AddControl(new CControlLength("x1"));
		m_controlWindow->GetControl("x1")->ConnectData(m_controlWindow->GetData(L"@x1"));

		m_controlWindow->AddControl(new CControlLength("y1"));
		m_controlWindow->GetControl("y1")->ConnectData(m_controlWindow->GetData(L"@y1"));

		m_controlWindow->AddControl(new CControlLength("x2"));
		m_controlWindow->GetControl("x2")->ConnectData(m_controlWindow->GetData(L"@x2"));

		m_controlWindow->AddControl(new CControlLength("y2"));
		m_controlWindow->GetControl("y2")->ConnectData(m_controlWindow->GetData(L"@y2"));

		CExternalResourcesRequired::Setup(m_controlWindow);
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
	}
};

class CSVGImageHandler :
	public CXMLControlsHandler,
	public CExternalResourcesRequired
{
public:
	CSVGImageHandler()
	{
	}

	virtual void Setup()
	{
	// Data
		m_controlWindow->AddData(new CXMLStringData(L"@x", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@y", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@width", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@height", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@preserveAspectRatio", L"xMidYMid meet"));

	// Controls
		m_controlWindow->AddControl(new CControlLength("x"));
		m_controlWindow->GetControl("x")->ConnectData(m_controlWindow->GetData(L"@x"));

		m_controlWindow->AddControl(new CControlLength("y"));
		m_controlWindow->GetControl("y")->ConnectData(m_controlWindow->GetData(L"@y"));

		m_controlWindow->AddControl(new CControlLength("width"));
		m_controlWindow->GetControl("width")->ConnectData(m_controlWindow->GetData(L"@width"));

		m_controlWindow->AddControl(new CControlLength("height"));
		m_controlWindow->GetControl("height")->ConnectData(m_controlWindow->GetData(L"@height"));

		AddPreserveAspectRatioControls(this);
	//
		CExternalResourcesRequired::Setup(m_controlWindow);
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
		if (HandlePreserveAspectRatioControls(this, pControl))
			return;
	}
};

class CSVGVideoHandler :
	public CXMLControlsHandler,
	public CExternalResourcesRequired
{
public:
	CSVGVideoHandler()
	{
	}

	virtual void Setup()
	{
	// Data
		m_controlWindow->AddData(new CXMLStringData(L"@x", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@y", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@width", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@height", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@preserveAspectRatio", L"xMidYMid meet"));

	// Controls
		m_controlWindow->AddControl(new CControlLength("x"));
		m_controlWindow->GetControl("x")->ConnectData(m_controlWindow->GetData(L"@x"));

		m_controlWindow->AddControl(new CControlLength("y"));
		m_controlWindow->GetControl("y")->ConnectData(m_controlWindow->GetData(L"@y"));

		m_controlWindow->AddControl(new CControlLength("width"));
		m_controlWindow->GetControl("width")->ConnectData(m_controlWindow->GetData(L"@width"));

		m_controlWindow->AddControl(new CControlLength("height"));
		m_controlWindow->GetControl("height")->ConnectData(m_controlWindow->GetData(L"@height"));

		AddPreserveAspectRatioControls(this);
	//
		CExternalResourcesRequired::Setup(m_controlWindow);
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
		if (HandlePreserveAspectRatioControls(this, pControl))
			return;
	}
};

class CSVGForeignObjectHandler :
	public CXMLControlsHandler,
	public CExternalResourcesRequired
{
public:
	CSVGForeignObjectHandler()
	{
	}

	virtual void Setup()
	{
	// Data
		m_controlWindow->AddData(new CXMLStringData(L"@x", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@y", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@width", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@height", L"0"));

	// Controls
		m_controlWindow->AddControl(new CControlLength("x"));
		m_controlWindow->GetControl("x")->ConnectData(m_controlWindow->GetData(L"@x"));

		m_controlWindow->AddControl(new CControlLength("y"));
		m_controlWindow->GetControl("y")->ConnectData(m_controlWindow->GetData(L"@y"));

		m_controlWindow->AddControl(new CControlLength("width"));
		m_controlWindow->GetControl("width")->ConnectData(m_controlWindow->GetData(L"@width"));

		m_controlWindow->AddControl(new CControlLength("height"));
		m_controlWindow->GetControl("height")->ConnectData(m_controlWindow->GetData(L"@height"));

		CExternalResourcesRequired::Setup(m_controlWindow);
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
	}
};

class CSVGUseHandler :
	public CXMLControlsHandler,
	public CExternalResourcesRequired
{
public:
	CSVGUseHandler()
	{
	}

	virtual void Setup()
	{
	// Data
		m_controlWindow->AddData(new CXMLStringData(L"@x", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@y", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@width", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@height", L"0"));

	// Controls
		m_controlWindow->AddControl(new CControlLength("x"));
		m_controlWindow->GetControl("x")->ConnectData(m_controlWindow->GetData(L"@x"));

		m_controlWindow->AddControl(new CControlLength("y"));
		m_controlWindow->GetControl("y")->ConnectData(m_controlWindow->GetData(L"@y"));

		m_controlWindow->AddControl(new CControlLength("width"));
		m_controlWindow->GetControl("width")->ConnectData(m_controlWindow->GetData(L"@width"));

		m_controlWindow->AddControl(new CControlLength("height"));
		m_controlWindow->GetControl("height")->ConnectData(m_controlWindow->GetData(L"@height"));

		CExternalResourcesRequired::Setup(m_controlWindow);
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
	}
};

class CSVGSymbolHandler : public CXMLControlsHandler
{
public:
	CSVGSymbolHandler()
	{
	}

	virtual void Setup()
	{
	// Data
		m_controlWindow->AddData(new CXMLStringData(L"@viewBox", L"0"));

	// Controls
		m_controlWindow->AddControl(new CXMLControlString("viewBox"));
		m_controlWindow->GetControl("viewBox")->ConnectData(m_controlWindow->GetData(L"@viewBox"));
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
	}
};

class CSVGTextHandler :
	public CXMLControlsHandler
{
public:
	CSVGTextHandler()
	{
	}

	virtual void Setup()
	{
	// Data
		m_controlWindow->AddData(new CXMLStringData(L"@x", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@y", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@dx", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@dy", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@rotate", L"0"));

	// Controls
		m_controlWindow->AddControl(new CXMLControlString("x"));
		m_controlWindow->GetControl("x")->ConnectData(m_controlWindow->GetData(L"@x"));

		m_controlWindow->AddControl(new CXMLControlString("y"));
		m_controlWindow->GetControl("y")->ConnectData(m_controlWindow->GetData(L"@y"));

		m_controlWindow->AddControl(new CXMLControlString("dx"));
		m_controlWindow->GetControl("dx")->ConnectData(m_controlWindow->GetData(L"@dx"));

		m_controlWindow->AddControl(new CXMLControlString("dy"));
		m_controlWindow->GetControl("dy")->ConnectData(m_controlWindow->GetData(L"@dy"));

		m_controlWindow->AddControl(new CXMLControlString("rotate"));
		m_controlWindow->GetControl("rotate")->ConnectData(m_controlWindow->GetData(L"@rotate"));
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
	}
};

class CSVGTSpanHandler :
	public CXMLControlsHandler
{
public:
	CSVGTSpanHandler()
	{
	}

	virtual void Setup()
	{
	// Data
		m_controlWindow->AddData(new CXMLStringData(L"@x", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@y", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@dx", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@dy", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@rotate", L"0"));

	// Controls
		m_controlWindow->AddControl(new CXMLControlString("x"));
		m_controlWindow->GetControl("x")->ConnectData(m_controlWindow->GetData(L"@x"));

		m_controlWindow->AddControl(new CXMLControlString("y"));
		m_controlWindow->GetControl("y")->ConnectData(m_controlWindow->GetData(L"@y"));

		m_controlWindow->AddControl(new CXMLControlString("dx"));
		m_controlWindow->GetControl("dx")->ConnectData(m_controlWindow->GetData(L"@dx"));

		m_controlWindow->AddControl(new CXMLControlString("dy"));
		m_controlWindow->GetControl("dy")->ConnectData(m_controlWindow->GetData(L"@dy"));

		m_controlWindow->AddControl(new CXMLControlString("rotate"));
		m_controlWindow->GetControl("rotate")->ConnectData(m_controlWindow->GetData(L"@rotate"));
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
	}
};

class CSVGTRefHandler : public CXMLControlsHandler
{
public:
	CSVGTRefHandler()
	{
	}

	virtual void Setup()
	{
	// Data
		m_controlWindow->AddData(new CXMLStringData(L"@x", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@y", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@dx", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@dy", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@rotate", L"0"));

	// Controls
		m_controlWindow->AddControl(new CXMLControlString("x"));
		m_controlWindow->GetControl("x")->ConnectData(m_controlWindow->GetData(L"@x"));

		m_controlWindow->AddControl(new CXMLControlString("y"));
		m_controlWindow->GetControl("y")->ConnectData(m_controlWindow->GetData(L"@y"));

		m_controlWindow->AddControl(new CXMLControlString("dx"));
		m_controlWindow->GetControl("dx")->ConnectData(m_controlWindow->GetData(L"@dx"));

		m_controlWindow->AddControl(new CXMLControlString("dy"));
		m_controlWindow->GetControl("dy")->ConnectData(m_controlWindow->GetData(L"@dy"));

		m_controlWindow->AddControl(new CXMLControlString("rotate"));
		m_controlWindow->GetControl("rotate")->ConnectData(m_controlWindow->GetData(L"@rotate"));
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
	}
};

class CSVGTextPathHandler : public CXMLControlsHandler
{
public:
	CSVGTextPathHandler()
	{
	}

	virtual void Setup()
	{
	// Data
		m_controlWindow->AddData(new CXMLStringData(L"@startOffset", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@method", L"align"));

	// Controls
		m_controlWindow->AddControl(new CControlLength("startOffset"));
		m_controlWindow->GetControl("startOffset")->ConnectData(m_controlWindow->GetData(L"@startOffset"));

		m_controlWindow->AddControl(new CXMLControlPopup("method", L"align|stretch"));
		m_controlWindow->GetControl("method")->ConnectData(m_controlWindow->GetData(L"@method"));
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
	}
};

class CSVGFontFaceHandler : public CXMLControlsHandler
{
public:
	CSVGFontFaceHandler()
	{
	}

	virtual void Setup()
	{
	// Data
		m_controlWindow->AddData(new CXMLStringData(L"@font-family", L""));
		m_controlWindow->AddData(new CXMLStringData(L"@units-per-em", L""));
		m_controlWindow->AddData(new CXMLStringData(L"@x-height", L""));
		m_controlWindow->AddData(new CXMLStringData(L"@ascent", L""));
		m_controlWindow->AddData(new CXMLStringData(L"@descent", L""));

	// Controls
		m_controlWindow->AddControl(new CXMLControlString("font-family"));
		m_controlWindow->GetControl("font-family")->ConnectData(m_controlWindow->GetData(L"@font-family"));

		m_controlWindow->AddControl(new CXMLControlNumber("units-per-em"));
		m_controlWindow->GetControl("units-per-em")->ConnectData(m_controlWindow->GetData(L"@units-per-em"));

		m_controlWindow->AddControl(new CXMLControlNumber("x-height"));
		m_controlWindow->GetControl("x-height")->ConnectData(m_controlWindow->GetData(L"@x-height"));

		m_controlWindow->AddControl(new CXMLControlNumber("ascent"));
		m_controlWindow->GetControl("ascent")->ConnectData(m_controlWindow->GetData(L"@ascent"));

		m_controlWindow->AddControl(new CXMLControlNumber("descent"));
		m_controlWindow->GetControl("descent")->ConnectData(m_controlWindow->GetData(L"@descent"));
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
	}
};

class CSVGFontHandler : public CXMLControlsHandler
{
public:
	CSVGFontHandler()
	{
	}

	virtual void Setup()
	{
	// Data
		m_controlWindow->AddData(new CXMLStringData(L"@horiz-origin-x", L""));
		m_controlWindow->AddData(new CXMLStringData(L"@horiz-origin-y", L""));

	// Controls
		m_controlWindow->AddControl(new CXMLControlNumber("horiz-origin-x"));
		m_controlWindow->GetControl("horiz-origin-x")->ConnectData(m_controlWindow->GetData(L"@horiz-origin-x"));

		m_controlWindow->AddControl(new CXMLControlNumber("horiz-origin-y"));
		m_controlWindow->GetControl("horiz-origin-y")->ConnectData(m_controlWindow->GetData(L"@horiz-origin-y"));
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
	}
};

class CSVGPatternHandler : public CXMLControlsHandler
{
public:
	CSVGPatternHandler()
	{
	}

	virtual void Setup()
	{
	// Data
		m_controlWindow->AddData(new CXMLStringData(L"@x", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@y", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@width", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@height", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@patternUnits", L"objectBoundingBox"));
		m_controlWindow->AddData(new CXMLStringData(L"@patternContentUnits", L"userSpaceOnUse"));
		m_controlWindow->AddData(new CXMLStringData(L"@viewBox", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@preserveAspectRatio", L"xMidYMid meet"));

	// Controls
		m_controlWindow->AddControl(new CControlLength("x"));
		m_controlWindow->GetControl("x")->ConnectData(m_controlWindow->GetData(L"@x"));

		m_controlWindow->AddControl(new CControlLength("y"));
		m_controlWindow->GetControl("y")->ConnectData(m_controlWindow->GetData(L"@y"));

		m_controlWindow->AddControl(new CControlLength("width"));
		m_controlWindow->GetControl("width")->ConnectData(m_controlWindow->GetData(L"@width"));

		m_controlWindow->AddControl(new CControlLength("height"));
		m_controlWindow->GetControl("height")->ConnectData(m_controlWindow->GetData(L"@height"));

		m_controlWindow->AddControl(new CXMLControlPopup("patternUnits", L"userSpaceOnUse|objectBoundingBox"));
		m_controlWindow->GetControl("patternUnits")->ConnectData(m_controlWindow->GetData(L"@patternUnits"));

		m_controlWindow->AddControl(new CXMLControlPopup("patternContentUnits", L"userSpaceOnUse|objectBoundingBox"));
		m_controlWindow->GetControl("patternContentUnits")->ConnectData(m_controlWindow->GetData(L"@patternContentUnits"));

		AddPreserveAspectRatioControls(this);
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
		if (HandlePreserveAspectRatioControls(this, pControl))
			return;
	}
};

class CSVGLinearGradientHandler : public CXMLControlsHandler
{
public:
	CSVGLinearGradientHandler()
	{
	}

	virtual void Setup()
	{
	// Data
		m_controlWindow->AddData(new CXMLStringData(L"@x1", L"0%"));
		m_controlWindow->AddData(new CXMLStringData(L"@y1", L"0%"));
		m_controlWindow->AddData(new CXMLStringData(L"@x2", L"100%"));
		m_controlWindow->AddData(new CXMLStringData(L"@y2", L"0%"));
		m_controlWindow->AddData(new CXMLStringData(L"@gradientUnits", L"objectBoundingBox"));
		m_controlWindow->AddData(new CXMLStringData(L"@spreadMethod", L"pad"));

	// Controls
		m_controlWindow->AddControl(new CControlLength("x1"));
		m_controlWindow->GetControl("x1")->ConnectData(m_controlWindow->GetData(L"@x1"));

		m_controlWindow->AddControl(new CControlLength("y1"));
		m_controlWindow->GetControl("y1")->ConnectData(m_controlWindow->GetData(L"@y1"));

		m_controlWindow->AddControl(new CControlLength("x2"));
		m_controlWindow->GetControl("x2")->ConnectData(m_controlWindow->GetData(L"@x2"));

		m_controlWindow->AddControl(new CControlLength("y2"));
		m_controlWindow->GetControl("y2")->ConnectData(m_controlWindow->GetData(L"@y2"));

		m_controlWindow->AddControl(new CXMLControlPopup("gradientUnits", L"userSpaceOnUse|objectBoundingBox"));
		m_controlWindow->GetControl("gradientUnits")->ConnectData(m_controlWindow->GetData(L"@gradientUnits"));

		m_controlWindow->AddControl(new CXMLControlPopup("spreadMethod", L"pad|reflect|repeat"));
		m_controlWindow->GetControl("spreadMethod")->ConnectData(m_controlWindow->GetData(L"@spreadMethod"));
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
	}
};

class CSVGRadialGradientHandler : public CXMLControlsHandler
{
public:
	CSVGRadialGradientHandler()
	{
	}

	virtual void Setup()
	{
	// Data
		m_controlWindow->AddData(new CXMLStringData(L"cx", L"0%"));
		m_controlWindow->AddData(new CXMLStringData(L"cy", L"0%"));
		m_controlWindow->AddData(new CXMLStringData(L"r", L"100%"));
		m_controlWindow->AddData(new CXMLStringData(L"fx", L"0%"));
		m_controlWindow->AddData(new CXMLStringData(L"fy", L"0%"));
		m_controlWindow->AddData(new CXMLStringData(L"gradientUnits", L"objectBoundingBox"));
		m_controlWindow->AddData(new CXMLStringData(L"spreadMethod", L"pad"));

	// Controls
		m_controlWindow->AddControl(new CControlLength("cx"));
		m_controlWindow->GetControl("cx")->ConnectData(m_controlWindow->GetData(L"cx"));

		m_controlWindow->AddControl(new CControlLength("cy"));
		m_controlWindow->GetControl("cy")->ConnectData(m_controlWindow->GetData(L"cy"));

		m_controlWindow->AddControl(new CControlLength("r"));
		m_controlWindow->GetControl("r")->ConnectData(m_controlWindow->GetData(L"r"));

		m_controlWindow->AddControl(new CControlLength("fx"));
		m_controlWindow->GetControl("fx")->ConnectData(m_controlWindow->GetData(L"fx"));

		m_controlWindow->AddControl(new CControlLength("fy"));
		m_controlWindow->GetControl("fy")->ConnectData(m_controlWindow->GetData(L"fy"));

		m_controlWindow->AddControl(new CXMLControlPopup("gradientUnits", L"userSpaceOnUse|objectBoundingBox"));
		m_controlWindow->GetControl("gradientUnits")->ConnectData(m_controlWindow->GetData(L"gradientUnits"));

		m_controlWindow->AddControl(new CXMLControlPopup("spreadMethod", L"pad|reflect|repeat"));
		m_controlWindow->GetControl("spreadMethod")->ConnectData(m_controlWindow->GetData(L"spreadMethod"));
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
	}
};

class CSVGStopHandler : public CXMLControlsHandler
{
public:
	CSVGStopHandler()
	{
	}

	virtual void Setup()
	{
	// Data
		m_controlWindow->AddData(new CXMLStringData(L"@offset", L"0"));

	// Controls
		m_controlWindow->AddControl(new CXMLControlNumber("offset"));
		m_controlWindow->GetControl("offset")->ConnectData(m_controlWindow->GetData(L"@offset"));
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
	}
};

class CSVGStyleHandler : public CXMLControlsHandler
{
public:
	CSVGStyleHandler()
	{
	}

	virtual void Setup()
	{
	// Data
		m_controlWindow->AddData(new CXMLStringData(L"type", L""));
		m_controlWindow->AddData(new CXMLStringData(L"media", L""));
		m_controlWindow->AddData(new CXMLStringData(L"title", L""));

	// Controls
		m_controlWindow->AddControl(new CXMLControlString("type"));
		m_controlWindow->GetControl("type")->ConnectData(m_controlWindow->GetData(L"type"));

		m_controlWindow->AddControl(new CXMLControlPopup("media", L"all|aural|braille|embossed|handheld|print|projection|screen|tty|tv"));
		m_controlWindow->GetControl("media")->ConnectData(m_controlWindow->GetData(L"media"));

		m_controlWindow->AddControl(new CXMLControlString("title"));
		m_controlWindow->GetControl("title")->ConnectData(m_controlWindow->GetData(L"title"));
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
	}
};

class CSVGMaskHandler : public CXMLControlsHandler
{
public:
	CSVGMaskHandler()
	{
	}

	virtual void Setup()
	{
	// Add data
		m_controlWindow->AddData(new CXMLStringData(L"x", L"-10%"));
		m_controlWindow->AddData(new CXMLStringData(L"y", L"-10%"));
		m_controlWindow->AddData(new CXMLStringData(L"width", L"120%"));
		m_controlWindow->AddData(new CXMLStringData(L"height", L"120%"));
		m_controlWindow->AddData(new CXMLStringData(L"maskUnits", L"objectBoundingBox"));
		m_controlWindow->AddData(new CXMLStringData(L"maskContentUnits", L"userSpaceOnUse"));

	// Add controls
		m_controlWindow->AddControl(new CControlLength("x"));
		m_controlWindow->GetControl("x")->ConnectData(m_controlWindow->GetData(L"x"));

		m_controlWindow->AddControl(new CControlLength("y"));
		m_controlWindow->GetControl("y")->ConnectData(m_controlWindow->GetData(L"y"));

		m_controlWindow->AddControl(new CControlLength("width"));
		m_controlWindow->GetControl("width")->ConnectData(m_controlWindow->GetData(L"width"));

		m_controlWindow->AddControl(new CControlLength("height"));
		m_controlWindow->GetControl("height")->ConnectData(m_controlWindow->GetData(L"height"));

		m_controlWindow->AddControl(new CXMLControlPopup("maskUnits", L"objectBoundingBox|userSpaceOnUse"));
		m_controlWindow->GetControl("maskUnits")->ConnectData(m_controlWindow->GetData(L"maskUnits"));

		m_controlWindow->AddControl(new CXMLControlPopup("maskContentUnits", L"objectBoundingBox|userSpaceOnUse"));
		m_controlWindow->GetControl("maskContentUnits")->ConnectData(m_controlWindow->GetData(L"maskContentUnits"));
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
	}
};

class CSVGFilterHandler : public CXMLControlsHandler
{
public:
	CSVGFilterHandler()
	{
	}

	virtual void Setup()
	{
	// Add data
		m_controlWindow->AddData(new CXMLStringData(L"@x", L"-10%"));
		m_controlWindow->AddData(new CXMLStringData(L"@y", L"-10%"));
		m_controlWindow->AddData(new CXMLStringData(L"@width", L"120%"));
		m_controlWindow->AddData(new CXMLStringData(L"@height", L"120%"));
		m_controlWindow->AddData(new CXMLStringData(L"@filterUnits", L"objectBoundingBox"));
		m_controlWindow->AddData(new CXMLStringData(L"@primitiveUnits", L"userSpaceOnUse"));

	// Add controls
		m_controlWindow->AddControl(new CControlLength("x"));
		m_controlWindow->GetControl("x")->ConnectData(m_controlWindow->GetData(L"@x"));

		m_controlWindow->AddControl(new CControlLength("y"));
		m_controlWindow->GetControl("y")->ConnectData(m_controlWindow->GetData(L"@y"));

		m_controlWindow->AddControl(new CControlLength("width"));
		m_controlWindow->GetControl("width")->ConnectData(m_controlWindow->GetData(L"@width"));

		m_controlWindow->AddControl(new CControlLength("height"));
		m_controlWindow->GetControl("height")->ConnectData(m_controlWindow->GetData(L"@height"));

		m_controlWindow->AddControl(new CXMLControlPopup("filterUnits", L"objectBoundingBox|userSpaceOnUse"));
		m_controlWindow->GetControl("filterUnits")->ConnectData(m_controlWindow->GetData(L"@filterUnits"));

		m_controlWindow->AddControl(new CXMLControlPopup("primitiveUnits", L"objectBoundingBox|userSpaceOnUse"));
		m_controlWindow->GetControl("primitiveUnits")->ConnectData(m_controlWindow->GetData(L"@primitiveUnits"));
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
	}
};

class CSVGFEBlendHandler : public CXMLControlsHandler
{
public:
	CSVGFEBlendHandler()
	{
	}

	virtual void Setup()
	{
	// Add data
		m_controlWindow->AddData(new CXMLStringData(L"@mode", L"normal"));

	// Add controls
		m_controlWindow->AddControl(new CXMLControlPopup("mode", L"normal|multiply|screen|darken|lighten"));
		m_controlWindow->GetControl("mode")->ConnectData(m_controlWindow->GetData(L"@mode"));
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
	}
};

class CSVGFEGaussianBlurHandler : public CXMLControlsHandler
{
public:
	CSVGFEGaussianBlurHandler()
	{
	}

	virtual void Setup()
	{
	// Add data
		m_controlWindow->AddData(new CXMLStringData(L"@stdDeviation", L"0"));

	// Add controls
		m_controlWindow->AddControl(new CXMLControlString("stdDeviation"));
		m_controlWindow->GetControl("stdDeviation")->ConnectData(m_controlWindow->GetData(L"@stdDeviation"));
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
	}
};

class CSVGFEOffsetHandler : public CXMLControlsHandler
{
public:
	CSVGFEOffsetHandler()
	{
	}

	virtual void Setup()
	{
	// Add data
		m_controlWindow->AddData(new CXMLStringData(L"@dx", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@dy", L"0"));

	// Add controls
		m_controlWindow->AddControl(new CXMLControlNumber("dx"));
		m_controlWindow->GetControl("dx")->ConnectData(m_controlWindow->GetData(L"@dx"));

		m_controlWindow->AddControl(new CXMLControlNumber("dy"));
		m_controlWindow->GetControl("dy")->ConnectData(m_controlWindow->GetData(L"@dy"));
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
	}
};

class CSVGFECompositeHandler : public CXMLControlsHandler
{
public:
	CSVGFECompositeHandler()
	{
	}

	virtual void Setup()
	{
	// Add data
		m_controlWindow->AddData(new CXMLStringData(L"@operator", L"over"));
		m_controlWindow->AddData(new CXMLStringData(L"@k1", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@k2", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@k3", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@k4", L"0"));

	// Add controls
		m_controlWindow->AddControl(new CXMLControlPopup("operator", L"over|in|out|atop|xor|arithmetic"));
		m_controlWindow->GetControl("operator")->ConnectData(m_controlWindow->GetData(L"@operator"));

		m_controlWindow->AddControl(new CXMLControlNumber("k1"));
		m_controlWindow->GetControl("k1")->ConnectData(m_controlWindow->GetData(L"@k1"));

		m_controlWindow->AddControl(new CXMLControlNumber("k2"));
		m_controlWindow->GetControl("k2")->ConnectData(m_controlWindow->GetData(L"@k2"));

		m_controlWindow->AddControl(new CXMLControlNumber("k3"));
		m_controlWindow->GetControl("k3")->ConnectData(m_controlWindow->GetData(L"@k3"));

		m_controlWindow->AddControl(new CXMLControlNumber("k4"));
		m_controlWindow->GetControl("k4")->ConnectData(m_controlWindow->GetData(L"@k4"));
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
	}
};

class CSVGFESpecularLightingHandler : public CXMLControlsHandler
{
public:
	CSVGFESpecularLightingHandler()
	{
	}

	virtual void Setup()
	{
	// Add data
		m_controlWindow->AddData(new CXMLStringData(L"@surfaceScale", L"1"));
		m_controlWindow->AddData(new CXMLStringData(L"@specularConstant", L"1"));
		m_controlWindow->AddData(new CXMLStringData(L"@specularExponent", L"1"));

	// Add controls
		m_controlWindow->AddControl(new CXMLControlNumber("surfaceScale"));
		m_controlWindow->GetControl("surfaceScale")->ConnectData(m_controlWindow->GetData(L"@surfaceScale"));

		m_controlWindow->AddControl(new CXMLControlNumber("specularConstant"));
		m_controlWindow->GetControl("specularConstant")->ConnectData(m_controlWindow->GetData(L"@specularConstant"));

		m_controlWindow->AddControl(new CXMLControlNumber("specularExponent"));
		m_controlWindow->GetControl("specularExponent")->ConnectData(m_controlWindow->GetData(L"@specularExponent"));

		m_controlWindow->AddControl(new CXMLControlPopup("LightType", L"Distant|Point|Spot"));
		//m_controlWindow->GetControl("LightType")->ConnectData(m_controlWindow->GetData(L"LightType"));

		DWORD dw = 0;

		if (/*m_controlWindow->*/PathNodeExists(L"feDistantLight"))
			dw |= 1;

		if (/*m_controlWindow->*/PathNodeExists(L"fePointLight"))
			dw |= 2;

		if (/*m_controlWindow->*/PathNodeExists(L"feSpotLight"))
			dw |= 4;

		if (dw == 1)
			m_controlWindow->GetControl("LightType")->SetProperty(NULL, _bstr_t(L"Distant"));
		else if (dw == 2)
			m_controlWindow->GetControl("LightType")->SetProperty(NULL, _bstr_t(L"Point"));
		else if (dw == 4)
			m_controlWindow->GetControl("LightType")->SetProperty(NULL, _bstr_t(L"Spot"));
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
		if (pControl->GetName() == _T("LightType"))
		{
			_bstr_t value = pControl->GetProperty(NULL);

			if (!wcscmp(value, L"Distant"))
			{
				/*m_controlWindow->*/SetPathNodeValue(L"fePointLight", NULL);
				/*m_controlWindow->*/SetPathNodeValue(L"feSpotLight", NULL);

				/*m_controlWindow->*/SetPathNodeValue(L"feDistantLight/@azimuth", L"0");
				/*m_controlWindow->*/SetPathNodeValue(L"feDistantLight/@elevation", L"0");
			}
			else if (!wcscmp(value, L"Point"))
			{
				/*m_controlWindow->*/SetPathNodeValue(L"feDistantLight", NULL);
				/*m_controlWindow->*/SetPathNodeValue(L"feSpotLight", NULL);

				/*m_controlWindow->*/SetPathNodeValue(L"fePointLight/@x", L"0");
				/*m_controlWindow->*/SetPathNodeValue(L"fePointLight/@y", L"0");
				/*m_controlWindow->*/SetPathNodeValue(L"fePointLight/@z", L"0");
			}
			else if (!wcscmp(value, L"Spot"))
			{
				/*m_controlWindow->*/SetPathNodeValue(L"feDistantLight", NULL);
				/*m_controlWindow->*/SetPathNodeValue(L"fePointLight", NULL);

				/*m_controlWindow->*/SetPathNodeValue(L"feSpotLight/@x", L"0");
				/*m_controlWindow->*/SetPathNodeValue(L"feSpotLight/@y", L"0");
				/*m_controlWindow->*/SetPathNodeValue(L"feSpotLight/@z", L"0");
				/*m_controlWindow->*/SetPathNodeValue(L"feSpotLight/@pointsAtX", L"0");
				/*m_controlWindow->*/SetPathNodeValue(L"feSpotLight/@pointsAtY", L"0");
				/*m_controlWindow->*/SetPathNodeValue(L"feSpotLight/@pointsAtZ", L"0");
			}
		}
	}
};

class CSVGFEDiffuseLightingHandler : public CXMLControlsHandler
{
public:
	CSVGFEDiffuseLightingHandler()
	{
	}

	virtual void Setup()
	{
	// Add data
		m_controlWindow->AddData(new CXMLStringData(L"@surfaceScale", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@diffuseConstant", L"0"));

	//	m_controlWindow->AddData(new CXMLStringData(L"LightType", NULL));

	// Add controls
		m_controlWindow->AddControl(new CXMLControlNumber("surfaceScale"));
		m_controlWindow->GetControl("surfaceScale")->ConnectData(m_controlWindow->GetData(L"@surfaceScale"));

		m_controlWindow->AddControl(new CXMLControlNumber("diffuseConstant"));
		m_controlWindow->GetControl("diffuseConstant")->ConnectData(m_controlWindow->GetData(L"@diffuseConstant"));

		m_controlWindow->AddControl(new CXMLControlPopup("LightType", L"Distant|Point|Spot"));
		//m_controlWindow->GetControl("LightType")->ConnectData(m_controlWindow->GetData(L"LightType"));

		DWORD dw = 0;

		if (/*m_controlWindow->*/PathNodeExists(L"feDistantLight"))
			dw |= 1;

		if (/*m_controlWindow->*/PathNodeExists(L"fePointLight"))
			dw |= 2;

		if (/*m_controlWindow->*/PathNodeExists(L"feSpotLight"))
			dw |= 4;

		if (dw == 1)
			m_controlWindow->GetControl("LightType")->SetProperty(NULL, _bstr_t(L"Distant"));
		else if (dw == 2)
			m_controlWindow->GetControl("LightType")->SetProperty(NULL, _bstr_t(L"Point"));
		else if (dw == 4)
			m_controlWindow->GetControl("LightType")->SetProperty(NULL, _bstr_t(L"Spot"));
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
		if (pControl->GetName() == _T("LightType"))
		{
			_bstr_t value = pControl->GetProperty(NULL);

			if (!wcscmp(value, L"Distant"))
			{
				/*m_controlWindow->*/SetPathNodeValue(L"feDistantLight/@azimuth", L"0");
				/*m_controlWindow->*/SetPathNodeValue(L"feDistantLight/@elevation", L"0");

				/*
				CComPtr<IWebXMLViewGroup> viewGroup;
				m_controlWindow->GetViewGroup(&viewGroup);

				long ncount;
				m_viewGroup->GetSelectedCount(&ncount);

				for (int i = 0; i < ncount; i++)
				{
					CComPtr<IESelectedElement> selectedElement;
					m_viewGroup->GetSelectedElementN(i, &selectedElement);

					CComPtr<IEElement> eElement;
					selectedElement->get_eElement(&eElement);

					CComPtr<ILDOMElement> domElement;
					eElement->get_domElement(&domElement);

					_bstr_t value = pData->GetValueAsString();

					if ((BSTR)value != NULL)
					{
						SetPathNodeValue(domElement, pData->m_name, value);
					}
					else
						ASSERT(0);
				}
			*/
			}
		}
	}
};

class CSVGFEPointLightHandler : public CXMLControlsHandler
{
public:
	CSVGFEPointLightHandler()
	{
	}

	virtual void Setup()
	{
	// Add data
		m_controlWindow->AddData(new CXMLStringData(L"@x", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@y", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@z", L"0"));

	// Add controls
		m_controlWindow->AddControl(new CXMLControlNumber("x"));
		m_controlWindow->GetControl("x")->ConnectData(m_controlWindow->GetData(L"@x"));

		m_controlWindow->AddControl(new CXMLControlNumber("y"));
		m_controlWindow->GetControl("y")->ConnectData(m_controlWindow->GetData(L"@y"));

		m_controlWindow->AddControl(new CXMLControlNumber("z"));
		m_controlWindow->GetControl("z")->ConnectData(m_controlWindow->GetData(L"@z"));
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
	}
};

class CSVGFESpotLightHandler : public CXMLControlsHandler
{
public:
	CSVGFESpotLightHandler()
	{
	}

	virtual void Setup()
	{
	// Add data
		m_controlWindow->AddData(new CXMLStringData(L"@x", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@y", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@z", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@pointsAtX", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@pointsAtY", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@pointsAtZ", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@specularExponent", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@limitingConeAngle", L"0")); 

	// Add controls
		m_controlWindow->AddControl(new CXMLControlNumber("x"));
		m_controlWindow->GetControl("x")->ConnectData(m_controlWindow->GetData(L"@x"));

		m_controlWindow->AddControl(new CXMLControlNumber("y"));
		m_controlWindow->GetControl("y")->ConnectData(m_controlWindow->GetData(L"@y"));

		m_controlWindow->AddControl(new CXMLControlNumber("z"));
		m_controlWindow->GetControl("z")->ConnectData(m_controlWindow->GetData(L"@z"));

		m_controlWindow->AddControl(new CXMLControlNumber("pointsAtX"));
		m_controlWindow->GetControl("pointsAtX")->ConnectData(m_controlWindow->GetData(L"@pointsAtX"));

		m_controlWindow->AddControl(new CXMLControlNumber("pointsAtY"));
		m_controlWindow->GetControl("pointsAtY")->ConnectData(m_controlWindow->GetData(L"@pointsAtY"));

		m_controlWindow->AddControl(new CXMLControlNumber("pointsAtZ"));
		m_controlWindow->GetControl("pointsAtZ")->ConnectData(m_controlWindow->GetData(L"@pointsAtZ"));

		m_controlWindow->AddControl(new CXMLControlNumber("specularExponent"));
		m_controlWindow->GetControl("specularExponent")->ConnectData(m_controlWindow->GetData(L"@specularExponent"));

		m_controlWindow->AddControl(new CXMLControlNumber("limitingConeAngle"));
		m_controlWindow->GetControl("limitingConeAngle")->ConnectData(m_controlWindow->GetData(L"@limitingConeAngle"));
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
	}
};

class CSVGFEDistantLightHandler : public CXMLControlsHandler
{
public:
	CSVGFEDistantLightHandler()
	{
	}

	virtual void Setup()
	{
	// Add data
		m_controlWindow->AddData(new CXMLStringData(L"@azimuth", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@elevation", L"0"));

	// Add controls
		m_controlWindow->AddControl(new CXMLControlDistantLight("light"));
		m_controlWindow->GetControl("light")->ConnectData(m_controlWindow->GetData(L"@azimuth"), L"azimuth");
		m_controlWindow->GetControl("light")->ConnectData(m_controlWindow->GetData(L"@elevation"), L"elevation");

		m_controlWindow->AddControl(new CXMLControlNumber("azimuth"));
		m_controlWindow->GetControl("azimuth")->ConnectData(m_controlWindow->GetData(L"@azimuth"));

		m_controlWindow->AddControl(new CXMLControlNumber("elevation"));
		m_controlWindow->GetControl("elevation")->ConnectData(m_controlWindow->GetData(L"@elevation"));
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
	}
};


class CSVGFEColorMatrixHandler : public CXMLControlsHandler
{
public:
	CSVGFEColorMatrixHandler()
	{
	}

	virtual void Setup()
	{
	// Add data
		m_controlWindow->AddData(new CXMLStringData(L"@type", L""));
		m_controlWindow->AddData(new CSVGNumberListData(L"@values", L"0"));

	// Add controls
		m_controlWindow->AddControl(new CXMLControlPopup("type", L"matrix|saturate|hueRotate|luminanceToAlpha"));
		m_controlWindow->GetControl("type")->ConnectData(m_controlWindow->GetData(L"@type"));

		m_controlWindow->AddControl(new CXMLControlHueRotate("hueRotate"));
		m_controlWindow->GetControl("hueRotate")->ConnectData(m_controlWindow->GetData(L"@values"));

		m_controlWindow->AddControl(new CXMLControlNumber("singleValueEdit"));
		m_controlWindow->GetControl("singleValueEdit")->ConnectData(m_controlWindow->GetData(L"@values"));

		m_controlWindow->AddControl(new CXMLControlSlider("saturateSlider", 0, 1));
		m_controlWindow->GetControl("saturateSlider")->ConnectData(m_controlWindow->GetData(L"@values"));

		m_controlWindow->AddControl(new CXMLControlColorMatrix("matrix"));
		m_controlWindow->GetControl("matrix")->ConnectData(m_controlWindow->GetData(L"@values"));

	//
//							p->m_attrsListWnd.m_pControlsHandler = new CFEColorMatrixControlsHandler;
//							p->m_attrsListWnd.m_pControlsHandler->m_controlWindow = &p->m_attrsListWnd;
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
		if (pControl->GetName() == "type")
		{
			_bstr_t type = _bstr_t(pControl->GetProperty(NULL));

			m_controlWindow->GetControl("hueRotate")->SetVisible(!wcscmp(type, L"hueRotate"));
			m_controlWindow->GetControl("singleValueEdit")->SetVisible(!wcscmp(type, L"hueRotate") || !wcscmp(type, L"saturate"));
			m_controlWindow->GetControl("saturateSlider")->SetVisible(!wcscmp(type, L"saturate"));
			m_controlWindow->GetControl("matrix")->SetVisible(!wcscmp(type, L"matrix"));

#if 0
			if (!wcscmp(pControl->m_pData->GetValueAsString(), L"matrix"))
			{
				m_controlWindow->GetData(L"values")->SetValue(L"1 0 0 0 0  0 1 0 0 0  0 0 1 0 0  0 0 0 1 0");
			}
			else if (!wcscmp(pControl->m_pData->GetValueAsString(), L"saturate"))
			{
				m_controlWindow->GetData(L"values")->SetValue(L"1");
			}
			else if (!wcscmp(pControl->m_pData->GetValueAsString(), L"hueRotate"))
			{
				m_controlWindow->GetData(L"values")->SetValue(L"0");
			}
			else if (!wcscmp(pControl->m_pData->GetValueAsString(), L"luminanceToAlpha"))
			{
				m_controlWindow->GetData(L"values")->SetValue(L"");	// This removes the attribute
			}
#endif
		}
	}
};

class CSVGFEComponentTransferHandler : public CXMLControlsHandler
{
public:
	CSVGFEComponentTransferHandler()
	{
	}

	virtual void Setup()
	{
	// Add data
		/*
		p->m_attrsListWnd.AddData(new CXMLStringData(L"dx", L"0", XMLTYPE_LENGTH()));
		p->m_attrsListWnd.AddData(new CXMLStringData(L"dy", L"0", XMLTYPE_LENGTH()));
		*/

	// Add controls

		m_controlWindow->AddControl(new CXMLControlPopup("channel", L"RGB|RGBA|R|G|B|A"));

		m_controlWindow->AddControl(new CXMLControlPopup("type", L"identity|table|discrete|linear|gamma"));

	//	p->m_attrsListWnd.AddControl(new CXMLControlNumber("dy"));
	//	p->m_attrsListWnd.GetControl("dy")->ConnectData(p->m_attrsListWnd.GetData(L"dy"));

		m_controlWindow->AddControl(new CXMLControlNumber("slope"));
		m_controlWindow->AddControl(new CXMLControlNumber("intercept"));
		m_controlWindow->AddControl(new CXMLControlNumber("amplitude"));
		m_controlWindow->AddControl(new CXMLControlNumber("exponent"));
		m_controlWindow->AddControl(new CXMLControlNumber("offset"));

		m_controlWindow->AddControl(new CXMLControlColorCurve("curve"));
		//
//							p->m_attrsListWnd.m_pControlsHandler = new CFEComponentTransferControlsHandler;
//							p->m_attrsListWnd.m_pControlsHandler->m_controlWindow = &p->m_attrsListWnd;
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
#if 0
		if (pControl->GetName() == "type")
		{
			m_controlWindow->GetControl("slope")->SetVisible(!wcscmp(pControl->m_pData->GetValueAsString(), L"linear"));
			m_controlWindow->GetControl("intercept")->SetVisible(!wcscmp(pControl->m_pData->GetValueAsString(), L"linear"));

			m_controlWindow->GetControl("amplitude")->SetVisible(!wcscmp(pControl->m_pData->GetValueAsString(), L"gamma"));
			m_controlWindow->GetControl("exponent")->SetVisible(!wcscmp(pControl->m_pData->GetValueAsString(), L"gamma"));
			m_controlWindow->GetControl("offset")->SetVisible(!wcscmp(pControl->m_pData->GetValueAsString(), L"gamma"));
		}

		m_controlWindow->Redraw();	// TODO, don't always do this
#endif
	}
};

class CSVGFEImageHandler : public CXMLControlsHandler
{
public:
	CSVGFEImageHandler()
	{
	}

	virtual void Setup()
	{
	// Add data
		m_controlWindow->AddData(new CXMLStringData(L"@preserveAspectRatio", L"TODO"));
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
	}
};

class CSVGFEMorphologyHandler : public CXMLControlsHandler
{
public:
	CSVGFEMorphologyHandler()
	{
	}

	virtual void Setup()
	{
	// Add data
		m_controlWindow->AddData(new CXMLStringData(L"@operator", L"erode"));
		m_controlWindow->AddData(new CXMLStringData(L"@radius", L"0"));

	// Add controls
		m_controlWindow->AddControl(new CXMLControlPopup("operator", L"erode|dilate"));
		m_controlWindow->GetControl("operator")->ConnectData(m_controlWindow->GetData(L"@operator"));

		m_controlWindow->AddControl(new CXMLControlString("radius"));
		m_controlWindow->GetControl("radius")->ConnectData(m_controlWindow->GetData(L"@radius"));
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
	}
};

class CSVGFETurbulenceHandler : public CXMLControlsHandler
{
public:
	CSVGFETurbulenceHandler()
	{
	}

	virtual void Setup()
	{
	// Add data
		m_controlWindow->AddData(new CXMLStringData(L"@baseFrequency", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@numOctaves", L"1"));
		m_controlWindow->AddData(new CXMLStringData(L"@seed", L"0"));
		m_controlWindow->AddData(new CXMLStringData(L"@stitchTiles", L"noStitch"));
		m_controlWindow->AddData(new CXMLStringData(L"@type", L"turbulence"));

	// Add controls
		m_controlWindow->AddControl(new CXMLControlString("baseFrequency"));
		m_controlWindow->GetControl("baseFrequency")->ConnectData(m_controlWindow->GetData(L"@baseFrequency"));

		m_controlWindow->AddControl(new CXMLControlNumber("numOctaves"));
		m_controlWindow->GetControl("numOctaves")->ConnectData(m_controlWindow->GetData(L"@numOctaves"));

		m_controlWindow->AddControl(new CXMLControlNumber("seed"));
		m_controlWindow->GetControl("seed")->ConnectData(m_controlWindow->GetData(L"@seed"));

		m_controlWindow->AddControl(new CXMLControlPopup("stitchTiles", L"stitch|noStitch"));
		m_controlWindow->GetControl("stitchTiles")->ConnectData(m_controlWindow->GetData(L"@stitchTiles"));

		m_controlWindow->AddControl(new CXMLControlPopup("type", L"fractalNoise|turbulence"));
		m_controlWindow->GetControl("type")->ConnectData(m_controlWindow->GetData(L"@type"));
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
	}
};

class CSVGColorProfileHandler : public CXMLControlsHandler
{
public:
	CSVGColorProfileHandler()
	{
	}

	virtual void Setup()
	{
	// Data
		m_controlWindow->AddData(new CXMLStringData(L"@xlink:href", L""));
		m_controlWindow->AddData(new CXMLStringData(L"@local", L""));
		m_controlWindow->AddData(new CXMLStringData(L"@name", L""));
		m_controlWindow->AddData(new CXMLStringData(L"@rendering-intent", L"auto"));

	// Controls
		m_controlWindow->AddControl(new CXMLControlString("xlink:href"));
		m_controlWindow->GetControl("xlink:href")->ConnectData(m_controlWindow->GetData(L"@xlink:href"));

		CComBSTR profiles = L"";

		ENUMTYPE enumtype = {0};
		enumtype.dwSize = sizeof(enumtype);
		enumtype.dwVersion = ENUM_TYPE_VERSION;
		//enumtype.dwDeviceClass = CLASS_MONITOR;

		DWORD size = 0;
		DWORD nprofiles = 0;
		EnumColorProfiles(NULL, &enumtype, NULL, &size, &nprofiles);
		{
			PBYTE buffer = (PBYTE)GlobalAlloc(0, size);
			if (buffer)
			{
				if (EnumColorProfiles(NULL, &enumtype, buffer, &size, &nprofiles))
				{
					BYTE* p = buffer;
					for (int i = 0; i < nprofiles; i++)
					{
						if (i > 0) profiles += L"|";
						profiles += (BSTR)_bstr_t((char*)p);

						p += strlen((char*)p);
						p++;
					}
				}

				GlobalFree(buffer);
			}
		}

		m_controlWindow->AddControl(new CXMLControlPopup("local", profiles));
		m_controlWindow->GetControl("local")->ConnectData(m_controlWindow->GetData(L"@local"));

		m_controlWindow->AddControl(new CXMLControlString("name"));
		m_controlWindow->GetControl("name")->ConnectData(m_controlWindow->GetData(L"@name"));

		m_controlWindow->AddControl(new CXMLControlPopup("rendering-intent", L"auto|perceptual|relative-colorimetric|saturation|absolute-colorimetric"));
		m_controlWindow->GetControl("rendering-intent")->ConnectData(m_controlWindow->GetData(L"@rendering-intent"));
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
	}
};

class CSVGScriptHandler : public CXMLControlsHandler
{
public:
	CSVGScriptHandler()
	{
	}

	virtual void Setup()
	{
	// Data
		m_controlWindow->AddData(new CXMLStringData(L"@xlink:href", L""));
		//m_controlWindow->AddData(new CXMLStringData(L"@local", L""));
		//m_controlWindow->AddData(new CXMLStringData(L"@name", L""));
		//m_controlWindow->AddData(new CXMLStringData(L"@rendering-intent", L"auto"));

	// Controls
		m_controlWindow->AddControl(new CXMLControlString("xlink:href"));
		m_controlWindow->GetControl("xlink:href")->ConnectData(m_controlWindow->GetData(L"@xlink:href"));

		/*
		m_controlWindow->AddControl(new CXMLControlPopup("local", profiles));
		m_controlWindow->GetControl("local")->ConnectData(m_controlWindow->GetData(L"@local"));

		m_controlWindow->AddControl(new CXMLControlString("name"));
		m_controlWindow->GetControl("name")->ConnectData(m_controlWindow->GetData(L"@name"));

		m_controlWindow->AddControl(new CXMLControlPopup("rendering-intent", L"auto|perceptual|relative-colorimetric|saturation|absolute-colorimetric"));
		m_controlWindow->GetControl("rendering-intent")->ConnectData(m_controlWindow->GetData(L"@rendering-intent"));
		*/
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
	}
};

/////////////////////////////////////////////////////////////////////////////
// CInspectorDlg

LRESULT CInspectorDlg::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	/*
	{
		CComPtr<ILDOMElement> element;
		m_behaviorSite->GetElement(&element);

		CComPtr<IUnknown> unk;
		element->getUserData(L"n", &unk);
		CComQIPtr<IEXMLViewGroup> viewGroup(unk);

		m_viewGroup = (viewGroup.p);
	}
*/
	ASSERT(m_viewGroup);

//	CComQIPtr<IUIActiveManager> uiActiveManager = m_app;
//	uiActiveManager->AddEventHandler(this);

	IDispEventImpl<1, CInspectorDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(m_viewGroup);

	OnViewGroupSelectionChanged();

	return 0;
}

LRESULT CInspectorDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//	CComQIPtr<IUIActiveManager> uiActiveManager = m_app;
//	uiActiveManager->RemoveEventHandler(this);

	if (m_controlWindow)
	{
		m_controlWindow->DestroyWindow();
		m_controlWindow.Release();
	}

	OnViewGroupSelectionChanging();

	IDispEventImpl<1, CInspectorDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_viewGroup);

	return 0;
}

LRESULT CInspectorDlg::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect client;
	GetClientRect(&client);

	if (m_controlWindow)
	{
		HWND hwnd;
		m_controlWindow->get_hwnd(&hwnd);
		::MoveWindow(hwnd, 0, 0, client.right, client.bottom, TRUE);
	}

	return 0;
}

//#include "XMLAttribute.h"

void __stdcall CInspectorDlg::OnViewGroupSelectionChanging()
{
	long ncount;
	m_viewGroup->GetSelectedCount(&ncount);

	for (int i = 0; i < ncount; i++)
	{
		CComPtr<IESelectedElement> selectedElement;
		m_viewGroup->GetSelectedElementN(i, &selectedElement);

		CComPtr<IEElement> eElement;
		selectedElement->get_eElement(&eElement);

		CComPtr<ILDOMElement> domElement;
		eElement->get_domElement(&domElement);

		// Remove event listeners on element
		{
			CComQIPtr<ILDOMEventTarget> eventTarget = domElement;

		// Non-Capture
			eventTarget->removeEventListener(L"DOMNodeInserted", (ILDOMEventListener*)this, VARIANT_FALSE);
			eventTarget->removeEventListener(L"DOMNodeRemoved", (ILDOMEventListener*)this, VARIANT_FALSE);
			eventTarget->removeEventListener(L"DOMNodeRemovedFromDocument", (ILDOMEventListener*)this, VARIANT_FALSE);
			eventTarget->removeEventListener(L"DOMAttrModified", (ILDOMEventListener*)this, VARIANT_FALSE);
			eventTarget->removeEventListener(L"DOMCharacterDataModified", (ILDOMEventListener*)this, VARIANT_FALSE);
			eventTarget->removeEventListener(L"DOMElementNameChanged", (ILDOMEventListener*)this, VARIANT_FALSE);

		// Capture
			eventTarget->removeEventListener(L"DOMNodeInserted", (ILDOMEventListener*)this, VARIANT_TRUE);
			eventTarget->removeEventListener(L"DOMNodeRemoved", (ILDOMEventListener*)this, VARIANT_TRUE);
			eventTarget->removeEventListener(L"DOMNodeRemovedFromDocument", (ILDOMEventListener*)this, VARIANT_TRUE);
			eventTarget->removeEventListener(L"DOMAttrModified", (ILDOMEventListener*)this, VARIANT_TRUE);
			eventTarget->removeEventListener(L"DOMCharacterDataModified", (ILDOMEventListener*)this, VARIANT_TRUE);
			eventTarget->removeEventListener(L"DOMElementNameChanged", (ILDOMEventListener*)this, VARIANT_TRUE);
		}
	}
}

void __stdcall CInspectorDlg::OnViewGroupSelectionChanged()
{
	ASSERT(m_viewGroup);

	if (m_controlWindow)
	{
		m_controlWindow->DestroyWindow();
		m_controlWindow.Release();
	}

	{
		long ncount;
		m_viewGroup->GetSelectedCount(&ncount);

		CComBSTR tagName;
		CComBSTR namespaceURI;

		for (int i = 0; i < ncount; i++)
		{
			CComPtr<IESelectedElement> selectedElement;
			m_viewGroup->GetSelectedElementN(i, &selectedElement);

			CComPtr<IEElement> eElement;
			selectedElement->get_eElement(&eElement);

			CComPtr<ILDOMElement> domElement;
			eElement->get_domElement(&domElement);

			// Add event listeners on element
			{
				CComQIPtr<ILDOMEventTarget> eventTarget = domElement;

			// Non-Capture
				eventTarget->addEventListener(L"DOMNodeInserted", (ILDOMEventListener*)this, VARIANT_FALSE);
				eventTarget->addEventListener(L"DOMNodeRemoved", (ILDOMEventListener*)this, VARIANT_FALSE);
				eventTarget->addEventListener(L"DOMNodeRemovedFromDocument", (ILDOMEventListener*)this, VARIANT_FALSE);
				eventTarget->addEventListener(L"DOMAttrModified", (ILDOMEventListener*)this, VARIANT_FALSE);
				eventTarget->addEventListener(L"DOMCharacterDataModified", (ILDOMEventListener*)this, VARIANT_FALSE);
				eventTarget->addEventListener(L"DOMElementNameChanged", (ILDOMEventListener*)this, VARIANT_FALSE);

			// Capture
				eventTarget->addEventListener(L"DOMNodeInserted", (ILDOMEventListener*)this, VARIANT_TRUE);
				eventTarget->addEventListener(L"DOMNodeRemoved", (ILDOMEventListener*)this, VARIANT_TRUE);
				eventTarget->addEventListener(L"DOMNodeRemovedFromDocument", (ILDOMEventListener*)this, VARIANT_TRUE);
				eventTarget->addEventListener(L"DOMAttrModified", (ILDOMEventListener*)this, VARIANT_TRUE);
				eventTarget->addEventListener(L"DOMCharacterDataModified", (ILDOMEventListener*)this, VARIANT_TRUE);
				eventTarget->addEventListener(L"DOMElementNameChanged", (ILDOMEventListener*)this, VARIANT_TRUE);
			}

			CComBSTR tagName2;
			domElement->get_localName(&tagName2);
			if (tagName2.Length() == 0)
			{
				tagName2.Empty();
				domElement->get_tagName(&tagName2);
			}

			CComBSTR namespaceURI2;
			domElement->get_namespaceURI(&namespaceURI2);

			if (i == 0)
			{
				tagName = tagName2;
				namespaceURI = namespaceURI2;
			}
			else if (
				!((namespaceURI.Length() == 0 && namespaceURI2.Length() == 0) || !wcscmp(namespaceURI, namespaceURI2))
				||
				wcscmp(tagName, tagName2))
			{
				tagName.Empty();
				namespaceURI.Empty();
				break;
			}
		}

		if (tagName.Length())
		{
			BOOL bAnimation;

			if (m_controlWindow == NULL)
			{
				if (
					!wcscmp(tagName, L"set") ||
					!wcscmp(tagName, L"animate") ||
					!wcscmp(tagName, L"animateColor") ||
					!wcscmp(tagName, L"animateTransform"))
					//!wcscmp(tagName, L"animateMotion") || ??
				{
					m_targetElement = NULL;

					long ncount;
					m_viewGroup->GetSelectedCount(&ncount);

					for (int i = 0; i < ncount; i++)
					{
						CComPtr<IESelectedElement> selectedElement;
						m_viewGroup->GetSelectedElementN(i, &selectedElement);

						CComPtr<IEElement> eElement;
						selectedElement->get_eElement(&eElement);

						CComPtr<ILDOMElement> domElement;
						eElement->get_domElement(&domElement);

						CComQIPtr<ILAnimationElement> animation = domElement;

						CComPtr<ILDOMElement> targetElement2;
						animation->get_targetElement(&targetElement2);

						if (i == 0)
						{
							m_targetElement = targetElement2;
						}
					// When multiple animation elements are selected, they must all target the same element
						else if (m_targetElement != targetElement2)
						{
							m_targetElement = NULL;
							break;
						}
					}

					if (m_targetElement)
					{
						CComBSTR tagName2;
						m_targetElement->get_localName(&tagName2);
						if (tagName2.Length() == 0)
						{
							tagName2.Empty();
							m_targetElement->get_tagName(&tagName2);
						}

						CComBSTR namespaceURI2;
						m_targetElement->get_namespaceURI(&namespaceURI2);

						tagName = tagName2;
						namespaceURI = namespaceURI2;
					}
					else
					{
						tagName.Empty();
						namespaceURI.Empty();
					}

					CComObject<CControlsContainer>* p;
					CComObject<CControlsContainer>::CreateInstance(&p);
					if (p)
					{
						m_controlWindow = p;
					}

					bAnimation = TRUE;
#if 0
					CComObject<CXMLKeyFrameValuesDlg>* p;
					CComObject<CXMLKeyFrameValuesDlg>::CreateInstance(&p);
					if (p)
					{
						m_controlWindow = p;
					}
#endif
				}
				else
				{
					bAnimation = FALSE;

					CComObject<CControlsContainer>* p;
					CComObject<CControlsContainer>::CreateInstance(&p);
					if (p)
					{
						m_controlWindow = p;
					}
				}

				//m_controlWindow->m_viewGroup = m_viewGroup;
				CXMLControlsHandler* handler = NULL;

				if (!wcscmp(namespaceURI, L"http://www.w3.org/1999/xhtml"))
				{
					if (!wcscmp(tagName, L"html"))
					{
						handler = new CHTMLHTMLHandler;
					}
					else if (!wcscmp(tagName, L"frame"))
					{
						handler = new CHTMLFrameHandler;
					}
					else if (!wcscmp(tagName, L"frameset"))
					{
						handler = new CHTMLFrameSetHandler;
					}
					else if (!wcscmp(tagName, L"a"))
					{
						handler = new CHTMLAHandler;
					}
				}
				else if (!wcscmp(namespaceURI, L"http://www.iptc.org/nitf"))
				{
					if (!wcscmp(tagName, L"person"))
					{
						handler = new CNITFPersonHandler;
					}
				}
				else if (!wcscmp(namespaceURI, L"http://www.w3.org/2000/svg"))
				{
					if (!wcscmp(tagName, L"svg"))
					{
						handler = new CSVGSVGHandler;
					}
					else if (!wcscmp(tagName, L"ellipse"))
					{
						handler = new CSVGEllipseHandler;
					}
					else if (!wcscmp(tagName, L"circle"))
					{
						handler = new CSVGCircleHandler;
					}
					else if (!wcscmp(tagName, L"rect"))
					{
						handler = new CSVGRectHandler;
					}
					else if (!wcscmp(tagName, L"line"))
					{
						handler = new CSVGLineHandler;
					}
					else if (!wcscmp(tagName, L"image"))
					{
						handler = new CSVGImageHandler;
					}
					else if (!wcscmp(tagName, L"video"))
					{
						handler = new CSVGVideoHandler;
					}
					else if (!wcscmp(tagName, L"foreignObject"))
					{
						handler = new CSVGForeignObjectHandler;
					}
					else if (!wcscmp(tagName, L"use"))
					{
						handler = new CSVGUseHandler;
					}
					else if (!wcscmp(tagName, L"symbol"))
					{
						handler = new CSVGSymbolHandler;
					}
				// Text
					else if (!wcscmp(tagName, L"text"))
					{
						handler = new CSVGTextHandler;
					}
					else if (!wcscmp(tagName, L"tspan"))
					{
						handler = new CSVGTSpanHandler;
					}
					else if (!wcscmp(tagName, L"tref"))
					{
						handler = new CSVGTRefHandler;
					}
					else if (!wcscmp(tagName, L"textPath"))
					{
						handler = new CSVGTextPathHandler;
					}
				// Fonts
					else if (!wcscmp(tagName, L"font"))
					{
						handler = new CSVGFontHandler;
					}
					else if (!wcscmp(tagName, L"font-face"))
					{
						handler = new CSVGFontFaceHandler;
					}
				// Pattern/Gradients
					else if (!wcscmp(tagName, L"pattern"))
					{
						handler = new CSVGPatternHandler;
					}
					else if (!wcscmp(tagName, L"linearGradient"))
					{
						handler = new CSVGLinearGradientHandler;
					}
					else if (!wcscmp(tagName, L"radialGradient"))
					{
						handler = new CSVGRadialGradientHandler;
					}
					else if (!wcscmp(tagName, L"stop"))
					{
						handler = new CSVGStopHandler;
					}
				//
					else if (!wcscmp(tagName, L"style"))
					{
						handler = new CSVGStyleHandler;
					}
				//
					else if (!wcscmp(tagName, L"mask"))
					{
						handler = new CSVGMaskHandler;
					}
				// Filters
					else if (!wcscmp(tagName, L"filter"))
					{
						handler = new CSVGFilterHandler;
					}
				// Filter primitives
					else if (!wcscmp(tagName, L"feGaussianBlur"))
					{
						handler = new CSVGFEGaussianBlurHandler;
					}
					else if (!wcscmp(tagName, L"feBlend"))
					{
						handler = new CSVGFEBlendHandler;
					}
					else if (!wcscmp(tagName, L"feColorMatrix"))
					{
						handler = new CSVGFEColorMatrixHandler;
					}
					else if (!wcscmp(tagName, L"feComponentTransfer"))
					{
						handler = new CSVGFEComponentTransferHandler;
					}
					else if (!wcscmp(tagName, L"feComposite"))
					{
						handler = new CSVGFECompositeHandler;
					}
					else if (!wcscmp(tagName, L"feDiffuseLighting"))
					{
						handler = new CSVGFEDiffuseLightingHandler;
					}
					else if (!wcscmp(tagName, L"feImage"))
					{
						handler = new CSVGFEImageHandler;
					}
					else if (!wcscmp(tagName, L"feMorphology"))
					{
						handler = new CSVGFEMorphologyHandler;
					}
					else if (!wcscmp(tagName, L"feOffset"))
					{
						handler = new CSVGFEOffsetHandler;
					}
					else if (!wcscmp(tagName, L"feSpecularLighting"))
					{
						handler = new CSVGFESpecularLightingHandler;
					}
					else if (!wcscmp(tagName, L"feTurbulence"))
					{
						handler = new CSVGFETurbulenceHandler;
					}
				// Filter Lights
					else if (!wcscmp(tagName, L"feDistantLight"))
					{
						handler = new CSVGFEDistantLightHandler;
					}
					else if (!wcscmp(tagName, L"fePointLight"))
					{
						handler = new CSVGFEPointLightHandler;
					}
					else if (!wcscmp(tagName, L"feSpotLight"))
					{
						handler = new CSVGFESpotLightHandler;
					}
				//
					else if (!wcscmp(tagName, L"color-profile"))
					{
						handler = new CSVGColorProfileHandler;
					}
					else if (!wcscmp(tagName, L"script"))
					{
						handler = new CSVGScriptHandler;
					}
				}
				else if (!wcscmp(namespaceURI, L"http://www.w3.org/2001/SMIL20/Language") ||
							!wcscmp(namespaceURI, L"http://www.w3.org/2000/SMIL20/CR/Language"))
				{
					if (!wcscmp(tagName, L"root-layout"))
					{
						handler = new CSMILRootLayoutHandler;
					}
					else if (!wcscmp(tagName, L"region"))
					{
						handler = new CSMILRegionHandler;
					}
					else if (!wcscmp(tagName, L"media") ||
						!wcscmp(tagName, L"video") ||
						!wcscmp(tagName, L"img") ||
						!wcscmp(tagName, L"ref") ||
						!wcscmp(tagName, L"audio"))
					{
						handler = new CSMILMediaHandler;
					}
					else if (!wcscmp(tagName, L"transition"))
					{
						handler = new CSMILTransitionHandler;
					}
				}

				if (handler)
				{
					handler->m_bAnimation = bAnimation;
					handler->m_viewGroup = m_viewGroup;

					handler->m_controlWindow = m_controlWindow;
					m_controlWindow->m_pControlsHandler = handler;

					m_controlWindow->m_pControlsHandler->Setup();

					if (bAnimation)
					{
						for (int i = 0; i < m_controlWindow->GetControlsCount(); i++)
						{
							CControl* pCtrl = m_controlWindow->GetControlByIndex(i);

						}
					}

					for (int nattr = 0; nattr < m_controlWindow->m_attributes.GetSize(); nattr++)
					{
						CXMLData* pData = m_controlWindow->m_attributes[nattr];

						handler->UpdateData(pData);
					}
				}
			}

			if (m_controlWindow)
			{
			//	BOOL success;
				m_controlWindow->Create(m_hWnd);
				m_controlWindow->ShowWindow(SW_SHOW);

				CRect client;
				GetClientRect(&client);

				HWND hwnd;
				m_controlWindow->get_hwnd(&hwnd);
				::MoveWindow(hwnd, 0, 0, client.right, client.bottom, TRUE);
			}
		}
		else
		{
		}
	}
}

// ILDOMEventListener
STDMETHODIMP CInspectorDlg::handleEvent(ILDOMEvent* evt)
{
	CComBSTR type;
	evt->get_type(&type);

	if (!wcscmp(type, L"DOMAttrModified"))
	{
		CComQIPtr<ILDOMMutationEvent> mut = evt;

		LDOMAttrChangeType attrChangeType;
		mut->get_attrChange(&attrChangeType);

		CComPtr<ILDOMEventTarget> target;
		mut->get_target(&target);
		CComQIPtr<ILDOMNode> node = target;

		CComPtr<ILDOMNode> attrNode;
		mut->get_relatedNode(&attrNode);
		CComQIPtr<ILDOMAttr> attr = attrNode;

		CComBSTR name;
		attr->get_name(&name);

		if (m_controlWindow)
		{
			for (int nattr = 0; nattr < m_controlWindow->m_attributes.GetSize(); nattr++)
			{
				CXMLData* pData = m_controlWindow->m_attributes[nattr];

				_bstr_t path = L"@" + _bstr_t(name);

				if (!wcscmp(pData->m_name, path))
				{
#if 0	// TODO Had this
					m_controlWindow->UpdateData(pData);
#endif
				}
			}
		}
	}

	return S_OK;
}

#if 0
// IUIEventHandler
STDMETHODIMP CInspectorDlg::handleActivateObjectEvent(IUnknown* object, long* cookie)
{
	CComQIPtr<IEXMLViewGroup> viewGroup = object;

	if (viewGroup)
	{
		ASSERT(m_viewGroup == NULL);
		m_viewGroup = viewGroup;
		IDispEventImpl<1, CInspectorDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(m_viewGroup);

		OnViewGroupSelectionChanged();

		*cookie = 1;
	}

	return S_OK;
}

STDMETHODIMP CInspectorDlg::handleDeactivateObjectEvent(IUnknown* object, long cookie, BOOL* bAllow)
{
	ASSERT(m_viewGroup != NULL);

	if 
	{
		m_controlWindow->DestroyWindow();
		m_controlWindow.Release();
	}

	OnViewGroupSelectionChanging();

	IDispEventImpl<1, CInspectorDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_viewGroup);
	m_viewGroup.Release();

	return S_OK;
}
#endif

#endif