#ifndef __SERIALCOMMTASK__
#define __SERIALCOMMTASK__

#include "Task.h"
#include "WindowControlTask.h"

class SerialCommTask : public Task {
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
    void init(int period) override; // Inherit from Task
    void tick() override;          // Inherit from Task
    void readSerial();             // Read serial messages
};

#endif
