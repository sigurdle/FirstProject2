//----------------------------------------------------------------------------------
// File:   Rain.cpp
// Author: Sarah Tariq
// Email:  sdkfeedback@nvidia.com
// 
// Copyright (c) 2007 NVIDIA Corporation. All rights reserved.
//
// TO  THE MAXIMUM  EXTENT PERMITTED  BY APPLICABLE  LAW, THIS SOFTWARE  IS PROVIDED
// *AS IS*  AND NVIDIA AND  ITS SUPPLIERS DISCLAIM  ALL WARRANTIES,  EITHER  EXPRESS
// OR IMPLIED, INCLUDING, BUT NOT LIMITED  TO, IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL  NVIDIA OR ITS SUPPLIERS
// BE  LIABLE  FOR  ANY  SPECIAL,  INCIDENTAL,  INDIRECT,  OR  CONSEQUENTIAL DAMAGES
// WHATSOEVER (INCLUDING, WITHOUT LIMITATION,  DAMAGES FOR LOSS OF BUSINESS PROFITS,
// BUSINESS INTERRUPTION, LOSS OF BUSINESS INFORMATION, OR ANY OTHER PECUNIARY LOSS)
// ARISING OUT OF THE  USE OF OR INABILITY  TO USE THIS SOFTWARE, EVEN IF NVIDIA HAS
// BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
//
//
//----------------------------------------------------------------------------------

#define _USE_MATH_DEFINES

#include "DXUT.h"
#include "DXUTmisc.h"
#include "DXUTcamera.h"
#include "DXUTgui.h"
#include "DXUTsettingsDlg.h"
#include "SDKmisc.h"
#include "sdkmesh_old.h"
#include "SDKmesh.h"
//#include "resource.h"
#include "NVUTMedia.h"
#pragma warning(disable:4995) // avoid warning for "...was marked as #pragma deprecated"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>


using namespace std;

#define DEG2RAD( a ) ( a * D3DX_PI / 180.f )


//--------------------------------------------------------------------------------------
// Global Variables
//--------------------------------------------------------------------------------------
CModelViewerCamera          g_Camera;               
CDXUTDialogResourceManager  g_DialogResourceManager;// manager for shared resources of dialogs
CD3DSettingsDlg             g_D3DSettingsDlg;       // Device settings dialog
CDXUTDialog                 g_HUD;                  // manages the 3D UI
CDXUTDialog                 g_SampleUI;             // dialog for sample specific controls

ID3DX10Font*                g_pFont = NULL;         // Font for drawing text
ID3DX10Sprite*              g_pSprite = NULL;       // Sprite for batching text drawing
ID3D10Effect*               g_pEffect = NULL;       // D3DX effect interface
CDXUTTextHelper*            g_pTxtHelper = NULL;
CDXUTDirectionWidget*       g_lightDirectionWidget;
bool                        g_bShowHelp = false;    // show help menu
D3D10_VIEWPORT              g_SceneVP;

//techniques
ID3D10EffectTechnique*  g_pTechniqueAdvanceRain            = NULL;
ID3D10EffectTechnique*  g_pTechniqueDrawRain               = NULL;
ID3D10EffectTechnique*  g_pTechniqueDrawRainCheap          = NULL;
ID3D10EffectTechnique*  g_pTechniqueRenderScene            = NULL;
ID3D10EffectTechnique*  g_pTechniqueRenderSky              = NULL;
ID3D10EffectTechnique*  g_pTechniqueRenderArrow            = NULL;


//vertex buffers and layout
ID3D10InputLayout*      g_pVertexLayoutRainVertex          = NULL; 
ID3D10InputLayout*      g_pVertexLayoutArrow               = NULL; // Vertex Layout for arrow
ID3D10InputLayout*      g_pVertexLayoutScene               = NULL;
ID3D10InputLayout*      g_pVertexLayoutSky                 = NULL;
ID3D10Buffer*           g_pParticleStart                   = NULL;
ID3D10Buffer*           g_pParticleStreamTo                = NULL;
ID3D10Buffer*           g_pParticleDrawFrom                = NULL;
CDXUTMesh10             g_Mesh;
CDXUTMesh10             g_MeshArrow;
ID3D10Buffer*           g_VertexBufferSky;


//shader variables
ID3D10EffectMatrixVariable* g_pWorldShaderVariable                = NULL;
ID3D10EffectMatrixVariable* g_pWorldViewProjShaderVariable        = NULL;
ID3D10EffectMatrixVariable* g_pInvViewShaderVariable              = NULL;
ID3D10EffectMatrixVariable* g_pWorldViewShaderVariable            = NULL; 
ID3D10EffectMatrixVariable* g_pProjectionShaderVariable           = NULL;
ID3D10EffectMatrixVariable* g_pInverseProjectionShaderVariable    = NULL;
ID3D10EffectVectorVariable* g_pEyePosShaderVariable               = NULL;
ID3D10EffectVectorVariable* g_pLightPosShaderVariable             = NULL;
ID3D10EffectVectorVariable* g_pTotalVelShaderVariable             = NULL;
ID3D10EffectVectorVariable* g_pDiffuseShaderVariable              = NULL;
ID3D10EffectVectorVariable* g_LightPosWithViewTransformationShaderVariable = NULL;
ID3D10EffectVectorVariable* g_LightPosWithViewTransformation2ShaderVariable = NULL;
ID3D10EffectVectorVariable* g_VecPointLightEyeShaderVariable      = NULL;
ID3D10EffectVectorVariable* g_VecPointLightEye2ShaderVariable      = NULL;
ID3D10EffectScalarVariable* g_pRenderBGShaderVariable             = NULL;
ID3D10EffectScalarVariable* g_pMoveParticlesShaderVariable        = NULL;
ID3D10EffectScalarVariable* g_pDirLightIntensityShaderVariable    = NULL;
ID3D10EffectScalarVariable* g_pPointLightIntensityShaderVariable  = NULL;
ID3D10EffectScalarVariable* g_pResponseDirLightShaderVariable     = NULL;
ID3D10EffectScalarVariable* g_pResponsePointLightShaderVariable   = NULL;
ID3D10EffectScalarVariable* g_pSpriteSizeShaderVariable           = NULL;
ID3D10EffectVectorVariable* g_pFogThicknessShaderVariable         = NULL;
ID3D10EffectScalarVariable* g_ScreenWidthShaderVariable           = NULL;
ID3D10EffectScalarVariable* g_ScreenHeightShaderVariable          = NULL;
ID3D10EffectScalarVariable* g_ScreenWidthMultiplierShaderVariable = NULL;
ID3D10EffectScalarVariable* g_ScreenHeightMultiplierShaderVariable= NULL;
ID3D10EffectScalarVariable* g_TSVPointLightShaderVariable         = NULL;
ID3D10EffectScalarVariable* g_DSVPointLightShaderVariable         = NULL;
ID3D10EffectScalarVariable* g_DSVPointLight2ShaderVariable        = NULL;
ID3D10EffectScalarVariable* g_DSVPointLight3ShaderVariable        = NULL;
ID3D10EffectScalarVariable* g_deShaderVariable                    = NULL;
ID3D10EffectScalarVariable* g_UseSpotLightShaderVariable          = NULL;
ID3D10EffectScalarVariable* g_CosSpotLightShaderVariable          = NULL;
ID3D10EffectScalarVariable* g_KdShaderVariable                    = NULL;
ID3D10EffectScalarVariable* g_KsPointShaderVariable               = NULL;
ID3D10EffectScalarVariable* g_KsDirShaderVariable                 = NULL;
ID3D10EffectScalarVariable* g_SpecPowerShaderVariable             = NULL;
ID3D10EffectScalarVariable* g_FPSShaderVariable                   = NULL;
ID3D10EffectScalarVariable* g_timeCycleShaderVariable             = NULL;
ID3D10EffectScalarVariable* g_rainSplashesXDisplaceShaderVariable = NULL;
ID3D10EffectScalarVariable* g_rainSplashesYDisplaceShaderVariable = NULL;

//presets for the variables
const D3DXVECTOR3 g_constFogVector1 = D3DXVECTOR3(0.03f,0.03f,0.03f);
const float       g_constDirLightIntensity1 = 0.18f;
const float       g_constResponseDirLight1 = 1.0f;
const float       g_constPointLightIntensity1 = 0.5f;
const float       g_constCosSpotLight1 = 0.3f;
const float       g_constResponsePointLight1 = 2.0f;
const float       g_constDrawFraction1 = 0.7f;
const float       g_constWindAmount1 = 1.0;
const D3DXVECTOR3 g_constVecEye1 = D3DXVECTOR3( 15.5f, 5.0f, 0.0f );
const D3DXVECTOR3 g_constAtVec1  = D3DXVECTOR3( 0.0f, 3.0f, 0.0f );
const D3DXVECTOR3 g_directionalLightVector1 = D3DXVECTOR3(0.551748, 0.731354, 0.400869);

const D3DXVECTOR3 g_constFogVector2 = D3DXVECTOR3(0.02f,0.02f,0.02f);
const float       g_constDirLightIntensity2 = 0.50f;
const float       g_constResponseDirLight2 = 0.68f;
const float       g_constPointLightIntensity2 = 0.4f;
const float       g_constCosSpotLight2 = 0.54f;
const float       g_constResponsePointLight2 = 2.0f;
const float       g_constDrawFraction2 = 0.6f;
const float       g_constWindAmount2 = 0.48;
const D3DXVECTOR3 g_constVecEye2 = D3DXVECTOR3( -4.0f, 18.0f, -5.0f );
const D3DXVECTOR3 g_constAtVec2  = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
const D3DXVECTOR3 g_directionalLightVector2 = D3DXVECTOR3(0.470105, 0.766044, 0.43838);

//global variables

float g_ScreenWidth = 1264.0f;
float g_ScreenHeight = 958.0f;
float g_SpriteSize = 0.8;
float g_dirLightRadius = 1000;
bool g_bRenderBg = true;
bool g_bMoveParticles = true; 
bool g_bDrawParticles = true;
int g_numRainVertices = 150000;
float g_dirLightIntensity = 0.27f;
float g_PointLightIntensity = 0.58;
float g_znear = 1.0f;
float g_zfar  = 30000.0f;
float g_fov =  0.3*D3DX_PI;
float g_cosSpotLight = 0.54;
bool g_bUseSpotLight = true;
float g_responseDirLight = 0.9f;
float g_responsePointLight = 2.0f;
float g_heightMin = 0.0f;
float g_heightRange = 40.0f;
float g_radiusMin = 0.0f;
float g_radiusRange = 45.0f; 
bool g_bUseCheapShader = false;
bool firstFrame;
int frameCount = 0;
float g_WindAmount;
float g_DrawFraction = 1.0;
D3DXVECTOR3 g_fogVector;
D3DXVECTOR3 g_vecEye;
D3DXVECTOR3 g_vecAt;
D3DXVECTOR3 g_lightPos;
D3DXVECTOR3 g_eyeInObjectSpace;
D3DXVECTOR3 g_TotalVel = D3DXVECTOR3(-0.05,-0.5,0);
D3DXVECTOR3 g_PointLightPos = D3DXVECTOR3(  3.7,5.8,3.15);
D3DXVECTOR3 g_PointLightPos2 = D3DXVECTOR3(-3.7,5.8,3.15);
D3DXMATRIX g_WorldMatrix;


//structures
struct RainVertex
{
    D3DXVECTOR3 pos;
    D3DXVECTOR3 seed;
    D3DXVECTOR3 speed;
    float random;
    unsigned char  Type;
};

struct SimpleVertex
{
    D3DXVECTOR3 Pos;  // Position
    D3DXVECTOR2 Tex; // Texture Coordinate
};

struct WindValue
{
   D3DXVECTOR3 windAmount;
   int time;
   WindValue(D3DXVECTOR3 wA, int t){windAmount = wA; time=t;};
};
vector<WindValue> WindAnimation;
int totalAnimationValues = 0;

//--------------------------------------------------------------------------------------
// UI control IDs
//--------------------------------------------------------------------------------------
#define IDC_TOGGLEFULLSCREEN             1
#define IDC_TOGGLEREF                    2
#define IDC_CHANGEDEVICE                 3
#define IDC_TOGGLEBG                     4
#define IDC_TOGGLEMOVE                   9
#define IDC_LIGHT_STATIC                10
#define IDC_DIRLIGHTINTENSITY_STATIC    11
#define IDC_DIRLIGHTINTENSITY_SCALE     12
#define IDC_RESPONSEDIRLIGHT_STATIC     13
#define IDC_RESPONSEDIRLIGHT_SCALE      14
#define IDC_POINTLIGHTINTENSITY_STATIC  15
#define IDC_POINTLIGHTINTENSITY_SCALE   16 
#define IDC_RESPONSEPOINTLIGHT_STATIC   17 
#define IDC_RESPONSEPOINTLIGHT_SCALE    18
#define IDC_FOGTHICKNESS_STATIC         19 
#define IDC_FOGTHICKNESS_SCALE          20
#define IDC_DRAWFRACTION_STATIC         21
#define IDC_DRAWFRACTION_SCALE          22
#define IDC_TOGGLESPOTLIGHT             23
#define IDC_COSSPOTLIGHT_STATIC         24
#define IDC_COSSPOTLIGHT_SCALE          25
#define IDC_SPRITEHEIGHT_STATIC         26  
#define IDC_SPRITEHEIGHT_SCALE          27  
#define IDC_SPRITEWIDTH_STATIC          28
#define IDC_SPRITEWIDTH_SCALE           29
#define IDC_WINDAMOUNT_STATIC           30
#define IDC_WINDAMOUNT_SCALE            31
#define IDC_TOGGLEDRAW                  32
#define IDC_TOGGLECHEAPSHADER           33
#define IDC_TOGGLEPRESET1               34
#define IDC_TOGGLEPRESET2               35


//--------------------------------------------------------------------------------------
// Forward declarations 
//--------------------------------------------------------------------------------------
bool    CALLBACK IsD3D10DeviceAcceptable( UINT Adapter, UINT Output, D3D10_DRIVER_TYPE DeviceType, DXGI_FORMAT BufferFormat, bool bWindowed, void* pUserContext );
HRESULT CALLBACK OnD3D10CreateDevice( ID3D10Device* pd3dDevice, const DXGI_SURFACE_DESC* pBufferSurfaceDesc, void* pUserContext );
HRESULT CALLBACK OnD3D10ResizedSwapChain( ID3D10Device* pd3dDevice, IDXGISwapChain *pSwapChain, const DXGI_SURFACE_DESC* pBufferSurfaceDesc, void* pUserContext );
void    CALLBACK OnD3D10FrameRender( ID3D10Device* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext );
void    CALLBACK OnD3D10ReleasingSwapChain( void* pUserContext );
void    CALLBACK OnD3D10DestroyDevice( void* pUserContext );
bool    CALLBACK OnDeviceRemoved( void* pUserContext );
void    CALLBACK OnGUIEvent( UINT nEvent, int nControlID, CDXUTControl* pControl, void* pUserContext );
LRESULT CALLBACK MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext );
void    CALLBACK KeyboardProc( UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext );
void    CALLBACK OnFrameMove( double fTime, float fElapsedTime, void* pUserContext );
bool    CALLBACK ModifyDeviceSettings( DXUTDeviceSettings* pDeviceSettings, void* pUserContext );
HRESULT loadTextureFromFile(LPCWSTR file,LPCSTR shaderTextureName, ID3D10Device* pd3dDevice);
HRESULT loadCubemapTextureFromFile(LPCWSTR file,LPCSTR shaderTextureName, ID3D10Device* pd3dDevice);
HRESULT load3DTextureFromFile(LPCWSTR file,LPCSTR shaderTextureName, ID3D10Device* pd3dDevice);
HRESULT LoadTextureArray( ID3D10Device* pd3dDevice, char* sTexturePrefix, int iNumTextures, ID3D10Texture2D** ppTex2D, ID3D10ShaderResourceView** ppSRV);
float random(); 
void resetVariablesToPreset1();
void resetVariablesToPreset2();
HRESULT loadLUTS(char* fileName, LPCSTR shaderTextureName, int xRes, int yRes, ID3D10Device* pd3dDevice);
void UpdateSpriteRotationMatrix();
void vectorMatrixMultiply(D3DXVECTOR3* vecOut,const D3DXMATRIX matrix,const D3DXVECTOR3 vecIn);
void RenderText();
void resetGUIControls();
void setShadingParametersBasedOnRain();


//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow )
{
    // Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

    // Set DXUT callbacks
    DXUTSetCallbackD3D10DeviceAcceptable( IsD3D10DeviceAcceptable );
    DXUTSetCallbackD3D10DeviceCreated( OnD3D10CreateDevice );
    DXUTSetCallbackD3D10SwapChainResized( OnD3D10ResizedSwapChain );
    DXUTSetCallbackD3D10SwapChainReleasing( OnD3D10ReleasingSwapChain );
    DXUTSetCallbackD3D10DeviceDestroyed( OnD3D10DestroyDevice );
    DXUTSetCallbackD3D10FrameRender( OnD3D10FrameRender );
    DXUTSetCallbackMsgProc( MsgProc );
    DXUTSetCallbackKeyboard( KeyboardProc );
    DXUTSetCallbackFrameMove( OnFrameMove );
    DXUTSetCallbackDeviceChanging( ModifyDeviceSettings );
    DXUTSetCallbackDeviceRemoved( OnDeviceRemoved );

    HRESULT hr;
   // V_RETURN(DXUTSetMediaSearchPath(L"..\\Source\\rain"));

    V_RETURN(DXUTSetMediaSearchPath(L"C:\\Program Files (x86)\\NVIDIA Corporation\\NVIDIA Direct3D SDK 10\\Source\\rain"));

    DXUTInit( true, true, NULL ); // Parse the command line, show msgboxes on error, no extra command line params
    DXUTSetCursorSettings( true, true ); // Show the cursor and clip it when in full screen
    DXUTCreateWindow( L"Rain" );
    DXUTCreateDevice( true, (int)g_ScreenWidth, (int)g_ScreenHeight ); 
    DXUTMainLoop(); // Enter into the DXUT render loop

    return DXUTGetExitCode();
}


//--------------------------------------------------------------------------------------
// GUI 
//--------------------------------------------------------------------------------------


void resetGUIControls()
{

    WCHAR sz[100];

    int iY = 10; 
    g_SampleUI.AddButton(IDC_TOGGLEPRESET1,L"Preset 1",35, iY, 125, 22, false, VK_F4);
    g_SampleUI.AddButton(IDC_TOGGLEPRESET2,L"Preset 2",35, iY+=24, 125, 22, false, VK_F5);
    iY+=24;
    g_SampleUI.AddCheckBox( IDC_TOGGLEBG, L"Show Background", 35, iY += 24, 125, 22, g_bRenderBg );
    g_SampleUI.AddCheckBox( IDC_TOGGLEMOVE, L"Move Particles", 35, iY += 24, 125, 22, g_bMoveParticles );
    g_SampleUI.AddCheckBox( IDC_TOGGLEDRAW, L"Draw Particles", 35, iY += 24, 125, 22, g_bDrawParticles );
    g_SampleUI.AddCheckBox( IDC_TOGGLECHEAPSHADER, L"Use constant intensity streaks", 35, iY += 24, 125, 22, g_bUseCheapShader );

    //fog
    iY += 24;
    StringCchPrintf( sz, 100, L"Fog Thickness: %0.2f", g_fogVector.x ); 
    g_SampleUI.AddStatic( IDC_FOGTHICKNESS_STATIC, sz, 35, iY += 24, 125, 22 );
    g_SampleUI.AddSlider( IDC_FOGTHICKNESS_SCALE, 50, iY += 20, 100, 22, 0, 200, (int)(g_fogVector.x*1000) );
    
    //directional light
    iY += 24;
    g_SampleUI.AddStatic( IDC_LIGHT_STATIC, L"Directional Light", 35, iY += 24 , 125, 22 );
   
    StringCchPrintf( sz, 100, L"Intensity: %0.2f", g_dirLightIntensity ); 
    g_SampleUI.AddStatic( IDC_DIRLIGHTINTENSITY_STATIC, sz, 35, iY += 24, 125, 22 );
    g_SampleUI.AddSlider( IDC_DIRLIGHTINTENSITY_SCALE, 50, iY += 20, 100, 22, 0, 100, (int)(g_dirLightIntensity*100) );

    StringCchPrintf( sz, 100, L"Rain response: %0.2f", g_responseDirLight ); 
    g_SampleUI.AddStatic( IDC_RESPONSEDIRLIGHT_STATIC, sz, 35, iY += 24, 125, 22 );
    g_SampleUI.AddSlider( IDC_RESPONSEDIRLIGHT_SCALE, 50, iY += 20, 100, 22, 0, 200, (int)(g_responseDirLight*100) );

    //point light
    iY += 24;
    StringCchPrintf( sz, 100, L"Point Light: %0.2f", g_PointLightIntensity ); 
    g_SampleUI.AddStatic( IDC_POINTLIGHTINTENSITY_STATIC, sz, 35, iY += 24, 125, 22 );
    g_SampleUI.AddSlider( IDC_POINTLIGHTINTENSITY_SCALE, 50, iY += 20, 100, 22, 0, 200, (int)(g_PointLightIntensity*100) );

    iY += 24;
    g_SampleUI.AddCheckBox( IDC_TOGGLESPOTLIGHT, L"Use SpotLight", 35, iY, 125, 22, g_bUseSpotLight );
  
    iY += 5;
    StringCchPrintf( sz, 100, L"Cos SpotLight: %0.2f", g_cosSpotLight ); 
    g_SampleUI.AddStatic( IDC_COSSPOTLIGHT_STATIC, sz, 35, iY += 24, 125, 22 );
    g_SampleUI.AddSlider( IDC_COSSPOTLIGHT_SCALE, 50, iY += 20, 100, 22, 0, 100, (int)(g_cosSpotLight*100) );

    StringCchPrintf( sz, 100, L"Rain response: %0.2f", g_responsePointLight ); 
    g_SampleUI.AddStatic( IDC_RESPONSEPOINTLIGHT_STATIC, sz, 35, iY += 24, 125, 22 );
    g_SampleUI.AddSlider( IDC_RESPONSEPOINTLIGHT_SCALE, 50, iY += 20, 100, 22, 0, 200, (int)(g_responsePointLight*100) );

    iY += 34;
    StringCchPrintf( sz, 100, L"Particles Drawn: %0.2f", g_numRainVertices*g_DrawFraction ); 
    g_SampleUI.AddStatic( IDC_DRAWFRACTION_STATIC, sz, 35, iY += 24, 150, 22 );
    g_SampleUI.AddSlider( IDC_DRAWFRACTION_SCALE, 50, iY += 20, 100, 22, 0, 100, (int)(g_DrawFraction*100) );

    iY += 14;
    StringCchPrintf( sz, 100, L"Wind: %0.2f", g_WindAmount ); 
    g_SampleUI.AddStatic( IDC_WINDAMOUNT_STATIC, sz, 35, iY += 24, 125, 22 );
    g_SampleUI.AddSlider( IDC_WINDAMOUNT_SCALE, 50, iY += 20, 100, 22, 0, 100, (int)(g_WindAmount*100) );

}

//--------------------------------------------------------------------------------------
// Reject any D3D10 devices that aren't acceptable by returning false
//--------------------------------------------------------------------------------------
bool CALLBACK IsD3D10DeviceAcceptable( UINT Adapter, UINT Output, D3D10_DRIVER_TYPE DeviceType, DXGI_FORMAT BufferFormat, bool bWindowed, void* pUserContext )
{
    return true;
}


//--------------------------------------------------------------------------------------
// Create any D3D10 resources that aren't dependant on the back buffer
//--------------------------------------------------------------------------------------
HRESULT CALLBACK OnD3D10CreateDevice( ID3D10Device* pd3dDevice, const DXGI_SURFACE_DESC *pBufferSurfaceDesc, void* pUserContext )
{
    HRESULT hr = S_OK;

    g_D3DSettingsDlg.GetDialogControl()->RemoveAllControls();
    g_D3DSettingsDlg.Init( &g_DialogResourceManager );
    g_HUD.RemoveAllControls();
    g_SampleUI.RemoveAllControls();
    g_HUD.Init( &g_DialogResourceManager );
    g_SampleUI.Init( &g_DialogResourceManager );
    g_HUD.SetCallback( OnGUIEvent ); 

    V_RETURN( g_DialogResourceManager.OnD3D10CreateDevice( pd3dDevice ) );
    V_RETURN( g_D3DSettingsDlg.OnD3D10CreateDevice( pd3dDevice ) );

 
    int iY = 10; 
    g_HUD.AddButton( IDC_TOGGLEFULLSCREEN, L"Toggle full screen", 35, iY, 125, 22 );
    g_HUD.AddButton( IDC_TOGGLEREF, L"Toggle REF (F3)", 35, iY += 24, 125, 22, VK_F3 );
    g_HUD.AddButton( IDC_CHANGEDEVICE, L"Change device (F2)", 35, iY += 24, 125, 22, VK_F2 );

    g_SampleUI.SetCallback( OnGUIEvent ); 


    
    V_RETURN( D3DX10CreateFont( pd3dDevice, 15, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET, 
                                OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, 
                                L"Arial", &g_pFont ) );
    V_RETURN( D3DX10CreateSprite( pd3dDevice, 512, &g_pSprite ) );
    g_pTxtHelper = new CDXUTTextHelper( NULL, NULL, g_pFont, g_pSprite, 15 );

    DWORD dwShaderFlags = D3D10_SHADER_AVOID_FLOW_CONTROL;

    // Read the D3DX effect file
    
    WCHAR str[MAX_PATH];
    ID3D10Blob *pErrors;
    V_RETURN( NVUTFindDXSDKMediaFileCch( str, MAX_PATH, L"rain.fx" ) );
    hr = D3DX10CreateEffectFromFile(str, NULL, NULL, "fx_4_0", dwShaderFlags, 0, pd3dDevice, NULL, NULL, &g_pEffect, &pErrors, &hr);
    if( FAILED( hr ) )
    {
        LPCSTR szErrors = NULL;
        if(pErrors)
        {
            szErrors = (LPCSTR)pErrors->GetBufferPointer();
            OutputDebugStringA(szErrors);
            pErrors->Release();
        }
        return E_FAIL;
    }


    // Obtain the techniques
    g_pTechniqueAdvanceRain   = g_pEffect->GetTechniqueByName("AdvanceParticles");
    g_pTechniqueDrawRain      = g_pEffect->GetTechniqueByName("RenderParticles");
    g_pTechniqueDrawRainCheap = g_pEffect->GetTechniqueByName("RenderParticlesCheap");
    g_pTechniqueRenderScene   = g_pEffect->GetTechniqueByName("RenderScene");
    g_pTechniqueRenderSky     = g_pEffect->GetTechniqueByName("RenderSky");
    g_pTechniqueRenderArrow  = g_pEffect->GetTechniqueByName("RenderArrow");


    // Obtain the variables
    g_pWorldShaderVariable = g_pEffect->GetVariableByName( "g_mWorld" )->AsMatrix();
    g_pWorldViewProjShaderVariable = g_pEffect->GetVariableByName( "g_mWorldViewProj" )->AsMatrix();
    g_pInvViewShaderVariable = g_pEffect->GetVariableByName( "g_mInvView" )->AsMatrix();
    g_pWorldViewShaderVariable = g_pEffect->GetVariableByName( "g_mWorldView" )->AsMatrix();
    g_pProjectionShaderVariable = g_pEffect->GetVariableByName( "g_mProjection" )->AsMatrix();
    g_pInverseProjectionShaderVariable = g_pEffect->GetVariableByName( "g_mInverseProjection" )->AsMatrix();
   
    g_pLightPosShaderVariable = g_pEffect->GetVariableByName( "g_lightPos" )->AsVector();  
    g_pEyePosShaderVariable = g_pEffect->GetVariableByName( "g_eyePos" )->AsVector();
    g_pTotalVelShaderVariable = g_pEffect->GetVariableByName( "g_TotalVel" )->AsVector();    
    g_pDiffuseShaderVariable = g_pEffect->GetVariableByName( "g_DiffuseColor" )->AsVector();

    g_pRenderBGShaderVariable = g_pEffect->GetVariableByName( "renderBg")->AsScalar();
    g_pMoveParticlesShaderVariable = g_pEffect->GetVariableByName( "moveParticles")->AsScalar();
    g_pFogThicknessShaderVariable = g_pEffect->GetVariableByName( "g_beta")->AsVector();
    g_pDirLightIntensityShaderVariable = g_pEffect->GetVariableByName( "dirLightIntensity")->AsScalar();
    g_pPointLightIntensityShaderVariable = g_pEffect->GetVariableByName( "g_PointLightIntensity")->AsScalar();
    g_pResponseDirLightShaderVariable = g_pEffect->GetVariableByName( "g_ResponseDirLight")->AsScalar();
    g_pResponsePointLightShaderVariable = g_pEffect->GetVariableByName( "g_ResponsePointLight")->AsScalar();
    g_pSpriteSizeShaderVariable = g_pEffect->GetVariableByName( "g_SpriteSize")->AsScalar();
    g_ScreenWidthShaderVariable = g_pEffect->GetVariableByName( "g_ScreenWidth")->AsScalar();
    g_ScreenHeightShaderVariable = g_pEffect->GetVariableByName( "g_ScreenHeight")->AsScalar();
    g_ScreenWidthMultiplierShaderVariable = g_pEffect->GetVariableByName( "g_ScreenWidthMultiplier")->AsScalar();
    g_ScreenHeightMultiplierShaderVariable = g_pEffect->GetVariableByName( "g_ScreenHeightMultiplier")->AsScalar();
    g_LightPosWithViewTransformationShaderVariable = g_pEffect->GetVariableByName( "g_ViewSpaceLightVec")->AsVector();
    g_LightPosWithViewTransformation2ShaderVariable = g_pEffect->GetVariableByName( "g_ViewSpaceLightVec2")->AsVector();
    g_VecPointLightEyeShaderVariable = g_pEffect->GetVariableByName( "g_VecPointLightEye")->AsVector();
    g_VecPointLightEye2ShaderVariable = g_pEffect->GetVariableByName( "g_VecPointLightEye2")->AsVector();
    g_TSVPointLightShaderVariable = g_pEffect->GetVariableByName( "g_TSVPointLight")->AsScalar();
    g_DSVPointLightShaderVariable = g_pEffect->GetVariableByName( "g_DSVPointLight")->AsScalar();
    g_DSVPointLight2ShaderVariable = g_pEffect->GetVariableByName( "g_DSVPointLight2")->AsScalar();
    g_DSVPointLight3ShaderVariable = g_pEffect->GetVariableByName( "g_DSVPointLight3")->AsScalar();
    g_deShaderVariable = g_pEffect->GetVariableByName( "g_de")->AsScalar();
    g_UseSpotLightShaderVariable = g_pEffect->GetVariableByName( "g_useSpotLight")->AsScalar();
    g_CosSpotLightShaderVariable = g_pEffect->GetVariableByName( "g_cosSpotlightAngle")->AsScalar();      
    g_KdShaderVariable = g_pEffect->GetVariableByName( "g_Kd")->AsScalar(); 
    g_KsPointShaderVariable = g_pEffect->GetVariableByName( "g_KsPoint")->AsScalar(); 
    g_KsDirShaderVariable = g_pEffect->GetVariableByName( "g_KsDir")->AsScalar(); 
    g_SpecPowerShaderVariable = g_pEffect->GetVariableByName( "g_specPower")->AsScalar();
    g_FPSShaderVariable = g_pEffect->GetVariableByName( "g_FrameRate")->AsScalar();
    g_timeCycleShaderVariable = g_pEffect->GetVariableByName( "g_timeCycle")->AsScalar();
	g_rainSplashesXDisplaceShaderVariable = g_pEffect->GetVariableByName( "g_splashXDisplace")->AsScalar();
	g_rainSplashesYDisplaceShaderVariable = g_pEffect->GetVariableByName( "g_splashYDisplace")->AsScalar();

    g_pEffect->GetVariableByName( "g_heightMin" )->AsScalar()->SetFloat(g_heightMin);
    g_pEffect->GetVariableByName( "g_radiusMin" )->AsScalar()->SetFloat(g_radiusMin);
    g_pEffect->GetVariableByName( "g_heightRange" )->AsScalar()->SetFloat(g_heightRange);
    g_pEffect->GetVariableByName( "g_radiusRange" )->AsScalar()->SetFloat(g_radiusRange);
    g_pEffect->GetVariableByName( "maxHeight" )->AsScalar()->SetFloat(-5);
    g_pEffect->GetVariableByName( "g_Near" )->AsScalar()->SetFloat(g_znear);
    g_pEffect->GetVariableByName( "g_Far" )->AsScalar()->SetFloat(g_zfar);

    V_RETURN( CDXUTDirectionWidget::StaticOnD3D10CreateDevice( pd3dDevice ) );
    resetVariablesToPreset1();
    resetGUIControls();
    g_Camera.SetEnablePositionMovement(true);
    g_Camera.SetScalers(0.01f,0.05f);
    frameCount = 0;

    //populate the wind animation
    WindAnimation.clear();
    int time = 0; //time in seconds between each key
    WindAnimation.push_back( WindValue( D3DXVECTOR3(-0.1,-0.5,0),   time ) );
    WindAnimation.push_back( WindValue( D3DXVECTOR3(-0.4,-0.5,0.04), time += 10 ) ); 
    WindAnimation.push_back( WindValue( D3DXVECTOR3(-0.2,-0.5,-0.4),   time += 5 ) );   
    WindAnimation.push_back( WindValue( D3DXVECTOR3(0.0,-0.5,-0.02), time += 10 ) );
    WindAnimation.push_back( WindValue( D3DXVECTOR3(0.0,-0.5,-0.02), time += 10 ) );
    WindAnimation.push_back( WindValue( D3DXVECTOR3(0.1,-0.5,0.4),  time += 6) );
    WindAnimation.push_back( WindValue( D3DXVECTOR3(-0.1,-0.5,0),   time += 5 ) );
    g_pTotalVelShaderVariable->SetFloatVector((float*)WindAnimation.at(0).windAmount);

    //set the variables
    D3DXMATRIX ViewMatrix;
    D3DXMATRIX InvViewMatrix;
    ViewMatrix = *g_Camera.GetViewMatrix();
    D3DXMatrixInverse( &InvViewMatrix, NULL, &ViewMatrix );


    D3DXVECTOR3 VecLightEye;
    D3DXVec3Subtract(&VecLightEye,&g_PointLightPos,g_Camera.GetEyePt());
    float lengthVecLightEye = D3DXVec3Length(&VecLightEye);
    D3DXVec3Normalize(&VecLightEye,&VecLightEye);

    D3DXVECTOR3 VecLightEye2;
    D3DXVec3Subtract(&VecLightEye2,&g_PointLightPos2,g_Camera.GetEyePt());
    float lengthVecLightEye2 = D3DXVec3Length(&VecLightEye2);
    D3DXVec3Normalize(&VecLightEye2,&VecLightEye2);


    //initialize the matrices
    g_pInvViewShaderVariable->SetMatrix( (float*)&InvViewMatrix );
    g_pProjectionShaderVariable->SetMatrix( (float*)g_Camera.GetProjMatrix());

     //initialize the vectors
    g_pEyePosShaderVariable->SetFloatVector((float*)&g_vecEye);
    D3DXVECTOR3 LightInViewSpace;
    vectorMatrixMultiply(&LightInViewSpace, ViewMatrix,g_PointLightPos);
    D3DXVec3Normalize(&LightInViewSpace,&LightInViewSpace);
    g_LightPosWithViewTransformationShaderVariable->SetFloatVector((float*)&LightInViewSpace);
    vectorMatrixMultiply(&LightInViewSpace, ViewMatrix,g_PointLightPos2);
    D3DXVec3Normalize(&LightInViewSpace,&LightInViewSpace);
    g_LightPosWithViewTransformation2ShaderVariable->SetFloatVector((float*)&LightInViewSpace);
    g_pFogThicknessShaderVariable->SetFloatVector((float*)&g_fogVector);


    //initialize the scalars
    g_pSpriteSizeShaderVariable->SetFloat(g_SpriteSize);
    g_ScreenWidthShaderVariable->SetFloat(g_ScreenWidth);
    g_ScreenHeightShaderVariable->SetFloat(g_ScreenHeight);
    g_ScreenWidthMultiplierShaderVariable->SetFloat( 2.0f/(g_ScreenWidth-1)  );
    g_ScreenHeightMultiplierShaderVariable->SetFloat( 2.0f/(g_ScreenHeight-1)  );
    g_DSVPointLightShaderVariable->SetFloat( lengthVecLightEye );
    g_DSVPointLight2ShaderVariable->SetFloat( lengthVecLightEye2 );
    g_deShaderVariable->SetFloat( (g_ScreenHeight/2.0f)/(tan(g_fov/2.0f)) );
    setShadingParametersBasedOnRain();



    //----------------------------------------------------------------------------------------------
    //vertex buffers 
    //----------------------------------------------------------------------------------------------

    
    //vertices for the rain particles---------------------------------------------------------------
    //generate vertices in a cylinder above the camera


    firstFrame = true;
    RainVertex* vertices = new RainVertex[g_numRainVertices];
    if(vertices==NULL) 
        exit(0);

    for(int i=0;i<g_numRainVertices;i++)
    {
        RainVertex raindrop;
        //use rejection sampling to generate random points inside a circle of radius 1 centered at 0,0
        float SeedX;
        float SeedZ;
        bool pointIsInside = false;
        while(!pointIsInside)
        { 
           SeedX = random() - 0.5f;
           SeedZ = random() - 0.5f;
           if( sqrt( SeedX*SeedX + SeedZ*SeedZ ) <= 0.5f )
               pointIsInside = true;
        }
        //save these random locations for reinitializing rain particles that have fallen out of bounds
        SeedX *= g_radiusRange;
        SeedZ *= g_radiusRange;
        float SeedY = random()*g_heightRange;
        raindrop.seed = D3DXVECTOR3(SeedX,SeedY,SeedZ); 
        
        //add some random speed to the particles, to prevent all the particles from following exactly the same trajectory
        //additionally, random speeds in the vertical direction ensure that temporal aliasing is minimized
        float SpeedX = 40.0f*(random()/20.0f);
        float SpeedZ = 40.0f*(random()/20.0f);
        float SpeedY = 40.0f*(random()/10.0f); 
        raindrop.speed = D3DXVECTOR3(SpeedX,SpeedY,SpeedZ);

        //move the rain particles to a random positions in a cylinder above the camera
        float x = SeedX + g_vecEye.x;
        float z = SeedZ + g_vecEye.z;
        float y = SeedY + g_vecEye.y;
        raindrop.pos = D3DXVECTOR3(x,y,z); 

        //get an integer between 1 and 8 inclusive to decide which of the 8 types of rain textures the particle will use
        raindrop.Type = int(floor(  random()*8 + 1 ));

        //this number is used to randomly increase the brightness of some rain particles
        raindrop.random = 1;
        float randomIncrease = random();
        if( randomIncrease > 0.8)
            raindrop.random += randomIncrease;

        vertices[i] = raindrop;
    }


    //create vertex buffers for the rain, two will be used to pingpong between during animation
    D3D10_BUFFER_DESC bd;
    bd.ByteWidth = sizeof( RainVertex ) * g_numRainVertices;
    bd.Usage = D3D10_USAGE_DEFAULT;
    bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = 0;
    bd.MiscFlags = 0;
    D3D10_SUBRESOURCE_DATA InitData;
    ZeroMemory( &InitData, sizeof(D3D10_SUBRESOURCE_DATA) );
    InitData.pSysMem = vertices;
    InitData.SysMemPitch = sizeof(RainVertex);
    V_RETURN( pd3dDevice->CreateBuffer( &bd, &InitData, &g_pParticleStart    ) );
    bd.BindFlags |= D3D10_BIND_STREAM_OUTPUT;
    V_RETURN( pd3dDevice->CreateBuffer( &bd, NULL,      &g_pParticleDrawFrom ) );
    V_RETURN( pd3dDevice->CreateBuffer( &bd, NULL,      &g_pParticleStreamTo ) );
//    delete[] vertices;

    // Create the vertex input layout for rain
    const D3D10_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D10_INPUT_PER_VERTEX_DATA, 0 },
        { "SEED",     0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12,  D3D10_INPUT_PER_VERTEX_DATA, 0 },
        { "SPEED",    0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24,  D3D10_INPUT_PER_VERTEX_DATA, 0 },
        { "RAND",     0, DXGI_FORMAT_R32_FLOAT,       0, 36, D3D10_INPUT_PER_VERTEX_DATA, 0 },
        { "TYPE",     0, DXGI_FORMAT_R8_UINT,         0, 40, D3D10_INPUT_PER_VERTEX_DATA, 0 },
    };
    UINT numElements = sizeof(layout)/sizeof(layout[0]);
    D3D10_PASS_DESC PassDesc;
    g_pTechniqueDrawRain->GetPassByIndex( 0 )->GetDesc( &PassDesc );
    V_RETURN(pd3dDevice->CreateInputLayout( layout, numElements, PassDesc.pIAInputSignature, PassDesc.IAInputSignatureSize, &g_pVertexLayoutRainVertex ));

    //---------------------------------------------------------------------------------------------
    
    //scene mesh

    // Create the input layout for the scene
    const D3D10_INPUT_ELEMENT_DESC layoutScene[] =
    {
        { "POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
        { "NORMAL",    0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D10_INPUT_PER_VERTEX_DATA, 0 },
        { "TANGENT",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 32, D3D10_INPUT_PER_VERTEX_DATA, 0 },
    };
    UINT numElementsScene = sizeof(layoutScene)/sizeof(layoutScene[0]);
    g_pTechniqueRenderScene->GetPassByIndex( 0 )->GetDesc( &PassDesc );
    V_RETURN( pd3dDevice->CreateInputLayout( layoutScene, numElementsScene, PassDesc.pIAInputSignature, PassDesc.IAInputSignatureSize, &g_pVertexLayoutScene ) );
    // Set the input layout
    pd3dDevice->IASetInputLayout( g_pVertexLayoutScene );
    //load the scene
    V_RETURN(NVUTFindDXSDKMediaFileCch(str, MAX_PATH, L"..\\..\\Media\\Bridge\\Bridge.x"));
    V_RETURN( g_Mesh.Create( pd3dDevice,str, (D3D10_INPUT_ELEMENT_DESC*)layoutScene, numElementsScene ) );
    
    //---------------------------------------------------------------------------------------------
    //mesh and layout for arrow

    // Create the input layout
    const D3D10_INPUT_ELEMENT_DESC layoutArrow[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
        { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D10_INPUT_PER_VERTEX_DATA, 0 },
    };
    numElements = sizeof(layoutArrow)/sizeof(layoutArrow[0]);
    g_pTechniqueRenderArrow->GetPassByIndex( 0 )->GetDesc( &PassDesc );
    V_RETURN( pd3dDevice->CreateInputLayout( layoutArrow, numElements, PassDesc.pIAInputSignature, PassDesc.IAInputSignatureSize, &g_pVertexLayoutArrow ) );
    //load the arrow mesh
    V_RETURN( NVUTFindDXSDKMediaFileCch( str, MAX_PATH, L"arrow.x" ) ); 
    V_RETURN( g_MeshArrow.Create( pd3dDevice, str, (D3D10_INPUT_ELEMENT_DESC*)layoutArrow, numElements ) );

    //-------------------------------------------------------------------------------------------------
    //vertex buffer and layout for sky

    // Create the input layout
    D3D10_INPUT_ELEMENT_DESC    layoutSky[] =
    {
      { "position", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
    };
    numElements = sizeof(layoutSky)/sizeof(layoutSky[0]);
    g_pTechniqueRenderSky->GetPassByIndex( 0 )->GetDesc( &PassDesc );
    V_RETURN( pd3dDevice->CreateInputLayout( layoutSky, numElements, PassDesc.pIAInputSignature, PassDesc.IAInputSignatureSize, &g_pVertexLayoutSky ) );

    //make the vertex buffer for the quad that will be used for the sky
    D3DXVECTOR2 verticesSky[4];
    verticesSky[0] = D3DXVECTOR2( 1.0f,  1.0f);
    verticesSky[1] = D3DXVECTOR2( 1.0f, -1.0f);
    verticesSky[2] = D3DXVECTOR2(-1.0f,  1.0f);
    verticesSky[3] = D3DXVECTOR2(-1.0f, -1.0f);
    D3D10_SUBRESOURCE_DATA InitDataSky;
    InitDataSky.pSysMem  = verticesSky;
    D3D10_BUFFER_DESC      bdSky;
    bdSky.Usage          = D3D10_USAGE_IMMUTABLE;
    bdSky.ByteWidth      = sizeof( D3DXVECTOR2 ) * 4;
    bdSky.BindFlags      = D3D10_BIND_VERTEX_BUFFER;
    bdSky.CPUAccessFlags = 0;
    bdSky.MiscFlags      = 0;    
    V_RETURN(pd3dDevice->CreateBuffer( &bdSky, &InitDataSky, &g_VertexBufferSky ));
   
    //---------------------------------------------------------------------------------------------
    //textures
    //---------------------------------------------------------------------------------------------
    
    //the textures for the bridge
    V_RETURN(loadTextureFromFile(L"../../Media/Bridge/bridge_color.dds","SceneTextureDiffuse",pd3dDevice)); 
    V_RETURN(loadTextureFromFile(L"../../Media/Bridge/bridge_spec.dds","SceneTextureSpecular",pd3dDevice)); 
    V_RETURN(loadTextureFromFile(L"../../Media/Bridge/bridge_normal.dds","SceneTextureNormal",pd3dDevice)); 

    //the 3D textures for the rain splashes
    V_RETURN(load3DTextureFromFile(L"../../Media/rainTextures/splashes/SBumpVolume.dds","SplashBumpTexture", pd3dDevice));
    V_RETURN(load3DTextureFromFile(L"../../Media/rainTextures/splashes/SDiffuseVolume.dds","SplashDiffuseTexture", pd3dDevice));

    //load the array of rain textures of point lights, see http://www1.cs.columbia.edu/CAVE/databases/rain_streak_db/rain_streak.php
    ID3D10Texture2D* rainTexture = NULL;
    ID3D10ShaderResourceView* textureRV = NULL;
    ID3D10EffectShaderResourceVariable*   textureArray = g_pEffect->GetVariableByName( "rainTextureArray" )->AsShaderResource();
    V_RETURN( LoadTextureArray( pd3dDevice, "../../Media/rainTextures/cv0_vPositive_", 370 , &rainTexture, &textureRV) );
    textureArray->SetResource( textureRV );
    SAFE_RELEASE(rainTexture);
    SAFE_RELEASE(textureRV);    
   
    //load the look up tables for the fog, see http://www1.cs.columbia.edu/~bosun/sig05.htm
    if(loadLUTS("../../Media/F_512_data.csv","Ftable",512,512, pd3dDevice) == S_FALSE)
        loadLUTS("../Media/F_512_data.csv","Ftable",512,512, pd3dDevice);             
    if(loadLUTS("../../Media/G0_pi_2_64_data.csv","Gtable",64,64, pd3dDevice) == S_FALSE)
        loadLUTS("../Media/G0_pi_2_64_data.csv","Gtable",64,64, pd3dDevice); 
    if(loadLUTS("../../Media/G20_pi_2_64_data.csv","G_20table",64,64, pd3dDevice) == S_FALSE)
        loadLUTS("../Media/G20_pi_2_64_data.csv","G_20table",64,64, pd3dDevice); 

    return S_OK;
}


//--------------------------------------------------------------------------------------
// Create any D3D10 resources that depend on the back buffer
//--------------------------------------------------------------------------------------
HRESULT CALLBACK OnD3D10ResizedSwapChain( ID3D10Device* pd3dDevice, IDXGISwapChain *pSwapChain, const DXGI_SURFACE_DESC* pBufferSurfaceDesc, void* pUserContext )
{
    HRESULT hr;

    ID3D10RenderTargetView* pNULLRT = {NULL};
    pd3dDevice->OMSetRenderTargets( 1, &(pNULLRT), NULL );

    //Set viewport
    ZeroMemory( &g_SceneVP, sizeof( D3D10_VIEWPORT ) );
    g_SceneVP.Height = pBufferSurfaceDesc->Height;
    g_SceneVP.Width = pBufferSurfaceDesc->Width;
    g_SceneVP.MaxDepth = 1.0f;

    V_RETURN( g_DialogResourceManager.OnD3D10ResizedSwapChain( pd3dDevice, pBufferSurfaceDesc ) );
    V_RETURN( g_D3DSettingsDlg.OnD3D10ResizedSwapChain( pd3dDevice, pBufferSurfaceDesc ) );

    // Setup the camera's projection parameters
    g_ScreenWidth = (float)pBufferSurfaceDesc->Width;
    g_ScreenHeight = (float)pBufferSurfaceDesc->Height;
    float fAspectRatio = static_cast<float>(pBufferSurfaceDesc->Width) / static_cast<float>(pBufferSurfaceDesc->Height);
    g_Camera.SetProjParams( g_fov , fAspectRatio, g_znear , g_zfar );
    g_Camera.SetWindow( pBufferSurfaceDesc->Width, pBufferSurfaceDesc->Height );
    g_Camera.SetButtonMasks(NULL, MOUSE_WHEEL, MOUSE_RIGHT_BUTTON );
    
    g_HUD.SetLocation( pBufferSurfaceDesc->Width-170, 0 );
    g_HUD.SetSize( 170, 170 );
    g_SampleUI.SetLocation( pBufferSurfaceDesc->Width-170, 100 ); 
    g_SampleUI.SetSize( 170, 300 );     

    g_ScreenWidthShaderVariable->SetFloat(g_ScreenWidth);
    g_ScreenHeightShaderVariable->SetFloat(g_ScreenHeight);
    g_ScreenWidthMultiplierShaderVariable->SetFloat( 2.0f/(g_ScreenWidth-1)  );
    g_ScreenHeightMultiplierShaderVariable->SetFloat( 2.0f/(g_ScreenHeight-1)  );
    g_deShaderVariable->SetFloat( (g_ScreenHeight/2.0f)/(tan(g_fov/2.0f)) );

    return S_OK;
}


void vectorMatrixMultiply(D3DXVECTOR3* vecOut,const D3DXMATRIX matrix,const D3DXVECTOR3 vecIn)
{
    vecOut->x = vecIn.x*matrix(0,0) + vecIn.y*matrix(1,0) + vecIn.z*matrix(2,0) + matrix(3,0);
    vecOut->y  = vecIn.x*matrix(0,1)+ vecIn.y*matrix(1,1) + vecIn.z*matrix(2,1) + matrix(3,1);
    vecOut->z = vecIn.x*matrix(0,2) + vecIn.y*matrix(1,2) + vecIn.z*matrix(2,2) + matrix(3,2);
}
//--------------------------------------------------------------------------------------
// Render the scene using the D3D10 device
//--------------------------------------------------------------------------------------

void CALLBACK OnD3D10FrameRender( ID3D10Device* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext )
{    

    ID3D10RenderTargetView* pOrigRT = DXUTGetD3D10RenderTargetView();
    ID3D10DepthStencilView* pOrigDS = DXUTGetD3D10DepthStencilView(); 

    //clear the render target and depth stencil view
    float ClearColor[4] = {0.0,0.0,0.0,1.0};
    pd3dDevice->ClearRenderTargetView( pOrigRT, ClearColor );
    pd3dDevice->ClearDepthStencilView( pOrigDS, D3D10_CLEAR_DEPTH, 1.0, 0 );

    //set the viewport and render target
    pd3dDevice->RSSetViewports( 1, &g_SceneVP );
    pd3dDevice->OMSetRenderTargets( 1, &pOrigRT, pOrigDS );

    // If the settings dialog is being shown, then
    // render it instead of rendering the app's scene
    if( g_D3DSettingsDlg.IsActive() )
    {
        g_D3DSettingsDlg.OnRender( fElapsedTime );
        return;
    } 

    //------------------------------------------------------------------------------------
    // Set the wind vector
    //piece-wise linear interpolation for the animation curve
    //------------------------------------------------------------------------------------

     //let the frame rate stabilize before using it to determine animation speed
     if(frameCount < 50)
     { 
           D3DXVECTOR3 wind = WindAnimation.at(0).windAmount;
           g_FPSShaderVariable->SetFloat(40.0f);
           g_pTotalVelShaderVariable->SetFloatVector((float*)wind);
         frameCount++;
     }
     else
    
     { 
         static float time = 0;
         if(g_bMoveParticles)
         {
              //estimate a value of wind at the given time frame
              //we use piecewise linear interpolation between an array of key frames of wind values

              int lastTime = WindAnimation.back().time;
              int upperFrame = 1;
              float framesPerSecond = DXUTGetFPS();
              g_FPSShaderVariable->SetFloat(framesPerSecond);

              while( time > WindAnimation.at(upperFrame).time )
                  upperFrame++;
        
              int lowerFrame = upperFrame - 1;
              float amount = float(time - WindAnimation.at(lowerFrame).time)/(WindAnimation.at(upperFrame).time - WindAnimation.at(lowerFrame).time);
              D3DXVECTOR3 interpolatedWind = WindAnimation.at(lowerFrame).windAmount + amount*( WindAnimation.at(upperFrame).windAmount - WindAnimation.at(lowerFrame).windAmount);

              //adjust the wind based on the current frame rate; the values were estimated for 40FPS
              interpolatedWind *= 40.0f/framesPerSecond;
              //lerp between the wind vector and just the vector pointing down depending on the amount of user chosen wind
              interpolatedWind = g_WindAmount*interpolatedWind + (1-g_WindAmount)*(D3DXVECTOR3(0,-0.5,0));

              g_pTotalVelShaderVariable->SetFloatVector((float*)interpolatedWind);
              time += 1.0f/framesPerSecond;
              if(time>lastTime)
                  time = 0;
         }
     }
     

    D3DXMATRIX ViewMatrix;
    D3DXMATRIX WorldViewMatrix;
    D3DXMATRIX WorldViewProjMatrix;
    D3DXMATRIX WorldInverseMatrix;
    D3DXMATRIX InvViewMatrix;
    D3DXMATRIX InvProjectionMatrix;


    //---------------------------------------------------------------------------------------
    // Draw the sky quad
    //------------------------------------------------------------------------------------
   
    if(g_bRenderBg)
    { 
         D3DXMATRIX ViewProjection;
         D3DXMatrixMultiply( &ViewProjection, &ViewMatrix, g_Camera.GetProjMatrix() );
         D3DXMATRIX ViewProjectionInverse;    
         D3DXMatrixInverse( &ViewProjectionInverse, NULL, &ViewProjection );
         g_pEffect->GetVariableByName("g_mViewProjectionInverse")->AsMatrix()->SetMatrix(ViewProjectionInverse);
         g_pTechniqueRenderSky->GetPassByIndex(0)->Apply(0);

         UINT stride[1] = {sizeof(D3DXVECTOR2)};
         UINT offset[1] = { 0 };
         pd3dDevice->IASetInputLayout(g_pVertexLayoutSky);
         pd3dDevice->IASetVertexBuffers(0,1,&g_VertexBufferSky, stride, offset);
         pd3dDevice->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
         pd3dDevice->Draw(4,0);
    }

    //------------------------------------------------------------------------------------
    //render the light directional control, and update the value of the light vector
    //------------------------------------------------------------------------------------

    g_lightPos = g_lightDirectionWidget->GetLightDirection();
    D3DXVec3Normalize(&g_lightPos,&g_lightPos);

    float arrowScale = 0.02f;
    D3DXMATRIX mScale;
    D3DXMatrixScaling( &mScale, arrowScale, arrowScale, arrowScale);

    D3DXMATRIX mLookAtMatrix;
    D3DXVECTOR3 ArrowPos =  g_vecAt - g_lightPos * g_lightDirectionWidget->GetRadius();
    D3DXVECTOR3 LightPos =  g_vecAt - g_lightPos * 1000;
    g_pLightPosShaderVariable->SetFloatVector((float*)&LightPos);
    D3DXVECTOR3 mOrigin = D3DXVECTOR3(0,0,0);
    D3DXVECTOR3 mUp = D3DXVECTOR3(0, 1, 0);
    D3DXMatrixLookAtLH(&mLookAtMatrix, &ArrowPos, &mOrigin, &mUp);
    D3DXMATRIX mLookAtInv;
    D3DXMatrixInverse(&mLookAtInv, NULL, &mLookAtMatrix);
    D3DXMATRIX mWorld = mScale * mLookAtInv * (*g_Camera.GetWorldMatrix());
    D3DXMatrixMultiply( &WorldViewMatrix, &mWorld, g_Camera.GetViewMatrix());
    D3DXMatrixMultiply( &WorldViewProjMatrix, &WorldViewMatrix, g_Camera.GetProjMatrix() );
    g_pWorldViewProjShaderVariable->SetMatrix( (float*)&WorldViewProjMatrix );

    pd3dDevice->IASetInputLayout(g_pVertexLayoutArrow);
    g_MeshArrow.Render(pd3dDevice,g_pTechniqueRenderArrow);
    

    //------------------------------------------------------------------------------------
    // Set Effects Parameters
    //------------------------------------------------------------------------------------

    ViewMatrix = *g_Camera.GetViewMatrix();
    D3DXVECTOR3 LightInViewSpace;
    vectorMatrixMultiply(&LightInViewSpace, ViewMatrix,g_PointLightPos);
    D3DXVec3Normalize(&LightInViewSpace,&LightInViewSpace);
    g_LightPosWithViewTransformationShaderVariable->SetFloatVector((float*)&LightInViewSpace);
    vectorMatrixMultiply(&LightInViewSpace, ViewMatrix,g_PointLightPos2);
    D3DXVec3Normalize(&LightInViewSpace,&LightInViewSpace);
    g_LightPosWithViewTransformation2ShaderVariable->SetFloatVector((float*)&LightInViewSpace);
    D3DXMatrixInverse( &InvViewMatrix, NULL, &ViewMatrix );
    g_pInvViewShaderVariable->SetMatrix( (float*)&InvViewMatrix ); 
    g_pProjectionShaderVariable->SetMatrix( (float*)g_Camera.GetProjMatrix());
    D3DXMatrixInverse( &InvProjectionMatrix, NULL, g_Camera.GetProjMatrix() );
    g_pInverseProjectionShaderVariable->SetMatrix( (float*)&InvProjectionMatrix);
    g_pEyePosShaderVariable->SetFloatVector((float*)g_Camera.GetEyePt());

    D3DXVECTOR3 VecLightEye;
    D3DXVec3Subtract(&VecLightEye,&g_PointLightPos,g_Camera.GetEyePt());
    float lengthVecLightEye = D3DXVec3Length(&VecLightEye);
    D3DXVec3Normalize(&VecLightEye,&VecLightEye);
    g_VecPointLightEyeShaderVariable->SetFloatVector((float*)&VecLightEye);
    g_DSVPointLightShaderVariable->SetFloat( lengthVecLightEye );

    D3DXVECTOR3 VecLightEye2;
    D3DXVec3Subtract(&VecLightEye2,&g_PointLightPos2,g_Camera.GetEyePt());
    float lengthVecLightEye2 = D3DXVec3Length(&VecLightEye2);
    D3DXVec3Normalize(&VecLightEye2,&VecLightEye2);
    g_VecPointLightEye2ShaderVariable->SetFloatVector((float*)&VecLightEye2);
    g_DSVPointLight2ShaderVariable->SetFloat( lengthVecLightEye2 );

    static float timeCycle = 0;
    if(g_bMoveParticles)
       timeCycle += 0.085;
    g_timeCycleShaderVariable->SetFloat(timeCycle);
    if(timeCycle>=1)
	{
		timeCycle = 0;
        g_rainSplashesXDisplaceShaderVariable->SetFloat( random()*2 );
        g_rainSplashesYDisplaceShaderVariable->SetFloat( random()*2 );
	}
    //-------------------------------------------------------------------------------------
    //draw the scene
    //-------------------------------------------------------------------------------------

    UINT stride[1] = { sizeof(SimpleVertex) };
    UINT offset[1] = { 0 };

    if(g_bRenderBg)
    { 
        D3DXMatrixScaling(&g_WorldMatrix, 3, 3, 3);
        D3DXMatrixMultiply( &WorldViewMatrix, &g_WorldMatrix, &ViewMatrix );
        D3DXMatrixMultiply( &WorldViewProjMatrix, &WorldViewMatrix, g_Camera.GetProjMatrix() );
        g_pWorldShaderVariable->SetMatrix((float*)&g_WorldMatrix);
        g_pWorldViewProjShaderVariable->SetMatrix( (float*)&WorldViewProjMatrix );
        g_pWorldViewShaderVariable->SetMatrix( (float*)&WorldViewMatrix );

        pd3dDevice->IASetInputLayout( g_pVertexLayoutScene );
        g_Mesh.Render( pd3dDevice, g_pTechniqueRenderScene );
    }

    //-------------------------------------------------------------------------------------
    //advance rain
    //-------------------------------------------------------------------------------------

    stride[0] = sizeof(RainVertex);

    if(g_bMoveParticles)
    {
        pd3dDevice->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_POINTLIST );
        pd3dDevice->IASetInputLayout( g_pVertexLayoutRainVertex );
    
        ID3D10Buffer *pBuffers[1];
        if(firstFrame)
            pBuffers[0] = g_pParticleStart;
        else
            pBuffers[0] = g_pParticleDrawFrom;

        pd3dDevice->IASetVertexBuffers( 0, 1, pBuffers, stride, offset );
 
        // Point to the correct output buffer
        pBuffers[0] = g_pParticleStreamTo;
        pd3dDevice->SOSetTargets( 1, pBuffers, offset );
        
        // draw
        D3D10_TECHNIQUE_DESC techDesc;
        g_pTechniqueAdvanceRain->GetDesc( &techDesc );
        g_pTechniqueAdvanceRain->GetPassByIndex(0)->Apply(0);

        pd3dDevice->Draw(g_numRainVertices , 0 );

        // Get back to normal
        pBuffers[0] = NULL;
        pd3dDevice->SOSetTargets( 1, pBuffers, offset );

        // Swap buffers
        ID3D10Buffer* pTemp = g_pParticleDrawFrom;
        g_pParticleDrawFrom = g_pParticleStreamTo;
        g_pParticleStreamTo = pTemp;
    
        firstFrame = false;

    }

    //-------------------------------------------------------------------------------------
    //draw rain
    //-------------------------------------------------------------------------------------


    if(g_bDrawParticles)
    {
        D3DXMatrixIdentity( &g_WorldMatrix );
        D3DXMatrixMultiply( &WorldViewMatrix, &g_WorldMatrix, &ViewMatrix );
        D3DXMatrixMultiply( &WorldViewProjMatrix, &WorldViewMatrix, g_Camera.GetProjMatrix() );
        g_pWorldShaderVariable->SetMatrix((float*)&g_WorldMatrix);
        g_pWorldViewProjShaderVariable->SetMatrix( (float*)&WorldViewProjMatrix );
        g_pWorldViewShaderVariable->SetMatrix( (float*)&WorldViewMatrix );

        pd3dDevice->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_POINTLIST );
        pd3dDevice->IASetInputLayout( g_pVertexLayoutRainVertex );
        pd3dDevice->IASetVertexBuffers( 0, 1, &g_pParticleDrawFrom, stride, offset );
        
        if(g_bUseCheapShader)
            g_pTechniqueDrawRainCheap->GetPassByIndex( 0 )->Apply(0);
        else
            g_pTechniqueDrawRain->GetPassByIndex( 0 )->Apply(0);

        pd3dDevice->Draw( int(g_numRainVertices*g_DrawFraction) , 0 );
    }

    //-------------------------------------------------------------------------------------
    //HUD
    //-------------------------------------------------------------------------------------
    
    g_SampleUI.OnRender( fElapsedTime );
    g_HUD.OnRender( fElapsedTime );
    RenderText();


    //-------------------------------------------------------------------------------------
    //capture the frame
    //-------------------------------------------------------------------------------------

//    #define captureImages
    #ifdef captureImages
    static int g_Frame = 0;
    g_Frame++;
    IDXGISwapChain* pSwapChain = DXUTGetDXGISwapChain();
    ID3D10Texture2D* pRTCap;
    pSwapChain->GetBuffer(0, __uuidof(pRTCap), reinterpret_cast<void**>(&pRTCap));
    WCHAR filename[100];
    StringCchPrintf(filename, 100, L"screenshots/screenshot%.3d.dds", g_Frame); 
    D3DX10SaveTextureToFile(pRTCap, D3DX10_IFF_DDS, filename);
    pRTCap->Release();
    #endif

    ID3D10RenderTargetView* pNULLRT = {NULL};
    pd3dDevice->OMSetRenderTargets( 1, &(pNULLRT), NULL );
}


//--------------------------------------------------------------------------------------
// Render the help and statistics text
//--------------------------------------------------------------------------------------
void RenderText()
{
    g_pTxtHelper->Begin();
    g_pTxtHelper->SetInsertionPos( 2, 0 );
    g_pTxtHelper->SetForegroundColor( D3DXCOLOR( 1.0f, 1.0f, 0.0f, 1.0f ) );
    g_pTxtHelper->DrawTextLine( DXUTGetFrameStats(true) );
    g_pTxtHelper->DrawTextLine( DXUTGetDeviceStats() );

    // Draw help
    if( g_bShowHelp )
    {
        UINT nBackBufferHeight = ( DXUTIsAppRenderingWithD3D9() ) ? DXUTGetD3D9BackBufferSurfaceDesc()->Height : DXUTGetDXGIBackBufferSurfaceDesc()->Height;
        g_pTxtHelper->SetInsertionPos( 2, nBackBufferHeight-15*6 );
        g_pTxtHelper->SetForegroundColor( D3DXCOLOR( 1.0f, 1.0f, 0.0f, 1.0f ) );
        g_pTxtHelper->DrawTextLine( L"Controls:" );

        g_pTxtHelper->SetInsertionPos( 20, nBackBufferHeight-15*5 );
        g_pTxtHelper->DrawTextLine( L"Rotate camera:  Right mouse button\n"
                                    L"Zoom camera:  Mouse wheel scroll\n"
                                    L"Rotate light: Left mouse button\n"
                                    );

        g_pTxtHelper->SetInsertionPos( 250, nBackBufferHeight-15*5 );
        g_pTxtHelper->DrawTextLine( L"Hide help: F1\n" 
                                    L"Quit: ESC\n" );
    }
    else
    {
        g_pTxtHelper->SetForegroundColor( D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
        g_pTxtHelper->DrawTextLine( L"Press F1 for help" );
    }

    g_pTxtHelper->End();
}


//--------------------------------------------------------------------------------------
// Release D3D10 resources created in OnD3D10ResizedSwapChain 
//--------------------------------------------------------------------------------------
void CALLBACK OnD3D10ReleasingSwapChain( void* pUserContext )
{
    g_DialogResourceManager.OnD3D10ReleasingSwapChain();
}


//--------------------------------------------------------------------------------------
// Release D3D10 resources created in OnD3D10CreateDevice 
//--------------------------------------------------------------------------------------

void CALLBACK OnD3D10DestroyDevice( void* pUserContext )
{
    g_DialogResourceManager.OnD3D10DestroyDevice();
    g_D3DSettingsDlg.GetDialogControl()->RemoveAllControls();
    g_D3DSettingsDlg.OnD3D10DestroyDevice();
    SAFE_DELETE(g_lightDirectionWidget);
    CDXUTDirectionWidget::StaticOnD3D10DestroyDevice();

    SAFE_RELEASE( g_pFont );
    SAFE_RELEASE( g_pSprite );
    SAFE_RELEASE( g_pEffect );
    SAFE_DELETE( g_pTxtHelper );

    //vertex buffers and layout
    SAFE_RELEASE( g_pVertexLayoutRainVertex ); 
    SAFE_RELEASE( g_pVertexLayoutScene );
    SAFE_RELEASE( g_pVertexLayoutArrow );
    SAFE_RELEASE( g_pVertexLayoutSky );
    SAFE_RELEASE( g_VertexBufferSky );
    SAFE_RELEASE( g_pParticleStart );
    SAFE_RELEASE( g_pParticleStreamTo );
    SAFE_RELEASE( g_pParticleDrawFrom );

    g_Mesh.Destroy();
    g_MeshArrow.Destroy();

}

//--------------------------------------------------------------------------------------
// Call if device was removed.  Return true to find a new device, false to quit
//--------------------------------------------------------------------------------------
bool CALLBACK OnDeviceRemoved( void* pUserContext )
{
    return true;
}


//--------------------------------------------------------------------------------------
// Called right before creating a D3D9 or D3D10 device, allowing the app to modify the device settings as needed
//--------------------------------------------------------------------------------------
bool CALLBACK ModifyDeviceSettings( DXUTDeviceSettings* pDeviceSettings, void* pUserContext )
{
    pDeviceSettings->d3d10.SyncInterval = 0;
    return true;
}


//--------------------------------------------------------------------------------------
// This callback function will be called once at the beginning of every frame. This is the
// best location for your application to handle updates to the scene, but is not 
// intended to contain actual rendering calls, which should instead be placed in the 
// OnFrameRender callback.  
//--------------------------------------------------------------------------------------
void CALLBACK OnFrameMove( double fTime, float fElapsedTime, void* pUserContext )
{
    g_Camera.FrameMove( fElapsedTime );
}


//--------------------------------------------------------------------------------------
// Before handling window messages, DXUT passes incoming windows 
// messages to the application through this callback function. If the application sets 
// *pbNoFurtherProcessing to TRUE, then DXUT will not process this message.
//--------------------------------------------------------------------------------------
LRESULT CALLBACK MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext )
{
    // Pass messages to dialog resource manager calls so GUI state is updated correctly
    *pbNoFurtherProcessing = g_DialogResourceManager.MsgProc( hWnd, uMsg, wParam, lParam );
    if( *pbNoFurtherProcessing )
        return 0;

    // Pass messages to settings dialog if its active
    if( g_D3DSettingsDlg.IsActive() )
    {
        g_D3DSettingsDlg.MsgProc( hWnd, uMsg, wParam, lParam );
        return 0;
    }

    // Give the dialogs a chance to handle the message first
    *pbNoFurtherProcessing = g_HUD.MsgProc( hWnd, uMsg, wParam, lParam );
    if( *pbNoFurtherProcessing )
        return 0;
    *pbNoFurtherProcessing = g_SampleUI.MsgProc( hWnd, uMsg, wParam, lParam );
    if( *pbNoFurtherProcessing )
        return 0;

    //handle messages for the comb directional control
    g_lightDirectionWidget->HandleMessages( hWnd, uMsg, wParam, lParam );

    // Pass all remaining windows messages to camera so it can respond to user input
    g_Camera.HandleMessages( hWnd, uMsg, wParam, lParam );

    return 0;
}


//--------------------------------------------------------------------------------------
// Handle key presses
//--------------------------------------------------------------------------------------
void CALLBACK KeyboardProc( UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext )
{
    if( bKeyDown )
    {
        switch( nChar )
        {
            case VK_F1: g_bShowHelp = !g_bShowHelp; 
                break;
        }
    }
}


//--------------------------------------------------------------------------------------
// Handles the GUI events
//--------------------------------------------------------------------------------------
void CALLBACK OnGUIEvent( UINT nEvent, int nControlID, CDXUTControl* pControl, void* pUserContext )
{    
    switch( nControlID )
    {
        case IDC_TOGGLEFULLSCREEN: DXUTToggleFullScreen(); break;
        case IDC_TOGGLEREF:        DXUTToggleREF(); break;
        case IDC_CHANGEDEVICE:     g_D3DSettingsDlg.SetActive( !g_D3DSettingsDlg.IsActive() ); break;

        case IDC_TOGGLEBG:
        {
            g_bRenderBg = g_SampleUI.GetCheckBox( IDC_TOGGLEBG )->GetChecked();
            g_pRenderBGShaderVariable->SetInt(g_bRenderBg);
            break;
        }
        case IDC_TOGGLEMOVE:
        {
            g_bMoveParticles = g_SampleUI.GetCheckBox( IDC_TOGGLEMOVE )->GetChecked();
            g_pMoveParticlesShaderVariable->SetInt(g_bMoveParticles);
            break;
        }
        case IDC_TOGGLEDRAW:
        {
            g_bDrawParticles = g_SampleUI.GetCheckBox( IDC_TOGGLEDRAW )->GetChecked();
            break;
        }
        case IDC_TOGGLECHEAPSHADER:
        {
            g_bUseCheapShader = g_SampleUI.GetCheckBox( IDC_TOGGLECHEAPSHADER )->GetChecked();
            break;
        }
        case IDC_TOGGLEPRESET1:
        {   
            g_SampleUI.RemoveAllControls();
            //set all variables to preset 1
            resetVariablesToPreset1();             
            //redraw the controls
            resetGUIControls();
            break;
        }
        case IDC_TOGGLEPRESET2:
        {   
            g_SampleUI.RemoveAllControls();
            //set all variables to preset 2
            resetVariablesToPreset2();             
            //redraw the controls
            resetGUIControls();
            break;
        }
        case IDC_TOGGLESPOTLIGHT:
        {
            g_bUseSpotLight = g_SampleUI.GetCheckBox( IDC_TOGGLESPOTLIGHT )->GetChecked();
            g_UseSpotLightShaderVariable->SetBool(g_bUseSpotLight);
            break;
        }
           
        case IDC_FOGTHICKNESS_SCALE:
        {
            WCHAR sz[100];
            g_fogVector.x = g_fogVector.y = g_fogVector.z =(float) (g_SampleUI.GetSlider( IDC_FOGTHICKNESS_SCALE )->GetValue()* 0.001f);
            StringCchPrintf( sz, 100, L"Fog Thickness: %0.2f", g_fogVector.x ); 
            g_SampleUI.GetStatic( IDC_FOGTHICKNESS_STATIC )->SetText( sz );
            g_pFogThicknessShaderVariable->SetFloatVector((float*)&g_fogVector);
            break;
        }
   
        case IDC_DIRLIGHTINTENSITY_SCALE:
        {
            WCHAR sz[100];
            g_dirLightIntensity = (float) (g_SampleUI.GetSlider( IDC_DIRLIGHTINTENSITY_SCALE )->GetValue()* 0.01f);
            StringCchPrintf( sz, 100, L"Intensity: %0.2f", g_dirLightIntensity ); 
            g_SampleUI.GetStatic( IDC_DIRLIGHTINTENSITY_STATIC )->SetText( sz );
            g_pDirLightIntensityShaderVariable->SetFloat(g_dirLightIntensity);
            break;
        }

        case IDC_RESPONSEDIRLIGHT_SCALE:
        {
            WCHAR sz[100];
            g_responseDirLight = (float) (g_SampleUI.GetSlider( IDC_RESPONSEDIRLIGHT_SCALE )->GetValue()* 0.01f);
            StringCchPrintf( sz, 100, L"Rain response: %0.2f", g_responseDirLight ); 
            g_SampleUI.GetStatic( IDC_RESPONSEDIRLIGHT_STATIC )->SetText( sz );
            g_pResponseDirLightShaderVariable->SetFloat(g_responseDirLight);
            break;
        }

        case IDC_POINTLIGHTINTENSITY_SCALE:
        {
            WCHAR sz[100];
            g_PointLightIntensity = (float) (g_SampleUI.GetSlider( IDC_POINTLIGHTINTENSITY_SCALE )->GetValue()* 0.01f);
            StringCchPrintf( sz, 100, L"Point Light: %0.2f", g_PointLightIntensity ); 
            g_SampleUI.GetStatic( IDC_POINTLIGHTINTENSITY_STATIC )->SetText( sz );
            g_pPointLightIntensityShaderVariable->SetFloat(g_PointLightIntensity);
            break;
        }

        case IDC_COSSPOTLIGHT_SCALE:
        {
            WCHAR sz[100];
            g_cosSpotLight = (float) (g_SampleUI.GetSlider( IDC_COSSPOTLIGHT_SCALE )->GetValue()* 0.01f);
            StringCchPrintf( sz, 100, L"Cos SpotLight: %0.2f", g_cosSpotLight ); 
            g_SampleUI.GetStatic( IDC_COSSPOTLIGHT_STATIC )->SetText( sz );
            g_CosSpotLightShaderVariable->SetFloat(g_cosSpotLight);
            break;
        }

        case IDC_RESPONSEPOINTLIGHT_SCALE:
        {
            WCHAR sz[100];
            g_responsePointLight = (float) (g_SampleUI.GetSlider( IDC_RESPONSEPOINTLIGHT_SCALE )->GetValue()* 0.01f);
            StringCchPrintf( sz, 100, L"Rain response: %0.2f", g_responsePointLight ); 
            g_SampleUI.GetStatic( IDC_RESPONSEPOINTLIGHT_STATIC )->SetText( sz );
            g_pResponsePointLightShaderVariable->SetFloat(g_responsePointLight);
            break;
        }

        case IDC_DRAWFRACTION_SCALE:
        {
            WCHAR sz[100];
            g_DrawFraction = (float) (g_SampleUI.GetSlider( IDC_DRAWFRACTION_SCALE )->GetValue()* 0.01f);
            StringCchPrintf( sz, 100, L"Particles Drawn: %0.2f", g_numRainVertices*g_DrawFraction ); 
            g_SampleUI.GetStatic( IDC_DRAWFRACTION_STATIC )->SetText( sz );
            setShadingParametersBasedOnRain();
            break;
        }
        case IDC_WINDAMOUNT_SCALE:
        {
            WCHAR sz[100];
            g_WindAmount = (float) (g_SampleUI.GetSlider( IDC_WINDAMOUNT_SCALE )->GetValue()* 0.01f);
            StringCchPrintf( sz, 100, L"Wind: %0.2f", g_WindAmount); 
            g_SampleUI.GetStatic( IDC_WINDAMOUNT_STATIC )->SetText( sz );
            break;
        }
    }
}

//--------------------------------------------------------------------------------------
// Helper functions
//--------------------------------------------------------------------------------------



HRESULT loadTextureFromFile(LPCWSTR file,LPCSTR shaderTextureName, ID3D10Device* pd3dDevice)
{

    HRESULT hr;

    D3DX10_IMAGE_LOAD_INFO texLoadInfo;
    texLoadInfo.MipLevels = 11;
    texLoadInfo.MipFilter = D3DX10_FILTER_TRIANGLE;
    texLoadInfo.Filter = D3DX10_FILTER_TRIANGLE;
    texLoadInfo.Format = DXGI_FORMAT_R16G16B16A16_UNORM;
    ID3D10Resource *pRes = NULL;

    WCHAR str[MAX_PATH];
    V_RETURN(NVUTFindDXSDKMediaFileCch(str, MAX_PATH, file));

    V_RETURN( D3DX10CreateTextureFromFile(pd3dDevice, str, &texLoadInfo, NULL, &pRes, &hr ) );
    if( pRes )
    {
        ID3D10Texture2D* texture;


        pRes->QueryInterface( __uuidof( ID3D10Texture2D ), (LPVOID*)&texture );
        D3D10_TEXTURE2D_DESC desc;
        texture->GetDesc( &desc );
        D3D10_SHADER_RESOURCE_VIEW_DESC SRVDesc;
        ZeroMemory( &SRVDesc, sizeof(SRVDesc) );
        SRVDesc.Format = desc.Format;
        SRVDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE2D;
        SRVDesc.Texture2D.MostDetailedMip = 0;
        SRVDesc.Texture2D.MipLevels = desc.MipLevels;

        ID3D10ShaderResourceView* textureRview;
        V_RETURN (pd3dDevice->CreateShaderResourceView( texture, &SRVDesc, &textureRview));
        ID3D10EffectShaderResourceVariable* textureRVar = g_pEffect->GetVariableByName( shaderTextureName )->AsShaderResource();
        textureRVar->SetResource( textureRview );

        SAFE_RELEASE( texture );
        SAFE_RELEASE(textureRview);
     }

    SAFE_RELEASE(pRes);
    return S_OK;
}

HRESULT loadCubemapTextureFromFile(LPCWSTR file,LPCSTR shaderTextureName, ID3D10Device* pd3dDevice)
{

    HRESULT hr;

    WCHAR str[MAX_PATH];
    V_RETURN(NVUTFindDXSDKMediaFileCch(str, MAX_PATH, file));

    D3DX10_IMAGE_INFO SrcInfo;
    hr = D3DX10GetImageInfoFromFile(str, NULL, &SrcInfo, &hr);

    D3DX10_IMAGE_LOAD_INFO texLoadInfo;
    texLoadInfo.Width          = SrcInfo.Width;
    texLoadInfo.Height         = SrcInfo.Height;
    texLoadInfo.Depth          = SrcInfo.Depth;
    texLoadInfo.FirstMipLevel  = 0;
    texLoadInfo.MipLevels      = SrcInfo.MipLevels;
    texLoadInfo.Usage          = D3D10_USAGE_DEFAULT;
    texLoadInfo.BindFlags      = D3D10_BIND_SHADER_RESOURCE;
    texLoadInfo.CpuAccessFlags = 0;
    texLoadInfo.MiscFlags      = SrcInfo.MiscFlags;
    texLoadInfo.Format         = SrcInfo.Format;
    texLoadInfo.Filter         = D3DX10_FILTER_TRIANGLE;
    texLoadInfo.MipFilter      = D3DX10_FILTER_TRIANGLE;
    texLoadInfo.pSrcInfo       = &SrcInfo;
    ID3D10Resource *pRes = NULL;

    V_RETURN( D3DX10CreateTextureFromFile(pd3dDevice, str, &texLoadInfo, NULL, &pRes, &hr ) );
    if( pRes )
    {
        ID3D10Texture2D* texture;


        pRes->QueryInterface( __uuidof( ID3D10Texture2D ), (LPVOID*)&texture );
        D3D10_SHADER_RESOURCE_VIEW_DESC SRVDesc;
        ZeroMemory( &SRVDesc, sizeof(SRVDesc) );
        SRVDesc.Format = texLoadInfo.Format;
        SRVDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURECUBE;
        SRVDesc.Texture2D.MostDetailedMip = 0;
        SRVDesc.Texture2D.MipLevels = texLoadInfo.MipLevels;

        ID3D10ShaderResourceView* textureRview;
        V_RETURN (pd3dDevice->CreateShaderResourceView( texture, &SRVDesc, &textureRview));
        ID3D10EffectShaderResourceVariable* textureRVar = g_pEffect->GetVariableByName( shaderTextureName )->AsShaderResource();
        textureRVar->SetResource( textureRview );

        SAFE_RELEASE( texture );
        SAFE_RELEASE(textureRview);
     }

    SAFE_RELEASE(pRes);
    return S_OK;
}

HRESULT load3DTextureFromFile(LPCWSTR file,LPCSTR shaderTextureName, ID3D10Device* pd3dDevice)
{

    HRESULT hr;

    WCHAR str[MAX_PATH];
    V_RETURN(NVUTFindDXSDKMediaFileCch(str, MAX_PATH, file));

    D3DX10_IMAGE_INFO SrcInfo;
    hr = D3DX10GetImageInfoFromFile(str, NULL, &SrcInfo, &hr);

    D3DX10_IMAGE_LOAD_INFO texLoadInfo;
    texLoadInfo.Width          = SrcInfo.Width;
    texLoadInfo.Height         = SrcInfo.Height;
    texLoadInfo.Depth          = SrcInfo.Depth;
    texLoadInfo.FirstMipLevel  = 0;
    texLoadInfo.MipLevels      = SrcInfo.MipLevels;
    texLoadInfo.Usage          = D3D10_USAGE_DEFAULT;
    texLoadInfo.BindFlags      = D3D10_BIND_SHADER_RESOURCE;
    texLoadInfo.CpuAccessFlags = 0;
    texLoadInfo.MiscFlags      = SrcInfo.MiscFlags;
    texLoadInfo.Format         = SrcInfo.Format;
    texLoadInfo.Filter         = D3DX10_FILTER_TRIANGLE;
    texLoadInfo.MipFilter      = D3DX10_FILTER_TRIANGLE;
    texLoadInfo.pSrcInfo       = &SrcInfo;
    ID3D10Resource *pRes = NULL;

    V_RETURN( D3DX10CreateTextureFromFile(pd3dDevice, str, &texLoadInfo, NULL, &pRes, &hr ) );
    if( pRes )
    {
        ID3D10Texture3D* texture;


        pRes->QueryInterface( __uuidof( ID3D10Texture3D ), (LPVOID*)&texture );
        D3D10_SHADER_RESOURCE_VIEW_DESC SRVDesc;
        ZeroMemory( &SRVDesc, sizeof(SRVDesc) );
        SRVDesc.Format = texLoadInfo.Format;
        SRVDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE3D;
        SRVDesc.Texture3D.MostDetailedMip = 0;
        SRVDesc.Texture3D.MipLevels = texLoadInfo.MipLevels;

        ID3D10ShaderResourceView* textureRview;
        V_RETURN (pd3dDevice->CreateShaderResourceView( texture, &SRVDesc, &textureRview));
        ID3D10EffectShaderResourceVariable* textureRVar = g_pEffect->GetVariableByName( shaderTextureName )->AsShaderResource();
        textureRVar->SetResource( textureRview );

        SAFE_RELEASE( texture );
        SAFE_RELEASE(textureRview);
     }

    SAFE_RELEASE(pRes);
    return S_OK;
}


//--------------------------------------------------------------------------------------
// LoadTextureArray loads a texture array and associated view from a series
// of textures on disk.
//--------------------------------------------------------------------------------------
HRESULT LoadTextureArray( ID3D10Device* pd3dDevice, char* sTexturePrefix, int iNumTextures, ID3D10Texture2D** ppTex2D, ID3D10ShaderResourceView** ppSRV)
{
    HRESULT hr = S_OK;
    D3D10_TEXTURE2D_DESC desc;
    ZeroMemory( &desc, sizeof(D3D10_TEXTURE2D_DESC) );
    
    WCHAR szTextureName[MAX_PATH];
    WCHAR str[MAX_PATH];
    for(int i=0; i<iNumTextures; i++)
    {
        wsprintf(szTextureName, L"%S%.4d.dds", sTexturePrefix, i); 
        V_RETURN( NVUTFindDXSDKMediaFileCch( str, MAX_PATH, szTextureName ) );

        ID3D10Resource *pRes = NULL;
        D3DX10_IMAGE_LOAD_INFO loadInfo;
        ZeroMemory( &loadInfo, sizeof( D3DX10_IMAGE_LOAD_INFO ) );
        loadInfo.Width = D3DX_FROM_FILE;
        loadInfo.Height  = D3DX_FROM_FILE;
        loadInfo.Depth  = D3DX_FROM_FILE;
        loadInfo.FirstMipLevel = 0;
        loadInfo.MipLevels = 10;
        loadInfo.Usage = D3D10_USAGE_STAGING;
        loadInfo.BindFlags = 0;
        loadInfo.CpuAccessFlags = D3D10_CPU_ACCESS_WRITE | D3D10_CPU_ACCESS_READ;
        loadInfo.MiscFlags = 0;
        loadInfo.Format = DXGI_FORMAT_R8_UNORM; 
        loadInfo.Filter = D3DX10_FILTER_TRIANGLE;
        loadInfo.MipFilter = D3DX10_FILTER_TRIANGLE;

        V_RETURN(D3DX10CreateTextureFromFile( pd3dDevice, str, &loadInfo, NULL, &pRes, &hr ));
        if( pRes )
        {
            ID3D10Texture2D* pTemp;
            pRes->QueryInterface( __uuidof( ID3D10Texture2D ), (LPVOID*)&pTemp );
            pTemp->GetDesc( &desc );

            D3D10_MAPPED_TEXTURE2D mappedTex2D;
            if(DXGI_FORMAT_R8_UNORM != desc.Format)   
                return false;

            if(!(*ppTex2D))
            {
                desc.Usage = D3D10_USAGE_DEFAULT;
                desc.BindFlags = D3D10_BIND_SHADER_RESOURCE;
                desc.CPUAccessFlags = 0;
                desc.ArraySize = iNumTextures;
                V_RETURN(pd3dDevice->CreateTexture2D( &desc, NULL, ppTex2D));
            }

            for(UINT iMip=0; iMip < desc.MipLevels; iMip++)
            {
                pTemp->Map( iMip, D3D10_MAP_READ, 0, &mappedTex2D );
                    
                pd3dDevice->UpdateSubresource( (*ppTex2D), 
                                                D3D10CalcSubresource( iMip, i, desc.MipLevels ),
                                                NULL,
                                                mappedTex2D.pData,
                                                mappedTex2D.RowPitch,
                                                0 );

                pTemp->Unmap( iMip );
            }

            SAFE_RELEASE( pRes );
            SAFE_RELEASE( pTemp );
        }
        else
        {
            return false;
        }
    }

    D3D10_SHADER_RESOURCE_VIEW_DESC SRVDesc;
    ZeroMemory( &SRVDesc, sizeof(SRVDesc) );
    SRVDesc.Format = desc.Format;
    SRVDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE2DARRAY;
    SRVDesc.Texture2DArray.MipLevels = desc.MipLevels;
    SRVDesc.Texture2DArray.ArraySize = iNumTextures;
    V_RETURN(pd3dDevice->CreateShaderResourceView( *ppTex2D, &SRVDesc, ppSRV ));

    return hr;
}

//-----------------------------------------------------------------------------------------------
//load LUTS as textures
//-----------------------------------------------------------------------------------------------

HRESULT loadLUTS(char* fileName, LPCSTR shaderTextureName, int xRes, int yRes, ID3D10Device* pd3dDevice)
{
    HRESULT hr = S_OK;

    ifstream infile (fileName ,ios::in);
    if (infile.is_open())
    {   
        float* data = new float[xRes*yRes];
        int index = 0;
        char tempc;
        for(int j=0;j<yRes;j++)
        {   for(int i=0;i<xRes-1;i++)  
               infile>>data[index++]>>tempc;
            infile>>data[index++];
            
        }
        
        D3D10_SUBRESOURCE_DATA InitData;
        InitData.SysMemPitch = sizeof(float) * xRes;
        InitData.pSysMem = data;

        ID3D10Texture2D* texture = NULL;
        D3D10_TEXTURE2D_DESC texDesc;
        ZeroMemory( &texDesc, sizeof(D3D10_TEXTURE2D_DESC) );
        texDesc.Width = xRes;
        texDesc.Height = yRes;
        texDesc.MipLevels = 1;
        texDesc.ArraySize = 1;
        texDesc.Format = DXGI_FORMAT_R32_FLOAT;
        texDesc.SampleDesc.Count = 1;
        texDesc.SampleDesc.Quality = 0;
        texDesc.Usage = D3D10_USAGE_DEFAULT;
        texDesc.BindFlags = D3D10_BIND_SHADER_RESOURCE;

        V_RETURN(pd3dDevice->CreateTexture2D(&texDesc,&InitData,&texture));

        D3D10_SHADER_RESOURCE_VIEW_DESC SRVDesc;
        ZeroMemory( &SRVDesc, sizeof(SRVDesc) );
        SRVDesc.Format = texDesc.Format;
        SRVDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE2D;
        SRVDesc.Texture2D.MipLevels = 1;
        SRVDesc.Texture2D.MostDetailedMip = 0;

        ID3D10ShaderResourceView* textureRview;
        V_RETURN (pd3dDevice->CreateShaderResourceView( texture, &SRVDesc, &textureRview));
        ID3D10EffectShaderResourceVariable* textureRVar = g_pEffect->GetVariableByName( shaderTextureName )->AsShaderResource();
        textureRVar->SetResource( textureRview );

        SAFE_RELEASE( texture );
        SAFE_RELEASE( textureRview);
        delete[] data;
    }
    else
       hr = S_FALSE;
    return hr;
}

//----------------------------------------------------------------------------------------
//random numbers; replace with a better quality generator for better particle distribution
//----------------------------------------------------------------------------------------

float random()
{
    return (float(   (double)rand() / ((double)(RAND_MAX)+(double)(1)) ));
}

//----------------------------------------------------------------------------------------
//function to reset all the controls to preset values
//----------------------------------------------------------------------------------------
void resetVariablesToPreset1()
{
     //set all variables to preset values
    g_bRenderBg = true;
    g_bMoveParticles = true;
    g_bDrawParticles = true;
    g_bUseCheapShader = false;
    g_bUseSpotLight = true;
    g_fogVector = g_constFogVector1;
    g_dirLightIntensity = g_constDirLightIntensity1;
    g_responseDirLight = g_constResponseDirLight1;
    g_PointLightIntensity = g_constPointLightIntensity1;
    g_cosSpotLight = g_constCosSpotLight1;
    g_responsePointLight = g_constResponsePointLight1;
    g_DrawFraction = g_constDrawFraction1;
    g_WindAmount = g_constWindAmount1;
     
     //update variables in the shader
    g_pRenderBGShaderVariable->SetInt(g_bRenderBg);
    g_pMoveParticlesShaderVariable->SetInt(g_bMoveParticles);
    g_UseSpotLightShaderVariable->SetBool(g_bUseSpotLight);
    g_pFogThicknessShaderVariable->SetFloatVector((float*)&g_fogVector);
    g_pDirLightIntensityShaderVariable->SetFloat(g_dirLightIntensity);
    g_pResponseDirLightShaderVariable->SetFloat(g_responseDirLight);
    g_pPointLightIntensityShaderVariable->SetFloat(g_PointLightIntensity);
    g_CosSpotLightShaderVariable->SetFloat(g_cosSpotLight);
    g_pResponsePointLightShaderVariable->SetFloat(g_responsePointLight);
    setShadingParametersBasedOnRain();
    
    SAFE_DELETE(g_lightDirectionWidget);
    g_lightDirectionWidget = new CDXUTDirectionWidget();
    g_lightDirectionWidget->SetButtonMask(MOUSE_LEFT_BUTTON);
    g_lightDirectionWidget->SetLightDirection( g_directionalLightVector1 );
    g_lightDirectionWidget->SetRadius( 10.0f );

    //set the camera back to where it was 
    g_vecEye = g_constVecEye1;
    g_vecAt = g_constAtVec1;
    g_Camera.SetViewParams( &g_vecEye, &g_vecAt );
}


void resetVariablesToPreset2()
{
    //set all variables to preset values
    g_bRenderBg = true;
    g_bMoveParticles = true;
    g_bDrawParticles = true;
    g_bUseCheapShader = false;
    g_bUseSpotLight = true;
    g_fogVector = g_constFogVector2;
    g_dirLightIntensity = g_constDirLightIntensity2;
    g_responseDirLight = g_constResponseDirLight2;
    g_PointLightIntensity = g_constPointLightIntensity2;
    g_cosSpotLight = g_constCosSpotLight2;
    g_responsePointLight = g_constResponsePointLight2;
    g_DrawFraction = g_constDrawFraction2;
    g_WindAmount = g_constWindAmount2;
     
    //update variables in the shader
    g_pRenderBGShaderVariable->SetInt(g_bRenderBg);
    g_pMoveParticlesShaderVariable->SetInt(g_bMoveParticles);
    g_UseSpotLightShaderVariable->SetBool(g_bUseSpotLight);
    g_pFogThicknessShaderVariable->SetFloatVector((float*)&g_fogVector);
    g_pDirLightIntensityShaderVariable->SetFloat(g_dirLightIntensity);
    g_pResponseDirLightShaderVariable->SetFloat(g_responseDirLight);
    g_pPointLightIntensityShaderVariable->SetFloat(g_PointLightIntensity);
    g_CosSpotLightShaderVariable->SetFloat(g_cosSpotLight);
    g_pResponsePointLightShaderVariable->SetFloat(g_responsePointLight);
    setShadingParametersBasedOnRain();
     
    SAFE_DELETE(g_lightDirectionWidget);
    g_lightDirectionWidget = new CDXUTDirectionWidget();
    g_lightDirectionWidget->SetButtonMask(MOUSE_LEFT_BUTTON);
    g_lightDirectionWidget->SetLightDirection( g_directionalLightVector1 );
    g_lightDirectionWidget->SetRadius( 10.0f );

    //set the camera back to where it was 
    g_vecEye = g_constVecEye2;
    g_vecAt = g_constAtVec2;
    g_Camera.SetViewParams( &g_vecEye, &g_vecAt );
}


void setShadingParametersBasedOnRain()
{
    //dry
    float DryKd = 1;
    float DryKsPoint = 0;
    float DryKsDir = 0;
    float DryspecPower = 5;
    //wet
    float WetKd = 0.4;
    float WetKsPoint = 2;
    float WetKsDir = 2;
    float WetspecPower = 100;

    g_KdShaderVariable->SetFloat( DryKd + g_DrawFraction*(WetKd-DryKd) );
    g_KsPointShaderVariable->SetFloat( DryKsPoint + g_DrawFraction*(WetKsPoint-DryKsPoint) ); 
    g_KsDirShaderVariable->SetFloat( DryKsDir + g_DrawFraction*(WetKsDir-DryKsDir) );
    g_SpecPowerShaderVariable->SetFloat( DryspecPower + g_DrawFraction*(WetspecPower-DryspecPower) );
}

