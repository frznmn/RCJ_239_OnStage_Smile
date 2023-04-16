# Untitled - By: hello - Пн мар 29 2021

import sensor, image, pyb, utime                        # we add libraries

from pyb import UART

sensor.reset()                                         # we reset image that we see
sensor.set_pixformat(sensor.RGB565)                    # we set the screen resolution
sensor.set_framesize(sensor.QCIF)                      # we set the frame size
sensor.skip_frames(time = 100)                         # we set speed of skipping frames
serial = pyb.UART(3, 9600, timeout = 100, timeout_char = 100)
serial.init(9600, bits = 8, parity = None, stop = 1, timeout_char = 100)

ledGreen = pyb.LED(2)
ledBlue = pyb.LED(3)
timeLed = 0
if_rotation = 0

ledGreen.on()
utime.sleep_ms(1000)
ledGreen.off()
while(True):                                           # endless cycle
    img=sensor.snapshot()                              # it is variables, which shows image of camera
    tags = img.find_apriltags(families=image.TAG36H11)
    if len(tags)==1:                                   # if the image has at least one apriltag
        t = tags[0]
        img.draw_rectangle(t.x(),t.y(),t.w(),t.h())
        #cx = round(-50 + t.cx()*70/176)
        x_center = 176//2
        if t.cx() >= x_center - 10 and t.cx() <= x_center + 10:
            if_rotation = 0
        elif t.cx() < x_center - 10:
            if_rotation = -1
        elif t.cx() > x_center + 10:
            if_rotation = 1
        else:
            if_rotation = 2
        #serial.writechar(t.id())
        serial.writechar(int(if_rotation))
        print(if_rotation)
