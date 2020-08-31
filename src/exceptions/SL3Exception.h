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

#import <ObjFW/ObjFW.h>

#import "SL3Connection.h"

OF_ASSUME_NONNULL_BEGIN

@interface SL3Exception: OFException
{
	SL3Connection *_connection;
	int _errorCode;
}

@property OF_NULLABLE_PROPERTY (readonly, nonatomic) SL3Connection *connection;
@property (readonly, nonatomic) int errorCode;

+ (instancetype)exception OF_UNAVAILABLE;
+ (instancetype)exceptionWithConnection: (nullable SL3Connection *)connection
			      errorCode: (int)errorCode;
- (instancetype)init OF_UNAVAILABLE;
- (instancetype)initWithConnection: (nullable SL3Connection *)connection
			 errorCode: (int)errorCode OF_DESIGNATED_INITIALIZER;
@end

OF_ASSUME_NONNULL_END
