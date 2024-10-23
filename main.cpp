#include "raylib.h"
#include <string>
int main() {
    // Initialize the window and audio device
    InitWindow(800, 450, "Simple Audio Player with Raylib");
    InitAudioDevice();  // Initialize the audio device

    Sound sound = LoadSound("../misato.wav");  // You can replace this with your own audio file

    // Main game loop
    while (!WindowShouldClose()) {
        // Play sound on spacebar press
        if (IsKeyPressed(KEY_SPACE)) {
            PlaySound(sound);
        }

        // Stop sound on enter press
        if (IsKeyPressed(KEY_ENTER)) {
            StopSound(sound);
        }

        // Begin drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText(sound,120,150,20,GREEN);
        DrawText("Press SPACE to play sound, ENTER to stop", 120, 200, 20, DARKGRAY);

        EndDrawing();
    }

    // Unload sound and close audio device
    UnloadSound(sound);
    CloseAudioDevice();  // Close the audio device
    CloseWindow();       // Close window

    return 0;
}