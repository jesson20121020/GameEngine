//
//  OGLView.m
//  client
//
//  Created by jesson on 2021/8/29.
//

#import "OGLView.h"
#include "../Scene.h"
#include "backends/imgui_impl_osx.h"
#include "backends/imgui_impl_opengl3.h"
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include "FileUtils-Mac.h"


static bool g_mousePressed[2] = { false, false };
static float g_mouseCoords[2] {0,0};

static OGLView* sOGLView;
@implementation OGLView

+(OGLView*)Instance{
    if (nullptr == sOGLView){
        sOGLView = [OGLView alloc];
    }
    return sOGLView;
}

-(void) initImGui
{
    // Init imgui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF(FileUtils::getInstance()->getFullFilePath("fonttitle02.ttf").c_str(), 14.0f, nullptr, io.Fonts->GetGlyphRangesChineseSimplifiedCommon());
    ImGui_ImplOSX_Init(self);
    ImGui::StyleColorsDark();
    ImGui_ImplOpenGL3_Init("#version 410");
}

-(void)initWithRect:(CGRect)rect{
    NSOpenGLPixelFormatAttribute pixel_format[] = {
      NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion4_1Core,
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
    
    [NSTimer scheduledTimerWithTimeInterval:0.016f target:self selector:@selector(UpdateScene) userInfo:nil repeats:YES];
    
    NSLog(@"%s", glGetString(GL_VERSION));

    NSURL *appFolder = [[[NSBundle mainBundle] bundleURL] URLByDeletingLastPathComponent];

    FileUtils::getInstance()->addSearchPath("/Users/jesson/Documents/GameEngine/client/res", true);

    
    
    [self initImGui];
    // Init OpenGL scene
    Init(rect.size.width, rect.size.height);
}


-(void)UpdateScene{
    [self setNeedsDisplay:YES];
}


-(void) drawImGui
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplOSX_NewFrame(self);
    if (ImGui::GetCurrentContext()) {
      ImGui::NewFrame();

	  RenderImGui();

      // ImGui::ShowDemoWindow();

      ImGui::Render();
    }
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

-(void) onBeginDraw{
    // begain draw
    glClearColor(0.1f, 0.4f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

-(void) onDraw
{
    Renderer();
    [self drawImGui];
}

-(void) onPostDraw
{
    glFlush();
}


- (void)drawRect:(NSRect)dirtyRect {
    [super drawRect:dirtyRect];
    [self onBeginDraw];
    [self onDraw];
    [self onPostDraw];
}



@end
