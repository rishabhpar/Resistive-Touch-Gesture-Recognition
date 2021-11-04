###########
# Author: Malav Shah
# ------------------
# Just used to plot things
############

import numpy as np
import matplotlib.pyplot as plt

data_slide_down = np.genfromtxt('slide_down.csv', delimiter=',')
data_slide_cross = np.genfromtxt('cross_screen_slide.csv', delimiter=',')
data_circle = np.genfromtxt('circle.csv', delimiter = ',')
data_point_touches = np.genfromtxt('point_touches.csv', delimiter = ',')
data_point_touches = np.genfromtxt('Check_Touch_TRIAL1.csv', delimiter = ',')
data_point_touches = np.genfromtxt('U.csv', delimiter = ',')
# data_point_touches = np.genfromtxt('Circle_Touch_TRIAL1.csv', delimiter = ',')

x, y = data_point_touches.T
plt.scatter(x,y)
plt.gca().invert_xaxis()
plt.show()
# plt.plot(data_point_touches)
# #plt.plot(data_slide_cross)
# #plt.plot(data_slide_down)
# plt.show()