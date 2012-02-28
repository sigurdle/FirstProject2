#include "stdafx.h"
#include "LMPEG4.h"
/*
#include "BIFSDec.h"

#include "MP4File.h"
#include "MP4Track.h"
*/

//#include "LScriptEngine.h"

namespace System
{
namespace Mpeg4
{

int GetNBits(int range);


System::StringW* ReadString(System::IO::CBitStream32* pBitStream);

enum
{
Anchor,// 0000001 2 DEF bits 3 IN bits 2 OUT bits 0 DYN bits
AnimationStream,// 0000010 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
Appearance,// 0000011 2 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
AudioBuffer,// 0000100 3 DEF bits 3 IN bits 4 OUT bits 0 DYN bits
AudioClip,// 0000101 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
AudioDelay,// 0000110 2 DEF bits 2 IN bits 1 OUT bits 0 DYN bits
AudioFX,// 0000111 3 DEF bits 3 IN bits 2 OUT bits 0 DYN bits
AudioMix,// 0001000 3 DEF bits 3 IN bits 2 OUT bits 0 DYN bits
AudioSource,// 0001001 3 DEF bits 3 IN bits 3 OUT bits 1 DYN bits
AudioSwitch,// 0001010 2 DEF bits 2 IN bits 1 OUT bits 0 DYN bits
Background,// 0001011 4 DEF bits 4 IN bits 4 OUT bits 2 DYN bits
Background2D,// 0001100 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
Billboard,// 0001101 1 DEF bits 2 IN bits 1 OUT bits 0 DYN bits
Bitmap,// 0001110 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
Box,// 0001111 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
Circle,// 0010000 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
Collision,// 0010001 2 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
Color,// 0010010 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
ColorInterpolator,// 0010011 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
CompositeTexture2D,// 0010100 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
CompositeTexture3D,// 0010101 3 DEF bits 4 IN bits 3 OUT bits 0 DYN bits
Conditional,// 0010110 0 DEF bits 2 IN bits 1 OUT bits 0 DYN bits
Cone,// 0010111 2 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
Coordinate,// 0011000 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
Coordinate2D,// 0011001 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
CoordinateInterpolator,// 0011010 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
CoordinateInterpolator2D,// 0011011 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
Curve2D,// 0011100 2 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
Cylinder,// 0011101 3 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
CylinderSensor,// 0011110 3 DEF bits 3 IN bits 4 OUT bits 0 DYN bits
DirectionalLight,// 0011111 3 DEF bits 3 IN bits 3 OUT bits 2 DYN bits
DiscSensor,// 0100000 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
ElevationGrid,// 0100001 4 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
Expression,// 0100010 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
Extrusion,// 0100011 4 DEF bits 2 IN bits 0 OUT bits 0 DYN bits
Face,// 0100100 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
FaceDefMesh,// 0100101 2 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
FaceDefTables,// 0100110 2 DEF bits 1 IN bits 1 OUT bits 0 DYN bits
FaceDefTransform,// 0100111 3 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
FAP,// 0101000 7 DEF bits 7 IN bits 7 OUT bits 0 DYN bits
FDP,// 0101001 3 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
FIT,// 0101010 4 DEF bits 4 IN bits 4 OUT bits 0 DYN bits
Fog,// 0101011 2 DEF bits 2 IN bits 2 OUT bits 1 DYN bits
FontStyle,// 0101100 4 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
Form,// 0101101 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
Group,// 0101110 0 DEF bits 2 IN bits 0 OUT bits 0 DYN bits
ImageTexture,// 0101111 2 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
IndexedFaceSet,// 0110000 4 DEF bits 3 IN bits 2 OUT bits 0 DYN bits
IndexedFaceSet2D,// 0110001 3 DEF bits 3 IN bits 2 OUT bits 0 DYN bits
IndexedLineSet,// 0110010 3 DEF bits 2 IN bits 1 OUT bits 0 DYN bits
IndexedLineSet2D,// 0110011 3 DEF bits 2 IN bits 1 OUT bits 0 DYN bits
Inline,// 0110100 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
LOD,// 0110101 2 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
Layer2D,// 0110110 2 DEF bits 3 IN bits 2 OUT bits 0 DYN bits
Layer3D,// 0110111 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
Layout,// 0111000 4 DEF bits 4 IN bits 4 OUT bits 2 DYN bits
LineProperties,// 0111001 2 DEF bits 2 IN bits 2 OUT bits 1 DYN bits
ListeningPoint,// 0111010 2 DEF bits 2 IN bits 3 OUT bits 1 DYN bits
Material,// 0111011 3 DEF bits 3 IN bits 3 OUT bits 3 DYN bits
Material2D,// 0111100 2 DEF bits 2 IN bits 2 OUT bits 1 DYN bits
MovieTexture,// 0111101 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
NavigationInfo,// 0111110 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
Normal,// 0111111 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
NormalInterpolator,// 1000000 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
OrderedGroup,// 1000001 1 DEF bits 2 IN bits 1 OUT bits 0 DYN bits
OrientationInterpolator,// 1000010 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
PixelTexture,// 1000011 2 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
PlaneSensor,// 1000100 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
PlaneSensor2D,// 1000101 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
PointLight,// 1000110 3 DEF bits 3 IN bits 3 OUT bits 3 DYN bits
PointSet,// 1000111 1 DEF bits 1 IN bits 1 OUT bits 0 DYN bits
PointSet2D,// 1001000 1 DEF bits 1 IN bits 1 OUT bits 0 DYN bits
PositionInterpolator,// 1001001 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
PositionInterpolator2D,// 1001010 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
ProximitySensor2D,// 1001011 2 DEF bits 2 IN bits 3 OUT bits 0 DYN bits
ProximitySensor,// 1001100 2 DEF bits 2 IN bits 3 OUT bits 0 DYN bits
QuantizationParameter,// 1001101 6 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
bifsRectangle,// 1001110 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
ScalarInterpolator,// 1001111 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
Script,// 1010000 2 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
Shape,// 1010001 1 DEF bits 1 IN bits 1 OUT bits 0 DYN bits
Sound,// 1010010 4 DEF bits 4 IN bits 4 OUT bits 3 DYN bits
Sound2D,// 1010011 2 DEF bits 2 IN bits 2 OUT bits 1 DYN bits
Sphere,// 1010100 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
SphereSensor,// 1010101 2 DEF bits 2 IN bits 3 OUT bits 0 DYN bits
SpotLight,// 1010110 4 DEF bits 4 IN bits 4 OUT bits 4 DYN bits
Switch,// 1010111 1 DEF bits 1 IN bits 1 OUT bits 0 DYN bits
TermCap,// 1011000 0 DEF bits 1 IN bits 1 OUT bits 0 DYN bits
Text,// 1011001 2 DEF bits 2 IN bits 2 OUT bits 1 DYN bits
TextureCoordinate,// 1011010 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
TextureTransform,// 1011011 2 DEF bits 2 IN bits 2 OUT bits 2 DYN bits
TimeSensor,// 1011100 3 DEF bits 3 IN bits 4 OUT bits 0 DYN bits
TouchSensor,// 1011101 0 DEF bits 0 IN bits 3 OUT bits 0 DYN bits
Transform,// 1011110 3 DEF bits 3 IN bits 3 OUT bits 3 DYN bits
Transform2D,// 1011111 3 DEF bits 3 IN bits 3 OUT bits 3 DYN bits
Valuator,// 1100000 4 DEF bits 5 IN bits 5 OUT bits 0 DYN bits
Viewpoint,// 1100001 3 DEF bits 3 IN bits 3 OUT bits 2 DYN bits
VisibilitySensor,// 1100010 2 DEF bits 2 IN bits 3 OUT bits 1 DYN bits
Viseme,// 1100011 2 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
WorldInfo
};

/*
StringW* WSTR2(const WCHAR* cstr)
{
	StringW* str = new StringW(cstr);
	AddPersistentLiveRoot((Object**)&str);
	return str;
}
*/

ImmutableString<WCHAR> material_str(L"material");
ImmutableString<WCHAR> texture_str(L"texture");
ImmutableString<WCHAR> textureTransform_str(L"textureTransform");
ImmutableString<WCHAR> addChildren_str(L"addChildren");
ImmutableString<WCHAR> removeChildren_str(L"removeChildren");
ImmutableString<WCHAR> children_str(L"children");
ImmutableString<WCHAR> url_str(L"url");
ImmutableString<WCHAR> pitch_str(L"pitch");
ImmutableString<WCHAR> speed_str(L"speed");
ImmutableString<WCHAR> startTime_str(L"startTime");
ImmutableString<WCHAR> stopTime_str(L"stopTime");
ImmutableString<WCHAR> numChan_str(L"numChan");
ImmutableString<WCHAR> phaseGroup_str(L"phaseGroup");
ImmutableString<WCHAR> set_bind_str(L"set_bind");
ImmutableString<WCHAR> backColor_str(L"backColor");
ImmutableString<WCHAR> isBound_str(L"isBound");
ImmutableString<WCHAR> scale_str(L"scale");
ImmutableString<WCHAR> radius_str(L"radius");
ImmutableString<WCHAR> activate_str(L"activate");
ImmutableString<WCHAR> reverseActivate_str(L"reverseActivate");
ImmutableString<WCHAR> buffer_str(L"buffer");
ImmutableString<WCHAR> isActive_str(L"isActive");
ImmutableString<WCHAR> point_str(L"point");

ImmutableString<WCHAR> set_colorIndex_str(L"set_colorIndex");
ImmutableString<WCHAR> set_coordIndex_str(L"set_coordIndex");
ImmutableString<WCHAR> set_texCoordIndex_str(L"set_texCoordIndex");
ImmutableString<WCHAR> color_str( L"color");
ImmutableString<WCHAR> coord_str(L"coord");
ImmutableString<WCHAR> texCoord_str(L"texCoord");
ImmutableString<WCHAR> colorIndex_str(L"colorIndex");
ImmutableString<WCHAR> colorPerVertex_str(L"colorPerVertex");
ImmutableString<WCHAR> convex_str(L"convex");
ImmutableString<WCHAR> coordIndex_str(L"coordIndex");
ImmutableString<WCHAR> texCoordIndex_str(L"texCoordIndex");

ImmutableString<WCHAR> lineColor_str(L"lineColor");
ImmutableString<WCHAR> lineStyle_str(L"lineStyle");
ImmutableString<WCHAR> width_str(L"width");

ImmutableString<WCHAR> emissiveColor_str(L"emissiveColor");
ImmutableString<WCHAR> filled_str(L"filled");
ImmutableString<WCHAR> lineProps_str(L"lineProps");
ImmutableString<WCHAR> transparency_str(L"transparency");

ImmutableString<WCHAR> order_str(L"order");

ImmutableString<WCHAR> isLocal_str(L"isLocal");
ImmutableString<WCHAR> position3DQuant_str(L"position3DQuant");
ImmutableString<WCHAR> position3DMin_str(L"position3DMin");
ImmutableString<WCHAR> position3DMax_str(L"position3DMax");
ImmutableString<WCHAR> position3DNbBits_str(L"position3DNbBits");
ImmutableString<WCHAR> position2DQuant_str(L"position2DQuant");
ImmutableString<WCHAR> position2DMin_str(L"position2DMin");
ImmutableString<WCHAR> position2DMax_str(L"position2DMax");
ImmutableString<WCHAR> position2DNbBits_str(L"position2DNbBits");
ImmutableString<WCHAR> drawOrderQuant_str(L"drawOrderQuant");
ImmutableString<WCHAR> drawOrderMin_str(L"drawOrderMin");
ImmutableString<WCHAR> drawOrderMax_str(L"drawOrderMax");
ImmutableString<WCHAR> drawOrderNbBits_str(L"drawOrderNbBits");
ImmutableString<WCHAR> colorQuant_str(L"colorQuant");
ImmutableString<WCHAR> colorMin_str(L"colorMin");
ImmutableString<WCHAR> colorMax_str(L"colorMax");
ImmutableString<WCHAR> colorNbBits_str(L"colorNbBits");
ImmutableString<WCHAR> textureCoordinateQuant_str(L"textureCoordinateQuant");
ImmutableString<WCHAR> textureCoordinateMin_str(L"textureCoordinateMin");
ImmutableString<WCHAR> textureCoordinateMax_str(L"textureCoordinateMax");
ImmutableString<WCHAR> textureCoordinateNbBits_str(L"textureCoordinateNbBits");
ImmutableString<WCHAR> angleQuant_str(L"angleQuant");
ImmutableString<WCHAR> angleMin_str(L"angleMin");
ImmutableString<WCHAR> angleMax_str(L"angleMax");
ImmutableString<WCHAR> angleNbBits_str(L"angleNbBits");
ImmutableString<WCHAR> scaleQuant_str(L"scaleQuant");
ImmutableString<WCHAR> scaleMin_str(L"scaleMin");
ImmutableString<WCHAR> scaleMax_str(L"scaleMax");
ImmutableString<WCHAR> scaleNbBits_str(L"scaleNbBits");
ImmutableString<WCHAR> keyQuant_str(L"keyQuant");
ImmutableString<WCHAR> keyMin_str(L"keyMin");
ImmutableString<WCHAR> keyMax_str(L"keyMax");
ImmutableString<WCHAR> keyNbBits_str(L"keyNbBits");
ImmutableString<WCHAR> normalQuant_str(L"normalQuant");
ImmutableString<WCHAR> normalNbBits_str(L"normalNbBits");
ImmutableString<WCHAR> sizeQuant_str(L"sizeQuant");
ImmutableString<WCHAR> sizeMin_str(L"sizeMin");
ImmutableString<WCHAR> sizeMax_str(L"sizeMax");
ImmutableString<WCHAR> sizeNbBits_str(L"sizeNbBits");
ImmutableString<WCHAR> useEfficientCoding_str(L"useEfficientCoding");

ImmutableString<WCHAR> size_str(L"size");

ImmutableString<WCHAR> directOutput_str(L"directOutput");
ImmutableString<WCHAR> mustEvaluate_str(L"mustEvaluate");

ImmutableString<WCHAR> appearance_str(L"appearance");
ImmutableString<WCHAR> geometry_str(L"geometry");

ImmutableString<WCHAR> intensity_str(L"intensity");
ImmutableString<WCHAR> location_str(L"location");
ImmutableString<WCHAR> source_str(L"source");
ImmutableString<WCHAR> spatialize_str(L"spatialize");

ImmutableString<WCHAR> whichChoice_str(L"whichChoice");

ImmutableString<WCHAR> center_str(L"center");
ImmutableString<WCHAR> rotationAngle_str(L"rotationAngle");
ImmutableString<WCHAR> scaleOrientation_str(L"scaleOrientation");
ImmutableString<WCHAR> translation_str(L"translation");

ImmutableString<WCHAR> info_str(L"info");
ImmutableString<WCHAR> title_str(L"title");

ImmutableString<WCHAR> string_str(L"string");
ImmutableString<WCHAR> length_str(L"length");
ImmutableString<WCHAR> fontStyle_str(L"fontStyle");
ImmutableString<WCHAR> maxExtent_str(L"maxExtent");

ImmutableString<WCHAR> repeatS_str(L"repeatS");
ImmutableString<WCHAR> repeatT_str(L"repeatT");

ImmutableString<WCHAR> ambientIntensity_str(L"ambientIntensity");
ImmutableString<WCHAR> direction_str(L"direction");
ImmutableString<WCHAR> on_str(L"on");

ImmutableString<WCHAR> attenuation_str(L"attenuation");
ImmutableString<WCHAR> beamWidth_str(L"beamWidth");
ImmutableString<WCHAR> cutOffAngle_str(L"cutOffAngle");

ImmutableString<WCHAR> set_fraction_str(L"set_fraction");
ImmutableString<WCHAR> key_str(L"key");
ImmutableString<WCHAR> keyValue_str(L"keyValue");
ImmutableString<WCHAR> value_changed_str(L"value_changed");

ImmutableString<WCHAR> loop_str(L"loop");
ImmutableString<WCHAR> cycleInterval_str(L"cycleInterval");
ImmutableString<WCHAR> cycleTime_str(L"cycleTime");
ImmutableString<WCHAR> enabled_str(L"enabled");
ImmutableString<WCHAR> time_str(L"time");
ImmutableString<WCHAR> fraction_changed_str(L"fraction_changed");

ImmutableString<WCHAR> fineness_str(L"fineness");
ImmutableString<WCHAR> type_str(L"type");

ImmutableString<WCHAR> family_str(L"family");
ImmutableString<WCHAR> horizontal_str(L"horizontal");
ImmutableString<WCHAR> justify_str(L"justify");
ImmutableString<WCHAR> language_str(L"language");
ImmutableString<WCHAR> leftToRight_str(L"leftToRight");
ImmutableString<WCHAR> spacing_str(L"spacing");
ImmutableString<WCHAR> style_str(L"style");
ImmutableString<WCHAR> topToBottom_str(L"topToBottom");

ImmutableString<WCHAR> groups_str(L"groups");
ImmutableString<WCHAR> constraints_str(L"constraints");
ImmutableString<WCHAR> groupsIndex_str(L"groupsIndex");

ImmutableString<WCHAR> duration_changed_str(L"duration_changed");

ImmutableString<WCHAR> inSFBool_str(L"inSFBool");
ImmutableString<WCHAR> inSFColor_str(L"inSFColor");
ImmutableString<WCHAR> inMFColor_str(L"inMFColor");
ImmutableString<WCHAR> inSFFloat_str(L"inSFFloat");
ImmutableString<WCHAR> inMFFloat_str(L"inMFFloat");
ImmutableString<WCHAR> inSFInt32_str(L"inSFInt32");
ImmutableString<WCHAR> inMFInt32_str(L"inMFInt32");
ImmutableString<WCHAR> inSFRotation_str(L"inSFRotation");
ImmutableString<WCHAR> inMFRotation_str(L"inMFRotation");
ImmutableString<WCHAR> inSFString_str(L"inSFString");
ImmutableString<WCHAR> inMFString_str(L"inMFString");
ImmutableString<WCHAR> inSFTime_str(L"inSFTime");
ImmutableString<WCHAR> inSFVec2f_str(L"inSFVec2f");
ImmutableString<WCHAR> inMFVec2f_str(L"inMFVec2f");
ImmutableString<WCHAR> inSFVec3f_str(L"inSFVec3f");
ImmutableString<WCHAR> inMFVec3f_str(L"inMFVec3f");
ImmutableString<WCHAR> outSFBool_str(L"outSFBool");
ImmutableString<WCHAR> outSFColor_str(L"outSFColor");
ImmutableString<WCHAR> outMFColor_str(L"outMFColor");
ImmutableString<WCHAR> outSFFloat_str(L"outSFFloat");
ImmutableString<WCHAR> outMFFloat_str(L"outMFFloat");
ImmutableString<WCHAR> outSFInt32_str(L"outSFInt32");
ImmutableString<WCHAR> outMFInt32_str(L"outMFInt32");
ImmutableString<WCHAR> outSFRotation_str(L"outSFRotation");
ImmutableString<WCHAR> outMFRotation_str(L"outMFRotation");
ImmutableString<WCHAR> outSFString_str(L"outSFString");
ImmutableString<WCHAR> outMFString_str(L"outMFString");
ImmutableString<WCHAR> outSFTime_str(L"outSFTime");
ImmutableString<WCHAR> outSFVec2f_str(L"outSFVec2f");
ImmutableString<WCHAR> outMFVec2f_str(L"outMFVec2f");
ImmutableString<WCHAR> outSFVec3f_str(L"outSFVec3f");
ImmutableString<WCHAR> outMFVec3f_str(L"outMFVec3f");
ImmutableString<WCHAR> Factor1_str(L"Factor1");
ImmutableString<WCHAR> Factor2_str(L"Factor2");
ImmutableString<WCHAR> Factor3_str(L"Factor3");
ImmutableString<WCHAR> Factor4_str(L"Factor4");
ImmutableString<WCHAR> Offset1_str(L"Offset1");
ImmutableString<WCHAR> Offset2_str(L"Offset2");
ImmutableString<WCHAR> Offset3_str(L"Offset3");
ImmutableString<WCHAR> Offset4_str(L"Offset4");
ImmutableString<WCHAR> Sum_str(L"Sum");

// Node names

ImmutableString<WCHAR> Anchor_str(L"Anchor");
ImmutableString<WCHAR> AnimationStream_str(L"AnimationStream");
ImmutableString<WCHAR> Appearance_str(L"Appearance");
ImmutableString<WCHAR> AudioBuffer_str(L"AudioBuffer");
ImmutableString<WCHAR> AudioClip_str(L"AudioClip");
ImmutableString<WCHAR> AudioDelay_str(L"AudioDelay");
ImmutableString<WCHAR> AudioFX_str(L"AudioFX");
ImmutableString<WCHAR> AudioMix_str(L"AudioMix");
ImmutableString<WCHAR> AudioSource_str(L"AudioSource");
ImmutableString<WCHAR> AudioSwitch_str(L"AudioSwitch");
ImmutableString<WCHAR> Background2D_str(L"Background2D");
ImmutableString<WCHAR> Bitmap_str(L"Bitmap");
ImmutableString<WCHAR> Circle_str(L"Circle");
ImmutableString<WCHAR> Conditional_str(L"Conditional");
ImmutableString<WCHAR> Coordinate2D_str(L"Coordinate2D");
ImmutableString<WCHAR> DirectionalLight_str(L"DirectionalLight");
ImmutableString<WCHAR> FontStyle_str(L"FontStyle");
ImmutableString<WCHAR> Form_str(L"Form");
ImmutableString<WCHAR> Group_str(L"Group");
ImmutableString<WCHAR> ImageTexture_str(L"ImageTexture");
ImmutableString<WCHAR> IndexedFaceSet_str(L"IndexedFaceSet");
ImmutableString<WCHAR> IndexedFaceSet2D_str(L"IndexedFaceSet2D");
ImmutableString<WCHAR> IndexedLineSet_str(L"IndexedLineSet");
ImmutableString<WCHAR> IndexedLineSet2D_str(L"IndexedLineSet2D");
ImmutableString<WCHAR> Inline_str(L"Inline");
ImmutableString<WCHAR> LOD_str(L"LOD");
ImmutableString<WCHAR> Layer2D_str(L"Layer2D");
ImmutableString<WCHAR> Layer3D_str(L"Layer3D");
ImmutableString<WCHAR> LinePropertiesBIFS_str(L"LinePropertiesBIFS");
ImmutableString<WCHAR> Material_str(L"Material");
ImmutableString<WCHAR> Material2D_str(L"Material2D");
ImmutableString<WCHAR> MovieTexture_str(L"MovieTexture");
ImmutableString<WCHAR> OrderedGroup_str(L"OrderedGroup");
ImmutableString<WCHAR> PositionInterpolator_str(L"PositionInterpolator");
ImmutableString<WCHAR> PositionInterpolator2D_str(L"PositionInterpolator2D");
ImmutableString<WCHAR> QuantizationParameter_str(L"QuantizationParameter");
ImmutableString<WCHAR> Rectangle_str(L"Rectangle");
ImmutableString<WCHAR> Script_str(L"Script");
ImmutableString<WCHAR> Shape_str(L"Shape");
ImmutableString<WCHAR> Sound2D_str(L"Sound2D");
ImmutableString<WCHAR> SpotLight_str(L"SpotLight");
ImmutableString<WCHAR> Switch_str(L"Switch");
ImmutableString<WCHAR> Text_str(L"Text");
ImmutableString<WCHAR> TimeSensor_str(L"TimeSensor");
ImmutableString<WCHAR> Transform2D_str(L"Transform2D");
ImmutableString<WCHAR> Valuator_str(L"Valuator");
ImmutableString<WCHAR> WorldInfo_str(L"WorldInfo");
ImmutableString<WCHAR> Cylinder_str(L"Cylinder");
ImmutableString<WCHAR> Curve2D_str(L"Curve2D");
ImmutableString<WCHAR> Fog_str(L"Fog");
ImmutableString<WCHAR> Cone_str(L"Cone");
ImmutableString<WCHAR> Coordinate_str(L"Coordinate");
ImmutableString<WCHAR> FAP_str(L"FAP");
ImmutableString<WCHAR> FDP_str(L"FDP");
ImmutableString<WCHAR> FIT_str(L"FIT");
ImmutableString<WCHAR> CylinderSensor_str(L"CylinderSensor");
ImmutableString<WCHAR> DiscSensor_str(L"DiscSensor");
ImmutableString<WCHAR> ElevationGrid_str(L"ElevationGrid");
ImmutableString<WCHAR> Expression_str(L"Expression");
ImmutableString<WCHAR> Extrusion_str(L"Extrusion");
ImmutableString<WCHAR> Face_str(L"Face");
ImmutableString<WCHAR> FaceDefMesh_str(L"FaceDefMesh");
ImmutableString<WCHAR> FaceDefTables_str(L"FaceDefTables");
ImmutableString<WCHAR> FaceDefTransform_str(L"FaceDefTransform");
ImmutableString<WCHAR> CoordinateInterpolator_str(L"CoordinateInterpolator");
ImmutableString<WCHAR> CoordinateInterpolator2D_str(L"CoordinateInterpolator2D");
ImmutableString<WCHAR> Box_str(L"Box");
ImmutableString<WCHAR> Color_str(L"Color");
ImmutableString<WCHAR> Billboard_str(L"Billboard");
ImmutableString<WCHAR> Background_str(L"Background");
ImmutableString<WCHAR> Collision_str(L"Collision");
ImmutableString<WCHAR> ColorInterpolator_str(L"ColorInterpolator");
ImmutableString<WCHAR> CompositeTexture2D_str(L"CompositeTexture2D");
ImmutableString<WCHAR> CompositeTexture3D_str(L"CompositeTexture3D");
ImmutableString<WCHAR> Transform_str(L"Transform");
ImmutableString<WCHAR> Viewpoint_str(L"Viewpoint");
ImmutableString<WCHAR> VisibilitySensor_str(L"VisibilitySensor");
ImmutableString<WCHAR> Viseme_str(L"Viseme");
ImmutableString<WCHAR> TouchSensor_str(L"TouchSensor");
ImmutableString<WCHAR> TextureCoordinate_str(L"TextureCoordinate");
ImmutableString<WCHAR> TextureTransform_str(L"TextureTransform");
ImmutableString<WCHAR> TermCap_str(L"TermCap");
ImmutableString<WCHAR> Sphere_str(L"Sphere");
ImmutableString<WCHAR> SphereSensor_str(L"SphereSensor");
ImmutableString<WCHAR> Sound_str(L"Sound");
ImmutableString<WCHAR> ScalarInterpolator_str(L"ScalarInterpolator");
ImmutableString<WCHAR> PlaneSensor_str(L"PlaneSensor");
ImmutableString<WCHAR> PlaneSensor2D_str(L"PlaneSensor2D");
ImmutableString<WCHAR> PointLight_str(L"PointLight");
ImmutableString<WCHAR> Normal_str(L"Normal");
ImmutableString<WCHAR> NormalInterpolator_str(L"NormalInterpolator");
ImmutableString<WCHAR> OrientationInterpolator_str(L"OrientationInterpolator");
ImmutableString<WCHAR> PixelTexture_str(L"PixelTexture");
ImmutableString<WCHAR> NavigationInfo_str(L"NavigationInfo");
ImmutableString<WCHAR> PointSet_str(L"PointSet");
ImmutableString<WCHAR> PointSet2D_str(L"PointSet2D");
ImmutableString<WCHAR> ProximitySensor2D_str(L"ProximitySensor2D");
ImmutableString<WCHAR> ProximitySensor_str(L"ProximitySensor");
ImmutableString<WCHAR> Layout_str(L"Layout");
ImmutableString<WCHAR> ListeningPoint_str(L"ListeningPoint");

// Fields

Field AppearanceFields[] =
{
	{&material_str, BIFS_SFMaterialNode,					1, 1, 1, 0,		0, 0,		-1, -1},
	{&texture_str, BIFS_SFTextureNode,						1, 1, 1, 0,		0, 0,		-1, -1},
	{&textureTransform_str, BIFS_SFTextureTransform,	1, 1, 1, 0,		0, 0,		-1, -1},
	NULL
};

/*
Field AppearanceFields[] =
{
	{&material_str, BIFS_SFMaterialNode,					1, 1, 1, 0,		0, 0,		-1, -1},
	{WSTR("texture"), BIFS_SFTextureNode,						1, 1, 1, 0,		0, 0,		-1, -1},
	{WSTR("textureTransform"), BIFS_SFTextureTransform,	1, 1, 1, 0,		0, 0,		-1, -1},
	NULL
};
*/

Field AudioSourceFields[] =
{
	{&addChildren_str, BIFS_MFAudioNode,				0, 1, 0, 0,		0, 0,			-1, -1},
	{&removeChildren_str, BIFS_MFAudioNode,			0, 1, 0, 0,		0, 0,			-1, -1},
	{&children_str, BIFS_MFAudioNode,					1, 1, 1, 0,		0, 0,			-1, -1},
	{&url_str, BIFS_MFURL,									1, 1, 1, 0,		0, 0,			-1, -1},
	{&pitch_str, BIFS_SFFloat,							1, 1, 1, 1,		0, LONG_MAX, 0, -1},
	{&speed_str, BIFS_SFFloat,							1, 1, 1, 1,		0, LONG_MAX, 0, -1},
	{&startTime_str, BIFS_SFTime,						1, 1, 1, 0,		0, 0,			-1, -1},
	{&stopTime_str, BIFS_SFTime,							1, 1, 1, 0,		0, 0,			-1, -1},
	{&numChan_str, BIFS_SFInt32,							1, 0, 0, 0,		0, 255,		13, 8},
	{&phaseGroup_str, BIFS_MFInt32,						1, 0, 0, 0,		0, 255,		13, 8},
	NULL
};

Field Background2DFields[] =
{
	{&set_bind_str, BIFS_SFBool,		0, 1, 0, 0,		0, 0,		-1, -1},
	{&backColor_str, BIFS_SFColor,	1, 1, 1, 0,		0, 1,		4, -1},
	{&url_str, BIFS_MFURL,				1, 1, 1, 0,		0, 0,		-1, -1},
	{&isBound_str, BIFS_SFBool,		0, 0, 1, 0,		0, 0,		-1, -1},
	NULL,
};

Field BitmapFields[] =
{
	{&scale_str, BIFS_SFVec2f,	1/*??*/,0,0,0,			0,0,	12,-1},
	NULL
};

Field CircleFields[] =
{
	{&radius_str, BIFS_SFFloat,	1/*??*/,0,0,0,			0,FLT_MAX,	12,-1},
	NULL
};

Field ConditionalFields[] =
{
	{&activate_str, BIFS_SFBool,				0,1,0,0,			0,0,		-1,-1},
	{&reverseActivate_str, BIFS_SFBool,	0,1,0,0,			0,0,		-1,-1},
	{&buffer_str, BIFS_SFCommandBuffer,	1/*??*/,1,0,0,	0,0,		-1,-1},
	{&isActive_str, BIFS_SFBool,				0,0,1,0,			0,0,		-1,-1},
	NULL
};

Field Coordinate2DFields[] =
{
	{&point_str, BIFS_MFVec2f, 1/*in the spec there's nothing there??*/, 0, 0, 0,		-FLT_MAX, FLT_MAX,		2, -1},
	NULL
};

Field Curve2DFields[] =
{
	{&point_str, BIFS_SFCoordinate2DNode,	1, 1, 1, 0,		0, 0,		-1, -1},
	{&fineness_str, BIFS_SFFloat,			1, 1, 1, 0,		0, 1,		0, -1},
	{&type_str, BIFS_MFInt32,					1, 1, 1, 0,		0, 3,		13, 2},
	NULL
};

Field DirectionalLightFields[] =
{
	{&ambientIntensity_str, BIFS_SFFloat,	1, 1, 1, 1,		0,1,		4, -1},
	{&color_str, BIFS_SFColor,				1, 1, 1, 1,		0,1,		4, -1},
	{&direction_str, BIFS_SFVec3f,			1, 1, 1, 1,		0,0,		9, -1},
	{&intensity_str, BIFS_SFFloat,			1, 1, 1, 1,		0,1,		4, -1},
	{&on_str, BIFS_SFBool,						1, 1, 1, 0,		0,0,		-1, -1},
	NULL,
};

Field FontStyleFields[] =
{
	{&family_str, BIFS_MFString,			1, 0, 0, 0,		0,0,			-1,-1},
	{&horizontal_str, BIFS_SFBool,		1, 0, 0, 0,		0,0,			-1,-1},
	{&justify_str, BIFS_MFString,		1, 0, 0, 0,		0,0,			-1,-1},
	{&language_str, BIFS_SFString,		1, 0, 0, 0,		0,0,			-1,-1},
	{&leftToRight_str, BIFS_SFBool,		1, 0, 0, 0,		0,0,			-1,-1},
	{&size_str, BIFS_SFFloat,				1, 0, 0, 0,		0,FLT_MAX,	11,-1},
	{&spacing_str, BIFS_SFFloat,			1, 0, 0, 0,		0,FLT_MAX,	11,-1},
	{&style_str, BIFS_SFString,			1, 0, 0, 0,		0,0,			-1,-1},
	{&topToBottom_str, BIFS_SFBool,		1, 0, 0, 0,		0,0,			-1,-1},
	NULL
};

Field FormFields[] =
{
	{&addChildren_str, BIFS_MF2DNode,				0,1,0,0,			0,0,			-1,-1},
	{&removeChildren_str, BIFS_MF2DNode,			0,1,0,0,			0,0,			-1,-1},
	{&children_str, BIFS_MF2DNode,					1,1,1,0,			0,0,			-1,-1},
	{&size_str, BIFS_SFVec2f,							1,1,1,0,			0,FLT_MAX,	12,-1},
	{&groups_str, BIFS_MFInt32,						1,1,1,0,			-1, 1022,	13,10},
	{&constraints_str, BIFS_MFString,				1,1,1,0,			0,0,			-1,-1},
	{&groupsIndex_str, BIFS_MFInt32,				1,1,1,0,			-1, 1022,	13,10},
	NULL
};

Field GroupFields[] =
{
	{&addChildren_str, BIFS_MF3DNode,		0,1,0,0,					0,0,			-1,-1},
	{&removeChildren_str, BIFS_MF3DNode,	0,1,0,0,					0,0,			-1,-1},
	{&children_str, BIFS_MF3DNode,			1/*??*/,1,0,0,			0,0,			-1,-1},
	NULL
};

Field ImageTextureFields[] =
{
	{&url_str, BIFS_MFURL,			1, 0, 0, 0,		0,0,	-1,-1},
	{&repeatS_str, BIFS_SFBool,	1, 0, 0, 0,		0,0,	-1,-1},
	{&repeatT_str, BIFS_SFBool,	1, 0, 0, 0,		0,0,	-1,-1},
	NULL
};

Field IndexedFaceSet2DFields[] =
{
	{&set_colorIndex_str, BIFS_MFInt32,				0, 1, 0, 0,		0,0,			-1, -1},
	{&set_coordIndex_str, BIFS_MFInt32,				0, 1, 0, 0,		0,0,			-1, -1},
	{&set_texCoordIndex_str, BIFS_MFInt32,			0, 1, 0, 0,		0,0,			-1, -1},
	{&color_str, BIFS_SFColorNode,						1, 1, 1, 0,		0,0,			-1, -1},
	{&coord_str, BIFS_SFCoordinate2DNode,				1, 1, 1, 0,		0,0,			-1, -1},
	{&texCoord_str, BIFS_SFTextureCoordinateNode,	1, 1, 1, 0,		0,0,			-1, -1},
	{&colorIndex_str, BIFS_MFInt32,						1, 0, 0, 0,		0,LONG_MAX,	14, -1},
	{&colorPerVertex_str, BIFS_SFBool,					1, 0, 0, 0,		0,0,			-1, -1},
	{&convex_str, BIFS_SFBool,							1, 0, 0, 0,		0,0,			-1, -1},
	{&coordIndex_str, BIFS_MFInt32,						1, 0, 0, 0,		0,LONG_MAX,	14, -1},
	{&texCoordIndex_str, BIFS_MFInt32,					1, 0, 0, 0,		0,LONG_MAX,	14, -1},

	NULL,
};

Field IndexedLineSet2DFields[] =
{
	{&set_colorIndex_str, BIFS_MFInt32,			0, 1, 0, 0,		0,0,			-1, -1},
	{&set_coordIndex_str, BIFS_MFInt32,			0, 1, 0, 0,		0,0,			-1, -1},
	{&color_str, BIFS_SFColorNode,					1, 1, 1, 0,		0,0,			-1, -1},
	{&coord_str, BIFS_SFCoordinate2DNode,			1, 1, 1, 0,		0,0,			-1, -1},
	{&colorIndex_str, BIFS_MFInt32,					1, 0, 0, 0,		0,LONG_MAX,	14, -1},
	{&colorPerVertex_str, BIFS_SFBool,				1, 0, 0, 0,		0,0,			-1, -1},
	{&coordIndex_str, BIFS_MFInt32,					1, 0, 0, 0,		0,LONG_MAX,	14, -1},
	NULL
};

Field LinePropertiesFields[] =
{
	{&lineColor_str, BIFS_SFColor,			1, 1, 1, 1,		0,1,			4, -1},
	{&lineStyle_str, BIFS_SFInt32,			1, 1, 1, 0,		0,5,			13, 3},
	{&width_str, BIFS_SFFloat,				1, 1, 1, 1,		0,FLT_MAX,	12, -1},
	NULL,
};

Field Material2DFields[] =
{
	{&emissiveColor_str, BIFS_SFColor,				1, 1, 1, 1,		0,1,		4, -1},
	{&filled_str, BIFS_SFBool,						1, 1, 1, 0,		0,0,		-1, -1},
	{&lineProps_str, BIFS_SFLinePropertiesNode,	1, 1, 1, 0,		0,0,		-1, -1},
	{&transparency_str, BIFS_SFFloat,				1, 1, 1, 1,		0,1,		4, -1},
	NULL
};

Field MovieTextureFields[] =
{
	{&loop_str, BIFS_SFBool,					1, 1, 1, 0,		0,0,						-1,-1},
	{&speed_str, BIFS_SFFloat,				1, 1, 1, 0,		-FLT_MAX,FLT_MAX,		0,-1},
	{&startTime_str, BIFS_SFTime,			1, 1, 1, 0,		-FLT_MAX,FLT_MAX,		-1,-1},
	{&stopTime_str, BIFS_SFTime,				1, 1, 1, 0,		-FLT_MAX,FLT_MAX,		-1,-1},
	{&url_str, BIFS_MFURL,						1, 1, 1, 0,		0,0,						-1,-1},
	{&repeatS_str, BIFS_SFBool,				1, 0, 0, 0,		0,0,						-1,-1},
	{&repeatT_str, BIFS_SFBool,				1, 0, 0, 0,		0,0,						-1,-1},
	{&duration_changed_str, BIFS_SFTime,	0, 0, 1, 0,		0,0,						-1,-1},
	{&isActive_str, BIFS_SFBool,				0, 0, 1, 0,		0,0						-1,-1},
	NULL
};

Field OrderedGroupFields[] =
{
	{&addChildren_str, BIFS_MF3DNode,		0, 1, 0, 0,			0,0,			-1, -1},
	{&removeChildren_str, BIFS_MF3DNode,	0, 1, 0, 0,			0,0,			-1, -1},
	{&children_str, BIFS_MF3DNode,			1, 1, 1, 0, 		0,0,			-1, -1},
	{&order_str, BIFS_MFFloat,				1, 1, 1, 0,			0,FLT_MAX,	3, -1},
	NULL
};

Field PositionInterpolator2DFields[] =
{
	{&set_fraction_str, BIFS_SFFloat,		0,1,0,0,			0,0,						-1,-1},
	{&key_str, BIFS_MFFloat,					1,1,1,0,			0,1,						8,-1},
	{&keyValue_str, BIFS_MFVec2f,			1,1,1,0,			-FLT_MAX,FLT_MAX,		2,-1},
	{&value_changed_str, BIFS_SFVec2f,		0,0,1,0,			0,0,						-1,-1},
	NULL
};

Field QuantizationParameterFields[] =
{
	{&isLocal_str, BIFS_SFBool,						1, 0, 0, 0,		0,0,					-1, -1},

	{&position3DQuant_str, BIFS_SFBool,			1, 0, 0, 0,		0,0,					-1, -1},
	{&position3DMin_str, BIFS_SFVec3f,				1, 0, 0, 0,		-FLT_MAX,FLT_MAX,	0, -1},
	{&position3DMax_str, BIFS_SFVec3f,				1, 0, 0, 0,		-FLT_MAX,FLT_MAX,	0, -1},
	{&position3DNbBits_str, BIFS_SFInt32,			1, 0, 0, 0,		0, 31,				13, 5},

	{&position2DQuant_str, BIFS_SFBool,			1, 0, 0, 0,		0,0,					-1, -1},
	{&position2DMin_str, BIFS_SFVec2f,				1, 0, 0, 0,		-FLT_MAX,FLT_MAX,	0, -1},
	{&position2DMax_str, BIFS_SFVec2f,				1, 0, 0, 0,		-FLT_MAX,FLT_MAX,	0, -1},
	{&position2DNbBits_str, BIFS_SFInt32,			1, 0, 0, 0,		0, 31,				13, 5},

	{&drawOrderQuant_str, BIFS_SFBool,				1, 0, 0, 0,		0,0,					-1, -1},
	{&drawOrderMin_str, BIFS_SFFloat,				1, 0, 0, 0,		-FLT_MAX,FLT_MAX,	0, -1},
	{&drawOrderMax_str, BIFS_SFFloat,				1, 0, 0, 0,		-FLT_MAX,FLT_MAX,	0, -1},
	{&drawOrderNbBits_str, BIFS_SFInt32,			1, 0, 0, 0,		0, 31,				13, 5},

	{&colorQuant_str, BIFS_SFBool,					1, 0, 0, 0,		0,0,					-1, -1},
	{&colorMin_str, BIFS_SFFloat,					1, 0, 0, 0,		0,1,					0, -1},
	{&colorMax_str, BIFS_SFFloat,					1, 0, 0, 0,		0,1,					0, -1},
	{&colorNbBits_str, BIFS_SFInt32,				1, 0, 0, 0,		0,31,					13, 5},

	{&textureCoordinateQuant_str, BIFS_SFBool,	1, 0, 0, 0,		0,0,					-1, -1},
	{&textureCoordinateMin_str, BIFS_SFFloat,	1, 0, 0, 0,		0,1,					0, -1},
	{&textureCoordinateMax_str, BIFS_SFFloat,	1, 0, 0, 0,		0,1,					0, -1},
	{&textureCoordinateNbBits_str, BIFS_SFInt32,1, 0, 0, 0,		0,31,					13, 5},

	{&angleQuant_str, BIFS_SFBool,					1, 0, 0, 0,		0,0,					-1, -1},
	{&angleMin_str, BIFS_SFFloat,					1, 0, 0, 0,		0,	6.2831853f,		0, -1},
	{&angleMax_str, BIFS_SFFloat,					1, 0, 0, 0,		0,	6.2831853f,		0, -1},
	{&angleNbBits_str, BIFS_SFInt32,				1, 0, 0, 0,		0,31,					13, 5},

	{&scaleQuant_str, BIFS_SFBool,					1, 0, 0, 0,		0,0,					-1, -1},
	{&scaleMin_str, BIFS_SFFloat,					1, 0, 0, 0,		0,FLT_MAX,			0, -1},
	{&scaleMax_str, BIFS_SFFloat,					1, 0, 0, 0,		0,FLT_MAX,			0, -1},
	{&scaleNbBits_str, BIFS_SFInt32,				1, 0, 0, 0,		0,31,					13, 5},

	{&keyQuant_str, BIFS_SFBool,						1, 0, 0, 0,		0,0,					-1, -1},
	{&keyMin_str, BIFS_SFFloat,						1, 0, 0, 0,		-FLT_MAX,FLT_MAX,	0, -1},
	{&keyMax_str, BIFS_SFFloat,						1, 0, 0, 0,		-FLT_MAX,FLT_MAX,	0, -1},
	{&keyNbBits_str, BIFS_SFInt32,					1, 0, 0, 0,		0,31,					13, 5},

	{&normalQuant_str, BIFS_SFBool,					1, 0, 0, 0,		0,0,					-1, -1},
	{&normalNbBits_str, BIFS_SFInt32,				1, 0, 0, 0,		0,31,					13, 5},

	{&sizeQuant_str, BIFS_SFBool,					1, 0, 0, 0,		0,0,					-1, -1},
	{&sizeMin_str, BIFS_SFFloat,						1, 0, 0, 0,		-FLT_MAX,FLT_MAX,	0, -1},
	{&sizeMax_str, BIFS_SFFloat,						1, 0, 0, 0,		-FLT_MAX,FLT_MAX,	0, -1},
	{&sizeNbBits_str, BIFS_SFInt32,					1, 0, 0, 0,		0,31,					13, 5},

	{&useEfficientCoding_str, BIFS_SFBool,		1, 0, 0, 0,		0,0,					-1, -1},
	NULL
};

Field RectangleFields[] =
{
	{&size_str, BIFS_SFVec2f,		1/*??*/, 0, 0, 0,		0, FLT_MAX,		12, -1},
	NULL
};

Field ScriptFields[] =
{
	{&url_str, BIFS_MFScript,				1,0,0,0,		0,0,		-1,-1},
	{&directOutput_str, BIFS_SFBool,	1,0,0,0,		0,0,		-1,-1},
	{&mustEvaluate_str, BIFS_SFBool,	1,0,0,0,		0,0,		-1,-1},
	NULL
};

Field ShapeFields[] =
{
	{&appearance_str, BIFS_SFAppearanceNode,		1, 1, 1, 0,		0,0,		-1, -1},
	{&geometry_str,  BIFS_SFGeometryNode,			1, 1, 1, 0,		0,0,		-1, -1},
	NULL,
};

Field Sound2DFields[] =
{
	{&intensity_str, BIFS_SFFloat,		1, 1, 1, 1,		0,1,					4, -1},
	{&location_str, BIFS_SFVec2f,		1, 1, 1, 1,		-FLT_MAX,FLT_MAX,	4, -1},
	{&source_str, BIFS_SFAudioNode,		1, 1, 1, 0,		0,0,					-1, -1},
	{&spatialize_str, BIFS_SFBool,		1, 0, 0, 0,		0,0,					-1, -1},
	NULL
};

Field SpotLightFields[] =
{
	{&ambientIntensity_str, BIFS_SFFloat,		1,1,1,1,	0, 1,						4,-1},
	{&attenuation_str, BIFS_SFVec3f,			1,1,1,1, 0, FLT_MAX,				11,-1},
	{&beamWidth_str, BIFS_SFFloat,				1,1,1,1, 0, 1.5707963f,			6,-1},
	{&color_str, BIFS_SFColor,					1,1,1,1, 0, 1,						4,-1},
	{&cutOffAngle_str, BIFS_SFFloat,			1,1,1,1, 0, 1.5707963f,			6,-1},
	{&direction_str, BIFS_SFVec3f,				1,1,1,1, -FLT_MAX, +FLT_MAX,	9,-1},
	{&intensity_str, BIFS_SFFloat,				1,1,1,1, 0, 1,						4,-1},
	{&location_str, BIFS_SFVec3f,				1,1,1,1, -FLT_MAX, +FLT_MAX,	1,-1},
	{&on_str, BIFS_SFBool,							1,1,1,0, 0,0,						-1,-1},
	{&radius_str, BIFS_SFFloat,					1,1,1,1,	0, +FLT_MAX,			11,-1},
	NULL
};

Field SwitchFields[] =
{
	{&children_str, BIFS_MF3DNode,			1, 1, 1, 0,		0,0,			-1, -1},	// "choice"
	{&whichChoice_str, BIFS_SFInt32,	1, 1, 1, 0,		-1,1022,		13, 10},
	NULL
};

Field TextFields[] =
{
	{&string_str, BIFS_MFString,					1, 1, 1, 0,		0,0,			-1,-1},
	{&length_str, BIFS_MFFloat,					1, 1, 1, 1,		0,FLT_MAX,	7,-1},
	{&fontStyle_str, BIFS_SFFontStyleNode,	1, 1, 1, 0,		0,0,			-1,-1},
	{&maxExtent_str, BIFS_SFFloat,				1, 1, 1, 1,		0,FLT_MAX,	7,-1},
	NULL
};

Field TimeSensorFields[] =
{
	{&cycleInterval_str, BIFS_SFTime,		1,1,1,0,		0,FLT_MAX,			-1,-1},
	{&enabled_str, BIFS_SFBool,				1,1,1,0,		0,0,					-1,-1},
	{&loop_str, BIFS_SFBool,					1,1,1,0,		0,0,					-1,-1},
	{&startTime_str, BIFS_SFTime,			1,1,1,0,		-FLT_MAX,FLT_MAX,	-1,-1},
	{&stopTime_str, BIFS_SFTime,				1,1,1,0,		-FLT_MAX,FLT_MAX,	-1,-1},
	{&cycleTime_str, BIFS_SFTime,			0,0,1,0,		0,0,					-1,-1},
	{&fraction_changed_str, BIFS_SFFloat,	0,0,1,0,		0,0,					-1,-1},
	{&isActive_str, BIFS_SFBool,				0,0,1,0,		0,0,					-1,-1},
	{&time_str, BIFS_SFTime,					0,0,1,0,		0,0,					-1,-1},
	NULL
};

Field Transform2DFields[] =
{
	{&addChildren_str, BIFS_MF2DNode,				0, 1, 0, 0,		0,0,					-1, -1},
	{&removeChildren_str, BIFS_MF2DNode,			0, 1, 0, 0,		0,0,					-1, -1},
	{&children_str, BIFS_MF2DNode,					1, 1, 1, 0,		0,0,					-1, -1},
	{&center_str, BIFS_SFVec2f,						1, 1, 1, 1,		-FLT_MAX,FLT_MAX,	2, -1},
	{&rotationAngle_str, BIFS_SFFloat,				1, 1, 1, 1,		0,6.2831853f,		6, -1},
	{&scale_str, BIFS_SFVec2f,						1, 1, 1, 1,		0,FLT_MAX,			7, -1},
	{&scaleOrientation_str, BIFS_SFFloat,			1, 1, 1, 1,		0,6.2831853f,		6, -1},
	{&translation_str, BIFS_SFVec2f,				1, 1, 1, 1,		-FLT_MAX,FLT_MAX,	2, -1},
	NULL
};

Field ValuatorFields[] =
{
	{&inSFBool_str, BIFS_SFBool,				0,1,0,0,			0,0,						-1,-1},
	{&inSFColor_str, BIFS_SFColor,			0,1,0,0,			0,0,						-1,-1},
	{&inMFColor_str, BIFS_MFColor,			0,1,0,0,			0,0,						-1,-1},
	{&inSFFloat_str, BIFS_SFFloat,			0,1,0,0,			0,0,						-1,-1},
	{&inMFFloat_str, BIFS_MFFloat,			0,1,0,0,			0,0,						-1,-1},
	{&inSFInt32_str, BIFS_SFInt32,			0,1,0,0,			0,0,						-1,-1},
	{&inMFInt32_str, BIFS_MFInt32,			0,1,0,0,			0,0,						-1,-1},
	{&inSFRotation_str, BIFS_SFRotation,	0,1,0,0,			0,0,						-1,-1},
	{&inMFRotation_str, BIFS_MFRotation,	0,1,0,0,			0,0,						-1,-1},
	{&inSFString_str, BIFS_SFString,		0,1,0,0,			0,0,						-1,-1},
	{&inMFString_str, BIFS_MFString,		0,1,0,0,			0,0,						-1,-1},
	{&inSFTime_str, BIFS_SFTime,				0,1,0,0,			0,0,						-1,-1},
	{&inSFVec2f_str, BIFS_SFVec2f,			0,1,0,0,			0,0,						-1,-1},
	{&inMFVec2f_str, BIFS_MFVec2f,			0,1,0,0,			0,0,						-1,-1},
	{&inSFVec3f_str, BIFS_SFVec3f,			0,1,0,0,			0,0,						-1,-1},
	{&inMFVec3f_str, BIFS_MFVec3f,			0,1,0,0,			0,0,						-1,-1},
	{&outSFBool_str, BIFS_SFBool,			0,0,1,0,			0,0,						-1,-1},
	{&outSFColor_str, BIFS_SFColor,			0,0,1,0,			0,0,						-1,-1},
	{&outMFColor_str, BIFS_MFColor,			0,0,1,0,			0,0,						-1,-1},
	{&outSFFloat_str, BIFS_SFFloat,			0,0,1,0,			0,0,						-1,-1},
	{&outMFFloat_str, BIFS_MFFloat,			0,0,1,0,			0,0,						-1,-1},
	{&outSFInt32_str, BIFS_SFInt32,			0,0,1,0,			0,0,						-1,-1},
	{&outMFInt32_str, BIFS_MFInt32,			0,0,1,0,			0,0,						-1,-1},
	{&outSFRotation_str, BIFS_SFRotation,	0,0,1,0,			0,0,						-1,-1},
	{&outMFRotation_str, BIFS_MFRotation,	0,0,1,0,			0,0,						-1,-1},
	{&outSFString_str, BIFS_SFString,		0,0,1,0,			0,0,						-1,-1},
	{&outMFString_str, BIFS_MFString,		0,0,1,0,			0,0,						-1,-1},
	{&outSFTime_str, BIFS_SFTime,			0,0,1,0,			0,0,						-1,-1},
	{&outSFVec2f_str, BIFS_SFVec2f,			0,0,1,0,			0,0,						-1,-1},
	{&outMFVec2f_str, BIFS_MFVec2f,			0,0,1,0,			0,0,						-1,-1},
	{&outSFVec3f_str, BIFS_SFVec3f,			0,0,1,0,			0,0,						-1,-1},
	{&outMFVec3f_str, BIFS_MFVec3f,			0,0,1,0,			0,0,						-1,-1},
	{&Factor1_str, BIFS_SFFloat,				1,1,1,0,			-FLT_MAX,FLT_MAX,		0,-1},
	{&Factor2_str, BIFS_SFFloat,				1,1,1,0,			-FLT_MAX,FLT_MAX,		0,-1},
	{&Factor3_str, BIFS_SFFloat,				1,1,1,0,			-FLT_MAX,FLT_MAX,		0,-1},
	{&Factor4_str, BIFS_SFFloat,				1,1,1,0,			-FLT_MAX,FLT_MAX,		0,-1},
	{&Offset1_str, BIFS_SFFloat,				1,1,1,0,			-FLT_MAX,FLT_MAX,		0,-1},
	{&Offset2_str, BIFS_SFFloat,				1,1,1,0,			-FLT_MAX,FLT_MAX,		0,-1},
	{&Offset3_str, BIFS_SFFloat,				1,1,1,0,			-FLT_MAX,FLT_MAX,		0,-1},
	{&Offset4_str, BIFS_SFFloat,				1,1,1,0,			-FLT_MAX,FLT_MAX,		0,-1},
	{&Sum_str, BIFS_SFBool,					1,1,1,0,			0,0,						-1,-1},
	NULL
};

Field WorldInfoFields[] =
{
	{&info_str, BIFS_MFString,		1, 0, 0, 0,		0, 0, -1,-1},
	{&title_str, BIFS_SFString,		1, 0, 0, 0,		0, 0, -1,-1},
	NULL
};

// Nodes

Node nodes[] =
{
&Anchor_str, NULL, // 0000001 2 DEF bits 3 IN bits 2 OUT bits 0 DYN bits
&AnimationStream_str, NULL,// 0000010 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
&Appearance_str, AppearanceFields,// 0000011 2 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
&AudioBuffer_str, NULL,// 0000100 3 DEF bits 3 IN bits 4 OUT bits 0 DYN bits
&AudioClip_str, NULL,// 0000101 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
&AudioDelay_str, NULL,// 0000110 2 DEF bits 2 IN bits 1 OUT bits 0 DYN bits
&AudioFX_str, NULL,// 0000111 3 DEF bits 3 IN bits 2 OUT bits 0 DYN bits
&AudioMix_str, NULL,// 0001000 3 DEF bits 3 IN bits 2 OUT bits 0 DYN bits
&AudioSource_str, AudioSourceFields,// 0001001 3 DEF bits 3 IN bits 3 OUT bits 1 DYN bits
&AudioSwitch_str, NULL,// 0001010 2 DEF bits 2 IN bits 1 OUT bits 0 DYN bits
&Background_str, NULL,// 0001011 4 DEF bits 4 IN bits 4 OUT bits 2 DYN bits
&Background2D_str, Background2DFields,// 0001100 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
&Billboard_str, NULL,// 0001101 1 DEF bits 2 IN bits 1 OUT bits 0 DYN bits
&Bitmap_str, BitmapFields,// 0001110 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
&Box_str, NULL,// 0001111 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
&Circle_str, CircleFields,// 0010000 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
&Collision_str, NULL,// 0010001 2 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
&Color_str, NULL,// 0010010 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
&ColorInterpolator_str, NULL,// 0010011 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
&CompositeTexture2D_str, NULL,// 0010100 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
&CompositeTexture3D_str, NULL,// 0010101 3 DEF bits 4 IN bits 3 OUT bits 0 DYN bits
&Conditional_str, ConditionalFields,// 0010110 0 DEF bits 2 IN bits 1 OUT bits 0 DYN bits
&Cone_str, NULL,// 0010111 2 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
&Coordinate_str, NULL,// 0011000 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
&Coordinate2D_str, Coordinate2DFields,// 0011001 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
&CoordinateInterpolator_str, NULL,// 0011010 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
&CoordinateInterpolator2D_str, NULL,// 0011011 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
&Curve2D_str, Curve2DFields,// 0011100 2 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
&Cylinder_str, NULL,// 0011101 3 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
&CylinderSensor_str, NULL,// 0011110 3 DEF bits 3 IN bits 4 OUT bits 0 DYN bits
&DirectionalLight_str, DirectionalLightFields,// 0011111 3 DEF bits 3 IN bits 3 OUT bits 2 DYN bits
&DiscSensor_str, NULL,// 0100000 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
&ElevationGrid_str, NULL,// 0100001 4 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
&Expression_str, NULL,// 0100010 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
&Extrusion_str, NULL,// 0100011 4 DEF bits 2 IN bits 0 OUT bits 0 DYN bits
&Face_str, NULL,// 0100100 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
&FaceDefMesh_str, NULL,// 0100101 2 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
&FaceDefTables_str, NULL,// 0100110 2 DEF bits 1 IN bits 1 OUT bits 0 DYN bits
&FaceDefTransform_str, NULL,// 0100111 3 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
&FAP_str, NULL,// 0101000 7 DEF bits 7 IN bits 7 OUT bits 0 DYN bits
&FDP_str, NULL,// 0101001 3 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
&FIT_str, NULL,// 0101010 4 DEF bits 4 IN bits 4 OUT bits 0 DYN bits
&Fog_str, NULL,// 0101011 2 DEF bits 2 IN bits 2 OUT bits 1 DYN bits
&FontStyle_str, FontStyleFields,// 0101100 4 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
&Form_str, FormFields,// 0101101 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
&Group_str, GroupFields,// 0101110 0 DEF bits 2 IN bits 0 OUT bits 0 DYN bits
&ImageTexture_str, ImageTextureFields,// 0101111 2 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
&IndexedFaceSet_str, NULL,// 0110000 4 DEF bits 3 IN bits 2 OUT bits 0 DYN bits
&IndexedFaceSet2D_str, IndexedFaceSet2DFields,// 0110001 3 DEF bits 3 IN bits 2 OUT bits 0 DYN bits
&IndexedLineSet_str, NULL,// 0110010 3 DEF bits 2 IN bits 1 OUT bits 0 DYN bits
&IndexedLineSet2D_str, IndexedLineSet2DFields,// 0110011 3 DEF bits 2 IN bits 1 OUT bits 0 DYN bits
&Inline_str, NULL,// 0110100 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
&LOD_str, NULL,// 0110101 2 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
&Layer2D_str, NULL,// 0110110 2 DEF bits 3 IN bits 2 OUT bits 0 DYN bits
&Layer3D_str, NULL,// 0110111 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
&Layout_str, NULL,// 0111000 4 DEF bits 4 IN bits 4 OUT bits 2 DYN bits
&LinePropertiesBIFS_str, LinePropertiesFields,// 0111001 2 DEF bits 2 IN bits 2 OUT bits 1 DYN bits
&ListeningPoint_str, NULL,// 0111010 2 DEF bits 2 IN bits 3 OUT bits 1 DYN bits
&Material_str, NULL,// 0111011 3 DEF bits 3 IN bits 3 OUT bits 3 DYN bits
&Material2D_str, Material2DFields,// 0111100 2 DEF bits 2 IN bits 2 OUT bits 1 DYN bits
&MovieTexture_str, MovieTextureFields,// 0111101 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
&NavigationInfo_str, NULL,// 0111110 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
&Normal_str, NULL,// 0111111 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
&NormalInterpolator_str, NULL,// 1000000 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
&OrderedGroup_str, OrderedGroupFields,// 1000001 1 DEF bits 2 IN bits 1 OUT bits 0 DYN bits
&OrientationInterpolator_str, NULL,// 1000010 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
&PixelTexture_str, NULL,// 1000011 2 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
&PlaneSensor_str, NULL,// 1000100 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
&PlaneSensor2D_str, NULL,// 1000101 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
&PointLight_str, NULL,// 1000110 3 DEF bits 3 IN bits 3 OUT bits 3 DYN bits
&PointSet_str, NULL,// 1000111 1 DEF bits 1 IN bits 1 OUT bits 0 DYN bits
&PointSet2D_str, NULL,// 1001000 1 DEF bits 1 IN bits 1 OUT bits 0 DYN bits
&PositionInterpolator_str, NULL,// 1001001 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
&PositionInterpolator2D_str, PositionInterpolator2DFields,// 1001010 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
&ProximitySensor_str, NULL,// 1001100 2 DEF bits 2 IN bits 3 OUT bits 0 DYN bits
&ProximitySensor2D_str, NULL,// 1001011 2 DEF bits 2 IN bits 3 OUT bits 0 DYN bits
&QuantizationParameter_str, QuantizationParameterFields,// 1001101 6 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
&Rectangle_str, RectangleFields,// 1001110 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
&ScalarInterpolator_str, NULL,// 1001111 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
&Script_str, ScriptFields,// 1010000 2 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
&Shape_str, ShapeFields,// 1010001 1 DEF bits 1 IN bits 1 OUT bits 0 DYN bits
&Sound_str, NULL,// 1010010 4 DEF bits 4 IN bits 4 OUT bits 3 DYN bits
&Sound2D_str, Sound2DFields,// 1010011 2 DEF bits 2 IN bits 2 OUT bits 1 DYN bits
&Sphere_str, NULL,// 1010100 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
&SphereSensor_str, NULL,// 1010101 2 DEF bits 2 IN bits 3 OUT bits 0 DYN bits
&SpotLight_str, SpotLightFields,// 1010110 4 DEF bits 4 IN bits 4 OUT bits 4 DYN bits
&Switch_str, SwitchFields,// 1010111 1 DEF bits 1 IN bits 1 OUT bits 0 DYN bits
&TermCap_str, NULL,// 1011000 0 DEF bits 1 IN bits 1 OUT bits 0 DYN bits
&Text_str, TextFields,// 1011001 2 DEF bits 2 IN bits 2 OUT bits 1 DYN bits
&TextureCoordinate_str, NULL,// 1011010 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
&TextureTransform_str, NULL,// 1011011 2 DEF bits 2 IN bits 2 OUT bits 2 DYN bits
&TimeSensor_str, TimeSensorFields,// 1011100 3 DEF bits 3 IN bits 4 OUT bits 0 DYN bits
&TouchSensor_str, NULL,// 1011101 0 DEF bits 0 IN bits 3 OUT bits 0 DYN bits
&Transform_str, NULL,// 1011110 3 DEF bits 3 IN bits 3 OUT bits 3 DYN bits
&Transform2D_str, Transform2DFields,// 1011111 3 DEF bits 3 IN bits 3 OUT bits 3 DYN bits
&Valuator_str, ValuatorFields,// 1100000 4 DEF bits 5 IN bits 5 OUT bits 0 DYN bits
&Viewpoint_str, NULL,// 1100001 3 DEF bits 3 IN bits 3 OUT bits 2 DYN bits
&VisibilitySensor_str, NULL,// 1100010 2 DEF bits 2 IN bits 3 OUT bits 1 DYN bits
&Viseme_str, NULL,// 1100011 2 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
&WorldInfo_str, WorldInfoFields,
};

enum
{
PROTO,
AcousticMaterial,
AcousticScene,
ApplicationWindow,
BAP,
BDP,
Body,
BodyDefTable,
BodySegmentConnectionHint,
DirectiveSound,
Hierarchical3DMesh,
MaterialKey,
PerceptualParameters,
};

ImmutableString<WCHAR> AcousticMaterial_str(L"AcousticMaterial");
ImmutableString<WCHAR> AcousticScene_str(L"AcousticScene");
ImmutableString<WCHAR> ApplicationWindow_str(L"ApplicationWindow");
ImmutableString<WCHAR> BAP_str(L"BAP");
ImmutableString<WCHAR> BDP_str(L"BDP");
ImmutableString<WCHAR> Body_str(L"Body");
ImmutableString<WCHAR> BodyDefTable_str(L"BodyDefTable");
ImmutableString<WCHAR> BodySegmentConnectionHint_str(L"BodySegmentConnectionHint");
ImmutableString<WCHAR> DirectiveSound_str(L"DirectiveSound");
ImmutableString<WCHAR> Hierarchical3DMesh_str(L"Hierarchical3DMesh");
ImmutableString<WCHAR> MaterialKey_str(L"MaterialKey");
ImmutableString<WCHAR> PerceptualParameters_str(L"PerceptualParameters");

Node nodesExt[] =
{
	NULL, NULL,//PROTO 0001
	&AcousticMaterial_str, NULL,// 0010 4 DEF bits 3 IN bits 3 OUT bits 3 DYN bits
	&AcousticScene_str, NULL,// 0011 3 DEF bits 1 IN bits 1 OUT bits 1 DYN bits
	&ApplicationWindow_str, NULL,// 0100 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
	&BAP_str, NULL,// 0101 9 DEF bits 9 IN bits 9 OUT bits 0 DYN bits
	&BDP_str, NULL,// 0110 1 DEF bits 1 IN bits 1 OUT bits 0 DYN bits
	&Body_str, NULL,// 0111 2 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
	&BodyDefTable_str, NULL,// 1000 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
	&BodySegmentConnectionHint_str, NULL,// 1001 2 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
	&DirectiveSound_str, NULL,// 1010 4 DEF bits 3 IN bits 3 OUT bits 2 DYN bits
	&Hierarchical3DMesh_str, NULL,// 1011 1 DEF bits 1 IN bits 1 OUT bits 0 DYN bits
	&MaterialKey_str, NULL,// 1100 3 DEF bits 3 IN bits 3 OUT bits 2 DYN bits
	&PerceptualParameters_str, NULL,// 1101 5 DEF bits 5 IN bits 5 OUT bits 5 DYN bits
};

NodeDataTypeNode SFTopNodeNodes[] =
{
Group, 0, 2, 0,// OUT bits 0 DYN bits
Layer2D, 2, 3, 2,// OUT bits 0 DYN bits
Layer3D, 3, 3, 3,// OUT bits 0 DYN bits
OrderedGroup, 1, 2, 1,// OUT bits 0 DYN bits
};

NodeDataTypeNode SF2DNodeNodes[] =
{
Anchor,							2, 3, 2,// 00001 2 DEF bits 3 IN bits 2 OUT bits 0 DYN bits
AnimationStream,				3, 3, 3,// 00010 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
Background2D,					1, 2, 2,// 00011 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
ColorInterpolator,			1, 2, 2,// 00100 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
Conditional,					0, 2, 1,// 00101 0 DEF bits 2 IN bits 1 OUT bits 0 DYN bits
CoordinateInterpolator2D,	1, 2, 2,// 00110 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
DiscSensor,						3, 3, 3,// 00111 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
Face,								3, 3, 3,// 01000 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
Form,								3, 3, 3,// 01001 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
Group,							0, 2,	0,// 01010 0 DEF bits 2 IN bits 0 OUT bits 0 DYN bits
Inline,							0, 0, 0,// 01011 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
LOD,								2, 0, 0,// 01100 2 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
Layer2D,							2, 3,	2,// 01101 2 DEF bits 3 IN bits 2 OUT bits 0 DYN bits
Layer3D,							3, 3, 3,// 01110 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
Layout,							4, 4, 4,// 01111 4 DEF bits 4 IN bits 4 OUT bits 2 DYN bits
OrderedGroup,					1, 2, 1,// 10000 1 DEF bits 2 IN bits 1 OUT bits 0 DYN bits
PlaneSensor2D,					3, 3, 3,// 10001 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
PositionInterpolator2D,		1, 2, 2,// 10010 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
ProximitySensor2D,			2, 2, 3,// 10011 2 DEF bits 2 IN bits 3 OUT bits 0 DYN bits
QuantizationParameter,		6, 0, 0,// 10100 6 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
ScalarInterpolator,			1, 2, 2,// 10101 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
Script,							2, 0, 0,// 10110 2 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
Shape,							1, 1, 1,// 10111 1 DEF bits 1 IN bits 1 OUT bits 0 DYN bits
Sound2D,							2, 2, 2,// 11000 2 DEF bits 2 IN bits 2 OUT bits 1 DYN bits
Switch,							1, 1, 1,// 11001 1 DEF bits 1 IN bits 1 OUT bits 0 DYN bits
TermCap,							0, 1, 1,// 11010 0 DEF bits 1 IN bits 1 OUT bits 0 DYN bits
TimeSensor,						3, 3, 4,// 11011 3 DEF bits 3 IN bits 4 OUT bits 0 DYN bits
TouchSensor,					0, 0, 3,// 11100 0 DEF bits 0 IN bits 3 OUT bits 0 DYN bits
Transform2D,					3, 3, 3,// 11101 3 DEF bits 3 IN bits 3 OUT bits 3 DYN bits
Valuator,						4, 5, 5,// 11110 4 DEF bits 5 IN bits 5 OUT bits 0 DYN bits
WorldInfo,						1, 0, 0,// 11111 1 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
};

NodeDataTypeNode SF3DNodeNodes[] =
{
Anchor,							2, 3, 2,// 000001 2 DEF bits 3 IN bits 2 OUT bits 0 DYN bits
AnimationStream,				3, 3, 3,// 000010 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
Background,						4, 4, 4,// 000011 4 DEF bits 4 IN bits 4 OUT bits 2 DYN bits
Background2D,					1, 2, 2,// 000100 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
Billboard,						1, 2, 1,// 000101 1 DEF bits 2 IN bits 1 OUT bits 0 DYN bits
Collision,						2, 2, 2,// 000110 2 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
ColorInterpolator,			1, 2, 2,// 000111 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
Conditional,					0, 2, 1,// 001000 0 DEF bits 2 IN bits 1 OUT bits 0 DYN bits
CoordinateInterpolator,		1, 2, 2,// 001001 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
CoordinateInterpolator2D,	1, 2, 2,// 001010 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
CylinderSensor,				3, 3, 4,// 001011 3 DEF bits 3 IN bits 4 OUT bits 0 DYN bits
DirectionalLight,				3, 3, 3,// 001100 3 DEF bits 3 IN bits 3 OUT bits 2 DYN bits
DiscSensor,						3, 3, 3,// 001101 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
Face,								3, 3, 3,// 001110 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
Fog,								2, 2, 2,// 001111 2 DEF bits 2 IN bits 2 OUT bits 1 DYN bits
Form,								3, 3, 3,// 010000 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
Group,							0, 2, 0,// 010001 0 DEF bits 2 IN bits 0 OUT bits 0 DYN bits
Inline,							0, 0, 0,// 010010 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
LOD,								2, 0, 0,// 010011 2 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
Layer2D,							2, 3, 2,// 010100 2 DEF bits 3 IN bits 2 OUT bits 0 DYN bits
Layer3D,							3, 3, 3,// 010101 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
Layout,							4, 4, 4,// 010110 4 DEF bits 4 IN bits 4 OUT bits 2 DYN bits
ListeningPoint,				2, 2, 3,// 010111 2 DEF bits 2 IN bits 3 OUT bits 1 DYN bits
NavigationInfo,				3, 3, 3,// 011000 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
NormalInterpolator,			1, 2, 2,// 011001 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
OrderedGroup,					1, 2, 1,// 011010 1 DEF bits 2 IN bits 1 OUT bits 0 DYN bits
OrientationInterpolator,	1, 2, 2,// 011011 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
PlaneSensor,					3, 3, 3,// 011100 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
PlaneSensor2D,					3, 3, 3,// 011101 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
PointLight,						3, 3, 3,// 011110 3 DEF bits 3 IN bits 3 OUT bits 3 DYN bits
PositionInterpolator,		1, 2, 2,// 011111 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
PositionInterpolator2D,		1, 2, 2,// 100000 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
ProximitySensor2D,			2, 2, 3,// 100001 2 DEF bits 2 IN bits 3 OUT bits 0 DYN bits
ProximitySensor,				2, 2, 3,// 100010 2 DEF bits 2 IN bits 3 OUT bits 0 DYN bits
QuantizationParameter,		6, 0, 0,// 100011 6 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
ScalarInterpolator,			1, 2, 2,// 100100 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
Script,							2, 0, 0,// 100101 2 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
Shape,							1, 1, 1,// 100110 1 DEF bits 1 IN bits 1 OUT bits 0 DYN bits
Sound,							4, 4, 4,// 100111 4 DEF bits 4 IN bits 4 OUT bits 3 DYN bits
Sound2D,							2, 2, 2,// 101000 2 DEF bits 2 IN bits 2 OUT bits 1 DYN bits
SphereSensor,					2, 2, 3,// 101001 2 DEF bits 2 IN bits 3 OUT bits 0 DYN bits
SpotLight,						4, 4, 4,// 101010 4 DEF bits 4 IN bits 4 OUT bits 4 DYN bits
Switch,							1, 1, 1,// 101011 1 DEF bits 1 IN bits 1 OUT bits 0 DYN bits
TermCap,							0, 1, 1,// 101100 0 DEF bits 1 IN bits 1 OUT bits 0 DYN bits
TimeSensor,						3, 3, 4,// 101101 3 DEF bits 3 IN bits 4 OUT bits 0 DYN bits
TouchSensor,					0, 0, 3,// 101110 0 DEF bits 0 IN bits 3 OUT bits 0 DYN bits
Transform,						3, 3, 3,// 101111 3 DEF bits 3 IN bits 3 OUT bits 3 DYN bits
Transform2D,					3, 3, 3,// 110000 3 DEF bits 3 IN bits 3 OUT bits 3 DYN bits
Valuator,						4, 5, 5,// 110001 4 DEF bits 5 IN bits 5 OUT bits 0 DYN bits
Viewpoint,						3, 3, 3,// 110010 3 DEF bits 3 IN bits 3 OUT bits 2 DYN bits
VisibilitySensor,				2, 2, 3,// 110011 2 DEF bits 2 IN bits 3 OUT bits 1 DYN bits
WorldInfo,						1, 0, 0,// 110100 1 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
};

NodeDataTypeNode SFAppearanceNodes[] =
{
Appearance, 2, 2, 2,//1 2 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
};

NodeDataTypeNode SFGeometryNodes[] =
{
Bitmap,				0, 0, 0,// 00001 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
Box,					0, 0, 0,// 00010 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
Circle,				0, 0, 0,// 00011 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
Cone,					2, 0, 0,// 00100 2 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
Curve2D,				2, 2, 2,// 00101 2 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
Cylinder,			3, 0, 0,// 00110 3 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
ElevationGrid,		4, 2, 2,// 00111 4 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
Extrusion,			4, 2, 0,// 01000 4 DEF bits 2 IN bits 0 OUT bits 0 DYN bits
IndexedFaceSet,	4, 3, 2,// 01001 4 DEF bits 3 IN bits 2 OUT bits 0 DYN bits
IndexedFaceSet2D, 3, 3, 2,// 01010 3 DEF bits 3 IN bits 2 OUT bits 0 DYN bits
IndexedLineSet,	3, 2, 1,// 01011 3 DEF bits 2 IN bits 1 OUT bits 0 DYN bits
IndexedLineSet2D, 3, 2, 1,// 01100 3 DEF bits 2 IN bits 1 OUT bits 0 DYN bits
PointSet,			1, 1, 1,// 01101 1 DEF bits 1 IN bits 1 OUT bits 0 DYN bits
PointSet2D,			1, 1, 1,// 01110 1 DEF bits 1 IN bits 1 OUT bits 0 DYN bits
bifsRectangle,		0, 0, 0,// 01111 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
Sphere,				0, 0, 0,// 10000 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
Text,					2, 2, 2,// 10001 2 DEF bits 2 IN bits 2 OUT bits 1 DYN bits
};

NodeDataTypeNode SFMaterialNodes[] =
{
Material,		3, 3, 3,// 01 3 DEF bits 3 IN bits 3 OUT bits 3 DYN bits
Material2D,		2, 2, 2,// 10 2 DEF bits 2 IN bits 2 OUT bits 1 DYN bits
};

NodeDataTypeNode SFTextureNodeNodes[] =
{
CompositeTexture2D,	3, 3, 3,// 001 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
CompositeTexture3D,	3, 4, 3,// 010 3 DEF bits 4 IN bits 3 OUT bits 0 DYN bits
ImageTexture,			2, 0, 0,// 011 2 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
MovieTexture,			3, 3, 3,// 100 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
PixelTexture,			2, 0, 0,// 101 2 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
};

NodeDataTypeNode SFLinePropertiesNodeNodes[] =
{
LineProperties,	2, 2, 2,//1 2 DEF bits 2 IN bits 2 OUT bits 1 DYN bits
};

NodeDataTypeNode SFCoordinate2DNodeNodes[] =
{
Coordinate2D,		0, 0, 0,// 1 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
};

NodeDataTypeNode SFAudioNodeNodes[] =
{
AudioBuffer,		3, 3, 4,// 001 3 DEF bits 3 IN bits 4 OUT bits 0 DYN bits
AudioClip,			3, 3, 3,// 010 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
AudioDelay,			2, 2, 1,// 011 2 DEF bits 2 IN bits 1 OUT bits 0 DYN bits
AudioFX,				3, 3, 2,// 100 3 DEF bits 3 IN bits 2 OUT bits 0 DYN bits
AudioMix,			3, 3, 2,// 101 3 DEF bits 3 IN bits 2 OUT bits 0 DYN bits
AudioSource,		3, 3, 3,// 110 3 DEF bits 3 IN bits 3 OUT bits 1 DYN bits
AudioSwitch,		2, 2, 1,// 111 2 DEF bits 2 IN bits 1 OUT bits 0 DYN bits
};

NodeDataTypeNode SFColorNodeNodes[] =
{
Color,				0, 0, 0// 0 OUT bits 0 DYN bits
};

NodeDataTypeNode SFTextureCoordinateNodeNodes[] =
{
TextureCoordinate, 0, 0, 0,// 0 OUT bits 0 DYN bits
};

NodeDataTypeNode SFFontStyleNodeNodes[] =
{
FontStyle, 4, 0, 0,// 4 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
};

NodeDataType nodeDataTypes[] =
{
	-1, NULL, //BIFS_MFBool, 
	-1, NULL, //BIFS_MFColor, 
	-1, NULL, //BIFS_MFColorRGBA,
	-1, NULL, //BIFS_MFDouble,
	-1, NULL, //BIFS_MFFloat, 
	-1, NULL, //BIFS_MFImage, 
	-1, NULL, //BIFS_MFInt32, 
	-1, NULL, //BIFS_MFNode, 
	-1, NULL, //BIFS_MFRotation, 
	-1, NULL, //BIFS_MFString, 
	-1, NULL, //BIFS_MFTime, 
	-1, NULL, //BIFS_MFVec2d, 
	-1, NULL, //BIFS_MFVec2f, 
	-1, NULL, //BIFS_MFVec3d, 
	-1, NULL, //BIFS_MFVec3f, 

	-1, NULL, //BIFS_MFURL
	-1, NULL, //BIFS_MFCommandBuffer
	-1, NULL, //BIFS_MFScript
	-1, NULL, //BIFS_MFTopNode,
	-1, NULL, //BIFS_MF2DNode,
	-1, NULL, //BIFS_MF3DNode,
	-1, NULL, //BIFS_MFAppearanceNode,
	-1, NULL, //BIFS_MFGeometryNode,
	-1, NULL, //BIFS_MFMaterialNode,
	-1, NULL, //BIFS_MFTextureNode,
	-1, NULL, //BIFS_MFTextureTransform,
	-1, NULL, //BIFS_MFLinePropertiesNode
	-1, NULL, //BIFS_MFCoordinate2DNode
	-1, NULL, //BIFS_MFAudioNode
	-1, NULL, //BIFS_MFColorNode
	-1, NULL, //BIFS_MFTextureCoordinateNode
	-1, NULL, //BIFS_MFFontStyleNode

	-1, NULL, //BIFS_SFBool, 
	-1, NULL, //BIFS_SFColor, 
	-1, NULL, //BIFS_SFColorRGBA, 
	-1, NULL, //BIFS_SFDouble, 
	-1, NULL, //BIFS_SFFloat, 
	-1, NULL, //BIFS_SFImage, 
	-1, NULL, //BIFS_SFInt32, 
	-1, NULL, //BIFS_SFNode, 
	-1, NULL, //BIFS_SFRotation, 
	-1, NULL, //BIFS_SFString, 
	-1, NULL, //BIFS_SFTime, 
	-1, NULL, //BIFS_SFVec2d, 
	-1, NULL, //BIFS_SFVec2f, 
	-1, NULL, //BIFS_SFVec3d, 
	-1, NULL, //BIFS_SFVec3f,

	-1, NULL, //BIFS_SFURL
	-1, NULL, //BIFS_SFCommandBuffer
	-1, NULL, //BIFS_SFScript
	3/*nbits*/, SFTopNodeNodes,
	5/*nbits*/, SF2DNodeNodes,
	6/*nbits*/, SF3DNodeNodes,
	1/*nbits*/, SFAppearanceNodes,
	5/*nbits*/, SFGeometryNodes,
	2/*nbits*/, SFMaterialNodes,
	3/*nbits*/, SFTextureNodeNodes,
	-1, NULL, //BIFS_SFTextureTransform,
	1/*nbits*/, SFLinePropertiesNodeNodes,
	1/*nbits*/, SFCoordinate2DNodeNodes,
	3/*nbits*/, SFAudioNodeNodes,
	1/*nbits*/, SFColorNodeNodes,
	1/*nbits*/, SFTextureCoordinateNodeNodes,
	1/*nbits*/, SFFontStyleNodeNodes,
};

// EXT

NodeDataTypeNode SF2DNodeExtNodes[] =
{
-1, //PROTO 01
ApplicationWindow,// 10 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
Body// 11 2 DEF bits 2 IN bits 2 OUT bits N bits
};

NodeDataTypeNode SF3DNodeExtNodes[] =
{
-1,//PROTO 001
AcousticScene,// 010 3 DEF bits 1 IN bits 1 OUT bits 1 DYN bits
Body,// 011 2 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
DirectiveSound,// 100 4 DEF bits 3 IN bits 3 OUT bits 2 DYN bits
Hierarchical3DMesh,// 101 1 DEF bits 1 IN bits 1 OUT bits bits};
};

NodeDataType nodeDataTypesExt[] =
{
	-1, NULL, //BIFS_MFBool, 
	-1, NULL, //BIFS_MFColor, 
	-1, NULL, //BIFS_MFColorRGBA,
	-1, NULL, //BIFS_MFDouble,
	-1, NULL, //BIFS_MFFloat, 
	-1, NULL, //BIFS_MFImage, 
	-1, NULL, //BIFS_MFInt32, 
	-1, NULL, //BIFS_MFNode, 
	-1, NULL, //BIFS_MFRotation, 
	-1, NULL, //BIFS_MFString, 
	-1, NULL, //BIFS_MFTime, 
	-1, NULL, //BIFS_MFVec2d, 
	-1, NULL, //BIFS_MFVec2f, 
	-1, NULL, //BIFS_MFVec3d, 
	-1, NULL, //BIFS_MFVec3f, 

	-1, NULL, //BIFS_MFURL
	-1, NULL, //BIFS_MFTopNode,
	-1, NULL, //BIFS_MF2DNode,
	-1, NULL, //BIFS_MF3DNode,
	-1, NULL, //BIFS_MFAppearanceNode,
	-1, NULL, //BIFS_MFGeometryNode,
	-1, NULL, //BIFS_MFMaterialNode,
	-1, NULL, //BIFS_MFTextureNode,
	-1, NULL, //BIFS_MFTextureTransform,
	-1, NULL, //BIFS_MFLinePropertiesNode
	-1, NULL, //BIFS_MFCoordinate2DNode
	-1, NULL, //BIFS_MFAudioNode
	-1, NULL, //BIFS_MFColorNode
	-1, NULL, //BIFS_MFTextureCoordinateNode

	-1, NULL, //BIFS_SFBool, 
	-1, NULL, //BIFS_SFColor, 
	-1, NULL, //BIFS_SFColorRGBA, 
	-1, NULL, //BIFS_SFDouble, 
	-1, NULL, //BIFS_SFFloat, 
	-1, NULL, //BIFS_SFImage, 
	-1, NULL, //BIFS_SFInt32, 
	-1, NULL, //BIFS_SFNode, 
	-1, NULL, //BIFS_SFRotation, 
	-1, NULL, //BIFS_SFString, 
	-1, NULL, //BIFS_SFTime, 
	-1, NULL, //BIFS_SFVec2d, 
	-1, NULL, //BIFS_SFVec2f, 
	-1, NULL, //BIFS_SFVec3d, 
	-1, NULL, //BIFS_SFVec3f,

	-1, NULL, //BIFS_MFURL
	-1/*nbits*/, NULL,//SFTopNodeNodes,
	2/*nbits*/, SF2DNodeExtNodes,
	3/*nbits*/, SF3DNodeExtNodes,

	-1/*nbits*/, NULL,//SFAppearanceNodes,
	-1/*nbits*/, NULL,//SFGeometryNodes,
	-1/*nbits*/, NULL,//SFMaterialNodes,
	-1/*nbits*/, NULL,//SFTextureNodeNodes,
	-1, NULL, //BIFS_SFTextureTransform,
	-1/*nbits*/, NULL,//SFLinePropertiesNodeNodes,
	-1/*nbits*/, NULL,//SFCoordinate2DNodeNodes,
	-1/*nbits*/, NULL,//SFAudioNodeNodes,
	-1/*nbits*/, NULL,//SFColorNodeNodes,
	-1/*nbits*/, NULL,//SFTextureCoordinateNodeNodes,
};

/*
Returns the nodeType of the node indexed by localNodeType in the node data type table. The nodeType of a
node is its index in the SFWorldNode NDT Table.
*/
int GetNodeType(int nodeDataType, int localNodeType)
{
	return nodeDataTypes[nodeDataType].nodes[localNodeType-1].index;
}

int GetExtNodeType(int nodeDataType, int extlocalNodeType)
{
	return nodeDataTypesExt[nodeDataType].nodes[extlocalNodeType-1].index;
}

/*
Returns the number of bits used to index the nodes of the matching node data type table (this number is indicated
in the last column of the first row of the node data type table).
*/
int GetNDTnbBits(int nodeDataType)
{
	return nodeDataTypes[nodeDataType].nbits;
}

int GetNDTnbBitsExt(int nodeDataType)
{
	return nodeDataTypesExt[nodeDataType].nbits;
}

////////////////////////////////////////////////////

/*
Table 19 - Quantization Categories
Category Description
0 None
1 3D position
2 2D positions
3 Drawing order
4 SFColor
5 Texture Coordinate
6 Angle
7 Scale
8 Interpolator keys
9 Normals
10 Rotations
11 Object Size 3D (1)
12 Object Size 2D (2)
13 Linear Scalar Quantization
14 CoordIndex
15 Reserved

*/

// use double for Vmin and Vmax to get higher precision in the calculations

int quantize(double Vmin, double Vmax, float v, int Nb)
{
	return (int)(((v - Vmin) / (Vmax - Vmin)) * ((2<<Nb) -1));
}

float invQuantize(double Vmin, double Vmax, int vq, int Nb)
{
//	return Vmin + vq * ((Vmax - Vmin) / ((1<<(max(Nb,1))) -1));
	return Vmin + vq * ((Vmax - Vmin) / (pow(2.0,MAX(Nb,1)) -1));
}

void ReadQuantizedField(System::IO::CBitStream32* pBitStream, FieldData& fieldData, int comps, int vq[])
{
	switch (fieldData.field->quantType)
	{
	case 9:
		{
			int direction = pBitStream->getbit();
		}
		break;

	case 10:
		{
			int orientation = pBitStream->getnbits(2);
		}
		break;
	}

	/*
	for (int i = 0; i < getNbComp(field);i++)
	{
		int(field.nbBits) vq[i]
	}
	*/
	for (int i = 0; i < comps; i++)
	{
		//int(field.nbBits) vq[i]
		vq[i] = pBitStream->getnbits(fieldData.nbBits);
	}
}

float ReadEfficientFloat(System::IO::CBitStream32* pBitStream)
{
	ASSERT(0);

	int mantissaLength = pBitStream->getnbits(4);
	if (mantissaLength != 0)
	{
#if 0
		int exponentLength = pBitStream->getnbits(3);
		int mantissaSign = pBitStream->getbit();
		int mantissa = pBitStream->getnbits(mantissaLength-1);

		int exponentSign;
		int exponent;

		if (exponentLength != 0)
		{
			exponentSign = pBitStream->getbit();
			exponent = pBitStream->getnbits(exponentLength-1);
		}
		else
		{
			exponent = 0;
		}

		(1-2*mantissaSign)*(pow(2, mantissaLength-1)+mantissa) * pow(2, (1-2*exponentSign)*(pow(2, exponentLength-1)+exponent));
#endif
	return 0;
	}
	else
	{
		return 0;
	}
}

class number
{
public:
	number(int v)
	{
	}

	number(float v)
	{
	}

	union
	{
		int intv;
		float floatv;
	}
	value;
};

number ReadNumber(System::IO::CBitStream32* pBitStream)
{
	int isInteger = pBitStream->getbit();
	if (isInteger)
	{
		int numbits = pBitStream->getnbits(5);  // number of bits the integer is represented
		long value = pBitStream->getnbits(numbits);// integer value

		return value;
	}
	else
	{
		int floatChar = pBitStream->getnbits(4); // 0-9, ., E,-, END_SYMBOL
		while (floatChar!= 13/*END_SYMBOL*/)
		{
			floatChar = pBitStream->getnbits(4);
		}
		return (long)0;	// TODO
	}
}

float ReadGenericFloat(System::IO::CBitStream32* pBitStream, bool useEfficientCoding)
{
	if (!useEfficientCoding)
	{
		uint32 value = pBitStream->getnbits(32);
		float fvalue = *(float*)&value;

		return fvalue;
	}
	else
	{
		ASSERT(0);
	//	EfficientFloat value;
		return 0;
	}
}

void ReadSFBool(System::IO::CBitStream32* pBitStream, bool* pVal)
{
	ASSERT(pVal != NULL);
	*pVal = pBitStream->getbit();
}

void ReadSFInt32(System::IO::CBitStream32* pBitStream, FieldData& fieldData, long* pVal)
{
	ASSERT(pVal != NULL);
	if (fieldData.isQuantized)
	{
		int vq[1];
		ReadQuantizedField(pBitStream, fieldData, 1, vq);

		*pVal = fieldData.intMin[0] + vq[0];

		ASSERT(*pVal >= fieldData.field->m && *pVal <= fieldData.field->M);

#if 0
		*pVal = invQuantize(fieldData.floatMin[0], fieldData.floatMax[0], vq[0], fieldData.nbBits);
#endif
	}
	else
	{
		*pVal = pBitStream->getnbits(32);
	}

//	TRACE("int32: %d\n", *pVal);
}

void ReadSFFloat(System::IO::CBitStream32* pBitStream, FieldData& field, float* pVal)//FieldData field)
{
	ASSERT(pVal != NULL);
	if (field.isQuantized)
	{
		ASSERT(0);
	//	QuantizedField qvalue(field);
	}
	else
	{
		*pVal = ReadGenericFloat(pBitStream, field.useEfficientCoding);
	//	TRACE("float: %g\n", *pVal);
	}
}

void ReadSFTime(System::IO::CBitStream32* pBitStream, FieldData& field, double* pVal)//FieldData field)
{
	ASSERT(pVal != NULL);
	__int64 intvalue = pBitStream->getlonglong();
	*pVal = *(double*)&intvalue;
}

void ReadSFVec2f(System::IO::CBitStream32* pBitStream, FieldData& fieldData, float value[2])
{
	ASSERT(value != NULL);

	if (fieldData.isQuantized)
	{
		int vq[2];
		ReadQuantizedField(pBitStream, fieldData, 2, vq);

		value[0] = invQuantize(fieldData.floatMin[0], fieldData.floatMax[0], vq[0], fieldData.nbBits);
		value[1] = invQuantize(fieldData.floatMin[1], fieldData.floatMax[1], vq[1], fieldData.nbBits);
	}
	else
	{
		value[0] = ReadGenericFloat(pBitStream, fieldData.useEfficientCoding);
		value[1] = ReadGenericFloat(pBitStream, fieldData.useEfficientCoding);
	}

	//TRACE("vec2f: %g, %g\n", value[0], value[1]);
}

void ReadSFVec3f(System::IO::CBitStream32* pBitStream, FieldData& field, float value[3])
{
	ASSERT(value != NULL);

	if (field.isQuantized)
	{
		ASSERT(0);
		//ReadQuantizedField(pBitStream, field);
	}
	else
	{
		value[0] = ReadGenericFloat(pBitStream, field.useEfficientCoding);
		value[1] = ReadGenericFloat(pBitStream, field.useEfficientCoding);
		value[2] = ReadGenericFloat(pBitStream, field.useEfficientCoding);

	//	TRACE("vec2f: %g, %g, %g\n", value[0], value[1], value[2]);
	}
}

void ReadSFColor(System::IO::CBitStream32* pBitStream, FieldData& field, float value[3])
{
	ASSERT(value != NULL);

	if (field.isQuantized)
	{
		ASSERT(0);
		//QuantizedField qvalue(field);
	}
	else
	{
		value[0] = ReadGenericFloat(pBitStream, field.useEfficientCoding);
		value[1] = ReadGenericFloat(pBitStream, field.useEfficientCoding);
		value[2] = ReadGenericFloat(pBitStream, field.useEfficientCoding);

		TRACE("color: %g, %g, %g\n", value[0], value[1], value[2]);
	}
}

void ReadSFString(System::IO::CBitStream32* pBitStream, FieldData& field)
{
	int lengthBits = pBitStream->getnbits(5);
	if (lengthBits > 0)
	{
		int length = pBitStream->getnbits(lengthBits);

		//char(8) value[length];
		for (int i = 0; i < length; i++)
		{
			pBitStream->getnbits(8);
		}
	}
}

void ReadSFUrl(System::IO::CBitStream32* pBitStream, FieldData& field, long* pODid)
{
	int isOD = pBitStream->getbit();
	if (isOD)
	{
		*pODid = pBitStream->getnbits(10);
	}
	else
	{
		*pODid = 0;
		ReadSFString(pBitStream, field);//SFString urlValue;
	}
}

void ReadSFCommandBuffer(System::IO::CBitStream32* pBitStream)
{
	int lengthBits = pBitStream->getnbits(5);
	int length = pBitStream->getnbits(lengthBits);
	for (int i = 0; i < length; i++)
	{
		uint8 value = pBitStream->getnbits(8);//bit(8) value[length];
	}
}

/*
Table 33 - Field Types for Script fields and PROTO fields.
fieldType value Field type
0bx000000 SFBool
0bx000001 SFFloat
0bx000010 SFTime
0bx000011 SFInt32
0bx000100 SFString
0bx000101 SFVec3f
0bx000110 FVec2f
0bx000111 SFColor
0bx001000 SFRotation
0bx001001 SFImage
0bx001010 SFNode
0bx100000 MFBool
0bx100001 MFFloat
0bx100010 MFTime
0bx100011 MFInt32
0bx100100 MFString
0bx100101 MFVec3f
0bx100110 MFVec2f
0bx100111 MFColor
0bx101000 MFRotation
0bx101001 MFImage
0bx101010 MFNode
*/
BIFSFieldType BIFSFieldTypes[] =
{
	BIFS_MFBool,
	BIFS_MFFloat,
	BIFS_MFTime,
	BIFS_MFInt32,
	BIFS_MFString,
	BIFS_MFVec3f,
	BIFS_MFVec2f,
	BIFS_MFColor,
	BIFS_MFRotation,
	BIFS_MFImage,
	BIFS_MFNode,
	/*
	BIFS_MFBool,
	BIFS_MFFloat,
	BIFS_MFTime,
	BIFS_MFInt32,
	BIFS_MFString,
	BIFS_MFVec3f,
	BIFS_MFVec2f,
	BIFS_MFColor,
	BIFS_MFRotation,
	BIFS_MFImage,
	BIFS_MFNode,
	*/
};

x3d::FieldType FieldTypes[] =
{
	x3d::FieldType_MFBool,
	x3d::FieldType_MFFloat,
	x3d::FieldType_MFTime,
	x3d::FieldType_MFInt32,
	x3d::FieldType_MFString,
	x3d::FieldType_MFVec3f,
	x3d::FieldType_MFVec2f,
	x3d::FieldType_MFColor,
	x3d::FieldType_MFRotation,
	x3d::FieldType_MFImage,
	x3d::FieldType_MFNode,
	/*
	MFBool,
	MFFloat,
	MFTime,
	MFInt32,
	MFString,
	MFVec3f,
	MFVec2f,
	MFColor,
	MFRotation,
	MFImage,
	MFNode,
	*/
};

#if 0
void BIFSDec::ReadScriptField(System::IO::CBitStream32* pBitStream, CScriptNode& scriptNode, NodeData& nodeData)
{
	int eventType = pBitStream->getnbits(2);	// 0, 1, and 2 representing fields, eventIns and eventOuts,
	int fieldType = pBitStream->getnbits(6);
	CWCharString fieldName = ReadString(pBitStream);//String;

	if (eventType == 0)
	{
		scriptNode.m_INFields++;
		scriptNode.m_OUTFields++;
	}
	else if (eventType == 1)
	{
		scriptNode.m_INFields++;
	}
	else if (eventType == 2)
	{
		scriptNode.m_OUTFields++;
	}

	if (eventType == 0/*FIELD*/)
	{
		int hasInitialValue = pBitStream->getbit();
		if (hasInitialValue)
		{
#if 0
			NodeData node = makeNode(ScriptNodeType);
			Field(node.field[fieldType]) value;
#endif
			Field field;
			field.name = fieldName;

			field.fieldType = BIFSFieldTypes[fieldType & ~0x20];
			if (!(fieldType & 0x20))	// SF
				field.fieldType = (BIFSFieldType)((int)field.fieldType + (int)BIFS_SFBool);

			FieldType ftype = FieldTypes[fieldType & ~0x20];
			if (!(fieldType & 0x20))	// SF
				ftype = (FieldType)((int)ftype + (int)SFBool);

			FieldData fieldData;
			fieldData.field = &field;

			CComPtr<ILX3DField> x3dfield;
			CComQIPtr<ILX3DScriptNode>(nodeData.x3dnode)->createField(fieldName, ftype, &x3dfield);

			ReadField(pBitStream, nodeData, fieldData, x3dfield, NULL, FALSE);
		}
	}

	if (TRUE)
	{
		CIdentifier identifier;
		identifier.m_name = fieldName;
		scriptNode.m_identifiers.Add(identifier);
	}
}

void BIFSDec::ReadScriptFieldsListDescription(System::IO::CBitStream32* pBitStream, CScriptNode& scriptNode, NodeData& nodeData)
{
	int endFlag = pBitStream->getbit(); // List description of the fields
	while (!endFlag)
	{
		ReadScriptField(pBitStream, scriptNode, nodeData);
		endFlag = pBitStream->getbit();//bit(1) endFlag;
	}
}

void BIFSDec::ReadScriptFieldsVectorDescription(System::IO::CBitStream32* pBitStream, CScriptNode& scriptNode, NodeData& nodeData)
{
	int fieldBits = pBitStream->getnbits(4); // Number of bits for number of fields

	int numFields = pBitStream->getnbits(fieldBits); // Number of fields in the script
	for (int i = 0; i < numFields; i++)
	{
		ReadScriptField(pBitStream, scriptNode, nodeData);
	}
}

sysstring BIFSDec::ReadIdentifier(System::IO::CBitStream32* pBitStream, CScriptNode& scriptNode)
{
	int received = pBitStream->getbit();
	if (received)
	{
		int num = GetNBits(scriptNode.m_identifiers.GetSize());
		int identifierCode = pBitStream->getnbits(num);// identifierCode // num is calculated by counting

		ASSERT(identifierCode < scriptNode.m_identifiers.GetSize());

	// number of distinguished identifiers
	// received so far
		TRACE("identifier reuse: %d\n", identifierCode);

		return scriptNode.m_identifiers[identifierCode].m_name;
	}
	else
	{
		CIdentifier identifier;
		identifier.m_name = ReadString(pBitStream);
		scriptNode.m_identifiers.Add(identifier);

		TRACE("identifier: %S\n", (BSTR)identifier.m_name);

		return identifier.m_name;
	}
}

void BIFSDec::ReadArguments(System::IO::CBitStream32* pBitStream, CScriptNode& scriptNode)
{
	int hasArgument = pBitStream->getbit();

	while (hasArgument)
	{
		ReadIdentifier(pBitStream, scriptNode);/// identifier;
		hasArgument = pBitStream->getbit();
	}
}

enum
{
	ifStatementType = 0,
	forStatementType = 1,
	whileStatementType = 2,
	returnStatementType = 3,
	compoundExpressionType = 4,
	breakStatementType = 5,
	continueStatementType = 6,
	switchStatementType = 7,
};

void BIFSDec::ReadParams(System::IO::CBitStream32* pBitStream, CScriptNode& scriptNode)
{
	int hasParam = pBitStream->getbit();
	while(hasParam)
	{
		ReadExpression(pBitStream, scriptNode);// expression;
		hasParam = pBitStream->getbit();
	}
}

/*
curvedExpressionType=0:
The expression consists of a compoundExpression.
NegativeExpressionType=1:
An expression shall be evaluated and the value returned shall be negated.
NotExpressionType=2:
An expression shall be evaluated and its returned value shall be logically negated (empty values return nonempty,
zero values return non-zero, and vice-versa).
OnescompExpressionType=3:
An expression shall be evaluated numerically (string values will yield an undefined result) and the value returned
shall be bitwise negated.
IncrementExpressionType=4:
An expression shall be evaluated numerically (string values will yield an undefined result) and the value returned
shall incremented by 1.
DecrementExpressionType=5:
An expression shall be evaluated numerically (string values will yield an undefined result) and the value returned
shall be decremented by 1.
PostIncrementExpressionType=6:
An expression shall be evaluated numerically (string values will yield an undefined result) and its returned value
shall be incremented by 1. The returned value of this expression shall be the value prior to the increment being
applied.
PostDecrementExpressionType=7:
An expression shall be evaluated numerically (string values will yield an undefined result) and its returned value
shall be decremented by 1. The returned value of this expression shall be the value prior to the decrement being
applied.
ConditionExpressionType=8:
Three expressions shall be evaluated. If the first expression returns a non-zero or non-empty value, then the
returned value of this expression shall be the value of the second expression. Otherwise, the returned value of
this expression shall be the value of the third expression.
StringExpressonType=9:
The expression contains a string.
NumberExpressionType=10:
The expression is a number.
VariableExpressionType=11:
Licensed to /SIGURD LERSTAD
ISO Store order #: 575943/Downloaded: 2003-12-28
Single user licence only, copying and networking prohibited
ISO/IEC 14496-1:2001(E)
© ISO/IEC 2001 – All rights reserved 123
The expression is a variable and shall return the value held by the variable determined by identifier.
FunctionCallExpressionType=12:
An identifier determines which function shall be evaluated. The params shall be passed to the function
by value. The returned value of the expression shall be the value returned by the function in its
returnStatement.
ObjectConstructExpressionType=13:
A new object shall be created (using a ‘new’ statement in the script) and the object shall be held in the variable
determined by identifier. A list of params shall be passed to any constructors that exist for the object.
ObjectMemberAccessExpressionType=14:
A member variable of an object shall be accessed and the returned value of the expression shall be the value in
this member variable. Normally, the first expression will evaluate to a node in the scene graph (which is
accessed through a script variable). This means that the first expression will normally evaluate to an
identifier reference. The following identifier will then refer to a field of the node.
ObjectMethodCallExpressionType=15:
A method of an object shall be evaluated. The first expression shall evaluate to an object. The following
identifier shall specify a method of this object. The following params shall be passed to the method. The value
of this expression shall be the value returned by the method.
ArrayDereferenceExpressionType=16:
The expression shall be an array element reference. The first expression shall evaluate to an array reference.
The following compoundExpression shall evaluate to a number that shall then be used to index the array. The
returned value of this expression shall be the value held in the referenced array element.
The following binary operands evaluate two expressions and return a value based on a binary operation of these
two expressions. The binary operation and value of expressionType is listed below for each binary operation.
Unless explicitely stated, a string value for either of the expressions will yield an undefined result.
BinaryOperand(=) = 17:
The first expression shall evaluate to an identifier which shall be assigned the value of the second
expression.
BinaryOperand(+=) = 18:
The first expression shall evaluate to an identifier. If the value held by the variable is numerical, the variable
value shall be incremented by the value of the second expression, which shall also evaluate to a numerical
value. If the variable is a string, then its new value shall be its original value with the second expression (which
shall be a string) appended.
BinaryOperand(-=) = 19:
The first expression shall evaluate to an identifier whose value shall be decremented by the value of the
second expression.
BinaryOperand(*=) = 20:
The first expression shall evaluate to an identifier whose value shall be set to its current value multiplied by
the value of the second expression.
BinaryOperand(/=) = 21:
The first expression shall evaluate to an identifier whose value shall be set to its current value divided by
the value of the second expression.
BinaryOperand(%=) = 22:
The first expression shall evaluate to an identifier whose value shall be set to its current value modulo the
value of the second expression. The expressions shall both evaluate to integer values.
BinaryOperand(&=) = 23:
The first expression shall evaluate to an identifier whose value shall be set to its current value logically
bitwise ANDed with the value of the second expression.
BinaryOperand(|=) = 24:
Licensed to /SIGURD LERSTAD
ISO Store order #: 575943/Downloaded: 2003-12-28
Single user licence only, copying and networking prohibited
ISO/IEC 14496-1:2001(E)
124 © ISO/IEC 2001 – All rights reserved
The first expression shall evaluate to an identifier whose value shall be set to its current value logically
bitwise ORed with the value of the second expression.
BinaryOperand(^=) = 25:
The first expression shall evaluate to an identifier whose value shall be set to its current value logically
bitwise EXCLUSIVE-ORed with the value of the second expression.
BinaryOperand(<<=) = 26:
The first expression shall evaluate to an identifier whose value shall be set to its current value bitwise
shifted to the left a number of bits specified by the second expression.
BinaryOperand(>>=) = 27:
The first expression shall evaluate to an identifier whose value shall be set to its current value bitwise
shifted to the right a number of bits specified by the second expression.
BinaryOperand(>>>=) = 28:
The first expression shall evaluate to an identifier whose value shall be set to its current value bitwise
shifted to the right (with the least significant bits looped) a number of bits specified by the second expression.
BinaryOperand(==) = 29:
This expression shall return a non-zero value when the first and second expression are identical. Otherwise, the
result of this expression shall be zero.
BinaryOperand(!=) = 30:
This expression shall return a non-zero value when the first and second expression are not identical. Otherwise,
the result of this expression shall be zero.
BinaryOperand(<) = 31:
This expression shall return a non-zero value when the first expression is numerically or lexicographically less
than the second. Otherwise, the result of this expression shall be zero.
BinaryOperand(<=) = 32:
This expression shall return a non-zero value when the first expression is numerically or lexicographically less
than or equal to the second. Otherwise, the result of this expression shall be zero.
BinaryOperand(>) = 33:
This expression shall return a non-zero value when the first expression is numerically or lexicographically greater
than the second. Otherwise, the result of this expression shall be zero.
BinaryOperan(>=) = 34:
This expression shall return a non-zero value when the first expression is numerically or lexicographically greater
than or equal to the second. Otherwise, the result of this expression shall be zero.
BinaryOperand(+) = 35:
This expression shall return the sum of the first and second expressions. If both expressions are strings, then
the result shall be the first string concatenated with the second.
BinaryOperand(-) = 36:
This expression shall return the difference of the first and second expressions.
BinaryOperand(*) = 37:
This expression shall return the product of the first and second expressions.
BinaryOperand(/) = 38:
This expression shall returns the quotient of the first and second expressions.
BinaryOperand(%) = 39:
This expression shall return the value of the first expression modulo the second expression.
BinaryOperand(&&) = 40:
This expression shall return the logical AND of the first and second expressions.
BinaryOperand(||) = 41:
Licensed to /SIGURD LERSTAD
ISO Store order #: 575943/Downloaded: 2003-12-28
Single user licence only, copying and networking prohibited
ISO/IEC 14496-1:2001(E)
This expression shall return the logical OR of the first and second expressions.
BinaryOperand(&) = 42:
This expression shall return the logical bitwise AND of the first and second expressions.
BinaryOperand(|) = 43:
This expression shall return the logical bitwise OR of the first and second expressions.
BinaryOperand(^) = 44:
This expression shall return the logical bitwise XOR of the first and second expressions.
BinaryOperand(<<) = 45:
This expression shall return the value of the first expression shifted to the left by the number of bits specified as
the value of the second expression.
BinaryOperand(>>) = 46:
Returns the value of the first expression shifted to the right by the number of bits specified as the value of the
second expression.
BinaryOperand(>>>) = 47:
This expression shall return the value of the first expression shifted to the right (with the least significant bit
looped to the most significant bit) by the number of bits specified as the value of the second expression.
*/

NODEP BIFSDec::ReadExpression(System::IO::CBitStream32* pBitStream, CScriptNode& scriptNode)
{
	int expressionType = pBitStream->getnbits(6);

	switch (expressionType)
	{
	case 0://curvedExpressionType: // (compoundExpression)
		{
			ReadCompoundExpression(pBitStream, scriptNode);// compoundExpression;
		}
		break;
		
	case 1://negativeExpressionType: // -expression
	case 2://notExpressionType: // !expression
	case 3://onescompExpressionType: // ~expression
	case 4://incrementExpressionType: // ++expression
	case 5://decrementExpressionType: // --expression
	case 6://postIncrementExpressionType: // expression++
	case 7://postDecrementExpressionType: // expression--
		{
			ReadExpression(pBitStream, scriptNode);// expression;
		}
		break;
		
	case 8://conditionExpressionType: // expression ? expression : expression
		{
			ReadExpression(pBitStream, scriptNode);// expression;
			ReadExpression(pBitStream, scriptNode);// expression;
			ReadExpression(pBitStream, scriptNode);// Expression expression;
		}
		break;
		
	case 9://stringExpressonType:
		{
			//String string;
			NODEP np = allocnode();
			np->e_token = SCON2;
			CWCharString str = ReadString(pBitStream);
			np->e.vu.bstrval = str.copyBSTR();
			
			return np;
		}
		break;
		
	case 10://numberExpressionType:
		{
			NODEP np = allocnode();
			
			_variant_t number = ReadNumber(pBitStream);
			
			if (number.vt == VT_I4)
			{
				np->e_token = ICON;
				np->e_ival = number.lVal;
			}
			else if (number.vt == VT_R8)
			{
				np->e_token = FCON;
				np->e_ival = number.dblVal;
			}
			else
				ASSERT(0);
			
			return np;
		}
		break;
		
	case 11://variableExpressionType:
		{
			ReadIdentifier(pBitStream, scriptNode);// identifier;
		}
		break;
		
	case 12://functionCallExpressionType:
	case 13://objectConstructExpressionType:
		{
			ReadIdentifier(pBitStream, scriptNode);// identifier;
			ReadParams(pBitStream, scriptNode);// params;
		}
		break;
		
	case 14://objectMemberAccessExpressionType:
		{
			ReadExpression(pBitStream, scriptNode);// expression;
			ReadIdentifier(pBitStream, scriptNode);// identifier;
		}
		break;
		
	case 15://objectMethodCallExpressionType:
		{
			ReadExpression(pBitStream, scriptNode);// expression;
			ReadIdentifier(pBitStream, scriptNode);// identifier;
			ReadParams(pBitStream, scriptNode);// params;
		}
		break;
		
	case 16://arrayDereferenceExpressionType:
		{
			ReadExpression(pBitStream, scriptNode);// expression;
			ReadCompoundExpression(pBitStream, scriptNode);// compoundExpression;
		}
		break;
		
	case 17:
	case 18:
	case 19:
	case 20:
	case 21:
	case 22:
	case 23:
	case 24:
	case 25:
	case 26:
	case 27:
	case 28:
	case 29:
	case 30:
	case 31:
	case 32:
	case 33:
	case 34:
	case 35:
	case 36:
	case 37:
	case 38:
	case 39:
	case 40:
	case 41:
	case 42:
	case 43:
	case 44:
	case 45:
	case 46:
	case 47:
		// =, +=, -=, *=, /=, %=, &=, |=, ^=, <<=, >>=, >>>=,
		// ==, !=, <, <=, >, >=, +, -, *, /, %, &&, ||, &, |,
		// ^, <<, >>, >>>
		{
			ReadExpression(pBitStream, scriptNode);// expression;
			ReadExpression(pBitStream, scriptNode);// expression;
		}
		break;
		
	default:
		{
			MessageBeep(-1);
			//	ReadExpression(pBitStream, scriptNode);// expression;
		}
		break;
	}
	
	return NULL;
}

/*
A CompoundExpression is a list of expressions, terminated when hasExpression has value 0. The value of
the compound expression shall be the value of the last evaluated expression.
*/
NODEP BIFSDec::ReadCompoundExpression(System::IO::CBitStream32* pBitStream, CScriptNode& scriptNode)
{
	NODEP np = allocnode();

	int hasExpression;
	do
	{
		NODEP left = ReadExpression(pBitStream, scriptNode);// expression;

		// Npt sure about this
		np->e.left = left;
		np = left;

		hasExpression = pBitStream->getbit();
	}
	while (hasExpression);

	return np;
}

void BIFSDec::ReadOptionalExpression(System::IO::CBitStream32* pBitStream, CScriptNode& scriptNode)
{
	int hasCompoundExpression = pBitStream->getbit();
	if (hasCompoundExpression)
	{
		ReadCompoundExpression(pBitStream, scriptNode);// compoundExpression;
	}
}

void BIFSDec::ReadIFStatement(System::IO::CBitStream32* pBitStream, CScriptNode& scriptNode, CIfStatement& stmt)
{
	stmt.test_expr = ReadCompoundExpression(pBitStream, scriptNode);// compoundExpression;
	ReadStatementBlock(pBitStream, scriptNode, stmt.m_if_block);// statementBlock;

	int hasELSEStatement = pBitStream->getbit();
	if (hasELSEStatement)
	{
		ReadStatementBlock(pBitStream, scriptNode, stmt.m_else_block);// statementBlock;
	}
}

void BIFSDec::ReadFORStatement(System::IO::CBitStream32* pBitStream, CScriptNode& scriptNode, CForStatement& stmt)
{
	ReadOptionalExpression(pBitStream, scriptNode);// optionalExpression;
	ReadOptionalExpression(pBitStream, scriptNode);// optionalExpression;
	ReadOptionalExpression(pBitStream, scriptNode);// optionalExpression;

	ReadStatementBlock(pBitStream, scriptNode, stmt.m_block);// statementBlock;
}

void BIFSDec::ReadRETURNStatement(System::IO::CBitStream32* pBitStream, CScriptNode& scriptNode)
{
	int returnValue = pBitStream->getbit();
	if (returnValue)
	{
		ReadCompoundExpression(pBitStream, scriptNode);// compoundExpression;
	}
}

CStatement* BIFSDec::ReadStatement(System::IO::CBitStream32* pBitStream, CScriptNode& scriptNode)
{
	int statementType = pBitStream->getnbits(3);

	switch (statementType)
	{
	case ifStatementType:
		{
			CIfStatement* pIf = new CIfStatement;

			ReadIFStatement(pBitStream, scriptNode, *pIf);// ifStatement;

			return pIf;
		}
		break;

	case forStatementType:
		{
			CForStatement* pFor = new CForStatement;

			ReadFORStatement(pBitStream, scriptNode, *pFor);// forStatement;

			return pFor;
		}
		break;

	case whileStatementType:
		{
			ASSERT(0);
			MessageBeep(-1);
//		WHILEStatement whileStatement;
		}
		break;

	case returnStatementType:
		{
			ReadRETURNStatement(pBitStream, scriptNode);// returnStatement;
		}
		break;

	case compoundExpressionType:
		{
			ReadCompoundExpression(pBitStream, scriptNode);// compoundExpression;
		}
		break;

	case breakStatementType:
	case continueStatementType:
		{
			MessageBeep(-1);
		}
		break;

	case switchStatementType:
		{
			ASSERT(0);
			MessageBeep(-1);
//			SWITCHStatement switchStatement;
		}
		break;

	default:
		ASSERT(0);
	}

	return NULL;
}

void BIFSDec::ReadStatementBlock(System::IO::CBitStream32* pBitStream, CScriptNode& scriptNode, CStatementBlock& statementBlock)
{
	int isCompoundStatement = pBitStream->getbit();

	if (isCompoundStatement)
	{
		int hasStatement = pBitStream->getbit();
		while (hasStatement)
		{
			CStatement* pStatement = ReadStatement(pBitStream, scriptNode);// statement;
			ASSERT(pStatement);
			statementBlock.m_stmts.AddTail(pStatement);

			hasStatement = pBitStream->getbit();
		}
	}
	else
	{
		CStatement* pStatement = ReadStatement(pBitStream, scriptNode);// statement;
		ASSERT(pStatement);
		statementBlock.m_stmts.AddTail(pStatement);
	}
}

void BIFSDec::ReadFunction(System::IO::CBitStream32* pBitStream, CScriptNode& scriptNode, CScriptItem* pItem)
{
	pItem->m_name = ReadIdentifier(pBitStream, scriptNode);// identifier;

	CComObject<CLScriptFunction>* pFunction;
	CComObject<CLScriptFunction>::CreateInstance(&pFunction);
	pFunction->AddRef();

	pItem->m_disp = pFunction;

	ReadArguments(pBitStream, scriptNode);// arguments;

	ReadStatementBlock(pBitStream, scriptNode, pFunction->m_stmts);// statementBlock;
}

void BIFSDec::ReadEncodedScript(System::IO::CBitStream32* pBitStream, CScriptNode& scriptNode)
{
	int hasFunction = pBitStream->getbit();
	while (hasFunction)
	{
		CScriptItem* pItem = new CScriptItem;

		ReadFunction(pBitStream, scriptNode, pItem);// function;

		scriptNode.m_pEngine->m_pDispatch->m_items.Add(pItem);

		hasFunction = pBitStream->getbit();
	}
}
#endif

void BIFSDec::ReadSFScript(System::IO::CBitStream32* pBitStream, NodeData& nodeData)
{
	ScriptNode scriptNode;
	scriptNode.m_INFields = 0;
	scriptNode.m_OUTFields = 0;

	ASSERT(0);
#if 0
	int isListDescription = pBitStream->getbit();//bit(1);
	if (isListDescription)
	{
		ReadScriptFieldsListDescription(pBitStream, scriptNode, nodeData);
	}
	else
	{
		ReadScriptFieldsVectorDescription(pBitStream, scriptNode, nodeData);
	}

	nodeData.nINbits = GetNBits(scriptNode.m_INFields);
	nodeData.nOUTbits = GetNBits(scriptNode.m_OUTFields);

//	INbits = GetNBits(scriptNode.m_INFields);
//	OUTbits = GetNBits(scriptNode.m_OUTFields);

	int reserved = pBitStream->getbit();//const bit(1) reserved=1;
	ASSERT(reserved == 1);

	ReadEncodedScript(pBitStream, scriptNode);
#endif
}

/////////////////////////////////////////////////////////////////////////////
// BIFSDec

void BIFSDec::ReadChildNode(System::IO::CBitStream32* pBitStream, FieldData& field, int fieldType, x3d::X3DField* x3dfield, x3d::QuantizationParameter* lqp, bool lqp_deep, x3d::X3DNode* *pVal)
{
	x3d::X3DNode* x3dnode;
	ReadSFNode(pBitStream, fieldType, lqp, lqp_deep, &x3dnode);

	dynamic_cast<x3d::MFNode*>(x3dfield)->append1Value(x3dnode);

	*pVal = x3dnode;
}

void BIFSDec::ReadSFField(System::IO::CBitStream32* pBitStream, NodeData& nodeData, FieldData& field, int fieldType, x3d::X3DField* x3dfield, x3d::QuantizationParameter* lqp, bool lqp_deep)
{
	bool sf = (field.field->fieldType >= BIFS_SFBool);

//	HRESULT_throw hr(S_OK);

	switch (fieldType)
	{
	case BIFS_SFNode:	// ??
	case BIFS_SF2DNode:
	case BIFS_SF3DNode:
	case BIFS_SFAppearanceNode:
	case BIFS_SFGeometryNode:
	case BIFS_SFMaterialNode:
	case BIFS_SFTextureNode:
	case BIFS_SFTextureTransform:	// Why doesn't this end with Node ???
	case BIFS_SFLinePropertiesNode:
	case BIFS_SFCoordinate2DNode:
	case BIFS_SFAudioNode:
	case BIFS_SFFontStyleNode:
		{
			x3d::X3DNode* x3dnode;
			ReadSFNode(pBitStream, fieldType, lqp, lqp_deep, &x3dnode);

			if (sf)
				dynamic_cast<x3d::SFNode*>(x3dfield)->setX3DNode(x3dnode);
			else
				dynamic_cast<x3d::MFNode*>(x3dfield)->append1Value(x3dnode);
		}
		break;

	case BIFS_SFBool:
		{
			bool value;
			ReadSFBool(pBitStream, &value);

			if (sf)
				dynamic_cast<x3d::SFBool*>(x3dfield)->setValue(value);
			else
				dynamic_cast<x3d::MFBool*>(x3dfield)->append1Value(value);
		}
		break;

	case BIFS_SFInt32:
		{
			long value;
			ReadSFInt32(pBitStream, field, &value);

			if (sf)
				dynamic_cast<x3d::SFInt32*>(x3dfield)->setValue(value);
			else
				dynamic_cast<x3d::MFInt32*>(x3dfield)->append1Value(value);
		}
		break;

	case BIFS_SFFloat:
		{
			float value;
			ReadSFFloat(pBitStream, field, &value);

			if (sf)
				dynamic_cast<x3d::SFFloat*>(x3dfield)->setValue(value);
			else
				dynamic_cast<x3d::MFFloat*>(x3dfield)->append1Value(value);
		}
		break;

	case BIFS_SFTime:
		{
			double value;
			ReadSFTime(pBitStream, field, &value);

			if (sf)
				dynamic_cast<x3d::SFTime*>(x3dfield)->setValue(value);
			else
				ASSERT(0);//dynamic_cast<x3d::MFTime*>(x3dfield)->append1Value(value);
		}
		break;

	case BIFS_SFVec2f:
		{
			x3d::Vec2f value;
			ReadSFVec2f(pBitStream, field, value);

			if (sf)
				dynamic_cast<x3d::SFVec2f*>(x3dfield)->setValue(value);
			else
				dynamic_cast<x3d::MFVec2f*>(x3dfield)->append1Value(value);
		}
		break;

	case BIFS_SFVec3f:
		{
			x3d::Vec3f value;
			ReadSFVec3f(pBitStream, field, value);

			if (sf)
				dynamic_cast<x3d::SFVec3f*>(x3dfield)->setValue(value);
			else
				dynamic_cast<x3d::MFVec3f*>(x3dfield)->append1Value(value);
		}
		break;

	case BIFS_SFColor:
		{
			x3d::Vec3f value;
			ReadSFColor(pBitStream, field, value);

			if (sf)
				dynamic_cast<x3d::SFColor*>(x3dfield)->setValue(value);
			else
				dynamic_cast<x3d::MFColor*>(x3dfield)->append1Value(value);
		}
		break;

	case BIFS_SFString:
		{
			ReadSFString(pBitStream, field);

			// TODO
		}
		break;

	case BIFS_SFURL:
		{
			long ODid;
			ReadSFUrl(pBitStream, field, &ODid);

			if (sf)
				ASSERT(0);//hr = CComQIPtr<ILSFURL>(x3dfield)->setValue(ODid, NULL);
			else
				dynamic_cast<x3d::MFURL*>(x3dfield)->append1Value(ODid, NULL);
		}
		break;

	case BIFS_SFCommandBuffer:
		{
			ReadSFCommandBuffer(pBitStream);
			// TODO
		}
		break;

	case BIFS_SFScript:
		{
			ReadSFScript(pBitStream, nodeData);
			//SFScript scriptValue();
			// TODO
		}
		break;

	default:
		ASSERT(0);
		throw L"TODO: Unimplemented parsing of field type";
	}
}

void BIFSDec::ReplaceSFField(System::IO::CBitStream32* pBitStream, FieldData& field, int fieldType, x3d::X3DField* x3dfield, x3d::QuantizationParameter* lqp, bool lqp_deep, int where)
{
	bool sf = (field.field->fieldType >= BIFS_SFBool);

	HRESULT_throw hr(Success);

	switch (fieldType)
	{
	case BIFS_SFNode:	// ??
	case BIFS_SF2DNode:
	case BIFS_SF3DNode:
	case BIFS_SFAppearanceNode:
	case BIFS_SFGeometryNode:
	case BIFS_SFMaterialNode:
	case BIFS_SFLinePropertiesNode:
	case BIFS_SFCoordinate2DNode:
	case BIFS_SFAudioNode:
		{
			x3d::X3DNode* x3dnode;
			ReadSFNode(pBitStream, fieldType, lqp, lqp_deep, &x3dnode);

#if 0
			if (sf)
				hr = CComQIPtr<ILSFNode>(x3dfield)->setValue(x3dnode);
			else
#endif
				dynamic_cast<x3d::MFNode*>(x3dfield)->set1Value(0, x3dnode);
		}
		break;

#if 0
	case BIFS_SFBool:
		{
			VARIANT_BOOL value;
			ReadSFBool(pBitStream, &value);

			if (sf)
				hr = CComQIPtr<ILSFBool>(x3dfield)->setValue(value);
			else
				hr = CComQIPtr<ILMFBool>(x3dfield)->append1Value(value);
		}
		break;

	case BIFS_SFInt32:
		{
			long value;
			ReadSFInt32(pBitStream, field, &value);

			if (sf)
				hr = CComQIPtr<ILSFInt32>(x3dfield)->setValue(value);
			else
				hr = CComQIPtr<ILMFInt32>(x3dfield)->append1Value(value);
		}
		break;

	case BIFS_SFFloat:
		{
			float value;
			ReadSFFloat(pBitStream, field, &value);

			if (sf)
				hr = CComQIPtr<ILSFFloat>(x3dfield)->setValue(value);
			else
				hr = CComQIPtr<ILMFFloat>(x3dfield)->append1Value(value);
		}
		break;

	case BIFS_SFVec2f:
		{
			float value[2];
			ReadSFVec2f(pBitStream, field, value);

			if (sf)
				hr = CComQIPtr<ILSFVec2f>(x3dfield)->setValue(value);
			else
				hr = CComQIPtr<ILMFVec2f>(x3dfield)->append1Value(value);
		}
		break;

	case BIFS_SFVec3f:
		{
			float value[3];
			ReadSFVec3f(pBitStream, field, value);

			if (sf)
				hr = CComQIPtr<ILSFVec3f>(x3dfield)->setValue(value);
			else
				hr = CComQIPtr<ILMFVec3f>(x3dfield)->append1Value(value);
		}
		break;

	case BIFS_SFColor:
		{
			float value[3];
			ReadSFColor(pBitStream, field, value);

			if (sf)
				hr = CComQIPtr<ILSFColor>(x3dfield)->setValue(value);
			else
				hr = CComQIPtr<ILMFColor>(x3dfield)->append1Value(value);
		}
		break;

	case BIFS_SFURL:
		{
			ReadSFUrl(pBitStream, field);
		}
		break;
#endif

	default:
		ASSERT(0);
		throw L"TODO: Unimplemented parsing of field type";
	}
}

void BIFSDec::ReadMFListDescription(System::IO::CBitStream32* pBitStream, NodeData& nodeData, FieldData& fieldData, x3d::X3DField* x3dfield, x3d::QuantizationParameter* lqp, bool lqp_deep)
{
	if (*fieldData.field->name == L"children"/* || !wcscmp(fieldData.field->name->c_str(), L"addChildren")*/)
	{
		while (!pBitStream->getbit())
		{
			if (lqp && !lqp_deep)
			{
				if (lqp->getIsLocal())	// Means that it only applies to one sibling
				{
					lqp = NULL;
				}
			}

			x3d::X3DNode* x3dnode;
			ReadChildNode(pBitStream, fieldData, (int)fieldData.field->fieldType + (int)BIFS_SFBool, x3dfield, lqp, lqp_deep, &x3dnode);

			x3d::QuantizationParameter* qp = dynamic_cast<x3d::QuantizationParameter*>(x3dnode);
			if (qp)
			{
				lqp = qp;
				lqp_deep = false;
			}
		}
	}
	else
	{
		while (!pBitStream->getbit())
		{
			ReadSFField(pBitStream, nodeData, fieldData, (int)fieldData.field->fieldType + (int)BIFS_SFBool, x3dfield, lqp, lqp_deep);	// fieldtype from MF to SF
		}
	}
}

void BIFSDec::ReadMFVectorDescription(System::IO::CBitStream32* pBitStream, NodeData& nodeData, FieldData& fieldData, x3d::X3DField* x3dfield, x3d::QuantizationParameter* lqp, bool lqp_deep)
{
	int NbBits = pBitStream->getnbits(5);
	int numberOfFields = pBitStream->getnbits(NbBits);

	if (String(fieldData.field->name) == L"children")
	{
		for (int i = 0; i < numberOfFields; i++)
		{
			if (lqp && !lqp_deep)
			{
				if (lqp->getIsLocal())	// Means that it only applies to one sibling
				{
					lqp = NULL;
				}
			}

			x3d::X3DNode* x3dnode;
			ReadChildNode(pBitStream, fieldData, (int)fieldData.field->fieldType + (int)BIFS_SFBool, x3dfield, lqp, lqp_deep, &x3dnode);

			x3d::QuantizationParameter* qp = dynamic_cast<x3d::QuantizationParameter*>(x3dnode);
			if (qp)
			{
				lqp = qp;
				lqp_deep = false;
			}
		}
	}
	else
	{
		for (int i = 0; i < numberOfFields; i++)
		{
			ReadSFField(pBitStream, nodeData, fieldData, (int)fieldData.field->fieldType + (int)BIFS_SFBool, x3dfield, lqp, lqp_deep);	// fieldtype from MF to SF
		}
	}
}

void BIFSDec::ReadMFField(System::IO::CBitStream32* pBitStream, NodeData& nodeData, FieldData& field, x3d::X3DField* x3dfield, x3d::QuantizationParameter* lqp, bool lqp_deep)
{
	int reserved = pBitStream->getbit();
	if (!reserved)
	{
		int isListDescription = pBitStream->getbit();
		if (isListDescription)
		{
			ReadMFListDescription(pBitStream, nodeData, field, x3dfield, lqp, lqp_deep);
		}
		else
		{
			ReadMFVectorDescription(pBitStream, nodeData, field, x3dfield, lqp, lqp_deep);
		}
	}
	else
		ASSERT(0);
}

void BIFSDec::ReadField(System::IO::CBitStream32* pBitStream, NodeData& nodeData, FieldData& fieldData, x3d::X3DField* x3dfield, x3d::QuantizationParameter* lqp, bool lqp_deep)
{
	fieldData.isQuantized = false;// is set to true when the three following conditions are met :
	if (lqp != NULL)
	{
		if (fieldData.field->quantType > 0)//!= 0)
		{
			bool quant = false;

			switch (fieldData.field->quantType)
			{
			case 2:
				{
					quant = lqp->getPosition2DQuant();
				}
				break;

			case 4:
				{
					quant = lqp->getColorQuant();
				}
				break;

			case 12:
				{
					quant = lqp->getSizeQuant();
				}
				break;

			case 13:
			case 14:
			case 15:
				{
					quant = true;
				}
				break;

			default:
				ASSERT(0);
			}

			if (quant)
			{
				fieldData.isQuantized = true;

				/*
				quantType nbBits
				1 lqp.position3DNbBits
				2 lqp.position2DNbBits
				3 lqp.drawOrderNbBits
				4 lqp.colorNbBits
				5 lqp.textureCoordinateNbBits
				6 lqp.angleNbBits
				7 lqp.scaleNbBits
				8 lqp.keyNbBits
				9,10 lqp.normalNbBits
				11,12 lqp.sizeNbBits
				13 fct.defaultNbBits
				14 This value is set according to the number
				of points received in the last received
				coord field of the node. Let N that number,
				then:
				. . ) ( log Ceil nbBits 2 N .
				where the function Ceil returns the
				smallest integer greater than its argument
				15 0
				*/

				switch (fieldData.field->quantType)
				{
				case 2:
					{
						fieldData.nbBits = lqp->getPosition2DNbBits();
					}
					break;

				case 4:
					{
						fieldData.nbBits = lqp->getColorNbBits();
					}
					break;

				case 11:
				case 12:
					{
						fieldData.nbBits = lqp->getSizeNbBits();
					}
					break;

				case 13:
					{
						fieldData.nbBits = fieldData.field->defaultNbBits;
					}
					break;

				case 15:
					{
						fieldData.nbBits = 0;
					}
					break;

				default:
					ASSERT(0);
				}

				// floatMin
				switch (fieldData.field->quantType)
				{
				case 2:
					{
						lqp->getPosition2DMin(fieldData.floatMin);
					}
					break;

				case 11:
				case 12:
					{
						if (fieldData.field->fieldType == BIFS_SFFloat)
						{
							fieldData.floatMin[0] = lqp->getSizeMin();
						}
						else if (fieldData.field->fieldType == BIFS_SFVec2f)
						{
							fieldData.floatMin[0] = lqp->getSizeMin();
							fieldData.floatMin[1] = lqp->getSizeMin();
						}
						else if (fieldData.field->fieldType == BIFS_SFVec3f)
						{
							fieldData.floatMin[0] = lqp->getSizeMin();
							fieldData.floatMin[1] = lqp->getSizeMin();
							fieldData.floatMin[2] = lqp->getSizeMin();
						}
						else
							ASSERT(0);
					}
					break;

				case 13:
				case 14:
				case 15:
					{
						/* ??
						NULL
							floatMin[0] = 0;
							floatMin[1] = 0;
							floatMin[2] = 0;
							floatMin[3] = 0;
							*/
					}
					break;

				default:
					ASSERT(0);
				}

				// floatMax
				switch (fieldData.field->quantType)
				{
				case 2:
					{
						lqp->getPosition2DMax(fieldData.floatMax);
					}
					break;

				case 11:
				case 12:
					{
						if (fieldData.field->fieldType == BIFS_SFFloat)
						{
							fieldData.floatMax[0] = lqp->getSizeMax();
						}
						else if (fieldData.field->fieldType == BIFS_SFVec2f)
						{
							fieldData.floatMax[0] = lqp->getSizeMax();
							fieldData.floatMax[1] = lqp->getSizeMax();
						}
						else if (fieldData.field->fieldType == BIFS_SFVec3f)
						{
							fieldData.floatMax[0] = lqp->getSizeMax();
							fieldData.floatMax[1] = lqp->getSizeMax();
							fieldData.floatMax[2] = lqp->getSizeMax();
						}
						else
							ASSERT(0);
					}
					break;

				case 13:
				case 14:
				case 15:
					{
						/* ??
						NULL
							floatMin[0] = 0;
							floatMin[1] = 0;
							floatMin[2] = 0;
							floatMin[3] = 0;
							*/
					}
					break;

				default:
					ASSERT(0);
				}

				// intMin
				switch (fieldData.field->quantType)
				{
				case 13:
				case 14:
					{
						fieldData.intMin[0] = fieldData.field->m;
					}
					break;

				default:
					{
					// NULL???
					}
					break;
				}
			}
		}
	/*
	.lqp!=0 (there is a x3d::QuantizationParameter node in the scope of the field)
	.quantType !=0 (the field value is of a type that may be quantized), and
	.the following condition is met for the relevant quantization type:
		quantType Condition
		1 lqp.position3DQuant == TRUE
		2 lqp.position2DQuant == TRUE
		3 lqp.drawOrderQuant == TRUE
		4 lqp.colorQuant == TRUE
		5 lqp.textureCoordinateQuant == TRUE
		6 lqp.angleQuant == TRUE
		7 lqp.scaleQuant == TRUE
		8 lqp.keyQuant == TRUE
		9 lqp.normalQuant == TRUE
		10 lqp.normalQuant == TRUE
		11 lqp.sizeQuant == TRUE
		12 lqp.sizeQuant == TRUE
		13 Always TRUE
		14 Always TRUE
		15 Always TRUE
*/
	}

	ASSERT(x3dfield);

	if (fieldData.field->fieldType >= BIFS_SFBool)
		ReadSFField(pBitStream, nodeData, fieldData, fieldData.field->fieldType, x3dfield, lqp, lqp_deep);
	else
		ReadMFField(pBitStream, nodeData, fieldData, x3dfield, lqp, lqp_deep);
}

void BIFSDec::ReadMaskNodeDescription(System::IO::CBitStream32* pBitStream, NodeData* nodeData, x3d::QuantizationParameter* lqp, bool lqp_deep)
{
#if 0	// TODO have this
	if (node.protoData != null)
	{
		for (i=0; i<node.numALLfields; i++)
		{
			bit(1) Mask;
			if (Mask)
			{
				bit(1) isedField;
				if (isedField)
				{
					unsigned int(node.proto.nALLbits) protoField;
				}
				else
				{
					Field value(node.field[i]]);
				}
			}
		}
	}
	else
#endif
	{ //regular list of fields – not from a PROTO
		//for (int i = 0; i < node->numDEFfields; i++)
		int i = 0;
		while (nodeData->node->fields[i].name)
		{
			if (nodeData->node->fields[i].bDef)
			{
				//if (node->fields[i].
				int Mask = pBitStream->getbit();
				if (Mask)
				{
					if (*nodeData->node->fields[i].name == L"removeChildren")
					{
						MessageBeep(-1);
					}

					x3d::X3DField* x3dfield = nodeData->x3dnode->getField(nodeData->node->fields[i].name);
					if (x3dfield == NULL)
					{
						ASSERT(0);
						throw L"Couldn't get field on node";
					}

					// TODO
					//Field value(node.field[node.def2all[i]]);
				//	TRACE("\tfield: %S:%S\n", nodeData->node->nodeName, nodeData->node->fields[i].name->c_str());

					FieldData fieldData;
					fieldData.field = &nodeData->node->fields[i];

					ReadField(pBitStream, *nodeData, fieldData, x3dfield, lqp, lqp_deep);
				}
			}

			i++;
		}
		//ASSERT(node->fields[i].name);	// Couldn't find field?
	}
}

void BIFSDec::ReadListNodeDescription(System::IO::CBitStream32* pBitStream, NodeData* nodeData, x3d::QuantizationParameter* lqp, bool lqp_deep)
{
	while (!pBitStream->getbit())
	{
#if 0	// TODO
		if (node.protoData != null )
		{
			bit(1) isedField;
			if (isedField){
				bit(node.nALLbits) fieldRef;
				bit(node.proto.nALLbits) protoField;
			} else {
				bit(node.nDEFbits) fieldRef;
				Field value(node.field[node.def2all[fieldRef]]);
			}
		}
		else
#endif
		{
//			Node* node = nodeData.node;//&nodes[GetNodeType(nodeDataType, localNodeType)];

			int nDEFbits = nodeDataTypes[nodeData->nodeDataType].nodes[nodeData->localNodeType-1].nDEFbits;

			int fieldRef;
			if (nDEFbits)
				fieldRef = pBitStream->getnbits(nDEFbits);
			else
				fieldRef = 0;

			int n = 0;
			int i = 0;
			while (nodeData->node->fields[i].name)
			{
				if (nodeData->node->fields[i].bDef)
				{
					if (fieldRef == n)
					{
					if (*nodeData->node->fields[i].name == L"removeChildren")
					{
						MessageBeep(-1);
					}

						x3d::X3DField* x3dfield = nodeData->x3dnode->getField(nodeData->node->fields[i].name);
						if (x3dfield == NULL)
						{
							ASSERT(0);
							throw L"Couldn't get field on node";
						}

						TRACE("\tfield: %S:%S\n", nodeData->node->nodeName, nodeData->node->fields[i].name);

						FieldData fieldData;
						fieldData.field = &nodeData->node->fields[i];

						ReadField(pBitStream, *nodeData, fieldData, x3dfield, lqp, lqp_deep);
						break;
					}
					n++;
				//	Field value(node.field[node.def2all[fieldRef]]);
				}
				i++;
			}
			ASSERT(nodeData->node->fields[i].name);	// Couldn't find field?
		}
	}
}

void BIFSDec::ReadSFNode(System::IO::CBitStream32* pBitStream, int nodeDataType, x3d::QuantizationParameter* lqp, bool lqp_deep, x3d::X3DNode* *pVal)
{
	ASSERT(pVal != NULL);
	*pVal = NULL;

	int isReused = pBitStream->getbit();
	if (isReused)
	{
		int nodeID = pBitStream->getnbits(m_pBIFSConfig->nodeIDbits);
		TRACE("USE %d\n", nodeID);

		NodeDef* pDef = FindNode(nodeID);
		if (pDef)
		{
			*pVal = pDef->nodeData->x3dnode;
		}
		else
		{
		// ???
	//		ASSERT(0);
	//		throw L"USE of undefined DEF";
		}
	}
	else
	{
		NodeData* nodeData = new NodeData;
		nodeData->nodeDataType = nodeDataType;
		nodeData->localNodeType = pBitStream->getnbits(GetNDTnbBits(nodeDataType));

		int nodeType;
		int extLocalNodeType = 0;

		x3d::X3DNode* x3dnode;

		if (nodeData->localNodeType == 0)
		{
			//return;
			throw (ErrorCode)Success_False;

			extLocalNodeType = pBitStream->getnbits(6/*GetNDTnbBitsExt(nodeDataType)*/);
			if (extLocalNodeType == 1)
			{
				ASSERT(0);
				int PROTOnodeType = pBitStream->getnbits(m_pBIFSConfig->PROTOIDbits);
#if 0
				nodeType = GetPROTONodeType(PROTODataType,PROTOnodeType)
#endif
			}
			else if (extLocalNodeType > 1)
			{
				nodeType = GetExtNodeType(nodeDataType, extLocalNodeType);
			}
			else
				ASSERT(0);
		}
		else
		{
			nodeType = GetNodeType(nodeData->nodeDataType, nodeData->localNodeType);

		//	TRACE("node: %S", nodes[nodeType].nodeName->c_str());

			x3dnode = m_scene->createNode(nodes[nodeType].nodeName);
			ASSERT(x3dnode != NULL);
			if (x3dnode == NULL)
			{
				ASSERT(0);
				throw L"Couldn't create node";
			}

			nodeData->x3dnode = x3dnode;

			nodeData->nINbits = nodeDataTypes[nodeData->nodeDataType].nodes[nodeData->localNodeType-1].nINbits;
			nodeData->nOUTbits = nodeDataTypes[nodeData->nodeDataType].nodes[nodeData->localNodeType-1].nOUTbits;

			nodeData->node = &nodes[nodeType];

			*pVal = x3dnode;
		}

		int isUpdateable = pBitStream->getbit();
		if (isUpdateable)
		{
			NodeDef* pDef = new NodeDef;
			//pDef->m_nodeDataType = nodeData.nodeDataType;
			//pDef->m_localNodeType = nodeData.localNodeType;

			pDef->m_nodeID = pBitStream->getnbits(m_pBIFSConfig->nodeIDbits);
			TRACE(" DEF %d", pDef->m_nodeID);

			//pDef->m_nodeDataType = &nodeDataTypes[nodeDataType].nodes[localNodeType-1];
			//pDef->m_x3dnode = x3dnode;
			pDef->nodeData = nodeData;
			m_defs.Add(pDef);

			if (m_USENAMES)
			{
				StringW* name = ReadString(pBitStream);
			}
		}
		TRACE("\n");

		if (	(extLocalNodeType == 0) &&
				(nodeType == IndexedFaceSet) &&
				(m_pBIFSConfig->use3DmeshCoding == 1))
		{
			ASSERT(0);
	#if 0
			Mesh3D mnode;
	#endif
		}
		else
		{
			int MaskAccess = pBitStream->getbit();
			if (MaskAccess)
			{
				ReadMaskNodeDescription(pBitStream, nodeData, lqp, true);
			}
			else
			{
				ReadListNodeDescription(pBitStream, nodeData, lqp, true);
			}
		}
	}
}

// Commands

ErrorCode BIFSDec::IndexedValueInsertion(System::IO::CBitStream32* pBitStream)
{
	int nodeID = pBitStream->getnbits(m_pBIFSConfig->nodeIDbits);

	NodeDef* pDef = FindNode(nodeID);
	ASSERT(pDef);

//	NodeUpdateField node=GetNodeFromID(nodeID);

	int inID = pBitStream->getnbits(nodeDataTypes[pDef->nodeData->nodeDataType].nodes[pDef->nodeData->localNodeType-1].nINbits);
	int insertionPosition = pBitStream->getnbits(2);

	int nodeType = GetNodeType(pDef->nodeData->nodeDataType, pDef->nodeData->localNodeType);
	Field* fields = nodes[nodeType].fields;
	int j = 0;
	int i = 0;
	while (fields[i].name)
	{
		if (fields[i].bIn)
		{
			if (inID == j)
			{
				break;
			}
			j++;
		}
		i++;
	}
	Field* field = &fields[j];
	if (field->name == NULL)
	{
		TRACE("Trying to insert a value into a non-input field");
		ASSERT(0);
		return Error;
	}

	if (field->fieldType >= BIFS_SFBool)
	{
		TRACE("Trying to insert a value into a single valued field");
		ASSERT(0);
		return Error;
	}

	x3d::X3DField* x3dfield = pDef->nodeData->x3dnode->getField(field->name);
	if (x3dfield == NULL)
	{
		TRACE("Couldn't find field on node");
		ASSERT(0);
		return Error;
	}

	switch (insertionPosition)
	{
	case 0: // insertion at a specified position
		{
			uint16 position = pBitStream->getnbits(16);

			ASSERT(0);	// TODO

			//SFField value(node.field[node.in2all[inID]]);
		}
		break;

	case 2: // insertion at the beginning of the field
		{
			ASSERT(0);
			//SFField value(node.field[node.in2all[inID]]);
		}
		break;

	case 3: // insertion at the end of the field
		{
			//NodeData nodeData;
			//nodeData.x3dnode = pDef->m_x3dnode;

			FieldData fieldData;
			fieldData.field = field;
			ReadSFField(pBitStream, *pDef->nodeData, fieldData, (int)field->fieldType + (int)BIFS_SFBool, x3dfield, NULL, false);
			//SFField value(node.field[node.in2all[inID]]);
		}
		break;
	}

	return Success;
}

ErrorCode BIFSDec::FieldReplacement(System::IO::CBitStream32* pBitStream)
{
//	bit(BIFSConfiguration.nodeIDbits) nodeID ;
	int nodeID = pBitStream->getnbits(m_pBIFSConfig->nodeIDbits);
//	NodeData node = GetNodeFromID(nodeID);
	NodeDef* pDef = FindNode(nodeID);
	ASSERT(pDef);
	if (pDef == NULL)
		return Error;

//	int(node.nINbits) inID;
	int inID = pBitStream->getnbits(nodeDataTypes[pDef->nodeData->nodeDataType].nodes[pDef->nodeData->localNodeType-1].nINbits);

	int nodeType = GetNodeType(pDef->nodeData->nodeDataType, pDef->nodeData->localNodeType);
	Field* fields = nodes[nodeType].fields;
	int j = 0;
	int i = 0;
	while (fields[i].name)
	{
		if (fields[i].bIn)
		{
			if (inID == j)
			{
				break;
			}
			j++;
		}
		i++;
	}
	Field* field = &fields[j];
	if (field->name == NULL)
	{
		TRACE("Trying to insert a value into a non-input field");
		ASSERT(0);
		return Error;
	}

	x3d::X3DField* x3dfield = pDef->nodeData->x3dnode->getField(field->name);
	if (x3dfield == NULL)
	{
		TRACE("Couldn't find field on node");
		ASSERT(0);
		return Error;
	}

	//NodeData nodeData;
	//nodeData.x3dnode = pDef->m_x3dnode;

	FieldData fieldData;
	fieldData.field = field;
	ReadField(pBitStream, *pDef->nodeData, fieldData, x3dfield, NULL, false);

#if 0
	Field value(node.field[node.in2all[inID]]);
#endif

	return Success;
}

ErrorCode BIFSDec::IndexedValueReplacement(System::IO::CBitStream32* pBitStream)
{
	int nodeID = pBitStream->getnbits(m_pBIFSConfig->nodeIDbits);

//	NodeData node = GetNodeFromID(nodeID);
	NodeDef* pDef = FindNode(nodeID);
	ASSERT(pDef);

	int inID = pBitStream->getnbits(nodeDataTypes[pDef->nodeData->nodeDataType].nodes[pDef->nodeData->localNodeType-1].nINbits);
	//int inID = (node.nINbits);
	int replacementPosition = pBitStream->getnbits(2);

	int nodeType = GetNodeType(pDef->nodeData->nodeDataType, pDef->nodeData->localNodeType);
	Field* fields = nodes[nodeType].fields;
	int j = 0;
	int i = 0;
	while (fields[i].name)
	{
		if (fields[i].bIn)
		{
			if (inID == j)
			{
				break;
			}
			j++;
		}
		i++;
	}
	Field* field = &fields[j];
	if (field->name == NULL)
	{
		TRACE("Trying to insert a value into a non-input field");
		ASSERT(0);
		return Error;
	}

	if (field->fieldType >= BIFS_SFBool)
	{
		TRACE("Trying to replace a value into a single valued field");
		ASSERT(0);
		return Error;
	}

	x3d::X3DField* x3dfield = pDef->nodeData->x3dnode->getField(field->name);
	if (x3dfield == NULL)
	{
		TRACE("Couldn't find field on node");
		ASSERT(0);
		return Error;
	}

	switch (replacementPosition)
	{
	case 0: // replacement at a specified position
		{
			int position = pBitStream->getnbits(16);

			ASSERT(0);
			//SFField value(node.field[node.in2all[inID]]);
		}
		break;

	case 2: // replacement at the beginning of the field
		{
			FieldData fieldData;
			fieldData.field = field;
			ReplaceSFField(pBitStream, fieldData, (int)field->fieldType + (int)BIFS_SFBool, x3dfield, NULL, false, 0);

			//	SFField value(node.field[node.in2all[inID]]);
		}
		break;

	case 3: // replacement at the end of the field
		{
			ASSERT(0);
			//SFField value(node.field[node.in2all[inID]]);
		}
		break;
	}

	return Success;
}

void BIFSDec::ResetDefs()
{
	for (int i = 0; i < m_defs.GetSize(); i++)
	{
		delete m_defs[i];
	}
	m_defs.RemoveAll();
}

void BIFSDec::ReadROUTE(System::IO::CBitStream32* pBitStream)
{
	int isUpdateable = pBitStream->getbit();
	if (isUpdateable)
	{
		int routeID = pBitStream->getnbits(m_pBIFSConfig->routeIDbits);
		if (m_USENAMES)
		{
			StringW* routeName = ReadString(pBitStream);
		}
	}

	int outNodeID = pBitStream->getnbits(m_pBIFSConfig->nodeIDbits);
	NodeDef* pOutNodeDef = FindNode(outNodeID);
	//if (nodeDataTypes[pOutNodeDef->m_nodeDataType].nodes[pOutNodeDef->m_localNodeType-1].nOUTbits)
	{
		int outFieldRef = pBitStream->getnbits(pOutNodeDef->nodeData->nOUTbits);
	}
//	NodeData nodeOUT = GetNodeFromID(outNodeID);
	//int outFieldRef = pOutNodeDef->int(nodeOUT.nOUTbits);

	int inNodeID = pBitStream->getnbits(m_pBIFSConfig->nodeIDbits);
	NodeDef* pInNodeDef = FindNode(inNodeID);
	//NodeData nodeIN = GetNodeFromID(inNodeID);
	//int(nodeIN.nINbits) inFieldRef;
	//if (nodeDataTypes[pInNodeDef->m_nodeDataType].nodes[pInNodeDef->m_localNodeType-1].nINbits > 0)

	{
	//	int inFieldRef = pBitStream->getnbits(nodeDataTypes[pInNodeDef->m_nodeDataType].nodes[pInNodeDef->m_localNodeType-1].nINbits);
		int inFieldRef = pBitStream->getnbits(pInNodeDef->nodeData->nINbits);
	}
}

ErrorCode BIFSDec::ReadScene(System::IO::CBitStream32* pBitStream)
{
	x3d::MFNode* rootNodes = m_scene->getRootNodes();

	try
	{
		int reserved = pBitStream->getnbits(6);// reserved;
		m_USENAMES = pBitStream->getbit();// USENAMES;

	//	PROTOlist protos;
		while (pBitStream->getbit() == 1)
		{
			ASSERT(0);
			//PROTOdeclaration() proto;
		}

		//SFNode nodes(SFTopNode);
		x3d::X3DNode* x3dnode;
		try
		{
			ReadSFNode(pBitStream, BIFS_SFTopNode, NULL, false, &x3dnode);
		}
		catch (Exception* e)
		{
		}
		catch (int)
		{
			ASSERT(0);
		}

		if (x3dnode)
		{
			rootNodes->append1Value(x3dnode);
		}

		int hasROUTEs = pBitStream->getbit();
		if (hasROUTEs)
		{
			int ListDescription = pBitStream->getbit();
			if (ListDescription)
			{
				//ListROUTEs lroutes();
				int moreROUTEs;
				do
				{
					ReadROUTE(pBitStream);// route();
					moreROUTEs = pBitStream->getbit();
				}
				while (moreROUTEs);
			}
			else
			{
				//VectorROUTEs vroutes();
				int nBits = pBitStream->getnbits(5);
				int length = pBitStream->getnbits(nBits);
				for (int i = 0; i < length; i++)
				{
					ReadROUTE(pBitStream);// route[length]();
				}
			}
		}
	}
	catch (ErrorCode hr)
	{
		return hr;
	}

	return Success;
}

void BIFSDec::InsertionCommand(System::IO::CBitStream32* pBitStream)
{
	HRESULT_throw hr(Success);

	int parameterType = pBitStream->getnbits(2);

	switch (parameterType)
	{
	case 0:
		{
			ASSERT(0);
//			NodeInsertion nodeInsert();
		}
		break;

	case 1:	// Not an option
		{
			ASSERT(0);
			// Which one of the two below ??
			throw L"Unrecognized BIFS Insertion parameter";
			//hr = E_FAIL;
		}
		break;

	case 2:
		{
			hr = IndexedValueInsertion(pBitStream);
//			IndexedValueInsertion idxInsert();
		}
		break;

	case 3:
		{
			ASSERT(0);
//			ROUTEInsertion ROUTEInsert();
		}
		break ;
	}
}

void BIFSDec::ReplacementCommand(System::IO::CBitStream32* pBitStream)
{
	HRESULT_throw hr(Success);

	int parameterType = pBitStream->getnbits(2);

	switch (parameterType)
	{
	case 0:
		{
			ASSERT(0);
		//	NodeReplacement nodeReplace();
		}
		break;

	case 1:
		{
		//	FieldReplacement fieldReplace();
			FieldReplacement(pBitStream);
		}
		break;

	case 2:
		{
			//ASSERT(0);
			//IndexedValueReplacement idxReplace();
			IndexedValueReplacement(pBitStream);
		}
		break;

	case 3:
		{
			ASSERT(0);
			//ROUTEReplacement ROUTEReplace();
		}
		break;
	}
}

}	// Mpeg4
}
