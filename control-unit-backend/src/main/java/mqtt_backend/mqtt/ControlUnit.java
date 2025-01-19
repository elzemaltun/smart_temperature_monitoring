package mqtt_backend.mqtt;

import io.netty.resolver.InetNameResolver;
import mqtt_backend.serial.SerialCommunicator;

public class ControlUnit {
    
    private SystemState currentState;
    private float T1, T2;
    private float DT;
    private int F1, F2;
    private SerialCommunicator serialCommunicator;

    // initialize the serial communiator in the constructor
    public ControlUnit() throws Exception {
        serialCommunicator = new SerialCommunicator("COM3", 9600);
        T1 = 27; // Celcius
        T2 = 34; // Celcius
        F1 = 3;
        F2 = 5;
        DT = 10000; // 10 seconds
    }

    public void updateState(float currentTemperature){
        int motorAngle = 0;
        int frequency = F1; // initial frequency of the temp check
        String mode = "";

        switch(currentState){
            case NORMAL:
                if (currentTemperature < T1){
                    mode = "NORMAL";
                    motorAngle = 0;
                    frequency = F1;
                }
                break;
            case HOT:
                if ( T1 <= currentTemperature && currentTemperature <= T2){
                    mode = "HOT";
                    motorAngle = calculateMotorAngle(currentTemperature);
                    frequency = F2;
                }
                break;
            case TOO_HOT:
                if (currentTemperature > T2){
                    mode = "TOO_HOT";
                    motorAngle = 90;
                    // if time > DT treshold, ALARM
                }
                break;
            case ALARM:
                mode = "ALARM";
                // wait until a flag raised from the operator dashboard
                break;
        }
        sendMsgToArduino(motorAngle, mode);
    }

    public int calculateMotorAngle(float temperature){
        int motorAngle = (int) ((temperature - T1) / (T2 - T1) * 90);
        return motorAngle;
    }

    private void sendMsgToArduino(int motorAngle, String mode){
        String message = "{REQ, " + mode + ", " + motorAngle + "}";
        serialCommunicator.sendMsg(message);
    }

}
