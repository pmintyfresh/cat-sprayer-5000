# Cat Sprayer 5000 🐱💦

Motion-activated water spray deterrent. Catches cats scratching the door at night.

## How It Works

A PIR motion sensor detects movement and triggers a relay, which fires a 12V diaphragm pump for a short burst. 8-second cooldown between firings. Wall powered, no batteries.

## Hardware

| Part | Notes |
|------|-------|
| Arduino Nano CH340 (USB-C) | Brains |
| HC-SR501 PIR Sensor | Motion detection |
| AEDIKO 5V 1-Channel Relay Module | Switches pump power |
| Gikfun R385 12V Diaphragm Pump | Water delivery |
| TMEZON 12V 2A Wall Adapter (5.5mm) | Pump power |
| DC Barrel Jack Screw Terminal Adapter | 12V wire connection |
| Silicone Tubing 1/4" ID | Plumbing |
| 1/4" Inline Check Valve | Prevents backflow |
| Antelco Adjustable Spray Jet 90° | Nozzle — clamped with stainless worm-drive hose clamp |
| IP65 ABS Project Box 158×90×60mm | Enclosure (includes 4 M16 cable glands) |
| M3 Brass Standoffs | Mounts Nano + relay inside box |
| USB-C Wall Charger 1A+ | Arduino power — direct cable, no adapters |
| 1L Clear Container | Reservoir |

## Wiring

```
Arduino 5V    → Relay DC+  (T-junction: also connects to PIR VCC)
Arduino GND①  → PIR GND
Arduino GND②  → Relay DC−
Arduino D2    → PIR OUT
Arduino D7    → Relay IN
12V adapter + → Relay COM
Relay NO      → Pump (+)
12V adapter − → Pump (−)
USB-C charger → Arduino USB-C
```

**Relay settings:** Slide switch → **L** (low trigger) · Pump on **NO** terminal  
**PIR jumper:** **H** (retriggering mode)  
**Arduino board:** `Arduino Nano` · Processor: `ATmega328P` (NOT Old Bootloader)

## Tuning

```cpp
const int SPRAY_MS    = 150;   // burst duration in ms
const int COOLDOWN_MS = 8000;  // refire delay in ms
```

## Startup Behavior

On power-on, the sketch waits for the PIR to output a stable LOW for 10 uninterrupted seconds before arming. This prevents false bursts during the sensor's 30–60 second warmup period. Serial monitor (9600 baud) shows countdown status.

## Planned — Phase 2

Add 433MHz RF remote button (EV1527 4-button kit) to manually trigger spray without motion detection.

## Notes

- Power the Arduino with a quality 1A+ USB-C charger via direct cable. Cheap chargers or USB-A adapters cause brownout resets when the relay fires.
- The Antelco nozzle barb (4mm) is undersized for 1/4" ID silicone tubing — use a stainless worm-drive hose clamp to secure it properly.
