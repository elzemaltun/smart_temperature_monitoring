// package mqtt_backend.mqtt;

// public class ControlUnit {
    
//     private SystemState currentState;
//     private float T1, T2;
//     private float DT;

//     public void updateState(float currentTemperature){
//         switch(currentState){
//             case NORMAL:
//                 if (currentTemperature < T1){
//                     // Motor = 0
//                     // Freq = F
//                 }
//             case HOT:
//                 if ( T1 <= currentTemperature && currentTemperature <= T2){
//                     // Motor = calculated according to the temp with interpolation
//                     // Freq > F1
//                 }
//             case TOO_HOT:
//                 if (currentTemperature > T2){
//                     // Motor = 90
//                     // if time > DT treshold, ALARM
//                 }
//             case ALARM:
//                 // wait until a flag raised from the operator dashboard
//         }
//     }

// }
