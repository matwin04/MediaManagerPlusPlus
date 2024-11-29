#include "MediaServer.h"
#include "UUIDGen.h"
#include <iostream>
#include <filesystem>

using namespace std;

MediaServer::MediaServer() : handle(0), running(false) {}

MediaServer::~MediaServer() {
    stop();
}

bool MediaServer::start() {
    const string device_description_path = "MediaServer.xml";

    // Check if the XML file exists
    if (!filesystem::exists(device_description_path)) {
        cerr << "Device description XML file not found: " << device_description_path << "\n";
        return false;
    }

    // Use UUIDGen to handle the XML file
    UUIDGen uuidGen(device_description_path);
    string content = uuidGen.readFile();
    if (content.empty()) {
        cerr << "Failed to read the XML file.\n";
        return false;
    }

    content = uuidGen.replacePlaceholder(content, "uuid:PLACEHOLDER_UUID");
    if (content.empty()) {
        cerr << "Failed to replace the placeholder UUID.\n";
        return false;
    }

    if (!uuidGen.writeFile(content)) {
        cerr << "Failed to write the updated XML file.\n";
        return false;
    }

    // Initialize UPnP
    if (UpnpInit2(nullptr, 0) != UPNP_E_SUCCESS) {
        cerr << "Failed to initialize UPnP.\n";
        return false;
    }

    // Register the root device
    int result = UpnpRegisterRootDevice(device_description_path.c_str(), nullptr, nullptr, &handle);
    if (result != UPNP_E_SUCCESS) {
        cerr << "Failed to register DLNA Media Server. Error code: " << result << "\n";
        UpnpFinish();
        return false;
    }

    running = true;
    cout << "DLNA Media Server Started Successfully.\n";
    return true;
}

void MediaServer::stop() {
    if (running) {
        UpnpUnRegisterRootDevice(handle);
        UpnpFinish();
        running = false;
        cout << "DLNA Media Server Stopped.\n";
    }
}

bool MediaServer::isRunning() const {
    return running;
}