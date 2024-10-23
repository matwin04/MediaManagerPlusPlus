#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include <string>
#include <iostream>
using namespace std;
float controlPitch(float pitch) {
    static bool pitchEditMode = false;
    static int pitchValue = (int)(pitch*50);
    if (GuiSpinner((Rectangle){ 350, 200, 120, 50 }, "Pitch", &pitchValue, 10, 200, pitchEditMode)) {
        pitchEditMode = !pitchEditMode;
    }
    return pitchValue / 50.0f;
}
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

        //Pitch Related
        pitch = controlPitch(pitch);
        //Set Music
        SetMusicPitch(music, pitch);
        // Control play/pause with SPACE key
        if (IsKeyPressed(KEY_SPACE)) {
            if (IsMusicStreamPlaying(music)) PauseMusicStream(music);
            else ResumeMusicStream(music);
        }
        if (IsKeyPressed(KEY_ENTER)) StopMusicStream(music);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        char pitchText[64];
        sprintf(pitchText, "Current Pitch: %.2f", pitch);
        DrawText(pitchText, 20, 20, 30, MAROON);
        EndDrawing();
    }

    // Unload sound and close audio device
    UnloadMusicStream(music);
    CloseAudioDevice();  // Close the audio device
    CloseWindow();       // Close window
    return 0;
}
