#include "raylib.h"
#include <string>
#include <iostream>
using namespace std;
int main() {
    // Initialize the window and audio device
    InitWindow(800, 450, "Simple Audio Player with Raylib");
    InitAudioDevice();  // Initialize the audio device
    Music music = LoadMusicStream("../misato.wav"); // Load File
    float pitch = 1.0f; //Load pitch to standard
    PlayMusicStream(music);
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        UpdateMusicStream(music);
        if (IsKeyPressed(KEY_UP)) pitch+=0.1f;
        if (IsKeyPressed(KEY_DOWN)) pitch-=0.1f;
        if (pitch < 0.1f) pitch = 0.1f;
        cout << pitch;
        SetMusicPitch(music, pitch);

        // Control play/pause with SPACE key
        if (IsKeyPressed(KEY_SPACE)) {
            if (IsMusicStreamPlaying(music)) PauseMusicStream(music);
            else ResumeMusicStream(music);
        }
        
        if (IsKeyPressed(KEY_ENTER)) StopMusicStream(music);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        DrawText("Playing Music", 120, 150, 20, GREEN);
        DrawText("Press SPACE to play sound, ENTER to stop", 120, 200, 20, DARKGRAY);
        DrawText("Designed By M.Winer 2024",120,425,10,BLACK);

        EndDrawing();
    }

    // Unload sound and close audio device
    UnloadMusicStream(music);
    CloseAudioDevice();  // Close the audio device
    CloseWindow();       // Close window
    return 0;
}
