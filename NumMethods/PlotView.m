//
//  PlotView.m
//  NumMethods
//
//  Created by Andrii Kulian on 12/9/13.
//  Copyright (c) 2013 Andrii Kulian. All rights reserved.
//

#import "PlotView.h"

const float LABEL_WIDTH = 100;
const float LABEL_HEIGHT = 40;
const float LABEL_PADDING = 3;

@implementation PlotView

- (id)init
{
    self = [super init];
    if (self) {
        [self initLabels];
    }
    return self;
}

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        [self initLabels];
    }
    return self;
}

-(void)initLabels {
    self.topLabel = [[UILabel alloc] init];
    [self.topLabel setTextColor:[UIColor whiteColor]];
    [self.topLabel setTextAlignment:NSTextAlignmentLeft];
    [self.topLabel setBackgroundColor:[UIColor clearColor]];
    self.centerLabel = [[UILabel alloc] init];
    [self.centerLabel setTextColor:[UIColor whiteColor]];
    [self.centerLabel setTextAlignment:NSTextAlignmentLeft];
    [self.centerLabel setBackgroundColor:[UIColor clearColor]];
    self.rightLabel = [[UILabel alloc] init];
    [self.rightLabel setTextColor:[UIColor whiteColor]];
    [self.rightLabel setTextAlignment:NSTextAlignmentRight];
    [self.rightLabel setBackgroundColor:[UIColor clearColor]];
}

// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
}

-(void)layoutSubviews {
    if (!self.topLabel || !self.rightLabel || !self.centerLabel) {
        return;
    }
    [self.topLabel removeFromSuperview];
    [self.centerLabel removeFromSuperview];
    [self.rightLabel removeFromSuperview];
    
    self.topLabel.frame = CGRectMake(LABEL_PADDING, LABEL_PADDING, LABEL_WIDTH, LABEL_HEIGHT);
    self.centerLabel.frame = CGRectMake(LABEL_PADDING, self.frame.size.height - LABEL_PADDING - LABEL_HEIGHT, LABEL_WIDTH, LABEL_HEIGHT);
    self.rightLabel.frame = CGRectMake(self.frame.size.width - LABEL_PADDING - LABEL_WIDTH, self.frame.size.height - LABEL_PADDING - LABEL_HEIGHT, LABEL_WIDTH, LABEL_HEIGHT);
    
    [self addSubview:self.topLabel];
    [self addSubview:self.centerLabel];
    [self addSubview:self.rightLabel];
}

@end
