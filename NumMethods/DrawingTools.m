//
//  DrawingTools.m
//  NumMethods
//
//  Created by Andrii Kulian on 12/9/13.
//  Copyright (c) 2013 Andrii Kulian. All rights reserved.
//

#import "DrawingTools.h"
#import "Pair.h"

@implementation DrawingTools

+(UIImage*)createImageWithSize:(CGSize)size andBackgroundColor:(UIColor*)backgroundColor {
    UIGraphicsBeginImageContext(size);
    CGContextRef context = UIGraphicsGetCurrentContext();

    CGContextSetFillColorWithColor(context, [backgroundColor CGColor]);

    CGContextFillRect(context, CGRectMake(0.0f, 0.0f, size.width, size.height));
    CGContextStrokePath(context);

    UIImage* result = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();

    return result;
}

+(UIImage*)createImageWithSize:(CGSize)size andColorNumbers:(int**)colorNumbers andColors:(NSArray*)colors {
    UIGraphicsBeginImageContext(size);
    CGContextRef context = UIGraphicsGetCurrentContext();
    
    CGContextSetFillColorWithColor(context, [[UIColor yellowColor] CGColor]);
    CGContextFillRect(context, CGRectMake(0.0f, 0.0f, size.width, size.height));
    
    for (int i = 0; i < size.height; i++) {
        for (int j = 0; j < size.width; j++) {
            CGContextSetFillColorWithColor(context, [[colors objectAtIndex:colorNumbers[i][j]] CGColor]);
            CGContextFillRect(context, CGRectMake(j, i, 1.0f, 1.0f));
        }
    }

    CGContextStrokePath(context);

    UIImage* result = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();

    return result;
}

+(UIImage *)drawLines:(NSArray*)lines onImage:(UIImage *)inputImage {
    return [self drawLines:lines withWidth:3.0f andColor:[UIColor blackColor] onImage:inputImage];
}

+(UIImage *)drawLines:(NSArray*)lines withWidth:(double)width andColor:(UIColor*)color onImage:(UIImage *)inputImage {
    UIGraphicsBeginImageContext(inputImage.size);
    [inputImage drawInRect:CGRectMake(0, 0, inputImage.size.width, inputImage.size.height)];
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGContextSetStrokeColorWithColor(context, [color CGColor]);
    CGContextSetLineWidth(context, width);
    // Drawing code using above context goes here
    for (Pair* pair in lines) {
        CGContextMoveToPoint(context, [pair.first CGPointValue].x, [pair.first CGPointValue].y);
        CGContextAddLineToPoint(context, [pair.second CGPointValue].x, [pair.second CGPointValue].x);
    }
    CGContextStrokePath(context);

    UIImage *outputImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return outputImage;
}

+(UIImage *)drawPoints:(NSArray*)points onImage:(UIImage *)inputImage {
    return [self drawPoints:points withColor:[UIColor blackColor] onImage:inputImage];
}

+(UIImage *)drawPoints:(NSArray*)points withColor:(UIColor*)color onImage:(UIImage *)inputImage {
    UIGraphicsBeginImageContext(inputImage.size);
    [inputImage drawInRect:CGRectMake(0, 0, inputImage.size.width, inputImage.size.height)];
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGContextSetStrokeColorWithColor(context, [color CGColor]);
    CGContextSetLineWidth(context, 1.0f);
    // Drawing code using above context goes here
    for (NSValue* point in points) {
        CGContextMoveToPoint(context, [point CGPointValue].x, [point CGPointValue].y);
        CGContextAddLineToPoint(context, [point CGPointValue].x, [point CGPointValue].y);
    }
    CGContextStrokePath(context);

    UIImage *outputImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return outputImage;
}

+(UIImage *)drawPoints:(point*)points number:(int)point_number withColor:(UIColor*)color onImage:(UIImage *)inputImage {
    return [self drawPoints:points number: point_number withWidth:2 withColor:color onImage:inputImage];
}

+(UIImage *)drawPoints:(point*)points number:(int)point_number withWidth:(float)width withColor:(UIColor*)color onImage:(UIImage *)inputImage {
    UIGraphicsBeginImageContext(inputImage.size);
    [inputImage drawInRect:CGRectMake(0, 0, inputImage.size.width, inputImage.size.height)];
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGContextSetStrokeColorWithColor(context, [color CGColor]);
    CGContextSetLineWidth(context, width);
    // Drawing code using above context goes here
    for (int i = 0; i < point_number; i++) {
        //CGContextMoveToPoint(context, [point CGPointValue].x - width / 2, [point CGPointValue].y - width / 2);
        CGContextAddRect(context, CGRectMake(points[i].x - width / 2, points[i].y - width / 2, width, width));
    }
    CGContextStrokePath(context);
    
    UIImage *outputImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return outputImage;
}

+(UIImage *)drawConnectedPoints:(point*)points number:(int)point_number withWidth:(double)width andColor:(UIColor*)color onImage:(UIImage*) inputImage {
    UIGraphicsBeginImageContext(inputImage.size);
    [inputImage drawAtPoint:CGPointMake(0, 0)];
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGContextSetStrokeColorWithColor(context, [color CGColor]);
    CGContextSetLineWidth(context, width);
    // Drawing code using above context goes here
    for (int i = 0; i < point_number-1; i++) {
        CGContextMoveToPoint(context, points[i].x, points[i].y);
        CGContextAddLineToPoint(context, points[i+1].x, points[i+1].y);
    }
    CGContextStrokePath(context);
    
    UIImage *outputImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return outputImage;
}

+(UIImage *)drawVectors:(vect*)vectors number:(int)number withWidth:(double)width andColor:(UIColor*)color onImage:(UIImage *)inputImage {
    UIGraphicsBeginImageContext(inputImage.size);
    [inputImage drawInRect:CGRectMake(0, 0, inputImage.size.width, inputImage.size.height)];
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGContextSetStrokeColorWithColor(context, [color CGColor]);
    CGContextSetLineWidth(context, width);
    // Drawing code using above context goes here
    // drawing axis are in different direction
    for (int i = 0; i < number; i++) {
        CGContextMoveToPoint(context, vectors[i].start.x, vectors[i].start.y);
        CGContextAddLineToPoint(context, vectors[i].finish.x, vectors[i].finish.y);
    }
    CGContextStrokePath(context);
    
    UIImage *outputImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return outputImage;
}

+(UIImage *)combineImages:(NSArray*)images {
    CGSize totalSize;
    totalSize.width = ((UIImage*)[images objectAtIndex:0]).size.width;
    totalSize.height = 0;
    for (int i = 0; i < images.count; i++) {
        totalSize.height += ((UIImage*)[images objectAtIndex:0]).size.height;
    }
    
    float currentY = 0;
    
    UIGraphicsBeginImageContext(totalSize);
    for (int i = 0; i < images.count; i++) {
        [[images objectAtIndex:i] drawInRect:CGRectMake(0, currentY, ((UIImage*)[images objectAtIndex:i]).size.width, ((UIImage*)[images objectAtIndex:i]).size.height)];
        currentY += ((UIImage*)[images objectAtIndex:i]).size.height;
    }
    UIImage *outputImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    
    return outputImage;
}

+(UIColor*)colorForValue:(double)value withBottomThreshold:(double)bottomThreshold andTopThreshold:(double)topThreshold {
    double t = (value - bottomThreshold) / (topThreshold - bottomThreshold);
    
    // Clamp t to the range [0 ... 1].
    t = MAX(0.0, MIN(t, 1.0));

    double kBottomR = 10;
    double kTopR = 255;
    double kBottomG = 0;
    double kTopG = 0;
    double kBottomB = 10;
    double kTopB = 255;
    
    double r = kBottomR + t * (kTopR - kBottomR);
    double g = kBottomG + t * (kTopG - kBottomG);
    double b = kBottomB + t * (kTopB - kBottomB);
    
    return [UIColor colorWithRed:r/255 green:g/255 blue:b/255 alpha:1];
}

@end
