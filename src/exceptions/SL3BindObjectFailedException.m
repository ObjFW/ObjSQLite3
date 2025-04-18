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

#import "SL3BindObjectFailedException.h"

@implementation SL3BindObjectFailedException
@synthesize object = _object, column = _column, statement = _statement;

+ (instancetype)exceptionWithConnection: (SL3Connection *)connection
			      errorCode: (int)errorCode
{
	OF_UNRECOGNIZED_SELECTOR
}

+ (instancetype)exceptionWithObject: (id)object
			     column: (int)column
			  statement: (SL3PreparedStatement *)statement
			  errorCode: (int)errorCode
{
	return objc_autoreleaseReturnValue(
	    [[self alloc] initWithObject: object
				  column: column
			       statement: statement
			       errorCode: errorCode]);
}

- (instancetype)initWithConnection: (SL3Connection *)connection
			 errorCode: (int)errorCode
{
	OF_INVALID_INIT_METHOD
}

- (instancetype)initWithObject: (id)object
			column: (int)column
		     statement: (SL3PreparedStatement *)statement
		     errorCode: (int)errorCode
{
	self = [super initWithConnection: statement->_connection
			       errorCode: errorCode];

	@try {
		_object = objc_retain(object);
		_statement = objc_retain(statement);
	} @catch (id e) {
		objc_release(self);
		@throw e;
	}

	return self;
}

- (void)dealloc
{
	objc_release(_object);
	objc_release(_statement);

	[super dealloc];
}
@end
