//
//  ViewController.m
//  TestNet.IOS
//
//  Created by KyungKun Ko on 7/16/17.
//  Copyright © 2017 KyungKun Ko. All rights reserved.
//

#import "ViewController.h"
#import "../../TestNet.Shared/TestNetNative.h"
#import "SFEngine.h"


@interface ViewController ()

@end

@implementation ViewController
{
    SF::SharedPointerT<TestNetNative> m_TestNetNative;
    //std::unique_ptr<SimpleRenderer> mCubeRenderer;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    SF::EngineInitParam initParam;
    
    SF::Engine::Start(initParam);
    
    m_TestNetNative = new(SF::GetSystemMemoryManager()) TestNetNative;
    m_TestNetNative->SetTickFlags((uint32_t)SF::EngineTaskTick::SyncPostTick);
}

- (void)dealloc
{
    m_TestNetNative->Dispose();
    m_TestNetNative = nullptr;
    
    SF::Engine::Stop();
}

- (IBAction)OnLoginClicked:(id)sender {
    m_TestNetNative->CloseAllConnections();
    
    m_TestNetNative->Connect("192.168.0.2", 21001);
}

- (IBAction)OnRefreshClicked:(id)sender {
    if (m_TestNetNative == nullptr)
        return;
    
    m_TestNetNative->RequestRanking();
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
