# Untitled - By: HP - Сб фев 5 2022

import sensor, image, time, pyb, math, utime

from pyb import UART

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQVGA)
serial = pyb.UART(3, 9600, timeout = 100, timeout_char = 100)
serial.init(9600, bits=8, parity=None, stop=1, timeout_char=100)
sensor.skip_frames(time = 2000)

fx = (2.8 / 3.984) * 160
fy = (2.8 / 2.952) * 120

cx = 80
cy = 60

while(True):
    #a = 120
    #a = a | 128
    #print(a)
    #serial.writechar(a)
    #p = 55
    #print(p)
    #serial.writechar()

    img = sensor.snapshot()
    img.lens_corr(1.4)
    tags = img.find_apriltags(families=image.TAG36H11)
    for t in tags:
        img.draw_rectangle(t.x(), t.y(), t.w(), t.h(), (255,0,0))
        x = t.x_translation()
        z = t.z_translation()
        err_z = -4.0 - z
        #print (x, err_z);
        posit = math.sqrt (x**2 + err_z**2)
        if err_z < 0:
            posit = posit * (-1)
        angle = math.atan(x/err_z)
        angle = math.degrees(angle)
        #print(angle, posit)
        angle = round(angle,2);
        posit = round(posit,2);
        print(posit, angle);
        angle = angle/1.5;
        posit = (posit*100/15)+13;
        angle = int(angle);
        posit = int(posit);
        if (angle<0):
            angle = angle * (-1);
            angle = angle | 64
        serial.writechar(angle)
        serial.writechar(posit | 128)
        utime.sleep_ms(10);
        #print (posit, angle)
