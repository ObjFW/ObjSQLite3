/*
 * Copyright (c) 2020, 2024 Jonathan Schleifer <js@nil.im>
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

#import "SL3Exception.h"

OF_ASSUME_NONNULL_BEGIN

/**
 * @class SL3PrepareStatementFailedException
 *	  SL3PrepareStatementFailedException.h
 *	  ObjSQLite3/ObjSQLite3.h
 *
 * @brief An exception indicating that preparing a statement failed.
 */
@interface SL3PrepareStatementFailedException: SL3Exception
{
	OFConstantString *_SQLStatement;
}

/**
 * @brief The SQL statement which could not be prepared.
 */
@property (readonly, nonatomic) OFConstantString *SQLStatement;

+ (instancetype)exceptionWithConnection: (nullable SL3Connection *)connection
			      errorCode: (int)errorCode OF_UNAVAILABLE;

/**
 * @brief Creates a new prepare statement failed exception.
 *
 * @param connection The connection for which the statement could not be
 *		     prepared
 * @param SQLStatement The SQL statement which could not be prepared
 * @param errorCode The SQLite3 error code
 * @return A new, autoreleased prepare statement failed exception
 */
+ (instancetype)exceptionWithConnection: (SL3Connection *)connection
			   SQLStatement: (OFConstantString *)SQLStatement
			      errorCode: (int)errorCode;

- (instancetype)initWithConnection: (nullable SL3Connection *)connection
			 errorCode: (int)errorCode OF_UNAVAILABLE;

/**
 * @brief Initializes an already allocated prepare statement failed exception.
 *
 * @param connection The connection for which the statement could not be
 *		     prepared
 * @param SQLStatement The SQL statement which could not be prepared
 * @param errorCode The SQLite3 error code
 * @return An initialized prepare statement failed exception
 */
- (instancetype)initWithConnection: (SL3Connection *)connection
		      SQLStatement: (OFConstantString *)SQLStatement
			 errorCode: (int)errorCode OF_DESIGNATED_INITIALIZER;
@end

OF_ASSUME_NONNULL_END
