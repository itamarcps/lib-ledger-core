// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from http_client.djinni

#import "RCTCoreLGHttpUrlConnection.h"


@implementation RCTCoreLGHttpUrlConnection
//Export module
RCT_EXPORT_MODULE(RCTCoreLGHttpUrlConnection)

-(instancetype)init
{
    self = [super init];
    //Init Objc implementation
    if(self)
    {
        self.objcImpl = [[LGHttpUrlConnectionImpl alloc] init];
    }
    return self;
}

/**
 * Gets the HTTP response status code
 * @return The HTTP response status code
 */
RCT_REMAP_METHOD(getStatusCode,getStatusCodeWithResolver:(RCTPromiseResolveBlock)resolve rejecter:(RCTPromiseRejectBlock)reject) {

    id result = @{@"result" :@([self.objcImpl getStatusCode])};if(result)
    {
        resolve(result);
    }
    else
    {
        reject(@"impl_call_error", @"Error while calling LGHttpUrlConnectionImpl::getStatusCode", nil);
    }
}

/**
 * Gets the HTTP response status text
 * @return The HTTP response status text
 */
RCT_REMAP_METHOD(getStatusText,getStatusTextWithResolver:(RCTPromiseResolveBlock)resolve rejecter:(RCTPromiseRejectBlock)reject) {

    id result = @{@"result" :[self.objcImpl getStatusText]};
    if(result)
    {
        resolve(result);
    }
    else
    {
        reject(@"impl_call_error", @"Error while calling LGHttpUrlConnectionImpl::getStatusText", nil);
    }
}

/**
 * Gets the HTTP response headers
 * @return The HTTP response headers
 */
RCT_REMAP_METHOD(getHeaders,getHeadersWithResolver:(RCTPromiseResolveBlock)resolve rejecter:(RCTPromiseRejectBlock)reject) {

    id result = @{@"result" :[self.objcImpl getHeaders]};
    if(result)
    {
        resolve(result);
    }
    else
    {
        reject(@"impl_call_error", @"Error while calling LGHttpUrlConnectionImpl::getHeaders", nil);
    }
}

/**
 * Reads available HTTP response body. This method will be called multiple times until it returns a empty bytes array.
 * @returns A chunk of the body data wrapped into a HttpReadBodyResult (for error management)
 */
RCT_REMAP_METHOD(readBody,readBodyWithResolver:(RCTPromiseResolveBlock)resolve rejecter:(RCTPromiseRejectBlock)reject) {

    id result = @{@"result" :[self.objcImpl readBody]};
    if(result)
    {
        resolve(result);
    }
    else
    {
        reject(@"impl_call_error", @"Error while calling LGHttpUrlConnectionImpl::readBody", nil);
    }
}
@end