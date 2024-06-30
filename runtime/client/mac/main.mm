//
//  main.m
//  client
//
//  Created by jesson on 2021/1/23.
//

#import <Cocoa/Cocoa.h>
#include "AppDelegate.h"

int main(int argc, const char * argv[]) {
    NSApplication* app = [NSApplication sharedApplication];
    [app setDelegate: [[AppDelegate alloc]init]];
    [NSApp run];
    return 0;
}
