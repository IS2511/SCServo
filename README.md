# SCServo
SCS/SMS servo library for Arduino

**THIS IS NOT WRITTEN BY ME.**  
AUTHOR: **Le Tan Hung (谭雄乐)**.

This is the most recent version I could find, dates ~~2017-08-22~~ 2019-08-01.

I modified it a bit:
- Define `SCS_USE_MICROS` before including and the library will use `micros()` instead of `millis()`. This may fix data reading from servos on ARM controllers (like Arduino Due)

Examples explain everything you need to know to use it.
Maybe I'll translate everything later... If I can spare some time.

Good luck!
