# miniweb-vladtepesch
Small, cross-platform HTTP server.  
It can serve content from an archive file (zip/7z).

**BEWARE: should be considered unsecure and be only used in local environment and under no circumstances made accessable from internet or other untrusted networks (please note the possibility to bind the server to specific (e.g. localhost) interfaces with** `-i` **)**

- This is a fork of https://github.com/avih/miniweb that was is not maintained anymore, with the following enhancements:
  - added zip - support
  - added dependencies for 7z-support (allthough it does not properly work with large 7zfiles)
  - made compilable with Visual Studio 2015
  - improved mime type support

# miniweb-avih
Small, cross-platform HTTP server

- This is a fork of http://miniweb.sourceforge.net/ , with the following enhancements:
  - Enhanced directory listing with sortable columns (requires js, else the normal listing).
  - Unicode support on windows - command line and directory listing.
  - Better support for large files in download (correct size at the HTTP header) and directory listing
  (displayed size is now correct).
  - Linux/OS X/etc: faster shutdown, and less wait before next successful startup.
  - POST support disabled for now.
  - Easier build  with custon `$CC`, and other minor improvements. The MSVC project files might be stale.
  - Name changed to `Miniweb-avih`.


- License: "GNU Library or Lesser General Public License version 2.0 (LGPLv2)".
See [License note](./miniweb-avih/LICENSE.md).
- A snapshot of the original repository 
[svn rev 208](https://sourceforge.net/p/miniweb/code/208/) on which this fork is
based is at branch `svn-orig-rev-208` of this repository (the original project seems
unmaintained since 2013.).

### [Original project description below]

## MiniWeb
MiniWeb is an embeddable, cross-platform, small-footprint HTTP server
implementation, implementing basic GET and POST requests as well as request
handling dynamic content generating. It works on x86 (Windows/Linux),
ARM, MIPS and any posix platforms, either embedded or standalone.

## Features
- small footprint HTTP server written in C
- GET & POST actions with basic HTTP authentication
- user-defined request handler routines
- cross-platform compatibility
- basic HTTP audio and video streaming
- serial UART to HTTP gateway
