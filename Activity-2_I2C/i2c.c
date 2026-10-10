#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>

#define I2C_BUS "/dev/i2c-2"
#define MPU_ADDR 0x68

/* Read registers using a combined I2C transaction */
int read_regs(int fd, uint8_t reg, uint8_t *data, uint16_t len)
{
struct i2c_msg msgs[2] = {
{
.addr = MPU_ADDR,
.flags = 0,
.len = 1,
.buf = &reg
},
{
.addr = MPU_ADDR,
.flags = I2C_M_RD,
.len = len,
.buf = data
}
};

struct i2c_rdwr_ioctl_data req = {
.msgs = msgs,
.nmsgs = 2
};

return ioctl(fd, I2C_RDWR, &req) < 0 ? -1 : 0;
}

static int16_t to_int16(uint8_t msb, uint8_t lsb)
{
return (int16_t)(((uint16_t)msb << 8) | lsb);
}

int main(void)
{
int fd = open(I2C_BUS, O_RDWR);
uint8_t identity, wake_data[2] = {0x6B, 0x00};

if (fd < 0) {
perror("Opening I2C bus failed");
return 1;
}

if (ioctl(fd, I2C_SLAVE, MPU_ADDR) < 0) {
perror("Selecting I2C address failed");
close(fd);
return 1;
}

if (read_regs(fd, 0x75, &identity, 1) < 0) {
perror("Reading WHO_AM_I failed");
close(fd);
return 1;
}

printf("WHO_AM_I = 0x%02X\n", identity);

if (identity != 0x68 && identity != 0x70) {
printf("Warning: unexpected identity; continuing diagnostic test.\n");
} else if (identity == 0x70) {
printf("Warning: 0x70 is not the standard MPU6050 identity.\n");
}

/* Clear SLEEP bit in power-management register */
if (write(fd, wake_data, 2) != 2) {
perror("Waking sensor failed");
close(fd);
return 1;
}

printf("\nLive readings: raw sensor counts\n");
printf("Press Ctrl+C to stop.\n\n");

while (1) {
uint8_t d[14];

if (read_regs(fd, 0x3B, d, sizeof(d)) < 0) {
perror("Reading sensor data failed");
sleep(1);
continue;
}

int16_t ax = to_int16(d[0], d[1]);
int16_t ay = to_int16(d[2], d[3]);
int16_t az = to_int16(d[4], d[5]);
int16_t tr = to_int16(d[6], d[7]);
int16_t gx = to_int16(d[8], d[9]);
int16_t gy = to_int16(d[10], d[11]);
int16_t gz = to_int16(d[12], d[13]);

/* Default MPU6050 scales: +/-2g and +/-250 degrees/sec */
printf("A[g]: X=%7.3f Y=%7.3f Z=%7.3f | "
"G[deg/s]: X=%7.2f Y=%7.2f Z=%7.2f | "
"Temp=%6.2f C\n",
ax / 16384.0, ay / 16384.0, az / 16384.0,
gx / 131.0, gy / 131.0, gz / 131.0,
tr / 340.0 + 36.53);

fflush(stdout);
usleep(200000);
}

close(fd);
return 0;
}
