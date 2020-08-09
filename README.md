### Requirements

Add to `OF_DIR/addons`:

- ofxFFT: https://github.com/kylemcdonald/ofxFft (disable FFTW)
- ofxMidi: https://github.com/danomatika/ofxMidi/

Pre-packaged for 64bit OSX:

- ofxSyphon: https://github.com/astellato/ofxSyphon

### Running multiple screens

- Go to system preferences >> mission control >> and set "Displays have separate Spaces" to false. Log out and Log in again, and it will work. ([source](https://forum.openframeworks.cc/t/dual-monitor-full-screen/13654/3))

### Audio Loopback

1. Install SoundFlower: https://github.com/mattingalls/Soundflower/releases/tag/2.0b2
2. Follow the instructions in the above link on how to create a "multi-output" device
3. Select that device in Audio MIDI Setup for Sound Output
4. Run dots, and drag the soundStreamDevice slider until SoundFlower (2ch) is selected

### Examples

https://www.youtube.com/watch?v=gGx9OthM9K4
https://www.youtube.com/watch?v=WMJG8p1r5iMIt
https://photos.google.com/u/1/share/AF1QipMfx5M4p5LDycnTRKAhyBOX-qWbjTVpQzl8y7xk2AoDvElDRCszMuVFuMM8MQUclw?key=b2pMM1RLY1MzODdvdS1yQW5lOEhWc0txUWozMDhR
