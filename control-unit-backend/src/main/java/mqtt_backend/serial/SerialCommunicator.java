package mqtt_backend.serial;

import java.util.concurrent.*;
import jssc.*;

public class SerialCommunicator implements CommChannel, SerialPortEventListener {
    
    private SerialPort serialPort;
    private BlockingQueue<String> queue; // for thread safety, handle events in seperate threads
    private StringBuffer currentMsg = new StringBuffer("");

    public void SerialCommChannel(String port, int rate) throws Exception{
        queue = new ArrayBlockingQueue<String>(100);

        serialPort = new SerialPort(port);
        serialPort.openPort();
        serialPort.setParams(rate, SerialPort.DATABITS_8, SerialPort.STOPBITS_1, SerialPort.PARITY_NONE); // 8 bits for data, 1 bit for stop, none bits for error checking
        serialPort.setFlowControlMode(SerialPort.FLOWCONTROL_RTSCTS_IN | SerialPort.FLOWCONTROL_RTSCTS_OUT) //send and receive data
        serialPort.addEventListener(this);
    }

    @Override
    public void sendMsg(String msg){
        char[] array = (msg+"\n").toCharArray(); // indicate the end of the message 
        byte[] bytes = new byte[array.length]; // convert characters to byte
        for (int i = 0; i<array.length; i++){
            bytes[i] = (byte) array[i];
        }
        try {
			synchronized (serialPort) {
				serialPort.writeBytes(bytes);
			}
		} catch(Exception ex){
			ex.printStackTrace();
		}
    }

    @Override
	public String receiveMsg() throws InterruptedException {
		// TODO Auto-generated method stub
		return queue.take();
	}

	@Override
	public boolean isMsgAvailable() {
		// TODO Auto-generated method stub
		return !queue.isEmpty();
	}

    public void close() {
		try {
			if (serialPort != null) {
				serialPort.removeEventListener();
				serialPort.closePort();
			}
		} catch (Exception ex) {
			ex.printStackTrace();
		}
	}


	public void serialEvent(SerialPortEvent event) {
		/* if there are bytes received in the input buffer */
		if (event.isRXCHAR()) {
            try {
            	    String msg = serialPort.readString(event.getEventValue());
            		
            		msg = msg.replaceAll("\r", "");
            		
            		currentMsg.append(msg);
            		
            		boolean goAhead = true;
            		
        			while(goAhead) {
        				String msg2 = currentMsg.toString();
        				int index = msg2.indexOf("\n");
            			if (index >= 0) {
            				queue.put(msg2.substring(0, index));
            				currentMsg = new StringBuffer("");
            				if (index + 1 < msg2.length()) {
            					currentMsg.append(msg2.substring(index + 1)); 
            				}
            			} else {
            				goAhead = false;
            			}
        		    }
        			
            } catch (Exception ex) {
            	ex.printStackTrace();
                System.out.println("Error in receiving string from COM-port: " + ex);
            }
        }
	}
}

