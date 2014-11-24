//
//  OptionsViewController.h
//  NumMethods
//
//  Created by Andrii Kulian on 12/11/13.
//  Copyright (c) 2013 Andrii Kulian. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "Options.h"

@class OptionsViewController;

@protocol OptionsViewControllerDelegate <NSObject>

-(void)didEndEditing:(Options*)options inViewController:(OptionsViewController*)viewController;

@end

@interface OptionsViewController : UIViewController<UITextFieldDelegate>
@property (strong, nonatomic) IBOutlet UITextField *alphaTextField;
@property (strong, nonatomic) IBOutlet UITextField *deltaTextField;
@property (strong, nonatomic) IBOutlet UITextField *gammaTextField;
@property (strong, nonatomic) IBOutlet UITextField *numberOfPointsTextField;
@property (strong, nonatomic) IBOutlet UITextField *numberOfColorsTextField;
@property (strong, nonatomic) IBOutlet UITextField *realWidthTextField;
@property (strong, nonatomic) IBOutlet UITextField *vWindowSizeTextField;
@property (strong, nonatomic) IBOutlet UILabel *timeLabel;
@property (strong, nonatomic) IBOutlet UISlider *timeSlider;

@property (strong, nonatomic) IBOutlet UISegmentedControl *arctgDipolSegmentedControl;

@property (nonatomic, strong) Options *options;
@property (nonatomic, strong) id<OptionsViewControllerDelegate> delegate;

@end
