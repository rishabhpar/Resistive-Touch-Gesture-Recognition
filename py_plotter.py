###########
# Author: Malav Shah
# ------------------
# Read in x y z acceleration data from serial port
# Save data into a csv file
############

import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib import style

import serial
import numpy as np




def captureSerialData():
    sample_rate = 200 #hertz
    time = 4 #seconds
    sampleSize = sample_rate * time
    acc = np.zeros((sampleSize, 2), dtype = float)

    port = '/dev/tty.usbmodem101'
    print(acc)
    arduino = serial.Serial(port,9600)
    arduino.flushInput()
    print('Starting capture')

    try:
        print('inside try')
        for i in range(sampleSize):
            data = arduino.readline()
            #print(data)
            Data = data[:-1].split(b',')
            acc[i,0] = int(float(Data[0]))
            acc[i,1] = int(float(Data[1]))
            print(Data)
        return acc
        arduino.close()
    except Exception as e:
        print(e)
        print("exception")
        return acc

if __name__ == '__main__':
    accData = captureSerialData()
    plt.plot(accData)
    np.savetxt('point_touches.csv', accData, delimiter=',', fmt='%d')