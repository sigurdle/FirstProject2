#include "stdafx.h"
#include "LXML.h"
#include "LXML2.h"

#include "cssproperty.h"

namespace System
{
namespace Web
{

CSSProperty::CSSProperty(const WCHAR* name, bool bInherited, const WCHAR* initialCSS, uint8 cssType) :
	m_name(name),
	m_bInherited(bInherited),
	m_initialCSS(initialCSS),
	m_cssType(cssType)
{
	GetType()->m_instances.m_list.push_back(this);
}

uint8 IID_ILCSSPrimitiveValue = 1;
uint8 IID_ILCSSValueList = 2;
uint8 CLSID_LSVGColor = 3;
uint8 CLSID_LSVGPaint = 4;

CSSProperty CSSProperties::moz_box_align(WSTR("-moz-box-align"),						false, WSTR("stretch"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::moz_box_flex(WSTR("-moz-box-flex"),						false, WSTR("0"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::moz_box_orient(WSTR("-moz-box-orient"),						false, WSTR("inline-axis"), IID_ILCSSPrimitiveValue);

CSSProperty CSSProperties::alignment_baseline(WSTR("alignment-baseline"),					false,	WSTR("auto"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::all_space_treatment(WSTR("all-space-treatment"),					true,	WSTR("collapse"), IID_ILCSSPrimitiveValue);

CSSProperty CSSProperties::background(WSTR("background"),							0,	NULL, NULL);	// shorthand
CSSProperty CSSProperties::background_attachment(WSTR("background-attachment"),				false,	WSTR("scroll"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::background_color(WSTR("background-color"),					false,	WSTR("transparent"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::background_fill(WSTR("background-fill"),						false,	WSTR("none"), CLSID_LSVGPaint);
CSSProperty CSSProperties::background_image(WSTR("background-image"),					false,	WSTR("none"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::background_position(WSTR("background-position"),				false,	WSTR("0% 0%"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::background_repeat(WSTR("background-repeat"),					false,	WSTR("repeat"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::baseline_shift(WSTR("baseline-shift"),						false,	WSTR("baseline"), IID_ILCSSPrimitiveValue);

CSSProperty CSSProperties::behavior(WSTR("behavior"),								false,	WSTR("none"), IID_ILCSSValueList);

CSSProperty CSSProperties::border(WSTR("border"),									0, NULL, NULL); // shorthand
CSSProperty CSSProperties::border_border_break(WSTR("border-border-break"),				false,	WSTR("0"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::border_bottom(WSTR("border-bottom"),						0, NULL, NULL); // shorthand
CSSProperty CSSProperties::border_bottom_color(WSTR("border-bottom-color"),				false,	WSTR("currentColor"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::border_bottom_left_radius(WSTR("border-bottom-left-radius"),		false,	WSTR("0"), IID_ILCSSValueList);
CSSProperty CSSProperties::border_bottom_right_radius(WSTR("border-bottom-right-radius"),		false,	WSTR("0"), IID_ILCSSValueList);
CSSProperty CSSProperties::border_bottom_style(WSTR("border-bottom-style"),				false,	WSTR("none"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::border_bottom_width(WSTR("border-bottom-width"),				false,	WSTR("0"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::border_collapse(WSTR("border-collapse"),						true,		WSTR("separate"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::border_color(WSTR("border-color"),							0,	NULL, NULL);	// shorthand
CSSProperty CSSProperties::border_left(WSTR("border-left"),							0, NULL, NULL); // shorthand
CSSProperty CSSProperties::border_left_color(WSTR("border-left-color"),					false,	WSTR("currentColor"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::border_left_style(WSTR("border-left-style"),					false,	WSTR("none"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::border_left_width(WSTR("border-left-width"),					false,	WSTR("0"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::border_radius(WSTR("border-radius"),						0, NULL, NULL); // shorthand
CSSProperty CSSProperties::border_right(WSTR("border-right"),							0, NULL, NULL); // shorthand
CSSProperty CSSProperties::border_right_color(WSTR("border-right-color"),					false,	WSTR("currentColor"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::border_right_style(WSTR("border-right-style"),					false,	WSTR("none"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::border_right_width(WSTR("border-right-width"),					false,	WSTR("0"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::border_spacing(WSTR("border-spacing"),						true,		WSTR("0"), IID_ILCSSValueList);
CSSProperty CSSProperties::border_style(WSTR("border-style"),							0,	NULL, NULL);	// shorthand 
CSSProperty CSSProperties::border_top(WSTR("border-top"),							0, NULL, NULL); // shorthand
CSSProperty CSSProperties::border_top_color(WSTR("border-top-color"),					false,	WSTR("currentColor"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::border_top_left_radius(WSTR("border-top-left-radius"),			false,	WSTR("0"), IID_ILCSSValueList);
CSSProperty CSSProperties::border_top_right_radius(WSTR("border-top-right-radius"),			false,	WSTR("0"), IID_ILCSSValueList);
CSSProperty CSSProperties::border_top_style(WSTR("border-top-style"),					false,	WSTR("none"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::border_top_width(WSTR("border-top-width"),					false,	WSTR("0"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::border_width(WSTR("border-width"),							0,	NULL,	NULL);	// shorthand
CSSProperty CSSProperties::bottom(WSTR("bottom"),									false,	WSTR("auto"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::box_shadow(WSTR("box-shadow"),							false, WSTR("none"), IID_ILCSSValueList);

CSSProperty CSSProperties::caption_side(WSTR("caption-side"),							true,		WSTR("top"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::clear(WSTR("clear"),									false,	WSTR("none"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::clip(WSTR("clip"),									false,	WSTR("auto"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::clip_path(WSTR("clip-path"),								false,	WSTR("none"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::clip_rule(WSTR("clip-rule"),								true,		WSTR("nonzero"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::color(WSTR("color"),									true,		WSTR("black"), IID_ILCSSPrimitiveValue);// ?
CSSProperty CSSProperties::color_interpolation(WSTR("color-interpolation"),				true,		WSTR("sRGB"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::color_interpolation_filters(WSTR("color-interpolation-filters"),		true,		WSTR("linearRGB"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::color_profile(WSTR("color-profile"),						true,		WSTR("auto"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::color_rendering(WSTR("color-rendering"),						true,		WSTR("auto"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::content(WSTR("content"),								false,	WSTR("normal"), IID_ILCSSValueList);
CSSProperty CSSProperties::counter_increment(WSTR("counter-increment"),					false,	WSTR("none"), IID_ILCSSValueList);
CSSProperty CSSProperties::counter_reset(WSTR("counter-reset"),						false,	WSTR("none"), IID_ILCSSValueList);
CSSProperty CSSProperties::cursor(WSTR("cursor"),									true,		WSTR("auto"), IID_ILCSSPrimitiveValue);

CSSProperty CSSProperties::direction(WSTR("direction"),								true, WSTR("ltr"), IID_ILCSSPrimitiveValue);

CSSProperty CSSProperties::display(WSTR("display"),								0, NULL, NULL);	// shorthand
CSSProperty CSSProperties::display_model(WSTR("display-model"),						false, WSTR("text"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::display_role(WSTR("display-role"),							false, WSTR("inline"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::dominant_baseline(WSTR("dominant-baseline"),					false, WSTR("auto"), IID_ILCSSPrimitiveValue);

CSSProperty CSSProperties::empty_cells(WSTR("empty-cells"),							true, WSTR("show"), IID_ILCSSPrimitiveValue/*IID_ILCSSValueList*/);
CSSProperty CSSProperties::enable_background(WSTR("enable-background"),					false, WSTR("accumulate"), IID_ILCSSPrimitiveValue/*IID_ILCSSValueList*/);

CSSProperty CSSProperties::fill(WSTR("fill"),									true, WSTR("#000000"), CLSID_LSVGPaint);
CSSProperty CSSProperties::fill_opacity(WSTR("fill-opacity"),							true, WSTR("1"), IID_ILCSSPrimitiveValue);	// ?
CSSProperty CSSProperties::fill_rule(WSTR("fill-rule"),								true, WSTR("nonzero"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::filter(WSTR("filter"),									false, WSTR("none"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::_float(WSTR("float"),									false,	WSTR("none"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::flood_color(WSTR("flood-color"),							false, WSTR("black"), CLSID_LSVGColor);
CSSProperty CSSProperties::flood_opacity(WSTR("flood-opacity"),						false, WSTR("1"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::font(WSTR("font"),									0, NULL, NULL/*WSTR(""), IID_ILCSSPrimitiveValue*/);
CSSProperty CSSProperties::font_family(WSTR("font-family"),							true, WSTR("Times New Roman"), IID_ILCSSValueList);
CSSProperty CSSProperties::font_size(WSTR("font-size"),								true, WSTR("12pt"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::font_size_adjust(WSTR("font-size-adjust"),					true, WSTR(""), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::font_stretch(WSTR("font-stretch"),							true, WSTR(""), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::font_style(WSTR("font-style"),							true, WSTR("normal"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::font_variant(WSTR("font-variant"),							true, WSTR(""), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::font_weight(WSTR("font-weight"),							true, WSTR("normal"), IID_ILCSSPrimitiveValue);

CSSProperty CSSProperties::glyph_orientation_horizontal(WSTR("glyph-orientation-horizontal"),	true, WSTR(""), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::glyph_orientation_vertical(WSTR("glyph-orientation-vertical"),		true, WSTR(""), IID_ILCSSPrimitiveValue);

CSSProperty CSSProperties::height(WSTR("height"),									false, WSTR("auto"), IID_ILCSSPrimitiveValue);

CSSProperty CSSProperties::image_rendering(WSTR("image-rendering"),						true, WSTR("auto"), IID_ILCSSPrimitiveValue);

CSSProperty CSSProperties::kerning(WSTR("kerning"),								true, WSTR("auto"), IID_ILCSSPrimitiveValue);

CSSProperty CSSProperties::left(WSTR("left"),									false,	WSTR("auto"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::letter_spacing(WSTR("letter-spacing"),						true, WSTR("normal"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::lighting_color(WSTR("lighting-color"),						false, WSTR("white"), CLSID_LSVGColor);
CSSProperty CSSProperties::line_height(WSTR("line-height"),							true,	WSTR("normal"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::linefeed_treatment(WSTR("linefeed-treatment"),				true, WSTR("auto"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::list_style_position(WSTR("list-style-position"),				true,	WSTR("outside"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::list_style_type(WSTR("list-style-type"),						true,	WSTR("disc"), IID_ILCSSPrimitiveValue);

CSSProperty CSSProperties::margin(WSTR("margin"),									false,	NULL, NULL); // shorthand
CSSProperty CSSProperties::margin_bottom(WSTR("margin-bottom"),						false,	WSTR("0"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::margin_left(WSTR("margin-left"),							false,	WSTR("0"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::margin_right(WSTR("margin-right"),							false,	WSTR("0"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::margin_top(WSTR("margin-top"),							false,	WSTR("0"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::marker(WSTR("marker"),									false, WSTR(""), IID_ILCSSPrimitiveValue);	// ?
CSSProperty CSSProperties::marker_end(WSTR("marker-end"),							true, WSTR("none"), IID_ILCSSPrimitiveValue);	// ?
CSSProperty CSSProperties::marker_mid(WSTR("marker-mid"),							true, WSTR("none"), IID_ILCSSPrimitiveValue);	// ?
CSSProperty CSSProperties::marker_start(WSTR("marker-start"),							true, WSTR("none"), IID_ILCSSPrimitiveValue);	// ?
CSSProperty CSSProperties::mask(WSTR("mask"),									false, WSTR("none"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::max_height(WSTR("max-height"),							false, WSTR("none"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::max_width(WSTR("max-width"),								false, WSTR("none"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::min_height(WSTR("min-height"),							false, WSTR("0"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::min_width(WSTR("min-width"),								false, WSTR("0"), IID_ILCSSPrimitiveValue);

CSSProperty CSSProperties::opacity(WSTR("opacity"),								false, WSTR("1"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::outline(WSTR("outline"),								false, NULL, NULL);	// shorthand
CSSProperty CSSProperties::outline_color(WSTR("outline-color"),						false, WSTR("invert"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::outline_style(WSTR("outline-style"),						false, WSTR("none"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::outline_width(WSTR("outline-width"),						false, WSTR("medium"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::overflow(WSTR("overflow"),								false, WSTR("visible"), IID_ILCSSPrimitiveValue);

CSSProperty CSSProperties::padding(WSTR("padding"),								false,	NULL,	NULL);	// shorthand
CSSProperty CSSProperties::padding_bottom(WSTR("padding-bottom"),						false,	WSTR("0"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::padding_left(WSTR("padding-left"),							false,	WSTR("0"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::padding_right(WSTR("padding-right"),						false,	WSTR("0"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::padding_top(WSTR("padding-top"),							false,	WSTR("0"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::pointer_events(WSTR("pointer-events"),						true,		WSTR("visiblePainted"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::position(WSTR("position"),								false,	WSTR("static"), IID_ILCSSPrimitiveValue);

CSSProperty CSSProperties::right(WSTR("right"),									false,	WSTR("auto"), IID_ILCSSPrimitiveValue);

CSSProperty CSSProperties::shape_rendering(WSTR("shape-rendering"),						true, WSTR("auto"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::solid_color(WSTR("solid-color"),							false, WSTR("black"), CLSID_LSVGColor);
CSSProperty CSSProperties::solid_opacity(WSTR("solid-opacity"),						false, WSTR("1"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::stop_color(WSTR("stop-color"),							false, WSTR("black"), CLSID_LSVGColor);
CSSProperty CSSProperties::stop_opacity(WSTR("stop-opacity"),							false, WSTR("1"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::stroke(WSTR("stroke"),									true, WSTR("none"), CLSID_LSVGPaint);// ?
CSSProperty CSSProperties::stroke_dasharray(WSTR("stroke-dasharray"),					true, WSTR("none"), IID_ILCSSValueList);
CSSProperty CSSProperties::stroke_dashoffset(WSTR("stroke-dashoffset"),					true, WSTR("0"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::stroke_linecap(WSTR("stroke-linecap"),						true, WSTR("butt"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::stroke_linejoin(WSTR("stroke-linejoin"),						true, WSTR("miter"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::stroke_miterlimit(WSTR("stroke-miterlimit"),					true, WSTR("4"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::stroke_opacity(WSTR("stroke-opacity"),						true, WSTR("1"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::stroke_width(WSTR("stroke-width"),							true, WSTR("1"), IID_ILCSSPrimitiveValue);

CSSProperty CSSProperties::text_align(WSTR("text-align"),							true, WSTR("left"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::text_anchor(WSTR("text-anchor"),							true, WSTR("start"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::text_decoration(WSTR("text-decoration"),						NULL);// now a shorthand false, WSTR("none"), IID_ILCSSValueList),
CSSProperty CSSProperties::text_indent(WSTR("text-indent"),							true, WSTR("0"), IID_ILCSSPrimitiveValue);

CSSProperty CSSProperties::text_line_through_color(WSTR("text-line-through-color"),			false, WSTR("currentColor"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::text_line_through_mode(WSTR("text-line-through-mode"),			false, WSTR("continuous"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::text_line_through_style(WSTR("text-line-through-style"),			false, WSTR("none"), IID_ILCSSPrimitiveValue);

CSSProperty CSSProperties::text_line_through_width(WSTR("text-line-through-width"),			false, WSTR("auto"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::text_overline_color(WSTR("text-overline-color"),				false, WSTR("currentColor"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::text_overline_mode(WSTR("text-overline-mode"),				false, WSTR("continuous"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::text_overline_style(WSTR("text-overline-style"),				false, WSTR("none"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::text_overline_width(WSTR("text-overline-width"),				false, WSTR("auto"), IID_ILCSSPrimitiveValue);

CSSProperty CSSProperties::text_rendering(WSTR("text-rendering"),						true, WSTR("auto"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::text_shadow(WSTR("text-shadow"),							false, WSTR("none"), IID_ILCSSValueList);
CSSProperty CSSProperties::text_underline_color(WSTR("text-underline-color"),				false, WSTR("currentColor"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::text_underline_mode(WSTR("text-underline-mode"),				false, WSTR("continuous"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::text_underline_style(WSTR("text-underline-style"),				false, WSTR("none"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::text_underline_width(WSTR("text-underline-width"),				false, WSTR("auto"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::top(WSTR("top"),									false, WSTR("auto"), IID_ILCSSPrimitiveValue);

CSSProperty CSSProperties::unicode_bidi(WSTR("unicode-bidi"),						false, WSTR("normal"), IID_ILCSSPrimitiveValue);

CSSProperty CSSProperties::vertical_align(WSTR("vertical-align"),						false, WSTR("baseline"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::visibility(WSTR("visibility"),							false, WSTR("visible"), IID_ILCSSPrimitiveValue);

CSSProperty CSSProperties::white_space(WSTR("white-space"),							true, NULL);// shorthand
CSSProperty CSSProperties::white_space_treatment(WSTR("white-space-treatment"),			true, WSTR("ignore-if-surrounding-linefeed"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::width(WSTR("width"),									false, WSTR("auto"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::word_spacing(WSTR("word-spacing"),						true, WSTR("normal"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::wrap_option(WSTR("wrap-option"),							true, WSTR("wrap"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::writing_mode(WSTR("writing-mode"),						true, WSTR("lr-tb"), IID_ILCSSPrimitiveValue);
CSSProperty CSSProperties::z_index(WSTR("z-index"),								false, WSTR("auto"), IID_ILCSSPrimitiveValue);

CSSProperty* CSSProperties::csspropertyList[] =
{
	&moz_box_align,
	&moz_box_flex,
	&moz_box_orient,

	&alignment_baseline,
	&all_space_treatment,

	&background,
	&background_attachment,
	&background_color,
	&background_fill,
	&background_image,
	&background_position,
	&background_repeat,
	&baseline_shift,

	&behavior,

	&border,
	&border_border_break,
	&border_bottom,
	&border_bottom_color,
	&border_bottom_left_radius,
	&border_bottom_right_radius,
	&border_bottom_style,
	&border_bottom_width,
	&border_collapse,
	&border_color,
	&border_left,
	&border_left_color,
	&border_left_style,
	&border_left_width,
	&border_radius,
	&border_right,
	&border_right_color,
	&border_right_style,
	&border_right_width,
	&border_spacing,
	&border_style,
	&border_top,
	&border_top_color,
	&border_top_left_radius,
	&border_top_right_radius,
	&border_top_style,
	&border_top_width,
	&border_width,
	&bottom,
	&box_shadow,

	&caption_side,
	&clear,
	&clip,
	&clip_path,
	&clip_rule,
	&color,
	&color_interpolation,
	&color_interpolation_filters,
	&color_profile,
	&color_rendering,
	&content,
	&counter_increment,
	&counter_reset,
	&cursor,

	&direction,

	&display,
	&display_model,
	&display_role,
	&dominant_baseline,

	&empty_cells,
	&enable_background,

	&fill,
	&fill_opacity,
	&fill_rule,
	&filter,
	&_float,
	&flood_color,
	&flood_opacity,
	&font,
	&font_family,
	&font_size,
	&font_size_adjust,
	&font_stretch,
	&font_style,
	&font_variant,
	&font_weight,

	&glyph_orientation_horizontal,
	&glyph_orientation_vertical,

	&height,

	&image_rendering,

	&kerning,

	&left,
	&letter_spacing,
	&lighting_color,
	&line_height,
	&linefeed_treatment,
	&list_style_position,
	&list_style_type,

	&margin,
	&margin_bottom,
	&margin_left,
	&margin_right,
	&margin_top,
	&marker,
	&marker_end,
	&marker_mid,
	&marker_start,
	&mask,
	&max_height,
	&max_width,
	&min_height,
	&min_width,

	&opacity,
	&outline,
	&outline_color,
	&outline_style,
	&outline_width,
	&overflow,

	&padding,
	&padding_bottom,
	&padding_left,
	&padding_right,
	&padding_top,
	&pointer_events,
	&position,

	&right,

	&shape_rendering,
	&solid_color,
	&solid_opacity,
	&stop_color,
	&stop_opacity,
	&stroke,
	&stroke_dasharray,
	&stroke_dashoffset,
	&stroke_linecap,
	&stroke_linejoin,
	&stroke_miterlimit,
	&stroke_opacity,
	&stroke_width,

	&text_align,
	&text_anchor,
	&text_decoration,
	&text_indent,

	&text_line_through_color,
	&text_line_through_mode,
	&text_line_through_style,
	&text_line_through_width,
	&text_overline_color,
	&text_overline_mode,
	&text_overline_style,
	&text_overline_width,

	&text_rendering,
	&text_shadow,
	&text_underline_color,
	&text_underline_mode,
	&text_underline_style,
	&text_underline_width,
	&top,

	&unicode_bidi,

	&vertical_align,
	&visibility,

	&white_space,
	&white_space_treatment,
	&width,
	&word_spacing,
	&wrap_option,
	&writing_mode,
	&z_index,
};

#define MAX_PROPERTIES _countof(CSSProperties::csspropertyList)

#if 0
void ReleaseCSSInitialValues()
{
	for (int i = 0; i < MAX_PROPERTIES; i++)
	{
		if (csstyleList[i].m_initialValue)
		{
//			int refcount = csstyleList[i].m_initialValue->Release();
		//	ASSERT(refcount == 0);
			csstyleList[i].m_initialValue = NULL;
		}
	}
}
#endif

WEBEXT CSSProperty* GetCSSProperty(StringIn propertyname)
{
	int minv = 0;        // beginning of search range 
	int maxv = MAX_PROPERTIES;   // end of search range 
	
	int n = maxv / 2;
	while (minv < maxv)
	{ 
		int cmp = CSSProperties::csspropertyList[n]->m_name.Compare(propertyname._stringObject());
		if (cmp > 0)
			maxv = n;
		else if (cmp < 0)
			minv = n+1;
		else
			return CSSProperties::csspropertyList[n];

		n = (minv + maxv) / 2; 
	}

//	ASSERT(0);
	return NULL;
}

/*
template<class T, class T2>
size_t find(const T* items, size_t count, T2 propertyname)
{
	int minv = 0;        // beginning of search range
	int maxv = MAX_PROPERTIES;   // end of search range
	
	int n = maxv / 2;
	while (minv < maxv)
	{ 
		int cmp = csspropertyList[n].m_name.Compare(propertyname));
		if (cmp > 0)
			maxv = n;
		else if (cmp < 0)
			minv = n+1;
		else
			return n;

		n = (minv + maxv) / 2;
	}

//	ASSERT(0);
	return -1;
}
*/

WEBEXT int GetCSSPropertyIndex(StringIn propertyname)
{
	int minv = 0;        // beginning of search range
	int maxv = MAX_PROPERTIES;   // end of search range
	
	int n = maxv / 2;
	while (minv < maxv)
	{ 
		int cmp = StringIn(&CSSProperties::csspropertyList[n]->m_name).Compare(propertyname);
		if (cmp > 0)
			maxv = n;
		else if (cmp < 0)
			minv = n+1;
		else
			return n;

		n = (minv + maxv) / 2;
	}

//	ASSERT(0);
	return -1;
}

}	// Web
}
