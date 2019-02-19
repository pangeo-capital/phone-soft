//
//  sipiosAccount.m
//  SipContact
//
//  Created by Tyurin Andrey on 14/04/16.
//  Copyright © 2016 Tyurin Andrey. All rights reserved.
//

#import "sipiosWrapper.h"
#include <string>
#include <map>
#include <vector>
#include "sipios.hpp"
//#import "KOHTAKT-Swift.h"


@implementation sipiosEndpointWrapper {
    @public
    endpoint_api_ptr_t _api;
}

class sipiosEndpoint : public EndpointDelegate {
    __weak sipiosEndpointWrapper* _wrapper;
public:
    
    sipiosEndpoint(sipiosEndpointWrapper* Wrapper) : _wrapper(Wrapper), EndpointDelegate() {};
    
    
    virtual void onTransportState(int state) {
        dispatch_async(dispatch_get_main_queue(), ^ {
            [_wrapper onTransportState: state];
        });
    }
    virtual void onPreviewVideo(void* window) {
        UIView* wnd = (__bridge UIView*)window;
        dispatch_async(dispatch_get_main_queue(), ^ {
            [_wrapper onPreviewVideo: wnd];
        });
    }
    
    virtual void onStop() {
        dispatch_async(dispatch_get_main_queue(), ^ {
            [_wrapper onStop];
        });
    }
    

};

- (id)init {
    if (self = [super init]) {
        _api = endpoint_api_ptr_t(new sipiosEndpoint(self));
    }
    return self;
}

-(void)start {
    _api->start();
}

-(void)stop {
    _api->hangup_all();
    _api->stop();
}

-(void)hangup_all {
    _api->hangup_all();
}

-(void)setSndDev:(NSString*)dev {
    _api->setSndDev([dev UTF8String]);
}
-(void)startPreview:(int)dev :(int)x :(int)y :(int)w :(int)h {
    _api->previewVideoStart(dev, x, y, w, h);
}
-(void)stopPreview:(int)dev {
    _api->previewVideoStop(dev);
}

@end


@implementation sipiosAccountWrapper {
    @public
    account_api_ptr_t _api;
}

class sipiosAccount: public AccountDelegate {
    __weak sipiosAccountWrapper* _wrapper;
public:

    sipiosAccount(sipiosAccountWrapper* Wrapper) : _wrapper(Wrapper), AccountDelegate() {};
    
    void onRegister(int status) {
        NSLog(@"register status=%d", status);
        dispatch_async(dispatch_get_main_queue(), ^ {
            [_wrapper onRegister:status];
        });
    };
    
    void onUnregister(int status) {
        NSLog(@"unregister status=%d", status);
        dispatch_async(dispatch_get_main_queue(), ^ {
            [_wrapper onUnregister:status];
        });
    };

    //sipiosAccount::onIncomingCall
    void onIncomingCall(int callId) {
        sipiosCallWrapper* call_wrap = (sipiosCallWrapper*)[_wrapper newCall: callId];
        dispatch_async(dispatch_get_main_queue(), ^ {
            [call_wrap onIncomingCall];
        });
    };
    
    int onIncomingSubscribe(const std::string& uri) {
        NSString* nuri = [NSString stringWithUTF8String:uri.c_str()];
        NSLog(@"onIncomingSubscribe = %@", nuri);
        //dispatch_async(dispatch_get_main_queue(), ^ {
            return [_wrapper onIncomingSubscribe:nuri];
        //});
    }
    
    void onInstantMessage(const std::string& fromuri, const std::string& touri, const std::string& msg, const std::string& info) {
        NSString* nfromuri = [NSString stringWithUTF8String:fromuri.c_str()];
        NSString* ntouri = [NSString stringWithUTF8String:touri.c_str()];
        NSString* nmsg = [NSString stringWithUTF8String:msg.c_str()];
        NSString* ninfo = [NSString stringWithUTF8String:info.c_str()];
        dispatch_async(dispatch_get_main_queue(), ^ {
            [_wrapper onInstantMessage:nfromuri :ntouri :nmsg :ninfo];
        });
    };
    
    void onInstantMessageStatus(const std::string& uri, const std::string& msg, const std::string& info, int status, int userData) {
        
        NSString* nuri = [NSString stringWithCString:uri.c_str()
                                            encoding:[NSString defaultCStringEncoding]];
        NSString* nmsg = [NSString stringWithUTF8String:msg.c_str()];
        NSString* ninfo = [NSString stringWithUTF8String:info.c_str()];

        dispatch_async(dispatch_get_main_queue(), ^ {
            [_wrapper onInstantMessageStatus:nuri :nmsg :ninfo :status :userData];
        });
    }

    

};

- (id)init {
    if (self = [super init]) {
        _api = account_api_ptr_t(new sipiosAccount(self));
     }
    return self;
}


-(void)setInfo:(NSString*)user :(NSString*)password :(NSString*)displayName :(NSString*)userAgent :(NSString*)deviceToken {
    _api->setInfo([user UTF8String], [password UTF8String], [displayName UTF8String], [userAgent UTF8String], [deviceToken UTF8String]);
}


-(void) registration:(NSString*)proto :(NSString*)proxy :(NSString*)domain {
    static int ss = 0;
    _api->send_registration([proto UTF8String], [proxy UTF8String], [domain UTF8String]);
}

-(void)onInstantMessage:(NSString*)fromuri :(NSString*)touri :(NSString*)msg {
    
}

-(void)onInstantMessageStatus:(int)status {
    
}

-(int)onIncomingSubscribe:(NSString *)uri {
    return 200;
}

-(void)setOnlineStatus:(int)state :(int)activity :(NSString*)note {
    const char* notec = [note UTF8String];
    _api->setOnlineStatus(state, activity, notec);
}

-(void)setKeepAlive {
    _api->send_reregistration();
}

-(void)keepAlive {
    _api->send_reregistration();
    [NSThread sleepForTimeInterval:5];
    NSLog(@"keep alive");
}

-(void)playFile:(NSString*)file {
    const char* filename = [file UTF8String];
    _api->playFile(filename);
    
}

-(void)unregistration {
    _api->unregistration();
}

-(void)presNotify {
    _api->presNotify();
}


-(void)setContactParams: (NSString*) params {
    const char* value = [params UTF8String];
    _api->setContactParams(value);
}

-(void)ipChangeDetected {
    _api->ipChangeDetected();
}


@end

@implementation sipiosCallWrapper {
    @public call_api_ptr_t _call;
    sipiosAccountWrapper* _account;
    NSString* _arch_uri;
}


class sipiosCall: public CallDelegate {
private:
    __weak sipiosCallWrapper* _parent;
 public:
    
    sipiosCall(sipiosCallWrapper* Wrapper, const std::string& uri, int call_id = -1) : _parent(Wrapper), CallDelegate(Wrapper->_account->_api, uri, call_id) {
        //NSLog(@"sipiosCall");
    };

    ~sipiosCall() {
        //NSLog(@"~sipiosCall");
    }
    
    void onCallState(int state) {
        NSLog(@"onCallProcess:%d", state);
        if (sipiosCallWrapper* p = _parent) {
            dispatch_async(dispatch_get_main_queue(), ^{ [p onCallState:state]; });
        }
        
    }

    void onMediaState(int dir, int state) {
        NSLog(@"onMediaState:dir=%d state=%d", dir, state);
        if (sipiosCallWrapper* p = _parent) {
            dispatch_async(dispatch_get_main_queue(), ^{ [p onMediaState:dir :state]; });
        }
        
    }
    void onVideoState(int dir, int state, void* window) {
        NSLog(@"onMediaState:dir=%d state=%d", dir, state);
        if (sipiosCallWrapper* p = _parent) {
            UIView* wnd = (__bridge UIView*)window;
            dispatch_async(dispatch_get_main_queue(), ^{ [p onVideoState:dir :state :wnd]; });
        }
        
    }
    void onMicState(int state) {
        NSLog(@"onMicState state=%d", state);
        if (sipiosCallWrapper* p = _parent) {
            dispatch_async(dispatch_get_main_queue(), ^{ [p onMicState: state]; });
        }
        
    }
};

- (id)initWith:(sipiosAccountWrapper*)account_wrap uri:(NSString*)uri call_id:(int)call_id {
    _account = account_wrap;
    self->_arch_uri = uri;
    if (_account && (self = [super init])) {
        _call = call_api_ptr_t(new sipiosCall(self, [uri UTF8String], call_id));
        _call->init();
    }
    return self;
}

-(void)calling {
    _call->make_call();
}

//-(void)onCallState:(int)state {
    
//}

-(void)hangup {
    _call->hangup();
}

-(void)answer {
    _call->answer();
}
-(void)ringing {
    _call->ringing();
}
-(void)toggleMic {
    _call->toggleMic();
}
-(void)startVideo {
    _call->startVideo();
}
-(void)stopVideo {
    _call->stopVideo();
}

-(void)changeCameraVideo {
    _call->changeCameraVideo();
}

-(void)dialDtmf:(NSString*)digits {
    const char* f = [digits UTF8String];
    _call->dialDtmf(f);
}

-(void)hold {
    _call->hold();
    
}

-(void)unhold {
    _call->unhold();
}

-(void)reset {
    _call->reset();
}

-(bool)isMicOn {
    return _call->isMicOn();
}
-(bool)isVideoOn {
    return _call->isVideoOn();
}

-(void)setVideoEnabled:(Boolean)isVideo {
    _call->setVideoEnabled(isVideo);
}

-(void)connectAudio {
    _call->connectAudio();
}

-(NSString*)getRemoteUri {
    NSString* nuri = [NSString stringWithUTF8String:_call->getRemoteUri().c_str()];
    return nuri;
}
            
-(NSString*)getCallIdString {
    NSString* nuri = [NSString stringWithUTF8String:_call->getCallIdString().c_str()];
    return nuri;
}

-(void)startPreview:(int) x :(int) y :(int) w :(int) h {
    _call->startPreview(x, y, w, h);
}
-(void)stopPreview {
    _call->stopPreview();
}

@end


@implementation sipiosBuddyWrapper {
@public
    buddy_api_ptr_t _api;
    sipiosAccountWrapper* _account;
}

class sipiosBuddy : public BuddyDelegate {
    __weak sipiosBuddyWrapper* _wrapper;
public:
    
    sipiosBuddy(sipiosBuddyWrapper* wrapper) :
    _wrapper(wrapper),
    BuddyDelegate(wrapper->_account->_api) {
    }
    
    void onBuddyState(int state, const std::string& contact, int code, int termCode) {
        NSString* nuri = [NSString stringWithUTF8String:contact.c_str()];
        dispatch_async(dispatch_get_main_queue(), ^{ [_wrapper onSubscribe:state uri:nuri code: code termCode:termCode]; });
    };
    
    
};

- (id)initWith:(sipiosAccountWrapper*)account_wrap {
    if (self = [super init]) {
        _account = account_wrap;
        _api = buddy_api_ptr_t(new sipiosBuddy(self));
    }
    return self;
}

-(void)subscribe: (NSString*)contact {
    const char* usr = [contact UTF8String];
    _api->subscribe(usr);
}

-(void)updatePresence {
    _api->updatePresense();
}

-(void)getInfo {
    _api->getInfo();
}


-(void)onSubscribe:(int)state uri:(NSString*)contact code:(int)code termCode:(int)termCode {
    
}

-(void)sendInstantMessage:(NSString*)msg : (int)userData{
    const char* message = [msg UTF8String];
    _api->sendInstatMessage(message, userData);
}



@end

@implementation sipiosAudPlayerWrapper {
@public
    audPlayer_api_ptr_t _api;
}

class sipiosAudPlayer : public AudPlayerDelegate {
    __weak sipiosAudPlayerWrapper* _wrapper;
public:
    
    sipiosAudPlayer(sipiosAudPlayerWrapper* wrapper) :
    _wrapper(wrapper), AudPlayerDelegate() {
        
    }
};

- (id)init {
    if ( self = [super init] ) {
        _api = audPlayer_api_ptr_t(new AudPlayerDelegate());
    }
    return self;
}


-(void)playFile:(NSString*)file {
    const char* f = [file UTF8String];
    _api->playFile(f);
    
}

-(void)stopPlayFile {
    _api->stopPlayFile();
}

-(void)startKPV {
    _api->startKPV();
}

-(void)stopKPV {
    _api->stopKPV();
}

-(void)playDigit:(NSString*)digit {
    const char* f = [digit UTF8String];
    _api->playDigit(f);
}

-(void)startHoldTone {
    _api->startHoldTone();
}

@end






