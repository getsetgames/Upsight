//
//  UpsightLoggerLevel.h
//  UpsightLogger
//
//  Created by Tolik Shevchenko on 3/18/15.
//  Copyright (c) 2015 Upsight. All rights reserved.
//

/** Every log message has an associated severity level. The log reporter uses the level to determine which messages should be displayed in the output window.
 You set the reporter's level with the defaultLogLevel: method of <UpsightLogger>. Any message with a level equal to or more severe than the setting is displayed. The log levels described below are ordered from most to least severe.
 */
typedef NS_ENUM(NSInteger, UpsightLoggerLevel)
{
    /// Used to disable logging
    UpsightLoggerLevelOff = -1,
    
    /// Critical errors indicating the state when the system cannot continue to work, for example the data store cannot build core data stack
    UpsightLoggerLevelCritical,
    
    /// Used to indicate errors during normal workflow, for example a storable object cannot be created with the given parameters.
    UpsightLoggerLevelError,
    
    /// Used to indicate issues that might need attention, such as network failures, dead data store observers, etc.
    UpsightLoggerLevelWarning,
    
    /// Used to indicate information that might be of interest in a particular workflow, for example an operation is complete or failed for some well-known reason, no network connection, etc.
    UpsightLoggerLevelInfo,
    
    /// Used to indicate information that might help to clarify the overall state of the system, data workflow, etc.
    UpsightLoggerLevelDebug,
};
