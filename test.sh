make >> log.txt
sudo insmod ./timer_sysfs.ko

echo 123 >> /sys/timer_dir/timer_period
cat /sys/timer_dir/timer_period

sudo rmmod timer_sysfs
make clean >> log.txt
