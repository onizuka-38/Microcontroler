# Microcontroler

## Final Project: Smart Cooling Controller (ATmega328P, C)

This repository now contains a complete microcontroller project written in C.

### Features
- Reads temperature from `LM35` on `ADC0`
- Controls fan speed via PWM (`OC1A/PB1`)
- Sends telemetry over UART (`9600 baud`)
- Button (`PD2`) toggles manual max-fan mode
- LED (`PB5`) indicates manual max-fan mode

### Wiring
- LM35 OUT -> `PC0/ADC0`
- Fan driver PWM input -> `PB1/OC1A`
- Button -> `PD2` to GND (internal pull-up enabled)
- Status LED -> `PB5`

### Build
```bash
make
```

### Flash (example)
```bash
make flash
```
Default upload port in `Makefile` is `COM3`; change it to your board port if needed.

### Project Structure
- `src/main.c`: main loop and telemetry
- `src/drivers/*.c`: hardware drivers (ADC/UART/PWM)
- `src/app/control.c`: application logic (temperature-to-duty mapping)
- `include/`: headers
- `docs/PROJECT_OVERVIEW.md`: design and extension guide
