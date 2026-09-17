# COSC363 Assignment 1 – Factory.cpp

Luke Hyndman

An OpenGL scene simulating an automated factory assembly line, built in C++ using immediate-mode OpenGL/GLUT.

## Description

The scene models a small conveyor system producing LEGO-style headpieces. Blocks of raw material exit a container, pass under a blowtorch for heating, are shaped by a drill/press, travel around a spiraling downward turn, and are painted by nozzles before returning to a different section of the container.

## Key Features

- **Moving, non-linear conveyor** — tiles follow a preprogrammed path along straight sections and a half-turn spiral, descending as they go.
- **Custom-built sweep surface** — the gear teeth on the spiral's central pole are generated procedurally from a polar sinusoidal function (`R(θ) = sin(θ · N_TEETH / 2) · TOOTH_SIZE + GEAR_RADIUS`), with analytically derived vertex normals rather than pre-modelled geometry.
- **Dual particle systems** — a torch flame (randomised start positions with velocities computed to converge into a tapering flame shape and fade with a time-varying red/blue colour profile) and a paint spray (constant nozzle origin, randomised velocities, particles despawn on contact with the part).
- **Sky sphere** environment mapping at r = 1000.
- **Free-flying camera** with 5 degrees of freedom (WASD + Space/Z for movement, arrow keys to pan/tilt), wireframe toggle, and a reset-to-start view.
- All animation is driven by piecewise, time-parameterised functions for position and rotation, with phase offsets used to stagger multiple heads/tiles along the same path.

## Build Instructions

Developed on Linux using GCC via Visual Studio Codium.

```bash
# Ensure g++ is installed
g++ --version
# If not:
sudo apt update && sudo apt install g++

# Compile
g++ -o Factory Factory.cpp legoman.cpp skybox.cpp conveyor.cpp particles.cpp gear.cpp -lGL -lGLU -lglut

# Move the executable into the build folder and run
mv Factory build/
cd build
./Factory
```

Re-run with `./Factory` as many times as needed; delete and recompile the executable after any code changes.

## Assets & References

- Skybox texture: Oliksiy Yakovlyev, via [Polyhaven](https://polyhaven.com/a/boiler_room)
- LEGO face texture: [LEGO Universe Wiki](https://legouniverse.fandom.com/wiki/LEGO_Universe_Wiki?file=Jamesster_Face_Texture.png)
- Metal texture: p0ss, via [OpenGameArt.org](https://opengameart.org/content/rusted-metal-texture-pack)
- Flame warning sign texture: iStockphoto

## AI Use

Generative AI tools (DeepSeek, GPT-4) were used to explain OpenGL lighting types, generate RGB values for the glowing ingot material, understand gear vertex-normal calculation, and for general debugging support. AI was also used to proofread the accompanying report.

Full write-up with diagrams and derivations available in the assignment report included in this repo.
