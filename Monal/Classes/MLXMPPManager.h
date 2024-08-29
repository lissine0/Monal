//
//  MLXMPPManager.h
//  Monal
//
//  Created by Anurodh Pokharel on 6/27/13.
//
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class xmpp;
@class MLContact;

/**
 A singleton to control all of the active XMPP connections
 */
@interface MLXMPPManager : NSObject
{
	dispatch_source_t _pinger;
}

+(MLXMPPManager*) sharedInstance;

-(BOOL) allAccountsIdle;

#pragma  mark connectivity
/**
 Checks if there are any enabled acconts and connects them if necessary.  
 */
-(void) connectIfNecessary;

/**
 logout all accounts
 */
-(void) reconnectAll;

-(void) disconnectAll;

/**
 disconnects the specified account
 */
-(void) disconnectAccount:(NSNumber*) accountID withExplicitLogout:(BOOL) explicitLogout;

/**
 connects the specified account
 */
-(void) connectAccount:(NSNumber*) accountID;

#pragma mark XMPP commands
/**
 Remove a contact from an account
 */
-(void) removeContact:(MLContact*) contact;

/**
 Add a contact from an account
 */
-(void) addContact:(MLContact*) contact;
-(void) addContact:(MLContact*) contact withPreauthToken:(NSString* _Nullable) preauthToken;

/**
 Block  a jid
 */
-(void) block:(BOOL) isBlocked contact:(MLContact*) contact;
-(void) block:(BOOL) isBlocked fullJid:(NSString*) contact onAccount:(NSNumber*) accountID;

/**
 Returns the user set name of the conencted account
 */
-(NSString*) getAccountNameForConnectedRow:(NSUInteger) row;

/*
 gets the connected account apecified by id. return nil otherwise
 */
-(xmpp* _Nullable) getEnabledAccountForID:(NSNumber*) accountID;

/**
 Returns YES if account is connected
 */
-(BOOL) isAccountForIdConnected:(NSNumber*) accountID;

/**
 When the account estblihsed its current connection. 
 */
-(NSDate *) connectedTimeFor:(NSNumber*) accountID;

-(NSNumber* _Nullable) login:(NSString*) jid password:(NSString*) password;
-(void) removeAccountForAccountID:(NSNumber*) accountID;
-(void) addNewAccountToKeychainAndConnectWithPassword:(NSString*) password andAccountID:(NSNumber*) accountID;

/**
 update the password in the keychan and update memory cache
 */
-(BOOL) isValidPassword:(NSString*) password forAccount:(NSNumber*) accountID;
-(NSString*) getPasswordForAccount:(NSNumber*) accountID;
-(void) updatePassword:(NSString*) password forAccount:(NSNumber*) accountID;

/**
Sends a message to a specified contact in account. Calls completion handler on success or failure.
 */
-(void) sendMessageAndAddToHistory:(NSString*) message havingType:(NSString*) messageType toContact:(MLContact*) contact isEncrypted:(BOOL) encrypted uploadInfo:(NSDictionary* _Nullable) uploadInfo withCompletionHandler:(void (^ _Nullable)(BOOL success, NSString* messageId)) completion;
-(void)sendMessage:(NSString*) message toContact:(MLContact*) contact isEncrypted:(BOOL) encrypted isUpload:(BOOL) isUpload messageId:(NSString*) messageId withCompletionHandler:(void (^ _Nullable)(BOOL success, NSString* messageId)) completion;
-(void) sendChatState:(BOOL) isTyping toContact:(MLContact*) contact;

#pragma mark XMPP settings

@property (nonatomic, strong, readonly) NSMutableArray* connectedXMPP;
@property (nonatomic, readonly) BOOL hasConnectivity;

@property (nonatomic, assign) BOOL hasAPNSToken;
@property (nonatomic, strong) NSString* pushToken;
@property (nonatomic, strong) NSError* _Nullable apnsError;

@property (nonatomic, readonly) BOOL isBackgrounded;
@property (nonatomic, readonly) BOOL isNotInFocus;

@property (nonatomic, readonly) BOOL onMobile;

@property (nonatomic, assign) BOOL isConnectBlocked;

/**
 updates delivery status after message has been sent
 */
-(void) handleSentMessage:(NSNotification*) notification;

-(void) noLongerInFocus;

/**
 updates client state on server as inactive
 */
-(void) nowBackgrounded;

/**
 sets client state on server as active
 */
-(void) nowForegrounded;

/**
 fetch entity software version
 */
-(void) getEntitySoftWareVersionForContact:(MLContact*) contact andResource:(NSString*) resource;

-(void) setPushToken:(NSString* _Nullable) token;
-(void) removeToken;

@end

NS_ASSUME_NONNULL_END
