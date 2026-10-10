# Make an LED blink on BeagleBone Black

First we need to write the C code. I've written this in led_blinking.c

Then we need to transfer the C file to the BBB:
```
scp ./led_blinking.c debian@192.168.7.2:/home/debian/radhan-daksh/activity1/led_blinking.c
```

Then we need to compile and run it on the BBB (this needs to be done by ssh-ing into the BBB):
```
gcc led_blinking.c -o led.out
./led.out
```
