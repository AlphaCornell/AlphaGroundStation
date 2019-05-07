# AlphaGroundStation
RockBlock MK.II Integration to Ground Station System for Space Mission Operations

## Overview
This is the Ground Station software for the AlphaCubesat project. It receives data from the RockBlock API, processes that data, and ships it to ElasticSearch. It is architected as a RESTful server with multiple modules, Telemetry being the only fully implemented one as of yet, with Control coming in the future. The project is developed in Visual Studio, and remotely built using GCC using Visual Studio's linux targeting features. _This requires setting up a connection to a linux machine_ for building and running. See "Setting up the Alpha Ground Station Development Environment" section.

## Dependencies
- Boost C++ Libraries (https://www.boost.org/users/download/)
- Simple-web-server (https://gitlab.com/eidheim/Simple-Web-Server)

## Setting up the Alpha Ground Station Development Environment
1. Make sure you have Visual Studio 2017 or later installed (https://visualstudio.microsoft.com/)
2. Clone this repo, and open AlphaCubesat.sln with Visual studio
3. Navigate to Tools->Options->Cross Platform->Connection Manager
4. Click "add", and input parameters for the desired linux machine. If your machine uses SSH keys for authentication, select "private key" as the authentication option, and provide the private key file for the user.
![Setup image 1](https://i.imgur.com/DKZLidH.png)
5. Make sure dependencies are installed on the linux machine (for boost, a simple apt-get install boost will do. For the web server, download the source off gitlab, and place it in a folder under /usr/include)
6. Navigate to Project->Properties->C/C++->General, and under "Additional Include Directories", add the file locations of your dependencies. In this example, my Boost libraries were located under /usr/include/, and web server under /usr/include/simple-web. Simply including /usr/include might work too, but will require you to navigate the files to locate the simple-web code
![Setup image 2](https://i.imgur.com/niUnDwy.png)
6. Stay in the properties window, Navigate to Linker->Input, and input into "Library Dependencies" the names of libraries that need to be linked against. This will probably be: pthread, boost_system, boost_filesystem, boost_date_time which is shown in the example:
![Setup image 3](https://i.imgur.com/mZP9Tqq.png)
7. Click "Apply" if it is not already grayed out. Then click "Ok"
8. In the IDE, click the play button (which should display the address of the remote machine) to build and run the software. Make sure port 8080 is open on the machine, and navigate to http://<machine's address>/ping to test if the server is working properly. You can also remotely debug and view the linux console from within visual studio.

## Documentation
You can use Doxygen (http://www.doxygen.nl/) to generate documentation for the source. A pdf copy is provided in this repo at: https://github.com/AlphaCornell/AlphaGroundStation/blob/master/doc_pdf.pdf
