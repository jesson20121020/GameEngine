//
//  OGLMainWIndow.m
//  client
//
//  Created by jesson on 2021/8/29.
//

#import "OGLMainWindow.h"

static OGLMainWindow* sOGLMainWindow;
@implementation OGLMainWindow
+(OGLMainWindow*)Instance{
    if (nullptr == sOGLMainWindow)
        sOGLMainWindow = [OGLMainWindow alloc];
    return sOGLMainWindow;
}

-(id)initWithContentRect:(NSRect)contentRect styleMask:(NSWindowStyleMask)style backing:(NSBackingStoreType)backingStoreType defer:(BOOL)flag{
    self = [super initWithContentRect:contentRect styleMask:style backing:backingStoreType defer:flag];
    [self setTitle:@"OGLMainWindow"];
    [self makeKeyAndOrderFront:self];
    [self makeMainWindow];
    return self;
}

@end
