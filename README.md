# Microcontroler

## Smart Cooling Controller (ATmega328P, C)

ATmega328P(Arduino Uno 호환) 기반의 C 펌웨어 예제입니다.  
LM35 온도센서를 읽어 팬 PWM을 자동 제어하고, UART로 상태를 출력합니다.

## 핵심 기능
- `ADC0`에서 LM35 온도값 샘플링
- 온도 구간(25~45°C) 기반 선형 PWM 제어
- 버튼(`PD2`)으로 수동 최대 풍량 모드 토글
- 상태 LED(`PB5`) 표시
- UART(9600 baud) 주기 로그 출력

## 하드웨어 연결
- LM35 OUT -> `PC0 / ADC0`
- Fan Driver PWM IN -> `PB1 / OC1A`
- Button -> `PD2` to GND (내부 Pull-up 사용)
- Status LED -> `PB5`

## 빠른 시작
1. AVR 툴체인 설치 (`avr-gcc`, `make`, `avrdude`)
2. 업로드 포트 확인 후 [Makefile](c:\코쓰\Microcontroler\Makefile)의 `COM3` 수정
3. 빌드

```bash
make
```

4. 업로드

```bash
make flash
```

## 로그 예시
```text
Smart Cooling Controller Start
TEMP=31C, DUTY=76/255
TEMP=33C, DUTY=102/255
```

## 프로젝트 구조
- `src/main.c`: 메인 루프, 주기 로그 출력
- `src/app/control.c`: 제어 로직(온도->PWM, 버튼 토글)
- `src/drivers/adc.c`: ADC 드라이버
- `src/drivers/pwm.c`: PWM 드라이버
- `src/drivers/uart.c`: UART 드라이버
- `include/`: 헤더 파일
- `docs/PROJECT_OVERVIEW.md`: 설계 개요 및 확장 아이디어

## 참고
- 기본 MCU/클럭 설정은 `ATmega328P`, `16MHz` 기준입니다.
- 보드가 다르면 핀/타이머/업로더 옵션을 함께 조정해야 합니다.
