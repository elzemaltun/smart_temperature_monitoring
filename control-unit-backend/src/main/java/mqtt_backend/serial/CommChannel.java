package mqtt_backend.serial;

// An interface for msg communication

public interface CommChannel {

    void sendMsg(String msg);
    String receiveMsg() throws InterruptedException;
    boolean isMsgAvailable();

}
