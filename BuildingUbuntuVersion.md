# Compiling from sources for Ubuntu #

[return to main page.](MainPage.md)

# A special Netbeans Plugin #
The linux code was created using Netbeans.
<br />
A special Netbeans plugin that I wrote was used in the creation of this code.  That plugin is located at:<br />
https://code.google.com/p/cpp-gnu-autotools-netbeans-plugin/source/browse/#git%2Fbuild

# To build the code #

Unzip to a folder and then open up a terminal,<br />
navigate to the folder where you unzipped the project called:<br />
gimp-plugin-insanebump<br />
Then type the following:<br />
aclocal<br />
automake<br />
autoconf<br />
./configure<br />
make<br />
Now in the directory:  InsaneBump/linux/gimp-plugin-insanebump/src
you will find the executable called:  gimp-plugin-insanebump
<br />
# Building for any Linux #
These instructions will work for any flavor of Linux.