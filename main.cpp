#include "raylib.h"
#include <string>
int main() {
    // Initialize the window and audio device
    InitWindow(800, 450, "Simple Audio Player with Raylib");
    InitAudioDevice();  // Initialize the audio device
    Music music = LoadMusicStream("../misato.wav");
    float pitch = 1.1f;
    PlayMusicStream(music);

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        UpdateMusicStream(music);
        SetMusicPitch(music, pitch);

        // Control play/pause with SPACE key
        if (IsKeyPressed(KEY_SPACE)) {
            if (IsMusicStreamPlaying(music)) PauseMusicStream(music);
            else ResumeMusicStream(music);
        }
        if (IsKeyPressed(KEY_ENTER)) StopMusicStream(music);

        // Begin drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Playing Music", 120, 150, 20, GREEN);
        DrawText("Press SPACE to play sound, ENTER to stop", 120, 200, 20, DARKGRAY);

        EndDrawing();
    }

    // Unload sound and close audio device
    UnloadMusicStream(music);
    CloseAudioDevice();  // Close the audio device
    CloseWindow();       // Close window

    return 0;
}
