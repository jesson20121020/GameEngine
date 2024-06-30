//
//  AppDelegate.m
//  client
//
//  Created by jesson on 2021/1/23.
//

#import "AppDelegate.h"
#include "OGLMainWindow.h"
#include "OGLView.h"

@interface AppDelegate ()


@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    // Insert code here to initialize your application
    NSRect rect = NSMakeRect(0.0f, 0.0f, 1334, 750);
    NSInteger style = NSWindowStyleMaskTitled| NSWindowStyleMaskClosable;
    
    [[OGLMainWindow Instance]initWithContentRect:rect styleMask:style backing:NSBackingStoreBuffered defer:NO];
    [[OGLView Instance]initWithRect:[[[OGLMainWindow Instance] contentView]bounds]];
    [[[OGLMainWindow Instance]contentView]addSubview:[OGLView Instance]];
}


- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}


@end
