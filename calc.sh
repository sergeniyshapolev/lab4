sudo insmod proc_calc.ko
sudo echo "12" > /proc/calc_first
sudo echo "-" > /proc/calc_operator
sudo echo "13" > /proc/calc_second
sudo cat /proc/calc_result

sudo echo "6" > /proc/calc_first
sudo echo "+" > /proc/calc_operator
sudo echo "8" > /proc/calc_second
sudo cat /proc/calc_result

sudo echo "2" > /proc/calc_first
sudo echo "*" > /proc/calc_operator
sudo echo "9" > /proc/calc_second
sudo cat /proc/calc_result

sudo echo "10" > /proc/calc_first
sudo echo "/" > /proc/calc_operator
sudo echo "2" > /proc/calc_second
sudo cat /proc/calc_result

sudo rmmod proc_calc
