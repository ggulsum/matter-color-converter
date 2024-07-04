#include <stdio.h>
#include <math.h>

// Struct to hold gamma correction parameters
typedef struct {
    float gamma;
    float transition;
    float slope;
    float offset;
} GammaCorrection;

// Struct to hold a 3x3 matrix
typedef struct {
    float data[3][3];
} Matrix;

// Struct to hold RGB color values
typedef struct {
    float r, g, b;
} Color;

// Struct to hold XYZ color values
typedef struct {
    float x, y, z;
} XYZ;

// Struct to hold xyY color values
typedef struct {
    float x, y, Y;
} xyY;

// Function to apply gamma correction
float gamma_correction(float value, const GammaCorrection *gc) {
    if (value <= gc->transition) {
        return gc->slope * value;
    }
    return (1 + gc->offset) * powf(value, gc->gamma) - gc->offset;
}

// Function to apply inverse gamma correction
float inv_gamma_correction(float value, const GammaCorrection *gc) {
    float gammaInv = 1.0f / gc->gamma;
    float transitionInv = gamma_correction(gc->transition, gc);
    float slopeInv = 1.0f / gc->slope;

    if (value <= transitionInv) {
        return value * slopeInv;
    }
    return powf((value + gc->offset) / (1 + gc->offset), gammaInv);
}

// Function to multiply a matrix by an array
void matrix_times_array(const Matrix *m, const float *v, float *result) {
    for (int i = 0; i < 3; ++i) {
        result[i] = 0.0f;
        for (int j = 0; j < 3; ++j) {
            result[i] += m->data[i][j] * v[j];
        }
    }
}

// Function to convert RGB to XYZ color space
XYZ rgbToXYZ(Color color, const Matrix *matrix, const GammaCorrection *gc) {
    float rgb[3] = {
        inv_gamma_correction(color.r, gc),
        inv_gamma_correction(color.g, gc),
        inv_gamma_correction(color.b, gc)
    };
    float xyz[3];
    matrix_times_array(matrix, rgb, xyz);
    return (XYZ){xyz[0], xyz[1], xyz[2]};
}

// Function to convert XYZ to xyY color space
xyY xyzToXyY(XYZ xyz) {
    float sum = xyz.x + xyz.y + xyz.z;
    if (sum < 1e-12) {
        return (xyY){0.3127f, 0.3290f, 0.0f}; // D65 white point
    }
    return (xyY){xyz.x / sum, xyz.y / sum, xyz.y};
}

// Function to convert xyY to XYZ color space
XYZ xyYToXYZ(xyY xyYColor) {
    float z = 1.0f - xyYColor.x - xyYColor.y;
    return (XYZ){(xyYColor.Y / xyYColor.y) * xyYColor.x, xyYColor.Y, (xyYColor.Y / xyYColor.y) * z};
}

// Function to convert XYZ to RGB color space
Color xyzToRGB(XYZ xyz, const Matrix *matrixInv, const GammaCorrection *gc) {
    float rgb[3];
    float xyzArray[3] = {xyz.x, xyz.y, xyz.z};
    matrix_times_array(matrixInv, xyzArray, rgb);
    return (Color){
        .r = gamma_correction(rgb[0], gc),
        .g = gamma_correction(rgb[1], gc),
        .b = gamma_correction(rgb[2], gc)
    };
}

// Function to round RGB color values to nearest integer
Color round_color(Color color) {
    return (Color){
        .r = roundf(color.r * 255.0f) / 255.0f,
        .g = roundf(color.g * 255.0f) / 255.0f,
        .b = roundf(color.b * 255.0f) / 255.0f
    };
}

int main() {
	// Initialize gamma correction and matrices
	GammaCorrection gc = {0.42f, 0.003f, 12.93f, 0.055f};
	Matrix matrix = {{
    	{0.4125f, 0.3576f, 0.180423f},
    	{0.2127f, 0.7152f, 0.0722f},
    	{0.0193f, 0.1192f, 0.9503f}
	}};
	Matrix matrixInv = {{
    	{3.2405f, -1.5371f, -0.4985f},
    	{-0.9693f, 1.8760f, 0.0416f},
    	{0.0556f, -0.2040f, 1.0572f}
	}};
    
	float r, g, b;
	printf("Enter RGB values (0-255) separated by spaces: ");
	scanf("%f %f %f", &r, &g, &b);
    
	// Normalize the input RGB values
	Color sampleColor = {r / 255.0f, g / 255.0f, b / 255.0f};
	XYZ xyz = rgbToXYZ(sampleColor, &matrix, &gc);
	xyY xyYColor = xyzToXyY(xyz);
	XYZ newXYZ = xyYToXYZ(xyYColor);
	Color newColor = xyzToRGB(newXYZ, &matrixInv, &gc);
	newColor = round_color(newColor);

	printf("Converted to xyY: x=%.3f, y=%.3f\n", xyYColor.x, xyYColor.y);
	printf("Converted back to RGB: R=%.3f, G=%.3f, B=%.3f\n", newColor.r * 255, newColor.g * 255, newColor.b * 255);


	return 0;
}


