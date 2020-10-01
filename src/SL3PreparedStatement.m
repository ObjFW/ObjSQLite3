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

#import "SL3PreparedStatement.h"
#import "SL3PreparedStatement+Private.h"

#import "SL3BindObjectFailedException.h"
#import "SL3ClearBindingsFailedException.h"
#import "SL3ExecuteStatementFailedException.h"
#import "SL3PrepareStatementFailedException.h"
#import "SL3ResetStatementFailedException.h"

static void
releaseObject(void *object)
{
	[(id)object release];
}

@implementation SL3PreparedStatement
- (instancetype)sl3_initWithConnection: (SL3Connection *)connection
			  SQLStatement: (OFConstantString *)SQLStatement
{
	self = [super init];

	@try {
		int code = sqlite3_prepare_v2(connection->_conn,
		    SQLStatement.UTF8String, SQLStatement.UTF8StringLength,
		    &_stmt, NULL);

		if (code != SQLITE_OK)
			@throw [SL3PrepareStatementFailedException
			    exceptionWithConnection: connection
				       SQLStatement: SQLStatement
					  errorCode: code];

		_connection = [connection retain];
	} @catch (id e) {
		[self release];
		@throw e;
	}

	return self;
}

- (void)dealloc
{
	sqlite3_finalize(_stmt);
	[_connection release];

	[super dealloc];
}

static void
bindObject(SL3PreparedStatement *statement, int column, id object)
{
	int code;

	if ([object isKindOfClass: [OFNumber class]]) {
		switch (*[object objCType]) {
		case 'f':
		case 'd':
			code = sqlite3_bind_double(statement->_stmt, column,
			    [object doubleValue]);
			break;
		/* TODO: Check for range when converting to signed. */
		default:
			code = sqlite3_bind_int64(statement->_stmt, column,
			    [object longLongValue]);
			break;
		}
	} else if ([object isKindOfClass: [OFString class]]) {
		OFString *copy = [object copy];

		code = sqlite3_bind_text64(statement->_stmt, column,
		    copy.UTF8String, copy.UTF8StringLength, releaseObject,
		    SQLITE_UTF8);
	} else if ([object isKindOfClass: [OFData class]]) {
		OFData *copy = [object copy];

		code = sqlite3_bind_blob64(statement->_stmt, column, copy.items,
		    copy.count * copy.itemSize, releaseObject);
	} else if ([object isEqual: [OFNull null]])
		code = sqlite3_bind_null(statement->_stmt, column);
	else
		@throw [OFInvalidArgumentException exception];

	if (code != SQLITE_OK)
		@throw [SL3BindObjectFailedException
		    exceptionWithObject: object
				 column: column
			      statement: statement
			      errorCode: code];
}

- (void)bindWithArray: (OFArray *)array
{
	void *pool = objc_autoreleasePoolPush();
	int column = 0;

	if (array.count > sqlite3_bind_parameter_count(_stmt))
		@throw [OFOutOfRangeException exception];

	for (id object in array)
		bindObject(self, ++column, object);

	objc_autoreleasePoolPop(pool);
}

- (void)bindWithDictionary:
    (OFDictionary OF_GENERIC(OFString *, id) *)dictionary
{
	void *pool = objc_autoreleasePoolPush();
	OFEnumerator OF_GENERIC(OFString *) *keyEnumerator =
	    [dictionary keyEnumerator];
	OFEnumerator *objectEnumerator = [dictionary objectEnumerator];
	OFString *key;
	id object;

	while ((key = [keyEnumerator nextObject]) != nil &&
	    (object = [objectEnumerator nextObject]) != nil) {
		int column = sqlite3_bind_parameter_index(
		    _stmt, key.UTF8String);

		if (column == 0)
			@throw [OFUndefinedKeyException
			    exceptionWithObject: self
					    key: key];

		bindObject(self, column, object);
	}

	objc_autoreleasePoolPop(pool);
}

- (void)clearBindings
{
	int code = sqlite3_clear_bindings(_stmt);

	if (code != SQLITE_OK)
		@throw [SL3ClearBindingsFailedException
		    exceptionWithStatement: self
				 errorCode: code];
}

- (bool)step
{
	int code = sqlite3_step(_stmt);

	if (code != SQLITE_DONE && code != SQLITE_ROW)
		@throw [SL3ExecuteStatementFailedException
		    exceptionWithStatement: self
				 errorCode: code];

	return (code == SQLITE_ROW);
}

- (id)objectForColumn: (size_t)column
{
	if (column > INT_MAX)
		@throw [OFOutOfRangeException exception];

	switch (sqlite3_column_type(_stmt, column)) {
	case SQLITE_INTEGER:
		return [OFNumber numberWithLongLong:
		    sqlite3_column_int64(_stmt, column)];
	case SQLITE_FLOAT:
		return [OFNumber numberWithDouble:
		    sqlite3_column_double(_stmt, column)];
	case SQLITE_TEXT:
		return [OFString stringWithUTF8String:
		    (const char *)sqlite3_column_text(_stmt, column)];
	case SQLITE_BLOB:
		return [OFData
		    dataWithItems: sqlite3_column_blob(_stmt, column)
			    count: sqlite3_column_bytes(_stmt, column)];
	case SQLITE_NULL:
		return [OFNull null];
	default:
		OF_ENSURE(0);
	}
}

- (size_t)columnCount
{
	return sqlite3_column_count(_stmt);
}

- (OFString *)nameForColumn: (size_t)column
{
	const char *name;

	if (column > [self columnCount])
		@throw [OFOutOfRangeException exception];

	if ((name = sqlite3_column_name(_stmt, column)) == NULL)
		@throw [OFOutOfMemoryException exception];

	return [OFString stringWithUTF8String: name];
}

- (void)reset
{
	int code = sqlite3_reset(_stmt);

	if (code != SQLITE_OK)
		@throw [SL3ResetStatementFailedException
		    exceptionWithStatement: self
				 errorCode: code];
}
@end
