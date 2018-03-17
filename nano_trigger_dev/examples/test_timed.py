import time
from nano_trigger_dev import TriggerDevice

dev = TriggerDevice('/dev/ttyUSB0')
dev.set_timed(2000)


