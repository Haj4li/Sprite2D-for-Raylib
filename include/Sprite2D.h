#include <raylib.h>

struct Animation
{
    unsigned int frames;
    unsigned int start_frame;
    unsigned int row;
    Animation(unsigned int frames=1, unsigned int start_frame=1, unsigned int row=1);
};

enum Origins {
    O_TOP_LEFT,
    O_CENTER_LEFT,
    O_BOTTOM_LEFT,
    O_BOTTOM_CENTER,
    O_BOTTOM_RIGHT,
    O_CENTER_RIGHT,
    O_TOP_RIGHT,
    O_CENTER_TOP,
    O_CENTER
};

class Sprite2D
{
    private:
        Texture2D texture;

        unsigned int rect_width,rect_height;
        Rectangle d_rect;
        unsigned int rows,cols;
        unsigned int crow,ccol;

        Vector2 origin;
        bool flipped_h = false;
        bool flipped_v = false;

        unsigned int animation_speed = 10;
        Animation animation;
        unsigned int current_frame = 0;
        unsigned int frame_count = 0;
        bool anim_playing = false;

        
    public:
        // Variables
        Vector2 position;
        Vector2 scale;
        float rotation = 0;


        // Functions
        /*
            Sprite2D class constructor
            you have to define the texture path 
            if your texture is not a tilemap or spritesheet leave the two other parameters undefined
            else please define the total rows and columns of the texture
        */
        Sprite2D(const char* texture_path, unsigned int rows = 1, unsigned int cols = 1);
        /*
            This function simply draw the texture on the screen
            you have to call this function between the BeginDrawing & EndDrawing
        */
        void Draw();
        /*
            This function can be used for debugging
            it draw a border around the texture
        */
        void DrawOutline(Color color);
        /*
            If your texture is a tilemap or spritesheet you can select a part of it to be drawn
        */
        void SelectRect(unsigned int row, unsigned int column);
        /*
            You can set the main animation of the sprite and the speed of animation playing
        */
        void SetAnimation(Animation anim, unsigned int speed=5);
        /*
            You can pause or play the animation with this function
        */
        void AnimationPlay(bool play);

        ~Sprite2D();

        /*
            Use this function to flip the texture horizontally or vertically
        */
        void Flip(bool flipped_h,bool flipped_v);
        /*
            You can easly scale the texture with this function
        */
        void Scale(float x=1,float y=1);
        /*
            Set the origin of the sprite for drawing, rotating or scale 
            You can use this values for this function :
                O_TOP_LEFT,
                O_CENTER_LEFT,
                O_BOTTOM_LEFT,
                O_BOTTOM_CENTER,
                O_BOTTOM_RIGHT,
                O_CENTER_RIGHT,
                O_TOP_RIGHT,
                O_CENTER_TOP,
                O_CENTER
        */
        void SetOrigin(Origins origin_value);
        /*
            Return's the destination rectangle of the sprite
        */
        Rectangle GetRect();
};




