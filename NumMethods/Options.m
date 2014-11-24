//
//  Options.m
//  NumMethods
//
//  Created by Andrii Kulian on 12/9/13.
//  Copyright (c) 2013 Andrii Kulian. All rights reserved.
//

#import "Options.h"

@implementation Options

-(Options*)initDefault {
    self = [super init];

    self.alpha = 0;
    self.delta = 0.034173567;
    self.gamma_0 = 0.1;
    self.number_of_points = 30;
    self.number_of_colors = 20;
    self.drawing_mode = MODE_PHI;
    self.show_V = YES;
    self.real_width = 3.;
    self.real_height = 8;
    self.dipol_presentation = YES;
    self.isTest = 0;
    self.time = 12;
    self.v_window_size = 30;
    self.value_window_size = 16;
    
    
    return self;
}

@end
