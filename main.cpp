#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include <string>
#include <iostream>
using namespace std;
float controlPitch(float pitch) {
    static bool pitchEditMode = false;
    static int pitchValue = (int)(pitch*50);
    if (GuiSpinner((Rectangle){ 350, 200, 120, 24 }, "Pitch", &pitchValue, 10, 200, pitchEditMode)) {
        pitchEditMode = !pitchEditMode;
    }
    return pitchValue / 50.0f;
}
void progBar(float progress) {
    GuiProgressBar((Rectangle){10,250,750,34},NULL, NULL, &progress, 0.0f, 1.0f);
}
int main() {
    // Initialize the window and audio device
    InitWindow(800, 450, "Simple Audio Player with Raylib");
    InitAudioDevice();  // Initialize the audio device
    Music music = LoadMusicStream("../misato.wav"); // Load File

    float pitch = 1.0f;
    float progress = 0.0f;

    PlayMusicStream(music);
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        UpdateMusicStream(music);

        //Pitch Related
        pitch = controlPitch(pitch);
        //Set Music
        SetMusicPitch(music, pitch);
        // get progress
        progress = GetMusicTimePlayed(music) / GetMusicTimeLength(music);  // Progress from 0.0 to 1.0

        // Control play/pause with SPACE key
        if (IsKeyPressed(KEY_SPACE)) {
            if (IsMusicStreamPlaying(music)) PauseMusicStream(music);
            else ResumeMusicStream(music);
        }
        if (IsKeyPressed(KEY_ENTER)) StopMusicStream(music);

        BeginDrawing();
        ClearBackground(BLACK);
        char pitchText[64];
        sprintf(pitchText, "Current Pitch: %.2f", pitch);
        DrawText(pitchText, 20, 20, 30, MAROON);
        progBar(progress);
        EndDrawing();
    }

    // Unload sound and close audio device
    UnloadMusicStream(music);
    CloseAudioDevice();  // Close the audio device
    CloseWindow();       // Close window
    return 0;
}
