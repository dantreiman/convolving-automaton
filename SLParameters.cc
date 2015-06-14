#include "SLParameters.h"

namespace ca {


static SLParameters SmoothLifeL = {
    10.0/3.0,
    10,
    1,
    0.257,
    0.336,
    0.365,
    0.549,
    0.028,
    0.147,
    0.1
};


static SLParameters Protoplasm = {
    10.0/3.0,
    10,
    1,
    0.305,
    0.443,
    0.556,
    0.814,
    0.028,
    0.147,
    0.1
};


static SLParameters ExplodingGliders = {
    12.7/3.0,
    12.7,
    .7,
    0.361,
    0.402,
    0.142,
    0.511,
    0.028,
    0.147,
    0.1
};

static SLParameters SmoothLifeM = {
    4.0,
    12.0,
    0.0,
    0.241,
    0.327,
    0.358,
    0.490,
    0.028,
    0.147,
    0.1
};

int SLParameters::GetPresetCount() {
    return 4;
}


SLParameters SLParameters::GetPreset(int preset) {
    switch (preset) {
        case 0:
            return SmoothLifeL;
        case 1:
            return ExplodingGliders;
        case 2:
            return Protoplasm;
		case 3:
            return SmoothLifeM;
    }
    return SmoothLifeL;
}

}  // namespace ca