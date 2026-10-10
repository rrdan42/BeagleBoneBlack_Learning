# Run on BBB terminal

First, query the current mode of pin 9.12:
```
sudo config-pin -q P9.12
```

Then, set the mode to gpio:
```
sudo config-pin P9.12 gpio
```
