/*
 * Copyright (c) 2020, 2024, 2025 Jonathan Schleifer <js@nil.im>
 *
 * https://git.nil.im/ObjFW/ObjSQLite3
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

#import "SL3PreparedStatement.h"

OF_ASSUME_NONNULL_BEGIN

/**
 * @class SL3BindObjectFailedException SL3BindObjectFailedException.h
 *	  ObjSQLite3/ObjSQLite3.h
 *
 * @brief An exception indicating that binding an object to a prepared
 *	  statement failed.
 */
@interface SL3BindObjectFailedException: SL3Exception
{
	id _object;
	int _column;
	SL3PreparedStatement *_statement;
}

/**
 * @brief The object that could not be bound to a prepared statement.
 */
@property (readonly, nonatomic) id object;

/**
 * @brief The column of the prepared statement to which the object could not be
 *	  bound.
 */
@property (readonly, nonatomic) int column;

/**
 * @brief The statement to which the object could not be bound.
 */
@property (readonly, nonatomic) SL3PreparedStatement *statement;

+ (instancetype)exceptionWithConnection: (nullable SL3Connection *)connection
			      errorCode: (int)errorCode OF_UNAVAILABLE;

/**
 * @brief Creates an new bind object failed exception.
 *
 * @param object The object that could not be bound to a prepared statement
 * @param column The column of the prepared statement to which the object could
 *		 not be bound
 * @param statement The statement to which the object could not be bound
 * @param errorCode The SQLite3 error code
 * @return A new, autoreleased bind object failed exception
 */
+ (instancetype)exceptionWithObject: (id)object
			     column: (int)column
			  statement: (SL3PreparedStatement *)statement
			  errorCode: (int)errorCode;

- (instancetype)initWithConnection: (nullable SL3Connection *)connection
			 errorCode: (int)errorCode OF_UNAVAILABLE;

/**
 * @brief Initializes an already allocated bind object failed exception.
 *
 * @param object The object that could not be bound to a prepared statement
 * @param column The column of the prepared statement to which the object could
 *		 not be bound
 * @param statement The statement to which the object could not be bound
 * @param errorCode The SQLite3 error code
 * @return An initialized bind object failed exception
 */
- (instancetype)initWithObject: (id)object
			column: (int)column
		     statement: (SL3PreparedStatement *)statement
		     errorCode: (int)errorCode OF_DESIGNATED_INITIALIZER;
@end

OF_ASSUME_NONNULL_END
