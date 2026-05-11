<h1 align="center">Cinnamon</h1>

<p align="center">
    <img src="icon.png" height="128px"></img>
</p>
<p align="center">
    <a href="https://discord.gg/AahyBCvVR2"><img src="https://img.shields.io/discord/1406856655920168971?color=5865F2&logo=discord&logoColor=white&label=discord"></a>
</p>

---

> [!IMPORTANT]  
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

## Building For Wii U

You must have a proper devkitPro Wii U enviroment set up and configured for your platform.

Configure with the Wii U CMake wrapper and then build:

```bash
powerpc-eabi-cmake -S . -B build/wiiu
cmake --build build/wiiu
```

This produces `Cinnamon.elf`, `Cinnamon.rpx`, and a `.wuhb` bundle in `build/wiiu`.

## Showcase

# Wii U

- **Snowdin Forest**

<img src="/resources/readme/screenshots/pic1.jpg" height="128px"></img>
 
- **Undyne the Undying:** https://www.youtube.com/watch?v=QqKhSn0SHL8

## Disclaimer

Cinnamon has no association, endorsement, or any connection whatsoever with any of the software that it facilitates, and does not provide any of the software it can run by itself. In order to use Cinnamon, you will need to provide your own game files.

