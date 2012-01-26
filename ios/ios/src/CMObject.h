//
//  CMObject.h
//  cloudmine-ios
//
//  Copyright (c) 2011 CloudMine, LLC. All rights reserved.
//  See LICENSE file included with SDK for details.
//

#import <Foundation/Foundation.h>
#import "CMSerializable.h"

@class CMUser;
@class CMStore;

/**
 * Extend from this instead of <tt>NSObject</tt> for all model objects in your app that need to be backed
 * by remote storage on CloudMine. Be sure to implement <tt>initWithCoder:</tt> and <tt>encodeWithCoder:</tt>
 * in each of these model classes to define how to serialize and deserialize the object. This behavior follows
 * the standard archiving/unarchiving conventions defined by Apple's <tt>NSCoding</tt> protocol.
 *
 * This will also take care of generating a default <tt>objectId</tt> for you, in the form of a UUID.
 */
@interface CMObject : NSObject <CMSerializable>

/**
 * The app user that owns this object. If this is <tt>nil</tt>, the object is app-level.
 * <b>Changing this is thread-safe.</b>
 *
 * @see isUserLevel
 */
@property (atomic, strong) CMUser *user;

/**
 * The store that the object belongs to. It is possible for this to be <tt>nil</tt>, meaning that the object
 * was created locally and hasn't been saved via a store yet.
 * It is important to note that the object must belong to a store if you need to save it. You can easily
 * add the object to a store and save it by using <tt>CMStore</tt>'s <tt>saveObject:</tt> method.
 *
 * If you manually change the store yourself, this object will automatically remove itself from the old
 * store and add it to the new store. <b>This operation is thread-safe.</b>
 */
@property (nonatomic, weak) CMStore *store;

/**
 * Initializes this app-level object by generating a UUID as the default value for <tt>objectId</tt>.
 */
- (id)init;

/**
 * Initializes this app-level object with the given object ID. Note that this MUST be unique throughout your app.
 */
- (id)initWithObjectId:(NSString *)theObjectId;

/**
 * Initializes this user-level object with the given object ID and <tt>CMUser</tt>. 
 * Note that the object ID MUST be unique throughout your app.
 */
- (id)initWithObjectId:(NSString *)theObjectId user:(CMUser *)theUser;

/**
 * Default behavior does nothing other than call <tt>[self init]</tt>. Override this in your subclasses
 * to define logic for creating an instance of each subclass from a serialized representation.
 *
 * @see CMSerializable
 */
- (id)initWithCoder:(NSCoder *)aDecoder;

/**
 * Default behavior does nothing. Override this in your subclasses to define logic 
 * for serializing instances of each subclass for remote storage.
 *
 * @see CMSerializable
 */
- (void)encodeWithCoder:(NSCoder *)aCoder;

/**
 * @return <tt>true</tt> if this object is owned by a particular user, <tt>false</tt> if app-level.
 */
- (BOOL)isUserLevel;

/**
 * Note: The object must belong to a store if you need to save it. You can easily add the object to a store and
 * save it by using <tt>CMStore</tt>'s <tt>saveObject:</tt> method.
 *
 * @see CMStore
 * @return <tt>true</tt> if this object is belongs to any store.
 */
- (BOOL)belongsToStore;

/**
 * Saves this object to CloudMine using its current store.
 * If this object does not belong to a store, you can easily add the object to a store and
 * save it by using <tt>CMStore</tt>'s <tt>saveObject:</tt> method instead.
 *
 * @see CMStore
 */
- (void)save;

@end
