# SDL Projects

This repository contains two SDL-based C projects: **SDL_Audio** and **SDL_Graphics**. Each demonstrates a different aspect of multimedia programming using the SDL2 library.

---

## SDL_Audio

A simple audio player that loads and plays a WAV file using SDL2's audio subsystem.

### Features
- Loads a WAV file (`sample.wav`)
- Plays the audio for 5 seconds
- Demonstrates basic SDL2 audio initialization and playback

### Files
- `audio.c`: Source code for the audio player
- `sample.wav`: Example WAV file to play
- `audio_player`: Compiled binary (if present)

### Build & Run
```sh
# Install SDL2 development libraries if not already installed
sudo apt-get install libsdl2-dev libsdl2-mixer-dev

# Compile
gcc audio.c -o audio_player -lSDL2

# Run
./audio_player
```

---

## SDL_Graphics (Bouncy Ball)

A graphical simulation of a bouncing ball using SDL2's software rendering. The ball responds to gravity, friction, and user input.

### Features
- Real-time 2D physics for a bouncing ball
- Software rendering of a filled circle
- User controls:
  - Click: Move ball to mouse position with random velocity
  - SPACE: Boost ball upward
  - R: Reset ball to initial position
  - ESC/Close: Quit simulation

### Files
- `bouncy_ball.c`: Main source code for the simulation
- `bouncy_ball.h`: Header file with ball structure and function prototypes
- `bouncy_ball`: Compiled binary (if present)

### Build & Run
```sh
# Install SDL2 development libraries if not already installed
sudo apt-get install libsdl2-dev

# Compile
gcc bouncy_ball.c -o bouncy_ball -lSDL2 -lm

# Run
./bouncy_ball
```

---

## Requirements
- SDL2 library (and SDL2_mixer for audio)
- GCC or compatible C compiler
- Linux (tested), but should work on other platforms with SDL2 support

## Notes
- Ensure you have the necessary SDL2 development packages installed.
- The provided binaries (`audio_player`, `bouncy_ball`) may need to be rebuilt on your system.
- `sample.wav` must be present in the `SDL_Audio` directory for the audio player to work.
