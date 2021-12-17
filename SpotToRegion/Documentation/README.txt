
2/24/05

- Demonstrates an external program using the SpotToRegion API to spot audio into a Pro Tools region.

- Use the Visual Studio.NET 2002 or Codewarrior 9.2 project files in WinBuild or MacBuild folder to build the demo application.

- There is no difference between the Release and Debug targets in the Windows project file.  The Release target is there for internal compatibility only.

- Currently only spots to one playlist at a time. You must split an interleaved file and call spot() twice to spot a stereo piece of audio.

- See Documentation/html/index.htm for full documentation of the API.
