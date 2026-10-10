# Interfacing with LM35 Temperature Sensor

Connect the output of LM35 to pin 39 of the BBB (In built ADC)

Check if the device is visible (on-board ADC?)
```
ls /sys/bus/iio/devices
```

Get the current value at the ADC
```
cat /sys/bus/iio/devices/iio\:device0/in_voltage0_raw
```

Or use watch to monitor the value:
```
watch -n 0.5 cat /sys/bus/iio/devices/iio\:device0/in_voltage0_raw
```


To convert to Celsius:

Value * 1800 / 4096
