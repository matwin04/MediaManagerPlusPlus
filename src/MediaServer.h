#ifndef MEDIASERVER_H
#define MEDIASERVER_H

#include <upnp/upnp.h>
class MediaServer {
    public:
        MediaServer();
        ~MediaServer();

        bool start();
        void stop();
        bool isRunning() const;
    private:
        UpnpClient_Handle handle;
        bool running;
};
#endif // MEDIASERVER_H