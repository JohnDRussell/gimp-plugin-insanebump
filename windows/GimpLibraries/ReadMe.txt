The def files in the def virtual folder of this project came from

****************************
1)  downloading gimp-2.6.11.tar.bz2.

    After downloading gimp-2.6.11.tar.bz2 extract to a folder.

    Then go into each lib directory.
    A lib directory such as libgimp and
    
    copy libgimp.def C:\Documents and Settings\<SOMEUSER>\My Documents\CodeLite\Projects\GimpLibraries\libgimp-2.0-0.def
    
    in this project.

    Do this for each of the library directories in the gimp-2.6.11.tar.bz2 file.


****************************
2)  Then download:

    gtk+_2.24.10-1_win32.zip
    gtk+-bundle_2.24.10-20120208_win32.zip
    gtk+-dev_2.24.10-1_win32.zip

    And extract each of these files onto themselves in a folder called c:\gtk

    Then create an empty folder called:

    c:\gtk\lib\gimp-2.0

    then create a prebuild of:

    dlltool -d libgimp-2.0-0.def -D "C:\Program Files\GIMP-2.0\bin\libgimp-2.0-0.dll" -l "C:\gtk\lib\gimp-2.0\libgimp.dll.a"

    for each gimp-2.0 library in the Program Files Directory of Gimp.


****************************
3) Then Download:

    glew-1.10.0-win32.zip
    
    And extract to C:\glew-1.10.0
    
    

Now your computer development environment is ready to build Gimp Plugins!


    
