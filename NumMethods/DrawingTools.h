//
//  DrawingTools.h
//  NumMethods
//
//  Created by Andrii Kulian on 12/9/13.
//  Copyright (c) 2013 Andrii Kulian. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "data_types.h"

@interface DrawingTools : NSObject

+(UIImage*)createImageWithSize:(CGSize)size andBackgroundColor:(UIColor*)backgroundColor;
+(UIImage*)createImageWithSize:(CGSize)size andColorNumbers:(int**)colorNumbers andColors:(NSArray*)colors;
+(UIImage *)drawLines:(NSArray*)lines onImage:(UIImage *)inputImage;
+(UIImage *)drawLines:(NSArray*)lines withWidth:(double)width andColor:(UIColor*)color onImage:(UIImage *)inputImage;

+(UIImage *)drawPoints:(NSArray*)points onImage:(UIImage *)inputImage;
+(UIImage *)drawPoints:(NSArray*)points withColor:(UIColor*)color onImage:(UIImage *)inputImage;
+(UIImage *)drawPoints:(point*)points number:(int)point_number withColor:(UIColor*)color onImage:(UIImage *)inputImage;
+(UIImage *)drawPoints:(point*)points number:(int)point_number withWidth:(float)width withColor:(UIColor*)color onImage:(UIImage *)inputImage;
+(UIImage *)drawPoints:(point*)points number:(int)point_number withWidth:(float)width andTypes:(bool*)type onImage:(UIImage *)inputImage;

+(UIImage *)drawConnectedPoints:(point*)points number:(int)point_number withWidth:(double)width andColor:(UIColor*)color onImage:(UIImage*) inputImage;
+(UIImage *)drawVectors:(vect*)vectors number:(int)number withWidth:(double)width andColor:(UIColor*)color onImage:(UIImage *)inputImage;
+(UIImage *)combineImages:(NSArray*)images;
+(UIColor*)colorForValue:(double)value withBottomThreshold:(double)bottomThreshold andTopThreshold:(double)topThreshold;

@end
