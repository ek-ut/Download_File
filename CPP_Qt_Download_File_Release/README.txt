CPP_Qt_Download_File.
Application designed to download files from a URL link.

Application developed in C ++ qt framework.
For a 32 bit system, build system qmake, MinGW 32 compiler.


Work description
 By clicking on the download button, a child stream is created and the file download begins in it.
 Url link is specified in the text field, if the field is empty, the default link is used
 https://ubuntu.volia.net/ubuntu-releases/20.04.2.0/ubuntu-20.04.2.0-desktop-amd64.iso
 The user logs out to the form and writes to a file.
 The application supports downloading multiple files at the same time.


Known issues
 Unless the link points directly to the file, page download may occur.
 Crashes with OpenSSL libraries were noticed on some PCs