#ifndef HDR10_H_
#define HDR10_H_

#define HDR_ST2084_MAX (10000.0f)

uniform float4 hdr_parameters;

#define HDR_WHITEPOINT_NITS (hdr_parameters.x)
#define HDR_UI_NITS_SCALAR  (hdr_parameters.y)
#define HDR_ENABLED         (hdr_parameters.z)
#define HDR_RENDERING_PDA   (hdr_parameters.w)

// from: https://panoskarabelas.com/blog/posts/hdr_in_under_10_minutes/
// NOTE: this should be applied before any tonemapping/gamma correction/etc
float3 sRGBToHDR10(float3 color, float scalar)
{
	// just don't tonemap if HDR is disabled
	if (!(HDR_ENABLED != 0.0)) {
		return color;
	}
	
	// undo 2.2 gamma since input is sRGB and we want linear
	color = pow(color, 2.2);
	
    float white_point = HDR_WHITEPOINT_NITS;

    // Convert Rec.709 to Rec.2020 color space to broaden the palette
    static const float3x3 from709to2020 =
    {
        { 0.6274040f, 0.3292820f, 0.0433136f },
        { 0.0690970f, 0.9195400f, 0.0113612f },
        { 0.0163916f, 0.0880132f, 0.8955950f }
    };   
    color = mul(from709to2020, color);

    // Normalize HDR scene values ([0..>1] to [0..1]) for ST.2084 curve
    color *= white_point * scalar / HDR_ST2084_MAX;

    // Apply ST.2084 (PQ curve) for HDR10 standard
    static const float m1 = 2610.0 / 4096.0 / 4;
    static const float m2 = 2523.0 / 4096.0 * 128;
    static const float c1 = 3424.0 / 4096.0;
    static const float c2 = 2413.0 / 4096.0 * 32;
    static const float c3 = 2392.0 / 4096.0 * 32;
    float3 cp             = pow(abs(color), m1);
    color                 = pow((c1 + c2 * cp) / (1 + c3 * cp), m2);

    return color;
}

#endif