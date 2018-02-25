# Real Time Laundry

### What is Real Time Laundry?
Real Time Laundry is a system that notifies the availability of laundry machines in a public laundry room.

By having Real Time Laundry, people can monitor the availability of laundry machines and plan their trip efficiently to a public laundry room, saving their time and labor.

### How it works
![process](http://via.placeholder.com/350x150)
Real Time Laundry consists of a camera and a server.

The camera is installed in a public laundry room, taking pictures of laundry machines every few minutes and sending them to the server via UDP.

The server receives the images and determines how many laundry machines are available with image processing (Laplacian of Gaussian filter) in real time.

The server then posts the information on Real Time Laundry website.

![website](http://via.placeholder.com/350x150)

### Used
* MATLAB
* C
* HTML
* CSS
* JavaScript
* Flask
* Linux
* Socket Programming

### Link
[link](https://google.com/)


<KAIST EE474 Introduction to Multimedia>
<Coded by Alan Wootae Song>