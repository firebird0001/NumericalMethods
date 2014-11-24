//
//  PlotView.h
//  NumMethods
//
//  Created by Andrii Kulian on 12/9/13.
//  Copyright (c) 2013 Andrii Kulian. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface PlotView : UIView

@property(nonatomic, strong) UIImageView* xAxis;
@property(nonatomic, strong) UIImageView* yAxis;
@property(nonatomic, strong) UILabel* topLabel;
@property(nonatomic, strong) UILabel* rightLabel;
@property(nonatomic, strong) UILabel* centerLabel;

@end
