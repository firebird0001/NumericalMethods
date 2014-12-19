//
//  TraceCallback.h
//  NumMethods
//
//  Created by Andrii Kulian on 12/9/14.
//  Copyright (c) 2014 Andrii Kulian. All rights reserved.
//

#ifndef NumMethods_TraceCallback_h
#define NumMethods_TraceCallback_h

// This is the C "trampoline" function that will be used
// to invoke a specific Objective-C method FROM C++
bool drawCurrentTrace(void *slf, int time);

#endif
