AVRDUDE = /Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avrdude
AVRDUDEFLAGS = -b 19200 -C /Applications/Arduino.app/Contents/Java/hardware/tools/avr/etc/avrdude.conf -c avrispmkII -p m328p -v
BOOTLOADER = optiboot_atmega328.hex

all: read

fuses:
	${AVRDUDE} ${AVRDUDEFLAGS} -e -U efuse:w:0x05:m -U hfuse:w:0xD6:m -U lfuse:w:0xFF:m

install: fuses
	${AVRDUDE} ${AVRDUDEFLAGS} -V -U flash:w:${BOOTLOADER}
	${AVRDUDE} ${AVRDUDEFLAGS} -U lock:w:0x0F:m

read:
	${AVRDUDE} ${AVRDUDEFLAGS}
