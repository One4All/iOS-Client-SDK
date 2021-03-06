Ziggeo iOS SDK 2.0
=============

Ziggeo API (http://ziggeo.com) allows you to integrate video recording and playback with only two lines of code in your site, service or app. This is the iOS SDK repository. 

## v 1.1.14 to v.1.1.15
The update brings a new feature - ability to add event handler to the event when video recording stops.

## v 1.1.13 to v.1.1.14
The update brings a fix to the customization of recorder buttons

## v 1.1.12 to v.1.1.13
The update brings a new feature - ability to adjust size of buttons and to set custom button icons in the video recorder .

## v 1.1.11 to v.1.1.12
The update brings a fix for compilation for iOS devices.

## v 1.1.10 to v.1.1.11
The update adds a new method setRecorderCacheConfig to ZiggeoRecorder

## v 1.1.9 to v.1.1.10
The update brings a fix for uploading videos from the camera roll in the latest iOS versions.

## v 1.1.8 to v.1.1.9
The update brings a fix for the compilation error in the advanced test app.

## v 1.1.7 to v.1.1.8
The update brings minor updates and fixes

## v 1.1.6 to v.1.1.7
the update brings iPad video orientation fix 

## v 1.1.5 to v.1.1.6
The update brings custom video and audio settings.

## v 1.1.4 to v.1.1.5
The update improves custom data support.

## v 1.1.3 to v.1.1.4
The update brings minor bugfixes mostly related to video orientation issues on some devices.

## v 1.1.2 to v.1.1.3
The update brings custom user data support on new video creation. See Custom User Data for details.

## v 1.1.1 to v.1.1.2
The update brings subtitles support for auto-transcripted videos. Another new feature - custom video gravity options for the Recorder.

## v 1.1.0 to v.1.1.1
The update brings new optional features such as light meter, audio level meter and face outlining. These features are also available in the updated ZiggeoRecorder delegate

## v.1.0.9 to v.1.1.0
The update bring hidden controls modes for recorder and player.

## v.1.0.8 to v.1.0.9
The update bring dashboard `/debugger` error reporting.

## v.1.0.7 to v.1.0.8
The update bring new `recordingQuality` parameter.

## v.1.0.6 to v.1.0.7
The update bring new `serverAuthToken` and `clientAuthToken` parameters in `ziggeo.connect` object (useful for global auth tokens).

## v.1.0.5 to v.1.0.6
The update bring minor bugfixes and new `data` parameter in `getImageForVideoByToken` method (useful for auth tokens).

## v.1.0.4 to v.1.0.5

New changes bring new features without changing the entry or exit points of any methods or functions. You can safely upgrade without any changes to your existing codes.

Added feature:
1. Video recorder can be utilized with `server_auth` and `client_auth` auth tokens.
	* To specify them for recorder you should use `extraArgsForCreateVideo`
2. Video player can be utilized with `server_auth` and `client_auth` auth tokens.
	* To specify them for player you should use [method described bellow](#initialization-with-optional-authorization-token)

## Setup
- Create iOS App
- Add the following frameworks
	- AVFoundation.framework
	- Ziggeo.framework
- Make sure Ziggeo.framework is added to Embedded Binaries and Linked Framework sections in your app target settings

## Building/Packaging App
- Using `universal` framework is ideal for building apps that run on simulators and actual devices.
  See: _iOS-Client-SDK/Ziggeo/Output/Release-universal_ directory

## Preparing App for submission to App Store
- Create "new run script phase" in the application target build settings to strip unused architectures. Use the script provided with the _iOS-Client-SDK/TestApp_ example (TestApp target settings -> Build phases -> Run script section)

# Basic Usage
## Initialize Application

```
#import "Ziggeo/Ziggeo.h"

Ziggeo* m_ziggeo = [[Ziggeo alloc] initWithToken:@"ZIGGEO_APP_TOKEN"];
```

## Video Player

### Initialization
```
- (ZiggeoPlayer*) createPlayer
{
    return [[ZiggeoPlayer alloc] initWithZiggeoApplication:m_ziggeo videoToken:@"ZIGGEO_VIDEO_TOKEN"];
}
```

Add audio category setup to enable playback and recording while application is in silent mode. This category will also allow to record background audio.

```
//AppDelegate.m
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    [[AVAudioSession sharedInstance] setCategory:AVAudioSessionCategoryPlayAndRecord
                                     withOptions:AVAudioSessionCategoryOptionDuckOthers | AVAudioSessionCategoryOptionDefaultToSpeaker
                                           error:nil];
    return YES;
}
```


### Initialization with optional authorization token
```
    [ZiggeoPlayer createPlayerWithAdditionalParams:m_ziggeo videoToken:@"VIDEO_TOKEN" params:@{ @"client_auth" : @"CLIENT_AUTH_TOKEN" } callback:^(ZiggeoPlayer *player) {
        dispatch_async(dispatch_get_main_queue(), ^
        {
            AVPlayerViewController* playerController = [[AVPlayerViewController alloc] init];
            playerController.player = player;
            [self presentViewController:playerController animated:true completion:nil];
            [playerController.player play];
        });
    }];
```

### Fullscreen Playback
```
    AVPlayerViewController* playerController = [[AVPlayerViewController alloc] init];
    playerController.player = [self createPlayer];
    [self presentViewController:playerController animated:true completion:nil];
    [playerController.player play];
```

### Embedded Playback
```
    ZiggeoPlayer* player = [self createPlayer];
    AVPlayerLayer* playerLayer = [AVPlayerLayer playerLayerWithPlayer:player];
    playerLayer.frame = self.videoViewPlaceholder.frame;
    [self.videoViewPlaceholder.layer addSublayer:playerLayer];
    [player play];
```

## Video Recorder

```
    ZiggeoRecorder* recorder = [[ZiggeoRecorder alloc] initWithZiggeoApplication:m_ziggeo];
    [self presentViewController:recorder animated:true completion:nil];
```

## ZiggeoRecorder2 (Beta)
New recorder rewritten from scratch. Allows to record video and audio without interrupting 3rd party apps playback (Music app, for example). Some additional setup required for simultaneous recording, see TestApp->AppDelegate.m for details.
```
    ZiggeoRecorder2* recorder = [[ZiggeoRecorder2 alloc] initWithZiggeoApplication:m_ziggeo];
    [self presentViewController:recorder animated:true completion:nil];
```

### Capture Duration Limit
```
    ZiggeoRecorder* recorder = [[ZiggeoRecorder alloc] initWithZiggeoApplication:m_ziggeo];
	recorder.videoMaximumDuration = 20; //optional capture duration limit
    [self presentViewController:recorder animated:true completion:nil];
```

### Enable Cover Selector Dialog
```
    recorder.coverSelectorEnabled = YES;
```

### Select Existing Video Instead of Capturing a New One

```
    [recorder selectExistingVideo];
```

### Disable Camera Flip Button

```
    recorder.cameraFlipButtonVisible = NO;
```

### Set Active Camera Device

```
    recorder.cameraDevice = UIImagePickerControllerCameraDeviceRear;
```

### Set Recording Quality

```
    recorder.recordingQuality = mediumQuality;
    //recorder.recordingQuality = lowQuality;
    //recorder.recordingQuality = highestQuality;
```

### Enable Face Outlining
```
recorder.showFaceOutline = YES;
```

### Enable Light Meter Indicator
```
recorder.showLightIndicator = YES;
```

### Enable Audio Level Indicator
```
recorder.showSoundIndicator = YES;
```

### Custom Create Video Parameters (like effects, profiles, etc)

```
    recorder.extraArgsForCreateVideo = @{ @"effect_profile" : @"12345" };
```

### Custom User Data
```
    recorder.extraArgsForCreateVideo = @{@"data": @"{\"foo\":\"bar\"}"}; 
```

### Authorization tokens

Recorder-level auth tokens:
```
    recorder.extraArgsForCreateVideo = @{ @"client_auth" : @"CLIENT_AUTH_TOKEN" };
    recorder.extraArgsForCreateVideo = @{ @"server_auth" : @"SERVER_AUTH_TOKEN" };
```

Global (application-level) auth tokens:
```
    m_ziggeo.connect.clientAuthToken = @"CLIENT_AUTH_TOKEN";
    m_ziggeo.connect.serverAuthToken = @"SERVER_AUTH_TOKEN";
```

### Custom Recorder UI

```
    recorder.showsCameraControls = NO;
    recorder.cameraOverlayView = some_view;
```
Since ZiggeoRecorder is a subclass of UIImagePickerController, it is possible to use any standard ways to create custom camera UI. Please check CustomUITestApp example and this Apple tutorial for more details: https://developer.apple.com/library/ios/samplecode/PhotoPicker/Introduction/Intro.html 

### Streaming Recording
```
    recorder.useLiveStreaming = YES;
```
Streaming recording mode will upload the video stream during the recording without caching to local file first. Video preview and video re-record are not available in this mode.

### Delegate
You can use ZiggeoVideosDelegate in your app to be notified about video uploading events.
```
@interface ViewController : UIViewController <ZiggeoVideosDelegate>

...

{
	...
	[m_ziggeo videos].delegate = self;
}

-(void) videoPreparingToUploadWithPath:(NSString*)sourcePath {
	//this method will be called first before any Ziggeo API interaction
}

-(void) videoPreparingToUploadWithPath:(NSString*)sourcePath token:(NSString*)token {
	//this method will be called immediately after empty video creation on Ziggeo platform
}


-(void) videoUploadStartedWithPath:(NSString*)sourcePath token:(NSString*)token backgroundTask:(NSURLSessionTask*)uploadingTask {
	//this method will be called on actual video upload start
}

-(void) videoUploadCompleteForPath:(NSString*)sourcePath token:(NSString*)token withResponse:(NSURLResponse*)response error:(NSError*)error json:(NSDictionary*)json {
	//video upload finished successfully or failed
}

-(void) videoUploadProgressForPath:(NSString*)sourcePath token:(NSString*)token totalBytesSent:(int)bytesSent totalBytesExpectedToSend:(int)totalBytes {
	//upload progress callback
}

```

# Advanced SDK usage
# Ziggeo API access
You can use the SDK to access Ziggeo Server API methods in the async manner. The SDK provides next functionality:
- Create/remove/index videos
- Custom Ziggeo Embedded Server API requests 

All the API methods are working asynchronously and never blocking the calling thread. You may optionally use custom callbacks (completion blocks) to receive the results.

## Videos API

### Get Video Accessor Object
```
    ZiggeoVideos* videos = [m_ziggeo videos];
```

### Get All Videos
```
    [videos indexWithData:nil Callback:^(NSArray *jsonArray, NSError *error) {
    	//the completion block will be executed asynchronously on the response received
        NSLog(@"videos: %@\nerror: %@", jsonArray, error);
    }];
```

### Create New Video
#### Basic
```
	[videos createVideoWithData:nil file:videoPath cover:nil callback:nil Progress:nil];
```

#### Advanced
You can add your custom completion/progress callbacks here to make the SDK inform your app about uploading progress and response. Cover image is optional and could be nil, making Ziggeo platform to generate default video cover
```
    [videos createVideoWithData:nil file:videoPath cover:(UIImage*)cover
    	callback:^(NSDictionary *jsonObject, NSURLResponse *response, NSError *error) {
	    	NSLog(@"video upload complete: %@, error = %@", jsonObject, error);
   		} Progress:^(int bytesSent, int totalBytes) {
    		NSLog(@"video upload progress: %i/%i", bytesSent, totalBytes);
    	}
    }];
```

### Delete Video
```
	[[self.ziggeo videos] deleteVideoByToken:videoToken 
    	callback:^(NSData *responseData, NSURLResponse *response, NSError *error) {
		//update UI 	
	}];
```

### Get Video URL for Your Own Custom Player
```
    NSURL* videoURL = [NSURL URLWithString:[videos getURLForVideoByToken:token]];
```

### Get Remote Video Thumbnail asynchronously
Remote video thumbs are cached on client side, so you can call the method as frequently as you wish without the performance or network load impact
```
    [videos getImageForVideoByToken:token 
    	callback:^(UIImage *image, NSURLResponse *response, NSError *error) {
        //update UI with the received image
    }];
```

### Generate Local Video Thumbnail asynchronously
Local video thumbs are cached on client side, so you can call the method as frequently as you wish without the performance impact
```
	[videos getImageForVideoByPath:localVideoPath 
    	callback:^(UIImage *image, NSError *error) {
    	//update UI with the received image
	}];
```

## Custom Ziggeo API Requests
The SDK provides an opportunity to make custom requests to Ziggeo Embedded Server API. You can make POST/GET/custom_method requests and receive RAW data, json-dictionary or string as the result.

### Get API Accessor Object
```
ZiggeoConnect* connection = [m_ziggeo connect];
```

### Make POST Request and Parse JSON Response
```
[connection postJsonWithPath:path Data:(NSDictionary*)data 
	Callback:^(NSDictionary *jsonObject, NSURLResponse *response, NSError *error) {
    	//jsonObject contains parsed json response received from Ziggeo API Server
	}
];
```

### Make POST Request and Get RAW Data Response
```
[connection postWithPath:path Data:(NSDictionary*)data 
	Callback:^(NSData *data, NSURLResponse *response, NSError *error) {
    	//data object contains raw data response received from Ziggeo API Server
	}
];
```

### Make GET Request and Get String Response
```
[connection getStringWithPath:path Data:(NSDictionary*)data 
	Callback:^(NSString *string, NSURLResponse *response, NSError *error) {
    	//the string contains stringified response received from Ziggeo API Server
	}
];
```
