/*
 * Copyright (c) 2020 Jonathan Schleifer <js@nil.im>
 *
 * https://fl.nil.im/objsqlite3
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
 * OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

#import "SL3PrepareStatementFailedException.h"

@implementation SL3PrepareStatementFailedException
@synthesize SQLStatement = _SQLStatement;

+ (instancetype)exceptionWithConnection: (SL3Connection *)connection
			      errorCode: (int)errorCode
{
	OF_UNRECOGNIZED_SELECTOR
}

+ (instancetype)exceptionWithConnection: (SL3Connection *)connection
			   SQLStatement: (OFConstantString *)SQLStatement
			      errorCode: (int)errorCode
{
	return [[[self alloc] initWithConnection: connection
				    SQLStatement: SQLStatement
				       errorCode: errorCode] autorelease];
}

- (instancetype)initWithConnection: (SL3Connection *)connection
			 errorCode: (int)errorCode
{
	OF_INVALID_INIT_METHOD
}

- (instancetype)initWithConnection: (SL3Connection *)connection
		      SQLStatement: (OFConstantString *)SQLStatement
			 errorCode: (int)errorCode
{
	self = [super initWithConnection: connection
			       errorCode: errorCode];

	@try {
		_SQLStatement = [SQLStatement retain];
	} @catch (id e) {
		[self release];
		@throw e;
	}

	return self;
}

- (void)dealloc
{
	[_SQLStatement release];

	[super dealloc];
}
@end
