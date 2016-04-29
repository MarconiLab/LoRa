# LoRa long range measurements

## Radio
We are using Libelium LoRa 868 / 900MHz SX1272 LoRa module for Arduino. Based on Semtech The SX1272/73 transceivers feature the LoRa® long range modem that provides ultra-long range spread spectrum communication and high interference immunity whilst minimising current consumption.

LoRa is a new, private and spread-spectrum modulation technique which allows sending data at extremely low data-rates to extremely long ranges. The low data-rate (down to few bytes per second) and LoRa modulation lead to very low receiver sensitivity (down to -134 dBm), which combined to an output power of +14 dBm means extremely large link budgets: up to 148 dB., what means more than 22km (13.6 miles) in LOS links and up to 2km (1.2miles) in NLOS links in urban environment (going through buildings).

Libelium's LoRa module works in both 868 and 900 MHz ISM bands, which makes it suitable for virtually any country. Those frequency bands are lower than the popular 2.4 GHz band, so path loss attenuation is better in LoRa. In addition, 868 and 900 MHz are bands with much fewer interference than the highly populated 2.4 GHz band. Besides, these low frequencies provide great penetration in possible materials (brick walls, trees, concrete), so these bands get less loss in the presence of obstacles than higher bands.

The great performance of LoRa in all these 3 features (good sensitivity, low path loss, good obstacle penetration) makes LoRa a disruptive technology enabling really long range links. This is specially important in urban scenarios, with very difficult transmission conditions. To sum up, LoRa can get long ranges in Smart Cities deployments, so it reduces dramatically the size of the backbone network (repeaters, gateways or concentrators).

## Test
One radio sending messages every second with a ID number generated froma  random number, Sequence and Lat&Long from GPS
Other radio Receive message and transmit an ACK. This radio is connected to a Rpi that logs data and send it to Ubidots.
