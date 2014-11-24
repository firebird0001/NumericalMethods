//
//  DrawingViewController.h
//  NumMethods
//
//  Created by Andrii Kulian on 12/2/13.
//  Copyright (c) 2013 Andrii Kulian. All rights reserved.
//

#import <UIKit/UIKit.h>

@class DrawingViewController;

@protocol DrawingViewControllerDelegate <NSObject>

-(void)didDrawPoints:(NSArray*)points withRipPointNumbers:(NSArray*)ripPointNumbers inViewController:(DrawingViewController*)viewController;
-(void)didCancelDrawingViewController:(DrawingViewController*)viewController;

@end

@interface DrawingViewController : UIViewController<UINavigationControllerDelegate>

@property (strong, nonatomic) IBOutlet UIImageView *drawImageView;
@property (strong, nonatomic) IBOutlet UIImageView *tempDrawImage;
@property (strong, nonatomic) IBOutlet UIButton *clearButton;
@property (strong, nonatomic) IBOutlet UIButton *proceedButton;
@property (strong, nonatomic) IBOutlet UIButton *ripButton;

@property (strong, nonatomic) id delegate;

-(IBAction)clear:(id)sender;
-(IBAction)rip_point:(id)sender;
-(IBAction)proceed:(id)sender;

@end
