/*
 * Copyright (c) 2020, 2021, 2024 Jonathan Schleifer <js@nil.im>
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

#import "SL3PreparedStatement.h"
#import "SL3PreparedStatement+Private.h"

#import "SL3BindObjectFailedException.h"
#import "SL3ClearBindingsFailedException.h"
#import "SL3ExecuteStatementFailedException.h"
#import "SL3PrepareStatementFailedException.h"
#import "SL3ResetStatementFailedException.h"

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

		_connection = objc_retain(connection);
	} @catch (id e) {
		objc_release(self);
		@throw e;
	}

	return self;
}

- (void)dealloc
{
	sqlite3_finalize(_stmt);
	objc_release(_connection);

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
		    copy.UTF8String, copy.UTF8StringLength,
		    (void (*)(void *))(void (*)(void))objc_release,
		    SQLITE_UTF8);
	} else if ([object isKindOfClass: [OFData class]]) {
		OFData *copy = [object copy];

		code = sqlite3_bind_blob64(statement->_stmt, column, copy.items,
		    copy.count * copy.itemSize,
		    (void (*)(void *))(void (*)(void))objc_release);
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

	if (array.count > INT_MAX)
		@throw [OFOutOfRangeException exception];

	if ((int)array.count > sqlite3_bind_parameter_count(_stmt))
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

- (id)objectForCurrentRowAtColumn: (size_t)column
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
		OFEnsure(0);
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

- (OFArray *)currentRowArray
{
	size_t count = [self columnCount];
	OFMutableArray *array = [OFMutableArray arrayWithCapacity: count];

	for (size_t i = 0; i < count; i++)
		[array addObject: [self objectForCurrentRowAtColumn: i]];

	[array makeImmutable];

	return array;
}

- (OFDictionary OF_GENERIC(OFString *, id) *)currentRowDictionary
{
	size_t count = [self columnCount];
	OFMutableDictionary *dictionary =
	    [OFMutableDictionary dictionaryWithCapacity: count];

	for (size_t i = 0; i < count; i++)
		[dictionary setObject: [self objectForCurrentRowAtColumn: i]
			       forKey: [self nameForColumn: i]];

	[dictionary makeImmutable];

	return dictionary;
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
