# Compiling the sources for Fedora 20 #

[return to main page.](MainPage.md)
<br />

# First you need to make sure you have the correct packages #
Download the following packages as follows:<br />
sudo yum install gcc-c++<br />
sudo yum install automake libtool<br />
sudo yum install icu4j<br />
sudo yum install gettext<br />
sudo yum install libX11-devel<br />
sudo yum install glib2-devel<br />
sudo yum install intltool<br />
sudo yum install gimp<br />
sudo yum install gimp-devel<br />
<br />

# Download the sources from the Source tab on this page #

git->fedora->gimp-plugin-insanebump<br />
Place the source code into a directory you can use.<br />
Then run the following commands as a user:<br />
aclocal<br />
automake<br />
autoconf<br />
chmod 777 configure<br />
./configure<br />
make<br />
<br />
Now in the directory: InsaneBump/fedora/gimp-plugin-insanebump/src you will find the executable called: gimp-plugin-insanebump