ifeq ($(OS),Windows_NT)
SHELL = $(ComSpec)
RMDIR = rmdir /s /q
RM = del /q
mymkdir = if not exist "$1" mkdir "$1"
else
RMDIR = rm -fr
RM = rm -f
mymkdir = mkdir -p $1
endif

PROJECT_OBJS = \
	project/lib/SmartNrfAPI/SmartNrf.cpp.o \
	project/main.cpp.o \

PLATFORM_CORE_OBJS = \
	core/wiring_pulse.S.o \
	core/hooks.c.o \
	core/WString.cpp.o \
	core/USBCore.cpp.o \
	core/new.cpp.o \
	core/HardwareSerial1.cpp.o \
	core/WInterrupts.c.o \
	core/wiring_pulse.c.o \
	core/CDC.cpp.o \
	core/Tone.cpp.o \
	core/WMath.cpp.o \
	core/wiring_shift.c.o \
	core/wiring_analog.c.o \
	core/IPAddress.cpp.o \
	core/PluggableUSB.cpp.o \
	core/abi.cpp.o \
	core/HardwareSerial0.cpp.o \
	core/HardwareSerial2.cpp.o \
	core/wiring_digital.c.o \
	core/main.cpp.o \
	core/Stream.cpp.o \
	core/Print.cpp.o \
	core/HardwareSerial.cpp.o \
	core/wiring.c.o \
	core/HardwareSerial3.cpp.o \

PLATFORM_VARIANT_OBJS = \

LIBRARIES_OBJS = \
	libraries/SPI/src/SPI.cpp.o \
	libraries/Wire/src/utility/twi.c.o \
	libraries/Wire/src/Wire.cpp.o \
	libraries/HID/src/HID.cpp.o \
	libraries/SoftwareSerial/src/SoftwareSerial.cpp.o \
	libraries/RF24/1.3.0/RF24.cpp.o \

TARGETS = \
	SmartNrf.hex \

all: $(TARGETS)

SmartNrf.hex: SmartNrf.elf
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-objcopy" -O ihex -R .eeprom  "./SmartNrf.elf" "./SmartNrf.hex"

SmartNrf.elf: $(PROJECT_OBJS) $(LIBRARIES_OBJS) core.a
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-gcc" -w -Os -g -flto -fuse-linker-plugin -Wl,--gc-sections -mmcu=atmega328p  -o "./SmartNrf.elf" $(PROJECT_OBJS) $(LIBRARIES_OBJS) "./core.a" "-L." -lm

core.a:	$(PLATFORM_CORE_OBJS) $(PLATFORM_VARIANT_OBJS)

clean:
	-$(RMDIR) project core variant libraries
	-$(RM) *.hex *.eep *.bin *.elf *.a *.ar *.d

size:
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-size" -A "./SmartNrf.elf"

project/lib/SmartNrfAPI/SmartNrf.cpp.o: ../../lib/SmartNrfAPI/SmartNrf.cpp project/lib/SmartNrfAPI/SmartNrf.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR   -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/variants/eightanaloginputs" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SPI/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/EEPROM/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/Wire/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/HID/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SoftwareSerial/src" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0/utility" "$<" -o "$@"

project/lib/SmartNrfAPI/SmartNrf.cpp.d: ;

-include project/lib/SmartNrfAPI/SmartNrf.cpp.d 

project/main.cpp.o: ../../main.cpp project/main.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR   -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/variants/eightanaloginputs" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SPI/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/EEPROM/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/Wire/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/HID/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SoftwareSerial/src" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0/utility" "$<" -o "$@"

project/main.cpp.d: ;

-include project/main.cpp.d 


core/wiring_pulse.S.o: /home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino/wiring_pulse.S
	@$(call mymkdir,$(dir $@))
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-gcc" -c -g -x assembler-with-cpp -flto -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR   -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/variants/eightanaloginputs" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SPI/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/EEPROM/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/Wire/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/HID/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SoftwareSerial/src" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0/utility" "$<" -o "$@"
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"

core/hooks.c.o: /home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino/hooks.c core/hooks.c.d
	@$(call mymkdir,$(dir $@))
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-gcc" -c -g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -MMD -flto -fno-fat-lto-objects -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR   -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/variants/eightanaloginputs" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SPI/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/EEPROM/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/Wire/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/HID/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SoftwareSerial/src" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0/utility" "$<" -o "$@"
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"
	
core/hooks.c.d: ;

-include core/hooks.c.d

core/WString.cpp.o: /home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino/WString.cpp core/WString.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR   -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/variants/eightanaloginputs" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SPI/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/EEPROM/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/Wire/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/HID/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SoftwareSerial/src" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0/utility" "$<" -o "$@"
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"

core/WString.cpp.d: ;

-include core/WString.cpp.d

core/USBCore.cpp.o: /home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino/USBCore.cpp core/USBCore.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR   -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/variants/eightanaloginputs" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SPI/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/EEPROM/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/Wire/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/HID/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SoftwareSerial/src" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0/utility" "$<" -o "$@"
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"

core/USBCore.cpp.d: ;

-include core/USBCore.cpp.d

core/new.cpp.o: /home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino/new.cpp core/new.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR   -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/variants/eightanaloginputs" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SPI/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/EEPROM/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/Wire/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/HID/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SoftwareSerial/src" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0/utility" "$<" -o "$@"
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"

core/new.cpp.d: ;

-include core/new.cpp.d

core/HardwareSerial1.cpp.o: /home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino/HardwareSerial1.cpp core/HardwareSerial1.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR   -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/variants/eightanaloginputs" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SPI/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/EEPROM/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/Wire/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/HID/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SoftwareSerial/src" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0/utility" "$<" -o "$@"
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"

core/HardwareSerial1.cpp.d: ;

-include core/HardwareSerial1.cpp.d

core/WInterrupts.c.o: /home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino/WInterrupts.c core/WInterrupts.c.d
	@$(call mymkdir,$(dir $@))
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-gcc" -c -g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -MMD -flto -fno-fat-lto-objects -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR   -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/variants/eightanaloginputs" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SPI/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/EEPROM/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/Wire/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/HID/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SoftwareSerial/src" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0/utility" "$<" -o "$@"
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"
	
core/WInterrupts.c.d: ;

-include core/WInterrupts.c.d

core/wiring_pulse.c.o: /home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino/wiring_pulse.c core/wiring_pulse.c.d
	@$(call mymkdir,$(dir $@))
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-gcc" -c -g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -MMD -flto -fno-fat-lto-objects -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR   -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/variants/eightanaloginputs" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SPI/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/EEPROM/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/Wire/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/HID/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SoftwareSerial/src" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0/utility" "$<" -o "$@"
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"
	
core/wiring_pulse.c.d: ;

-include core/wiring_pulse.c.d

core/CDC.cpp.o: /home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino/CDC.cpp core/CDC.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR   -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/variants/eightanaloginputs" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SPI/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/EEPROM/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/Wire/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/HID/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SoftwareSerial/src" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0/utility" "$<" -o "$@"
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"

core/CDC.cpp.d: ;

-include core/CDC.cpp.d

core/Tone.cpp.o: /home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino/Tone.cpp core/Tone.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR   -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/variants/eightanaloginputs" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SPI/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/EEPROM/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/Wire/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/HID/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SoftwareSerial/src" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0/utility" "$<" -o "$@"
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"

core/Tone.cpp.d: ;

-include core/Tone.cpp.d

core/WMath.cpp.o: /home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino/WMath.cpp core/WMath.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR   -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/variants/eightanaloginputs" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SPI/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/EEPROM/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/Wire/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/HID/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SoftwareSerial/src" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0/utility" "$<" -o "$@"
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"

core/WMath.cpp.d: ;

-include core/WMath.cpp.d

core/wiring_shift.c.o: /home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino/wiring_shift.c core/wiring_shift.c.d
	@$(call mymkdir,$(dir $@))
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-gcc" -c -g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -MMD -flto -fno-fat-lto-objects -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR   -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/variants/eightanaloginputs" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SPI/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/EEPROM/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/Wire/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/HID/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SoftwareSerial/src" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0/utility" "$<" -o "$@"
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"
	
core/wiring_shift.c.d: ;

-include core/wiring_shift.c.d

core/wiring_analog.c.o: /home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino/wiring_analog.c core/wiring_analog.c.d
	@$(call mymkdir,$(dir $@))
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-gcc" -c -g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -MMD -flto -fno-fat-lto-objects -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR   -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/variants/eightanaloginputs" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SPI/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/EEPROM/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/Wire/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/HID/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SoftwareSerial/src" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0/utility" "$<" -o "$@"
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"
	
core/wiring_analog.c.d: ;

-include core/wiring_analog.c.d

core/IPAddress.cpp.o: /home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino/IPAddress.cpp core/IPAddress.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR   -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/variants/eightanaloginputs" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SPI/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/EEPROM/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/Wire/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/HID/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SoftwareSerial/src" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0/utility" "$<" -o "$@"
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"

core/IPAddress.cpp.d: ;

-include core/IPAddress.cpp.d

core/PluggableUSB.cpp.o: /home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino/PluggableUSB.cpp core/PluggableUSB.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR   -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/variants/eightanaloginputs" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SPI/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/EEPROM/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/Wire/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/HID/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SoftwareSerial/src" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0/utility" "$<" -o "$@"
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"

core/PluggableUSB.cpp.d: ;

-include core/PluggableUSB.cpp.d

core/abi.cpp.o: /home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino/abi.cpp core/abi.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR   -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/variants/eightanaloginputs" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SPI/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/EEPROM/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/Wire/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/HID/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SoftwareSerial/src" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0/utility" "$<" -o "$@"
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"

core/abi.cpp.d: ;

-include core/abi.cpp.d

core/HardwareSerial0.cpp.o: /home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino/HardwareSerial0.cpp core/HardwareSerial0.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR   -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/variants/eightanaloginputs" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SPI/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/EEPROM/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/Wire/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/HID/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SoftwareSerial/src" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0/utility" "$<" -o "$@"
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"

core/HardwareSerial0.cpp.d: ;

-include core/HardwareSerial0.cpp.d

core/HardwareSerial2.cpp.o: /home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino/HardwareSerial2.cpp core/HardwareSerial2.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR   -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/variants/eightanaloginputs" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SPI/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/EEPROM/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/Wire/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/HID/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SoftwareSerial/src" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0/utility" "$<" -o "$@"
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"

core/HardwareSerial2.cpp.d: ;

-include core/HardwareSerial2.cpp.d

core/wiring_digital.c.o: /home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino/wiring_digital.c core/wiring_digital.c.d
	@$(call mymkdir,$(dir $@))
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-gcc" -c -g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -MMD -flto -fno-fat-lto-objects -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR   -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/variants/eightanaloginputs" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SPI/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/EEPROM/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/Wire/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/HID/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SoftwareSerial/src" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0/utility" "$<" -o "$@"
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"
	
core/wiring_digital.c.d: ;

-include core/wiring_digital.c.d

core/main.cpp.o: /home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino/main.cpp core/main.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR   -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/variants/eightanaloginputs" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SPI/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/EEPROM/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/Wire/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/HID/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SoftwareSerial/src" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0/utility" "$<" -o "$@"
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"

core/main.cpp.d: ;

-include core/main.cpp.d

core/Stream.cpp.o: /home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino/Stream.cpp core/Stream.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR   -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/variants/eightanaloginputs" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SPI/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/EEPROM/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/Wire/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/HID/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SoftwareSerial/src" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0/utility" "$<" -o "$@"
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"

core/Stream.cpp.d: ;

-include core/Stream.cpp.d

core/Print.cpp.o: /home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino/Print.cpp core/Print.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR   -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/variants/eightanaloginputs" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SPI/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/EEPROM/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/Wire/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/HID/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SoftwareSerial/src" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0/utility" "$<" -o "$@"
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"

core/Print.cpp.d: ;

-include core/Print.cpp.d

core/HardwareSerial.cpp.o: /home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino/HardwareSerial.cpp core/HardwareSerial.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR   -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/variants/eightanaloginputs" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SPI/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/EEPROM/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/Wire/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/HID/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SoftwareSerial/src" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0/utility" "$<" -o "$@"
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"

core/HardwareSerial.cpp.d: ;

-include core/HardwareSerial.cpp.d

core/wiring.c.o: /home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino/wiring.c core/wiring.c.d
	@$(call mymkdir,$(dir $@))
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-gcc" -c -g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -MMD -flto -fno-fat-lto-objects -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR   -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/variants/eightanaloginputs" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SPI/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/EEPROM/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/Wire/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/HID/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SoftwareSerial/src" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0/utility" "$<" -o "$@"
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"
	
core/wiring.c.d: ;

-include core/wiring.c.d

core/HardwareSerial3.cpp.o: /home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino/HardwareSerial3.cpp core/HardwareSerial3.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR   -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/variants/eightanaloginputs" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SPI/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/EEPROM/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/Wire/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/HID/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SoftwareSerial/src" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0/utility" "$<" -o "$@"
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"

core/HardwareSerial3.cpp.d: ;

-include core/HardwareSerial3.cpp.d



libraries/SPI/src/SPI.cpp.o: /home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SPI/src/SPI.cpp libraries/SPI/src/SPI.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR   -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/variants/eightanaloginputs" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SPI/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/EEPROM/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/Wire/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/HID/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SoftwareSerial/src" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0/utility" "$<" -o "$@"

libraries/SPI/src/SPI.cpp.d: ;

-include libraries/SPI/src/SPI.cpp.d

libraries/Wire/src/utility/twi.c.o: /home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/Wire/src/utility/twi.c libraries/Wire/src/utility/twi.c.d
	@$(call mymkdir,$(dir $@))
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-gcc" -c -g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -MMD -flto -fno-fat-lto-objects -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR   -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/variants/eightanaloginputs" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SPI/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/EEPROM/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/Wire/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/HID/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SoftwareSerial/src" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0/utility" "$<" -o "$@"

libraries/Wire/src/utility/twi.c.d: ;

-include libraries/Wire/src/utility/twi.c.d

libraries/Wire/src/Wire.cpp.o: /home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/Wire/src/Wire.cpp libraries/Wire/src/Wire.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR   -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/variants/eightanaloginputs" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SPI/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/EEPROM/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/Wire/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/HID/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SoftwareSerial/src" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0/utility" "$<" -o "$@"

libraries/Wire/src/Wire.cpp.d: ;

-include libraries/Wire/src/Wire.cpp.d

libraries/HID/src/HID.cpp.o: /home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/HID/src/HID.cpp libraries/HID/src/HID.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR   -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/variants/eightanaloginputs" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SPI/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/EEPROM/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/Wire/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/HID/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SoftwareSerial/src" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0/utility" "$<" -o "$@"

libraries/HID/src/HID.cpp.d: ;

-include libraries/HID/src/HID.cpp.d

libraries/SoftwareSerial/src/SoftwareSerial.cpp.o: /home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SoftwareSerial/src/SoftwareSerial.cpp libraries/SoftwareSerial/src/SoftwareSerial.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR   -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/variants/eightanaloginputs" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SPI/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/EEPROM/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/Wire/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/HID/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SoftwareSerial/src" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0/utility" "$<" -o "$@"

libraries/SoftwareSerial/src/SoftwareSerial.cpp.d: ;

-include libraries/SoftwareSerial/src/SoftwareSerial.cpp.d

libraries/RF24/1.3.0/RF24.cpp.o: /home/mario/.arduinocdt/libraries/RF24/1.3.0/RF24.cpp libraries/RF24/1.3.0/RF24.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/mario/.arduinocdt/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR   -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/cores/arduino" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/variants/eightanaloginputs" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SPI/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/EEPROM/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/Wire/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/HID/src" -I"/home/mario/.arduinocdt/packages/arduino/hardware/avr/1.6.20/libraries/SoftwareSerial/src" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0" -I"/home/mario/.arduinocdt/libraries/RF24/1.3.0/utility" "$<" -o "$@"

libraries/RF24/1.3.0/RF24.cpp.d: ;

-include libraries/RF24/1.3.0/RF24.cpp.d

