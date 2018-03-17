import time
from nano_trigger_dev import TriggerDevice

dev = TriggerDevice('/dev/ttyUSB0')
state = False

while True:

    if state:
        dev.set_low()
        state = False
        print('set_high')
    else:
        dev.set_high()
        state = True
        print('set_low')

    time.sleep(0.1)

