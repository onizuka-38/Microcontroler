# PROJECT OVERVIEW

## 1. Goal
Build a deployable C firmware project for an 8-bit MCU with practical embedded patterns:
- HAL-like driver split
- deterministic super-loop
- low-overhead telemetry
- clear extension points

## 2. Control Policy
1. Read ADC value from LM35 sensor.
2. Convert ADC to temperature in degree Celsius.
3. Map temperature to PWM duty:
- <= 25C -> 0%
- >= 45C -> 100%
- between -> linear interpolation
4. If user button is toggled, force 100% duty.

## 3. Timing
Main loop period is 500 ms:
- update control
- print one UART log line

## 4. Next Extensions
- Add moving-average filter for ADC noise.
- Add over-temperature alarm buzzer.
- Add EEPROM for configurable temperature thresholds.
- Add watchdog and brown-out robustness settings.
