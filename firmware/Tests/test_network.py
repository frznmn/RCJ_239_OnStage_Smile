import sensor, image, tf

sensor.reset()
sensor.set_pixformat(sensor.GRAYSCALE)
sensor.set_framesize(sensor.B128X128)

while(True):
    snap=sensor.snapshot().rotation_corr(x_rotation=180,y_rotation=180).draw_rectangle(30,30,60,60)
    img=snap.copy(roi=(31,31,58,58),x_size=64)
    cl=tf.classify('blackmodel.tflite',img)[0][4]
    res=cl.index(max(cl))
    print(res)
