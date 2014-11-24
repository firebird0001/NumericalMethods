//
//  Options.h
//  NumMethods
//
//  Created by Andrii Kulian on 12/9/13.
//  Copyright (c) 2013 Andrii Kulian. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum {
    MODE_PHI,
    MODE_PSI,
    MODE_CP
} mode;

@interface Options : NSObject

@property (nonatomic, assign) double alpha;
@property (nonatomic, assign) double delta;
@property (nonatomic, assign) double gamma_0;
@property (nonatomic, assign) int number_of_points;
@property (nonatomic, assign) int number_of_colors;
@property (nonatomic, assign) mode drawing_mode;
@property (nonatomic, assign) double real_width;
@property (nonatomic, assign) double real_height;
@property (nonatomic, assign) BOOL show_V;
@property (nonatomic, assign) BOOL dipol_presentation;
@property (nonatomic, assign) int isTest;
@property (nonatomic, assign) int time;
@property (nonatomic, assign) int v_window_size;
@property (nonatomic, assign) int value_window_size;

-(Options*)initDefault;

@end
