# 🚀 R-Type

A game engine that roars !

## Table of Contents

- [Project Overview](#project-overview)
- [Download](#download)
- [Installation](#installation)
- [Project Structure](#project-structure)
- [Contributing](#contributing)
- [Documentation](#documentation)
- [License](#license)
- [Authors](#authors)

## Project Overview

R-Type is a reimagined version of the iconic side-scrolling shooter. This project is developed by a
team of enthusiasts aiming to recreate the core gameplay experience with modern technologies.

## Download

Go to the [releases](./releases) page and download the latest version of the game for your platform.

### Binaries

The project provides 2 binaries:

- **Client**: The game client, responsible for rendering the game and handling user input.
- **Server**: The game server, responsible for managing the game state and handling network
  communication.

> [!NOTE]
> You can choose to download only the client or server binaries, depending on your needs.

### Platforms

The project binaries are available for:

- Windows (x64)
- Debian - Ubuntu (x64)
- Other Linux distributions (x64) (manual installation required)
- MacOS (x64 and ARM64) (manual compilation required)

## Installation

Once you have downloaded the binaries you need, follow the instructions below to install the game on
your platform.

### Windows (x64)

1. Download the Windows binaries from the [releases](./releases) page.
2. Execute the `R-Type-client-X.X.X.exe` or `R-Type-server-X.X.X.exe` file depending on what you've
   downloaded.
3. Follow the installation wizard instructions.
4. Once the installation is complete, you can launch the game from the desktop shortcut or the start
   menu.

### Debian - Ubuntu (x64)

1. Download the Debian - Ubuntu binaries from the [releases](./releases) page.
2. Install the `.deb` package:
    - From **command line**: `sudo dpkg -i rtype-client_X.X.X.deb` or
      `sudo dpkg -i rtype-server_X.X.X.deb` depending on what you've downloaded.
    - From **GUI**: Double-click on the downloaded `.deb` file and follow the installation wizard
      instructions.
3. Once the installation is complete, you can launch the game from the application menu.

### Other Linux distributions (x64)

1. Download the Linux binaries from the [releases](./releases) page as a `.tar.gz` archive.
2. Extract the archive to a directory of your choice.
   ```sh
   # Replace X.X.X with the version you've downloaded
   # CLIENT
   tar -xvf R-Type-client-X.X.X.tar.gz
    
   # SERVER
   tar -xvf R-Type-server-X.X.X.tar.gz
   ```

3. Navigate to the extracted directory and run the game:
   ```sh
    # CLIENT
    cd R-Type-client-X.X.X
    ./r-type_client
   
    # SERVER
    cd R-Type-server-X.X.X
    ./r-type_server --help # To see the available options
    ```

### MacOS (x64 and ARM64)
> [!WARNING]
> MacOS binaries are not provided. You need to compile the project manually.

Follow the instructions [here](https://g-epitech.github.io/DFMY-RType/docs/start/build) to compile the project on MacOS.

## Project Structure

The project is divided into several modules, each responsible for a specific aspect of the game.

* **client**: The game client, responsible for rendering the game and handling user input.
* **server**: The game server, responsible for managing the game state and handling network
  communication.
* **libs**: Shared or dependency libraries used by the client and server
    * **zygarde**: Our Entity-Component-System (ECS) library
    * **abra**: Our networking library
    * **game**: Shared game logic and data structures

## Contributing

We welcome contributions from anyone interested in the project. Please refer to
the [CONTRIBUTING.md](./CONTRIBUTING.md) file for more information.

## Documentation

You can find all project documentation [here](https://g-epitech.github.io/DFMY-RType/).

## License

This project is licensed under the MIT License - see the [LICENSE](./LICENSE) file for details.

## Authors

- [Flavien Chenu](https://github.com/flavien-chenu)
- [Math](https://github.com/TekMath)
- [Suceveanu Dragos](https://github.com/sdragos1)
- [Yann Masson](https://github.com/Yann-Masson)
