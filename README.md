# oi.client.rgbd.libfreenect

Stream KinectV1 data using libfreenect through UDP accross the network.

## Installation
 - Install [libfreenect](https://github.com/OpenKinect/libfreenect)
 - Install [cmake](https://cmake.org/download/)
 - Install [libjpeg-turbo](https://sourceforge.net/projects/libjpeg-turbo/files/1.5.3/libjpeg-turbo-1.5.3-vc64.exe/download)
 - Clone [asio](https://github.com/chriskohlhoff/asio) and [oi.client.rgbd.libfreenect2](https://github.com/OpenIMPRESS/oi.client.rgbd.libfreenect2). 
 - Use this folder structure:
```
  OpenIMPRESS/
    dependencies/
      asio/
     (libfreenect/)
     (libfreenect2/)
    clients/
      oi.client.rgbd.libfreenect/
      oi.client.rgbd.libfreenect2/
```
- ```cd clients/oi.client.rgbd.libfreenect```
- ```mkdir build```
- ```cd build```
- ```cmake -G XCode ..``` (or your platform equivalent, don't forget the two dots at the end!)
- Now open build/oi.client.rgbd.libfreenect.xcodeproj with XCode (or your platform equivalent, i.e. on linux just 'make')

## Command Line Parameters for the binary

```-mm [1|0]```  
Use matchmaking (1=yes, 0=configure ip/port manually)

```-id [socketID]```  
The socket name.

```-lp [portnumber]```  
The port on which this streamer is listening for commands. Automatically set if using matchmaking.

```-rp [portnumber]```  
The port on the streaming destination to which data is sent. If using matchmaking, this is the port of the matchmaking  server.

```-rh [hostname/ip]```  
The ip/hostname on the streaming destination to which data is sent. If using matchmaking, this is the ip/hostname of the matchmaking  server.

```-sn [serialnumber]```  
The serial number of the kinect.

```-pp [pipeline]```  
Not used for microsoft sdk.

```-md [???]```  
Max depth. Don't use this.

```-o [filename]```  
Default file to store recordings to.

```-i [filename]```  
Default file to load recordings from

```-d [folder path]```  
Folder to load/store recordings in/from.

```-dl [0-10]```  
Debug level

## Tip for debugging
In Visual Studio, right click on the oi.client.rgbd.kinectsdk2, go to properties, then "debugging" and enter your preferred command line parameters in the "Command Arguments" field. 
In XCode you can find similar settings under 'edit scheme'.

## Minimal Example: Stream Kinect to a local unity client
Run from Visual Studio/XCode (with the Command Arguments configured) or the compiled binary from CMD:  

```./oi.client.rgbd.libfreenect.exe -rh 127.0.0.1 -rp 5001 -lp 5005 -mm 0```
 
In Unity, use the "LocalExample" prefab from oi.plugin.rgbd to render this pointcloud.
