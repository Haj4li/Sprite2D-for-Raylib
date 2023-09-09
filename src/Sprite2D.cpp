#include "Sprite2D.h"

Sprite2D::Sprite2D(const char* texture_path, unsigned int rows, unsigned int cols)
{
    position = Vector2{0,0};
    scale = Vector2{1,1};
    if (rows <= 0){
        rows = 1;
    }
    if (cols <= 0){
        cols = 1;
    }
    ccol = 0;
    crow = 0;


    this->rows = rows;
    this->cols = cols;

    // load texture
    texture = LoadTexture(texture_path);

    // set rect size

    rect_width = texture.width / cols;
    rect_height = texture.height / rows;

    SetOrigin(O_TOP_LEFT);
}

void Sprite2D::SelectRect(unsigned int row, unsigned int column)
{
    ccol = column * rect_width;
    crow = (row-1)*rect_height;
}

void Sprite2D::SetAnimation(Animation anim, unsigned int speed)
{
    animation = anim;
    animation_speed = speed;
}

void Sprite2D::AnimationPlay(bool play)
{
    anim_playing = play;
}

void Sprite2D::Flip(bool flipped_h,bool flipped_v)
{
    this->flipped_h = flipped_h;
    this->flipped_v = flipped_v;
}
void Sprite2D::Scale(float x, float y)
{
    scale.x = x;
    scale.y = y;
}
void Sprite2D::SetOrigin(Origins origin_value)
{
    // set the origin
    switch (origin_value)
    {
    case O_TOP_LEFT:
        origin = {0,0};
        break;
    case O_CENTER_LEFT:
        origin = {(float)rect_height/2,0};
        break;
    case O_BOTTOM_LEFT:
        origin = {(float)rect_height,0};
        break;
    case O_BOTTOM_CENTER:
        origin = {(float)rect_height,(float)rect_width/2};
        break;
    case O_BOTTOM_RIGHT:
        origin = {(float)rect_height,(float)rect_width};
        break;
    case O_CENTER_RIGHT:
        origin = {(float)rect_height/2,(float)rect_width};
        break;
    case O_TOP_RIGHT:
        origin = {0,(float)rect_width};
        break;
    case O_CENTER_TOP:
        origin = {0,(float)rect_width/2};
        break;
    case O_CENTER:
        origin = {(float)rect_width/2,(float)rect_height/2};
        break;
    default:
        break;
    }

}
Rectangle Sprite2D::GetRect()
{
    return d_rect;
}
void Sprite2D::Draw()
{
    
    if (animation.frames > 1 && anim_playing) // has animation
    {
        frame_count++;
        if (frame_count >= (60/animation_speed))
        {
            frame_count = 0;
            current_frame++;
            if (current_frame >= animation.frames)
            {
                current_frame = animation.start_frame-1;
            }

            ccol = current_frame * rect_width;
            crow = rect_height * (animation.row-1);
        }
    }
    Rectangle s_rect = Rectangle{(float)ccol, (float)crow, (flipped_h ? -(float)rect_width : (float)rect_width), (flipped_v ? -(float)rect_height : (float)rect_height)};

    d_rect = Rectangle{position.x, position.y, rect_width * scale.x, rect_height * scale.y};

    DrawTexturePro(texture, s_rect, d_rect, origin, rotation, WHITE);

}

void Sprite2D::DrawOutline(Color color)
{
    DrawRectangleLines(d_rect.x,d_rect.y,d_rect.width,d_rect.height,color);
}

Animation::Animation(unsigned int frames, unsigned int start_frame, unsigned int row)
{
    this->frames = frames;
    this->start_frame = start_frame;
    this->row = row;
}

Sprite2D::~Sprite2D()
{
    UnloadTexture(texture);
}