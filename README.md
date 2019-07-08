### WML2XML 
wml2xml is a conversion tool for "Battle for Wesnoth" WML (replays and scenarios) files. It converts the WML files to XML.

#### Build
Install dependencies: sdl, boost_iostreams, boost_filesystem, boost_system, boost_locale

Simply type:

    make

#### Usage
The tool takes a WML file as argument and outputs XML on standard output. When called without argument it reads the WML from standard input.
