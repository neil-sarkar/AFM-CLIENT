# Technical Notes (March 2016)
## Next steps
- Prune all files for constants and put them in constants.h or constants.cpp (especially consider this for the settings
- Determine if the AbstractCommandNode is indeed necessary or if it is a remnant of the previous architecture where the commandnode was a templated class













# TECHNICAL NOTES for AFM SERIAL COMMUNICATION C++ APPLICATION

Please also see Google Drive\ICSPI Corp_2\06 R&D\11 Software\Qt Client for GUI design documents.

 - Version 0.1, 2014-12-14
   - Serial communication with the MCU
   - Most main functionality is complete

## Build Instructions

Latest build on Windows 10

Install the Qt bundle. Qt 5.5.0 with Qt Creator 3.5.0 is the current build env. 

1. Download and install qwt-6.1.1
2. Download and install qwtplot3d-0.3.1-322
3. Update the .pro project file with the required file paths
4. Run qmake and build the application and you should be good to go

# Core Components

The main application is divided into 5 threads and several classes. For description of the classes, see src. 

##### 1. mainThead GUI thread
mainThread: responsible for the graphical aspects of the program (e.g., plots, buttons, etc.) as well as reacting to user inputs by creating events for the serialThread (e.g., approach, scan, etc.). 

Local automation algorithms implemented in mainwindow.cpp include:
- Auto Frequency Sweep
- Set DAC Table
- One-click scan 
- Qt-based autoapproach (not very reliable. might be broken as of 2015-12-1)
- Auto stepper motor sleep/wake for appr/retract

As more user conveience features are added, the mainwindow.cpp file will only get larger. It should be split into smaller sections in the future for better maintainability and visibility. 
	
##### 2. sendThread Sender thread
serialThread (serial sender): Owns afm.cpp as an AFM object, s_afm. Translates commandnode pushed by mainwindow, then calls to the AFM object as appropriate. 

##### 3. receiveThread Receiver thread
receiveThread (serial receiver): Owns nothing. Receives MCU response as full messages from afmThread, performs error checking, process the message, sends content of message (if any) to the mainThread for logging or user viewing.

##### 4. eventThread Continuous event thread
eventThread (timed thread): creates events for the serialThread on a periodic basis for continuous plotting of data (e.g., amplitude plot). Note that this is the only thread with a sense of time. 

##### 5. afmThread AFM Communication Thread
afmThread: This thread owns the serial port exclusively. it implements the serial protocol support for such features like masking/etc. Upon collection of some characters on serial, the class emits the message recv signal to receive_worker for processing. 

The threads communicate by way of 3 buffers, plus one buffer for graphics.

Note that Qt uses an internal event buffer for signals and such. afm.cpp and afm_worker.cpp are connected using only the event queue. 

##### 1. Command buffer
The Command buffer can only be written to by the GUI thread. When the user performs an action the GUI pushes to this buffer to request that the Sender thread communicates with the MCU. Captures the flow of the commands that are to be sent to the MCU. Commands could be initiated by the user (mainThread) or generated on a timer for plotting purposes (eventThread).

buffer writers: mainThread and eventThread  
buffer reader: serialThread

##### 2.Receive buffer
The Receive buffer is written to by the Sender thread. When the sender receives a 
request for a command it pushes to the receive buffer to notify the receiver thread
that there will be bytes to be read. Synchronizes the serial sender (serialThread) and the serial receiver (receiveThread) threads. serialThread (upon sending a command to the MCU) uses this buffer to notify the receiveThread what type of command was issued  so that the receiveThread knows what response it should receive from the MCU and in what order. This buffer allows for an easy way to check for communication errors by enforcing a temporal ordering of commands.

buffer writer: serialThread
buffer reader: receiveThread

##### 3.Return buffer
The return buffer is written to by the receiver thread. When the receiver receives a
notification to read the serial port it will place the data it reads into the 
return buffer and then the GUI reads the return buffer. Captures the flow of the MCU response. receiveThread fills it up with the content of the MCU response. mainThread uses this buffer to display data to the user.

buffer writer: receiveThread  
buffer reader: mainThread

##### 4.Event thread - graph buffer

The event thread write to the command buffer when we want to update graphs. This thread should handle all graph updating so that the main thread isn't required to spend  resources updating the graphs.

The event thread also pushes nodes into command queue depending on state of the UI. 

## Adding new features

All gui additions can be added easily in the mainwindow.ui file

In order to add new MCU functionality several things must be done.

1. First the objects must be created in the ui menu. Qt takes care of the events.
2. In the mainwindow thread a new node must be pushed onto the commandQueue of type command.
2. In the serialworker thread that node must be dequeued and based on the commandName the corresponding afm function is called. The serialworker will also push a node onto the receiveQueue for the receiver thread to act on.
3. The afm class must have a corresponding function where the bytes are written.
4. The receiver thread must then wait for data to be emitted from the MCU. Then act on the data	and push the buffer back to the main thread to be displayed to the user. The receiver thread must make sure the shift the response buffer from the MCU by the correct number of bytes.

## Future Improvements

In order of priority:
- Template/Polymorphism for commandnode instead of all these constructors. This will greatly improve the readability and modularity of the application.
- Build up a table of errors accumulated over time. This should be in the form of a log. A brief description of the error with a timestamp should be recorded.
- Create a config file with all the project configurations centralized: 
	for example: baudrate, timeout, etc..
- Investigate options for ensuring thread safe access to the MCU
- Explore the functionality of the 3D plotting software. Seems pretty powerful
- Use private variables in places where there are currently macros
- Clean up the code

## Python-based automatic C code generation
cog is used to manage all serial message IDs and relevant enums. It also generates boilterplate code for receive worker. It can be used to generate boilterplate code for sender too. Running CodeValet.bat will download the Serial Message Specifications and Firmware Serial Software Common Enums spreadsheets from Google Drive, and automatically update the source code. 

See http://nedbatchelder.com/code/cog/ for usage. 



	
