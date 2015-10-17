//
//  ZiggeoVideos.h
//
//  Copyright (c) 2015 Ziggeo Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ZiggeoApplication.h"
@import UIKit;

@protocol ZiggeoVideosDelegate <NSObject>

-(void) videoUploadStartedWithPath:(NSString*)sourcePath backgroundTask:(NSURLSessionTask*)uploadingTask;
-(void) videoUploadCompleteForPath:(NSString*)sourcePath withResponse:(NSURLResponse*)response error:(NSError*)error json:(NSDictionary*)json;
-(void) videoUploadProgressForPath:(NSString*)sourcePath totalBytesSent:(int)bytesSent totalBytesExpectedToSend:(int)totalBytes;

@end

@interface ZiggeoVideos : NSObject{
    Ziggeo* _application;
}

@property (weak) id<ZiggeoVideosDelegate> delegate;

- (id) initWithApplication:(Ziggeo*)application_;

- (NSURLSessionTask*) indexWithData:(NSDictionary*)data Callback:(void (^)(NSArray* jsonArray, NSError* error))callback;

- (NSURLSessionTask*) createVideoWithData:(NSDictionary*)data file:(NSString*)fileName cover:(UIImage*)cover callback:(void (^)(NSDictionary* jsonObject, NSURLResponse* response, NSError* error))callback Progress:(void (^)(int totalBytesSent, int totalBytesExpectedToSend))progress;

- (NSURLSessionTask*) getImageForVideoByToken:(NSString*)token callback:(void (^)(UIImage* image, NSURLResponse* response, NSError* error))callback;

- (void) getImageForVideoByPath:(NSString*)path callback:(void (^)(UIImage* image, NSError* error))callback;
- (void) enforceImageForVideoByPath:(NSString*)path image:(UIImage*)image;

- (NSString*) getURLForVideoByToken:(NSString*)token;

-(NSURLSessionTask*) deleteVideoByToken:(NSString*)token callback:(void (^)(NSData* responseData, NSURLResponse* response, NSError* error))callback;

-(NSURLSessionTask*) getDefaultStreamForVideoByToken:(NSString*)token callback:(void (^)(NSString* streamToken, NSURLResponse* response, NSError* error))callback;

-(NSURLSessionTask*) createEmptyVideoWithData:(NSDictionary*)data callback:(void (^)(NSDictionary* jsonObject, NSURLResponse* response, NSError* error))callback;

-(NSURLSessionTask*) recorderSubmitWithVideoToken:(NSString*)videoToken streamToken:(NSString*)streamToken callback:(void (^)(NSDictionary* jsonObject, NSURLResponse* response, NSError* error))callback;

- (NSURLSessionTask*) attachVideoWithVideoToken:(NSString*)videoToken streamToken:(NSString*)streamToken data:(NSDictionary*)data file:(NSString*)fileName callback:(void (^)(NSDictionary* jsonObject, NSURLResponse* response, NSError* error))callback Progress:(void (^)(int totalBytesSent, int totalBytesExpectedToSend))progress;

- (NSURLSessionTask*) attachCoverWithVideoToken:(NSString*)videoToken streamToken:(NSString*)streamToken cover:(UIImage*)cover callback:(void (^)(NSData* data, NSURLResponse* response, NSError* error))callback;

@end
