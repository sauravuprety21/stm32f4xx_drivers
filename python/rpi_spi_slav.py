'''
@Overview 			Complements "Src/stm_rpi_spi_comms.c". Recieve "Hello World" over SPI
                    in slave mode, and print to command line.

@Configuration 	 	
'''
import spidev
import time


bus = 0

device = 1

spi = spidev.SpiDev()

spi.open(bus, device)

spi.max_speed_hz = 12000000
spi.mode= 0b00

try:
    while True:
        msg = spi.readbytes(1)

finally:
    spi.close()

