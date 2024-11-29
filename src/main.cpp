#include <iostream>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include "MediaServer.h"
using namespace std;
using namespace ftxui;

int main(){
    auto startBtn = Button("Start Server",[&]{});
    auto stopBtn = Button("Stop Button",[&]{});
    auto quitBtn = Button("Quit", [&]{});
    auto layout = Container::Vertical({
        startBtn,
        stopBtn,
        quitBtn,
    });
    auto renderer = Renderer(layout, [&] {
        return vbox({
            text("DLNA Media Server CLI") | center,
            separator(),
            startBtn->Render(),
            stopBtn->Render(),
            quitBtn->Render(),
        });
    });

    auto screen = ScreenInteractive::TerminalOutput();
    screen.Loop(renderer);
    cout << "Hello World\n";
    cout << "MediaManager ++ version 1\n";
    return 0;
}