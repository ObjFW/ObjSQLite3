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
 * @class SL3ResetStatementFailedException SL3ResetStatementFailedException.h
 *	  ObjSQLite3/ObjSQLite3.h
 *
 * @param An exception indicating that resetting a statement failed.
 */
@interface SL3ResetStatementFailedException: SL3Exception
{
	SL3PreparedStatement *_statement;
}

/**
 * @brief The statement that could not be reset.
 */
@property (readonly, nonatomic) SL3PreparedStatement *statement;

+ (instancetype)exceptionWithConnection: (nullable SL3Connection *)connection
			      errorCode: (int)errorCode OF_UNAVAILABLE;

/**
 * @brief Creates a new reset statement failed exception.
 *
 * @param statement The statement that could not be reset
 * @param errorCode The SQLite3 error code
 * @return A new, autoreleased reset statement failed exception.
 */
+ (instancetype)exceptionWithStatement: (SL3PreparedStatement *)statement
			     errorCode: (int)errorCode;

- (instancetype)initWithConnection: (nullable SL3Connection *)connection
			 errorCode: (int)errorCode OF_UNAVAILABLE;

/**
 * @brief Initializes an already allocated reset statement failed exception.
 *
 * @param statement The statement that could not be reset
 * @param errorCode The SQLite3 error code
 * @return An initialized reset statement failed exception.
 */
- (instancetype)initWithStatement: (SL3PreparedStatement *)statement
			errorCode: (int)errorCode OF_DESIGNATED_INITIALIZER;
@end

OF_ASSUME_NONNULL_END
