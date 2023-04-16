# Untitled - By: hello - Пн мар 29 2021

import sensor, image, utime, pyb

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QCIF)
sensor.skip_frames(time = 100)
serial = pyb.UART(3, 9600, timeout = 100, timeout_char = 100)
serial.init(9600, bits=8, parity=None, stop=1, timeout_char=100)
tag_families = 0
tag_families |= image.TAG36H11
tag_families |= image.TAG16H5

while(True):
    img=sensor.snapshot()
    tags = img.find_apriltags(families=image.TAG36H11)
    if len(tags) == 1:
        tag = tags[0]
        if tag.id() == 6:
            k = 1
        if tag.id() == 7:
            k = 2
        if tag.id() == 0:
            while (True):
                img=sensor.snapshot()
                tags = img.find_apriltags(families=image.TAG36H11)
                if len(tags) == 1:                                   # if the image has at least one apriltag
                    t = tags[0]
                    img.draw_rectangle(t.x(),t.y(),t.w(),t.h())
                    #cx = round(-50 + t.cx()*70/176)
                    x_center = 176//2
                    if t.cx() >= x_center - 20 and t.cx() <= x_center + 20:
                        if_rotation = 0
                    elif t.cx() < x_center - 20:
                        if_rotation = -1
                    elif t.cx() > x_center + 20:
                        if_rotation = 1
                    #serial.writechar(t.id())
                    print(int(if_rotation))
                    serial.writechar(int(if_rotation))
                elif len(tags) == 0:
                    print(2)
                    serial.writechar(2)
        serial.writechar(tag.id())
        print(tag.id())
        img.draw_rectangle(tag.x(),tag.y(),tag.w(),tag.h())
