#include <Metro.h>
#include "SerialReceiver.h"

const int MaxArgs = 4;
const int NumTrigger = 2;
const int TriggerPin[NumTrigger] = {2,3};

const long CmdSetTriggerLow = 0;
const long CmdSetTriggerHigh = 1;
const long CmdSetTriggerTimed = 2;

SerialReceiver receiver = SerialReceiver();
Metro metro = Metro();

struct CmdMessage 
{
    int num_args = 0;
    long args[MaxArgs];
};


void setup()
{
    Serial.begin(115200);
    init_trigger_pin();
}

void loop()
{
    CmdMessage cmd_msg;

    while (Serial.available() > 0) {
        receiver.process(Serial.read());
        if (receiver.messageReady()) {
            cmd_msg = get_command_args(cmd_msg);
        }
    }

    handle_command(cmd_msg);
}


CmdMessage get_command_args(CmdMessage &cmd_msg)
{
    cmd_msg.num_args = receiver.numberOfItems();
    for (int i=0; i<cmd_msg.num_args; i++)
    {
        cmd_msg.args[i] = receiver.readLong(i);
    }
    receiver.reset();
    return cmd_msg;
}


void handle_command(CmdMessage &cmd_msg)
{
    static bool metro_on = false;
    if (cmd_msg.num_args > 0) 
    {
        // DEBUG
        // ------------------------------------------
        //for (int i=0; i<cmd_msg.num_args; i++)
        //{
        //    Serial.print("args[");
        //    Serial.print(i);
        //    Serial.print("] = ");
        //    Serial.println(cmd_msg.args[i]);
        //}
        //Serial.println();
        // ------------------------------------------


        long cmd_id = cmd_msg.args[0];

        switch (cmd_id)
        {
            case CmdSetTriggerLow:
                set_trigger_low();
                break;

            case CmdSetTriggerHigh:
                set_trigger_high();
                break;

            case CmdSetTriggerTimed:
                if (cmd_msg.num_args > 1)
                {
                    long alarm_dt = abs(cmd_msg.args[1]);
                    set_trigger_high();
                    metro.interval(alarm_dt);
                    metro.reset();
                    metro_on = true;
                }
                break;

            default:
                break;

        }
    }

    if (metro_on)
    {
        if (metro.check())
        {
            set_trigger_low();
            metro_on = false;
        }
    }
}


void init_trigger_pin()
{
    for (int i=0; i<NumTrigger; i++)
    {
        pinMode(TriggerPin[i],OUTPUT);
    }
    set_trigger_low();
}


void set_trigger_high()
{
    //Serial.println("Trigger HIGH");
    for (int i=0; i<NumTrigger; i++)
    {
        digitalWrite(TriggerPin[i],HIGH);
    }
}


void set_trigger_low()
{
    //Serial.println("Trigger LOW");
    for (int i=0; i<NumTrigger; i++)
    {
        digitalWrite(TriggerPin[i],LOW);
    }
}


