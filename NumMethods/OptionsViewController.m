//
//  OptionsViewController.m
//  NumMethods
//
//  Created by Andrii Kulian on 12/11/13.
//  Copyright (c) 2013 Andrii Kulian. All rights reserved.
//

#import "OptionsViewController.h"

@interface OptionsViewController ()

@end

@implementation OptionsViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [self.alphaTextField setText:[NSString stringWithFormat:@"%d", (int)self.options.alpha]];
    [self.deltaTextField setText:[NSString stringWithFormat:@"%.2f", self.options.delta]];
    [self.gammaTextField setText:[NSString stringWithFormat:@"%.2f", self.options.gamma_0]];
    [self.numberOfPointsTextField setText:[NSString stringWithFormat:@"%d", self.options.number_of_points]];
    [self.numberOfColorsTextField setText:[NSString stringWithFormat:@"%d", self.options.number_of_colors]];
    [self.realWidthTextField setText:[NSString stringWithFormat:@"%f", self.options.real_width]];
    [self.vWindowSizeTextField setText:[NSString stringWithFormat:@"%d", self.options.v_window_size]];
    [self.timeSlider setValue:self.options.time];
    [self.timeLabel setText:[NSString stringWithFormat:@"Час: %d", self.options.time]];
    [self.arctgDipolSegmentedControl setSelectedSegmentIndex:(self.options.dipol_presentation ? 1 : 0)];
    
    [self.timeSlider addTarget:self action:@selector(sliderValueChanged:) forControlEvents:UIControlEventValueChanged];
    
    [self.alphaTextField setDelegate:self];
    [self.deltaTextField setDelegate:self];
    [self.gammaTextField setDelegate:self];
    [self.numberOfPointsTextField setDelegate:self];
    [self.numberOfColorsTextField setDelegate:self];
    [self.realWidthTextField setDelegate:self];
    
    UITapGestureRecognizer *tap = [[UITapGestureRecognizer alloc]
                                   initWithTarget:self
                                   action:@selector(dismissKeyboard)];
    
    [self.view addGestureRecognizer:tap];
    
    UIBarButtonItem *backButton = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemDone target:self action:@selector(finish)];
    self.navigationItem.leftBarButtonItem = backButton;
    
    [self.navigationController.navigationBar setTranslucent:NO];
    if ([self respondsToSelector:@selector(edgesForExtendedLayout)])
        self.edgesForExtendedLayout = UIRectEdgeNone;   // iOS 7 specific
}

- (IBAction)sliderValueChanged:(UISlider *)sender {
    self.options.time = (int)[sender value];
    [self.timeLabel setText:[NSString stringWithFormat:@"Час: %d", self.options.time]];
}

-(void)dismissKeyboard {
    [self.alphaTextField resignFirstResponder];
    [self.deltaTextField resignFirstResponder];
    [self.gammaTextField resignFirstResponder];
    [self.numberOfPointsTextField resignFirstResponder];
    [self.numberOfColorsTextField resignFirstResponder];
    [self.realWidthTextField resignFirstResponder];
}

-(void)textFieldDidEndEditing:(UITextField *)textField {
    [self dismissKeyboard];
}

-(void)finish {
    self.options.alpha = [self.alphaTextField.text doubleValue];
    self.options.delta = [self.deltaTextField.text doubleValue];
    self.options.gamma_0 = [self.gammaTextField.text doubleValue];
    self.options.number_of_points = [self.numberOfPointsTextField.text intValue];
    self.options.number_of_colors = [self.numberOfColorsTextField.text intValue];
    self.options.real_width = [self.realWidthTextField.text doubleValue];
    self.options.v_window_size = [self.vWindowSizeTextField.text intValue];
    self.options.time = (int)[self.timeSlider value];
    self.options.dipol_presentation = (self.arctgDipolSegmentedControl.selectedSegmentIndex == 1);

    if (self.delegate) {
        [self.delegate didEndEditing:self.options inViewController:self];
    }
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
