//
//  CMStore.h
//  cloudmine-ios
//
//  Copyright (c) 2011 CloudMine, LLC. All rights reserved.
//  See LICENSE file included with SDK for details.
//

/** @file */

#import <Foundation/Foundation.h>
#import "CMWebService.h"

/**
 * Callback block signature for all operations on <tt>CMStore</tt> that fetch objects
 * from the CloudMine servers. These block should return <tt>void</tt> and take an
 * <tt>NSArray</tt> of objects as an argument.
 */
typedef void (^CMStoreObjectCallback)(NSArray *objects);

/**
 * This is the high-level interface for interacting with remote objects stored on CloudMine.
 * Note that all the methods here that involve network operations are asynchronous to avoid blocking
 * your app's UI thread. Synchronous versions will come eventually for cases where you are managing a 
 * number of threads and can guarantee that blocking network operations will execute on a background thread.
 *
 * All of the async methods in this class take a callback of type <tt>CMStoreObjectCallback</tt> that will
 * be called with all the object instances once they are finished downloading and inflating.
 */
@interface CMStore : NSObject

/** The <tt>CMWebService</tt> instance that backs this store */
@property (nonatomic, strong) CMWebService *webService;

/**
 * Convenience method to return a newly initialized CMStore instance.
 * Note that, like when using <tt>init</tt>, you must have already initialized the
 * <tt>CMAPICredentials</tt> singleton with your app identifier and secret key.
 *
 * @see CMAPICredentials
 */
+ (CMStore *)store;

/**
 * Default constructor. Note that you must have already initialized the
 * <tt>CMAPICredentials</tt> singleton with your app identifier and secret key.
 *
 * @see CMAPICredentials
 */
- (id)init;

- (void)allObjects:(CMStoreObjectCallback)callback;

- (void)allObjectsOfType:(NSString *)type callback:(CMStoreObjectCallback)callback;

@end