/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package embeddedapplication1;

import com.oracle.deviceaccess.PeripheralEventListener;
import com.oracle.deviceaccess.PeripheralManager;
import com.oracle.deviceaccess.PeripheralNotAvailableException;
import com.oracle.deviceaccess.PeripheralNotFoundException;
import com.oracle.deviceaccess.PeripheralTypeNotSupportedException;
import com.oracle.deviceaccess.gpio.GPIOPin;
import com.oracle.deviceaccess.gpio.GPIOPort;
import com.oracle.deviceaccess.gpio.PinEvent;
import com.oracle.deviceaccess.gpio.PinListener;
import com.oracle.deviceaccess.i2cbus.I2CDevice;
import java.io.IOException;
import java.util.Date;
import java.util.Timer;
import java.util.TimerTask;
import javax.microedition.midlet.*;

/**
 * @author vadim
 */
public class IMlet extends MIDlet {

    public void startApp() {
        task1();
        task2();
        task3();
    }
    
    public void pauseApp() {
    }
    
    public void destroyApp(boolean unconditional) {
    }
    
    /*
     * Task 1.
     * The state of the output pin "GPIO10" should be changed every 5 seconds. 
     */
    private void task1() {
        try {
            final GPIOPin pin = (GPIOPin)PeripheralManager.open("GPIO10", GPIOPin.class, null);
            Timer cron = new Timer();
            cron.schedule(new TimerTask() {

                public void run() {
                    try {
                        pin.setValue(!pin.getValue());
                    } catch (PeripheralNotAvailableException ex) {
                        ex.printStackTrace();
                    } catch (IOException ex) {
                        ex.printStackTrace();
                    }
                }
            }, 0, 5000);
            
        } catch (PeripheralNotAvailableException ex) {
            ex.printStackTrace();
        } catch (PeripheralNotFoundException ex) {
            ex.printStackTrace();
        } catch (PeripheralTypeNotSupportedException ex) {
            ex.printStackTrace();
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }
    
    /*
     * Task2.
     * For input pin "GPIO0":
each "low"->"high" state changing should change the state of the output pin "GPIO11".
(Changing the output pin state means changing it’s value from "high" to "low" or backward.)

For input pin "GPIO1":
the first "low"->"high" state changing should terminate the application.

     */
    private void task2() {
        try {
            final GPIOPin pin0 = (GPIOPin)PeripheralManager.open("GPIO0", GPIOPin.class, null);
            final GPIOPin pin11 = (GPIOPin)PeripheralManager.open("GPIO11", GPIOPin.class, null);
            final GPIOPin pin1 = (GPIOPin)PeripheralManager.open("GPIO1", GPIOPin.class, null);
            pin0.setInputListener(new PinListener(){

                public void valueChanged(PinEvent event) {
                    if (event.getValue()) //low -> high
                        try {
                            pin11.setValue(!pin11.getValue());
                    } catch (PeripheralNotAvailableException ex) {
                        ex.printStackTrace();
                    } catch (IOException ex) {
                        ex.printStackTrace();
                    }
                }
                
            });
            
            pin1.setInputListener(new PinListener() {

                public void valueChanged(PinEvent event) {
                    if (event.getValue()) //low -> high
                        notifyDestroyed(); //JSR-195: System.exit() will raise exception
                }
            });
        } catch (PeripheralNotAvailableException ex) {
            ex.printStackTrace();
        } catch (PeripheralNotFoundException ex) {
            ex.printStackTrace();
        } catch (PeripheralTypeNotSupportedException ex) {
            ex.printStackTrace();
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    private void task3() {
        try {
            final I2CDevice tempSensor = (I2CDevice)PeripheralManager.open("TEMP-SENSOR", I2CDevice.class, null);
            Timer cron = new Timer();
            cron.schedule(new TimerTask() {
                
                public void run() {
                    try {
                        byte[] tempBuf = new byte[1];
                        tempSensor.read(0, 1, tempBuf, 0, 1);
                        byte temperature = tempBuf[0];
                        Date date = new Date();
                        
                        System.out.println(date + ": " + temperature);
                    } catch (PeripheralNotAvailableException ex) {
                        ex.printStackTrace();
                    } catch (IOException ex) {
                        ex.printStackTrace();
                    }
                }
            }, 0, 1000);
        } catch (PeripheralNotAvailableException ex) {
            ex.printStackTrace();
        } catch (PeripheralNotFoundException ex) {
            ex.printStackTrace();
        } catch (PeripheralTypeNotSupportedException ex) {
            ex.printStackTrace();
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }
}
