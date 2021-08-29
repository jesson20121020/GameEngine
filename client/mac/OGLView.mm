//
//  OGLView.m
//  client
//
//  Created by jesson on 2021/8/29.
//

#import "OGLView.h"
#include "Scene.h"


static OGLView* sOGLView;
@implementation OGLView

+(OGLView*)Instance{
    if (nullptr == sOGLView){
        sOGLView = [OGLView alloc];
    }
    return sOGLView;
}

-(void)initWithRect:(CGRect)rect{
    NSOpenGLPixelFormatAttribute pixel_format[] = {
      NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersionLegacy,
    NSOpenGLPFAColorSize, 32,
        NSOpenGLPFADepthSize, 24,
        NSOpenGLPFAStencilSize, 8,
        NSOpenGLPFAAlphaSize, 8,
        NSOpenGLPFAAccelerated,
        0
    };
    NSOpenGLPixelFormat* format = [[NSOpenGLPixelFormat alloc] initWithAttributes:pixel_format];
    [self initWithFrame:rect pixelFormat:format];
    [[self openGLContext] makeCurrentContext];
    // Init OpenGL scene
    Init(rect.size.width, rect.size.height);
}

- (void)drawRect:(NSRect)dirtyRect {
    [super drawRect:dirtyRect];
    // Drawing code here.
    Renderer();
}

@end
