//
//  SSManagedObject.h
//  SSDataKit
//
//  Created by Sam Soffes on 10/23/11.
//  Copyright (c) 2011-2013 Sam Soffes. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreData/CoreData.h>

@interface SSManagedObject : NSManagedObject <NSCoding>

#pragma mark - Accessing the application contexts

/**
 Created as the "root" managed object context. This context has no parent
 and instead has the `persistentStoreCoordinator` set. Use this to perform
 any background processing in your Core Data stack. Make sure to pull data into
 descendant contexts if you save directly here.

 Changes saved to any direct descendants of this context are automatically
 pulled up and saved to the persistent store.
 */
+ (NSManagedObjectContext *)privateQueueContext;
+ (BOOL)hasPrivateQueueContext;

/**
Created as a child of the `privateQueueContext`. Use this context on the main
thread or to update your interface.

Changes saved here are automatically reflected in the `privateQueueContext`.
 */
+ (NSManagedObjectContext *)mainQueueContext;
+ (BOOL)hasMainQueueContext;


/**
 Synonymous with the `mainQueueContext` methods.
 */
+ (NSManagedObjectContext *)mainContext DEPRECATED_ATTRIBUTE;
+ (BOOL)hasMainContext DEPRECATED_ATTRIBUTE;


#pragma mark - Configuring the Persistent Store

/**
 Helpers for handling default store configuration parameters. Override these
 to return other default settings, or call
 `setPersistentStoreOptions:type:URL:forConfiguration:` passing nil for
 configuration.
 
 The provided implementations are best suited for SQLite store types.
 */
+ (NSURL *)defaultPersistentStoreURL;
+ (NSDictionary *)defaultPersistentStoreOptions;
+ (NSString *)defaultPersistentStoreType;

/**
 Set the options, type, and location for the store with the given configuration.
 The behavior of this method and its parameters mirror those seen on 
 `+ [NSPersistentStoreCoordinator addPersistentStoreWithType:configuration:URL:options:error:&error]`.
 
 The only required paramter here is type. If configuration is nil, no other
 configurations may be specified. Once a non-nil configuration is specified,
 the default nil configuration is removed.
 */
+ (void)setPersistentStoreOptions:(NSDictionary *)options
							 type:(NSString *)type
							  URL:(NSURL *)URL
				 forConfiguration:(NSString *)configuration;

/**
 Removes the store definition with the given configuration. Pass nil to remove
 the default store definition. Note that this does not unload the given store.
 */
+ (void)removeStoreDefinitionForConfiguration:(NSString *)configuration;

/**
 Set and get the managed object model. Loaded when creating the persistent
 store coordinator.
 */
+ (NSManagedObjectModel *)managedObjectModel;
+ (void)setManagedObjectModel:(NSManagedObjectModel *)model;

/**
 Returns the persistent coordinator. If none exists, one is created and all
 persisten store configurations are loaded.
 */
+ (NSPersistentStoreCoordinator *)persistentStoreCoordinator;


#pragma mark - Resetting the Presistent Store

+ (void)resetPersistentStore;

/**
 By default, this is NO. If you set this to YES, it will automatically delete the persistent store file and make a new
 one if it fails to initialize (i.e. you failed to add a migration). This is super handy for development. You must set
 this before calling `persistentStoreCoordinator` or anything that calls it like `mainContext`.
 */
+ (void)setAutomaticallyResetsPersistentStore:(BOOL)automaticallyReset;
+ (BOOL)automaticallyResetsPersistentStore;


#pragma mark -  Getting Entity Information

+ (NSString *)entityName;
+ (NSEntityDescription *)entity;
+ (NSEntityDescription *)entityWithContext:(NSManagedObjectContext *)context;
+ (NSArray *)defaultSortDescriptors;


#pragma mark -  Initializing

- (id)initWithContext:(NSManagedObjectContext *)context;


#pragma mark - Object ID resolution

- (NSManagedObjectID *)permanentObjectID;


#pragma mark -  Reflection

- (NSArray *)attributeKeys;
- (NSArray *)persistedAttributeKeys;
- (NSArray *)transientAttributeKeys;
- (NSArray *)relationshipKeys;
- (NSRelationshipDescription *)relationshipForKeyPath:(NSString *)keyPath;


#pragma mark -  Manipulation

- (void)save;
- (void)delete;


@end