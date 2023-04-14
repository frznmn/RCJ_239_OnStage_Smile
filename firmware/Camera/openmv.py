import sensor, image, tf, time
from pyb import UART,LED

uart = UART(3, 9600)
led=LED(1)
led.off()

sensor.reset()
sensor.set_pixformat(sensor.GRAYSCALE)
sensor.set_framesize(sensor.B128X128)

while True:
    snap=sensor.snapshot().rotation_corr(x_rotation=180,y_rotation=180)
    tags=snap.find_apriltags(family=image.TAG16H5)
    if len(tags)!=0:
        print('Tag has been found')
        t = tags[0]
        #cx = round(-50 + t.cx()*70/176)
        x_center = 128//2
        if t.cx() >= x_center - 20 and t.cx() <= x_center + 20:
            if_rotation = 0
        elif t.cx() < x_center - 20:
            if_rotation = -1
        elif t.cx() > x_center + 20:
            if_rotation = 1
        led.on()
        time.sleep(1)
        for i in range(5):
            led.off()
            time.sleep(0.2)
            led.on()
            time.sleep(0.2)
        led.off()
        led=LED(2)
        led.on()
        img=sensor.snapshot().rotation_corr(x_rotation=180,y_rotation=180).copy(roi=(t.x()-20,t.y()-20,t.w()+40,t.w()+40),x_size=64)
        classification=tf.classify('blackmodel.tflite',img)[0][4]
        res=classification.index(max(classification))
        print('Resut:',res)
        uart.writechar(int(res))
        uart.writechar(int(if_rotation))
    led.off()


