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

#import "SL3PreparedStatement.h"

OF_ASSUME_NONNULL_BEGIN

/**
 * @class SL3ExecuteStatementFailedException
 *	  SL3ExecuteStatementFailedException.h
 *	  ObjSQLite3/ObjSQLite3.h
 *
 * @brief An exception indicating that executing a statement failed.
 */
@interface SL3ExecuteStatementFailedException: SL3Exception
{
	SL3PreparedStatement *_Nullable _statement;
}

/**
 * @brief The statement that could not be executed.
 */
@property OF_NULLABLE_PROPERTY (readonly, nonatomic)
    SL3PreparedStatement *statement;

/**
 * @brief Creates a new execute statement failed exception.
 *
 * @param statement The statement that could not be executed
 * @param errorCode The SQLite3 error code
 * @return A new, autoreleased execute statement exception failed.
 */
+ (instancetype)exceptionWithStatement: (SL3PreparedStatement *)statement
			     errorCode: (int)errorCode;

/**
 * @brief Initializes an an already allocated execute statement failed
 *	  exception.
 *
 * @param statement The statement that could not be executed
 * @param errorCode The SQLite3 error code
 * @return An initialized execute statement exception failed.
 */
- (instancetype)initWithStatement: (SL3PreparedStatement *)statement
			errorCode: (int)errorCode;
@end

OF_ASSUME_NONNULL_END
