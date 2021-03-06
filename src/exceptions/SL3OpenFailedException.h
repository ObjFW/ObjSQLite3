/*
 * Copyright (c) 2020, Jonathan Schleifer <js@nil.im>
 *
 * https://fossil.nil.im/objsqlite3
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice is present in all copies.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#import "SL3Exception.h"

OF_ASSUME_NONNULL_BEGIN

@interface SL3OpenFailedException: SL3Exception
{
	OFString *_path;
	int _flags;
}

@property (readonly, nonatomic) OFString *path;
@property (readonly, nonatomic) int flags;

+ (instancetype)exceptionWithConnection: (nullable SL3Connection *)connection
			      errorCode: (int)errorCode OF_UNAVAILABLE;
+ (instancetype)exceptionWithPath: (OFString *)path
			    flags: (int)flags
			errorCode: (int)errorCode;
- (instancetype)initWithConnection: (nullable SL3Connection *)connection
			 errorCode: (int)errorCode OF_UNAVAILABLE;
- (instancetype)initWithPath: (OFString *)path
		       flags: (int)flags
		   errorCode: (int)errorCode OF_DESIGNATED_INITIALIZER;
@end

OF_ASSUME_NONNULL_END
