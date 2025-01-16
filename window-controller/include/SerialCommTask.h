#ifndef __SERIALCOMMTASK__
#define __SERIALCOMMTASK__

#include "WindowControlTask.h"

class SerialCommTask {
private:
    WindowControlTask* windowControlTask;
    String ackMessage;
    int windowOpeningLevel;
    int mode;

    void parseMessage(String message);
    void handleRequestMessage(String message);
    void sendStatusMessage();
    void sendErrorMessage();

public:
    SerialCommTask(WindowControlTask* windowControlTask);
    void init();
    void tick();
};

#endif
