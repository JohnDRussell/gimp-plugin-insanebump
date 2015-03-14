# InsaneBump #
This is the main repository for the source code for the Gimp plug-in InsaneBump.
<br />
This is a C language version of the Insane Bump plugin.  I have converted the Python code to a C language program and all the needed libraries and tools to do so.  I have improved upon this program by adding an AO adjustment and 5 Preview panes.  This is the sixth release.
This plug-in produces different files within the original image's directory:<br />
the filename\_n is the normal map,<br />
the filename\_s is the specular,<br />
the filename\_d is the diffusion (just the color)<br />
the filename\_a is the ambient occlusion<br />
the filename\_h is the displacement (or height map)<br />
[Installation on Windows](WindowsInstallation.md)<br />
[Installation on Ubuntu Linux](UbuntuInstallation.md)<br />
[Installation on Fedora 20](Fedora20Installation.md)<br />
[Tutorials](Tutorials.md)
<br />
<h2>Notes</h2>
AO adjustment now affects all produced images. <br />
Works with Windows XP, 7, 8, Ubuntu 12.04 and newer.
Tested with Gimp version 2.6 and 2.8.8.  Source code
includes libraries needed for building any gimp<br />
plug-in on Windows using MinGW.
<br />
<h2>Using InsaneBump</h2>
Copy this new file to your gimp user directory.  On my machine it was:
/home/derby/.gimp-2.6/plug-ins/

Start gimp, open up your graphics base file.  Then select Filters
and then Map and then InsaneBump...
<br />
Filters->Map->InsaneBump...
<br />
Make a try at the settings in the dialog box that pops up,
click Execute.  The files will be written to the hard disk as follows:
<br />
the filename\_n is the small normal map,<br />
the filename\_s is the specular map,<br />
the filename\_d is the diffusion map (just the color),<br />
the filename\_a is the ambient occlusion map,<br />
the filename\_h is the displacement (or height map),<br />
the filename\_hn is the high normal map,<br />
the filename\_ln is the large normal map,<br />
the filename\_mn is the medium normal map,<br />
the filename\_sn is the small normal map<br />
So say your image is called Fence.png
the program will output the following files:<br />
Fence\_n.png<br />
Fence\_s.png<br />
Fence\_d.png<br />
Fence\_a.png<br />
Fence\_h.png<br />
Fence\_hn.png<br />
Fence\_ln.png<br />
Fence\_mn.png<br />
Fence\_sn.png<br />
and overwrite existing files in the same directory
as the Fence.png file.

Here is a screenshot of InsaneBump on Ubuntu with default values:<br />
<img src='https://gimp-plugin-insanebump.googlecode.com/git/images/InsaneBumpScreenShot6.png' />
<h2>Figure 1 Screen Shot</h2>

Here is a Wood Tree Scene Example:<br />
Here is the original Wood Tree Scene image:<br />
<img src='https://gimp-plugin-insanebump.googlecode.com/git/images/WoodTextureScaled.png' />
<h2>Figure 2 original image</h2>
Here is the ambient occlusion map produced:<br />
<img src='https://gimp-plugin-insanebump.googlecode.com/git/images/WoodTextureScaled_a.png' />
<h2>Figure 3 ambient occlusion map image</h2>
Here is the diffuse color map produced:<br />
<img src='https://gimp-plugin-insanebump.googlecode.com/git/images/WoodTextureScaled_d.png' />
<h2>Figure 4 diffuse color map image</h2>
Here is the specular map produced:<br />
<img src='https://gimp-plugin-insanebump.googlecode.com/git/images/WoodTextureScaled_s.png' />
<h2>Figure 5 specular map image</h2>
Here is the normal map produced:<br />
<img src='https://gimp-plugin-insanebump.googlecode.com/git/images/WoodTextureScaled_n.png' />
<h2>Figure 6 normal map image</h2>
Here is a screenshot of InsaneBump on Windows XP with default values:<br />
<img src='https://gimp-plugin-insanebump.googlecode.com/git/images/InsaneBumpScreenShot6Win.png' />
<h2>Figure 7 Screen Shot Windows</h2>
<br />
# Links #
Here is the link to the Ubuntu 12.04 binary: https://gimp-plugin-insanebump.googlecode.com/git/linux/bin/gimp-plugin-insanebump-Ubuntu-1.0.6.tar.gz

<br />
Here is a link to the Windows Executable: https://gimp-plugin-insanebump.googlecode.com/git/windows/bin/InsaneBump.exe

<br />
and here is the maybe needed mingwm10.dll: https://gimp-plugin-insanebump.googlecode.com/git/windows/bin/mingwm10.dll

<br />
and here is the compressed both files in zip: https://gimp-plugin-insanebump.googlecode.com/git/windows/bin/InsaneBump-Windows-1.0.5.zip
<br />
# Compiling Sources #
The code is gimp and gtk.  So, it built with no changes from Ubuntu 12.04 to Windows XP, 7 and 8.<br />
It does build easily with MSVC, I will give a solution soon.<br />
[Compiling from source for Windows](BuildingWindowsVersion.md)<br />
[Compiling from source for Ubuntu or Linux](BuildingUbuntuVersion.md)<br />
[Compiling from source for Fedora 20](BuildingFedora20Version.md)
<br />
# Update #
Update: Issues corrected, "Restore Defaults" button added<br />
Update: Added instructions and executable for Fedora 20