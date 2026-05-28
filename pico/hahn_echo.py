# main.py -- Raspberry Pi Pico (MicroPython, rp2 PIO)
# π/2 = 1 µs HIGH, τ = 20 µs LOW, π = 2 µs HIGH, optional gap = 10 µs LOW
from machine import Pin
import rp2
import time

PIN = 15            # change to the GP pin you are probing (4 or 15)

@rp2.asm_pio(set_init=rp2.PIO.OUT_LOW)   # use 'set(pins, ...)' to drive outputs
def hahn_echo():
    wrap_target()
    set(pins, 1)         # 1 µs HIGH (π/2)
    set(pins, 0) [19]    # 20 µs LOW  (1 + 19 = 20 cycles)
    set(pins, 1)         # π pulse - first µs
    set(pins, 1)         # π pulse - second µs (total 2 µs)
    set(pins, 0) [9]     # gap 10 µs LOW  (1 + 9 = 10 cycles)
    wrap()

# ensure pin is output and start SM
pin = Pin(PIN, Pin.OUT)
pin.value(0)

# map the PIO "set(pins,..)" to physical PIN
sm = rp2.StateMachine(0, hahn_echo, freq=1_000_000, set_base=Pin(PIN))
sm.active(1)

try:
    while True:
        time.sleep(1)
except KeyboardInterrupt:
    sm.active(0)
    pin.value(0)
