import Adafruit_GPIO.SPI as SPI
import Adafruit_MCP3008
import time

# Define SPI connection parameters
SPI_PORT = 0
SPI_DEVICE = 0

# Create MCP3008 instance using hardware SPI
mcp = Adafruit_MCP3008.MCP3008(spi=SPI.SpiDev(SPI_PORT, SPI_DEVICE))

# Continuously read from channel 0
while True:
    value1 = mcp.read_adc(0)
    print("Gas value:", value1)
    time.sleep(2)
