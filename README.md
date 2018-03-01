## nano_trigger_dev 

Simple Arduino Nano based trigger device + python library. 



## Installation

Requirements: python-serial 

```bash
$ python setup.py install 

```


## Example

``` python
dev = TriggerDevice('/dev/ttyUSB0')
dev.set_high()
dev.set_low()

```



