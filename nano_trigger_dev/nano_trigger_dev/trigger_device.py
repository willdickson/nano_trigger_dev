from __future__ import print_function
import time
import serial


class TriggerDevice(serial.Serial):

    ResetSleepDt = 2.0
    Baudrate = 115200

    CmdSetTriggerLow = 0
    CmdSetTriggerHigh = 1
    CmdSetTriggerTimed = 2

    def __init__(self,port,timeout=10.0):
        param = {'baudrate': self.Baudrate, 'timeout': timeout}
        super(TriggerDevice,self).__init__(port,**param)
        time.sleep(self.ResetSleepDt)
        self.set_low();

    def set_low(self):
        self.write('[{0}]\n'.format(self.CmdSetTriggerLow))

    def set_high(self):
        self.write('[{0}]\n'.format(self.CmdSetTriggerHigh))

    def set_timed(self,dt_ms):
        self.write('[{0},{1}]\n'.format(self.CmdSetTriggerTimed,dt_ms))





