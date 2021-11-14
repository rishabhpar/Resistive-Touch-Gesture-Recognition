###########
# Author: Malav Shah
# ------------------
# Read in x y z acceleration data from serial port
# Save data into a csv file
############

import serial
import numpy as np

def captureSerialData():
    #sample_rate = 10 #hertz
    #time = 4 #seconds
    #sampleSize = sample_rate * time
    sampleSize = 32
    acc = np.zeros((sampleSize, 2), dtype = float)

    port = '/dev/tty.usbserial-0001'
    print(acc)
    arduino = serial.Serial(port,9600)
    data = arduino.readline()
    arduino.flushInput()
    print('Starting capture')

    try:
        print('inside try')
        for i in range(sampleSize):
            data = arduino.readline()
            print(i)
            Data = data[:-1].split(b',')
            acc[i,0] = int(float(Data[0]))
            acc[i,1] = int(float(Data[1]))
        return acc
        arduino.close()
    except Exception as e:
        print(e)
        print("exception")
        return acc

if __name__ == '__main__':
    accData = captureSerialData()
    #plt.plot(accData)
    np.savetxt('TRIANGLE_TRIAL1.csv', accData, delimiter=',', fmt='%d')