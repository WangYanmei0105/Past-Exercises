//
//  ViewController.m
//  SimpleGUI
//
//  Created by Amy Wang on 2020/2/24.
//  Copyright © 2020 Amy Wang. All rights reserved.
//

#import "ViewController.h"

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    // Do any additional setup after loading the view.
}


- (void)setRepresentedObject:(id)representedObject {
    [super setRepresentedObject:representedObject];

    // Update the view, if already loaded.
}

- (IBAction)Login:(id)sender {
    NSString * pstrUser = _edtUser.stringValue;
    NSString * pstrPwd = _edtPwd.stringValue;
    if([pstrUser isEqualToString:@"123"]){
        if([pstrPwd isEqualToString:@"000"]){
            NSLog(@"登录成功");
        }
        else{
            NSLog(@"密码错误");
        }
    }
    else{
        NSLog(@"用户名错误");
    }
    
}

@end
