namespace ca {

struct ColorScheme {
    static int GetPresetCount();
    static ColorScheme GetPreset(int i);
    
    float background_color[4];
    float color1[4];
    float color2[4];
    float color3[4];
    float color4[4];
};

}  // namespace ca