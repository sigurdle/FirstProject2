//----------------------------------------------------------------------------------
// File:   Rain.fx
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

#define PI 3.14159265

Texture2DArray rainTextureArray;
Texture2D singleTexture;
Texture2D backgroundTexture;
Texture2D SceneTextureDiffuse;
Texture2D SceneTextureSpecular;
Texture2D SceneTextureNormal;
Texture2D Ftable;
Texture2D Gtable;
Texture2D G_20table;
Texture3D SplashBumpTexture;
Texture3D SplashDiffuseTexture;

//ChangesEveryFrame

matrix g_mInverseProjection;

matrix g_mWorld;
matrix g_mWorldViewProj;
matrix g_mWorldView;
matrix g_mProjection;
matrix g_mViewProjectionInverse;
float4x4 g_mInvView;
float3 g_eyePos;   //eye in world space
float3 g_lightPos = float3(10,10,0); //the directional light in world space 
float g_de;
float3 g_ViewSpaceLightVec;
float3 g_ViewSpaceLightVec2;
float g_DSVPointLight;
float g_DSVPointLight2;
float g_DSVPointLight3;
float3 g_VecPointLightEye;
float3 g_VecPointLightEye2; 
float3 g_VecPointLightEye3;
bool g_useSpotLight = true;
float g_cosSpotlightAngle = 0.8;
float3 g_SpotLightDir = float3(0,-1,0);
float g_FrameRate;
float g_timeCycle;
float g_splashXDisplace;
float g_splashYDisplace;

//changesOften
float g_ResponseDirLight = 1.0;
float g_ResponsePointLight = 1.0;
float dirLightIntensity = 1.0;
bool renderBg = false;   
bool moveParticles = false;
float3 g_TotalVel = float3(0,-0.25,0);
float4 g_DiffuseColor;
float g_PointLightIntensity = 2.0;
float g_SpriteSize = 1.0;
float3 g_beta = float3(0.04,0.04,0.04);
float g_BgAirLight = 0.0;
float g_Kd = 0.1;
float g_KsPoint = 20;
float g_KsDir = 10;
float g_specPower = 20;


//changesRarely
float g_ScreenWidth = 640.0;
float g_ScreenHeight = 480.0;
float g_ScreenWidthMultiplier =  0.0031299;
float g_ScreenHeightMultiplier = 0.0041754;
float g_heightMin = 0.0;
float g_radiusMin = 1.0;
float g_heightRange = 30.0;
float g_radiusRange = 30.0;
float maxHeight;
float g_Near; 
float g_Far; 

cbuffer cbImmutable
{
    float3 g_positions[4] =
    {
        float3( -1, 1, 0 ),
        float3( 1, 1, 0 ),
        float3( -1, -1, 0 ),
        float3( 1, -1, 0 ),
    };
    float2 g_texcoords[4] = 
    { 
        float2(0,1), 
        float2(1,1),
        float2(0,0),
        float2(1,0),
    };
    
    //normalization factors for the rain textures, one per texture
    float g_rainfactors[370] = 
    {

        0.004535 , 0.014777 , 0.012512 , 0.130630 , 0.013893 , 0.125165 , 0.011809 , 0.244907 , 0.010722 , 0.218252,
        0.011450 , 0.016406 , 0.015855 , 0.055476 , 0.015024 , 0.067772 , 0.021120 , 0.118653 , 0.018705 , 0.142495, 
        0.004249 , 0.017267 , 0.042737 , 0.036384 , 0.043433 , 0.039413 , 0.058746 , 0.038396 , 0.065664 , 0.054761, 
        0.002484 , 0.003707 , 0.004456 , 0.006006 , 0.004805 , 0.006021 , 0.004263 , 0.007299 , 0.004665 , 0.007037, 
        0.002403 , 0.004809 , 0.004978 , 0.005211 , 0.004855 , 0.004936 , 0.006266 , 0.007787 , 0.006973 , 0.007911, 
        0.004843 , 0.007565 , 0.007675 , 0.011109 , 0.007726 , 0.012165 , 0.013179 , 0.021546 , 0.013247 , 0.012964, 
        0.105644 , 0.126661 , 0.128746 , 0.101296 , 0.123779 , 0.106198 , 0.123470 , 0.129170 , 0.116610 , 0.137528, 
        0.302834 , 0.379777 , 0.392745 , 0.339152 , 0.395508 , 0.334227 , 0.374641 , 0.503066 , 0.387906 , 0.519618, 
        0.414521 , 0.521799 , 0.521648 , 0.498219 , 0.511921 , 0.490866 , 0.523137 , 0.713744 , 0.516829 , 0.743649, 
        0.009892 , 0.013868 , 0.034567 , 0.025788 , 0.034729 , 0.036399 , 0.030606 , 0.017303 , 0.051809 , 0.030852, 
        0.018874 , 0.027152 , 0.031625 , 0.023033 , 0.038150 , 0.024483 , 0.029034 , 0.021801 , 0.037730 , 0.016639, 
        0.002868 , 0.004127 , 0.133022 , 0.013847 , 0.123368 , 0.012993 , 0.122183 , 0.015031 , 0.126043 , 0.015916, 
        0.002030 , 0.002807 , 0.065443 , 0.002752 , 0.069440 , 0.002810 , 0.081357 , 0.002721 , 0.076409 , 0.002990, 
        0.002425 , 0.003250 , 0.003180 , 0.011331 , 0.002957 , 0.011551 , 0.003387 , 0.006086 , 0.002928 , 0.005548, 
        0.003664 , 0.004258 , 0.004269 , 0.009404 , 0.003925 , 0.009233 , 0.004224 , 0.009405 , 0.004014 , 0.008435, 
        0.038058 , 0.040362 , 0.035946 , 0.072104 , 0.038315 , 0.078789 , 0.037069 , 0.077795 , 0.042554 , 0.073945, 
        0.124160 , 0.122589 , 0.121798 , 0.201886 , 0.122283 , 0.214549 , 0.118196 , 0.192104 , 0.122268 , 0.209397, 
        0.185212 , 0.181729 , 0.194527 , 0.420721 , 0.191558 , 0.437096 , 0.199995 , 0.373842 , 0.192217 , 0.386263, 
        0.003520 , 0.053502 , 0.060764 , 0.035197 , 0.055078 , 0.036764 , 0.048231 , 0.052671 , 0.050826 , 0.044863, 
        0.002254 , 0.023290 , 0.082858 , 0.043008 , 0.073780 , 0.035838 , 0.080650 , 0.071433 , 0.073493 , 0.026725, 
        0.002181 , 0.002203 , 0.112864 , 0.060140 , 0.115635 , 0.065531 , 0.093277 , 0.094123 , 0.093125 , 0.144290, 
        0.002397 , 0.002369 , 0.043241 , 0.002518 , 0.040455 , 0.002656 , 0.002540 , 0.090915 , 0.002443 , 0.101604, 
        0.002598 , 0.002547 , 0.002748 , 0.002939 , 0.002599 , 0.003395 , 0.002733 , 0.003774 , 0.002659 , 0.004583, 
        0.003277 , 0.003176 , 0.003265 , 0.004301 , 0.003160 , 0.004517 , 0.003833 , 0.008354 , 0.003140 , 0.009214, 
        0.008558 , 0.007646 , 0.007622 , 0.026437 , 0.007633 , 0.021560 , 0.007622 , 0.017570 , 0.007632 , 0.018037, 
        0.031062 , 0.028428 , 0.028428 , 0.108300 , 0.028751 , 0.111013 , 0.028428 , 0.048661 , 0.028699 , 0.061490, 
        0.051063 , 0.047597 , 0.048824 , 0.129541 , 0.045247 , 0.124975 , 0.047804 , 0.128904 , 0.045053 , 0.119087, 
        0.002197 , 0.002552 , 0.002098 , 0.200688 , 0.002073 , 0.102060 , 0.002111 , 0.163116 , 0.002125 , 0.165419, 
        0.002060 , 0.002504 , 0.002105 , 0.166820 , 0.002117 , 0.144274 , 0.005074 , 0.143881 , 0.004875 , 0.205333, 
        0.001852 , 0.002184 , 0.002167 , 0.163804 , 0.002132 , 0.212644 , 0.003431 , 0.244546 , 0.004205 , 0.315848, 
        0.002450 , 0.002360 , 0.002243 , 0.154635 , 0.002246 , 0.148259 , 0.002239 , 0.348694 , 0.002265 , 0.368426, 
        0.002321 , 0.002393 , 0.002376 , 0.074124 , 0.002439 , 0.126918 , 0.002453 , 0.439270 , 0.002416 , 0.489812, 
        0.002484 , 0.002629 , 0.002559 , 0.150246 , 0.002579 , 0.140103 , 0.002548 , 0.493103 , 0.002637 , 0.509481, 
        0.002960 , 0.002952 , 0.002880 , 0.294884 , 0.002758 , 0.332805 , 0.002727 , 0.455842 , 0.002816 , 0.431807, 
        0.003099 , 0.003028 , 0.002927 , 0.387154 , 0.002899 , 0.397946 , 0.002957 , 0.261333 , 0.002909 , 0.148548, 
        0.004887 , 0.004884 , 0.006581 , 0.414647 , 0.003735 , 0.431317 , 0.006426 , 0.148997 , 0.003736 , 0.080715, 
        0.001969 , 0.002159 , 0.002325 , 0.200211 , 0.002288 , 0.202137 , 0.002289 , 0.595331 , 0.002311 , 0.636097 

        };
    
    float4 pointLightColor = float4(1.0,1.0,1.0,1.0);
    float3 g_PointLightPos = float3(  3.7,5.8,3.15);     
    float3 g_PointLightPos2 = float3(-3.7,5.8,3.15);

    float g_fXOffset = 0; 
    float g_fXScale = 0.6366198; //1/(PI/2)
    float g_fYOffset = 0;        
    float g_fYScale = 0.5;
    
    float g_20XOffset = 0; 
    float g_20XScale = 0.6366198; //1/(PI/2) 
    float g_20YOffset = 0;
    float g_20YScale = 0.5;

     

    float g_diffXOffset = 0; 
    float g_diffXScale = 0.5;
    float g_diffYOffset = 0;        
    float g_diffYScale = 0.3183099;  //1/PI   
}

BlendState CorrectBlending
{
    AlphaToCoverageEnable = FALSE;
    BlendEnable[0] = TRUE;
    SrcBlend = SRC_ALPHA;
    DestBlend = INV_SRC_ALPHA;
    BlendOp = ADD;
    SrcBlendAlpha = ONE;
    DestBlendAlpha = ONE;
    BlendOpAlpha = ADD;
    RenderTargetWriteMask[0] = 0x0F;
}; 


BlendState AdditiveBlending
{
    AlphaToCoverageEnable = FALSE;
    BlendEnable[0] = TRUE;
    SrcBlend = 1;
    DestBlend = INV_SRC_ALPHA;
    BlendOp = ADD;
    SrcBlendAlpha = ONE;
    DestBlendAlpha = ONE;
    BlendOpAlpha = ADD;
    RenderTargetWriteMask[0] = 0x0F;
}; 

DepthStencilState EnableDepth
{
        //depth
        DepthEnable = true;
        DepthWriteMask = ALL;
        DepthFunc = Less;
    
        //stencil
        StencilEnable = false;
        StencilReadMask = 0xFF;
        StencilWriteMask = 0x00;
};

BlendState NoBlending
{
    AlphaToCoverageEnable = FALSE;
    BlendEnable[0] = FALSE;
    RenderTargetWriteMask[0] = 0x0F;
};

DepthStencilState DisableDepth
{
        DepthEnable = false;
        DepthWriteMask = ZERO;
        DepthFunc = Less;
    
        //Stencil
        StencilEnable = false;
        StencilReadMask = 0xFF;
        StencilWriteMask = 0x00;
};

DepthStencilState EnableDepthTestingOnly
{
        DepthEnable = true;
        DepthWriteMask = 0x00;
        DepthFunc = Less;
    
        StencilEnable = false;
};

SamplerState samAniso
{
    Filter = ANISOTROPIC;
    AddressU = Wrap;
    AddressV = Wrap;
};

SamplerState samLinear
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;
    AddressV = Wrap;
};

SamplerState samAnisoMirror
{
  Filter = ANISOTROPIC;
  AddressU = Mirror;
  AddressV = Mirror;
};

SamplerState samLinearClamp
{
    Filter = MIN_MAG_LINEAR_MIP_POINT;
    AddressU = Clamp;
    AddressV = Clamp;
};

RasterizerState CullNone
{
    MultiSampleEnable = False;
    CullMode=None;
};

RasterizerState CullBack
{
    MultiSampleEnable = True;
    CullMode=Back;
};

//--------------------------------------------------------------------------------------------
// draw rain
//--------------------------------------------------------------------------------------------

struct VSParticleIn
{   
    float3 pos              : POSITION;         //position of the particle
    float3 seed             : SEED;
    float3 speed            : SPEED;
    float random            : RAND;
    uint   Type             : TYPE;             //particle type
};

struct PSSceneIn
{
    float4 pos : SV_Position;
    float3 lightDir   : LIGHT;
    float3 pointLightDir : LIGHT2;
    float3 eyeVec     : EYE;
    float2 tex : TEXTURE0;
    uint type  : TYPE;
    float random : RAND;
};


VSParticleIn VSPassThroughRain(VSParticleIn input )
{
    return input;
}


bool cullSprite( float3 position, float SpriteSize)
{
    float4 vpos = mul(float4(position,1), g_mWorldView);
    
    
    if( (vpos.z < (g_Near - SpriteSize )) || ( vpos.z > (g_Far + SpriteSize)) ) 
    {
        return true;
    }
    else 
    {
        float4 ppos = mul( vpos, g_mProjection);
        float wext = ppos.w + SpriteSize;
        if( (ppos.x < -wext) || (ppos.x > wext) ||
            (ppos.y < -wext) || (ppos.y > wext) ) {
            return true;
        }
        else 
        {
            return false;
        }
    }
    
    return false;
}

void GenRainSpriteVertices(float3 worldPos, float3 velVec, float3 eyePos, out float3 outPos[4])
{
    float height = g_SpriteSize/2.0;
    float width = height/10.0;

    velVec = normalize(velVec);
    float3 eyeVec = eyePos - worldPos;
    float3 eyeOnVelVecPlane = eyePos - ((dot(eyeVec, velVec)) * velVec);
    float3 projectedEyeVec = eyeOnVelVecPlane - worldPos;
    float3 sideVec = normalize(cross(projectedEyeVec, velVec));
    
    outPos[0] =  worldPos - (sideVec * 0.5*width);
    outPos[1] = outPos[0] + (sideVec * width);
    outPos[2] = outPos[0] + (velVec * height);
    outPos[3] = outPos[2] + (sideVec * width );
}

// GS for rendering rain as point sprites.  Takes a point and turns it into 2 tris.
[maxvertexcount(4)]
void GSRenderRain(point VSParticleIn input[1], inout TriangleStream<PSSceneIn> SpriteStream)
{
    float totalIntensity = g_PointLightIntensity*g_ResponsePointLight + dirLightIntensity*g_ResponseDirLight;
    if(!cullSprite(input[0].pos,2*g_SpriteSize) && totalIntensity > 0)
    {    
        PSSceneIn output = (PSSceneIn)0;
        output.type = input[0].Type;
        output.random = input[0].random;
       
        float3 pos[4];
        GenRainSpriteVertices(input[0].pos.xyz, input[0].speed.xyz/g_FrameRate + g_TotalVel, g_eyePos, pos);
        
        float3 closestPointLight = g_PointLightPos;
        float closestDistance = length(g_PointLightPos - pos[0]);
        if( length(g_PointLightPos2 - pos[0]) < closestDistance )
           closestPointLight = g_PointLightPos2;
        
        output.pos = mul( float4(pos[0],1.0), g_mWorldViewProj );
        output.lightDir = g_lightPos - pos[0];
        output.pointLightDir = closestPointLight - pos[0];
        output.eyeVec = g_eyePos - pos[0];
        output.tex = g_texcoords[0];
        SpriteStream.Append(output);
                
        output.pos = mul( float4(pos[1],1.0), g_mWorldViewProj );
        output.lightDir = g_lightPos - pos[1];
        output.pointLightDir = closestPointLight - pos[1];
        output.eyeVec = g_eyePos - pos[1];
        output.tex = g_texcoords[1];
        SpriteStream.Append(output);
        
        output.pos = mul( float4(pos[2],1.0), g_mWorldViewProj );
        output.lightDir = g_lightPos - pos[2];
        output.pointLightDir = closestPointLight - pos[2];
        output.eyeVec = g_eyePos - pos[2];
        output.tex = g_texcoords[2];
        SpriteStream.Append(output);
                
        output.pos = mul( float4(pos[3],1.0), g_mWorldViewProj );
        output.lightDir = g_lightPos - pos[3];
        output.pointLightDir = closestPointLight - pos[3];
        output.eyeVec = g_eyePos - pos[3];
        output.tex = g_texcoords[3];
        SpriteStream.Append(output);
        
        SpriteStream.RestartStrip();
    }   
}


void rainResponse(PSSceneIn input, float3 lightVector, float lightIntensity, float3 lightColor, float3 eyeVector, bool fallOffFactor, inout float4 rainResponseVal)
{
    
    float opacity = 0.0;

    float fallOff;
    if(fallOffFactor)
    {  
        float distToLight = length(lightVector);
        fallOff = 1.0/( distToLight * distToLight);
        fallOff = saturate(fallOff);   
    }
    else
    {  fallOff = 1;
    }

    if(fallOff > 0.01 && lightIntensity > 0.01 )
    {
        float3 dropDir = g_TotalVel;

        #define MAX_VIDX 4
        #define MAX_HIDX 8
        // Inputs: lightVector, eyeVector, dropDir
        float3 L = normalize(lightVector);
        float3 E = normalize(eyeVector);
        float3 N = normalize(dropDir);
        
        bool is_EpLp_angle_ccw = true;
        float hangle = 0;
        float vangle = abs( (acos(dot(L,N)) * 180/PI) - 90 ); // 0 to 90
        
        {
            float3 Lp = normalize( L - dot(L,N)*N );
            float3 Ep = normalize( E - dot(E,N)*N );
            hangle = acos( dot(Ep,Lp) ) * 180/PI;  // 0 to 180
            hangle = (hangle-10)/20.0;           // -0.5 to 8.5
            is_EpLp_angle_ccw = dot( N, cross(Ep,Lp)) > 0;
        }
        
        if(vangle>=88.0)
        {
            hangle = 0;
            is_EpLp_angle_ccw = true;
        }
                
        vangle = (vangle-10.0)/20.0; // -0.5 to 4.5
        
        // Outputs:
        // verticalLightIndex[1|2] - two indices in the vertical direction
        // t - fraction at which the vangle is between these two indices (for lerp)
        int verticalLightIndex1 = floor(vangle); // 0 to 5
        int verticalLightIndex2 = min(MAX_VIDX, (verticalLightIndex1 + 1) );
        verticalLightIndex1 = max(0, verticalLightIndex1);
        float t = frac(vangle);

        // textureCoordsH[1|2] used in case we need to flip the texture horizontally
        float textureCoordsH1 = input.tex.x;
        float textureCoordsH2 = input.tex.x;
        
        // horizontalLightIndex[1|2] - two indices in the horizontal direction
        // s - fraction at which the hangle is between these two indices (for lerp)
        int horizontalLightIndex1 = 0;
        int horizontalLightIndex2 = 0;
        float s = 0;
        
        s = frac(hangle);
        horizontalLightIndex1 = floor(hangle); // 0 to 8
        horizontalLightIndex2 = horizontalLightIndex1+1;
        if( horizontalLightIndex1 < 0 )
        {
            horizontalLightIndex1 = 0;
            horizontalLightIndex2 = 0;
        }
                   
        if( is_EpLp_angle_ccw )
        {
            if( horizontalLightIndex2 > MAX_HIDX ) 
            {
                horizontalLightIndex2 = MAX_HIDX;
                textureCoordsH2 = 1.0 - textureCoordsH2;
            }
        }
        else
        {
            textureCoordsH1 = 1.0 - textureCoordsH1;
            if( horizontalLightIndex2 > MAX_HIDX ) 
            {
                horizontalLightIndex2 = MAX_HIDX;
            } else 
            {
                textureCoordsH2 = 1.0 - textureCoordsH2;
            }
        }
                
        if( verticalLightIndex1 >= MAX_VIDX )
        {
            textureCoordsH2 = input.tex.x;
            horizontalLightIndex1 = 0;
            horizontalLightIndex2 = 0;
            s = 0;
        }
        
        // Generate the final texture coordinates for each sample
        uint type = input.type;
        uint2 texIndicesV1 = uint2(verticalLightIndex1*90 + horizontalLightIndex1*10 + type,
                                     verticalLightIndex1*90 + horizontalLightIndex2*10 + type);
        float3 tex1 = float3(textureCoordsH1, input.tex.y, texIndicesV1.x);
        float3 tex2 = float3(textureCoordsH2, input.tex.y, texIndicesV1.y);
        if( (verticalLightIndex1<4) && (verticalLightIndex2>=4) ) 
        {
            s = 0;
            horizontalLightIndex1 = 0;
            horizontalLightIndex2 = 0;
            textureCoordsH1 = input.tex.x;
            textureCoordsH2 = input.tex.x;
        }
        
        uint2 texIndicesV2 = uint2(verticalLightIndex2*90 + horizontalLightIndex1*10 + type,
                                     verticalLightIndex2*90 + horizontalLightIndex2*10 + type);
        float3 tex3 = float3(textureCoordsH1, input.tex.y, texIndicesV2.x);        
        float3 tex4 = float3(textureCoordsH2, input.tex.y, texIndicesV2.y);

        // Sample opacity from the textures
        float col1 = rainTextureArray.Sample( samAniso, tex1) * g_rainfactors[texIndicesV1.x];
        float col2 = rainTextureArray.Sample( samAniso, tex2) * g_rainfactors[texIndicesV1.y];
        float col3 = rainTextureArray.Sample( samAniso, tex3) * g_rainfactors[texIndicesV2.x];
        float col4 = rainTextureArray.Sample( samAniso, tex4) * g_rainfactors[texIndicesV2.y];

        // Compute interpolated opacity using the s and t factors
        float hOpacity1 = lerp(col1,col2,s);
        float hOpacity2 = lerp(col3,col4,s);
        opacity = lerp(hOpacity1,hOpacity2,t);
        opacity = pow(opacity,0.7); // inverse gamma correction (expand dynamic range)
        opacity = 4*lightIntensity * opacity * fallOff;
    }
         
   rainResponseVal = float4(lightColor,opacity);

}

float4 PSRenderRain(PSSceneIn input) : SV_Target
{     
      //return float4(1,0,0,0.1);
       
      //directional lighting---------------------------------------------------------------------------------
      float4 directionalLight;
      rainResponse(input, input.lightDir, 2.0*dirLightIntensity*g_ResponseDirLight*input.random, float3(1.0,1.0,1.0), input.eyeVec, false, directionalLight);

      //point lighting---------------------------------------------------------------------------------------
      float4 pointLight = float4(0,0,0,0);
      
      float3 L = normalize( input.pointLightDir );
      float angleToSpotLight = dot(-L, g_SpotLightDir);
      
      if( !g_useSpotLight || g_useSpotLight && angleToSpotLight > g_cosSpotlightAngle )
          rainResponse(input, input.pointLightDir, 2*g_PointLightIntensity*g_ResponsePointLight*input.random, pointLightColor.xyz, input.eyeVec, true,pointLight);
      
      float totalOpacity = pointLight.a+directionalLight.a;
      return float4( float3(pointLight.rgb*pointLight.a/totalOpacity + directionalLight.rgb*directionalLight.a/totalOpacity), totalOpacity);
}


technique10 RenderParticles
{
    pass p0
    {
        SetVertexShader( CompileShader(   vs_4_0, VSPassThroughRain() ) );
        SetGeometryShader( CompileShader( gs_4_0, GSRenderRain() ) );
        SetPixelShader( CompileShader(    ps_4_0, PSRenderRain() ) );
        
        SetBlendState( CorrectBlending, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xFFFFFFFF );
        SetDepthStencilState( EnableDepthTestingOnly, 0 );
        SetRasterizerState( CullNone );
    }  
}

//--------------------------------------------------------------------------------------------
// cheap pixel shader for rendering rain
//--------------------------------------------------------------------------------------------


struct PSRainIn
{
    float4 pos : SV_Position;
    float2 tex : TEXTURE0;
};

// GS for rendering rain as point sprites.  Takes a point and turns it into 2 tris.
[maxvertexcount(4)]
void GSRenderRainCheap(point VSParticleIn input[1], inout TriangleStream<PSRainIn> SpriteStream)
{
   
    PSRainIn output = (PSRainIn)0;
    
    float3 pos[4];
    GenRainSpriteVertices(input[0].pos, input[0].speed.xyz/g_FrameRate + g_TotalVel, g_eyePos, pos);
        
    output.pos = mul( float4(pos[0],1.0), g_mWorldViewProj );
    output.tex = g_texcoords[0];
    SpriteStream.Append(output);
        
    output.pos = mul( float4(pos[1],1.0), g_mWorldViewProj );
    output.tex = g_texcoords[1];
    SpriteStream.Append(output);
        
    output.pos = mul( float4(pos[2],1.0), g_mWorldViewProj );
    output.tex = g_texcoords[2];
    SpriteStream.Append(output);
                
    output.pos = mul( float4(pos[3],1.0), g_mWorldViewProj );
    output.tex = g_texcoords[3];
    SpriteStream.Append(output);
        
    SpriteStream.RestartStrip();
       
}

float4 PSRenderRainCheap(PSRainIn input) : SV_Target
{     
    return float4(1,1,1,dirLightIntensity*g_ResponseDirLight*0.1);
}


technique10 RenderParticlesCheap
{
    pass p0
    {
        SetVertexShader( CompileShader(   vs_4_0, VSPassThroughRain() ) );
        SetGeometryShader( CompileShader( gs_4_0, GSRenderRainCheap() ) );
        SetPixelShader( CompileShader(    ps_4_0, PSRenderRainCheap() ) );
        
        SetBlendState( CorrectBlending, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xFFFFFFFF );
        SetDepthStencilState( EnableDepthTestingOnly, 0 );
        SetRasterizerState( CullNone );
    }  
}


//--------------------------------------------------------------------------------------------
// advance rain
//--------------------------------------------------------------------------------------------

VSParticleIn VSAdvanceRain(VSParticleIn input)
{
     if(moveParticles)
     {
         //move forward
         input.pos.xyz += input.speed.xyz/g_FrameRate + g_TotalVel.xyz;

         //if the particle is outside the bounds, move it to random position near the eye         
         if(input.pos.y <=  g_eyePos.y-g_heightRange )
         {
            float x = input.seed.x + g_eyePos.x;
            float z = input.seed.z + g_eyePos.z;
            float y = input.seed.y + g_eyePos.y;
            input.pos = float3(x,y,z);
         }
    }

    return input;
    
}

GeometryShader gsStreamOut = ConstructGSWithSO( CompileShader( vs_4_0, VSAdvanceRain() ), "POSITION.xyz; SEED.xyz; SPEED.xyz; RAND.x; TYPE.x" );  
technique10 AdvanceParticles
{
    pass p0
    {
        SetVertexShader( CompileShader( vs_4_0, VSAdvanceRain() ) );
        SetGeometryShader( gsStreamOut );
        SetPixelShader( NULL );
        
        SetDepthStencilState( DisableDepth, 0 );
    }  
}


//---------------------------------------------------------------------------------------
//auxiliary functions for calculating the Fog
//---------------------------------------------------------------------------------------

float3 calculateAirLightPointLight(float Dvp,float Dsv,float3 S,float3 V)
{
    float gamma = acos(dot(S, V));
    gamma = clamp(gamma,0.01,PI-0.01);
    float sinGamma = sin(gamma);
    float cosGamma = cos(gamma);
    float u = g_beta.x * Dsv * sinGamma;
    float v1 = 0.25*PI+0.5*atan((Dvp-Dsv*cosGamma)/(Dsv*sinGamma)); 
    float v2 = 0.5*gamma;
            
    float lightIntensity = g_PointLightIntensity * 100;        
            
    float f1= Ftable.SampleLevel(samLinearClamp, float2((v1-g_fXOffset)*g_fXScale, (u-g_fYOffset)*g_fYScale), 0);
    float f2= Ftable.SampleLevel(samLinearClamp, float2((v2-g_fXOffset)*g_fXScale, (u-g_fYOffset)*g_fYScale), 0);
    float airlight = (g_beta.x*lightIntensity*exp(-g_beta.x*Dsv*cosGamma))/(2*PI*Dsv*sinGamma)*(f1-f2);
    
    return airlight.xxx;
}

float3 calculateDiffusePointLight(float Kd,float Dvp,float Dsv,float3 pointLightDir,float3 N,float3 V)
{

    float Dsp = length(pointLightDir);
    float3 L = pointLightDir/Dsp;
    float thetas = acos(dot(N, L));
    float lightIntensity = g_PointLightIntensity * 100;
    
    //spotlight
    float angleToSpotLight = dot(-L, g_SpotLightDir);
    if(g_useSpotLight)
    {    if(angleToSpotLight > g_cosSpotlightAngle)
             lightIntensity *= abs((angleToSpotLight - g_cosSpotlightAngle)/(1-g_cosSpotlightAngle));
         else
             lightIntensity = 0;         
    }   
    
    //diffuse contribution
    float t1 = exp(-g_beta.x*Dsp)*max(cos(thetas),0)/Dsp;
    float4 t2 = g_beta.x*Gtable.SampleLevel(samLinearClamp, float2((g_beta.x*Dsp-g_diffXOffset)*g_diffXScale, (thetas-g_diffYOffset)*g_diffYScale),0)/(2*PI);
    float rCol = (t1+t2.x)*exp(-g_beta.x*Dvp)*Kd*lightIntensity/Dsp;
    float diffusePointLight = float3(rCol,rCol,rCol);  
    return diffusePointLight.xxx;
}



float3 Specular(float lightIntensity, float Ks, float Dsp, float Dvp, float specPow, float3 L, float3 VReflect)
{
    lightIntensity = lightIntensity * 100;
    float LDotVReflect = dot(L,VReflect);
    float thetas = acos(LDotVReflect);

    float t1 = exp(-g_beta*Dsp)*pow(max(LDotVReflect,0),specPow)/Dsp;
    float4 t2 = g_beta.x*G_20table.SampleLevel(samLinearClamp, float2((g_beta.x*Dsp-g_20XOffset)*g_20XScale, (thetas-g_20YOffset)*g_20YScale),0)/(2*PI);
    float specular = (t1+t2.x)*exp(-g_beta.x*Dvp)*Ks*lightIntensity/Dsp;
    return specular.xxx;
}


float3 phaseFunctionSchlick(float cosTheta)
{
   float k = -0.2; 
   float p = (1-k*k)/(pow(1+k*cosTheta,2) );
   return float3(p,p,p);
}


//---------------------------------------------------------------------------------------
// rendering the Scene
//---------------------------------------------------------------------------------------

struct VS_INPUT_SCENE
{
    float3 Position          : POSITION;    
    float3 Normal            : NORMAL;  
    float2 Texture           : TEXCOORD;
    float3 Tan               : TANGENT;

};
struct VS_OUTPUT_SCENE
{
    float4 Position            : SV_POSITION; 
    float3 Normal              : NORMAL;
    float3 Tan                 : TANGENT;
    float4 worldPos            : WPOSITION;
    float2 Texture             : TEXTURE0;   
};

//vertex shader for the scene
VS_OUTPUT_SCENE VSScene( VS_INPUT_SCENE input )
{
    VS_OUTPUT_SCENE output = (VS_OUTPUT_SCENE)0;
        
    output.Position = mul( float4(input.Position,1), g_mWorldViewProj );
    output.Normal   = mul( input.Normal, g_mWorld );
    output.Tan      = normalize( mul( input.Tan, (float3x3)g_mWorld ) );
    output.worldPos = mul( float4(input.Position,1), g_mWorld );  
    float3 worldPos = mul( input.Position, g_mWorld );
    output.Texture  = input.Texture;    
    
    return output;
    
}

float4 visualizeVector(float3 vec)
{
  return float4((normalize(vec)+1)*0.5,1);
}

//pixel shader for the scene
float4 PSScene(VS_OUTPUT_SCENE In) : SV_Target
{
    float4 outputColor;
        
    float4 sceneColor = SceneTextureDiffuse.Sample( samLinear, In.Texture );
    float3 viewVec = In.worldPos - g_eyePos;
    float Dvp = length(viewVec);
    float3 V =  viewVec/Dvp; 
    float3 exDir = float3( exp(-g_beta.x*Dvp),  exp(-g_beta.y*Dvp),  exp(-g_beta.z*Dvp)  );
    float4 sceneSpecular = SceneTextureSpecular.Sample( samLinear, In.Texture );
   
    //perturb the normal based on the surface and the rain-----------------------------
    
    float3 Tan = normalize(In.Tan);
    float3 InNormal = normalize(In.Normal);
    float wetSurf = saturate(g_KsDir/2.0*saturate(InNormal.y));

    float4 normalMap = SceneTextureNormal.Sample( samAniso, In.Texture );
    float3 norm = float3(normalMap.g*2-1, normalMap.a*2-1,0);
    norm.z = sqrt( 1 - norm.x*norm.x + norm.y*norm.y );
    float3 binorm = normalize( cross( InNormal, Tan ) );
    if( dot( normalize(In.worldPos) ,binorm) < 0 )
        binorm = -binorm;
    float3x3 BTNMatrix = float3x3( binorm, Tan, InNormal );
    float3 N = normalize(mul( norm, BTNMatrix ));
     
     
    //add the normal map from the rain bumps
    //based on the direction of the surface and the amount of rainyness   
    float4 BumpMapVal = SplashBumpTexture.Sample(samAnisoMirror, 
                       float3(In.worldPos.x/2.0 + g_splashXDisplace, In.worldPos.z/2.0 + g_splashYDisplace, g_timeCycle)) - 0.5;
    N += wetSurf * 2 * (BumpMapVal.x * Tan + BumpMapVal.y * binorm);
    N = normalize(N);
    float3 splashDiffuse = wetSurf * SplashDiffuseTexture.Sample(samAnisoMirror, float3(In.worldPos.xz, g_timeCycle));
        
    //reflection of the scene-----------------------------------------------------------
    float3 reflVect = reflect(V, N);
        
    //directional light-----------------------------------------------------------------
    float3 lightDir = g_lightPos - In.worldPos;
    float3 lightDirNorm = normalize(lightDir);
    float3 SDir = normalize( g_lightPos - g_eyePos);
    float cosGammaDir = dot(SDir, V);
    float dirLighting = g_Kd*dirLightIntensity*saturate( dot( N,lightDirNorm ) );
    //diffuse
    float3 diffuseDirLight = dirLighting*exDir;        
    //airlight
    float3 dirAirLight = phaseFunctionSchlick(cosGammaDir)* dirLightIntensity*float3(1-exDir.x,1-exDir.y,1-exDir.z);
    //specular
    float3 specularDirLight = saturate( pow(  dot(lightDirNorm,reflVect),g_specPower)) * dirLightIntensity * g_KsDir * exDir; 

    //point light 1---------------------------------------------------------------------
    //diffuse surface radiance and airlight due to point light
    float3 pointLightDir = g_PointLightPos - In.worldPos;
    //diffuse
    float3 diffusePointLight1 = calculateDiffusePointLight(0.1,Dvp,g_DSVPointLight,pointLightDir,N,V);
    //airlight
    float3 airlight1 = calculateAirLightPointLight(Dvp,g_DSVPointLight,g_VecPointLightEye,V);
    //specular
    float3 specularPointLight = Specular(g_PointLightIntensity, g_KsPoint, length(pointLightDir), Dvp, g_specPower, normalize(pointLightDir), reflVect);

    //point light 2---------------------------------------------------------------------
    //diffuse surface radiance
    float3 diffusePointLight2 = float3(0,0,0);
    float3 pointLightDir2 = g_PointLightPos2 - In.worldPos;
    //diffuse
    diffusePointLight2 = calculateDiffusePointLight(0.1,Dvp,g_DSVPointLight2,pointLightDir2,N,V);
    //airlight
    float3 airlight2 = calculateAirLightPointLight(Dvp,g_DSVPointLight2,g_VecPointLightEye2,V);
    //specular
    float3 specularPointLight2 = Specular(g_PointLightIntensity, g_KsPoint, length(pointLightDir2), Dvp, g_specPower, normalize(pointLightDir2), reflVect);
    

    float3 airlightColor = airlight1 + airlight2 + dirAirLight;

    outputColor = float4( airlightColor.xyz + 
                          sceneColor.xyz*(diffusePointLight1.xyz + diffusePointLight2.xyz + diffuseDirLight.xyz) +
                          (splashDiffuse + sceneSpecular.xyz)*(specularDirLight + specularPointLight + specularPointLight2) ,1); 
   
     //if this is a lamp make it emissive 
    if(sceneColor.x > 0.9 && sceneColor.y> 0.9)
        outputColor = float4(1,1,1,1)*g_PointLightIntensity*20; 
   
    return outputColor; 
}


technique10 RenderScene
{
    pass P0
    {
        SetVertexShader(CompileShader( vs_4_0, VSScene( ) )); 
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PSScene() ) );
        
        SetBlendState( NoBlending, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xFFFFFFFF );
        SetDepthStencilState( EnableDepth, 0 );
        SetRasterizerState(CullBack);
    }

}

//---------------------------------------------------------------------------------------
// rendering the sdirectional light arrow
//---------------------------------------------------------------------------------------

struct VS_INPUT_ARROW
{ 
    float3 Position          : POSITION;
    float3 Normal            : NORMAL;
    float2 Texture           : TEXCOORD;

};

struct VS_OUTPUT_ARROW
{
    float4 Position   : SV_POSITION;  
};

VS_OUTPUT_ARROW VSArrow( VS_INPUT_ARROW input )
{
    VS_OUTPUT_ARROW output = (VS_OUTPUT_ARROW)0;
    output.Position =  mul( float4(input.Position, 1), g_mWorldViewProj );
    return output;
}

float4 PSArrow(VS_OUTPUT_ARROW In) : SV_Target
{  
    return float4(1,1,1,1);
}


technique10 RenderArrow
{
    pass P0
    {
        SetVertexShader(    CompileShader( vs_4_0,VSArrow()      ) ); 
        SetGeometryShader(  NULL                                   );
        SetPixelShader(     CompileShader( ps_4_0,PSArrow()      ) );
        
        SetBlendState( NoBlending, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xFFFFFFFF );
        SetDepthStencilState( EnableDepth, 1 );
    }
}


//---------------------------------------------------------------------------------------
// rendering the sky box
//---------------------------------------------------------------------------------------



struct VS_INPUT_SKY
{
    float2 Pos : position;
};

struct VS_OUTPUT_SKY
{
    float4 HPos : SV_POSITION;
    float3 worldPos : POSITION;
};

VS_OUTPUT_SKY VSSky( VS_INPUT_SKY Input )
{
    VS_OUTPUT_SKY Output;
    
    Output.HPos =  float4(Input.Pos.xy, 1.0, 1.0);
    float4 unprojectedPos = mul( float4( Input.Pos.xy, 0, 1 ), g_mInverseProjection );
    unprojectedPos.xy *= g_Near;
    unprojectedPos.z = g_Near;
    unprojectedPos.w = 1;
    Output.worldPos = mul(unprojectedPos, g_mInvView).xyz;
    
    return Output;
}


//pixel shader for the scene
float4 PSSky(VS_OUTPUT_SKY In) : SV_Target
{
  
    float4 outputColor;    
    float4 sceneColor =  float4(0,0,0,0);

    float3 viewVec = In.worldPos - g_eyePos ;
    float Dvp = 50; 
    float3 V =  normalize(viewVec);
    float3 exDir = float3( exp(-g_beta.x*Dvp),  exp(-g_beta.y*Dvp),  exp(-g_beta.z*Dvp)  );
        
    //directional light
    float3 SDir = normalize( g_eyePos - g_lightPos);
    float cosGammaDir = dot(SDir, -V);
    float3 diffuseDirLight = dirLightIntensity*exDir;
    float3 dirAirLight = phaseFunctionSchlick(cosGammaDir)*  
                         dirLightIntensity*float3(1-exDir.x,1-exDir.y,1-exDir.z);

    // air light
    float3 viewRay = normalize(float3(In.HPos.x - g_ScreenWidth/2.0, g_ScreenHeight/2.0 - In.HPos.y ,g_de));    
    float3 airlight = calculateAirLightPointLight(Dvp,g_DSVPointLight,g_ViewSpaceLightVec,viewRay);
    float3 airlight2 = calculateAirLightPointLight(Dvp,g_DSVPointLight2,g_ViewSpaceLightVec2,viewRay);
           
    float3 airlightColor = airlight + airlight2 + dirAirLight;
    outputColor = float4( airlightColor.xyz + sceneColor.xyz*diffuseDirLight.xyz, 1); 
    
    return outputColor;
    
}


technique10 RenderSky
{
    pass p0
    {
        SetVertexShader( CompileShader( vs_4_0, VSSky() ) );
        SetGeometryShader( NULL );
        SetPixelShader(  CompileShader( ps_4_0, PSSky() ) );
        
        SetBlendState( NoBlending, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xFFFFFFFF );
        SetDepthStencilState( DisableDepth, 0 );
        SetRasterizerState(CullNone);
    }  
}

