#include "Game.h"
#include <random>


// Don't forget to like and subscribe to my channel :D
// https://www.youtube.com/@sudoAliyt
// My github : https://github.com/Haj4li

int main() {
    
    // Initialize the window
    InitWindow(800,600,"Sprite2D | Subscribe please -");

    // Create the Player, Healthbar and Medkit Sprite
    Sprite2D healtBar("Assets/HealthBar.png",1,24); // This sprite has 24 columns
    Sprite2D medKit("Assets/Medkit.png"); // this one has only 1 row and 1 column
    Sprite2D player("Assets/Player.png",21,13); // this sprite has 21 rows and 13 columns

    // Sprite2D can handle spritesheets

    // Healthbar settings
    healtBar.position.x = 25;
    healtBar.position.y = 25;
    healtBar.scale.x = 2;
    healtBar.scale.y = 2;


    // Medkit settings
    medKit.position.x = 200;
    medKit.position.y = 200;
    medKit.scale.x = 0.85;
    medKit.scale.y = 0.85;

    // Player settings
    player.position.x = 400;
    player.position.y = 300;
    
    int player_health = 2;

    // Set health bar value to player health
    healtBar.SelectRect(1,player_health);

    // Sprite2D class can handle multiple animations
    // You just need to create an animation object

    Animation player_walk_l(9,1,10);
    Animation player_walk_t(9,1,9);
    Animation player_walk_d(9,1,11);
    Animation player_walk_r(9,1,12);

    // Load background texture
    Texture2D bg = LoadTexture("Assets/BG.png");


    // Random numbers
    std::random_device rd;  // Seed generator from hardware or system
    std::mt19937 mt(rd()); // Mersenne Twister engine

    // We need to make sure that the random position is visible in the screen x  and y
    std::uniform_int_distribution<int> distx(50, 750);
    std::uniform_int_distribution<int> disty(50, 550);


    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Update   
        // Movement
        if (IsKeyDown(KEY_A))
        {
            // You can set the animation speed with SetAnimation function
            player.SetAnimation(player_walk_l,10);
            player.AnimationPlay(true);
            player.position.x -=2.5;
        }
        else if (IsKeyDown(KEY_D))
        {
            player.SetAnimation(player_walk_r,10);
            player.AnimationPlay(true);
            player.position.x +=2.5;
        }
        else if (IsKeyDown(KEY_W))
        {
            player.SetAnimation(player_walk_t,10);
            player.AnimationPlay(true);
            player.position.y -=2.5;
        }
        else if (IsKeyDown(KEY_S))
        {
            player.SetAnimation(player_walk_d,10);
            player.AnimationPlay(true);
            player.position.y +=2.5;
        }
        else
        {
            // Stop animation when player stop moving
            player.AnimationPlay(false);
        }

        if (CheckCollisionRecs(medKit.GetRect(),player.GetRect()) && player_health< 23)
        {
            player_health += 2;
            if (player_health >= 23)
            {
                player_health = 23;
                // Grow player size when health is full
                player.scale.x = 1.5;
                player.scale.y = 1.5;
            }

            // Send medkit to random position
            medKit.position.x = distx(mt);
            medKit.position.y = disty(mt);

            // Update the health bar
            healtBar.SelectRect(1,player_health);

        }

        // Draw
        BeginDrawing();

        ClearBackground(WHITE);

        // Draw Background
        DrawTexture(bg,0,0,WHITE);

        // Draw objects
        medKit.Draw();
        //medKit.DrawOutline(RED); // you can draw outline for sprites to see the hitbox too

        player.Draw();
        //player.DrawOutline(BLUE); // you can draw outline for sprites to see the hitbox too

        healtBar.Draw();

        EndDrawing();
    }
    CloseWindow();

    return 0;
}