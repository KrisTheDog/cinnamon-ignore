<h1 align="center">🥧 Butterscotch 🥧</h1>

<!-- Badges, about the GitHub repository itself -->
<p align="center">
<a href="https://discord.gg/2gQR7t3WJR"><img src="https://img.shields.io/discord/1406856655920168971?color=5865F2&logo=discord&logoColor=white&label=discord"></a>
</p>

> [!IMPORTANT]  
<<<<<<< HEAD
> Butterscotch is still VERY early in development and it is NOT that good yet.

When you create a game in GameMaker: Studio and export it, GameMaker: Studio exports the game code as bytecode instead of native compiled code, and that bytecode is compatible with any other GameMaker: Studio runner (also known as YoYo runner), as long as they have matching GameMaker: Studio versions. This is similar to how Java applications work.

This is how projects such as [Droidtale](https://mrpowergamerbr.com/projects/droidtale) (which was also made by yours truly) can exist. We exploit that GameMaker: Studio games compile to bytecode, which means they can be ran on *any* platform that has an official runner for it!
=======
> Cinnamon is not finished and will have bugs. 

When you create a game in GameMaker: Studio and export it, GameMaker: Studio exports the game code as bytecode instead of native compiled code, and that bytecode is compatible with any other GameMaker: Studio runner (also known as YoYo runner), as long as they have matching GameMaker: Studio versions. This is similar to how Java applications work.

This is how projects such as Droidtale can exist. We exploit that GameMaker: Studio games compile to bytecode, which means they can be ran on any platform that has an official runner for it!

If GameMaker games use bytecode, what prevents us from creating our own runner? And if we can write our own runner, what prevents us from porting GameMaker: Studio games to other platforms?

Thats where projects like [Butterscotch](https://github.com/MrPowerGamerBR/Butterscotch) come in! Butterscotch is an open source reimplementation of GameMaker: Studio's runner.

If this already exists, then whats stopping people from porting Butterscotch to MORE consoles? Whats stopping *us* from porting a variety of GameMaker: Studio games to the 3DS and Wii U?

This is where Cinnamon, a fork of Butterscotch comes in!

Cinnamon aims to be a open source re-implementation of GameMaker Studios runner **for the 3DS and Wii U.** This opens up lots of opportunities for games like Pizza Tower, Hyper Light Drifter, Undertale, and Deltarune to run on the 3DS and Wii U.


## Game Compatibility

Butterscotch's and Cinnamon's goal is to be able to have Undertale v1.08 (GameMaker: Studio 1.4.1804, Bytecode Version 16) fully playable. But we do want to support more GameMaker: Studio games in the future too!

While our target is Undertale v1.08, that doesn't mean that other games CAN'T run in Cinnamon! Because Cinnamon itself is a runner and not a Undertale port/remake, you CAN run other GameMaker: Studio games with it and, as long as the game is compiled with GameMaker: Studio 1.4.1804 and they only use GML variables and functions that Cinnamon supports, it should work fine.

Here are the Bytecode Versions that Cinnamon supports

* Bytecode Version 16
* Bytecode Version 17

However, that doesn't mean that a game that uses a compatible version WILL run! The bytecode support is still a WIP, and Cinnamon may have quirks that the original GameMaker: Studio runner may not have.

Of course, there are exceptions that break game compatibility altogether:

* Games compiled with YYC, because they use native code instead of bytecode. 
* Games compiled with the new [GMRT](https://github.com/YoYoGames/GMRT-Beta/tree/main), because they use native code instead of bytecode.

## Supported Platforms
* Nintendo 3DS
* Nintendo Wii U
* ...and maybe more in the future!

## Project Sunshine
* Project Sunshine is a project that aims to use Cinnamon to port a variety of games (such as UNDERTALE, DELTARUNE, and maybe more games in the future) to the Wii U, 3DS, and maybe more consoles like the GameCube in the future! You can get beta builds on our [Discord](https://discord.gg/AahyBCvVR2) aswell as news on the ports.
### UNDERTALE: Wii U Edition
* A released, full port of UNDERTALE on the Wii U. You can download this port on our releases page or on our Discord.
### DELTARUNE: Wii U Edition
* A full port of DELTARUNE to the Wii U. Still currently in development. Expect a Chapter 1 release date of before July.
### UNDERTALE: 3DS Edition
* A full port of UNDERTALE to the 3DS with 3DS exclusive features such as 3D and bottom screen features.
### DELTARUNE: 3DS Edition
* A full port of atleast Chapter One of DELTARUNE to the 3DS.
>>>>>>> fd39ee1c2b15c00f1ee7d7d136530af4b1239c2c

Ever since I created Droidtale 10+ years ago, I had that lingering thought in my mind... If GameMaker games use bytecode, what prevents us from creating our *own* runner? And if we can write our *own* runner, what prevents us from porting GameMaker: Studio games to other platforms?

And that's where Butterscotch comes in! Butterscotch is an open source re-implementation of GameMaker: Studio's runner.

**Butterscotch PlayStation 2 ISO Generator:** https://butterscotch.mrpowergamerbr.com/

## Game Compatibility

Butterscotch's goal is to be able to have Undertale v1.08 (GameMaker: Studio 1.4.1804, Bytecode Version 16) fully playable. But we do want to support more GameMaker: Studio games in the future too!

While our target is Undertale v1.08, that doesn't mean that other games CAN'T run in Butterscotch! Because Butterscotch is a runner and not a Undertale port/remake, you CAN run other GameMaker: Studio games with it and, as long as the game is compiled with GameMaker: Studio 1.4.1804 and they only use GML variables and functions that Butterscotch supports, it should work fine.

Here are the Bytecode Versions that Butterscotch supports

* Bytecode Version 15
* Bytecode Version 16
* Bytecode Version 17

However, that doesn't mean that a game that uses a compatible version WILL run! The bytecode support is still a WIP, and Butterscotch may have quirks that the original GameMaker: Studio runner may not have.

Of course, there are exceptions that break game compatibility altogether:

* Games compiled with YYC, because they use native code instead of bytecode. 
* Games compiled with the new [GMRT](https://github.com/YoYoGames/GMRT-Beta/tree/main), because they use native code instead of bytecode.

## Supported Platforms

* Linux (GLFW, OpenGL)
* macOS (GLFW, OpenGL)
* Windows (GLFW, OpenGL, MinGW)
* PlayStation 2 (ps2sdk, gsKit)
* Haiku (GLFW)
* ...and maybe more in the future!

## Community Ports

* [Xbox 360 (Butterscotch-360)](https://github.com/ceilingtilefan/Butterscotch-360) by @ceilingtilefan
* [3DS and Wii U (Cinnamon)](https://github.com/Project-Sunshine-Native/cinnamon) by @casrielasriel, @grayforz24682, @d16.dorian, @ralcactus

## Building Butterscotch

```bash
mkdir build && cd build
cmake -DPLATFORM=glfw -DCMAKE_BUILD_TYPE=Debug ..
make
```

If you are using CLion, set the platform in `Settings` > `Build, Execution, Deployment` > `CMake` and add `-DPLATFORM=glfw`

Then run Butterscotch with `./butterscotch /path/to/data.win`!

<<<<<<< HEAD
## CLI parameters

The GLFW target has a lot of nifty CLI parameters that you can use to trace and debug games running on it.
=======
### Wii U (Real Hardware)

- **UNDERTALE (Bytecode 16)**
<img width="160" height="120" alt="Image" src="https://github.com/Project-Sunshine-Native/cinnamon/blob/db8de335d5067d628d3bae1c90a705a57db3dbf9/resources/readme/screenshots/1000057247.jpg" />
<img width="160" height="120" alt="Image" src="https://github.com/Project-Sunshine-Native/cinnamon/blob/db8de335d5067d628d3bae1c90a705a57db3dbf9/resources/readme/screenshots/1000057245.jpg" />
<img width="160" height="120" alt="Image" src="https://github.com/Project-Sunshine-Native/cinnamon/blob/db8de335d5067d628d3bae1c90a705a57db3dbf9/resources/readme/screenshots/1000057243.jpg" />

- **SURVEY_PROGRAM (Bytecode 16)**
<img width="160" height="200" alt="Image" src="https://github.com/Project-Sunshine-Native/cinnamon/blob/db8de335d5067d628d3bae1c90a705a57db3dbf9/resources/readme/screenshots/1000045789.jpg" />
<img width="160" height="200" alt="Image" src="https://github.com/Project-Sunshine-Native/cinnamon/blob/db8de335d5067d628d3bae1c90a705a57db3dbf9/resources/readme/screenshots/1000057255.jpg" />

### Wii U (Cemu/Emulator)

- **SURVEY_PROGRAM (Bytecode 16)**
<img width="160" height="200" alt="Image" src="https://github.com/Project-Sunshine-Native/cinnamon/blob/fe76737aea9d6402a55eb0059444c5283f88dff1/resources/readme/screenshots/1000057249.jpg" />
<img width="160" height="200" alt="Image" src="https://github.com/Project-Sunshine-Native/cinnamon/blob/fe76737aea9d6402a55eb0059444c5283f88dff1/resources/readme/screenshots/1000057251.jpg" />

- **Pizza Tower Demo (Demo 1, Sage 2019 Demo) (Bytecode 16)**
<img width="160" height="200" alt="Image" src="https://github.com/Project-Sunshine-Native/cinnamon/blob/fe76737aea9d6402a55eb0059444c5283f88dff1/resources/readme/screenshots/1000057253.png" />
<img width="160" height="200" alt="Image" src="https://github.com/Project-Sunshine-Native/cinnamon/blob/fe76737aea9d6402a55eb0059444c5283f88dff1/resources/readme/screenshots/1000057254.png" />

### 3DS (Real Hardware)

- **UNDERTALE (Bytecode 16)**
<img width="160" height="300" alt="Image" src="https://github.com/Project-Sunshine-Native/cinnamon/blob/d2b7229ec79a30dc5cabaad163a595741d37897a/resources/readme/screenshots/1000057263.jpg" />
<img width="160" height="300" alt="Image" src="https://github.com/Project-Sunshine-Native/cinnamon/blob/d2b7229ec79a30dc5cabaad163a595741d37897a/resources/readme/screenshots/1000057262.jpg" />
<img width="160" height="300" alt="Image" src="https://github.com/Project-Sunshine-Native/cinnamon/blob/d2b7229ec79a30dc5cabaad163a595741d37897a/resources/readme/screenshots/1000057257.jpg" />
<img width="160" height="300" alt="Image" src="https://github.com/Project-Sunshine-Native/cinnamon/blob/d2b7229ec79a30dc5cabaad163a595741d37897a/resources/readme/screenshots/1000049179.jpg" />
>>>>>>> fd39ee1c2b15c00f1ee7d7d136530af4b1239c2c

* `--debug`: Enables debugging hotkeys
* `--screenshot=file_%d.png`: Screenshots the runner, requires `--screenshot-at-frame`.
* `--screenshot-at-frame=Frame`: Screenshots the runner at a specific frame. Can be used multiple times.
* `--headless`: Runs the runner in headless mode. When running in headless mode, the game will run at the max speed that your system can handle.
* `--print-rooms`: Prints all the rooms in the `data.win` file and exits.
* `--print-declared-functions`: Prints all the declared functions (scripts, object events, etc) in the `data.win` file and exists.
* `--trace-variable-reads`: Traces variable reads
* `--trace-variable-writes`: Traces variable writes
* `--trace-function-calls`: Traces function calls
* `--trace-alarms`: Traces alarms
* `--trace-instance-lifecycles`: Traces instance creations and deletions
* `--trace-events`: Traces events
* `--trace-event-inherited`: Traces event inherited calls
* `--trace-tiles`: Traces drawn tiles
* `--trace-opcodes`: Traces opcodes
* `--trace-stack`: Traces stack
* `--trace-frames`: Logs when a frame starts and when a frame ends, including how much time it took to process each frame.
* `--always-log-unknown-functions`: When enabled, Butterscotch will always log unknown functions instead of logging them once per script.
* `--always-log-stubbed-functions`: When enabled, Butterscotch will always log stubbed functions instead of logging them once per script.
* `--trace-bytecode-after-frame`: When set, controls when `--trace-opcodes` and `--trace-stack` will start logging. Useful when debugging interpreter-heavy scripts.
* `--exit-at-frame=Frame`: Automatically exit the runner after X frames.
* `--speed`: Speed multiplier
* `--seed=Seed`: Sets a fixed seed for the runner, useful for reproduceable runs.
* `--print-rooms`: Prints all rooms to the console, along with all objects present in the room.
* `--print-declared-functions`: Prints all declared GML scripts by the game
* `--disassemble`: Dissassembles a specific script
* `--record-inputs`: Records user inputs
* `--playback-inputs`: Playbacks user inputs
* `--os-type`: Allows changing the built-in `os_type` value. The default is Windows. Example: When running Undertale Xbox, you would need to set it to `--os-type xboxone`.
* `--profile-gml-scripts`: Logs which GML scripts are the heaviest in terms of time and executed instructions.
* `--profile-opcodes`: Ranks which GML opcodes were executed the most.

<<<<<<< HEAD
## Debug Features

When running Butterscotch with `--debug`, the following hotkeys are enabled:

* `Page Up`: Moves forward one room
* `Page Down`: Moves backwards one room
* `P`: Pauses the game
* `O`: While paused, advances the game loop by one frame
* `F12`: Dumps the current runner state to the console
* `F11`: Dumps the current runner state to the console (JSON format), or dumps it to a file if `--dump-frame-json-file` is set.
* `F10`: Sets the `global.interact` flag to `0`. Useful in Undertale when you are moving through rooms and one of them starts a cutscene that doesn't let you move.

## Performance

Performance is pretty good on any modern computer, but when running on low end targets (like the PS2) it is *very* slow when there's a lot of instances on screen, or when a instance does a for loop.

## Then why not have a transpiler?

The issue with a transpiler is that, if you try transpiling the game in the "naive" way, that is, emitting VM calls like it was the original bytecode, you won't get any 
*improvement* from it, you would need to create a *good* transpiler that actually transpiles it into *good* code, and that's way harder.

Having a transpiler also have other disadvantages:

1. You lose the ability of debugging the runner at a "high level" by tracing opcodes.
2. Compilation is SLOW, transpiling Undertale in a naive way to C and building it takes 90 seconds on a modern computer, and building it to other targets is so slow that I wasn't even able to test it.

## Screenshots

### Undertale (GLFW) [Bytecode Version 16]

<img width="160" height="120" alt="Image" src="https://github.com/user-attachments/assets/6651cc2e-0d6d-4354-b98d-081e84a981df" />
<img width="160" height="120" alt="Image" src="https://github.com/user-attachments/assets/1d6edc51-2829-4f8f-b900-393f21a6655b" />
<img width="160" height="120" alt="Image" src="https://github.com/user-attachments/assets/0d41f16c-7ee5-47de-a2e8-5831cdcd2745" />
<img width="160" height="120" alt="Image" src="https://github.com/user-attachments/assets/45dc47fb-6d8a-44d4-8cbb-2e5791100144" />
<img width="160" height="120" alt="Image" src="https://github.com/user-attachments/assets/7db1c869-e625-4558-9119-0f23da0f020c" />
<img width="160" height="120" alt="Image" src="https://github.com/user-attachments/assets/71fc7616-d580-48fe-aa6d-1e6ceea41bdb" />
<img width="160" height="120" alt="Image" src="https://github.com/user-attachments/assets/4098936e-a1b9-4971-901d-702ec390afa7" />
<img width="160" height="120" alt="Image" src="https://github.com/user-attachments/assets/dd3dcce3-3d78-452f-9af0-27133497650c" />
<img width="160" height="120" alt="Image" src="https://github.com/user-attachments/assets/2e356d04-5aaf-47d4-9bc3-4abba78cd18d" />
<img width="160" height="120" alt="Image" src="https://github.com/user-attachments/assets/a9cbc57f-e9c1-4985-a6af-a98e5fce5ff3" />
<img width="160" height="120" alt="Image" src="https://github.com/user-attachments/assets/e5c67781-0ffc-43c8-9c7d-333254eed704" />
<img width="160" height="120" alt="Image" src="https://github.com/user-attachments/assets/93900e3c-79b5-4a05-bd6c-d68814e9e101" />

### Undertale (PlayStation 2) [Bytecode Version 16]

Here's a video :3 https://youtu.be/PuzBxe0VGtY

### DELTARUNE (SURVEY_PROGRAM) (PlayStation 2) [Bytecode Version 16]

Here's a video :3 https://youtu.be/TLJtV2WnrmQ

### DELTARUNE Chapter 2 (GLFW) [Bytecode Version 17]

<img width="160" height="120" alt="image" src="https://github.com/user-attachments/assets/d0df9858-ad2b-4642-9f32-a542d1d942e0" />

### DELTARUNE Chapter 3 (GLFW) [Bytecode Version 17]

<img width="160" height="120" alt="image" src="https://github.com/user-attachments/assets/7b49d434-e66f-4ee3-bfe8-c0b4f45ceeb7" />
<img width="160" height="120" alt="image" src="https://github.com/user-attachments/assets/afbe62ad-4706-4882-a9c9-6c239ed57c69" />
<img width="160" height="120" alt="image" src="https://github.com/user-attachments/assets/d83c9f8c-e9b9-410e-8d3d-3663ede23fab" />

### DELTARUNE Chapter Selector (GLFW) [Bytecode Version 17]

<img width="160" height="120" alt="image" src="https://github.com/user-attachments/assets/b8a848df-fd1c-49b7-9602-e8020ac86d5d" />
=======
Cinnamon has no association, endorsement, or any connection whatsoever with any of the software that it facilitates, and does not provide any of the software it can run by itself. In order to use Cinnamon, you will need to provide your own game files.

>>>>>>> fd39ee1c2b15c00f1ee7d7d136530af4b1239c2c
