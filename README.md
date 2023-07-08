# GigE C++

This code consists of three tools that allow you to do the following:

## enumerate
Lists the cameras available on the local network, and returns a JSON with the following data:

- SerialNumber
- ModelName
- IpAddress

This is an example of the JSON structure:
{"Cameras":[{"SerialNumber":"00000000","ModelName":"acAXX00-X0gm","IpAddress":"192.168.1.XXX"}]}

## grab
It provides a function with only one argument: the SerialNumber of the camera. It takes an image from the camera and returns it in jpg format, the maximum waiting time is 1000ms.
Several error catches have been placed in case no cameras are available to test the code.

## grab_wo_opencv
Identical function to the previous one, but does not require the opencv library (due to its complexity to be compiled on some architectures); it returns an image in .tif format.

## tested on the following systems and architectures:

### OS
- Windows 10.0.19045.3086
- Debian 11 (Bullseye)
- Ubuntu 20.04 LTS (Focal Fossa)
- Ubuntu 22.04 LTS (Jammy Jellyfish
- Ubuntu 23.04 (Lunar Lobster)

### Architecture
- arm64
- AMD64 (x86_64)

