import smbus
import time
from time import sleep 
from gpiozero import DistanceSensor, PWMLED
from signal import signal, SIGTERM, SIGHUP, pause

sensor = DistanceSensor(echo = 17, trigger = 4)

channel = 1
address = 0x10

bus = smbus.SMBus(channel)

prev_distance = 0
distance = sensor.value * 100
diff = 0

while True:
    prev_distance = distance
    distance = sensor.value * 100
        
    diff = distance - prev_distance
    
    diff = int(diff)
    
    print("previous distance: ")
    print(prev_distance)
    print("distance:")
    print(distance)
        
    print("diff: ")
    print(diff)
    
    if (diff > 0):
        bus.write_byte(address, diff)
    sleep(300)

