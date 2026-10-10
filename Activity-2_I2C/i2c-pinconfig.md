# Setting the Pin Configuration for I2C

First, query the current mode of pin 9.19 and 9.20:
```
sudo config-pin -q P9.19
sudo config-pin -q P9.20
```

Note: You can list the available modes by `config-pin -l P9.19`

Then, set the mode to i2c:
```
sudo config-pin P9.19 i2c
sudo config-pin P9.20 i2c
```

Then check i2c devices in device list (/dev) 
```
ls -l /dev/i2c*
```



# Hardware Connections

We're using MPU9250. This should map to address 0x68

 | MPU9250 Pin | BBB Pin |
 |-------------|---------|
 | VCC | 3V3 |
 | GND | DGND |
 | SCL | SCL |
 | SDA | SDA |
 
You can find the pin diagram of BBB here: https://vadl.github.io/images/bbb/bbb_headers.png

Then, in the BBB terminal, run:
```
sudo i2cdetect -y -r 2
```

You should see 68 visible in the output.


```
sudo i2cget -y 2 0x68 0x75
```

Now you should be able to run programs that use i2c!
