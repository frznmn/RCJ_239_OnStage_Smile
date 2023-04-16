# Untitled - By: hello - Пн мар 29 2021

import sensor, image, utime, pyb

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QCIF)
sensor.skip_frames(time = 100)
serial = pyb.UART(3, 9600, timeout = 100, timeout_char = 100)
serial.init(9600, bits=8, parity=None, stop=1, timeout_char=100)
tag_families = 0
tag_families |= image.TAG36H11 # comment out to disable this family (default family)

while(True):
    img=sensor.snapshot()
    tags = img.find_apriltags(families=image.TAG36H11)
    if len(tags) == 1:
        tag = tags[0]
        if tag.id() == 6:
            k = 1
        if tag.id() == 7:
            k = 2
        serial.writechar(tag.id())
        print(tag.id())
        img.draw_rectangle(tag.x(),tag.y(),tag.w(),tag.h())
