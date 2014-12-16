=========================================
AFM SERIAL COMMUNICATION C++ APPLICATION
=========================================

-Version 0.1
	- Serial communication with the MCU
	- Most main functionality is complete

	
	
**************************
1. BUILD INSTRUCTIONS
**************************

Currently only tested on Windows 7 SP1

Before you start make sure you have the mingw-32 compiler installed
and at least version 5.3.2 of Qt Creator

1. Download and install qwt-6.1.1

2. Download and install qwtplot3d-0.3.1-322

3. Update the nano-i.pro project file with the required file paths

4. Run qmake and build the application and you should be good to go

**************************
2. CORE COMPONENTS
**************************

The main application is divided into 4 threads
	1.GUI thread
	2.Sender thread
	3.Receiver thread
	4.Continuous event thread 
	
The threads communicate by way of 3 buffers
	1.Command buffer
		The Command buffer can only be written to by the GUI thread
		When the user performs an action the GUI pushes to this buffer to request
		That the Sender thread communicates with the MCU
		
	2.Receive buffer
		The Receive buffer is written to by the Sender thread. When the sender receives a 
		request for a command it pushes to the receive buffer to notify the receiver thread
		that there will be bytes to be read.
		
	3.Return buffer
		The return buffer is written to by the receiver thread. When the receiver receives a
		notification to read the serial port it will place the data it reads into the 
		return buffer and then the GUI reads the return buffer.

	4.Event thread
		The event thread write to the command buffer when we want to update graphs. This thread
		should handle all graph updating so that the main thread isn't required to spend 
		resources updating the graphs

**************************
3. ADDITIONS
**************************

All gui additions can be added easily in the mainwindow.ui file

In order to add new MCU functionality several things must be done.
	1. First the objects must be created in the ui menu. Qt takes care of the events.
	
	2. In the mainwindow thread a new node must be pushed onto the commandQueue of type command.
	
	2. In the serialworker thread that node must be dequeued and based on the commandName the 
		corresponding afm function is called. The serialworker will also push a node onto the 
		receiveQueue for the receiver thread to act on.
		
	3. The afm class must have a corresponding function where the bytes are written.
	
	4. The receiver thread must then wait for data to be emitted from the MCU. Then act on the data
		and push the buffer back to the main thread to be displayed to the user. The receiver thread
		must make sure the shift the response buffer from the MCU by the correct number of bytes.
		
**************************
4. FUTURE IMPROVEMENTS
**************************

In order of priority:
	- Template/Polymorphism for commandnode instead of all these constructors. This will greatly 
		improve the readability and modularity of the application.
	- Build up a table of errors accumulated over time. This should be in the form of a log. A brief
		description of the error with a timestamp should be recorded.
	- Automate setting the timeout as a field in the command itself. Add an field in the commandNode
		that specifies the timeout.
	- Create a config file with all the project configurations centralized: 
		for example: baudrate, timeout, etc..
	- Investigate options for ensuring thread safe access to the MCU
	- Explore the functionality of the 3D plotting software. Seems pretty powerful
	- Use private variables in places where there are currently macros
	- Clean up the code
	