namespace ca {

struct SLParameters {
    
	static int GetPresetCount();
    static SLParameters GetPreset(int preset);
    
    float inner_radius;
    float outer_radius;
    float border;
    float b1, b2;
    float d1, d2;
    float alphan;
    float alpham;
    float dt;
};


}