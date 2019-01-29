#import "GameViewController.h"
#import <OpenGLES/ES2/glext.h>
//#import "../../TestNet.Shared/SimpleRenderer.h"
#import "SFEngine.h"
#import "TestNetNative.h"

#import <memory>

@interface GameViewController () {}
@property (strong, nonatomic) EAGLContext *context;


- (void)setupGL;
- (void)tearDownGL;

@end

@implementation GameViewController
{
	SharedPointerT<TestNetNative> m_TestNetNative;
    //std::unique_ptr<SimpleRenderer> mCubeRenderer;
}

- (IBAction)OnLoginClicked:(id)sender {

   	m_TestNetNative->CloseAllConnections();

	m_TestNetNative->Connect("192.168.0.2", 21001);

}

- (IBAction)OnRefreshRankingClicked:(id)sender {

	if (m_TestNetNative == nullptr)
		return;

	m_TestNetNative->RequestRanking();
    
}

- (void)viewDidLoad
{
    [super viewDidLoad];

    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];

    if (!self.context) {
        NSLog(@"Failed to create ES context");
    }

    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;

	EngineInitParam initParam;

	Engine::Start(initParam);

	m_TestNetNative = new TestNetNative;


    [self setupGL];
}

- (void)dealloc
{
    [self tearDownGL];

	m_TestNetNative->Dispose();
	m_TestNetNative = nullptr;

	Engine::Stop();


    if ([EAGLContext currentContext] == self.context) {
        [EAGLContext setCurrentContext:nil];
    }
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];

    if ([self isViewLoaded] && ([[self view] window] == nil)) {
        self.view = nil;

        [self tearDownGL];

        if ([EAGLContext currentContext] == self.context) {
            [EAGLContext setCurrentContext:nil];
        }
        self.context = nil;
    }

    // Dispose of any resources that can be recreated.
}

- (BOOL)prefersStatusBarHidden {
    return YES;
}

- (void)setupGL
{
    [EAGLContext setCurrentContext:self.context];

}

- (void)tearDownGL
{
    [EAGLContext setCurrentContext:self.context];

}

#pragma mark - GLKView and GLKViewController delegate methods

extern float _rotation;

- (void)update
{
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
}

@end
