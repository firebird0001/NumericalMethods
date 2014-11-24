//
//  KFImageZoomView.h
//  NumMethods
//
//  Created by Andrii Kulian on 12/10/13.
//  Copyright (c) 2013 Andrii Kulian. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface KFImageZoomView : UIScrollView <UIScrollViewDelegate> {
    UIImageView *imageView;
}

@property (nonatomic, retain)   UIImageView     *imageView;

#pragma mark Initialisation
- (id)initWithImageNamed:(NSString *)imageName atLocation:(CGPoint)location;
- (id)initWithImage:(UIImage *)image atLocation:(CGPoint)location;

@end
