#include "Sprite2D.h"

Sprite2D::Sprite2D()
{
    initTime = GetTime();
}

void Sprite2D::LoadSprite(Texture2D texture, unsigned int rows, unsigned int cols)
{
    loadedByTexture = true;
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
    this->texture = texture;

    // set rect size

    rect_width = this->texture.width / cols;
    rect_height = this->texture.height / rows;

    SetOrigin(O_TOP_LEFT);
}

void Sprite2D::LoadSprite(const char *texture_path, unsigned int rows, unsigned int cols)
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

Sprite2D::Sprite2D(const char *texture_path, unsigned int rows, unsigned int cols)
{
    LoadSprite(texture_path,rows,cols);
}

double Sprite2D::GetInitTime()
{
    return initTime;
}

void Sprite2D::Draw()
{
    _Draw(position);
}

void Sprite2D::SelectRect(unsigned int row, unsigned int column)
{
    ccol = column * rect_width;
    crow = (row-1)*rect_height;
}

void Sprite2D::DrawRectAt(unsigned int row, unsigned int column, Vector2 position)
{
    _Draw(position,(row-1)*rect_height,column * rect_width);
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

bool Sprite2D::IsAnimationPlaying()
{
    return anim_playing;
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

    float ow = rect_width;
    float oh = rect_height;

    rect_width *= scale.x;
    rect_height *= scale.y;
    
    SetOrigin(current_origin);

    rect_width = ow;
    rect_height = oh;
}
void Sprite2D::SetOrigin(Origins origin_value)
{
    current_origin = origin_value;
    switch (origin_value)
    {
    case O_TOP_LEFT:
        origin = {0.0f, 0.0f}; // Top-left corner
        break;
    case O_CENTER_LEFT:
        origin = {0.0f, rect_height * 0.5f}; // Middle of left edge
        break;
    case O_BOTTOM_LEFT:
        origin = {0.0f, rect_height}; // Bottom-left corner
        break;
    case O_BOTTOM_CENTER:
        origin = {rect_width * 0.5f, rect_height}; // Middle of bottom edge
        break;
    case O_BOTTOM_RIGHT:
        origin = {rect_width, rect_height}; // Bottom-right corner
        break;
    case O_CENTER_RIGHT:
        origin = {rect_width, rect_height * 0.5f}; // Middle of right edge
        break;
    case O_TOP_RIGHT:
        origin = {rect_width, 0.0f}; // Top-right corner
        break;
    case O_CENTER_TOP:
        origin = {rect_width * 0.5f, 0.0f}; // Middle of top edge
        break;
    case O_CENTER:
        origin = {rect_width * 0.5f, rect_height * 0.5f}; // Center of texture
        break;
    default:
        origin = {0.0f, 0.0f}; // Fallback to top-left
        break;
    }
}
Rectangle Sprite2D::GetRect()
{
    return d_rect;
}

void Sprite2D::_Draw(Vector2 _position, int _crow, int _ccol)
{
    // Default to current frame values
    if (_crow == -1 || _ccol == -1) {
        _crow = crow;
        _ccol = ccol;
    }

    // Handle animation frame updates
    if (animation.frames > 1 && anim_playing) {
        frame_count++;
        if (frame_count >= (60 / animation_speed)) {
            frame_count = 0;
            current_frame++;

            if (current_frame >= animation.frames) {
                current_frame = animation.start_frame - 1;

                if (!animation.loop) {
                    anim_playing = false;
                    return;
                }
            }

            ccol = current_frame * rect_width;
            crow = rect_height * (animation.row - 1);
        }
    }

    // Build source rectangle (with flipping)
    Rectangle s_rect = {
        (float)_ccol,
        (float)_crow,
        (flipped_h ? -1.f : 1.f) * (float)rect_width,
        (flipped_v ? -1.f : 1.f) * (float)rect_height
    };
    
    // Build destination rectangle
    d_rect = {
        _position.x,
        _position.y,
        rect_width  * scale.x,
        rect_height * scale.y
    };
    

    // Draw with custom alpha
    Color tintWithAlpha = ColorAlpha(WHITE, alpha / 255.0f);
    DrawTexturePro(texture, s_rect, d_rect, origin, rotation, tintWithAlpha);
}


void Sprite2D::DrawOutline(Color color)
{
    DrawRectangleLines(d_rect.x,d_rect.y,d_rect.width,d_rect.height,color);
}

Animation::Animation(unsigned int frames, unsigned int start_frame, unsigned int row,bool loop)
{
    this->frames = frames;
    this->start_frame = start_frame;
    this->row = row;
    this->loop = loop;
}

Sprite2D::~Sprite2D()
{
    if (!loadedByTexture){

        UnloadTexture(texture);
    }
}