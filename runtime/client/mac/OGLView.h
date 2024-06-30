//
//  OGLView.h
//  client
//
//  Created by jesson on 2021/8/29.
//

#import <Cocoa/Cocoa.h>

NS_ASSUME_NONNULL_BEGIN

@interface OGLView : NSOpenGLView
+(OGLView*)Instance;
-(void)initWithRect:(CGRect)rect;
-(void)drawRect:(NSRect)dirtyRect;
@end

NS_ASSUME_NONNULL_END
