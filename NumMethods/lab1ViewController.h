//
//  lab1ViewController.h
//  NumMethods
//
//  Created by Andrii Kulian on 9/10/13.
//  Copyright (c) 2013 Andrii Kulian. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "DrawingViewController.h"
#import "OptionsViewController.h"
#import "Options.h"
#import "KFImageZoomView.h"
#import "PlotView.h"
#import "WEPopoverController.h"
#import "WEPopoverContentViewController.h"

@interface lab1ViewController : UIViewController<UITextFieldDelegate, DrawingViewControllerDelegate, OptionsViewControllerDelegate, UIScrollViewDelegate, UINavigationControllerDelegate, WEPopoverControllerDelegate, UIPopoverControllerDelegate> {
	NSInteger currentPopoverCellIndex;
	Class popoverClass;
}
@property (strong, nonatomic) IBOutlet UILabel *statusLabel;
@property (strong, nonatomic) IBOutlet UITextField *pointNumberTextField;
@property (strong, nonatomic) IBOutlet UIImageView *imageView;
@property (strong, nonatomic) KFImageZoomView *imageScrollView;
@property (strong, nonatomic) PlotView *axisView;
@property (strong, nonatomic) IBOutlet UISegmentedControl *modeControl;

@property (strong, nonatomic) NSArray* points;
@property (strong, nonatomic) Options* options;

@property (strong, nonatomic) UIImage* resultImage;
@property (assign, nonatomic) BOOL isPausedByUser;

@property (nonatomic, retain) WEPopoverController *w_popoverController;

- (IBAction)showPopover:(id)sender;
@property (strong, nonatomic) IBOutlet UIButton *stopButton;
- (IBAction)stop:(id)sender;

@end
