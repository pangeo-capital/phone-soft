//
//  sipiosAccount.h
//  SipContact
//
//  Created by Tyurin Andrey on 14/04/16.
//  Copyright © 2016 Tyurin Andrey. All rights reserved.
//
// SipiosWrapper.h ver 10.2

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>


@interface sipiosAccountWrapper : NSObject

-(void)setInfo:(NSString*)user :(NSString*)password :(NSString*)displayName :(NSString*)userAgent :(NSString*)deviceToken;

-(void)registration:(NSString*)proto :(NSString*)proxy :(NSString*)domain;

-(void)onRegister:(int)state;
-(void)onUnregister:(int)state;

-(void)onInstantMessage:(NSString*)fromuri :(NSString*)touri :(NSString*)msg :(NSString*)info;

-(void)onInstantMessageStatus:(NSString*)uri :(NSString*)msg :(NSString*)info :(int)status :(int)userData;

-(int)onIncomingSubscribe:(NSString*)uri;

//-(void)onIncomingCall:(int)call_id;

-(NSObject*)newCall:(int)callId;

-(void)setOnlineStatus:(int)state :(int)activity :(NSString*)note;

-(void)setKeepAlive;
-(void)keepAlive;
-(void)unregistration;

-(void)presNotify;

-(void)setContactParams: (NSString*) params;

-(void)ipChangeDetected;



@end



@interface sipiosCallWrapper : NSObject

- (id)initWith:(sipiosAccountWrapper*)account_wrap uri:(NSString*)uri call_id:(int)call_id;

-(void)calling;

-(void)onCallState:(int)state;
-(void)onMediaState:(int)dir :(int)state;
-(void)onVideoState:(int)dir :(int)state :(UIView*)window;
-(void)onMicState:(int)state;

-(void)hangup;

-(void)onIncomingCall;

-(void)answer;

-(void)ringing;

-(void)toggleMic;
-(void)startVideo;
-(void)stopVideo;
-(void)changeCameraVideo;

-(void)dialDtmf:(NSString*)digits;

-(void)hold;
-(void)unhold;
-(void)reset;

-(bool)isMicOn;
-(bool)isVideoOn;
-(void)setVideoEnabled:(Boolean)isVideo;
-(void)connectAudio;
-(NSString*)getRemoteUri;
-(NSString*)getCallIdString;

-(void)startPreview:(int) x :(int) y :(int) w :(int) h;
-(void)stopPreview;

@end


@interface sipiosBuddyWrapper : NSObject

- (id)initWith:(sipiosAccountWrapper*)account_wrap;

-(void)subscribe: (NSString*)contact;

-(void)onSubscribe:(int)state uri:(NSString*)contact code:(int)code termCode: (int)termCode;

-(void)sendInstantMessage: (NSString*)msg :(int)userData;

-(void)updatePresence;

-(void)getInfo;

@end



@interface sipiosAudPlayerWrapper : NSObject

-(id)init;

-(void)playFile:(NSString*)file;

-(void)stopPlayFile;

-(void)startKPV;

-(void)stopKPV;

-(void)playDigit:(NSString*)digit;

-(void)startHoldTone;

@end


@interface sipiosEndpointWrapper : NSObject

-(id)init;

-(void)onTransportState: (int)state;
-(void)onPreviewVideo: (UIView*)window;
-(void)onStop;

-(void)start;
-(void)stop;
-(void)hangup_all;
-(void)setSndDev:(NSString*) dev;
-(void)startPreview:(int) dev :(int) x :(int) y :(int) w :(int) h;
-(void)stopPreview:(int) dev;
@end

