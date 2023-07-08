# GigE C++
-----------

This code consists of three tools that allow you to do the following:

### enumerate
Lists the cameras available on the local network, and returns a JSON with the following data:

- SerialNumber
- ModelName
- IpAddress

This is an example of the JSON structure:
{"Cameras":[{"SerialNumber":"00000000","ModelName":"acAXX00-X0gm","IpAddress":"192.168.1.XXX"}]}

### grab
It provides a function with only one argument: the SerialNumber of the camera. It takes an image from the camera and returns it in jpg format, the maximum waiting time is 1000ms.
Several error catches have been placed in case no cameras are available to test the code.

### grab_wo_opencv
Identical function to the previous one, but does not require the opencv library (due to its complexity to be compiled on some architectures); it returns an image in .tif format.

## Tested on the following systems and architectures:

### OS
- Windows 10.0.19045.3086
- Debian 11 (Bullseye)
- Ubuntu 20.04 LTS (Focal Fossa)
- Ubuntu 22.04 LTS (Jammy Jellyfish
- Ubuntu 23.04 (Lunar Lobster)

### Architectures
- arm64
- AMD64 (x86_64)

## Requirements:

### Pylon

Download from: https://www.baslerweb.com/en/downloads/software-downloads/

- Windows 10
  - pylon 7.3.0 Camera Software Suite Windows
- Linux
  - pylon 7.3.0 Camera Software Suite Linux x86 [64 Bit]
- Linux ARM
  - pylon 7.3.0 Camera Software Suite Linux ARM 64 bit

### Others
- CMake
- RapidJSON (via **vcpkg** or **sudo apt install -y rapidjson-dev**)
- OpenCV (necessary only for the **grab** function)




