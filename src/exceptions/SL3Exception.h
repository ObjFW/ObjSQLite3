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

#import <ObjFW/ObjFW.h>

#import "SL3Connection.h"

OF_ASSUME_NONNULL_BEGIN

/**
 * @class SL3Exception SL3Exception.h ObjSQLite3/ObjSQLite3.h
 *
 * @brief An SQLite3 exception.
 */
@interface SL3Exception: OFException
{
	SL3Connection *_Nullable _connection;
	int _errorCode;
}

/**
 * @brief The connection for which the exception occurred.
 */
@property OF_NULLABLE_PROPERTY (readonly, nonatomic) SL3Connection *connection;

/**
 * @brief The SQLite3 error code.
 */
@property (readonly, nonatomic) int errorCode;

+ (instancetype)exception OF_UNAVAILABLE;

/**
 * @brief Creates a new SQLite3 exception.
 *
 * @param connection The connection for which the exception occurred
 * @param errorCode The SQLite3 error code
 * @return A new, autoreleased SQLite3 exception
 */
+ (instancetype)exceptionWithConnection: (nullable SL3Connection *)connection
			      errorCode: (int)errorCode;

- (instancetype)init OF_UNAVAILABLE;

/**
 * @brief Initializes an already allocated SQLite3 exception.
 *
 * @param connection The connection for which the exception occurred
 * @param errorCode The SQLite3 error code
 * @return An initialized SQLite3 exception
 */
- (instancetype)initWithConnection: (nullable SL3Connection *)connection
			 errorCode: (int)errorCode OF_DESIGNATED_INITIALIZER;
@end

OF_ASSUME_NONNULL_END
