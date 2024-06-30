//
//  NSWindow+OGLMainWindow.h
//  client
//
//  Created by jesson on 2021/8/29.
//

#import <Cocoa/Cocoa.h>

NS_ASSUME_NONNULL_BEGIN

@interface OGLMainWindow: NSWindow
+(OGLMainWindow*)Instance;
-(id)initWithContentRect:(NSRect)contentRect styleMask:(NSWindowStyleMask)style backing:(NSBackingStoreType)backingStoreType defer:(BOOL)flag;
@end

NS_ASSUME_NONNULL_END
