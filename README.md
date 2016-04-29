# LoRa long range measurements

## Radio
The SX1272/73 transceivers feature the LoRa® long range modem that provides ultra-long range spread spectrum communication and high interference immunity whilst minimising current consumption.

Using Semtech’s patented LoRa modulation technique SX1272/73 can achieve a sensitivity of over -137 dBm using a low cost crystal and bill of materials. The high sensitivity combined with the integrated +20 dBm power amplifier yields industry leading link budget making it optimal for any application requiring range or robustness. LoRa also provides significant advantages in both blocking and selectivity over conventional modulation techniques, solving the traditional design compromise between range, interference immunity and energy consumption.

## Test
One radio sending messages every second with a ID number generated froma  random number, Sequence and Lat&Long from GPS
Other radio Receive message and transmit an ACK. This radio is connected to a Rpi that logs data and send it to Ubidots.
