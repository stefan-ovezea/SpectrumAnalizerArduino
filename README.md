# Arduino Spectrum Analizer
Audio visualizer through serial on Arduino

## Details
The client app sends an array of peak amplitudes for a spectrum to an Arduino through serial, then the Arduino does the rest.  
Currently there are 2 versions of the client applications.  
One in Python that works on all Operating Systems, but can only capture data from a microphone.  
The other one in C# that works only on Windows, but can capture the audio output of the sound card.  
