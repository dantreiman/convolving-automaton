#include "ColorScheme.h"

namespace ca {

static ColorScheme Undersea = {
    {0.0, 0.0, 0.0, 1.0},
    {33/255.0, 98./255.0, 227/255.0, 1.0},
    {0.0, 233/255.0, 255/255.0, 1.0},
    {0.0, 176/255.0, 255/255.0, 1.0},
    {68/255.0, 0, 242/255.0, 1.0}
};

static ColorScheme Silver = {
    {0.0, 0.0, 0.0, 1.0},
    {0.1, 0.1, 0.1, 1.0},
    {1.0, 1.0, 1.0, 1.0},
    {.6, .6, .6, 1.0},
    {.3, .3, .3, 1.0}
};

static ColorScheme Jupiter = {
    {.1, .1, .1, 1.0},
    {223/255.0, 81/255.0, 61/255.0, 1.0},
    {212/255.0, 46/255.0, 108/255.0, 1.0},
    {129/255.0, 4/255.0, 38/255.0, 1.0},
    {284/255.0, 201/255.0, 40/255.0, 1.0}
};


int ColorScheme::GetPresetCount() {
    return 3;
}

ColorScheme ColorScheme::GetPreset(int i) {
    switch (i) {
        case 0:
            return Undersea;
        case 1:
            return Silver;
        case 2:
            return Jupiter;
    }
    return Undersea;
}

}  // namespace ca