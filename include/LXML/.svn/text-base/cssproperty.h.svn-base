#ifndef Web_CSSProperty_h
#define Web_CSSProperty_h

namespace System
{
namespace Web
{

class WEBEXT CSSProperty : public Object
{
public:
	CTOR CSSProperty(const WCHAR* name, bool bInherited, const WCHAR* initialCSS = NULL, uint8 cssType = 0);

	virtual String ToString() override
	{
		// TODO, more info
		return &m_name;
	}

	String get_Name()
	{
		return &m_name;
	}

	ImmutableString<WCHAR> m_name;
	ImmutableString<WCHAR> m_initialCSS;
	uint8 m_cssType;
	bool m_bInherited;
};

class WEBEXT CSSProperties
{
public:

	static CSSProperty moz_box_align;
	static CSSProperty moz_box_flex;
	static CSSProperty moz_box_orient;

	static CSSProperty alignment_baseline;
	static CSSProperty all_space_treatment;

	static CSSProperty background;
	static CSSProperty background_attachment;
	static CSSProperty background_color;
	static CSSProperty background_fill;
	static CSSProperty background_image;
	static CSSProperty background_position;
	static CSSProperty background_repeat;
	static CSSProperty baseline_shift;

	static CSSProperty behavior;

	static CSSProperty border;
	static CSSProperty border_border_break;
	static CSSProperty border_bottom;
	static CSSProperty border_bottom_color;
	static CSSProperty border_bottom_left_radius;
	static CSSProperty border_bottom_right_radius;
	static CSSProperty border_bottom_style;
	static CSSProperty border_bottom_width;
	static CSSProperty border_collapse;
	static CSSProperty border_color;
	static CSSProperty border_left;
	static CSSProperty border_left_color;
	static CSSProperty border_left_style;
	static CSSProperty border_left_width;
	static CSSProperty border_radius;
	static CSSProperty border_right;
	static CSSProperty border_right_color;
	static CSSProperty border_right_style;
	static CSSProperty border_right_width;
	static CSSProperty border_spacing;
	static CSSProperty border_style;
	static CSSProperty border_top;
	static CSSProperty border_top_color;
	static CSSProperty border_top_left_radius;
	static CSSProperty border_top_right_radius;
	static CSSProperty border_top_style;
	static CSSProperty border_top_width;
	static CSSProperty border_width;
	static CSSProperty bottom;
	static CSSProperty box_shadow;

	static CSSProperty caption_side;
	static CSSProperty clear;
	static CSSProperty clip;
	static CSSProperty clip_path;
	static CSSProperty clip_rule;
	static CSSProperty color;
	static CSSProperty color_interpolation;
	static CSSProperty color_interpolation_filters;
	static CSSProperty color_profile;
	static CSSProperty color_rendering;
	static CSSProperty content;
	static CSSProperty counter_increment;
	static CSSProperty counter_reset;
	static CSSProperty cursor;

	static CSSProperty direction;

	static CSSProperty display;
	static CSSProperty display_model;
	static CSSProperty display_role;
	static CSSProperty dominant_baseline;

	static CSSProperty empty_cells;
	static CSSProperty enable_background;

	static CSSProperty fill;
	static CSSProperty fill_opacity;
	static CSSProperty fill_rule;
	static CSSProperty filter;
	static CSSProperty _float;
	static CSSProperty flood_color;
	static CSSProperty flood_opacity;
	static CSSProperty font;
	static CSSProperty font_family;
	static CSSProperty font_size;
	static CSSProperty font_size_adjust;
	static CSSProperty font_stretch;
	static CSSProperty font_style;
	static CSSProperty font_variant;
	static CSSProperty font_weight;

	static CSSProperty glyph_orientation_horizontal;
	static CSSProperty glyph_orientation_vertical;

	static CSSProperty height;

	static CSSProperty image_rendering;

	static CSSProperty kerning;

	static CSSProperty left;
	static CSSProperty letter_spacing;
	static CSSProperty lighting_color;
	static CSSProperty line_height;
	static CSSProperty linefeed_treatment;
	static CSSProperty list_style_position;
	static CSSProperty list_style_type;

	static CSSProperty margin;
	static CSSProperty margin_bottom;
	static CSSProperty margin_left;
	static CSSProperty margin_right;
	static CSSProperty margin_top;
	static CSSProperty marker;
	static CSSProperty marker_end;
	static CSSProperty marker_mid;
	static CSSProperty marker_start;
	static CSSProperty mask;
	static CSSProperty max_height;
	static CSSProperty max_width;
	static CSSProperty min_height;
	static CSSProperty min_width;

	static CSSProperty opacity;
	static CSSProperty outline;
	static CSSProperty outline_color;
	static CSSProperty outline_style;
	static CSSProperty outline_width;
	static CSSProperty overflow;

	static CSSProperty padding;
	static CSSProperty padding_bottom;
	static CSSProperty padding_left;
	static CSSProperty padding_right;
	static CSSProperty padding_top;
	static CSSProperty pointer_events;
	static CSSProperty position;

	static CSSProperty right;

	static CSSProperty shape_rendering;
	static CSSProperty solid_color;
	static CSSProperty solid_opacity;
	static CSSProperty stop_color;
	static CSSProperty stop_opacity;
	static CSSProperty stroke;
	static CSSProperty stroke_dasharray;
	static CSSProperty stroke_dashoffset;
	static CSSProperty stroke_linecap;
	static CSSProperty stroke_linejoin;
	static CSSProperty stroke_miterlimit;
	static CSSProperty stroke_opacity;
	static CSSProperty stroke_width;

	static CSSProperty text_align;
	static CSSProperty text_anchor;
	static CSSProperty text_decoration;
	static CSSProperty text_indent;

	static CSSProperty text_line_through_color;
	static CSSProperty text_line_through_mode;
	static CSSProperty text_line_through_style;
	static CSSProperty text_line_through_width;
	static CSSProperty text_overline_color;
	static CSSProperty text_overline_mode;
	static CSSProperty text_overline_style;
	static CSSProperty text_overline_width;

	static CSSProperty text_rendering;
	static CSSProperty text_shadow;
	static CSSProperty text_underline_color;
	static CSSProperty text_underline_mode;
	static CSSProperty text_underline_style;
	static CSSProperty text_underline_width;
	static CSSProperty top;

	static CSSProperty unicode_bidi;

	static CSSProperty vertical_align;
	static CSSProperty visibility;

	static CSSProperty white_space;
	static CSSProperty white_space_treatment;
	static CSSProperty width;
	static CSSProperty word_spacing;
	static CSSProperty wrap_option;
	static CSSProperty writing_mode;
	static CSSProperty z_index;

	//static CSSProperty* csspropertyList[];

	static CSSProperty* csspropertyList[];

//	vector<CSSProperty*> m_items;

private:
	CTOR CSSProperties();

//	static CSSProperties* Single;
};

WEBEXT CSSProperty* GetCSSProperty(StringIn propertyName);
WEBEXT int GetCSSPropertyIndex(StringIn propertyName);

enum
{
	CSSProperty__box_align,
	CSSProperty__box_flex,
	CSSProperty__box_orient,

	CSSProperty_alignment_baseline,
	CSSProperty_all_space_treatment,

	CSSProperty_background,
	CSSProperty_background_attachment,
	CSSProperty_background_color,
	CSSProperty_background_fill,
	CSSProperty_background_image,
	CSSProperty_background_position,
	CSSProperty_background_repeat,
	CSSProperty_baseline_shift,
	CSSProperty_behavior,	//
	CSSProperty_border,
	CSSProperty_border_break,
	CSSProperty_border_bottom,
	CSSProperty_border_bottom_color,
	CSSProperty_border_bottom_left_radius,
	CSSProperty_border_bottom_right_radius,
	CSSProperty_border_bottom_style,
	CSSProperty_border_bottom_width,
	CSSProperty_border_collapse,
	CSSProperty_border_color,
	CSSProperty_border_left,
	CSSProperty_border_left_color,
	CSSProperty_border_left_style,
	CSSProperty_border_left_width,
	CSSProperty_border_radius,
	CSSProperty_border_right,
	CSSProperty_border_right_color,
	CSSProperty_border_right_style,
	CSSProperty_border_right_width,
	CSSProperty_border_spacing,
	CSSProperty_border_style,
	CSSProperty_border_top,
	CSSProperty_border_top_color,
	CSSProperty_border_top_left_radius,
	CSSProperty_border_top_right_radius,
	CSSProperty_border_top_style,
	CSSProperty_border_top_width,
	CSSProperty_border_width,
	CSSProperty_bottom,
	CSSProperty_box_shadow,

	CSSProperty_caption_side,
	CSSProperty_clear,
	CSSProperty_clip,
	CSSProperty_clip_path,
	CSSProperty_clip_rule,
	CSSProperty_color,
	CSSProperty_color_interpolation,
	CSSProperty_color_interpolation_filters,
	CSSProperty_color_profile,
	CSSProperty_color_rendering,
	CSSProperty_content,
	CSSProperty_counter_increment,
	CSSProperty_counter_reset,
	CSSProperty_cursor,

	CSSProperty_direction,
	CSSProperty_display,
	CSSProperty_display_model,
	CSSProperty_display_role,
	CSSProperty_dominant_baseline,

	CSSProperty_empty_cells,	// CSS Tables
	CSSProperty_enable_background,	// SVG

	CSSProperty_fill,
	CSSProperty_fill_opacity,
	CSSProperty_fill_rule,
	CSSProperty_filter,
	CSSProperty_float,
	CSSProperty_flood_color,
	CSSProperty_flood_opacity,
	CSSProperty_font,
	CSSProperty_font_family,
	CSSProperty_font_size,
	CSSProperty_font_size_adjust,
	CSSProperty_font_stretch,
	CSSProperty_font_style,
	CSSProperty_font_variant,
	CSSProperty_font_weight,

	CSSProperty_glyph_orientation_horizontal,
	CSSProperty_glyph_orientation_vertical,

	CSSProperty_height,

	CSSProperty_image_rendering,

	CSSProperty_kerning,

	CSSProperty_left,
	CSSProperty_letter_spacing,
	CSSProperty_lighting_color,
	CSSProperty_line_height,
	CSSProperty_linefeed_treatment,
	CSSProperty_list_style_position,
	CSSProperty_list_style_type,

	CSSProperty_margin,
	CSSProperty_margin_bottom,
	CSSProperty_margin_left,
	CSSProperty_margin_right,
	CSSProperty_margin_top,
	CSSProperty_marker,
	CSSProperty_marker_end,
	CSSProperty_marker_mid,
	CSSProperty_marker_start,
	CSSProperty_mask,
	CSSProperty_max_height,
	CSSProperty_max_width,
	CSSProperty_min_height,
	CSSProperty_min_width,

	CSSProperty_opacity,
	CSSProperty_outline,
	CSSProperty_outline_color,
	CSSProperty_outline_style,
	CSSProperty_outline_width,
	CSSProperty_overflow,

	CSSProperty_padding,
	CSSProperty_padding_bottom,
	CSSProperty_padding_left,
	CSSProperty_padding_right,
	CSSProperty_padding_top,
	CSSProperty_pointer_events,
	CSSProperty_position,

	CSSProperty_right,

	CSSProperty_shape_rendering,
	CSSProperty_solid_color,
	CSSProperty_solid_opacity,
	CSSProperty_stop_color,
	CSSProperty_stop_opacity,
	CSSProperty_stroke,
	CSSProperty_stroke_dasharray,
	CSSProperty_stroke_dashoffset,
	CSSProperty_stroke_linecap,
	CSSProperty_stroke_linejoin,
	CSSProperty_stroke_miterlimit,
	CSSProperty_stroke_opacity,
	CSSProperty_stroke_width,

	CSSProperty_text_align,
	CSSProperty_text_anchor,
	CSSProperty_text_decoration,
	CSSProperty_text_indent,
	CSSProperty_text_line_through_color,
	CSSProperty_text_line_through_mode,
	CSSProperty_text_line_through_style,
	CSSProperty_text_line_through_width,
	CSSProperty_text_overline_color,
	CSSProperty_text_overline_mode,
	CSSProperty_text_overline_style,
	CSSProperty_text_overline_width,
	CSSProperty_text_rendering,
	CSSProperty_text_shadow,
	CSSProperty_text_underline_color,
	CSSProperty_text_underline_mode,
	CSSProperty_text_underline_style,
	CSSProperty_text_underline_width,
	CSSProperty_top,

	CSSProperty_unicode_bidi,

	CSSProperty_vertical_align,
	CSSProperty_visibility,

	CSSProperty_white_space,
	CSSProperty_white_space_treatment,
	CSSProperty_width,
	CSSProperty_word_spacing,
	CSSProperty_wrap_option,
	CSSProperty_writing_mode,
	CSSProperty_z_index,

//
	CSSPropertyCount
};

}	// Web
}

#endif	// Web_CSSProperty_h
