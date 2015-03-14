# Compiling from source on Microsoft Windows #

[return to main page.](MainPage.md)

<h2>Requirements</h2>
CodeLite
MinGW
GimpLibrary Project from this google code Source.<br />
The windows sources are inside the Linux Sources.<br />
Here is the link to the Windows Sources:<br />
https://code.google.com/p/gimp-plugin-insanebump/source/browse/#git%2Flinux%2Fgimp-plugin-insanebump%2Fsrc<br />
<h2>GimpLibraries for CodeLite</h2>
In order to compile with CodeLite and MinGW I needed to create some lib files from Gimp dll's.<br />
I created a separate CodeLite Project for that.  It is a non-source project.<br />
The directory names inside the project settings will have to be changed to work on your machine.<br />
And again this was designed from Gimp 2.6.11 source code for the def files.  <br />
This library can be used to compile any gimp plugin using MinGW.
<h2>InsaneBump CodeLite</h2>
The source code in the Source area is for Windows and Linux.<br />
There is a CodeLite workspace included for building in Windows.
<br />
If you need CodeLite and MinGW for building on Windows:<br />

Current available downloads for CodeLite with MinGW are:<br />

CodeLite 5.3 Installer for Windows (8, 7, Vista and XP) with MinGW TDM-GCC 4.7.1 included (SourceForge)<br />

CodeLite 5.3 Installer for Windows (8, 7, Vista and XP) with MinGW TDM-GCC 4.7.1 included (Direct Link)<br />
which are available at:<br />
http://codelite.org/support.php<br />
<h2>CodeLite</h2>
Open up a CodeLite project.<br />
Select the build type: Debug or Release.<br />
Select build.<br />
enjoy.