from machine import Pin
from time import sleep

led1 = Pin(12, Pin.OUT)

while True: 
    led1.on()
    sleep(10)
    led1.off()
    sleep(10)
    

