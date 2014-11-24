//
//  KFImageZoomView.m
//  NumMethods
//
//  Created by Andrii Kulian on 12/10/13.
//  Copyright (c) 2013 Andrii Kulian. All rights reserved.
//

#import "KFImageZoomView.h"

@implementation KFImageZoomView

@synthesize imageView;

#pragma mark - Initialisation

- (id)initWithImageNamed:(NSString *)imageName atLocation:(CGPoint)location {
    self = [super init];
    if (self) {
        // Need to set delegate in other classes
        
        // Create our image view using the passed in image name
        self.imageView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:imageName]];
        
        // Update the ImageZoom frame to match the dimensions of passed in image
        self.frame = CGRectMake(location.x, location.y,
                                self.imageView.frame.size.width, self.imageView.frame.size.height);
        
        // Set a default minimum and maximum zoom scale
        self.minimumZoomScale = 0.01f;
        self.maximumZoomScale = 10.0f;
        
        // Add image view as a subview
        [self addSubview:self.imageView];
    }
    
    return self;
}

- (id)initWithImage:(UIImage *)image atLocation:(CGPoint)location {
    self = [super init];
    if (self) {
        // Assign the delegate
        self.delegate = self;
        
        // Create our image view using the passed in image name
        self.imageView = [[UIImageView alloc] initWithImage:image];
        
        // Update the ImageZoom frame to match the dimensions of passed in image
        self.frame = CGRectMake(location.x, location.y,
                                self.imageView.frame.size.width, self.imageView.frame.size.height);
        
        // Set a default minimum and maximum zoom scale
        self.minimumZoomScale = 0.5f;
        self.maximumZoomScale = 4.0f;
        
        // Add image view as a subview
        [self addSubview:self.imageView];
    }
    
    return self;
}


@end
