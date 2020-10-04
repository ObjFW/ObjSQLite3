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

#import "SL3Connection.h"
#import "SL3PreparedStatement.h"
#import "SL3PreparedStatement+Private.h"

#import "SL3ExecuteStatementFailedException.h"
#import "SL3OpenFailedException.h"

@implementation SL3Connection
+ (instancetype)connectionWithPath: (OFString *)path
{
	return [[[self alloc] initWithPath: path] autorelease];
}

+ (instancetype)connectionWithPath: (OFString *)path
			     flags: (int)flags
{
	return [[[self alloc] initWithPath: path
				     flags: flags] autorelease];
}

- (instancetype)initWithPath: (OFString *)path
{
	return [self initWithPath: path
			    flags: SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE];
}

- (instancetype)initWithPath: (OFString *)path
		       flags: (int)flags
{
	self = [super init];

	@try {
		int code = sqlite3_open_v2(path.UTF8String, &_conn, flags,
		    NULL);

		if (code != SQLITE_OK)
			@throw [SL3OpenFailedException exceptionWithPath: path
								   flags: flags
							       errorCode: code];
	} @catch (id e) {
		[self release];
		@throw e;
	}

	return self;
}

- (void)dealloc
{
	sqlite3_close(_conn);

	[super dealloc];
}

- (SL3PreparedStatement *)prepareStatement: (OFConstantString *)SQL
{
	return [[[SL3PreparedStatement alloc]
	    sl3_initWithConnection: self
		      SQLStatement: SQL] autorelease];
}

- (void)executeStatement: (OFConstantString *)SQL
{
	int code = sqlite3_exec(_conn, SQL.UTF8String, NULL, NULL, NULL);

	if (code != SQLITE_OK)
		@throw [SL3ExecuteStatementFailedException
		    exceptionWithConnection: self
				  errorCode: code];
}

#ifdef OF_HAVE_BLOCKS
- (void)transactionWithBlock: (bool (^)(void))block
{
	bool commit;

	[self executeStatement: @"BEGIN TRANSACTION"];

	@try {
		commit = block();
	} @catch (id e) {
		[self executeStatement: @"ROLLBACK TRANSACTION"];
		@throw e;
	}

	if (commit)
		[self executeStatement: @"COMMIT TRANSACTION"];
	else
		[self executeStatement: @"ROLLBACK TRANSACTION"];
}
#endif
@end
