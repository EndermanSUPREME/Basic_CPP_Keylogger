# Basic_CPP_Keylogger
Basic Keylogger made using C++, logs words and runs a check on all logged words upon<br>
`[ENTER]` being pressed and runs a system command when a typed word is within a blacklist.

# Setup \& Edit Points
Be sure if you wish to make changes, there are areas where paths point to `C:\Users\Public\Documents\lockdown`<br>
you can change this to you needs.

The following PS1 files are responsible for running powershell commands to take screenshots of the laptop screen & send emails<br>
you are able to use/remove/edit these to your needs as well.

# Build
I used Visual Studio IDE to build this Windows Project, be sure to set the build to `Release` if it's on DEBUG.<br>
You can create a new VS Project and add the `main.cpp, extern.hpp` into your project.
