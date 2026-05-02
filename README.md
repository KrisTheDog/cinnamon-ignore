<h1 align="center">Cinnamon</h1>

<p align="center">
    <img src="icon.png" height="128px"></img>
</p>
<p align="center">
    <a href="https://discord.gg/AahyBCvVR2"><img src="https://img.shields.io/discord/1406856655920168971?color=5865F2&logo=discord&logoColor=white&label=discord"></a>
</p>

---

> [!IMPORTANT]  
> Cinnamon is not finished and will have bugs. 3DS is going through a rewrite so you cannot build at this time.

Cinnamon aims to be a open source re-implementation of GameMaker 1.4's (gms2 soon) runner for the 3DS and Wii U. This opens up lots of opportunities for games like Pizza Tower, Forager, Undertale, and Deltarune to run on the 3DS and Wii U.

Games like UNDERTALE have already been successfully ported to the Wii U and 3DS and are playable the whole way through. While only Bytecode version 16 is supported as of now, more bytecodes and features will be implemented in the future.

## Building For Wii U

You must have a proper devkitPro Wii U enviroment set up and configured for your platform.

Configure with the Wii U CMake wrapper and then build:

```bash
powerpc-eabi-cmake -S . -B build/wiiu
cmake --build build/wiiu
```

This produces `Cinnamon.elf`, `Cinnamon.rpx`, and a `.wuhb` bundle in `build/wiiu`.

## Showcase

- **Snowdin Forest**

<img src="/resources/readme/screenshots/pic1.jpg" height="128px"></img>
 
- **Undyne the Undying:** https://www.youtube.com/watch?v=QqKhSn0SHL8

## Disclaimer

Cinnamon has no association, endorsement, or any connection whatsoever with any of the software that it facilitates, and does not provide any of the software it can run by itself. In order to use Cinnamon, you will need to provide your own game files.
